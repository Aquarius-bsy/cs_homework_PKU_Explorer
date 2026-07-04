#include "intro_window.h"
#include "ui_intro_window.h"

#include <QFont>
#include <QGuiApplication>
#include <QScreen>
#include <QVector>

namespace {

struct IntroStep {
    QString title;
    QString body;
};

QVector<IntroStep> introSteps()
{
    return {
        {QStringLiteral("欢迎来到魔幻校园"),
         QStringLiteral(
             "你即将踏上 PKU-Explorer 的旅程：在魔幻风格的北大地图上，从咒术大楼出发，"
             "逐步探索十二处神秘地标。禁书馆、镜湖与奥术尖塔中，都藏着等待你解锁的故事。")},
        {QStringLiteral("地图与地点"),
         QStringLiteral(
             "主界面中央是校园地图。圆点旁的小标签会显示「未解锁」「待探索」或「已探索」。\n"
             "开局时，咒术大楼为待探索状态，其余地点尚未解锁。点击地图地名旁的圆点即可进入该地点。")},
        {QStringLiteral("圆点颜色"),
         QStringLiteral(
             "灰色：未解锁，无法进入。\n"
             "黄色：待探索，可以点击进入。\n"
             "绿色：已探索，可随时回顾。\n"
             "地点之间的连线也会随探索进度变色：两端均未探索为灰，仅一端已探索为黄，两端均已探索为绿。")},
        {QStringLiteral("地点窗口：Next 挑战"),
         QStringLiteral(
             "进入地点后，需先点击「Next」按钮。第 N 号地点需要连续点击 N 次 Next，"
             "完成后才会进入答题环节。请耐心完成每一次点击。")},
        {QStringLiteral("地点窗口：答题判定"),
         QStringLiteral(
             "Next 次数达标后，在输入框中填写答案并提交。\n"
             "答案正确显示 AC，该地点标记为已探索；答案错误显示 WA，可修改后再次提交。")},
        {QStringLiteral("解锁相邻地点"),
         QStringLiteral(
             "完成一处地点后，与其相连的邻接地点会从「未解锁」变为「待探索」。"
             "合理规划路线，从咒术大楼向地图深处推进，逐步揭开整张地图。")},
        {QStringLiteral("湖心岛：最终奖励"),
         QStringLiteral(
             "湖心岛是特殊地点：需先探索完其余 11 处，圆点才会逐渐填满黄色并解锁。"
             "每完成一处，湖心岛圆点会增加一分黄色填充；全部完成后方可进入。"
             "探索湖心岛成功后，圆点将变为彩色，地图上的湖心岛区域也会焕发光彩。")},
        {QStringLiteral("进度与通关"),
         QStringLiteral(
             "左上角显示「已探索：x/12」。全部十二处探索完成后，将弹出通关祝贺窗口。"
             "若需重新开始，可使用「重置进度」——会清空所有地点状态，并再次播放本引导。")},
        {QStringLiteral("准备出发"),
         QStringLiteral(
             "引导到此结束。点击「开始探索」后，将自动进入咒术大楼序章；"
             "完成序章后再在地图上选择后续路线。祝你在北大校园的探险顺利！")},
    };
}

} // namespace

Intro_Window::Intro_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Intro_Window)
{
    ui->setupUi(this);
    setFixedSize(size());

    if (const QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect area = screen->availableGeometry();
        move(area.center().x() - width() / 2, area.center().y() - height() / 2);
    }

    setMenuBar(nullptr);
    setStatusBar(nullptr);
    applyStyles();
    showStep(0);

    connect(ui->btnContinue, &QPushButton::clicked, this, &Intro_Window::onContinueClicked);
}

Intro_Window::~Intro_Window()
{
    delete ui;
}

void Intro_Window::applyStyles()
{
    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget#centralwidget {"
        "    background-color: rgb(34, 28, 46);"
        "}"
        "QLabel#lblStep {"
        "    color: rgb(196, 168, 255);"
        "    font-size: 12px;"
        "}"
        "QLabel#lblTitle {"
        "    color: rgb(255, 220, 140);"
        "    font-size: 22px;"
        "    font-weight: bold;"
        "}"
        "QLabel#lblBody {"
        "    color: rgb(228, 220, 245);"
        "    font-size: 15px;"
        "    line-height: 1.45;"
        "}"
        "QPushButton#btnContinue {"
        "    background-color: rgb(72, 56, 98);"
        "    color: rgb(255, 236, 190);"
        "    border: 1px solid rgb(196, 158, 78);"
        "    border-radius: 10px;"
        "    font-size: 15px;"
        "    font-weight: bold;"
        "    padding: 8px 32px;"
        "}"
        "QPushButton#btnContinue:hover {"
        "    background-color: rgb(92, 72, 124);"
        "    border: 1px solid rgb(255, 210, 110);"
        "}"
        "QPushButton#btnContinue:pressed {"
        "    background-color: rgb(58, 46, 82);"
        "}"));

    QFont bodyFont = ui->lblBody->font();
    bodyFont.setPointSize(11);
    ui->lblBody->setFont(bodyFont);
}

void Intro_Window::showStep(int index)
{
    const QVector<IntroStep> steps = introSteps();
    const IntroStep &step = steps.at(index);

    ui->lblStep->setText(QStringLiteral("引导 %1 / %2").arg(index + 1).arg(steps.size()));
    ui->lblTitle->setText(step.title);
    ui->lblBody->setText(step.body);
    ui->btnContinue->setText(index + 1 == steps.size() ? QStringLiteral("开始探索")
                                                       : QStringLiteral("继续"));
}

void Intro_Window::onContinueClicked()
{
    const int lastIndex = introSteps().size() - 1;
    if (m_stepIndex < lastIndex) {
        ++m_stepIndex;
        showStep(m_stepIndex);
        return;
    }

    emit introFinished();
    close();
}
