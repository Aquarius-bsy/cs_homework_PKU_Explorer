#ifndef ENTRY_WINDOW_H
#define ENTRY_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Entry_Window;
}
QT_END_NAMESPACE

class Entry_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Entry_Window(QWidget *parent = nullptr);
    ~Entry_Window() override;

private slots:
    void onStartGameClicked();

private:
    void openExplorerWindow(bool autoOpenSpellHall = false);
    void paintEvent(QPaintEvent *event) override;

    Ui::Entry_Window *ui;
    QPixmap m_backgroundPixmap;
};
#endif // ENTRY_WINDOW_H
