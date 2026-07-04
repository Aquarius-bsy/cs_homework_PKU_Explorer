#include "ending_window.h"
#include "ui_ending_window.h"

#include "dialogue_text.h"
#include "explorer_window_layout.h"
#include "site_dialogues.h"

#include <QEvent>
#include <QKeyEvent>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

namespace {

QString endingTitle(StoryEndingKind kind)
{
    switch (kind) {
    case StoryEndingKind::Return:
        return QStringLiteral("结局A · 归返");
    case StoryEndingKind::Stay:
        return QStringLiteral("结局B · 留守");
    case StoryEndingKind::Forget:
        return QStringLiteral("结局C · 遗忘");
    }
    return QStringLiteral("结局");
}

QString endingTitleColor(StoryEndingKind kind)
{
    switch (kind) {
    case StoryEndingKind::Return:
        return QStringLiteral("rgb(200, 176, 96)");
    case StoryEndingKind::Stay:
        return QStringLiteral("rgb(112, 144, 200)");
    case StoryEndingKind::Forget:
        return QStringLiteral("rgb(160, 160, 176)");
    }
    return QStringLiteral("rgb(196, 168, 255)");
}

QString endingSummary(StoryEndingKind kind)
{
    switch (kind) {
    case StoryEndingKind::Return:
        return QStringLiteral(
            "你推开门，回到了熟悉的走廊与下午。\n"
            "符文在投影上流动，和先前一模一样——\n"
            "只是偶尔，你会想起一条细细的金线。");
    case StoryEndingKind::Stay:
        return QStringLiteral(
            "你没有走进那扇门。\n"
            "你留在了湖心岛；对岸的灯火仍亮着，颜色却渐渐模糊。\n"
            "园子里的路，从此只向深处延伸。");
    case StoryEndingKind::Forget:
        return QStringLiteral(
            "生活继续。符文在投影上流动，和先前一模一样。\n"
            "偶尔路过园子的边，会觉得风在某处折返——\n"
            "但下一脚，仍只是平常的路。");
    }
    return {};
}

QVector<QString> endingBeatsForKind(StoryEndingKind kind)
{
    switch (kind) {
    case StoryEndingKind::Return:
        return luIslandReturnEndingBeats();
    case StoryEndingKind::Stay:
        return luIslandStayEndingBeats();
    case StoryEndingKind::Forget:
        return dreamWakeForgetEndingBeats();
    }
    return {};
}

} // namespace

Ending_Window::Ending_Window(StoryEndingKind kind, QWidget *parent)
    : QMainWindow(parent)
    , m_kind(kind)
    , ui(new Ui::Ending_Window)
{
    ui->setupUi(this);

    setMenuBar(nullptr);
    setStatusBar(nullptr);

    const QString title = endingTitle(m_kind);
    setWindowTitle(title);
    ui->lblTitle->setText(title);
    ui->lblTitle->show();

    applyWindowSize();
    applyStyles();

    ui->btnReturn->hide();

    m_beats = endingBeatsForKind(m_kind);

    connect(ui->btnReturn, &QPushButton::clicked, this, &Ending_Window::onReturnClicked);

    ui->centralwidget->setCursor(Qt::PointingHandCursor);
    setCursor(Qt::PointingHandCursor);
    ui->centralwidget->installEventFilter(this);
    installEventFilter(this);

    startEndingSequence();
}

Ending_Window::~Ending_Window()
{
    delete ui;
}

void Ending_Window::applyWindowSize()
{
    applyExplorerWindowFrame(this, explorerWindowSize());
}

void Ending_Window::paintEvent(QPaintEvent *event)
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

void Ending_Window::applyStyles()
{
    setAttribute(Qt::WA_StyledBackground, false);
    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget#centralwidget { background: transparent; }"
        "QLabel#lblTitle {"
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

    ui->lblTitle->setStyleSheet(
        QStringLiteral("color: %1;").arg(endingTitleColor(m_kind)));
    ui->lblDialogue->setFixedWidth(620);
    ui->lblDialogue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
}

void Ending_Window::startEndingSequence()
{
    m_beatIndex = 0;
    m_endingComplete = false;
    showEndingBeat(m_beatIndex);
}

void Ending_Window::showEndingBeat(int index)
{
    if (index < 0 || index >= m_beats.size()) {
        showEndingComplete();
        return;
    }

    ui->lblClickHint->setText(QStringLiteral("▼  点击屏幕或按任意键继续"));
    ui->lblClickHint->show();
    startTypewriter(m_beats.at(index));
}

void Ending_Window::showEndingComplete()
{
    m_endingComplete = true;
    finishTypewriter();

    ui->lblTitle->setText(endingTitle(m_kind));
    ui->lblTitle->show();

    ui->lblDialogue->setText(formatDialogueHtml(endingSummary(m_kind)));
    ui->lblDialogue->show();

    ui->lblClickHint->hide();
    ui->btnReturn->show();

    ui->centralwidget->setCursor(Qt::ArrowCursor);
    setCursor(Qt::ArrowCursor);
}

void Ending_Window::startTypewriter(const QString &plainText)
{
    m_typewriterPlainText = plainText;
    m_typewriterIndex = 0;
    m_typewriterActive = !plainText.isEmpty();

    if (!m_typewriterTimer) {
        m_typewriterTimer = new QTimer(this);
        m_typewriterTimer->setInterval(40);
        connect(m_typewriterTimer, &QTimer::timeout, this, &Ending_Window::onTypewriterTick);
    }

    if (!m_typewriterActive) {
        ui->lblDialogue->clear();
        return;
    }

    ui->lblDialogue->clear();
    m_typewriterTimer->start();
    onTypewriterTick();
}

void Ending_Window::finishTypewriter()
{
    if (m_typewriterTimer) {
        m_typewriterTimer->stop();
    }
    m_typewriterActive = false;
    m_typewriterIndex = m_typewriterPlainText.size();
    ui->lblDialogue->setText(formatDialogueHtml(m_typewriterPlainText));
}

void Ending_Window::skipTypewriter()
{
    if (!m_typewriterActive) {
        return;
    }
    finishTypewriter();
}

bool Ending_Window::isTypewriterActive() const
{
    return m_typewriterActive;
}

void Ending_Window::onTypewriterTick()
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

void Ending_Window::advanceEnding()
{
    if (m_endingComplete) {
        return;
    }

    if (isTypewriterActive()) {
        skipTypewriter();
        ui->lblClickHint->setText(QStringLiteral("▼  点击屏幕或按任意键继续"));
        return;
    }

    ++m_beatIndex;
    if (m_beatIndex >= m_beats.size()) {
        showEndingComplete();
        return;
    }

    showEndingBeat(m_beatIndex);
}

bool Ending_Window::eventFilter(QObject *watched, QEvent *event)
{
    if (!m_endingComplete) {
        if (event->type() == QEvent::MouseButtonPress) {
            auto *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                advanceEnding();
                return true;
            }
        }
        if (event->type() == QEvent::KeyPress) {
            advanceEnding();
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void Ending_Window::onReturnClicked()
{
    emit returnRequested();
    close();
}
