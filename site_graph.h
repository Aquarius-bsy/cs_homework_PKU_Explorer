#ifndef SITE_GRAPH_H
#define SITE_GRAPH_H

#include "site_state.h"

#include <QColor>
#include <QPointF>
#include <QString>
#include <QVector>

inline constexpr int kSiteCount = 12;
inline constexpr int kLuIslandSiteId = 7;
inline constexpr int kMirrorLakeSiteId = 6;
inline constexpr int kInitialStartSiteId = 11;
inline constexpr int kSitesRequiredBeforeLuIsland = kSiteCount - 1;

enum class LuIslandVisitMode {
    ShoreView,
    ExploreMore,
    Finale,
};

struct GraphNode {
    int id = 0;
    QString name;
    QPointF normPos;
    QPointF markerOffsetNorm;
};

struct GraphEdge {
    int fromId = 0;
    int toId = 0;
};

inline QVector<GraphNode> defaultSiteNodes()
{
    // 圆点坐标（campus_map_fantasy_named_v2.png）；markerOffsetNorm 将圆点挪到标牌外侧，避免挡住地名
    return {
        {1, QStringLiteral("天门"), {0.03, 0.62}, {0.018, 0.030}},
        {2, QStringLiteral("遗迹花园"), {0.18, 0.48}, {-0.022, 0.028}},
        {3, QStringLiteral("旧日之境"), {0.125, 0.72}, {-0.020, 0.034}},
        {4, QStringLiteral("禁书收藏馆"), {0.46, 0.46}, {0.0, 0.036}},
        {5, QStringLiteral("塞万提斯像"), {0.28, 0.36}, {-0.024, -0.018}},
        {6, QStringLiteral("镜湖"), {0.50, 0.26}, {0.0, 0.012}},
        {7, QStringLiteral("湖心岛"), {0.47, 0.165}, {0.0, -0.026}},
        {8, QStringLiteral("奥术尖塔"), {0.685, 0.355}, {0.026, 0.012}},
        {9, QStringLiteral("行者酒馆"), {0.63, 0.56}, {0.034, 0.014}},
        {10, QStringLiteral("吟游剧场"), {0.48, 0.645}, {0.0, 0.038}},
        {11, QStringLiteral("咒术大楼"), {0.755, 0.535}, {0.008, 0.030}},
        {12, QStringLiteral("角斗场"), {0.735, 0.795}, {0.024, 0.040}},
    };
}

inline QString siteName(int siteId)
{
    const QVector<GraphNode> nodes = defaultSiteNodes();
    for (const GraphNode &node : nodes) {
        if (node.id == siteId) {
            return node.name;
        }
    }
    return {};
}

inline QVector<GraphEdge> defaultSiteEdges()
{
    return {
        {1, 2}, {1, 3},
        {2, 4}, {2, 5}, {2, 10},
        {3, 10},
        {4, 5}, {4, 6}, {4, 8}, {4, 9},
        {5, 6},
        {6, 8},
        {8, 9}, {8, 11},
        {9, 10}, {9, 11}, {9, 12},
        {10, 12},
    };
}

inline QVector<int> neighborsOf(int siteId)
{
    switch (siteId) {
    case 1: return {2, 3};
    case 2: return {1, 4, 5, 10};
    case 3: return {1, 10};
    case 4: return {2, 5, 6, 8, 9};
    case 5: return {2, 4, 6};
    case 6: return {4, 5, 8};
    case 7: return {};
    case 8: return {4, 6, 9, 11};
    case 9: return {4, 8, 10, 11, 12};
    case 10: return {2, 3, 9, 12};
    case 11: return {8, 9};
    case 12: return {9, 10, 11};
    default: return {};
    }
}

inline bool isInitialStartSite(int siteId)
{
    return siteId == kInitialStartSiteId;
}

inline bool isLuIslandSite(int siteId)
{
    return siteId == kLuIslandSiteId;
}

template <typename StateContainer>
int exploredCountExcludingLuIsland(const StateContainer &states)
{
    int count = 0;
    for (int i = 0; i < states.size(); ++i) {
        if (i + 1 == kLuIslandSiteId) {
            continue;
        }
        if (states[i] == SiteState::Explored) {
            ++count;
        }
    }
    return count;
}

template <typename StateContainer>
qreal luIslandUnlockProgress(const StateContainer &states)
{
    return static_cast<qreal>(exploredCountExcludingLuIsland(states))
        / static_cast<qreal>(kSitesRequiredBeforeLuIsland);
}

inline QVector<int> luIslandAdjacentSiteIds()
{
    return {4, 5, kMirrorLakeSiteId, 8};
}

template <typename StateContainer>
bool isMirrorLakePassed(const StateContainer &states)
{
    return states.at(kMirrorLakeSiteId - 1) == SiteState::Explored;
}

template <typename StateContainer>
bool isAnyLuIslandAdjacentExplored(const StateContainer &states)
{
    for (int siteId : luIslandAdjacentSiteIds()) {
        if (states.at(siteId - 1) == SiteState::Explored) {
            return true;
        }
    }
    return false;
}

template <typename StateContainer>
bool areAllSitesExploredExceptLuIsland(const StateContainer &states)
{
    for (int i = 0; i < states.size(); ++i) {
        if (i + 1 == kLuIslandSiteId) {
            continue;
        }
        if (states.at(i) != SiteState::Explored) {
            return false;
        }
    }
    return true;
}

template <typename StateContainer>
LuIslandVisitMode luIslandVisitModeFor(const StateContainer &states)
{
    if (!isMirrorLakePassed(states)) {
        return LuIslandVisitMode::ShoreView;
    }
    if (!areAllSitesExploredExceptLuIsland(states)) {
        return LuIslandVisitMode::ExploreMore;
    }
    return LuIslandVisitMode::Finale;
}

inline const GraphNode *findGraphNode(const QVector<GraphNode> &nodes, int id)
{
    for (const GraphNode &node : nodes) {
        if (node.id == id) {
            return &node;
        }
    }
    return nullptr;
}

enum class SiteMarkerType {
    MagicTower,
    Tavern,
    Arena,
    Alchemist,
    Camp,
    Council,
    SecretGarden,
};

inline SiteMarkerType siteMarkerType(int siteId)
{
    switch (siteId) {
    case 8:
    case 11:
        return SiteMarkerType::MagicTower;
    case 9:
        return SiteMarkerType::Tavern;
    case 12:
        return SiteMarkerType::Arena;
    case 4:
        return SiteMarkerType::Alchemist;
    case 3:
    case 6:
    case 10:
        return SiteMarkerType::Camp;
    case 1:
    case 5:
        return SiteMarkerType::Council;
    case 2:
    case 7:
    default:
        return SiteMarkerType::SecretGarden;
    }
}

inline QColor siteMarkerColor(SiteMarkerType type)
{
    switch (type) {
    case SiteMarkerType::MagicTower:
        return QColor(QStringLiteral("#7F77DD"));
    case SiteMarkerType::Tavern:
        return QColor(QStringLiteral("#EF9F27"));
    case SiteMarkerType::Arena:
        return QColor(QStringLiteral("#D85A30"));
    case SiteMarkerType::Alchemist:
        return QColor(QStringLiteral("#1D9E75"));
    case SiteMarkerType::Camp:
        return QColor(QStringLiteral("#378ADD"));
    case SiteMarkerType::Council:
        return QColor(QStringLiteral("#888780"));
    case SiteMarkerType::SecretGarden:
        return QColor(QStringLiteral("#D4537E"));
    }
    return QColor(QStringLiteral("#888780"));
}

inline QString siteMarkerIcon(SiteMarkerType type)
{
    switch (type) {
    case SiteMarkerType::MagicTower:
        return QStringLiteral("M");
    case SiteMarkerType::Tavern:
        return QStringLiteral("T");
    case SiteMarkerType::Arena:
        return QStringLiteral("A");
    case SiteMarkerType::Alchemist:
        return QStringLiteral("L");
    case SiteMarkerType::Camp:
        return QStringLiteral("C");
    case SiteMarkerType::Council:
        return QStringLiteral("K");
    case SiteMarkerType::SecretGarden:
        return QStringLiteral("*");
    }
    return QStringLiteral("?");
}

#endif // SITE_GRAPH_H
