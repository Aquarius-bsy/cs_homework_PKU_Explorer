#include "explorer_map_widget.h"

#include <QConicalGradient>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QResizeEvent>
#include <QScrollBar>
#include <QSet>
#include <QShowEvent>
#include <QTimer>
#include <QWheelEvent>

namespace {

class ExplorerSiteMarker : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit ExplorerSiteMarker(int siteId, const QString &name, SiteMarkerType type, QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent)
        , m_siteId(siteId)
        , m_name(name)
        , m_type(type)
    {
        setAcceptHoverEvents(true);
        setToolTip(name);
    }

    QRectF boundingRect() const override
    {
        return QRectF(-28, -28, 56, 56);
    }

    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override
    {
        p->setRenderHint(QPainter::Antialiasing);

        if (m_hovered) {
            p->setPen(Qt::NoPen);
            p->setBrush(QColor(255, 255, 255, 40));
            p->drawEllipse(-32, -32, 64, 64);
        }

        if (isLuIslandSite(m_siteId) && m_colorful) {
            QConicalGradient gradient(0, 0, 0);
            gradient.setColorAt(0.00, QColor(180, 120, 255));
            gradient.setColorAt(0.25, QColor(255, 210, 90));
            gradient.setColorAt(0.50, QColor(120, 235, 190));
            gradient.setColorAt(0.75, QColor(110, 180, 255));
            gradient.setColorAt(1.00, QColor(255, 140, 190));
            p->setPen(QPen(QColor(255, 252, 235), m_hovered ? 2.5 : 1.5));
            p->setBrush(gradient);
            p->drawEllipse(-22, -22, 44, 44);
        } else if (isLuIslandSite(m_siteId) && !m_locked && m_unlockProgress > 0.0) {
            p->setPen(QPen(QColor(240, 236, 255), m_hovered ? 2.5 : 1.5));
            p->setBrush(QColor(140, 134, 168));
            p->drawEllipse(-22, -22, 44, 44);

            const QRectF fillRect(-22, 22 - 44 * m_unlockProgress, 44, 44 * m_unlockProgress);
            p->setPen(Qt::NoPen);
            p->setBrush(QColor(255, 228, 110));
            p->drawRect(fillRect);
        } else {
            const QColor base = siteMarkerColor(m_type);
            const QColor fill = m_locked ? QColor(QStringLiteral("#aaaaaa"))
                                         : (m_explored ? base.lighter(120) : base);
            const QColor border = m_hovered ? Qt::white : base.darker(130);
            p->setPen(QPen(border, m_hovered ? 2.5 : 1.5));
            p->setBrush(fill);
            p->drawEllipse(-22, -22, 44, 44);
        }

        const QString icon = m_locked ? QStringLiteral("?") : siteMarkerIcon(m_type);
        p->setPen(m_locked ? QColor(QStringLiteral("#666666")) : Qt::white);
        QFont font = p->font();
        font.setPixelSize(18);
        p->setFont(font);
        p->drawText(QRectF(-22, -22, 44, 44), Qt::AlignCenter, icon);

        if (m_hovered && !m_locked) {
            QFont nameFont = p->font();
            nameFont.setPixelSize(11);
            p->setFont(nameFont);
            QFontMetrics fm(nameFont);
            const int tw = fm.horizontalAdvance(m_name) + 12;
            p->setBrush(QColor(0, 0, 0, 150));
            p->setPen(Qt::NoPen);
            p->drawRoundedRect(-tw / 2, -44, tw, 18, 4, 4);
            p->setPen(Qt::white);
            p->drawText(QRect(-tw / 2, -44, tw, 18), Qt::AlignCenter, m_name);
        }

        if (!m_explored && !m_locked) {
            p->setPen(Qt::NoPen);
            p->setBrush(QColor(QStringLiteral("#E24B4A")));
            p->drawEllipse(18, -30, 9, 9);
        }
    }

    void setState(SiteState state, qreal unlockProgress, bool colorful)
    {
        m_locked = state == SiteState::Locked;
        m_explored = state == SiteState::Explored;
        m_unlockProgress = unlockProgress;
        m_colorful = colorful;
        setAcceptedMouseButtons(isSiteClickable(state) ? Qt::LeftButton : Qt::NoButton);
        update();
    }

signals:
    void clicked(int siteId);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            event->accept();
            const int siteId = m_siteId;
            QTimer::singleShot(0, this, [this, siteId]() { emit clicked(siteId); });
            return;
        }
        QGraphicsItem::mousePressEvent(event);
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override
    {
        m_hovered = true;
        update();
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override
    {
        m_hovered = false;
        update();
    }

private:
    int m_siteId = 0;
    QString m_name;
    SiteMarkerType m_type = SiteMarkerType::Camp;
    bool m_locked = true;
    bool m_explored = false;
    bool m_hovered = false;
    bool m_colorful = false;
    qreal m_unlockProgress = 0.0;
};

} // namespace

ExplorerMapWidget::ExplorerMapWidget(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new QGraphicsScene(this))
    , m_nodes(defaultSiteNodes())
    , m_edges(defaultSiteEdges())
{
    setScene(m_scene);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(QStringLiteral("background: #1a1a2e; border: none;"));
    setMinimumSize(640, 480);

    m_siteStates.fill(SiteState::Locked);

    const QPixmap map(QStringLiteral(":/images/campus_map_fantasy_named_v2.png"));
    if (!map.isNull()) {
        m_mapBg = m_scene->addPixmap(map);
        m_mapBg->setZValue(-1);
        m_mapBg->setAcceptedMouseButtons(Qt::NoButton);
        m_scene->setSceneRect(map.rect());
    } else {
        m_scene->setSceneRect(0, 0, 800, 600);
    }

    rebuildScene();
}

void ExplorerMapWidget::setSiteStates(const std::array<SiteState, kSiteCount> &states)
{
    m_siteStates = states;
    rebuildScene();
}

void ExplorerMapWidget::rebuildScene()
{
    for (QGraphicsItem *item : m_markers) {
        if (!item) {
            continue;
        }
        m_scene->removeItem(item);
        if (auto *marker = dynamic_cast<ExplorerSiteMarker *>(item)) {
            marker->deleteLater();
        } else {
            delete item;
        }
    }
    m_markers.fill(nullptr);

    for (QGraphicsLineItem *edge : m_edgeItems) {
        m_scene->removeItem(edge);
        delete edge;
    }
    m_edgeItems.clear();

    const QRectF sceneRect = m_scene->sceneRect();
    if (sceneRect.isEmpty()) {
        return;
    }

    QMap<int, QPointF> posMap;
    for (const GraphNode &node : m_nodes) {
        posMap[node.id] =
            QPointF((node.normPos.x() + node.markerOffsetNorm.x()) * sceneRect.width(),
                    (node.normPos.y() + node.markerOffsetNorm.y()) * sceneRect.height());
    }

    const qreal luProgress = luIslandUnlockProgress(m_siteStates);
    const bool luExplored = isSiteExplored(m_siteStates[kLuIslandSiteId - 1]);

    QSet<QString> drawnEdges;
    for (const GraphEdge &edge : m_edges) {
        const QString edgeKey =
            edge.fromId < edge.toId ? QStringLiteral("%1-%2").arg(edge.fromId).arg(edge.toId)
                                   : QStringLiteral("%1-%2").arg(edge.toId).arg(edge.fromId);
        if (drawnEdges.contains(edgeKey)) {
            continue;
        }
        drawnEdges.insert(edgeKey);

        if (!posMap.contains(edge.fromId) || !posMap.contains(edge.toId)) {
            continue;
        }

        const SiteState fromState = m_siteStates.at(edge.fromId - 1);
        const SiteState toState = m_siteStates.at(edge.toId - 1);
        const bool bothUnlocked = fromState != SiteState::Locked && toState != SiteState::Locked;

        QPen pen;
        if (bothUnlocked) {
            pen = QPen(QColor(100, 90, 180, 120), 1.5, Qt::SolidLine, Qt::RoundCap);
        } else {
            pen = QPen(QColor(60, 55, 100, 60), 1.0, Qt::DashLine, Qt::RoundCap);
        }

        auto *line = m_scene->addLine(QLineF(posMap.value(edge.fromId), posMap.value(edge.toId)), pen);
        line->setZValue(0);
        line->setAcceptedMouseButtons(Qt::NoButton);
        m_edgeItems << line;
    }

    for (const GraphNode &node : m_nodes) {
        auto *marker = new ExplorerSiteMarker(node.id, node.name, siteMarkerType(node.id));
        marker->setPos(posMap.value(node.id));
        marker->setZValue(1);
        m_scene->addItem(marker);
        m_markers[node.id - 1] = marker;

        qreal progress = 0.0;
        bool colorful = false;
        if (isLuIslandSite(node.id)) {
            progress = luProgress;
            colorful = luExplored;
        }

        marker->setState(m_siteStates.at(node.id - 1), progress, colorful);
        connect(marker, &ExplorerSiteMarker::clicked, this, &ExplorerMapWidget::siteClicked);
    }
}

bool ExplorerMapWidget::isSiteMarkerAt(const QPoint &viewPos) const
{
    return dynamic_cast<ExplorerSiteMarker *>(itemAt(viewPos)) != nullptr;
}

void ExplorerMapWidget::refitMapView()
{
    if (m_scene->sceneRect().isEmpty()) {
        return;
    }

    fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    m_initialFitDone = true;
}

void ExplorerMapWidget::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    if (!m_initialFitDone) {
        QTimer::singleShot(0, this, [this]() { refitMapView(); });
    }
}

void ExplorerMapWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    if (!m_initialFitDone && width() > 0 && height() > 0) {
        refitMapView();
    }
}

void ExplorerMapWidget::wheelEvent(QWheelEvent *event)
{
    const double factor = event->angleDelta().y() > 0 ? 1.15 : 0.87;
    const double currentScale = transform().m11();
    if ((factor > 1.0 && currentScale < 3.0) || (factor < 1.0 && currentScale > 0.5)) {
        scale(factor, factor);
    }
}

void ExplorerMapWidget::mousePressEvent(QMouseEvent *event)
{
    const bool panButton =
        event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton;
    if (panButton && !isSiteMarkerAt(event->pos())) {
        m_dragging = true;
        m_lastPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void ExplorerMapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        const QPoint delta = event->pos() - m_lastPos;
        m_lastPos = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        event->accept();
        return;
    }

    setCursor(isSiteMarkerAt(event->pos()) ? Qt::ArrowCursor : Qt::OpenHandCursor);
    QGraphicsView::mouseMoveEvent(event);
}

void ExplorerMapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_dragging) {
        m_dragging = false;
        setCursor(isSiteMarkerAt(event->pos()) ? Qt::ArrowCursor : Qt::OpenHandCursor);
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

#include "explorer_map_widget.moc"
