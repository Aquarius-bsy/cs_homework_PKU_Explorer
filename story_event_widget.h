#ifndef STORY_EVENT_WIDGET_H
#define STORY_EVENT_WIDGET_H

#include <QList>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>

class QLabel;
class QLineEdit;
class QTimer;
class QVBoxLayout;

class StoryEventWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StoryEventWidget(QWidget *parent = nullptr);

    void setEventTitle(const QString &title);
    void setBackgroundPixmap(const QPixmap &pixmap);
    void clearBackground();

    void setLeftPortrait(const QPixmap &pixmap,
                         bool upperBodyCrop = false,
                         bool fullBody = false,
                         bool compactFullBody = false);
    void setRightPortrait(const QPixmap &pixmap, bool fullBody = false);
    void clearPortraits();

    void setNarrativeText(const QString &text, bool typewriter = true);
    void setDialogueSiteId(int siteId);
    void skipTypewriter();
    bool isTypewriterActive() const;

    void setAdvanceHintVisible(bool visible);
    void showChoiceButtons(const QString &choiceA, const QString &choiceB);
    void showChoiceButtons(const QString &choiceA,
                           const QString &choiceB,
                           const QString &choiceC);
    void showMonumentInput(const QString &deferText,
                             const QString &promptText,
                             const QString &placeholder);
    void hideInteractions();

    QString monumentAnswer() const;
    void clearMonumentAnswer();

    bool canAdvanceNarration() const;

signals:
    void advanceRequested();
    void closeRequested();
    void choiceARequested();
    void choiceBRequested();
    void choiceCRequested();
    void monumentDeferRequested();
    void monumentSubmitRequested();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onTypewriterTick();
    void onAdvanceClicked();

private:
    void buildLayout();
    void positionPortrait();
    void positionChoiceOverlay();
    void positionInputOverlay();
    void positionCloseButton();
    void clearChoiceButtons();
    void finishTypewriter();

    QPixmap m_bgPixmap;
    QPixmap m_leftPortraitSource;
    QPixmap m_rightPortraitSource;
    bool m_leftUpperBodyCrop = false;
    bool m_leftPortraitFullBody = false;
    bool m_leftPortraitCompactFullBody = false;
    bool m_rightPortraitFullBody = false;

    QWidget *m_imageAreaWidget = nullptr;
    QWidget *m_choiceOverlay = nullptr;
    QVBoxLayout *m_choiceLayout = nullptr;
    QList<QPushButton *> m_choiceButtons;

    QWidget *m_inputOverlay = nullptr;
    QLabel *m_inputPrompt = nullptr;
    QLineEdit *m_inputEdit = nullptr;
    QPushButton *m_inputDeferBtn = nullptr;
    QPushButton *m_inputSubmitBtn = nullptr;

    QLabel *m_titleLabel = nullptr;
    QLabel *m_narrativeLabel = nullptr;
    QPushButton *m_pageBtn = nullptr;
    QPushButton *m_closeBtn = nullptr;

    QLabel *m_portraitLeft = nullptr;
    QLabel *m_portraitRight = nullptr;

    QTimer *m_typeTimer = nullptr;
    QString m_pendingText;
    int m_typeIndex = 0;
    bool m_typewriterActive = false;
    int m_dialogueSiteId = 0;

    static constexpr int kTextPanelH = 175;
    static constexpr int kImageMinH = 380;
    static constexpr int kPortX = 12;
    static constexpr int kLeftPortraitLiftY = 48;
    static constexpr int kLeftPortraitDropY = 20;
    static constexpr int kRightPortraitDropY = 20;
    static constexpr int kPanelAlpha = 230;
};

#endif // STORY_EVENT_WIDGET_H
