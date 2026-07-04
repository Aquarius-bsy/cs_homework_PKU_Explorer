#ifndef WAKE_WINDOW_H
#define WAKE_WINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui {
class Wake_Window;
}
QT_END_NAMESPACE

class Wake_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Wake_Window(QWidget *parent = nullptr);
    ~Wake_Window() override;

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

    Ui::Wake_Window *ui;
    QVector<QString> m_beats;
    int m_beatIndex = 0;
    bool m_endingComplete = false;
    bool m_typewriterActive = false;
    int m_typewriterIndex = 0;
    QString m_typewriterPlainText;
    QTimer *m_typewriterTimer = nullptr;
};

#endif // WAKE_WINDOW_H
