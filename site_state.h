#ifndef SITE_STATE_H
#define SITE_STATE_H

#include <QString>
#include <QVariant>

enum class SiteState {
    Locked = 0,
    ToExplore = 1,
    Explored = 2,
};

inline QString siteStateLabel(SiteState state)
{
    switch (state) {
    case SiteState::Locked:
        return QStringLiteral("未解锁");
    case SiteState::ToExplore:
        return QStringLiteral("待探索");
    case SiteState::Explored:
        return QStringLiteral("已探索");
    }
    return QStringLiteral("未解锁");
}

inline bool isSiteClickable(SiteState state)
{
    return state == SiteState::ToExplore || state == SiteState::Explored;
}

inline bool isSiteExplored(SiteState state)
{
    return state == SiteState::Explored;
}

inline SiteState siteStateFromVariant(const QVariant &value, SiteState defaultState)
{
    bool ok = false;
    const int raw = value.toInt(&ok);
    if (!ok || raw < 0 || raw > 2) {
        return defaultState;
    }
    return static_cast<SiteState>(raw);
}

#endif // SITE_STATE_H
