#include "entry_window.h"
#include "ui_entry_window.h"

#include "game_progress.h"
#include "intro_window.h"
#include "pku_explorer_window.h"
#include "site_graph.h"

#include <QFont>
#include <QFontMetrics>
#include <QLabel>
#include <QLinearGradient>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>

namespace {

constexpr int kEntryWindowWidth = 800;
constexpr int kEntryWindowHeight = 600;

const char *kStartButtonStyle = R"(
QPushButton#btnStartGame {
    background: qlineargradient(x1:0,y1:0,x2:0,y2:1, stop:0 #5a52bb, stop:1 #3d3788);
    color: #f0e8d0;
    border: 1px solid #7f77dd;
    border-radius: 8px;
    font-size: 18px;
    font-weight: bold;
    letter-spacing: 4px;
    padding: 12px 48px;
}
QPushButton#btnStartGame:hover {
    background: qlineargradient(x1:0,y1:0,x2:0,y2:1, stop:0 #7a72db, stop:1 #5d57a8);
    border-color: #a09aee;
}
QPushButton#btnStartGame:pressed {
    background: #2d2a6a;
}
)";

const char *kCreatorLabelStyle = R"(
QLabel#lblCreator {
    color: rgb(200, 196, 220);
    background-color: rgba(0, 0, 0, 120);
    padding: 4px 10px;
    border-radius: 4px;
    font-size: 12px;
}
)";

class EntryTitleLabel : public QLabel
{
public:
    explicit EntryTitleLabel(QWidget *parent = nullptr)
        : QLabel(parent)
    {
        setText(QStringLiteral("PKU-Explorer"));
        setAttribute(Qt::WA_TranslucentBackground, true);
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    }

    QSize sizeHint() const override
    {
        QFont font = titleFont();
        const QFontMetrics metrics(font);
        return {metrics.horizontalAdvance(text()) + 12, metrics.height() + 10};
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);

        const QFont font = titleFont();
        painter.setFont(font);

        QPainterPath path;
        path.addText(2, height() - 8, font, text());

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(20, 14, 36, 90));
        painter.drawPath(path.translated(2, 2));

        QLinearGradient fill(0, 0, width(), height());
        fill.setColorAt(0.0, QColor(232, 213, 163));
        fill.setColorAt(0.45, QColor(248, 228, 170));
        fill.setColorAt(1.0, QColor(196, 158, 78));

        painter.setBrush(fill);
        painter.setPen(QPen(QColor(62, 38, 12), 1.0));
        painter.drawPath(path);
    }

private:
    QFont titleFont() const
    {
        QFont font(QStringLiteral("Times New Roman"));
        font.setPointSize(28);
        font.setBold(true);
        font.setLetterSpacing(QFont::AbsoluteSpacing, 2.0);
        return font;
    }
};

QPixmap loadEntryBackground()
{
    const QPixmap fromResource(QStringLiteral(":/images/entry_bg.png"));
    if (!fromResource.isNull()) {
        return fromResource;
    }

    return QPixmap(QStringLiteral(":/images/entry.png"));
}

} // namespace

Entry_Window::Entry_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Entry_Window)
{
    ui->setupUi(this);

    m_backgroundPixmap = loadEntryBackground();

    setFixedSize(kEntryWindowWidth, kEntryWindowHeight);
    setWindowTitle(QStringLiteral("PKU-Explorer"));

    ui->centralwidget->setObjectName(QStringLiteral("central"));
    ui->centralwidget->setAttribute(Qt::WA_StyledBackground, true);
    ui->centralwidget->setStyleSheet(QStringLiteral("QWidget#central { background: transparent; }"));

    ui->btnStartGame->setObjectName(QStringLiteral("btnStartGame"));
    ui->btnStartGame->setText(QStringLiteral("开 始 冒 险"));
    ui->btnStartGame->setMinimumSize(200, 54);
    ui->btnStartGame->setCursor(Qt::PointingHandCursor);
    ui->btnStartGame->setStyleSheet(QString::fromUtf8(kStartButtonStyle));
    ui->btnStartGame->setAutoFillBackground(true);

    ui->lblCreator->setObjectName(QStringLiteral("lblCreator"));
    ui->lblCreator->setStyleSheet(QString::fromUtf8(kCreatorLabelStyle));

    delete ui->lblGameTitle;
    ui->lblGameTitle = new EntryTitleLabel(ui->centralwidget);

    auto *subtitle = new QLabel(QStringLiteral("探索被魔法改变的校园世界"), ui->centralwidget);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet(
        QStringLiteral("color: #a098c8; font-size: 16px; letter-spacing: 2px; background: transparent;"));

    auto *hint = new QLabel(QStringLiteral("点击各地点标记开始探索  ·  完成剧情解锁整张地图"),
                            ui->centralwidget);
    hint->setAlignment(Qt::AlignCenter);
    hint->setStyleSheet(
        QStringLiteral("color: #5a5870; font-size: 12px; background: transparent;"));

    auto *layout = ui->verticalLayout;
    while (layout->count() > 0) {
        layout->takeAt(0);
    }

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addStretch(3);
    layout->addWidget(ui->lblGameTitle, 0, Qt::AlignHCenter);
    layout->addSpacing(12);
    layout->addWidget(subtitle, 0, Qt::AlignHCenter);
    layout->addStretch(2);

    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(ui->btnStartGame);
    btnRow->addStretch();
    layout->addLayout(btnRow);

    layout->addStretch(2);
    layout->addWidget(hint, 0, Qt::AlignHCenter);

    auto *bottomRow = new QHBoxLayout();
    bottomRow->setContentsMargins(16, 0, 16, 14);
    bottomRow->addStretch();
    bottomRow->addWidget(ui->lblCreator);
    layout->addLayout(bottomRow);
    layout->addStretch(1);

    setMenuBar(nullptr);
    setStatusBar(nullptr);

    connect(ui->btnStartGame, &QPushButton::clicked, this, &Entry_Window::onStartGameClicked);
}

Entry_Window::~Entry_Window()
{
    delete ui;
}

void Entry_Window::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (!m_backgroundPixmap.isNull()) {
        painter.drawPixmap(rect(), m_backgroundPixmap);
        painter.fillRect(rect(), QColor(10, 10, 26, 160));
    } else {
        QLinearGradient grad(0, 0, 0, height());
        grad.setColorAt(0.0, QColor(13, 13, 26));
        grad.setColorAt(0.5, QColor(20, 18, 42));
        grad.setColorAt(1.0, QColor(10, 10, 20));
        painter.fillRect(rect(), grad);
    }

    QMainWindow::paintEvent(event);
}

void Entry_Window::openExplorerWindow(bool autoOpenSpellHall)
{
    auto *explorer = new PKU_Explorer_Window();
    explorer->setAttribute(Qt::WA_DeleteOnClose);
    explorer->show();

    if (autoOpenSpellHall) {
        explorer->openInitialSiteIfAvailable(kInitialStartSiteId);
    }
}

void Entry_Window::onStartGameClicked()
{
    migrateIntroForLegacySave();

    if (shouldShowIntroOnStart()) {
        auto *intro = new Intro_Window(this);
        intro->setAttribute(Qt::WA_DeleteOnClose);
        connect(intro, &Intro_Window::introFinished, this, [this]() {
            setIntroCompleted(true);
            openExplorerWindow(true);
        });
        intro->show();
        return;
    }

    openExplorerWindow(false);
}
