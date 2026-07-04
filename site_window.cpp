#include "site_window.h"
#include "ui_site_window.h"

#include "dialogue_text.h"
#include "pku_explorer_window.h"
#include "site_answer_book.h"
#include "site_dialogues.h"
#include "explorer_window_layout.h"
#include "game_progress.h"
#include "story_event_widget.h"
#include "site_graph.h"

#include <QCoreApplication>
#include <QDir>
#include <QEvent>
#include <QFileInfo>
#include <QKeyEvent>
#include <QLineEdit>
#include <QCloseEvent>
#include <QPixmap>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QWidget>
#include <QSizePolicy>
#include <QColor>
#include <QTimer>

namespace {

QPixmap loadScenePixmap(const QString &fileName)
{
    const QPixmap fromResource(QStringLiteral(":/images/") + fileName);
    if (!fromResource.isNull()) {
        return fromResource;
    }

    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList candidates = {
        QStringLiteral("images/") + fileName,
        QDir(appDir).filePath(QStringLiteral("../images/") + fileName),
        QDir(appDir).filePath(QStringLiteral("../../images/") + fileName),
        QDir(appDir).filePath(QStringLiteral("../../../images/") + fileName),
    };

    for (const QString &path : candidates) {
        if (!QFileInfo::exists(path)) {
            continue;
        }
        const QPixmap fromDisk(path);
        if (!fromDisk.isNull()) {
            return fromDisk;
        }
    }

    return {};
}

QString playerLine(const QString &text)
{
    return QStringLiteral("你：「%1」").arg(text);
}

} // namespace

Site_Window::Site_Window(int siteIndex, QWidget *parent)
    : QMainWindow(parent)
    , m_siteIndex(siteIndex)
    , ui(new Ui::Site_Window)
{
    ui->setupUi(this);
    const QString name = siteName(m_siteIndex);
    setWindowTitle(name);
    ui->lblSiteTitle->setText(name);

    if (isDialogueOnlySite(m_siteIndex)) {
        setupDialogueMode();
        return;
    }

    setAttribute(Qt::WA_QuitOnClose, false);
    setupChallengeModeStyles();
    ui->sceneStage->hide();
    ui->dialogueChoiceWidget->hide();
    ui->monumentChoiceWidget->hide();
    ui->lblChallengeHint->setText(QStringLiteral("请输入答案以通过："));
    ui->lblDialogue->hide();
    ui->lblClickHint->hide();

    updateProgressDisplay();
    connect(ui->btnNext, &QPushButton::clicked, this, &Site_Window::onNextClicked);
    connect(ui->btnSubmit, &QPushButton::clicked, this, &Site_Window::onSubmitAnswer);
    connect(ui->inputAnswer, &QLineEdit::returnPressed, this, &Site_Window::onSubmitAnswer);
}

Site_Window::~Site_Window()
{
    delete ui;
}

void Site_Window::setupChallengeModeStyles()
{
    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget#centralwidget { background: #16162a; color: #d0c8b8; }"
        "QLabel#lblSiteTitle { color: #e8c87a; font-size: 18px; font-weight: 600; }"
        "QLabel#lblProgress, QLabel#lblChallengeHint { color: #c8c0b0; font-size: 14px; }"
        "QPushButton { background: #14142c; color: #ede0c4; "
        "border: 1px solid rgba(190,160,80,210); border-radius: 4px; padding: 8px 20px; }"
        "QPushButton:hover { background: #2a2650; color: #fff8e0; }"
        "QLineEdit { background: #1e1e38; color: #e8e0d0; border: 1px solid rgba(140,120,60,160); "
        "border-radius: 4px; padding: 8px 12px; }"));
    applyMapLikeWindowSize();
}

void Site_Window::startDialogueTypewriter(const QString &plainText)
{
    if (m_storyWidget) {
        m_storyWidget->setNarrativeText(plainText, true);
    }
}

void Site_Window::finishDialogueTypewriter()
{
    if (m_storyWidget) {
        m_storyWidget->skipTypewriter();
    }
}

void Site_Window::skipDialogueTypewriter()
{
    finishDialogueTypewriter();
}

void Site_Window::setDialoguePlainText(const QString &plainText, bool typewriter)
{
    if (m_storyWidget) {
        m_storyWidget->setNarrativeText(plainText, typewriter);
    }
}

bool Site_Window::isTypewriterActive() const
{
    return m_storyWidget && m_storyWidget->isTypewriterActive();
}

void Site_Window::applyMapLikeWindowSize()
{
    applyExplorerWindowFrame(this, explorerWindowSizeFromParent(parentWidget()));
}

void Site_Window::setupDialogueMode()
{
    m_dialogueMode = true;
    m_skipSiteCompletion = false;
    if (m_siteIndex == kLuIslandSiteId) {
        const auto *explorer = qobject_cast<const PKU_Explorer_Window *>(parentWidget());
        const LuIslandVisitMode mode =
            explorer ? luIslandVisitModeFor(explorer->siteStates()) : LuIslandVisitMode::ShoreView;
        m_dialogueBeats = luIslandDialogueBeatsForMode(mode);
        m_skipSiteCompletion = (mode != LuIslandVisitMode::Finale);
    } else {
        m_dialogueBeats = dialogueBeatsForSite(m_siteIndex);
    }
    m_dialogueStep = 0;
    m_waitingForInput = false;
    m_currentSceneImageFile.clear();
    m_currentLeftPortraitFile.clear();
    m_currentRightPortraitFile.clear();

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_QuitOnClose, false);
    applyStoryDialogFrame(this, explorerWindowSizeFromParent(parentWidget()));
    setMenuBar(nullptr);
    setStatusBar(nullptr);
    ui->centralwidget->setStyleSheet(QStringLiteral("background: #0e0e16;"));

    ui->lblSiteTitle->hide();
    ui->sceneStage->hide();
    ui->lblDialogue->hide();
    ui->dialogueChoiceWidget->hide();
    ui->monumentChoiceWidget->hide();
    ui->lblClickHint->hide();
    ui->lblProgress->hide();
    ui->btnNext->hide();
    ui->challengeWidget->hide();

    if (!m_storyWidget) {
        m_storyWidget = new StoryEventWidget(ui->centralwidget);
        ui->verticalLayout->insertWidget(0, m_storyWidget, 1);
        connect(m_storyWidget, &StoryEventWidget::advanceRequested, this, &Site_Window::advanceDialogue);
        connect(m_storyWidget, &StoryEventWidget::choiceARequested, this, &Site_Window::onDialogueChoiceA);
        connect(m_storyWidget, &StoryEventWidget::choiceBRequested, this, &Site_Window::onDialogueChoiceB);
        connect(m_storyWidget, &StoryEventWidget::choiceCRequested, this, &Site_Window::onDialogueChoiceC);
        connect(m_storyWidget, &StoryEventWidget::monumentDeferRequested, this, &Site_Window::onMonumentDefer);
        connect(m_storyWidget, &StoryEventWidget::monumentSubmitRequested, this, &Site_Window::onMonumentSubmit);
        connect(m_storyWidget, &StoryEventWidget::closeRequested, this, &Site_Window::close);
    }

    m_storyWidget->setEventTitle(m_siteIndex == kInitialStartSiteId
                                     ? QStringLiteral("序章·魔咒设计实习")
                                     : m_siteIndex == kMirrorLakeSiteId
                                           ? QStringLiteral("镜湖·无风之夜")
                                           : m_siteIndex == kArcaneTowerSiteId
                                                 ? QStringLiteral("奥术尖塔·永恒的光")
                                                 : m_siteIndex == kLuIslandSiteId && m_skipSiteCompletion
                                                       ? QStringLiteral("湖心岛")
                                                       : siteName(m_siteIndex));
    m_storyWidget->setDialogueSiteId(m_siteIndex);
    setFocusPolicy(Qt::StrongFocus);
    updateDialogueDisplay();
}

bool Site_Window::isWaitingForInput() const
{
    return m_waitingForInput;
}

void Site_Window::hideDialogueInteractions()
{
    m_waitingForInput = false;
    if (m_storyWidget) {
        m_storyWidget->hideInteractions();
    }
}

void Site_Window::showBinaryChoice(const DialogueBeat &beat)
{
    m_waitingForInput = true;
    if (m_storyWidget) {
        m_storyWidget->showChoiceButtons(beat.choiceA, beat.choiceB);
    }
}

void Site_Window::showMultiChoice(const DialogueBeat &beat)
{
    m_waitingForInput = true;
    if (m_storyWidget) {
        m_storyWidget->showChoiceButtons(beat.choiceA, beat.choiceB, beat.choiceC);
    }
}

void Site_Window::switchDialogueSequence(const QVector<DialogueBeat> &beats)
{
    m_dialogueBeats = beats;
    m_dialogueStep = 0;
    updateDialogueDisplay();
}

void Site_Window::appendDialogueAfterChoice(const QVector<DialogueBeat> &followUp)
{
    hideDialogueInteractions();
    m_dialogueBeats.resize(m_dialogueStep + 1);
    m_dialogueBeats.append(followUp);
    ++m_dialogueStep;
    updateDialogueDisplay();
}

void Site_Window::insertPlayerAndNpcLines(const QString &playerText,
                                          const QString &npcLine,
                                          const QString &sceneImageFile,
                                          const QString &npcPortraitFile)
{
    const int insertAt = m_dialogueStep + 1;
    m_dialogueBeats.insert(insertAt, narrationBeat(npcLine, sceneImageFile, npcPortraitFile));
    m_dialogueBeats.insert(insertAt, narrationBeat(playerLine(playerText), sceneImageFile));

    m_dialogueStep = insertAt;
    updateDialogueDisplay();
}

void Site_Window::showMirrorLakeTowerDecision()
{
    m_waitingForInput = true;
    setDialoguePlainText(QStringLiteral("你：（斟酌该如何作答。）"), false);
    applyStoryPortraits(narrationBeat({}, {}));
    if (m_storyWidget) {
        m_storyWidget->showMonumentInput(QStringLiteral("我再想想"),
                                         QStringLiteral("告诉我所见塔的层数，唤醒镜湖的魔法"),
                                         QStringLiteral("填写层数"));
    }
}

void Site_Window::showMonumentDecision()
{
    m_waitingForInput = true;
    setDialoguePlainText(QStringLiteral("你：（沉默片刻，斟酌如何作答……）"), true);
    applyStoryPortraits(narrationBeat({}, {}));
    if (m_storyWidget) {
        m_storyWidget->showMonumentInput(QStringLiteral("看来我对这个园子还有待探索"),
                                         QStringLiteral("我知道，他就在"),
                                         QStringLiteral("填写地点"));
    }
}

void Site_Window::showForbiddenArchiveCatalogDecision(const QString &sceneImageFile)
{
    m_waitingForInput = true;
    setDialoguePlainText(QStringLiteral("你：（旧目录卡缺了一截，你在脑子里拼索书号。）"), false);
    applyStoryPortraits(narrationBeat({}, {}));
    if (m_storyWidget) {
        m_storyWidget->showMonumentInput(
            QStringLiteral("先逛逛别的"),
            QStringLiteral("《原神之力》的索书号"),
            QStringLiteral("填写索书号"));
    }
    if (!sceneImageFile.isEmpty()) {
        applyStoryBackground(sceneImageFile);
    }
}

void Site_Window::showOldRealmShopNameDecision(const QString &sceneImageFile)
{
    m_waitingForInput = true;
    setDialoguePlainText(QStringLiteral("你：（打量那块几乎认不出字的招牌。）"), false);
    applyStoryPortraits(narrationBeat({}, {}));
    if (m_storyWidget) {
        m_storyWidget->showMonumentInput(QStringLiteral("离开这里"),
                                         QStringLiteral("你在招牌下，用手写下这家店的名称"),
                                         QStringLiteral("填写店名"));
    }
    if (!sceneImageFile.isEmpty()) {
        applyStoryBackground(sceneImageFile);
    }
}

void Site_Window::showTheaterMuralDecision()
{
    m_waitingForInput = true;
    setDialoguePlainText(QStringLiteral("你：（CM.J在等你说。）"), true);
    applyStoryPortraits(narrationBeat({}, {}));
    if (m_storyWidget) {
        m_storyWidget->showMonumentInput(QStringLiteral("我还不知道"),
                                         QStringLiteral("《踏秋图》的作者是"),
                                         QStringLiteral("填写作者姓名"));
    }
}

void Site_Window::handleTavernFirstChoice(const QString &playerText, const QString &bossReply)
{
    hideDialogueInteractions();
    insertPlayerAndNpcLines(
        playerText, bossReply, tavernBossBackgroundFile(), barPublicanPortraitFile());
}

void Site_Window::handleArcaneTowerChoice(bool enterTower)
{
    hideDialogueInteractions();

    const QString bgDoor = arcaneTowerDoorBackgroundFile();

    if (enterTower) {
        QVector<DialogueBeat> followUp = {
            narrationBeat(playerLine(QStringLiteral("推门上塔")), bgDoor),
        };
        followUp.append(arcaneTowerClimbBeats());
        appendDialogueAfterChoice(followUp);
        return;
    }

    QVector<DialogueBeat> followUp = {
        narrationBeat(playerLine(QStringLiteral("转身离去，不打扰")), bgDoor),
    };
    followUp.append(arcaneTowerLeaveBeats());
    appendDialogueAfterChoice(followUp);
}

void Site_Window::handleArenaJoinChoice(bool joinBattle)
{
    const QString bgEnter = arenaEntranceBackgroundFile();
    const QString bgSpectator = arenaSpectatorBackgroundFile();
    const QString witch = witchPortraitFile();

    if (joinBattle) {
        QVector<DialogueBeat> followUp = {
            narrationBeat(playerLine(QStringLiteral("下场参战")), bgEnter),
            narrationBeat(QStringLiteral("小魔女：「好。先别急着冲——」"), bgEnter, witch),
        };
        followUp.append(arenaJoinTrainingBeats());
        appendDialogueAfterChoice(followUp);
        return;
    }

    QVector<DialogueBeat> followUp = {
        narrationBeat(playerLine(QStringLiteral("留在场边观看")), bgEnter),
        narrationBeat(QStringLiteral("小魔女：「也好。先看清楚这里的规矩。」"), bgSpectator, witch),
    };
    followUp.append(arenaSpectatorBeats());
    appendDialogueAfterChoice(followUp);
}

void Site_Window::handleArenaExerciseChoice(bool exercisedToday)
{
    const QString bgSpectator = arenaSpectatorBackgroundFile();
    const QString witch = witchPortraitFile();

    if (exercisedToday) {
        QVector<DialogueBeat> followUp = {
            narrationBeat(playerLine(QStringLiteral("有，今天去过五四操场")), bgSpectator),
            narrationBeat(QStringLiteral("小魔女：「那就上吧。把训练兑现成胜利。」"), bgSpectator, witch),
        };
        followUp.append(arenaVictoryBeats());
        appendDialogueAfterChoice(followUp);
        return;
    }

    QVector<DialogueBeat> followUp = {
        narrationBeat(playerLine(QStringLiteral("还没有")), bgSpectator),
        narrationBeat(QStringLiteral("小魔女：「先去五四操场练练再来。角斗场不认侥幸。」"), bgSpectator, witch),
    };
    followUp.append(arenaSpectatorBeats());
    appendDialogueAfterChoice(followUp);
}

void Site_Window::handleTheaterViewChoice(bool viewGlassMural)
{
    const QString bgTalk = theaterMuralTalkBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString assistance = theaterAssistancePortraitFile();

    hideDialogueInteractions();
    QVector<DialogueBeat> followUp;
    if (viewGlassMural) {
        followUp = {
            narrationBeat(playerLine(QStringLiteral("等雾起，看玻璃里的那一幅")), bgTalk),
            narrationBeat(QStringLiteral("（雾里人影一闪。CM.J把你拉回半步。）"), bgTalk),
            narrationBeat(QStringLiteral("CM.J：「别盯太久。」"), bgTalk, assistance),
            narrationBeat(QStringLiteral("小魔女：「签名在墙边，不在传说里。《踏秋图》也是。」"), bgTalk, witch),
        };
    } else {
        followUp = {
            narrationBeat(playerLine(QStringLiteral("先去看石壁上的画")), bgTalk),
        };
    }
    followUp.append(theaterMuralTalkBeats());
    followUp.append(theaterMuralViewBeats());
    appendDialogueAfterChoice(followUp);
}

void Site_Window::handleTianmenChoice(bool leaveMagicWorld)
{
    hideDialogueInteractions();

    if (leaveMagicWorld) {
        m_tianmenFirstChoiceStep = m_dialogueStep;
        const QString bg3 = gateBackground3File();
        QVector<DialogueBeat> followUp = {
            narrationBeat(playerLine(QStringLiteral("往外走。")), bg3),
        };
        followUp.append(tianmenLeaveApproachBeats());
        appendDialogueAfterChoice(followUp);
        return;
    }

    const QString bg4 = gateBackground4File();
    QVector<DialogueBeat> followUp = {
        narrationBeat(playerLine(QStringLiteral("离开天门，回到园中。")), bg4),
    };
    followUp.append(tianmenContinueEndingBeats());
    appendDialogueAfterChoice(followUp);
}

void Site_Window::handleTianmenConfirmLeave(bool confirmLeave)
{
    hideDialogueInteractions();

    if (confirmLeave) {
        m_endWithDreamWake = true;
        const QString bg3 = gateBackground3File();
        QVector<DialogueBeat> followUp = {
            narrationBeat(playerLine(QStringLiteral("确认离开魔法世界")), bg3),
        };
        followUp.append(tianmenLeaveHandoffBeats());
        appendDialogueAfterChoice(followUp);
        return;
    }

    m_endWithDreamWake = false;
    if (m_tianmenFirstChoiceStep >= 0 && m_tianmenFirstChoiceStep < m_dialogueBeats.size()) {
        m_dialogueBeats.resize(m_tianmenFirstChoiceStep + 1);
        m_dialogueStep = m_tianmenFirstChoiceStep;
        updateDialogueDisplay();
    }
}

void Site_Window::handleLuIslandChoice(bool returnToRealWorld)
{
    hideDialogueInteractions();

    const QString bg = islandBackgroundFile();

    if (returnToRealWorld) {
        m_endWithLuIslandReturn = true;
        QVector<DialogueBeat> followUp = {
            narrationBeat(playerLine(luIslandLeaveChoiceText()), bg),
        };
        followUp.append(luIslandReturnTransitionBeats());
        appendDialogueAfterChoice(followUp);
        return;
    }

    if (mirrorLakePath() != MirrorLakePath::StoneBoat) {
        appendDialogueAfterChoice(luIslandBridgeStayPersuasionBeats());
        return;
    }

    m_endWithLuIslandStay = true;
    QVector<DialogueBeat> followUp = {
        narrationBeat(playerLine(luIslandStayChoiceText()), bg),
    };
    followUp.append(luIslandStayTransitionBeats());
    appendDialogueAfterChoice(followUp);
}

void Site_Window::startTavernEnding(bool befriendedTraveler, const QString &playerLine)
{
    hideDialogueInteractions();
    m_dialogueBeats = befriendedTraveler ? tavernGoodEndingBeats(playerLine)
                                         : tavernPartingEndingBeats(playerLine);
    m_dialogueStep = 0;
    updateDialogueDisplay();
}

void Site_Window::startTheaterEnding(bool muralsAligned, const QString &playerLine, bool wrongGuess)
{
    hideDialogueInteractions();
    if (muralsAligned) {
        m_dialogueBeats = theaterAlignedEndingBeats(playerLine);
    } else if (wrongGuess) {
        m_dialogueBeats = theaterWrongAnswerEndingBeats(playerLine);
    } else {
        m_dialogueBeats = theaterPendingEndingBeats(playerLine);
    }
    m_dialogueStep = 0;
    updateDialogueDisplay();
}

void Site_Window::finishDialogue()
{
    if (m_endWithDreamWake) {
        emit dreamWakeEnding();
        close();
        return;
    }

    if (m_endWithLuIslandReturn) {
        emit luIslandReturnEnding();
        close();
        return;
    }

    if (m_endWithLuIslandStay) {
        emit luIslandStayEnding();
        close();
        return;
    }

    if (m_skipSiteCompletion) {
        close();
        return;
    }

    emit siteCompleted(m_siteIndex);
    close();
}

void Site_Window::applyStoryBackground(const QString &sceneImageFile)
{
    if (sceneImageFile == m_currentSceneImageFile) {
        return;
    }

    m_currentSceneImageFile = sceneImageFile;
    if (!m_storyWidget) {
        return;
    }

    if (sceneImageFile.isEmpty()) {
        m_storyWidget->clearBackground();
        return;
    }

    m_storyWidget->setBackgroundPixmap(loadScenePixmap(sceneImageFile));
}

void Site_Window::applyStoryPortraits(const DialogueBeat &beat)
{
    if (!m_storyWidget) {
        return;
    }

    m_storyWidget->clearPortraits();

    const QString portraitFile = speakerPortraitForLine(beat.line);
    if (portraitFile.isEmpty()) {
        return;
    }

    if (portraitFile == theaterAssistancePortraitFile()) {
        m_storyWidget->setRightPortrait(loadScenePixmap(portraitFile), true);
        return;
    }

    if (portraitFile == williamYangPortraitFile()) {
        m_storyWidget->setLeftPortrait(loadScenePixmap(portraitFile), false, true, true);
        return;
    }

    m_storyWidget->setRightPortrait(loadScenePixmap(portraitFile));
}

void Site_Window::updateDialogueDisplay()
{
    if (!m_dialogueMode || !m_storyWidget || m_dialogueStep >= m_dialogueBeats.size()) {
        return;
    }

    const DialogueBeat &beat = m_dialogueBeats.at(m_dialogueStep);
    applyStoryBackground(beat.sceneImageFile);

    if (beat.type == DialogueBeatType::BinaryChoice) {
        applyStoryPortraits(narrationBeat({}, {}));
        setDialoguePlainText(QStringLiteral("你"), false);
        showBinaryChoice(beat);
        return;
    }

    if (beat.type == DialogueBeatType::MultiChoice) {
        applyStoryPortraits(narrationBeat({}, {}));
        setDialoguePlainText(QStringLiteral("你"), false);
        showMultiChoice(beat);
        return;
    }

    if (beat.type == DialogueBeatType::MirrorLakeTowerDecision) {
        showMirrorLakeTowerDecision();
        return;
    }

    if (beat.type == DialogueBeatType::TavernMonumentDecision) {
        showMonumentDecision();
        return;
    }

    if (beat.type == DialogueBeatType::TheaterMuralDecision) {
        showTheaterMuralDecision();
        return;
    }

    if (beat.type == DialogueBeatType::OldRealmShopNameDecision) {
        showOldRealmShopNameDecision(beat.sceneImageFile);
        return;
    }

    if (beat.type == DialogueBeatType::ForbiddenArchiveCatalogDecision) {
        showForbiddenArchiveCatalogDecision(beat.sceneImageFile);
        return;
    }

    hideDialogueInteractions();
    applyStoryPortraits(beat);
    setDialoguePlainText(beat.line, true);
}

void Site_Window::advanceDialogue()
{
    if (!m_dialogueMode || isWaitingForInput()) {
        return;
    }

    if (isTypewriterActive()) {
        skipDialogueTypewriter();
        return;
    }

    ++m_dialogueStep;
    if (m_dialogueStep >= m_dialogueBeats.size()) {
        finishDialogue();
        return;
    }

    updateDialogueDisplay();
}

void Site_Window::onDialogueChoiceA()
{
    if (!m_dialogueMode || m_dialogueStep >= m_dialogueBeats.size()) {
        return;
    }

    const DialogueBeat &beat = m_dialogueBeats.at(m_dialogueStep);
    switch (beat.choiceKind) {
    case DialogueChoiceKind::TavernFirstReply:
        handleTavernFirstChoice(beat.choiceA, tavernBossReplyAfterWine());
        break;
    case DialogueChoiceKind::ArenaJoinBattle:
        handleArenaJoinChoice(true);
        break;
    case DialogueChoiceKind::ArcaneTowerEnterOrLeave:
        handleArcaneTowerChoice(true);
        break;
    case DialogueChoiceKind::ArenaExerciseToday:
        handleArenaExerciseChoice(true);
        break;
    case DialogueChoiceKind::TheaterViewMural:
        handleTheaterViewChoice(false);
        break;
    case DialogueChoiceKind::TianmenLeaveOrStay:
        handleTianmenChoice(true);
        break;
    case DialogueChoiceKind::TianmenConfirmLeave:
        handleTianmenConfirmLeave(true);
        break;
    case DialogueChoiceKind::LuIslandFinalChoice:
        handleLuIslandChoice(true);
        break;
    case DialogueChoiceKind::LuIslandReturnOnly:
        handleLuIslandChoice(true);
        break;
    case DialogueChoiceKind::SpellHallPrologueChoice:
        handleSpellHallChoice(0);
        break;
    case DialogueChoiceKind::OldRealmEnterShop:
        handleOldRealmEnterChoice(true);
        break;
    case DialogueChoiceKind::RuinGardenLightOrShade:
        handleRuinGardenPathChoice(true);
        break;
    case DialogueChoiceKind::RuinGardenStayOrLeave:
        handleRuinGardenHeartChoice(true);
        break;
    case DialogueChoiceKind::ForbiddenArchiveVisitIntent:
        handleForbiddenArchiveVisitChoice(true);
        break;
    case DialogueChoiceKind::ForbiddenArchiveGenesisBookFamiliarity:
        handleForbiddenArchiveBookFamiliarityChoice(true);
        break;
    default:
        break;
    }
}

void Site_Window::onDialogueChoiceB()
{
    if (!m_dialogueMode || m_dialogueStep >= m_dialogueBeats.size()) {
        return;
    }

    const DialogueBeat &beat = m_dialogueBeats.at(m_dialogueStep);
    switch (beat.choiceKind) {
    case DialogueChoiceKind::TavernFirstReply:
        handleTavernFirstChoice(beat.choiceB, tavernBossReplyAfterTalk());
        break;
    case DialogueChoiceKind::ArenaJoinBattle:
        handleArenaJoinChoice(false);
        break;
    case DialogueChoiceKind::ArcaneTowerEnterOrLeave:
        handleArcaneTowerChoice(false);
        break;
    case DialogueChoiceKind::ArenaExerciseToday:
        handleArenaExerciseChoice(false);
        break;
    case DialogueChoiceKind::TheaterViewMural:
        handleTheaterViewChoice(true);
        break;
    case DialogueChoiceKind::TianmenLeaveOrStay:
        handleTianmenChoice(false);
        break;
    case DialogueChoiceKind::TianmenConfirmLeave:
        handleTianmenConfirmLeave(false);
        break;
    case DialogueChoiceKind::LuIslandFinalChoice:
        handleLuIslandChoice(false);
        break;
    case DialogueChoiceKind::SpellHallPrologueChoice:
        handleSpellHallChoice(1);
        break;
    case DialogueChoiceKind::OldRealmEnterShop:
        handleOldRealmEnterChoice(false);
        break;
    case DialogueChoiceKind::RuinGardenLightOrShade:
        handleRuinGardenPathChoice(false);
        break;
    case DialogueChoiceKind::RuinGardenStayOrLeave:
        handleRuinGardenHeartChoice(false);
        break;
    case DialogueChoiceKind::ForbiddenArchiveVisitIntent:
        handleForbiddenArchiveVisitChoice(false);
        break;
    case DialogueChoiceKind::ForbiddenArchiveGenesisBookFamiliarity:
        handleForbiddenArchiveBookFamiliarityChoice(false);
        break;
    default:
        break;
    }
}

void Site_Window::onDialogueChoiceC()
{
    if (!m_dialogueMode || m_dialogueStep >= m_dialogueBeats.size()) {
        return;
    }

    const DialogueBeat &beat = m_dialogueBeats.at(m_dialogueStep);
    if (beat.choiceKind == DialogueChoiceKind::SpellHallPrologueChoice) {
        handleSpellHallChoice(2);
    }
}

void Site_Window::handleForbiddenArchiveVisitChoice(bool casualBrowse)
{
    hideDialogueInteractions();
    appendDialogueAfterChoice(forbiddenArchiveVisitChoiceFollowUp(casualBrowse));
}

void Site_Window::handleForbiddenArchiveBookFamiliarityChoice(bool heardBefore)
{
    hideDialogueInteractions();
    appendDialogueAfterChoice(forbiddenArchiveBookFamiliarityFollowUp(heardBefore));
}

void Site_Window::handleOldRealmEnterChoice(bool enterShop)
{
    hideDialogueInteractions();
    if (enterShop) {
        appendDialogueAfterChoice(oldRealmShopMemoryBeats());
        return;
    }
    appendDialogueAfterChoice(oldRealmDeclineEntryBeats());
}

void Site_Window::handleRuinGardenPathChoice(bool takeLightPath)
{
    hideDialogueInteractions();
    appendDialogueAfterChoice(takeLightPath ? ruinGardenLightPathFollowUpBeats()
                                           : ruinGardenShadePathFollowUpBeats());
}

void Site_Window::handleRuinGardenHeartChoice(bool stayLonger)
{
    hideDialogueInteractions();
    appendDialogueAfterChoice(stayLonger ? ruinGardenStayFollowUpBeats()
                                         : ruinGardenLeaveFollowUpBeats());
}

void Site_Window::handleSpellHallChoice(int choiceIndex)
{
    hideDialogueInteractions();
    appendDialogueAfterChoice(spellHallChoiceFollowUpBeats(choiceIndex));
}

void Site_Window::onMonumentDefer()
{
    if (m_siteIndex == kForbiddenArchiveSiteId) {
        hideDialogueInteractions();
        appendDialogueAfterChoice(forbiddenArchiveDeferBeats());
        return;
    }

    if (m_siteIndex == kOldRealmSiteId) {
        hideDialogueInteractions();
        appendDialogueAfterChoice(oldRealmSilentLeaveBeats());
        return;
    }

    if (m_siteIndex == kMirrorLakeSiteId) {
        hideDialogueInteractions();
        m_skipSiteCompletion = true;
        appendDialogueAfterChoice(mirrorLakeDeferBeats());
        return;
    }

    if (m_siteIndex == kTheaterSiteId) {
        startTheaterEnding(false, playerLine(QStringLiteral("……我还不知道。")));
        return;
    }

    startTavernEnding(false, playerLine(QStringLiteral("看来我对这个园子还有待探索")));
}

void Site_Window::onMonumentSubmit()
{
    const QString answer = m_storyWidget ? m_storyWidget->monumentAnswer() : QString();

    if (m_siteIndex == kForbiddenArchiveSiteId) {
        if (answer.isEmpty()) {
            onMonumentDefer();
            return;
        }

        if (!checkForbiddenArchiveCatalogAnswer(answer)) {
            hideDialogueInteractions();
            QVector<DialogueBeat> followUp = forbiddenArchiveWrongShelfBeats(answer);
            followUp.append(forbiddenArchiveCatalogDecisionBeat());
            appendDialogueAfterChoice(followUp);
            return;
        }

        hideDialogueInteractions();
        appendDialogueAfterChoice(forbiddenArchiveCorrectShelfBeats());
        return;
    }

    if (m_siteIndex == kOldRealmSiteId) {
        if (answer.isEmpty()) {
            onMonumentDefer();
            return;
        }

        if (!checkOldRealmShopNameAnswer(answer)) {
            hideDialogueInteractions();
            QVector<DialogueBeat> followUp = oldRealmWrongNameBeats();
            followUp.append(oldRealmShopNameDecisionBeat());
            appendDialogueAfterChoice(followUp);
            return;
        }

        hideDialogueInteractions();
        QVector<DialogueBeat> followUp = oldRealmDoorRevealBeats();
        followUp.append(binaryChoiceBeat(DialogueChoiceKind::OldRealmEnterShop,
                                         oldRealmShopDoorFile(),
                                         QStringLiteral("推开门进去"),
                                         QStringLiteral("今天先离开")));
        appendDialogueAfterChoice(followUp);
        return;
    }

    if (m_siteIndex == kMirrorLakeSiteId) {
        if (answer.isEmpty()) {
            onMonumentDefer();
            return;
        }

        const int towerCount = parseMirrorLakeTowerAnswer(answer);
        if (towerCount == 0) {
            hideDialogueInteractions();
            m_skipSiteCompletion = true;
            appendDialogueAfterChoice(mirrorLakeWrongAnswerBeats(answer));
            return;
        }

        hideDialogueInteractions();
        setMirrorLakePath(towerCount == 26 ? MirrorLakePath::StoneBoat : MirrorLakePath::Bridge);
        appendDialogueAfterChoice(mirrorLakeTowerAnswerBeats(towerCount));
        return;
    }

    if (m_siteIndex == kTheaterSiteId) {
        if (answer.isEmpty()) {
            startTheaterEnding(false, playerLine(QStringLiteral("……我还不知道。")));
            return;
        }

        const QString playerLineText =
            QStringLiteral("你：「《踏秋图》的作者是%1。」").arg(answer);
        const bool aligned = checkTheaterMuralAuthorAnswer(answer);
        startTheaterEnding(aligned, playerLineText, !aligned);
        return;
    }

    if (answer.isEmpty()) {
        startTavernEnding(false, playerLine(QStringLiteral("……我还不知道。")));
        return;
    }

    const QString playerLineText =
        QStringLiteral("你：「我知道，他就在%1。」").arg(answer);
    startTavernEnding(checkTavernMonumentAnswer(answer), playerLineText);
}

bool Site_Window::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    Q_UNUSED(event);
    return QMainWindow::eventFilter(watched, event);
}

void Site_Window::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
        event->accept();
        return;
    }

    if (m_dialogueMode && !isWaitingForInput()) {
        advanceDialogue();
        event->accept();
        return;
    }
    QMainWindow::keyPressEvent(event);
}

void Site_Window::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

void Site_Window::updateProgressDisplay() const
{
    if (m_challengeActive) {
        ui->lblProgress->setText(QStringLiteral("Next 已完成，请提交答案"));
        return;
    }

    ui->lblProgress->setText(
        QStringLiteral("本次 Next：%1 / %2").arg(m_sessionClickCount).arg(m_siteIndex));
}

void Site_Window::enterChallengePhase()
{
    m_challengeActive = true;
    ui->btnNext->setEnabled(false);
    ui->challengeWidget->setVisible(true);
    ui->lblVerdict->clear();
    ui->inputAnswer->clear();
    ui->inputAnswer->setFocus();
    updateProgressDisplay();
}

void Site_Window::showVerdict(const QString &text, const QString &color)
{
    ui->lblVerdict->setText(text);
    ui->lblVerdict->setStyleSheet(
        QStringLiteral("color: %1; font-size: 16px; font-weight: bold;").arg(color));
}

void Site_Window::onNextClicked()
{
    if (m_dialogueMode || m_challengeActive) {
        return;
    }

    ++m_sessionClickCount;
    updateProgressDisplay();

    if (m_sessionClickCount >= m_siteIndex) {
        enterChallengePhase();
    }
}

void Site_Window::onSubmitAnswer()
{
    if (m_dialogueMode || !m_challengeActive) {
        return;
    }

    if (SiteAnswerBook::instance().checkAnswer(m_siteIndex, ui->inputAnswer->text())) {
        showVerdict(QStringLiteral("AC"), QStringLiteral("#1a7f37"));
        emit siteCompleted(m_siteIndex);
        close();
        return;
    }

    showVerdict(QStringLiteral("WA"), QStringLiteral("#c62828"));
    ui->inputAnswer->setFocus();
    ui->inputAnswer->selectAll();
}
