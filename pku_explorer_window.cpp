#include "pku_explorer_window.h"
#include "ui_pku_explorer_window.h"

#include "explorer_map_widget.h"
#include "finish_window.h"
#include "ending_window.h"
#include "game_progress.h"
#include "site_answer_book.h"
#include "site_dialogues.h"
#include "site_graph.h"
#include "site_window.h"

#include <QCloseEvent>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QTimer>
#include <QVBoxLayout>
#include "explorer_window_layout.h"

namespace {

QString siteStateKey(int index)
{
    return QStringLiteral("siteState/button%1").arg(index);
}

QString legacyUnlockKey(int index)
{
    return QStringLiteral("unlocked/button%1").arg(index);
}

QString legacyClickCountKey(int index)
{
    return QStringLiteral("clickCount/button%1").arg(index);
}

SiteState loadSiteState(QSettings &settings, int buttonIndex)
{
    SiteState defaultState = SiteState::Locked;
    if (isInitialStartSite(buttonIndex)) {
        defaultState = SiteState::ToExplore;
    } else if (isLuIslandSite(buttonIndex)) {
        defaultState = SiteState::Locked;
    }

    if (settings.contains(siteStateKey(buttonIndex))) {
        return siteStateFromVariant(settings.value(siteStateKey(buttonIndex)), defaultState);
    }

    if (settings.contains(legacyUnlockKey(buttonIndex))) {
        return settings.value(legacyUnlockKey(buttonIndex)).toBool() ? SiteState::ToExplore
                                                                     : SiteState::Locked;
    }

    return defaultState;
}

} // namespace

PKU_Explorer_Window::PKU_Explorer_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PKU_Explorer_Window)
{
    ui->setupUi(this);

    applyExplorerWindowFrame(this);
    setWindowTitle(QStringLiteral("PKU-Explorer"));

    setMenuBar(nullptr);
    setStatusBar(nullptr);

    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget { background: #16162a; color: #d0c8b8; }"
        "QProgressBar { border: 1px solid #4a4a7a; border-radius: 4px; background: #1e1e38; }"
        "QProgressBar::chunk { background: #7f77dd; }"
        "QListWidget { background: #1e1e38; border: 1px solid #3a3a5a; color: #d0c8b8; }"
        "QPushButton#btnReset {"
        "    background: #1c1c38; color: #e8d5a3; border: 1px solid rgba(180,150,70,180);"
        "    border-radius: 4px; padding: 10px 24px; font-size: 14px; }"
        "QPushButton#btnReset:hover {"
        "    background: #2a2a50; border-color: rgba(220,185,90,240); }"
        "QLabel#lblExploredProgress { color: #e8c87a; font-size: 15px; font-weight: 600; }"
        "QLabel#lblPanelTitle { color: #c8c0b0; font-size: 13px; font-weight: 600; }"));

    auto *splitter = new QSplitter(Qt::Horizontal, ui->centralwidget);
    auto *rootLayout = new QHBoxLayout(ui->centralwidget);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(splitter);

    m_mapWidget = new ExplorerMapWidget(splitter);
    m_mapWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->addWidget(m_mapWidget);

    auto *rightPanel = new QWidget(splitter);
    auto *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(12, 12, 12, 12);
    rightLayout->setSpacing(10);

    m_lblExploredProgress = new QLabel(QStringLiteral("已探索：0/12"), rightPanel);
    m_lblExploredProgress->setObjectName(QStringLiteral("lblExploredProgress"));
    rightLayout->addWidget(m_lblExploredProgress);

    auto *sep1 = new QFrame(rightPanel);
    sep1->setFrameShape(QFrame::HLine);
    sep1->setStyleSheet(QStringLiteral("color: #3a3a5a;"));
    rightLayout->addWidget(sep1);

    auto *logTitle = new QLabel(QStringLiteral("冒险日志"), rightPanel);
    logTitle->setObjectName(QStringLiteral("lblPanelTitle"));
    rightLayout->addWidget(logTitle);

    m_logList = new QListWidget(rightPanel);
    rightLayout->addWidget(m_logList, 1);

    auto *sep2 = new QFrame(rightPanel);
    sep2->setFrameShape(QFrame::HLine);
    sep2->setStyleSheet(QStringLiteral("color: #3a3a5a;"));
    rightLayout->addWidget(sep2);

    m_btnReset = new QPushButton(QStringLiteral("重置进度"), rightPanel);
    m_btnReset->setObjectName(QStringLiteral("btnReset"));
    m_btnReset->setMinimumSize(120, 36);
    rightLayout->addWidget(m_btnReset, 0, Qt::AlignHCenter);

    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    splitter->setSizes({840, 360});

    setupConnections();
    loadProgress();
    appendLog(QStringLiteral("探索开始。从咒术大楼选择你的第一条路线。"));
}

PKU_Explorer_Window::~PKU_Explorer_Window()
{
    saveProgress();
    delete ui;
}

void PKU_Explorer_Window::closeEvent(QCloseEvent *event)
{
    saveProgress();
    QMainWindow::closeEvent(event);
}

void PKU_Explorer_Window::setSiteAnswer(int siteId, const QString &answer)
{
    SiteAnswerBook::instance().setAnswer(siteId, answer);
}

void PKU_Explorer_Window::setSiteAnswers(const QMap<int, QString> &answers)
{
    SiteAnswerBook::instance().setAnswers(answers);
}

QString PKU_Explorer_Window::siteAnswer(int siteId) const
{
    return SiteAnswerBook::instance().answerFor(siteId);
}

void PKU_Explorer_Window::resetSiteAnswer(int siteId)
{
    SiteAnswerBook::instance().resetAnswer(siteId);
}

void PKU_Explorer_Window::resetAllSiteAnswers()
{
    SiteAnswerBook::instance().resetAllToDefaults();
}

void PKU_Explorer_Window::setInitialSiteStates()
{
    m_siteStates.fill(SiteState::Locked);
    m_siteStates[kInitialStartSiteId - 1] = SiteState::ToExplore; // 咒术大楼
}

void PKU_Explorer_Window::setupConnections()
{
    connect(m_mapWidget, &ExplorerMapWidget::siteClicked, this, &PKU_Explorer_Window::onLocationButtonClicked);
    connect(m_btnReset, &QPushButton::clicked, this, &PKU_Explorer_Window::onResetClicked);
}

void PKU_Explorer_Window::loadProgress()
{
    QSettings settings = makeGameSettings();
    setInitialSiteStates();

    for (int i = 0; i < m_siteStates.size(); ++i) {
        m_siteStates[i] = loadSiteState(settings, i + 1);
    }

    syncLuIslandUnlockState();
    refreshMap();
}

void PKU_Explorer_Window::saveProgress() const
{
    QSettings settings = makeGameSettings();
    for (int i = 0; i < m_siteStates.size(); ++i) {
        settings.setValue(siteStateKey(i + 1), static_cast<int>(m_siteStates[i]));
    }
    settings.sync();
}

void PKU_Explorer_Window::refreshMap()
{
    syncLuIslandUnlockState();
    m_mapWidget->setSiteStates(m_siteStates);
    updateExploredProgressDisplay();
}

int PKU_Explorer_Window::exploredCount() const
{
    int count = 0;
    for (SiteState state : m_siteStates) {
        if (state == SiteState::Explored) {
            ++count;
        }
    }
    return count;
}

void PKU_Explorer_Window::updateExploredProgressDisplay() const
{
    m_lblExploredProgress->setText(
        QStringLiteral("已探索：%1/%2").arg(exploredCount()).arg(kSiteCount));
}

void PKU_Explorer_Window::appendLog(const QString &line)
{
    if (!m_logList) {
        return;
    }

    m_logList->insertItem(0, line);
    while (m_logList->count() > 80) {
        delete m_logList->takeItem(m_logList->count() - 1);
    }
}

void PKU_Explorer_Window::checkAllExploredAndShowFinish()
{
    if (exploredCount() < kSiteCount || m_finishWindowShown) {
        return;
    }

    m_finishWindowShown = true;
    auto *finish = new Finish_Window(this);
    finish->setAttribute(Qt::WA_DeleteOnClose);
    connect(finish, &QObject::destroyed, this, [this]() {
        m_finishWindowShown = false;
    });
    finish->show();
}

void PKU_Explorer_Window::unlockNeighbors(int siteIndex)
{
    for (int neighborId : neighborsOf(siteIndex)) {
        if (isLuIslandSite(neighborId)) {
            continue;
        }
        const int neighborIndex = neighborId - 1;
        if (m_siteStates[neighborIndex] == SiteState::Locked) {
            m_siteStates[neighborIndex] = SiteState::ToExplore;
        }
    }
}

void PKU_Explorer_Window::syncLuIslandUnlockState()
{
    const int luIndex = kLuIslandSiteId - 1;
    if (m_siteStates[luIndex] == SiteState::Explored) {
        return;
    }

    if (isAnyLuIslandAdjacentExplored(m_siteStates)) {
        m_siteStates[luIndex] = SiteState::ToExplore;
    } else {
        m_siteStates[luIndex] = SiteState::Locked;
    }
}

void PKU_Explorer_Window::openInitialSiteIfAvailable(int siteId)
{
    if (siteId < 1 || siteId > kSiteCount) {
        return;
    }

    if (!isSiteClickable(m_siteStates.at(siteId - 1))) {
        return;
    }

    QTimer::singleShot(250, this, [this, siteId]() {
        onLocationButtonClicked(siteId);
    });
}

void PKU_Explorer_Window::onLocationButtonClicked(int index)
{
    if (index < 1 || index > kSiteCount) {
        return;
    }

    if (!isSiteClickable(m_siteStates[index - 1])) {
        return;
    }

    auto *site = new Site_Window(index, this);
    site->setAttribute(Qt::WA_DeleteOnClose);
    connect(site, &Site_Window::siteCompleted, this, &PKU_Explorer_Window::onSiteCompleted);
    connect(site, &Site_Window::dreamWakeEnding, this, &PKU_Explorer_Window::onDreamWakeEnding);
    connect(site, &Site_Window::luIslandReturnEnding, this, &PKU_Explorer_Window::onLuIslandReturnEnding);
    connect(site, &Site_Window::luIslandStayEnding, this, &PKU_Explorer_Window::onLuIslandStayEnding);
    if (isDialogueOnlySite(index)) {
        applyStoryDialogFrame(site, size());
    } else {
        applyExplorerWindowFrame(site, size());
    }
    site->show();
}

void PKU_Explorer_Window::onSiteCompleted(int siteIndex)
{
    if (siteIndex < 1 || siteIndex > kSiteCount) {
        return;
    }

    m_siteStates[siteIndex - 1] = SiteState::Explored;
    appendLog(QStringLiteral("完成探索：%1").arg(siteName(siteIndex)));
    if (!isLuIslandSite(siteIndex)) {
        unlockNeighbors(siteIndex);
    }
    syncLuIslandUnlockState();

    refreshMap();
    saveProgress();
    checkAllExploredAndShowFinish();
}

void PKU_Explorer_Window::onDreamWakeEnding()
{
    clearGameProgress();
    setInitialSiteStates();
    m_finishWindowShown = false;
    refreshMap();
    saveProgress();

    auto *ending = new Ending_Window(StoryEndingKind::Forget, this);
    ending->setAttribute(Qt::WA_DeleteOnClose);
    connect(ending, &Ending_Window::returnRequested, this, [this]() {
        close();
    });
    applyExplorerWindowFrame(ending, size());
    ending->show();
}

void PKU_Explorer_Window::completeLuIslandAndShowEnding(StoryEndingKind kind)
{
    m_siteStates[kLuIslandSiteId - 1] = SiteState::Explored;
    refreshMap();
    saveProgress();

    auto *ending = new Ending_Window(kind, this);
    ending->setAttribute(Qt::WA_DeleteOnClose);
    connect(ending, &Ending_Window::returnRequested, this, [this]() {
        close();
    });
    applyExplorerWindowFrame(ending, size());
    ending->show();
}

void PKU_Explorer_Window::onLuIslandReturnEnding()
{
    completeLuIslandAndShowEnding(StoryEndingKind::Return);
}

void PKU_Explorer_Window::onLuIslandStayEnding()
{
    completeLuIslandAndShowEnding(StoryEndingKind::Stay);
}

void PKU_Explorer_Window::onResetClicked()
{
    const auto reply = QMessageBox::question(
        this,
        QStringLiteral("重置进度"),
        QStringLiteral("确定要清空所有地点状态、恢复初始状态，并重新播放引导吗？"),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    setInitialSiteStates();
    m_finishWindowShown = false;
    refreshMap();

    clearGameProgress();
    setIntroCompleted(false);
}
