#include "game_progress.h"

#include "site_graph.h"

QString introCompletedKey()
{
    return QStringLiteral("intro/completed");
}

QString mirrorLakePathKey()
{
    return QStringLiteral("mirrorLake/path");
}

QString siteStateKey(int index)
{
    return QStringLiteral("siteState/button%1").arg(index);
}

QString legacyUnlockKey(int index)
{
    return QStringLiteral("unlocked/button%1").arg(index);
}

QString legacyClickCountKey(int index)
{
    return QStringLiteral("clickCount/button%1").arg(index);
}

QSettings makeGameSettings()
{
    return QSettings(QStringLiteral("PKU-Explorer"), QStringLiteral("basic_framework"));
}

bool isProgressSaveEmpty()
{
    QSettings settings = makeGameSettings();

    for (int i = 1; i <= kSiteCount; ++i) {
        if (settings.contains(siteStateKey(i))) {
            return false;
        }
        if (settings.contains(legacyUnlockKey(i))) {
            return false;
        }
        if (settings.contains(legacyClickCountKey(i))) {
            return false;
        }
    }

    return true;
}

bool isIntroCompleted()
{
    return makeGameSettings().value(introCompletedKey(), false).toBool();
}

bool shouldShowIntroOnStart()
{
    return !isIntroCompleted();
}

void migrateIntroForLegacySave()
{
    QSettings settings = makeGameSettings();
    if (settings.contains(introCompletedKey())) {
        return;
    }

    if (!isProgressSaveEmpty()) {
        setIntroCompleted(true);
    }
}

void clearMirrorLakePath()
{
    QSettings settings = makeGameSettings();
    settings.remove(mirrorLakePathKey());
    settings.sync();
}

void clearGameProgress()
{
    QSettings settings = makeGameSettings();
    for (int i = 1; i <= kSiteCount; ++i) {
        settings.remove(siteStateKey(i));
        settings.remove(legacyUnlockKey(i));
        settings.remove(legacyClickCountKey(i));
    }
    settings.remove(mirrorLakePathKey());
    settings.sync();
}

void setIntroCompleted(bool completed)
{
    QSettings settings = makeGameSettings();
    settings.setValue(introCompletedKey(), completed);
    settings.sync();
}

MirrorLakePath mirrorLakePath()
{
    const int stored = makeGameSettings().value(mirrorLakePathKey(), 0).toInt();
    if (stored == static_cast<int>(MirrorLakePath::Bridge)) {
        return MirrorLakePath::Bridge;
    }
    if (stored == static_cast<int>(MirrorLakePath::StoneBoat)) {
        return MirrorLakePath::StoneBoat;
    }
    return MirrorLakePath::Unknown;
}

void setMirrorLakePath(MirrorLakePath path)
{
    QSettings settings = makeGameSettings();
    settings.setValue(mirrorLakePathKey(), static_cast<int>(path));
    settings.sync();
}
