#include "explorer_site_pin.h"

#include "site_graph.h"

#include <QPainter>
#include <QPainterPath>
#include <QtMath>

namespace {

void drawPinGlow(QPainter &painter, const QRect &rect, const QColor &glowColor)
{
    QRadialGradient glow(rect.center(), rect.width() * 0.85);
    glow.setColorAt(0.0, glowColor);
    glow.setColorAt(1.0, QColor(glowColor.red(), glowColor.green(), glowColor.blue(), 0));
    painter.setPen(Qt::NoPen);
    painter.setBrush(glow);
    painter.drawEllipse(rect.adjusted(-5, -5, 5, 5));
}

} // namespace

ExplorerSitePin::ExplorerSitePin(int siteId, QWidget *parent)
    : QPushButton(parent)
    , m_siteId(siteId)
{
    setCursor(Qt::PointingHandCursor);
}

void ExplorerSitePin::setPinState(SiteState state, qreal progressFill, bool colorful)
{
    m_state = state;
    m_progress = qBound(0.0, progressFill, 1.0);
    m_colorful = colorful;
    setStyleSheet(QString());
    update();
}

void ExplorerSitePin::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QRect pinRect = rect().adjusted(2, 2, -2, -2);

    if (m_siteId == kLuIslandSiteId) {
        paintLuIslandPin(painter, pinRect);
        return;
    }

    paintStandardPin(painter, pinRect);
}

void ExplorerSitePin::paintStandardPin(QPainter &painter, const QRect &rect)
{
    QColor fill;
    QColor border;
    QColor glow;

    switch (m_state) {
    case SiteState::Locked:
        fill = QColor(168, 162, 198);
        border = QColor(240, 236, 255);
        glow = QColor(200, 195, 230, 150);
        break;
    case SiteState::ToExplore:
        fill = QColor(255, 228, 110);
        border = QColor(255, 252, 220);
        glow = QColor(255, 220, 100, 190);
        break;
    case SiteState::Explored:
        fill = QColor(118, 235, 188);
        border = QColor(230, 255, 245);
        glow = QColor(120, 240, 200, 185);
        break;
    }

    drawPinGlow(painter, rect, glow);

    painter.setPen(QPen(border, 2));
    painter.setBrush(fill);
    painter.drawEllipse(rect);
}

void ExplorerSitePin::paintLuIslandPin(QPainter &painter, const QRect &rect)
{
    const QPointF center = rect.center();
    const qreal radius = qMin(rect.width(), rect.height()) / 2.0;

    if (m_state == SiteState::Explored && m_colorful) {
        drawPinGlow(painter, rect, QColor(220, 180, 255, 200));

        QConicalGradient gradient(center, -90);
        gradient.setColorAt(0.0, QColor(210, 120, 255));
        gradient.setColorAt(0.25, QColor(255, 228, 120));
        gradient.setColorAt(0.5, QColor(130, 245, 200));
        gradient.setColorAt(0.75, QColor(150, 200, 255));
        gradient.setColorAt(1.0, QColor(255, 150, 190));

        painter.setPen(QPen(QColor(255, 252, 235), 2));
        painter.setBrush(gradient);
        painter.drawEllipse(center, radius, radius);
        return;
    }

    const QColor baseGray(140, 134, 168);
    const QColor borderGray(250, 246, 255);
    const QColor fillYellow(255, 228, 110);

    drawPinGlow(painter, rect, QColor(255, 220, 120, m_state == SiteState::ToExplore ? 200 : 120));

    painter.setPen(QPen(borderGray, 2));
    painter.setBrush(baseGray);
    painter.drawEllipse(center, radius, radius);

    const qreal fillRatio = m_state == SiteState::ToExplore ? 1.0 : m_progress;
    if (fillRatio <= 0.0) {
        return;
    }

    QPainterPath clipPath;
    const qreal fillHeight = rect.height() * fillRatio;
    const QRectF fillRect(rect.left(), rect.bottom() - fillHeight + 1, rect.width(), fillHeight);
    clipPath.addRect(fillRect);
    clipPath.addEllipse(center, radius, radius);

    painter.save();
    painter.setClipPath(clipPath, Qt::IntersectClip);
    painter.setPen(Qt::NoPen);
    painter.setBrush(fillYellow);
    painter.drawEllipse(center, radius, radius);
    painter.restore();
}
