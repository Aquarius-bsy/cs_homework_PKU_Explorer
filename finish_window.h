#ifndef FINISH_WINDOW_H
#define FINISH_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Finish_Window;
}
QT_END_NAMESPACE

class Finish_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Finish_Window(QWidget *parent = nullptr);
    ~Finish_Window() override;

private:
    Ui::Finish_Window *ui;
};

#endif // FINISH_WINDOW_H
