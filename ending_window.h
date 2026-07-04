#ifndef ENDING_WINDOW_H
#define ENDING_WINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

class QTimer;

enum class StoryEndingKind {
    Return,
    Stay,
    Forget,
};

QT_BEGIN_NAMESPACE
namespace Ui {
class Ending_Window;
}
QT_END_NAMESPACE

class Ending_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ending_Window(StoryEndingKind kind, QWidget *parent = nullptr);
    ~Ending_Window() override;

signals:
    void returnRequested();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onReturnClicked();
    void onTypewriterTick();

private:
    void applyStyles();
    void applyWindowSize();
    void startEndingSequence();
    void advanceEnding();
    void showEndingBeat(int index);
    void showEndingComplete();
    void startTypewriter(const QString &plainText);
    void finishTypewriter();
    void skipTypewriter();
    bool isTypewriterActive() const;

    StoryEndingKind m_kind = StoryEndingKind::Return;
    Ui::Ending_Window *ui;
    QVector<QString> m_beats;
    int m_beatIndex = 0;
    bool m_endingComplete = false;
    bool m_typewriterActive = false;
    int m_typewriterIndex = 0;
    QString m_typewriterPlainText;
    QTimer *m_typewriterTimer = nullptr;
};

#endif // ENDING_WINDOW_H
