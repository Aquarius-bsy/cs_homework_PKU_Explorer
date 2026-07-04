#include "story_event_widget.h"

#include "dialogue_text.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QVBoxLayout>

namespace {

constexpr qreal kStaffPortraitUpperBodyRatio = 0.60;

QPixmap upperBodyPortrait(const QPixmap &source, int targetHeight, int maxWidth)
{
    if (source.isNull() || targetHeight < 1) {
        return {};
    }

    const int cropHeight =
        qMax(1, static_cast<int>(source.height() * kStaffPortraitUpperBodyRatio));
    const QPixmap upperBody = source.copy(0, 0, source.width(), cropHeight);
    QPixmap scaled = upperBody.scaledToHeight(targetHeight, Qt::SmoothTransformation);
    if (maxWidth > 0 && scaled.width() > maxWidth) {
        scaled = upperBody.scaled(maxWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    return scaled;
}

QPixmap halfBodyPortrait(const QPixmap &source, int targetHeight, int maxWidth)
{
    if (source.isNull() || targetHeight < 1) {
        return {};
    }

    QPixmap scaled = source.scaledToHeight(targetHeight, Qt::SmoothTransformation);
    if (maxWidth > 0 && scaled.width() > maxWidth) {
        scaled = source.scaled(maxWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    return scaled;
}

} // namespace

StoryEventWidget::StoryEventWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setFocusPolicy(Qt::StrongFocus);
    buildLayout();

    m_typeTimer = new QTimer(this);
    m_typeTimer->setInterval(18);
    connect(m_typeTimer, &QTimer::timeout, this, &StoryEventWidget::onTypewriterTick);
}

void StoryEventWidget::buildLayout()
{
    auto *root = new QVBoxLayout(this);
    root->setSpacing(0);
    root->setContentsMargins(0, 0, 0, 0);

    m_imageAreaWidget = new QWidget(this);
    m_imageAreaWidget->setMinimumHeight(kImageMinH);
    m_imageAreaWidget->setStyleSheet(QStringLiteral("background: transparent;"));
    root->addWidget(m_imageAreaWidget, 1);

    auto *sep = new QWidget(this);
    sep->setFixedHeight(1);
    sep->setStyleSheet(QStringLiteral("background: rgba(80, 80, 140, 120);"));
    root->addWidget(sep, 0);

    auto *textPanel = new QWidget(this);
    textPanel->setFixedHeight(kTextPanelH);
    textPanel->setStyleSheet(
        QStringLiteral("QWidget { background: rgba(10, 10, 22, %1); }").arg(kPanelAlpha));
    auto *textRow = new QHBoxLayout(textPanel);
    textRow->setContentsMargins(24, 14, 24, 14);
    textRow->setSpacing(20);

    m_titleLabel = new QLabel(textPanel);
    m_titleLabel->setStyleSheet(
        QStringLiteral("font-size: 15px; font-weight: 600; color: #e8c87a; background: transparent;"));
    m_titleLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_titleLabel->setFixedWidth(130);
    m_titleLabel->setWordWrap(true);
    textRow->addWidget(m_titleLabel, 0, Qt::AlignTop);

    auto *vline = new QWidget(textPanel);
    vline->setFixedSize(1, kTextPanelH - 28);
    vline->setStyleSheet(QStringLiteral("background: rgba(120, 100, 60, 80);"));
    textRow->addWidget(vline, 0, Qt::AlignVCenter);

    auto *textCol = new QVBoxLayout();
    textCol->setSpacing(4);
    textCol->setContentsMargins(0, 0, 0, 0);

    m_narrativeLabel = new QLabel(textPanel);
    m_narrativeLabel->setWordWrap(true);
    m_narrativeLabel->setTextFormat(Qt::RichText);
    m_narrativeLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_narrativeLabel->setStyleSheet(
        QStringLiteral("font-size: 16px; line-height: 1.7; color: #d8d0c4; background: transparent;"));
    textCol->addWidget(m_narrativeLabel, 1);

    m_pageBtn = new QPushButton(QStringLiteral("▼  点击屏幕或按任意键继续 · Esc 关闭"), textPanel);
    m_pageBtn->setStyleSheet(
        QStringLiteral("QPushButton { background: transparent; color: #6a64cc; "
                       "border: none; font-size: 12px; padding: 2px 4px; }"
                       "QPushButton:hover { color: #9490e0; }"));
    m_pageBtn->setCursor(Qt::PointingHandCursor);
    m_pageBtn->hide();
    textCol->addWidget(m_pageBtn, 0, Qt::AlignRight | Qt::AlignBottom);
    textRow->addLayout(textCol, 1);
    root->addWidget(textPanel, 0);

    m_choiceOverlay = new QWidget(this);
    m_choiceOverlay->setObjectName(QStringLiteral("choiceOverlay"));
    m_choiceOverlay->setAttribute(Qt::WA_StyledBackground, true);
    m_choiceOverlay->setStyleSheet(
        QStringLiteral("QWidget#choiceOverlay { background: transparent; }"));
    m_choiceLayout = new QVBoxLayout(m_choiceOverlay);
    m_choiceLayout->setSpacing(10);
    m_choiceLayout->setContentsMargins(0, 0, 0, 0);
    m_choiceOverlay->hide();

    m_inputOverlay = new QWidget(this);
    m_inputOverlay->setAttribute(Qt::WA_StyledBackground, true);
    m_inputOverlay->setStyleSheet(
        QStringLiteral("QWidget { background: #13132a; border: 1px solid rgba(160, 130, 60, 180); "
                       "border-radius: 6px; }"));
    auto *inputVbox = new QVBoxLayout(m_inputOverlay);
    inputVbox->setSpacing(10);
    inputVbox->setContentsMargins(20, 16, 20, 16);

    m_inputPrompt = new QLabel(m_inputOverlay);
    m_inputPrompt->setWordWrap(true);
    m_inputPrompt->setStyleSheet(
        QStringLiteral("QLabel { font-size: 15px; color: #d8d0c4; background: transparent; border: none; }"));
    inputVbox->addWidget(m_inputPrompt);

    m_inputEdit = new QLineEdit(m_inputOverlay);
    m_inputEdit->setPlaceholderText(QStringLiteral("在此输入……"));
    m_inputEdit->setStyleSheet(
        QStringLiteral("QLineEdit { background: #1e1e38; color: #e8e0d0; font-size: 15px; "
                       "border: 1px solid rgba(140, 120, 60, 160); border-radius: 4px; "
                       "padding: 8px 12px; selection-background-color: #4a4a8a; }"));
    inputVbox->addWidget(m_inputEdit);

    auto *btnRow = new QHBoxLayout();
    btnRow->setSpacing(10);

    m_inputDeferBtn = new QPushButton(m_inputOverlay);
    m_inputDeferBtn->setStyleSheet(
        QStringLiteral("QPushButton { background: #1a1a30; color: #8888aa; font-size: 13px; "
                       "border: 1px solid rgba(100,100,150,120); border-radius: 4px; padding: 8px 16px; }"
                       "QPushButton:hover { color: #aaaacc; border-color: rgba(140,140,180,180); }"));
    btnRow->addWidget(m_inputDeferBtn);

    btnRow->addStretch();

    m_inputSubmitBtn = new QPushButton(QStringLiteral("确　认"), m_inputOverlay);
    m_inputSubmitBtn->setStyleSheet(
        QStringLiteral("QPushButton { background: #2a2450; color: #e8d5a3; font-size: 14px; "
                       "border: 1px solid rgba(190,160,80,200); border-radius: 4px; padding: 8px 24px; }"
                       "QPushButton:hover { background: #38306a; border-color: rgba(230,195,100,255); }"));
    btnRow->addWidget(m_inputSubmitBtn);
    inputVbox->addLayout(btnRow);
    m_inputOverlay->hide();

    m_portraitLeft = new QLabel(this);
    m_portraitLeft->setStyleSheet(QStringLiteral("background: transparent;"));
    m_portraitLeft->setAttribute(Qt::WA_TranslucentBackground);
    m_portraitLeft->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    m_portraitLeft->hide();

    m_portraitRight = new QLabel(this);
    m_portraitRight->setStyleSheet(QStringLiteral("background: transparent;"));
    m_portraitRight->setAttribute(Qt::WA_TranslucentBackground);
    m_portraitRight->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    m_portraitRight->hide();

    m_closeBtn = new QPushButton(QStringLiteral("×"), this);
    m_closeBtn->setFixedSize(34, 34);
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setToolTip(QStringLiteral("关闭（Esc）"));
    m_closeBtn->setStyleSheet(
        QStringLiteral("QPushButton { background: rgba(10, 10, 22, 180); color: #c8c0b0; "
                       "border: 1px solid rgba(120, 100, 60, 140); border-radius: 17px; "
                       "font-size: 20px; font-weight: 600; padding-bottom: 2px; }"
                       "QPushButton:hover { background: rgba(42, 38, 80, 220); color: #fff8e0; "
                       "border-color: rgba(220, 185, 90, 220); }"));
    m_closeBtn->raise();

    setStyleSheet(
        QStringLiteral("QWidget { background: #0e0e16; }"
                       "#choiceOverlay QPushButton {"
                       "    background: #14142c; color: #ede0c4; "
                       "    border: 1.5px solid rgba(190, 160, 80, 210); border-radius: 4px; "
                       "    padding: 13px 28px; font-size: 16px; text-align: center; }"
                       "#choiceOverlay QPushButton:hover {"
                       "    background: #2a2650; border-color: rgba(240, 200, 100, 255); color: #fff8e0; }"
                       "#choiceOverlay QPushButton:pressed { background: #38306a; }"));

    connect(m_pageBtn, &QPushButton::clicked, this, &StoryEventWidget::onAdvanceClicked);
    connect(m_closeBtn, &QPushButton::clicked, this, &StoryEventWidget::closeRequested);
    connect(m_inputDeferBtn, &QPushButton::clicked, this, &StoryEventWidget::monumentDeferRequested);
    connect(m_inputSubmitBtn, &QPushButton::clicked, this, &StoryEventWidget::monumentSubmitRequested);
    connect(m_inputEdit, &QLineEdit::returnPressed, this, &StoryEventWidget::monumentSubmitRequested);

    m_imageAreaWidget->installEventFilter(this);
    m_narrativeLabel->installEventFilter(this);
}

void StoryEventWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath clip;
    clip.addRoundedRect(rect(), 12, 12);
    p.setClipPath(clip);

    const int imageH = height() - kTextPanelH;

    p.fillRect(0, 0, width(), imageH, QColor(0x0d, 0x0d, 0x1a));
    if (!m_bgPixmap.isNull()) {
        QPixmap scaled = m_bgPixmap.scaledToWidth(width(), Qt::SmoothTransformation);
        if (scaled.height() < imageH) {
            scaled = m_bgPixmap.scaledToHeight(imageH, Qt::SmoothTransformation);
        }
        const int drawY = (imageH - scaled.height()) / 2;
        p.drawPixmap(0, drawY, scaled);
    }
    p.fillRect(0, imageH, width(), kTextPanelH, QColor(10, 10, 22));

    p.setClipping(false);
    p.setPen(QPen(QColor(0x4a, 0x4a, 0x7a), 1));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5), 12, 12);
}

void StoryEventWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    positionPortrait();
    positionChoiceOverlay();
    positionInputOverlay();
    positionCloseButton();
}

void StoryEventWidget::positionCloseButton()
{
    if (!m_closeBtn) {
        return;
    }

    m_closeBtn->move(width() - m_closeBtn->width() - 10, 10);
    m_closeBtn->raise();
}

void StoryEventWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && canAdvanceNarration()) {
        onAdvanceClicked();
        event->accept();
        return;
    }
    QWidget::mousePressEvent(event);
}

void StoryEventWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit closeRequested();
        event->accept();
        return;
    }

    if (canAdvanceNarration()) {
        onAdvanceClicked();
        event->accept();
        return;
    }
    QWidget::keyPressEvent(event);
}

bool StoryEventWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        auto *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton && canAdvanceNarration()) {
            onAdvanceClicked();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

bool StoryEventWidget::canAdvanceNarration() const
{
    return m_pageBtn && m_pageBtn->isVisible() && m_choiceOverlay && m_choiceOverlay->isHidden()
        && m_inputOverlay && m_inputOverlay->isHidden();
}

void StoryEventWidget::setEventTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

void StoryEventWidget::setDialogueSiteId(int siteId)
{
    m_dialogueSiteId = siteId;
}

void StoryEventWidget::setBackgroundPixmap(const QPixmap &pixmap)
{
    m_bgPixmap = pixmap;
    update();
}

void StoryEventWidget::clearBackground()
{
    m_bgPixmap = {};
    update();
}

void StoryEventWidget::setLeftPortrait(const QPixmap &pixmap,
                                       bool upperBodyCrop,
                                       bool fullBody,
                                       bool compactFullBody)
{
    m_leftPortraitSource = pixmap;
    m_leftUpperBodyCrop = upperBodyCrop;
    m_leftPortraitFullBody = fullBody;
    m_leftPortraitCompactFullBody = compactFullBody;
    if (pixmap.isNull()) {
        m_portraitLeft->hide();
        return;
    }
    m_portraitLeft->show();
    positionPortrait();
}

void StoryEventWidget::setRightPortrait(const QPixmap &pixmap, bool fullBody)
{
    m_rightPortraitSource = pixmap;
    m_rightPortraitFullBody = fullBody;
    if (pixmap.isNull()) {
        m_portraitRight->hide();
        return;
    }
    m_portraitRight->show();
    positionPortrait();
}

void StoryEventWidget::clearPortraits()
{
    m_leftPortraitSource = {};
    m_rightPortraitSource = {};
    m_leftPortraitFullBody = false;
    m_leftPortraitCompactFullBody = false;
    m_rightPortraitFullBody = false;
    m_portraitLeft->hide();
    m_portraitRight->hide();
}

void StoryEventWidget::positionPortrait()
{
    const int imageH = height() - kTextPanelH;
    const int defaultRightEffH = qMin(height() / 2, imageH);
    const int rightEffH = m_rightPortraitFullBody ? imageH : defaultRightEffH;
    const int rightMaxW = m_rightPortraitFullBody
        ? qMax(200, static_cast<int>(width() * 0.32))
        : qMax(180, static_cast<int>(width() * 0.34));
    const int rightBottomOffset = m_rightPortraitFullBody ? kRightPortraitDropY : 0;
    const int leftEffH = [&]() {
        if (!m_leftPortraitFullBody) {
            return qMax(240, qMin(static_cast<int>(imageH * 0.46), defaultRightEffH));
        }
        if (m_leftPortraitCompactFullBody) {
            return qMax(220, static_cast<int>(imageH * 0.90));
        }
        return imageH;
    }();
    const int leftMaxW = [&]() {
        if (!m_leftPortraitFullBody) {
            return qMax(180, static_cast<int>(width() * 0.30));
        }
        if (m_leftPortraitCompactFullBody) {
            return qMax(170, static_cast<int>(width() * 0.28));
        }
        return qMax(200, static_cast<int>(width() * 0.32));
    }();
    const int leftBottomOffset = m_leftPortraitFullBody ? kLeftPortraitDropY : -kLeftPortraitLiftY;

    const auto placePortrait = [&](QLabel *label,
                                   const QPixmap &source,
                                   bool upperBodyCrop,
                                   bool onRight,
                                   int effH,
                                   int maxPortW,
                                   int bottomOffset) {
        if (!label->isVisible() || source.isNull()) {
            return;
        }

        const QPixmap display = upperBodyCrop ? upperBodyPortrait(source, effH, maxPortW)
                                              : halfBodyPortrait(source, effH, maxPortW);
        if (display.isNull()) {
            label->hide();
            return;
        }

        const int labelH = display.height();
        label->setFixedSize(display.width(), labelH);
        label->setPixmap(display);
        const int portY = imageH - labelH + bottomOffset;
        const int portX = onRight ? width() - display.width() - kPortX : kPortX;
        label->move(portX, portY);
        label->raise();
    };

    placePortrait(m_portraitRight, m_rightPortraitSource, false, true, rightEffH, rightMaxW, rightBottomOffset);
    placePortrait(m_portraitLeft,
                  m_leftPortraitSource,
                  m_leftUpperBodyCrop,
                  false,
                  leftEffH,
                  leftMaxW,
                  leftBottomOffset);

    if (m_choiceOverlay) {
        m_choiceOverlay->raise();
    }
    if (m_inputOverlay) {
        m_inputOverlay->raise();
    }
}

void StoryEventWidget::positionChoiceOverlay()
{
    if (!m_choiceOverlay || m_choiceButtons.isEmpty()) {
        return;
    }

    m_choiceOverlay->adjustSize();
    const int imageH = height() - kTextPanelH;
    const int overlayW = qMin(static_cast<int>(width() * 0.62), 660);
    const int overlayH = m_choiceOverlay->sizeHint().height();
    const int x = (width() - overlayW) / 2;
    const int y = qMax(20, imageH / 2 - overlayH / 2);
    m_choiceOverlay->setGeometry(x, y, overlayW, overlayH);
    m_choiceOverlay->raise();
}

void StoryEventWidget::positionInputOverlay()
{
    if (!m_inputOverlay) {
        return;
    }

    m_inputOverlay->adjustSize();
    const int imageH = height() - kTextPanelH;
    const int overlayW = qMin(static_cast<int>(width() * 0.62), 660);
    const int overlayH = m_inputOverlay->sizeHint().height();
    const int x = (width() - overlayW) / 2;
    const int y = qMax(20, imageH / 2 - overlayH / 2);
    m_inputOverlay->setGeometry(x, y, overlayW, overlayH);
    m_inputOverlay->raise();
}

void StoryEventWidget::setNarrativeText(const QString &text, bool typewriter)
{
    hideInteractions();
    m_pageBtn->hide();

    if (!typewriter) {
        finishTypewriter();
        m_narrativeLabel->setText(formatDialogueHtml(text, m_dialogueSiteId));
        m_pendingText = text;
        m_typeIndex = text.size();
        setAdvanceHintVisible(true);
        return;
    }

    m_pendingText = text;
    m_typeIndex = 0;
    m_typewriterActive = true;
    m_narrativeLabel->clear();
    m_typeTimer->start();
    onTypewriterTick();
}

void StoryEventWidget::onTypewriterTick()
{
    if (m_typeIndex >= m_pendingText.size()) {
        m_typeTimer->stop();
        m_typewriterActive = false;
        setAdvanceHintVisible(true);
        return;
    }

    m_narrativeLabel->setText(formatDialogueHtml(m_pendingText.left(++m_typeIndex), m_dialogueSiteId));
}

void StoryEventWidget::skipTypewriter()
{
    if (!m_typewriterActive) {
        return;
    }
    finishTypewriter();
    setAdvanceHintVisible(true);
}

void StoryEventWidget::finishTypewriter()
{
    if (m_typeTimer) {
        m_typeTimer->stop();
    }
    m_typewriterActive = false;
    m_typeIndex = m_pendingText.size();
    m_narrativeLabel->setText(formatDialogueHtml(m_pendingText, m_dialogueSiteId));
}

bool StoryEventWidget::isTypewriterActive() const
{
    return m_typewriterActive;
}

void StoryEventWidget::setAdvanceHintVisible(bool visible)
{
    m_pageBtn->setVisible(visible);
    if (visible) {
        setFocus(Qt::OtherFocusReason);
    }
}

void StoryEventWidget::clearChoiceButtons()
{
    for (QPushButton *button : m_choiceButtons) {
        m_choiceLayout->removeWidget(button);
        button->deleteLater();
    }
    m_choiceButtons.clear();
}

void StoryEventWidget::showChoiceButtons(const QString &choiceA, const QString &choiceB)
{
    showChoiceButtons(choiceA, choiceB, {});
}

void StoryEventWidget::showChoiceButtons(const QString &choiceA,
                                         const QString &choiceB,
                                         const QString &choiceC)
{
    hideInteractions();
    clearChoiceButtons();

    auto addChoiceButton = [this](const QString &text, auto signal) {
        if (text.isEmpty()) {
            return;
        }
        auto *button = new QPushButton(text, m_choiceOverlay);
        button->setAutoFillBackground(true);
        button->setStyleSheet(
            QStringLiteral("QPushButton { background: rgba(20, 20, 44, 230); color: #ede0c4; "
                           "border: 1px solid rgba(190,160,80,210); border-radius: 4px; "
                           "padding: 10px 16px; text-align: left; }"
                           "QPushButton:hover { background: rgba(42, 38, 80, 240); color: #fff8e0; }"));
        connect(button, &QPushButton::clicked, this, signal);
        m_choiceLayout->addWidget(button);
        m_choiceButtons << button;
    };

    addChoiceButton(choiceA, &StoryEventWidget::choiceARequested);
    addChoiceButton(choiceB, &StoryEventWidget::choiceBRequested);
    addChoiceButton(choiceC, &StoryEventWidget::choiceCRequested);

    m_choiceOverlay->show();
    positionChoiceOverlay();
}

void StoryEventWidget::showMonumentInput(const QString &deferText,
                                         const QString &promptText,
                                         const QString &placeholder)
{
    hideInteractions();
    m_inputDeferBtn->setText(deferText);
    m_inputPrompt->setText(promptText);
    m_inputEdit->setPlaceholderText(placeholder);
    m_inputEdit->clear();
    m_inputOverlay->show();
    positionInputOverlay();
    m_inputEdit->setFocus();
}

void StoryEventWidget::hideInteractions()
{
    m_pageBtn->hide();
    clearChoiceButtons();
    m_choiceOverlay->hide();
    m_inputOverlay->hide();
}

QString StoryEventWidget::monumentAnswer() const
{
    return m_inputEdit->text().trimmed();
}

void StoryEventWidget::clearMonumentAnswer()
{
    m_inputEdit->clear();
}

void StoryEventWidget::onAdvanceClicked()
{
    if (m_typewriterActive) {
        skipTypewriter();
        return;
    }
    emit advanceRequested();
}
