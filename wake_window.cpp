#include "wake_window.h"
#include "ui_wake_window.h"

#include "dialogue_text.h"
#include "explorer_window_layout.h"
#include "site_dialogues.h"

#include <QEvent>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

Wake_Window::Wake_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Wake_Window)
{
    ui->setupUi(this);

    setMenuBar(nullptr);
    setStatusBar(nullptr);
    applyWindowSize();
    applyStyles();

    ui->lblTitle->hide();
    ui->btnReturn->hide();

    m_beats = dreamWakeForgetEndingBeats();

    connect(ui->btnReturn, &QPushButton::clicked, this, &Wake_Window::onReturnClicked);

    ui->centralwidget->setCursor(Qt::PointingHandCursor);
    setCursor(Qt::PointingHandCursor);
    ui->centralwidget->installEventFilter(this);
    installEventFilter(this);

    startEndingSequence();
}

Wake_Window::~Wake_Window()
{
    delete ui;
}

void Wake_Window::applyWindowSize()
{
    applyExplorerWindowFrame(this, explorerWindowSize());
}

void Wake_Window::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(8, 8, 16));

    QLinearGradient top(0, 0, 0, 80);
    top.setColorAt(0, QColor(0, 0, 0, 120));
    top.setColorAt(1, QColor(0, 0, 0, 0));
    painter.fillRect(0, 0, width(), 80, top);

    QLinearGradient bottom(0, height() - 80, 0, height());
    bottom.setColorAt(0, QColor(0, 0, 0, 0));
    bottom.setColorAt(1, QColor(0, 0, 0, 140));
    painter.fillRect(0, height() - 80, width(), 80, bottom);

    QMainWindow::paintEvent(event);
}

void Wake_Window::applyStyles()
{
    setAttribute(Qt::WA_StyledBackground, false);
    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget#centralwidget { background: transparent; }"
        "QLabel#lblTitle {"
        "    color: rgb(144, 144, 144);"
        "    font-size: 20px;"
        "    font-weight: 600;"
        "    letter-spacing: 2px;"
        "}"
        "QLabel#lblDialogue {"
        "    color: rgb(208, 200, 192);"
        "    background: transparent;"
        "    padding: 0px;"
        "    font-size: 17px;"
        "    min-height: 120px;"
        "}"
        "QLabel#lblClickHint {"
        "    color: rgb(106, 100, 204);"
        "    font-size: 13px;"
        "}"
        "QPushButton#btnReturn {"
        "    background-color: rgb(28, 28, 56);"
        "    color: rgb(232, 213, 163);"
        "    border: 1px solid rgba(180,150,70,180);"
        "    border-radius: 4px;"
        "    font-size: 15px;"
        "    padding: 12px 32px;"
        "}"
        "QPushButton#btnReturn:hover {"
        "    background-color: rgb(42, 42, 80);"
        "    border-color: rgba(220,185,90,240);"
        "}"));

    ui->lblDialogue->setFixedWidth(620);
    ui->lblDialogue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
}

void Wake_Window::startEndingSequence()
{
    m_beatIndex = 0;
    m_endingComplete = false;
    showEndingBeat(m_beatIndex);
}

void Wake_Window::showEndingBeat(int index)
{
    if (index < 0 || index >= m_beats.size()) {
        showEndingComplete();
        return;
    }

    ui->lblClickHint->setText(QStringLiteral("▼  点击继续"));
    ui->lblClickHint->show();
    startTypewriter(m_beats.at(index));
}

void Wake_Window::showEndingComplete()
{
    m_endingComplete = true;
    finishTypewriter();

    ui->lblTitle->setText(QStringLiteral("梦醒·遗忘"));
    ui->lblTitle->show();

    ui->lblDialogue->setText(formatDialogueHtml(QStringLiteral(
        "生活继续。符文在投影上流动，和先前一模一样。\n"
        "偶尔路过园子的边，会觉得风在某处折返——\n"
        "但下一脚，仍只是平常的路。")));
    ui->lblDialogue->show();

    ui->lblClickHint->hide();
    ui->btnReturn->show();

    ui->centralwidget->setCursor(Qt::ArrowCursor);
    setCursor(Qt::ArrowCursor);
}

void Wake_Window::startTypewriter(const QString &plainText)
{
    m_typewriterPlainText = plainText;
    m_typewriterIndex = 0;
    m_typewriterActive = !plainText.isEmpty();

    if (!m_typewriterTimer) {
        m_typewriterTimer = new QTimer(this);
        m_typewriterTimer->setInterval(40);
        connect(m_typewriterTimer, &QTimer::timeout, this, &Wake_Window::onTypewriterTick);
    }

    if (!m_typewriterActive) {
        ui->lblDialogue->clear();
        return;
    }

    ui->lblDialogue->clear();
    m_typewriterTimer->start();
    onTypewriterTick();
}

void Wake_Window::finishTypewriter()
{
    if (m_typewriterTimer) {
        m_typewriterTimer->stop();
    }
    m_typewriterActive = false;
    m_typewriterIndex = m_typewriterPlainText.size();
    ui->lblDialogue->setText(formatDialogueHtml(m_typewriterPlainText));
}

void Wake_Window::skipTypewriter()
{
    if (!m_typewriterActive) {
        return;
    }
    finishTypewriter();
}

bool Wake_Window::isTypewriterActive() const
{
    return m_typewriterActive;
}

void Wake_Window::onTypewriterTick()
{
    if (!m_typewriterActive) {
        return;
    }

    if (m_typewriterIndex >= m_typewriterPlainText.size()) {
        finishTypewriter();
        return;
    }

    ++m_typewriterIndex;
    ui->lblDialogue->setText(
        formatDialogueHtml(m_typewriterPlainText.left(m_typewriterIndex)));
}

void Wake_Window::advanceEnding()
{
    if (m_endingComplete) {
        return;
    }

    if (isTypewriterActive()) {
        skipTypewriter();
        ui->lblClickHint->setText(QStringLiteral("▼  点击继续"));
        return;
    }

    ++m_beatIndex;
    if (m_beatIndex >= m_beats.size()) {
        showEndingComplete();
        return;
    }

    showEndingBeat(m_beatIndex);
}

bool Wake_Window::eventFilter(QObject *watched, QEvent *event)
{
    if (!m_endingComplete && event->type() == QEvent::MouseButtonPress) {
        auto *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            advanceEnding();
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void Wake_Window::onReturnClicked()
{
    emit returnRequested();
    close();
}
