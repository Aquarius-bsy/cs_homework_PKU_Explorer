#ifndef SITE_WINDOW_H
#define SITE_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QVector>

class QCloseEvent;

#include "site_dialogues.h"

class QTimer;
class StoryEventWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class Site_Window;
}
QT_END_NAMESPACE

class Site_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Site_Window(int siteIndex, QWidget *parent = nullptr);
    ~Site_Window() override;

signals:
    void siteCompleted(int siteIndex);
    void dreamWakeEnding();
    void luIslandReturnEnding();
    void luIslandStayEnding();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNextClicked();
    void onSubmitAnswer();
    void onDialogueChoiceA();
    void onDialogueChoiceB();
    void onDialogueChoiceC();
    void onMonumentDefer();
    void onMonumentSubmit();

private:
    void applyMapLikeWindowSize();
    void setupDialogueMode();
    void advanceDialogue();
    void updateDialogueDisplay();
    void applyStoryPortraits(const DialogueBeat &beat);
    void applyStoryBackground(const QString &sceneImageFile);
    void hideDialogueInteractions();
    void showBinaryChoice(const DialogueBeat &beat);
    void showMultiChoice(const DialogueBeat &beat);
    void showMonumentDecision();
    void showMirrorLakeTowerDecision();
    void showTheaterMuralDecision();
    void showOldRealmShopNameDecision(const QString &sceneImageFile);
    void showForbiddenArchiveCatalogDecision(const QString &sceneImageFile);
    void insertPlayerAndNpcLines(const QString &playerText,
                                 const QString &npcLine,
                                 const QString &sceneImageFile,
                                 const QString &npcPortraitFile);
    void switchDialogueSequence(const QVector<DialogueBeat> &beats);
    void appendDialogueAfterChoice(const QVector<DialogueBeat> &followUp);
    void handleTavernFirstChoice(const QString &playerText, const QString &bossReply);
    void handleTheaterViewChoice(bool viewGlassMural);
    void handleArenaJoinChoice(bool joinBattle);
    void handleArenaExerciseChoice(bool exercisedToday);
    void handleArcaneTowerChoice(bool enterTower);
    void handleTianmenChoice(bool leaveMagicWorld);
    void handleTianmenConfirmLeave(bool confirmLeave);
    void handleLuIslandChoice(bool returnToRealWorld);
    void handleSpellHallChoice(int choiceIndex);
    void handleOldRealmEnterChoice(bool enterShop);
    void handleRuinGardenPathChoice(bool takeLightPath);
    void handleRuinGardenHeartChoice(bool stayLonger);
    void handleForbiddenArchiveVisitChoice(bool casualBrowse);
    void handleForbiddenArchiveBookFamiliarityChoice(bool heardBefore);
    void startTavernEnding(bool befriendedTraveler, const QString &playerLine);
    void startTheaterEnding(bool muralsAligned, const QString &playerLine, bool wrongGuess = false);
    void startDialogueTypewriter(const QString &plainText);
    void finishDialogueTypewriter();
    void skipDialogueTypewriter();
    void setDialoguePlainText(const QString &plainText, bool typewriter);
    void finishDialogue();
    void setupChallengeModeStyles();
    void showVerdict(const QString &text, const QString &color);
    void updateProgressDisplay() const;
    void enterChallengePhase();
    bool isWaitingForInput() const;
    bool isTypewriterActive() const;

    StoryEventWidget *m_storyWidget = nullptr;
    int m_siteIndex = 0;
    int m_sessionClickCount = 0;
    bool m_challengeActive = false;
    bool m_dialogueMode = false;
    bool m_waitingForInput = false;
    bool m_endWithDreamWake = false;
    bool m_endWithLuIslandReturn = false;
    bool m_endWithLuIslandStay = false;
    bool m_skipSiteCompletion = false;
    int m_tianmenFirstChoiceStep = -1;
    bool m_typewriterActive = false;
    int m_typewriterIndex = 0;
    QString m_typewriterPlainText;
    QVector<DialogueBeat> m_dialogueBeats;
    int m_dialogueStep = 0;
    QString m_currentSceneImageFile;
    QString m_currentLeftPortraitFile;
    QString m_currentRightPortraitFile;
    QTimer *m_typewriterTimer = nullptr;
    Ui::Site_Window *ui;
};

#endif // SITE_WINDOW_H
