#include "finish_window.h"
#include "ui_finish_window.h"

#include "explorer_window_layout.h"

Finish_Window::Finish_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Finish_Window)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("探索完成"));
    applyExplorerWindowFrame(this, QSize(520, 220));
    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget#centralwidget { background: #16162a; color: #d0c8b8; }"
        "QLabel#lblMessage { color: #e8c87a; font-size: 18px; font-weight: 600; }"));
}

Finish_Window::~Finish_Window()
{
    delete ui;
}
