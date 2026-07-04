#ifndef EXPLORER_MAP_WIDGET_H
#define EXPLORER_MAP_WIDGET_H

#include "site_graph.h"
#include "site_state.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <array>

class ExplorerMapWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ExplorerMapWidget(QWidget *parent = nullptr);

    void setSiteStates(const std::array<SiteState, kSiteCount> &states);

signals:
    void siteClicked(int siteId);

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void refitMapView();

    QGraphicsScene *m_scene = nullptr;
    QGraphicsPixmapItem *m_mapBg = nullptr;
    std::array<QGraphicsItem *, kSiteCount> m_markers{};
    QList<QGraphicsLineItem *> m_edgeItems;
    std::array<SiteState, kSiteCount> m_siteStates{};
    QVector<GraphNode> m_nodes;
    QVector<GraphEdge> m_edges;
    bool m_dragging = false;
    bool m_initialFitDone = false;
    QPoint m_lastPos;

    void rebuildScene();
    bool isSiteMarkerAt(const QPoint &viewPos) const;
};

#endif // EXPLORER_MAP_WIDGET_H
