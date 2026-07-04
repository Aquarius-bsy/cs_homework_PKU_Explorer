#ifndef INTRO_WINDOW_H
#define INTRO_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Intro_Window;
}
QT_END_NAMESPACE

class Intro_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Intro_Window(QWidget *parent = nullptr);
    ~Intro_Window() override;

signals:
    void introFinished();

private slots:
    void onContinueClicked();

private:
    void applyStyles();
    void showStep(int index);

    Ui::Intro_Window *ui;
    int m_stepIndex = 0;
};

#endif // INTRO_WINDOW_H
