#ifndef GAME_PROGRESS_H
#define GAME_PROGRESS_H

#include <QSettings>

enum class MirrorLakePath {
    Unknown = 0,
    Bridge = 1,
    StoneBoat = 2,
};

QSettings makeGameSettings();

bool isProgressSaveEmpty();
bool isIntroCompleted();
bool shouldShowIntroOnStart();
void setIntroCompleted(bool completed = true);
void migrateIntroForLegacySave();
void clearGameProgress();

MirrorLakePath mirrorLakePath();
void setMirrorLakePath(MirrorLakePath path);
void clearMirrorLakePath();

#endif // GAME_PROGRESS_H
