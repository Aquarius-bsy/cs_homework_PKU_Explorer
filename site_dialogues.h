#ifndef SITE_DIALOGUES_H
#define SITE_DIALOGUES_H

#include "site_graph.h"

#include "game_progress.h"
#include "site_answer_book.h"

#include <QVector>

inline constexpr int kTianmenSiteId = 1;
inline constexpr int kRuinGardenSiteId = 2;
inline constexpr int kOldRealmSiteId = 3;
inline constexpr int kForbiddenArchiveSiteId = 4;
inline constexpr int kArcaneTowerSiteId = 8;
inline constexpr int kTavernSiteId = 9;
inline constexpr int kTheaterSiteId = 10;
inline constexpr int kArenaSiteId = 12;

enum class DialogueBeatType {
    Narration,
    BinaryChoice,
    MultiChoice,
    TavernMonumentDecision,
    TheaterMuralDecision,
    MirrorLakeTowerDecision,
    OldRealmShopNameDecision,
    ForbiddenArchiveCatalogDecision,
};

enum class DialogueChoiceKind {
    None,
    TavernFirstReply,
    TavernMonument,
    TheaterMuralAuthor,
    TheaterViewMural,
    ArenaJoinBattle,
    ArenaExerciseToday,
    TianmenLeaveOrStay,
    TianmenConfirmLeave,
    LuIslandFinalChoice,
    LuIslandReturnOnly,
    SpellHallPrologueChoice,
    MirrorLakeTowerCount,
    ArcaneTowerEnterOrLeave,
    OldRealmEnterShop,
    ForbiddenArchiveVisitIntent,
    ForbiddenArchiveGenesisBookFamiliarity,
    RuinGardenLightOrShade,
    RuinGardenStayOrLeave,
};

inline QString mirrorLakeShoreBackgroundFile()
{
    return QStringLiteral("lake_background_1.png");
}

inline QString mirrorLakeBoatBackgroundFile()
{
    return QStringLiteral("lake_background_2.png");
}

inline QString mirrorLakeBoatAwakenedBackgroundFile()
{
    return QStringLiteral("lake_background_3.png");
}

inline QString mirrorLakeBackgroundFile()
{
    return mirrorLakeShoreBackgroundFile();
}

inline QString classroomBackground1File()
{
    return QStringLiteral("classroom_background_1.png");
}

inline QString classroomBackground2File()
{
    return QStringLiteral("classroom_background_2.png");
}

inline QString classroomBackground3File()
{
    return QStringLiteral("classroom_background_3.png");
}

inline QString classroomBackgroundFile()
{
    return classroomBackground2File();
}

inline QString tavernBossBackgroundFile()
{
    return QStringLiteral("bar_background_1.png");
}

inline QString tavernTravelerBackgroundFile()
{
    return QStringLiteral("bar_background_2.png");
}

inline QString witchPortraitFile()
{
    return QStringLiteral("witch.png");
}

inline QString barPublicanPortraitFile()
{
    return QStringLiteral("bar_publican.png");
}

inline QString barStrangerPortraitFile()
{
    return QStringLiteral("bar_stranger.png");
}

inline QString arenaEntranceBackgroundFile()
{
    return QStringLiteral("abattoir_background_1.png");
}

inline QString arcaneTowerApproachBackground1File()
{
    return QStringLiteral("tower_background_1.png");
}

inline QString arcaneTowerApproachBackground2File()
{
    return QStringLiteral("tower_background_2.png");
}

inline QString arcaneTowerDoorBackgroundFile()
{
    return QStringLiteral("tower_background_3.png");
}

inline QString arcaneTowerInteriorBackgroundFile()
{
    return QStringLiteral("tower_in.png");
}

inline QString arcaneTowerSummitBackgroundFile()
{
    return QStringLiteral("tower_on.png");
}

inline QString arcaneTowerLeaveBackgroundFile()
{
    return QStringLiteral("tower_leave.png");
}

inline QString arenaSpectatorBackgroundFile()
{
    return QStringLiteral("abattoir_background_2.png");
}

inline QString arenaBattleBackgroundFile()
{
    return QStringLiteral("abattoir_background_3.png");
}

inline QString abattoirWarriorPortraitFile()
{
    return QStringLiteral("abattoir_warrior.png");
}

inline QString abattoirManagerPortraitFile()
{
    return QStringLiteral("abattoir_manager.png");
}

inline QString abattoirAudience1PortraitFile()
{
    return QStringLiteral("abattoir_audience_1.png");
}

inline QString abattoirAudience2PortraitFile()
{
    return QStringLiteral("abattoir_audience_2.png");
}

inline QString theaterArrivalBackgroundFile()
{
    return QStringLiteral("theater_background_1.png");
}

inline QString theaterStaffBackgroundFile()
{
    return QStringLiteral("theater_background_2.png");
}

inline QString theaterMuralTalkBackgroundFile()
{
    return QStringLiteral("theater_background_3.png");
}

inline QString theaterMuralSleepingBackgroundFile()
{
    return QStringLiteral("theater_paint_sleeping.png");
}

inline QString theaterMuralAwakenBackgroundFile()
{
    return QStringLiteral("theater_paint_awaken.png");
}

inline QString theaterAssistancePortraitFile()
{
    return QStringLiteral("theater_staff.png");
}

inline QString williamYangPortraitFile()
{
    return QStringLiteral("library_assistance.png");
}

inline QString libraryBackground1File()
{
    return QStringLiteral("library_background_1.png");
}

inline QString libraryBackground2File()
{
    return QStringLiteral("library_background_2.png");
}

inline QString libraryBackground3File()
{
    return QStringLiteral("library_background_3.png");
}

inline QString libraryHallBackgroundFile()
{
    return libraryBackground1File();
}

inline QString libraryHistoryCorridorBackgroundFile()
{
    return libraryBackground2File();
}

inline QString libraryPhilosophyWingBackgroundFile()
{
    return libraryBackground3File();
}

inline QString libraryAncientStacksBackgroundFile()
{
    return libraryBackground3File();
}

inline QString libraryShelfBackgroundFile()
{
    return QStringLiteral("library_shelf.png");
}

inline QString libraryBookBackgroundFile()
{
    return QStringLiteral("library_book.png");
}

inline QString libraryReadingBackgroundFile()
{
    return libraryBookBackgroundFile();
}

inline QString gateBackground1File()
{
    return QStringLiteral("gate_background_1.png");
}

inline QString gateBackground2File()
{
    return QStringLiteral("gate_background_2.png");
}

inline QString gateBackground3File()
{
    return QStringLiteral("gate_background_3.png");
}

inline QString gateBackground4File()
{
    return QStringLiteral("gate_background_4.png");
}

inline QString ruinGardenEntryBackgroundFile()
{
    return QStringLiteral("garden_entry.png");
}

inline QString ruinGardenLightForkBackgroundFile()
{
    return QStringLiteral("garden_light_1.png");
}

inline QString ruinGardenShadowForkBackgroundFile()
{
    return QStringLiteral("garden_shadow_1.png");
}

inline QString ruinGardenLightPathBackgroundFile()
{
    return QStringLiteral("garden_light_2.png");
}

inline QString ruinGardenShadowPathBackgroundFile()
{
    return QStringLiteral("garden_shadow_2.png");
}

inline QString ruinGardenHeartBackgroundFile()
{
    return QStringLiteral("garden_pool.png");
}

inline QString ruinGardenFarewellBackgroundFile()
{
    return QStringLiteral("garden_leave.png");
}

inline bool lineHasSpeakerPrefix(const QString &line, const QString &prefix)
{
    return line.startsWith(prefix) || line.contains(QStringLiteral("\n") + prefix);
}

inline QString speakerPortraitForLine(const QString &line)
{
    if (lineHasSpeakerPrefix(line, QStringLiteral("小魔女"))) {
        return witchPortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("CM.J"))) {
        return theaterAssistancePortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("William.Yang"))) {
        return williamYangPortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("观众甲"))) {
        return abattoirAudience1PortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("观众乙"))) {
        return abattoirAudience2PortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("监管者"))) {
        return abattoirManagerPortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("战士"))) {
        return abattoirWarriorPortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("老板"))
        || lineHasSpeakerPrefix(line, QStringLiteral("老金"))
        || lineHasSpeakerPrefix(line, QStringLiteral("掌柜"))
        || lineHasSpeakerPrefix(line, QStringLiteral("郭神"))) {
        return barPublicanPortraitFile();
    }
    if (lineHasSpeakerPrefix(line, QStringLiteral("旅人"))) {
        return barStrangerPortraitFile();
    }
    return {};
}

struct DialogueBeat {
    DialogueBeatType type = DialogueBeatType::Narration;
    DialogueChoiceKind choiceKind = DialogueChoiceKind::None;
    QString line;
    QString sceneImageFile;
    QString speakerPortraitFile;
    QString leftPortraitFile;
    QString choiceA;
    QString choiceB;
    QString choiceC;
};

inline DialogueBeat narrationBeat(const QString &line,
                                  const QString &sceneImageFile = {},
                                  const QString &speakerPortraitFile = {})
{
    DialogueBeat beat;
    beat.type = DialogueBeatType::Narration;
    beat.choiceKind = DialogueChoiceKind::None;
    beat.line = line;
    beat.sceneImageFile = sceneImageFile;
    beat.speakerPortraitFile = speakerPortraitFile;
    return beat;
}

inline DialogueBeat binaryChoiceBeat(DialogueChoiceKind choiceKind,
                                     const QString &sceneImageFile,
                                     const QString &choiceA,
                                     const QString &choiceB)
{
    DialogueBeat beat;
    beat.type = DialogueBeatType::BinaryChoice;
    beat.choiceKind = choiceKind;
    beat.sceneImageFile = sceneImageFile;
    beat.choiceA = choiceA;
    beat.choiceB = choiceB;
    return beat;
}

inline DialogueBeat multiChoiceBeat(DialogueChoiceKind choiceKind,
                                    const QString &sceneImageFile,
                                    const QString &choiceA,
                                    const QString &choiceB,
                                    const QString &choiceC)
{
    DialogueBeat beat;
    beat.type = DialogueBeatType::MultiChoice;
    beat.choiceKind = choiceKind;
    beat.sceneImageFile = sceneImageFile;
    beat.choiceA = choiceA;
    beat.choiceB = choiceB;
    beat.choiceC = choiceC;
    return beat;
}

inline DialogueBeat dualPortraitBeat(const QString &line,
                                     const QString &sceneImageFile,
                                     const QString &leftPortraitFile,
                                     const QString &rightPortraitFile)
{
    DialogueBeat beat = narrationBeat(line, sceneImageFile);
    beat.leftPortraitFile = leftPortraitFile;
    beat.speakerPortraitFile = rightPortraitFile;
    return beat;
}

inline QString islandBackgroundFile()
{
    return QStringLiteral("island.png");
}

inline QString oldRealmGardenEntryFile()
{
    return QStringLiteral("yannan_background_1.png");
}

inline QString oldRealmGardenPathFile()
{
    return QStringLiteral("yannan_background_2.png");
}

inline QString oldRealmGardenDepthFile()
{
    return QStringLiteral("yannan_background_3.png");
}

inline QString oldRealmCottageExteriorFile()
{
    return QStringLiteral("yannan_house.png");
}

inline QString oldRealmShopSignFile()
{
    return QStringLiteral("yannan_house.png");
}

inline QString oldRealmShopDoorFile()
{
    return QStringLiteral("yannan_door.png");
}

inline QString oldRealmShopInteriorFile()
{
    return QStringLiteral("yannan_in.png");
}

inline bool isDialogueOnlySite(int siteId)
{
    return siteId == kInitialStartSiteId || siteId == kTianmenSiteId || siteId == kRuinGardenSiteId
        || siteId == kOldRealmSiteId
        || siteId == kForbiddenArchiveSiteId || siteId == kMirrorLakeSiteId || siteId == kTavernSiteId
        || siteId == kTheaterSiteId || siteId == kArenaSiteId || siteId == kArcaneTowerSiteId
        || siteId == kLuIslandSiteId;
}

inline DialogueBeat forbiddenArchiveCatalogDecisionBeat(const QString &sceneImageFile = {})
{
    DialogueBeat beat;
    beat.type = DialogueBeatType::ForbiddenArchiveCatalogDecision;
    beat.sceneImageFile =
        sceneImageFile.isEmpty() ? libraryAncientStacksBackgroundFile() : sceneImageFile;
    return beat;
}

inline bool checkForbiddenArchiveCatalogAnswer(const QString &userInput)
{
    return SiteAnswerBook::instance().checkAnswer(kForbiddenArchiveSiteId, userInput);
}

inline DialogueBeat oldRealmShopNameDecisionBeat(const QString &sceneImageFile = {})
{
    DialogueBeat beat;
    beat.type = DialogueBeatType::OldRealmShopNameDecision;
    beat.sceneImageFile = sceneImageFile.isEmpty() ? oldRealmShopSignFile() : sceneImageFile;
    return beat;
}

inline bool checkOldRealmShopNameAnswer(const QString &userInput)
{
    return SiteAnswerBook::instance().checkAnswer(kOldRealmSiteId, userInput);
}

inline QVector<DialogueBeat> tianmenMainDialogueBeats()
{
    const QString witch = witchPortraitFile();
    const QString bg1 = gateBackground1File();
    const QString bg2 = gateBackground2File();

    return {
        narrationBeat(QStringLiteral("（两根界柱立在道口。风从柱间穿过，又折回园里，像有人在那里系了看不见的绳结。）"),
                      bg1),
        narrationBeat(QStringLiteral("（柱基有极浅的刻痕，日光移过时，才显出一点旧色。）"), bg1),
        narrationBeat(QStringLiteral("小魔女：「天门。」"), bg1, witch),
        narrationBeat(QStringLiteral("（她只说了两个字，便和你一同站定。）"), bg1),
        narrationBeat(QStringLiteral("（远处有人负卷离开，有人负卷进来；靴底敲地的节奏一样轻。）"), bg2),
        narrationBeat(QStringLiteral("（有一瞬，柱影压在你脚前，像一道很低的门槛。）"), bg2),
        narrationBeat(QStringLiteral("（风里掠过半截未说完的咒名，碎在界柱后面。）"), bg2),
        narrationBeat(QStringLiteral("小魔女：「风常常在这里折返。」"), bg2, witch),
        narrationBeat(QStringLiteral("（界柱内侧，园的草木香；外侧，外域的天色略淡一点——也许只是云。）"), bg2),
        narrationBeat(QStringLiteral("（道口开着。没有锁，也没有声。）"), bg2),
        narrationBeat(QStringLiteral("（小魔女退半步，把道口让给你。）"), bg2),
        binaryChoiceBeat(DialogueChoiceKind::TianmenLeaveOrStay,
                         bg2,
                         QStringLiteral("往外走。"),
                         QStringLiteral("离开天门，回到园中。")),
    };
}

inline QVector<DialogueBeat> tianmenLeaveApproachBeats()
{
    const QString witch = witchPortraitFile();
    const QString bg3 = gateBackground3File();

    return {
        narrationBeat(QStringLiteral("（你迈出半步。）"), bg3),
        narrationBeat(QStringLiteral("（界柱、风、刻痕——像被水轻轻晕开。）"), bg3),
        narrationBeat(QStringLiteral("（脚底不再有门槛的感觉。）"), bg3),
        narrationBeat(QStringLiteral("小魔女：「……」"), bg3, witch),
        narrationBeat(QStringLiteral("（她没拦你。界柱外侧的天色，已经贴到了眼前。）"), bg3),
        narrationBeat(QStringLiteral("（再一步，大概就是外域。）"), bg3),
        narrationBeat(QStringLiteral(
                          "小魔女：「出了这道口，这次的探索便到此为止。园子里的路，不会为你留着。」"),
                      bg3,
                      witch),
        narrationBeat(QStringLiteral(
                          "小魔女：「确认离开的话，你在燕园的探索记录也会一并清空。」"),
                      bg3,
                      witch),
        binaryChoiceBeat(DialogueChoiceKind::TianmenConfirmLeave,
                         bg3,
                         QStringLiteral("确认离开魔法世界"),
                         QStringLiteral("我再想想")),
    };
}

inline QVector<QString> dreamWakeForgetEndingBeats()
{
    return {
        QStringLiteral("（投影的符文在眼前亮着。）"),
        QStringLiteral("（桌上摊着笔记，墨还没干。）"),
        QStringLiteral("（窗外树影晃了一下。）"),
        QStringLiteral("（你抬头。）"),
        QStringLiteral("（教室里很安静。实习课还没散。）"),
        QStringLiteral("（笔记本上都是你刚写的咒文。顺序都对，和睡着前一模一样。）"),
        QStringLiteral("（邻座有人在低声问导师。投影上的光斑移动，一切如常。）"),
        QStringLiteral("（好像做过很长的梦。）"),
        QStringLiteral("（你试着回忆——界柱，风，刻痕——像隔着一层雾。）"),
        QStringLiteral("（有什么名字在舌尖，还没吐出来，就散了。）"),
        QStringLiteral("（可梦里的字，一个也想不起来。）"),
        QStringLiteral("（……什么也没有发生。）"),
        QStringLiteral("（你只是睡着了，又醒了一次。）"),
        QStringLiteral("（生活继续。）"),
        QStringLiteral("（后来路过园子的边，风在某处折返。）"),
        QStringLiteral("（那一瞬间，你觉得丢过什么。）"),
        QStringLiteral("（下一脚，仍只是平常的路。）"),
        QStringLiteral("（想不起来了。）"),
    };
}

inline QVector<DialogueBeat> tianmenLeaveHandoffBeats()
{
    return {
        narrationBeat(QStringLiteral("（……）"), gateBackground3File()),
    };
}

inline QVector<DialogueBeat> tianmenContinueEndingBeats()
{
    const QString witch = witchPortraitFile();
    const QString bg4 = gateBackground4File();

    return {
        narrationBeat(QStringLiteral("（你转身，回到界柱内侧。）"), bg4),
        narrationBeat(QStringLiteral("（风从园里来，把柱基刻痕吹得又清楚一点。）"), bg4),
        narrationBeat(QStringLiteral("小魔女：「好。」"), bg4, witch),
        narrationBeat(QStringLiteral("（就一个字。她先走，袍角掠过刻痕边缘。）"), bg4),
        narrationBeat(QStringLiteral("（你跟上去。道口还在身后，门闩从未合上。）"), bg4),
        narrationBeat(QStringLiteral("（天门在视野里变小，像一枚始终未落的月。）"), bg4),
    };
}

inline bool checkTavernMonumentAnswer(const QString &userInput)
{
    return SiteAnswerBook::instance().checkAnswer(kTavernSiteId, userInput);
}

inline bool checkTheaterMuralAuthorAnswer(const QString &userInput)
{
    return SiteAnswerBook::instance().checkAnswer(kTheaterSiteId, userInput);
}

inline QVector<DialogueBeat> tavernMainDialogueBeats()
{
    const QString bossScene = tavernBossBackgroundFile();
    const QString travelerScene = tavernTravelerBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString boss = barPublicanPortraitFile();
    const QString stranger = barStrangerPortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「歇一脚吧。这家酒馆在冒险者嘴里只认两件事：酒贵，消息更贵。」"),
         bossScene,
         witch},
        narrationBeat(QStringLiteral("郭神：（把木杯重重放下）「两位，先说明白——买酒，还是买话？」"),
                      bossScene,
                      boss),
        binaryChoiceBeat(DialogueChoiceKind::TavernFirstReply,
                         bossScene,
                         QStringLiteral("买酒"),
                         QStringLiteral("买话")),
        narrationBeat(QStringLiteral("旅人：（角落里，声音沙哑）「换话的人，通常换不走真相，只能换走一个更安全的问题。」"),
                      travelerScene,
                      stranger),
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：（压低声音）「他在打听花神庙碑的下落，但不想自己露面。」"),
         travelerScene,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("郭神：（朝旅人努努嘴）「那位客人付过酒钱了，付的是你的那份。他说，只要你回答他一个问题，今晚全店的人都会装作没见过你。」"),
         travelerScene,
         boss},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「什么问题？」"),
         travelerScene,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("旅人：「镜湖的边上有一座花神庙，据说当年迁至镜湖边上时还有一块花神庙碑一同迁来。而花神庙碑却在迁移途中丢失，至今不知所踪，你可曾见过它在哪里吗？」"),
         travelerScene,
         stranger},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：（轻轻碰了碰你的袖子）「别急着编。花神庙碑是真实存在的，如果你还没见到过，不妨多在校园里走走，发现了再来回答吧。」"),
         travelerScene,
         witch},
        {DialogueBeatType::TavernMonumentDecision,
         DialogueChoiceKind::TavernMonument,
         {},
         travelerScene,
         {}},
    };
}

inline QString tavernBossReplyAfterWine()
{
    return QStringLiteral("郭神：「酒三枚银币，先付后饮。话嘛……看你们能拿什么换。」");
}

inline QString tavernBossReplyAfterTalk()
{
    return QStringLiteral("郭神：「话按问题计价。你若能答上来，今晚的酒钱便算这位客人请了。」");
}

inline QVector<DialogueBeat> tavernGoodEndingBeats(const QString &playerAnswerLine)
{
    const QString bossScene = tavernBossBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString boss = barPublicanPortraitFile();
    const QString stranger = barStrangerPortraitFile();

    return {
        {DialogueBeatType::Narration, DialogueChoiceKind::None, playerAnswerLine, tavernTravelerBackgroundFile(), {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("旅人：（把一枚旧银币放在桌上）「看来你不是在胡编。这园子里，确实还有人记得它。」"),
         tavernTravelerBackgroundFile(),
         stranger},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("郭神：（笑了）「行，酒钱免了。出门口往左，别往右；右边通往角斗场，最近不太平。」"),
         bossScene,
         boss},
        {DialogueBeatType::Narration, DialogueChoiceKind::None, QStringLiteral("小魔女：「谢了。我们走吧。」"), bossScene, witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「花神庙碑……原来真在那种地方。」"),
         bossScene,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("郭神：（擦杯子）「在行者酒馆，记性比酒量更值钱。」"),
         bossScene,
         boss},
    };
}

inline QVector<DialogueBeat> tavernPartingEndingBeats(const QString &playerLine)
{
    const QString bossScene = tavernBossBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString stranger = barStrangerPortraitFile();

    return {
        {DialogueBeatType::Narration, DialogueChoiceKind::None, playerLine, tavernTravelerBackgroundFile(), {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("旅人：（把银币收回袖中）「无凭无据，便无需再谈。后会有期。」"),
         tavernTravelerBackgroundFile(),
         stranger},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「走吧。园子里还有别处值得看看。」"),
         bossScene,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("郭神：（擦杯子）「在行者酒馆，最好奇的人，通常活不过第二杯。」"),
         bossScene,
         barPublicanPortraitFile()},
    };
}

inline QVector<DialogueBeat> arenaLeaveBeats()
{
    const QString bgEnter = arenaEntranceBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「走吧。等 85 决斗的 DDL 一过，角斗场就不会再这么热闹了。」"),
         bgEnter,
         witch},
    };
}

inline QVector<DialogueBeat> arcaneTowerClimbBeats()
{
    const QString bgIn = arcaneTowerInteriorBackgroundFile();
    const QString bgOn = arcaneTowerSummitBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（你推门进去。门轴响了一下，又很快归于安静。）"), bgIn),
        narrationBeat(QStringLiteral("（楼道昏暗，台阶一层一层向上。"
                                     "墙上有褪色的符文，像被时间磨钝了。）"),
                      bgIn),
        narrationBeat(QStringLiteral("（越往上走，下面的风越低，塔顶的光却越亮——"
                                     "像有什么在尽头等你。）"),
                      bgIn),
        narrationBeat(QStringLiteral("（你推开塔顶的小门。）"), bgOn),
        narrationBeat(QStringLiteral("（整个燕园在眼下铺开：禁书收藏馆、镜湖、湖心岛……"
                                     "你在心里重新画了一遍路线。）"),
                      bgOn),
        narrationBeat(QStringLiteral("（塔顶的灯就在头顶。它不照你，只是亮着，"
                                     "像整座园子的刻度。）"),
                      bgOn),
        narrationBeat(QStringLiteral("小魔女：「据说这园子的建造者早年也常爱在这塔顶俯瞰这院子。」"),
                      bgOn,
                      witch),
        narrationBeat(QStringLiteral("（你在这驻足许久，夕阳在你的视线中缓缓暗去。）"), bgOn),
        narrationBeat(QStringLiteral("小魔女：「时候不早啦，可别在这塔上待到太晚。」"), bgOn, witch),
        narrationBeat(QStringLiteral("（你转身下楼，离开了奥术尖塔。）"), bgIn),
    };
}

inline QVector<DialogueBeat> arcaneTowerLeaveBeats()
{
    const QString bgDoor = arcaneTowerDoorBackgroundFile();
    const QString bgApproach = arcaneTowerApproachBackground2File();
    const QString bgLeave = arcaneTowerLeaveBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（你把半掩的门轻轻合上，像把打扰挡在外面。）"), bgDoor),
        narrationBeat(QStringLiteral("（你转身，沿来路走出一段。）"), bgApproach),
        narrationBeat(QStringLiteral("（再回头时，奥术尖塔仍立在那里。"
                                     "塔顶的灯未熄，像从未被谁惊动过。）"),
                      bgLeave),
    };
}

inline QVector<DialogueBeat> arcaneTowerMainDialogueBeats()
{
    const QString bg1 = arcaneTowerApproachBackground1File();
    const QString bg2 = arcaneTowerApproachBackground2File();
    const QString bgDoor = arcaneTowerDoorBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（远道上，奥术尖塔先行一步立在天空下。"
                                     "塔顶的灯昼夜不熄，像一枚钉在园子上空的旧光点。）"),
                      bg1),
        narrationBeat(QStringLiteral("小魔女：「博雅塔。在园子里迷路了，抬头找它就行。」"), bg1, witch),
        narrationBeat(QStringLiteral("（你们沿塔基绕行。越走近，塔身越高，"
                                     "砖缝里长着颜色很深的小花，仿佛从石头里长出来。）"),
                      bg2),
        narrationBeat(QStringLiteral("（风在塔身上折了一下，又散开。"
                                     "塔影落在地面，指向与太阳无关的方向。）"),
                      bg2),
        narrationBeat(QStringLiteral("（塔门半掩。门缝里漏出一线昏暗的光，却听不见脚步声。）"), bgDoor),
        narrationBeat(QStringLiteral("（风里带来砖石和旧灯油的气味。）"), bgDoor),
        narrationBeat(QStringLiteral("（你敲了敲门。）"), bgDoor),
        narrationBeat(QStringLiteral("（没有人应答。塔里只有很轻的回声，很快又散了。）"), bgDoor),
        binaryChoiceBeat(DialogueChoiceKind::ArcaneTowerEnterOrLeave,
                         bgDoor,
                         QStringLiteral("推门上塔"),
                         QStringLiteral("转身离去，不打扰")),
    };
}

inline QVector<DialogueBeat> arenaMainDialogueBeats()
{
    const QString bgEnter = arenaEntranceBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「听——角斗场这几天是全园最热闹的地方。85 决斗的 DDL 就快到了，等最后一战落定，沙地上很难再见到这般盛况。」"),
         bgEnter,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「入口的热浪里全是喊杀声……沙地上是几十号人同时在打？」"),
         bgEnter,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「正是大乱斗。85 决斗的最后一战，人人各自为战，谁也休想结盟。你要下场，还是先在看台边把规矩看懂？」"),
         bgEnter,
         witch},
        binaryChoiceBeat(DialogueChoiceKind::ArenaJoinBattle,
                         bgEnter,
                         QStringLiteral("下场参战"),
                         QStringLiteral("留在场边观看")),
    };
}

inline QVector<DialogueBeat> arenaJoinTrainingBeats()
{
    const QString bgSpectator = arenaSpectatorBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「等等。角斗场的战士可不是靠一时热血就能站稳的——参战之前，得有强力的训练。」"),
         bgSpectator,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「你今天有去五四操场跑步，或者认真运动过吗？」"),
         bgSpectator,
         witch},
        binaryChoiceBeat(DialogueChoiceKind::ArenaExerciseToday,
                         bgSpectator,
                         QStringLiteral("有，今天去过五四操场"),
                         QStringLiteral("还没有")),
    };
}

inline QVector<DialogueBeat> arenaVictoryBeats()
{
    const QString bgBattle = arenaBattleBackgroundFile();
    const QString bgSpectator = arenaSpectatorBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString manager = abattoirManagerPortraitFile();

    QVector<DialogueBeat> beats = {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：（深吸一口气，跃入混战的人群）"),
         bgBattle,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（号角、铁器与叫喊叠成一片。数十名战士各自为战，你借着在五四操场练出来的耐力，一次次从包围里撕开缺口。）"),
         bgBattle,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("监管者：（铁链拖地，扫视全场）「今日胜者，可持角斗士令牌离场。」"),
         bgBattle,
         manager},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：（接住抛来的角斗士令牌）「还真给啊。」"),
         bgBattle,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「看吧。身体先到场，故事才会给你让路。」"),
         bgSpectator,
         witch},
    };
    beats.append(arenaLeaveBeats());
    return beats;
}

inline QVector<DialogueBeat> arenaSpectatorBeats()
{
    const QString bgSpectator = arenaSpectatorBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString audience1 = abattoirAudience1PortraitFile();
    const QString audience2 = abattoirAudience2PortraitFile();
    const QString warrior = abattoirWarriorPortraitFile();
    const QString manager = abattoirManagerPortraitFile();

    QVector<DialogueBeat> beats = {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("观众甲：（压低声）「别靠太近。85 决斗的规矩——只许各自为战。」"),
         bgSpectator,
         audience1},
        dualPortraitBeat(
            QStringLiteral("观众乙：「要是有人想联手，场边的魔兽监管者会立刻把人拖走。」"),
            bgSpectator,
            audience2,
            warrior),
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「这里从不奖励配合。两个人并肩，在这里反而像犯规。」"),
         bgSpectator,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("监管者：（披着铁链，沿看台巡过）「各自为战。谁敢抱团，就拖出去。」"),
         bgSpectator,
         manager},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：（望着沙地上扭打的人群，轻声）「……有时候我也觉得，这些战士挺不容易的。明明可以一起把事做完，却必须互相为敌。」"),
         bgSpectator,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「那我们呢？」"),
         bgSpectator,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「我们先看完这一战。该动身的时候，再去五四操场也不迟。」"),
         bgSpectator,
         witch},
    };
    beats.append(arenaLeaveBeats());
    return beats;
}

inline QVector<DialogueBeat> theaterMuralTalkBeats()
{
    const QString bgTalk = theaterMuralTalkBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString assistance = theaterAssistancePortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「术士把同一道咒画了两遍——一遍留学院，一遍扔进别的时间。」"),
         bgTalk,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「我们这幅夜里会自己亮。另一幅只在起雾时能看见——"
                         "那一界叫它《踏秋图》，星轨是反的。」"),
         bgTalk,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（脚步声敲地，墙上的色块轻轻荡，玻璃里的影子慢半拍才跟上。）"),
         bgTalk,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「改词改灯都没用。得让两幅画认回同一个执笔人，雾才散。」"),
         bgTalk,
         assistance},
    };
}

inline QVector<DialogueBeat> theaterMuralViewBeats()
{
    const QString bgPaint = theaterMuralSleepingBackgroundFile();
    const QString assistance = theaterAssistancePortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（近旭日厅，整面墙都是画。色块像有呼吸，衣角好像刚动过。）"),
         bgPaint,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「作者都找不到，怎么认？」"),
         bgPaint,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「本界没了，那一界往往还留着。」"),
         bgPaint,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「另一时空里，《踏秋图》的作者是？」"),
         bgPaint,
         assistance},
        {DialogueBeatType::TheaterMuralDecision,
         DialogueChoiceKind::TheaterMuralAuthor,
         {},
         bgPaint,
         {}},
    };
}

inline QVector<DialogueBeat> theaterMainDialogueBeats()
{
    const QString bgArrival = theaterArrivalBackgroundFile();
    const QString bgStaff = theaterStaffBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString assistance = theaterAssistancePortraitFile();

    return {
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「这几夜剧场不太对劲——不是演员的问题，是楼在醒。」"),
         bgArrival,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（门缝里漏出追光，台词卡在一半。海报上《星坠燕园》的「延期」被划了又写。）"),
         bgArrival,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：（挤出门缝）「今晚没票，只有彩排。再往里，导演要骂人的。」"),
         bgStaff,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：（低声）「外廊也少站。两幅画没对齐时，那儿不清净。」"),
         bgStaff,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「两幅画？」"),
         bgStaff,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「另一幅在别的时空，名叫《踏秋图》。笔意一样，各睡各的。」"),
         bgStaff,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（里面有人念到「双星坠落」，外廊的灯暗了一瞬，又亮回来。）"),
         bgStaff,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「这出禁演本，为什么非在这排？」"),
         bgStaff,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「导演说戏是写给这栋楼听的。可楼心里还挂着另一幅没睡着的画。」"),
         bgStaff,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("你：「谁画的？」"),
         bgStaff,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：（摇头）「说不清。说是上古术士，封完笔就消失了。档案里也只写『墙上有画』。」"),
         bgStaff,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「这一界的作者，早就找不到了。」"),
         bgStaff,
         assistance},
        binaryChoiceBeat(DialogueChoiceKind::TheaterViewMural,
                         bgStaff,
                         QStringLiteral("先去看石壁上的画"),
                         QStringLiteral("等雾起，看玻璃里的那一幅")),
    };
}

inline QVector<DialogueBeat> theaterAlignedEndingBeats(const QString &playerAnswerLine)
{
    const QString bgPaint = theaterMuralSleepingBackgroundFile();
    const QString bgAwaken = theaterMuralAwakenBackgroundFile();
    const QString bgStaff = theaterStaffBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString assistance = theaterAssistancePortraitFile();

    return {
        {DialogueBeatType::Narration, DialogueChoiceKind::None, playerAnswerLine, bgPaint, {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（两道光弧轻轻一碰。墙上的符纹沉下去，玻璃里的重影扣合上。雾散了。里面有人喊：「灯稳了，继续！」）"),
         bgAwaken,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「……《踏秋图》对上了。」"),
         bgAwaken,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「走吧，别在玻璃边站太久。」"),
         bgStaff,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「认对人就行。墙会睡的。」"),
         bgStaff,
         assistance},
    };
}

inline QVector<DialogueBeat> theaterPendingEndingBeats(const QString &playerLine)
{
    const QString bgPaint = theaterMuralSleepingBackgroundFile();
    const QString bgStaff = theaterStaffBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString assistance = theaterAssistancePortraitFile();

    return {
        {DialogueBeatType::Narration, DialogueChoiceKind::None, playerLine, bgPaint, {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「不急。这类事，得亲眼看过才算数。」"),
         bgPaint,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「《踏秋图》的画师，在咱们这一界仍能在墙边被找到。改天去百讲看看，想好了再来。」"),
         bgPaint,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「墙会等的。园子里还有别处值得逛。」"),
         bgStaff,
         assistance},
    };
}

inline QVector<DialogueBeat> theaterWrongAnswerEndingBeats(const QString &playerLine)
{
    const QString bgPaint = theaterMuralSleepingBackgroundFile();
    const QString bgStaff = theaterStaffBackgroundFile();
    const QString witch = witchPortraitFile();
    const QString assistance = theaterAssistancePortraitFile();

    return {
        {DialogueBeatType::Narration, DialogueChoiceKind::None, playerLine, bgPaint, {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("（壁画静着，雾也还在。）"),
         bgPaint,
         {}},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「墙没应……看来还得再找找。」"),
         bgPaint,
         assistance},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("小魔女：「《踏秋图》的画师，在咱们这一界仍能在墙边被找到。改天去百讲看看，想好了再来。」"),
         bgPaint,
         witch},
        {DialogueBeatType::Narration,
         DialogueChoiceKind::None,
         QStringLiteral("CM.J：「不急。认对了，它自然会醒。」"),
         bgStaff,
         assistance},
    };
}

inline int parseMirrorLakeTowerAnswer(const QString &userInput)
{
    const QString trimmed = userInput.trimmed();
    if (trimmed == QStringLiteral("13") || trimmed == QStringLiteral("十三")) {
        return 13;
    }
    if (trimmed == QStringLiteral("26") || trimmed == QStringLiteral("二十六")) {
        return 26;
    }
    return 0;
}

inline bool checkMirrorLakeTowerAnswer(const QString &userInput)
{
    return parseMirrorLakeTowerAnswer(userInput) != 0;
}

inline QString luIslandLeaveChoiceText()
{
    return QStringLiteral("与这个世界道别");
}

inline QString luIslandStayChoiceText()
{
    return QStringLiteral("留在这个世界");
}

inline QString luIslandBridgeStayChoiceText()
{
    return QStringLiteral("我想留在这里");
}

inline QVector<DialogueBeat> luIslandReturnTransitionBeats()
{
    const QString bg = islandBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（你朝那扇门走去。门缝里漏出熟悉的光——不是魔法，是日常。）"), bg),
        narrationBeat(QStringLiteral("（身后，湖心岛安静得像从未存在过；你也没有再回头。）"), bg),
    };
}

inline QVector<DialogueBeat> luIslandStayTransitionBeats()
{
    const QString bg = islandBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（你在岛边坐下，把脚伸进水里。水是凉的，是真实的。）"), bg),
        narrationBeat(QStringLiteral("（对岸的灯一盏一盏亮起来。你决定，先留在这个世界里。）"), bg),
    };
}

inline QVector<DialogueBeat> luIslandBridgeStayPersuasionBeats()
{
    const QString bg = islandBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("你：「%1」").arg(luIslandBridgeStayChoiceText()), bg),
        narrationBeat(QStringLiteral("（老校长沉默片刻，目光仍旧温和。）"), bg),
        narrationBeat(QStringLiteral("老校长：「……你不属于这个世界。」"), bg),
        narrationBeat(QStringLiteral("老校长：「不是责备。这一趟对你已经够了，"
                                     "可这片园子若要留人，需要你在对岸那些稀松平常的日子里也有根。」"),
                      bg),
        narrationBeat(QStringLiteral("老校长：「回去吧。那才是现在真正属于你的生活。」"), bg),
        narrationBeat(QStringLiteral("小魔女：「……听他的。」"), bg, witch),
        narrationBeat(QStringLiteral("（你忽然明白：木桥、这扇门，原只为送别而备。）"), bg),
        binaryChoiceBeat(DialogueChoiceKind::LuIslandReturnOnly,
                         bg,
                         luIslandLeaveChoiceText(),
                         {}),
    };
}

inline QVector<DialogueBeat> luIslandBridgePathDialogueBeats()
{
    const QString bg = islandBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（你沿镜湖上架起的木桥，走上湖心岛。桥板很旧，却意外地稳。）"), bg),
        narrationBeat(QStringLiteral(
                          "（岛上立着一块石碑，和旧日之境的花神庙碑遥遥呼应，但这块更古老，刻满了你认不出的字。）"),
                      bg),
        narrationBeat(QStringLiteral("（石碑旁，一位老人正等着。白发整齐，目光温厚，像许多年前在走廊里与你擦肩的那位师长。）"),
                      bg),
        narrationBeat(QStringLiteral("老校长：「孩子，你来得巧，也来得正好。」"), bg),
        narrationBeat(QStringLiteral("老校长：「这一趟，该看的、该问的，你都走过了。"
                                     "对岸还有课表、还有没写完的代码——那才是你现在该回去的地方。」"),
                      bg),
        narrationBeat(QStringLiteral("老校长：「门在那边。走进去，便是你来的那个下午。」"), bg),
        narrationBeat(QStringLiteral("小魔女：（轻声）「……走或留，你自己定。」"), bg, witch),
        narrationBeat(QStringLiteral("（岛上只有一扇门，通往来时的方向——那个下午，那些照旧的日子。）"), bg),
        binaryChoiceBeat(DialogueChoiceKind::LuIslandFinalChoice,
                         bg,
                         luIslandLeaveChoiceText(),
                         luIslandBridgeStayChoiceText()),
    };
}

inline QVector<DialogueBeat> luIslandStoneBoatPathDialogueBeats()
{
    const QString bg = islandBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（无风的夜里，石舫载着你穿过镜湖。舷边几乎不起涟漪，"
                                     "舷栏的光仍沿着纹路缓缓流动。）"),
                      mirrorLakeBoatAwakenedBackgroundFile()),
        narrationBeat(QStringLiteral("（石舫靠岸。你踏上湖心岛，像踏进另一重安静的天。）"), bg),
        narrationBeat(QStringLiteral("小魔女：「你把该去的地方都去了，该见的人都见了。燕园的封印松了一扣。」"),
                      bg,
                      witch),
        narrationBeat(QStringLiteral(
                          "（岛上立着一块石碑，和旧日之境的花神庙碑遥遥呼应，但这块更古老，刻满了你认不出的字。）"),
                      bg),
        narrationBeat(QStringLiteral("（石碑旁，一位老人缓缓走来。）"), bg),
        narrationBeat(QStringLiteral("老校长：「石舫肯载你来，说明你和这园子有缘。」"), bg),
        narrationBeat(QStringLiteral("老校长：「若你愿意，可以留下——这园子里，确实还有值得你多看一眼的灯火。」"),
                      bg),
        narrationBeat(QStringLiteral("老校长：「当然，门也在那边。走进去，便是你来的那个下午；"
                                     "不走进去，便留在这园子里。」"),
                      bg),
        narrationBeat(QStringLiteral("小魔女：（轻声）「……走或不走，你自己定。」"), bg, witch),
        narrationBeat(QStringLiteral("（岛上只有一扇门，通往来时的方向——那个下午，那些照旧的日子。）"), bg),
        binaryChoiceBeat(DialogueChoiceKind::LuIslandFinalChoice,
                         bg,
                         luIslandLeaveChoiceText(),
                         luIslandStayChoiceText()),
    };
}

inline QVector<DialogueBeat> luIslandMainDialogueBeats()
{
    if (mirrorLakePath() == MirrorLakePath::StoneBoat) {
        return luIslandStoneBoatPathDialogueBeats();
    }
    return luIslandBridgePathDialogueBeats();
}

inline QVector<DialogueBeat> mirrorLakeWrongAnswerBeats(const QString &answer)
{
    const QString bg = mirrorLakeBoatBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("你：「%1。」").arg(answer), bg),
        narrationBeat(QStringLiteral("（风仍未起。你等的回应——桥的延伸、石舫的震颤——都没有来。）"), bg),
        narrationBeat(QStringLiteral("（镜湖平静得像从未被询问过。无风之夜的魔法没有生效。）"), bg),
        narrationBeat(QStringLiteral("小魔女：「……今晚大概不是它开声的时候。改天无风，再来吧。」"), bg, witch),
    };
}

inline QVector<DialogueBeat> mirrorLakeTowerAnswerBeats(int towerCount)
{
    const QString bg = mirrorLakeBoatBackgroundFile();
    const QString witch = witchPortraitFile();

    if (towerCount == 26) {
        const QString lakeBoat = mirrorLakeBoatBackgroundFile();
        const QString lakeAwakened = mirrorLakeBoatAwakenedBackgroundFile();

        return {
            narrationBeat(QStringLiteral("你：「二十六。」"), lakeBoat),
            narrationBeat(QStringLiteral("（小魔女没有立刻接话。风仍未起，湖面平整如故——"
                                         "你的数字落进湖里，像一枚石子，却没有立刻激起该有的回应。）"),
                          lakeBoat),
            narrationBeat(QStringLiteral("（沉寂了一瞬。随后，石舫轻轻一震。）"), lakeBoat),
            narrationBeat(QStringLiteral("（舷边的石栏里，有光顺着纹路醒来，一圈一圈地亮，"
                                         "像有人把眠于砖缝里的咒语重新念完。青苔退向暗处，"
                                         "旧砖的颜色深下去，又浅回来。）"),
                          lakeAwakened),
            narrationBeat(QStringLiteral("（整艘石舫在无声中调整了重量——不是浮，也不是沉，"
                                         "而是承认了你站在上面的这件事。"
                                         "舷外，湖水贴过来，像为载具让路。）"),
                          lakeAwakened),
            narrationBeat(QStringLiteral("（镜湖的魔法终于醒了。无风之夜里，它只认这一道应答。）"),
                          lakeAwakened),
            narrationBeat(QStringLiteral("小魔女：「这才是石舫该做的事——载认准湖的人，去对岸。」"),
                          lakeAwakened,
                          witch),
        };
    }

    return {
        narrationBeat(QStringLiteral("你：「十三。」"), bg),
        narrationBeat(QStringLiteral("（小魔女看了你一眼，点点头，便不再多问。）"), bg, witch),
        narrationBeat(QStringLiteral("（湖心方向，有什么东西轻轻响了一下——像木头的叹息。）"), bg),
        narrationBeat(QStringLiteral("（一道木桥从雾里伸出来，横在湖上，只通向对岸。）"), bg),
        narrationBeat(QStringLiteral("小魔女：「桥够了。以后要去对岸，走这道就行。」"), bg, witch),
        narrationBeat(QStringLiteral("（石舫仍旧沉寂。风没有起，湖也没有再多说一句话。）"), bg),
    };
}

inline QVector<DialogueBeat> mirrorLakeDeferBeats()
{
    const QString bg = mirrorLakeBoatBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("小魔女：「不急。等你亲眼所见之后，再来吧。」"), bg, witch),
    };
}

inline QVector<DialogueBeat> mirrorLakeMainDialogueBeats()
{
    const QString lakeShore = mirrorLakeShoreBackgroundFile();
    const QString lakeBoat = mirrorLakeBoatBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（镜湖入夜。岸灯一盏一盏亮起来，风停了，湖面出奇地静。）"), lakeShore),
        narrationBeat(QStringLiteral("（水面平整，几乎听不见波纹——安静得像一面镜子。"
                                     "这或许也是它名字的由来。）"),
                      lakeShore),
        narrationBeat(QStringLiteral("小魔女：「园里有个说法：风大的时候别来镜湖，湖会碎。"
                                     "要等一个风平浪静的晚上。」"),
                      lakeShore,
                      witch),
        narrationBeat(QStringLiteral("（远处，奥术尖塔的灯在塔顶亮着。）"), lakeShore),
        narrationBeat(QStringLiteral("小魔女：「走，上石舫。要去湖心岛，这里是必经之处。」"), lakeBoat, witch),
        narrationBeat(QStringLiteral("小魔女：「把你亲眼所见的塔层数告诉我——数对了，才能唤醒镜湖的魔法。」"),
                      lakeBoat,
                      witch),
        narrationBeat(QStringLiteral("（石舫的砖很旧，边沿的青苔仿佛诉说着光阴的故事。"
                                     "你扶住舷边的石栏，望向尖塔。）"),
                      lakeBoat),
        narrationBeat(QStringLiteral("小魔女：「从这儿，你一共能看见多少层塔？」"), lakeBoat, witch),
        {DialogueBeatType::MirrorLakeTowerDecision,
         DialogueChoiceKind::MirrorLakeTowerCount,
         {},
         lakeBoat,
         {},
         {},
         {}},
    };
}

inline QVector<DialogueBeat> luIslandShoreViewBeats()
{
    const QString bg = mirrorLakeShoreBackgroundFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（你在镜湖岸边停下。湖心岛在不远的水面上，像一枚从未靠岸的月。）"), bg),
        narrationBeat(QStringLiteral("（岛上有影，有树，却看不见码头，也看不见桥。）"), bg),
        narrationBeat(QStringLiteral("（风依然停了。湖面的魔法像一堵透明的墙——"
                                     "你知道它在那儿，却不知道怎么穿过去。）"),
                      bg),
        narrationBeat(QStringLiteral("小魔女：「别急着往水里走。镜湖的通行，得等它在无风夜开声。」"), bg, witch),
        narrationBeat(QStringLiteral("（你望了很久。岛仍在水中央，安静，神秘，像永远只供眺望。）"), bg),
    };
}

inline QVector<DialogueBeat> luIslandExploreMoreBeats()
{
    const QString bg = islandBackgroundFile();
    const QString lakeBg = mirrorLakeShoreBackgroundFile();
    const QString witch = witchPortraitFile();
    QVector<DialogueBeat> beats;

    if (mirrorLakePath() == MirrorLakePath::StoneBoat) {
        beats.append(narrationBeat(QStringLiteral("（石舫载你们渡过镜湖。无风夜里，舷边的光一路铺开，"
                                                  "像有人提前点好了路。）"),
                                   mirrorLakeBoatAwakenedBackgroundFile()));
    } else {
        beats.append(narrationBeat(QStringLiteral("（你沿木桥走上湖心岛。桥板在脚下发出很轻的叹息。）"),
                                   lakeBg));
    }

    beats.append({
        narrationBeat(QStringLiteral("（岛心不比远处看起来更宽。石碑立在老树旁，一位老人正朝你走来。）"), bg),
        narrationBeat(QStringLiteral("老校长：「孩子，你找对了路。」"), bg),
        narrationBeat(QStringLiteral("老校长：「可湖心岛是整座燕园的终点——不是半路歇息的地方。」"), bg),
        narrationBeat(QStringLiteral("老校长：「别处还有你没走完的门、没听完的故事。"
                                     "先把那些路走完，再来见我。」"),
                      bg),
        narrationBeat(QStringLiteral("小魔女：「……他说得对。我们回去吧。」"), bg, witch),
        narrationBeat(QStringLiteral("（你们沿来时的路退回岸边。岛在身后重新变远，像一枚始终未落的月。）"), lakeBg),
    });
    return beats;
}

inline QVector<DialogueBeat> luIslandDialogueBeatsForMode(LuIslandVisitMode mode)
{
    switch (mode) {
    case LuIslandVisitMode::ShoreView:
        return luIslandShoreViewBeats();
    case LuIslandVisitMode::ExploreMore:
        return luIslandExploreMoreBeats();
    case LuIslandVisitMode::Finale:
        return luIslandMainDialogueBeats();
    }
    return luIslandShoreViewBeats();
}

inline QVector<DialogueBeat> spellHallCommonEndingBeats()
{
    const QString witch = witchPortraitFile();
    const QString bg2 = classroomBackground2File();
    const QString bg3 = classroomBackground3File();

    return {
        narrationBeat(QStringLiteral("小魔女：「好啦好啦，再发呆下去下节课的学生要来了。」"),
                      bg2,
                      witch),
        narrationBeat(QStringLiteral("（她走向门口，在门槛停下来回头。）"), bg2),
        narrationBeat(QStringLiteral("小魔女：「看你这么迷迷糊糊的，要不要我带你出去看看？」"), bg2, witch),
        narrationBeat(QStringLiteral("（魔杖朝走廊的方向轻轻一点。）"), bg2),
        narrationBeat(QStringLiteral("（你走出了教室。）"), bg3),
        narrationBeat(QStringLiteral("小魔女：（故弄玄虚）「对啦，最近路过骑士像的时候注意一下，听说有人看见它动了。」"),
                      bg3,
                      witch),
    };
}

inline QVector<DialogueBeat> spellHallChoiceFollowUpBeats(int choiceIndex)
{
    const QString witch = witchPortraitFile();
    const QString bg2 = classroomBackground2File();
    QVector<DialogueBeat> followUp;

    if (choiceIndex == 0) {
        followUp = {
            narrationBeat(QStringLiteral("你：「……这里是哪里？」"), bg2),
            narrationBeat(QStringLiteral("（她眨了一下眼，挑起眉毛。）"), bg2),
            narrationBeat(QStringLiteral("小魔女：「魔咒学院四楼，魔咒设计实习的教室。」"), bg2, witch),
            narrationBeat(QStringLiteral("（顿了顿。）"), bg2),
            narrationBeat(QStringLiteral("小魔女：「你还没睡醒吗？」"), bg2, witch),
            narrationBeat(QStringLiteral("（她转过头，仔细看了看你，若有所思。）"), bg2),
        };
    } else if (choiceIndex == 1) {
        followUp = {
            narrationBeat(QStringLiteral("你：「你是同学吗？」"), bg2),
            narrationBeat(QStringLiteral("「啪」，魔杖落到你的脑门。"), bg2),
            narrationBeat(QStringLiteral("小魔女：（气鼓鼓）「同学？」"), bg2, witch),
            narrationBeat(QStringLiteral("小魔女：「我是这门课的老师！要不是看在你是我学生的情面上，"
                                        "后面一个月你就捂着新长的蜥蜴尾巴走路吧！」"),
                          bg2,
                          witch),
            narrationBeat(QStringLiteral("（见你愣住，她叹了口气，转身整理桌上的东西。）"), bg2),
            narrationBeat(QStringLiteral("小魔女：「年龄是给那些数着日子过活的人准备的，我可不数日子。」"),
                          bg2,
                          witch),
        };
    } else {
        followUp = {
            narrationBeat(QStringLiteral("（你不说话，看向窗外。）"), bg2),
            narrationBeat(QStringLiteral("窗外是校园。也不完全是。"), bg2),
            narrationBeat(QStringLiteral("树还在，小路还在，远处的屋檐还在——但屋檐上停着一只你叫不出名字的鸟，"
                                        "尾羽像日落后的天空，泛着蓝紫色的光芒。"),
                          bg2),
            narrationBeat(QStringLiteral("有人叼着面包，扶着帽子，骑着扫帚从天空一闪而过，"
                                        "让你想起了赶早八的日子。"),
                          bg2),
            narrationBeat(QStringLiteral("石板路上，一只橙色的小火蜥蜴慢悠悠爬过，背上暖橙色的火苗跃动着。"),
                          bg2),
            narrationBeat(QStringLiteral("（小魔女顺着你的视线望了一眼，沉默了片刻。）"), bg2, witch),
        };
    }

    followUp.append(spellHallCommonEndingBeats());
    return followUp;
}

inline QVector<DialogueBeat> spellHallMainDialogueBeats()
{
    const QString witch = witchPortraitFile();
    const QString bg1 = classroomBackground1File();
    const QString bg2 = classroomBackground2File();

    return {
        narrationBeat(QStringLiteral("下午的教室，阳光从窗外倾泻进来，流淌在课桌上。屏幕亮着，上面是一段未完成的代码。"
                                     "周围同学的键盘声、翻书声渐渐远去，晕成一片白噪音。"),
                      bg1),
        narrationBeat(QStringLiteral("PPT 投影上的字开始变得模糊——不是困意所致，是某种更奇怪的东西。"
                                     "那是……符文？还是一直就是这样写的？"),
                      bg1),
        narrationBeat(QStringLiteral("视线落入一片黑暗。"), bg1),
        narrationBeat(QStringLiteral("黑暗里有个声音，不近，也不远，像是从很久以前传来的："), bg1),
        narrationBeat(QStringLiteral("「——你上次，认真看过这里，是什么时候？」"), bg1),
        narrationBeat(QStringLiteral("没有回答的时间，光线重新涌进来。"), bg1),
        narrationBeat(QStringLiteral("某种细细的东西戳了戳你的肩膀。"), bg1),
        narrationBeat(QStringLiteral("小魔女：「喂。」"), bg2, witch),
        narrationBeat(QStringLiteral("（又戳了一下。）"), bg2),
        narrationBeat(QStringLiteral("小魔女：「魔咒设计实习已经结束啦！怎么还睡呀。」"), bg2, witch),
        narrationBeat(QStringLiteral("你抬起头。站在旁边的是一个看起来和你差不多年纪的人，穿着有点奇怪——"
                                     "像是把学院制服和博物馆橱窗里的长袍拼贴在一起，袖口绣着细小的符文。"
                                     "她手里拿着一根泛着淡蓝色微光的魔杖，正用它指着你。"),
                      bg2),
        multiChoiceBeat(DialogueChoiceKind::SpellHallPrologueChoice,
                        bg2,
                        QStringLiteral("「……这里是哪里？」"),
                        QStringLiteral("「你是同学吗？」"),
                        QStringLiteral("（不说话，看向窗外）")),
    };
}

inline QVector<QString> luIslandReturnEndingBeats()
{
    return {
        QStringLiteral("「世界始终如此，你今日方至。」"),
        QStringLiteral("湖心岛上的门打开的那一刻，你看见的不是别处——\n"
                       "是教室的走廊，是下午四点的光线，是你来时走过的那条路。"),
        QStringLiteral("你走进去。"),
        QStringLiteral("— — —"),
        QStringLiteral("（然后你醒了。）"),
        QStringLiteral("教室里，同学们已经散了大半。\n"
                       "投影还亮着，最后一行咒文——不，是代码——停在那里。"),
        QStringLiteral("你坐了一会儿，没有立刻走。"),
        QStringLiteral("窗外，有人骑着自行车从树荫下穿过。\n"
                       "树叶的影子落在他身上，一片一片的，很好看。"),
        QStringLiteral("你不知道自己在等什么，但就这么看了一会儿。"),
        QStringLiteral("然后你拎起包，走出去了。\n\n"
                       "走廊里有阳光，从窗缝里斜切进来，\n"
                       "落在地板上，是一条细细的金线。"),
        QStringLiteral("你绕开它走了一步，然后停下来，\n"
                       "退回去，踩上去。"),
        QStringLiteral("没什么特别的。\n\n就是觉得，可以踩一下。"),
    };
}

inline QVector<QString> luIslandStayEndingBeats()
{
    return {
        QStringLiteral("你没有走进那扇门。"),
        QStringLiteral("湖面很平静。远处的岸边，灯火一盏一盏亮起来。\n"
                       "你坐在岛边，把脚伸进水里。水是凉的，是真实的。"),
        QStringLiteral("（老校长不知道什么时候站到了你旁边。\n他没有说话。）"),
        QStringLiteral("很久之后，他开口：\n\n「留下来的人，我见过不少。」"),
        QStringLiteral("你问：「后来呢？」\n\n他想了想：「后来他们都很好。」"),
        QStringLiteral("又沉默了一会儿。\n\n「只是会慢慢忘记，对岸的灯，是什么颜色的。」"),
        QStringLiteral("（他走了。）"),
        QStringLiteral("（湖面上，对岸的灯还亮着。\n你看了很久，想把那个颜色记住。）"),
        QStringLiteral("（后来，你想不起来了。）"),
    };
}

inline QVector<DialogueBeat> oldRealmMainDialogueBeats()
{
    const QString witch = witchPortraitFile();
    const QString bgEntry = oldRealmGardenEntryFile();
    const QString bgPath = oldRealmGardenPathFile();
    const QString bgDepth = oldRealmGardenDepthFile();
    const QString bgExterior = oldRealmCottageExteriorFile();
    const QString bgSign = oldRealmShopSignFile();

    return {
        narrationBeat(QStringLiteral("（踏进旧日之境，外面的喧声像被树冠滤掉了。）"), bgEntry),
        narrationBeat(QStringLiteral("（天光薄，风也慢。小径向绿深处弯去，石阶缝里生着苔。）"), bgEntry),
        narrationBeat(QStringLiteral("小魔女：「燕南园的老路，都收在这里。」"), bgEntry, witch),
        narrationBeat(QStringLiteral("小魔女：「慢点走。树影里凉。」"), bgEntry, witch),

        narrationBeat(QStringLiteral("（你沿小径往里。两侧是深院：门扉漆色沉旧，檐下石阶仍见扫帚痕。）"),
                      bgPath),
        narrationBeat(QStringLiteral("（一扇窗半掩着，帘子垂着不动，桌上像还留着未收的书签。）"), bgPath),
        narrationBeat(QStringLiteral("（院角一把空椅。椅面落了几片叶，叶缘被拂到一边——不久之前，这里还坐过人。）"),
                      bgPath),
        narrationBeat(QStringLiteral("（远处隐约传来讲堂方向的钟声，一响，风就把余音吹散在树里。）"), bgPath),
        narrationBeat(QStringLiteral("小魔女：「以前住在这里的人，有的写书，有的教书，有的只是在傍晚散步。」"),
                      bgPath,
                      witch),
        narrationBeat(QStringLiteral("小魔女：「墙上有字，有影，有半杯凉掉的茶。」"), bgPath, witch),

        narrationBeat(QStringLiteral("（小径分岔。你选较窄的一条，两侧竹影压得更低，脚步也轻了。）"), bgDepth),
        narrationBeat(QStringLiteral("（墙根下立着一块小牌，字已磨平，只剩「……园」的半个轮廓。）"), bgDepth),
        narrationBeat(QStringLiteral("（再往前，旧日信箱、晾绳、花盆仍放在原处，院里没有人声。）"), bgDepth),
        narrationBeat(QStringLiteral("（午后的光停在回廊角，迟迟不挪动。）"), bgDepth),
        narrationBeat(QStringLiteral("（你忽然想起现实里某个类似的午后：书库闭馆前，有人抱着一摞书从这条方向慢慢走过。）"),
                      bgDepth),
        narrationBeat(QStringLiteral("（那画面一闪即逝。路在竹影下折向更深处，苔色一层比一层浅。）"), bgDepth),

        narrationBeat(QStringLiteral("（小径尽头，绿让出一块空。风里夹着一丝热气和油耗气，从树丛那边飘过来。）"),
                      bgDepth),
        narrationBeat(QStringLiteral("小魔女：（停步）「……你闻到了吗？」"), bgDepth, witch),
        narrationBeat(QStringLiteral("（你顺着那缕若有若无的香，才看见绿里嵌着的一间小屋。）"), bgExterior),
        narrationBeat(QStringLiteral("（窗内暖灯，桌椅、碗碟挨齐。你绕到正面，四面墙平平的，没有门框。）"),
                      bgExterior),
        narrationBeat(QStringLiteral("小魔女：「听说燕南园深处，曾经有过一家店。」"), bgExterior, witch),
        narrationBeat(QStringLiteral("小魔女：「也有人说，饿极了的人，会在树影里闻到饭菜香。」"), bgExterior, witch),
        narrationBeat(QStringLiteral("（悬在檐下的木牌漆色剥落，只剩「燕」和「馆」两个字的轮廓，其余糊成一团。）"),
                      bgSign),
        narrationBeat(QStringLiteral("小魔女：「檐下那块牌，等着人去填那些糊掉的字。」"), bgSign, witch),
        narrationBeat(QStringLiteral("小魔女：「填上了，墙才会开门。」"), bgSign, witch),
        oldRealmShopNameDecisionBeat(bgSign),
    };
}

inline QVector<DialogueBeat> oldRealmWrongNameBeats()
{
    const QString bgSign = oldRealmShopSignFile();

    return {
        narrationBeat(QStringLiteral("（你在牌下写了几个字。墨色渗进木纹，又慢慢淡去，像从未落笔。）"), bgSign),
        narrationBeat(QStringLiteral("（小屋还是那样。没有门，也没有饭香。）"), bgSign),
    };
}

inline QVector<DialogueBeat> oldRealmDoorRevealBeats()
{
    const QString bgHouse = oldRealmCottageExteriorFile();
    const QString bgDoor = oldRealmShopDoorFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（你写下的字一笔一划贴上了木牌。模糊处被墨色填满。）"), bgHouse),
        narrationBeat(QStringLiteral("（同一面墙上，门框的线条一层层浮出来。）"), bgDoor),
        narrationBeat(QStringLiteral("小魔女：「……门在了。」"), bgDoor, witch),
    };
}

inline QVector<DialogueBeat> oldRealmShopMemoryBeats()
{
    const QString bgInterior = oldRealmShopInteriorFile();
    const QString bgDoor = oldRealmShopDoorFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("你：「推开门进去。」"), bgDoor),
        narrationBeat(QStringLiteral("（饭香扑面。厅里空着，两副碗筷，其中一副被推开了一半。）"),
                      bgInterior),
        narrationBeat(QStringLiteral("（你忽然想起某个下午：第四节课后端着餐盘找座位，一层满员，"
                                      "有人端着饭碗站在树影里，把最后一口扒完才回图书馆。）"),
                      bgInterior),
        narrationBeat(QStringLiteral("（又想起闭馆前最后十分钟，师傅在里头收灶，"
                                      "外头还有人扬声问「还有吗」，问完又在门边多站了一会儿。）"),
                      bgInterior),
        narrationBeat(QStringLiteral("（还有一条路：离书库很近，吃完回去继续占座，"
                                      "风从燕南园吹过来，带着刚出锅的热气。）"),
                      bgInterior),
        narrationBeat(QStringLiteral("小魔女：「……是这个味道。」"), bgInterior, witch),
        narrationBeat(QStringLiteral("（你退出来。门还在，招牌上的字比来时清楚了一点。）"), bgDoor),
        narrationBeat(QStringLiteral("（深院的树影重新合拢。饭香留在小屋里，像一段被单独收好的下午。）"),
                      oldRealmGardenPathFile()),
        narrationBeat(QStringLiteral("（旧日之境的风从背上吹过去。树影照旧，身后的屋里还留着一点饭香。）"),
                      oldRealmGardenEntryFile()),
    };
}

inline QVector<DialogueBeat> oldRealmDeclineEntryBeats()
{
    const QString bgDoor = oldRealmShopDoorFile();
    const QString bgPath = oldRealmGardenPathFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("你：「今天先离开。」"), bgDoor),
        narrationBeat(QStringLiteral("（你没有推门。门框仍在墙上，像等人改日再来。）"), bgDoor),
        narrationBeat(QStringLiteral("小魔女：「门在了。今日进不进，随你。」"), bgDoor, witch),
        narrationBeat(QStringLiteral("（你沿来路退回深院。饭香留在身后，树影重新合拢。）"), bgPath),
        narrationBeat(QStringLiteral("（风从燕南园深处吹出来，带着一点残余的热气。）"), bgPath),
    };
}

inline QVector<DialogueBeat> oldRealmSilentLeaveBeats()
{
    const QString bgSign = oldRealmShopSignFile();
    const QString bgPath = oldRealmGardenPathFile();
    const QString bgEntry = oldRealmGardenEntryFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("（你没有再写。招牌还是糊的，小屋还是无门。）"), bgSign),
        narrationBeat(QStringLiteral("（木牌下的地面干干净净，像很久没人在这里落笔。）"), bgSign),
        narrationBeat(QStringLiteral("（你转身离开。深院里，空椅、半掩的窗、磨平的小牌，一一退到身后。）"), bgPath),
        narrationBeat(QStringLiteral("小魔女：「走吧。园子会替你留着这块空牌。」"), bgPath, witch),
        narrationBeat(QStringLiteral("（旧日之境的入口在树影里合拢。复归安静。）"), bgEntry),
    };
}

inline QVector<DialogueBeat> forbiddenArchiveMainDialogueBeats()
{
    const QString witch = witchPortraitFile();
    const QString william = williamYangPortraitFile();
    const QString bgHall = libraryHallBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（禁书收藏馆里很静。空调送着冷风，混着旧纸和木架的味道。）"), bgHall),
        narrationBeat(QStringLiteral("小魔女：「进来轻点声。这里连脚步声都像会被书页记下来。」"), bgHall, witch),
        narrationBeat(QStringLiteral("（服务台后有人抬头。胸牌：William.Yang。）"), bgHall),
        narrationBeat(QStringLiteral("William.Yang：「第一次来？随便看看可以，禁书区不能外借。」"), bgHall, william),
        narrationBeat(QStringLiteral("William.Yang：「今天来做什么？」"), bgHall, william),
        binaryChoiceBeat(DialogueChoiceKind::ForbiddenArchiveVisitIntent,
                         bgHall,
                         QStringLiteral("想随便逛逛"),
                         QStringLiteral("有事请教")),
    };
}

inline QVector<DialogueBeat> forbiddenArchiveTourBeats()
{
    const QString witch = witchPortraitFile();
    const QString william = williamYangPortraitFile();
    const QString bgHistory = libraryHistoryCorridorBackgroundFile();
    const QString bgPhilosophy = libraryPhilosophyWingBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（展柜里是早期的借书牌、手抄目录，还有一张褪色的园子地图。）"), bgHistory),
        narrationBeat(QStringLiteral("William.Yang：「收藏馆最早只是咒术大楼的一间附室，"
                                     "后来书多了，哲学和神术原典挪到里面的古分馆。」"),
                      bgHistory,
                      william),
        narrationBeat(QStringLiteral("（展墙地图上，尖塔、镜湖、湖心岛各标着一个小藏书点。）"), bgHistory),
        narrationBeat(QStringLiteral("（说明牌字小，要凑近了才看得清。）"), bgHistory),
        narrationBeat(QStringLiteral("William.Yang：「园子里不少地方，都能在这里找到对应的卷宗。」"),
                      bgHistory,
                      william),
        narrationBeat(QStringLiteral("小魔女：「走慢点。这里的灯比外面暗。」"), bgHistory, witch),

        narrationBeat(QStringLiteral("（哲学图书馆 · 古分馆。砖墙更旧，壁灯一盏挨着一盏。）"), bgPhilosophy),
        narrationBeat(QStringLiteral("（排架之间很窄，铁扣古本一行一行摞上去，像沉默的墙。）"), bgPhilosophy),
        narrationBeat(QStringLiteral("William.Yang：「上古的书多半封在这里。年头一久，连管理员也只见得书名，"
                                     "不见得记得住架位。」"),
                      bgPhilosophy,
                      william),
        narrationBeat(QStringLiteral("William.Yang：「你听说过《原神之力》这本书吗？」"), bgPhilosophy, william),
        binaryChoiceBeat(DialogueChoiceKind::ForbiddenArchiveGenesisBookFamiliarity,
                         bgPhilosophy,
                         QStringLiteral("略有耳闻"),
                         QStringLiteral("从未听说")),
    };
}

inline QVector<DialogueBeat> forbiddenArchiveVisitChoiceFollowUp(bool casualBrowse)
{
    const QString bgHall = libraryHallBackgroundFile();
    const QString william = williamYangPortraitFile();

    QVector<DialogueBeat> beats;
    if (casualBrowse) {
        beats.append(narrationBeat(QStringLiteral("你：「想随便逛逛。」"), bgHall));
        beats.append(narrationBeat(QStringLiteral("William.Yang：「好。底楼展廊还开着，跟我来。」"), bgHall, william));
    } else {
        beats.append(narrationBeat(QStringLiteral("你：「有事请教。」"), bgHall));
        beats.append(
            narrationBeat(QStringLiteral("William.Yang：「行。我先带你转转，边走边说。」"), bgHall, william));
    }
    beats.append(forbiddenArchiveTourBeats());
    return beats;
}

inline QVector<DialogueBeat> forbiddenArchiveBookFamiliarityFollowUp(bool heardBefore)
{
    const QString witch = witchPortraitFile();
    const QString william = williamYangPortraitFile();
    const QString bgPhilosophy = libraryPhilosophyWingBackgroundFile();

    QVector<DialogueBeat> beats;
    if (heardBefore) {
        beats.append(narrationBeat(QStringLiteral("你：「略有耳闻。」"), bgPhilosophy));
        beats.append(narrationBeat(QStringLiteral("William.Yang：「嗯。馆藏里有真本，封存太久了，"
                                                   "架上反而找不着。」"),
                                   bgPhilosophy,
                                   william));
    } else {
        beats.append(narrationBeat(QStringLiteral("你：「从未听说。」"), bgPhilosophy));
        beats.append(narrationBeat(QStringLiteral("William.Yang：「上古魔典。真本一直在馆里，"
                                                   "封存太久了，架上反而找不着。」"),
                                   bgPhilosophy,
                                   william));
    }

    beats.append(narrationBeat(QStringLiteral("William.Yang：「听说书里藏着通往湖心岛的秘密。"
                                               "封存太久，架上找不着——得回忆起索书号才行。」"),
                               bgPhilosophy,
                               william));
    beats.append(narrationBeat(QStringLiteral("（索引柜里只剩半张旧目录卡，字迹漫漶，索书号缺了一截。）"),
                               bgPhilosophy));
    beats.append(narrationBeat(QStringLiteral("William.Yang：「你想到了，告诉我。我带你去对应的书柜。」"),
                               bgPhilosophy,
                               william));
    beats.append(forbiddenArchiveCatalogDecisionBeat(bgPhilosophy));
    return beats;
}

inline QVector<DialogueBeat> forbiddenArchiveWrongShelfBeats(const QString &catalogNumber)
{
    const QString bgShelf = libraryShelfBackgroundFile();
    const QString william = williamYangPortraitFile();

    return {
        narrationBeat(QStringLiteral("William.Yang：「%1，这边。」").arg(catalogNumber), bgShelf, william),
        narrationBeat(QStringLiteral("（古分馆深处，一排铁扣古本挤得满满当当。）"), bgShelf),
        narrationBeat(QStringLiteral("（你一本本看过去。书脊上的名字各异，没有《原神之力》。）"), bgShelf),
        narrationBeat(QStringLiteral("William.Yang：「这一架对不上。再想想？」"), bgShelf, william),
    };
}

inline QVector<DialogueBeat> forbiddenArchiveCorrectShelfBeats()
{
    const QString bgShelf = libraryShelfBackgroundFile();
    const QString bgBook = libraryBookBackgroundFile();
    const QString bgHall = libraryHallBackgroundFile();
    const QString william = williamYangPortraitFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("William.Yang：「没错，最里侧。」"), bgShelf, william),
        narrationBeat(QStringLiteral("（书柜尽头，一册薄书卡在铁扣里。书脊：原神，下款小字：之力。）"), bgShelf),
        narrationBeat(QStringLiteral("（你把《原神之力》抽出来。纸页旧，指尖抚过却不断。）"), bgBook),
        narrationBeat(QStringLiteral("（读了几页。字里行间提到镜湖、木桥、湖心——"
                                      "像一条被写进条目里的路。）"),
                      bgBook),
        narrationBeat(QStringLiteral("（再往后翻，内页空白。）"), bgBook),
        narrationBeat(QStringLiteral("William.Yang：「看到这儿就行。不能带出馆。」"), bgBook, william),
        narrationBeat(QStringLiteral("小魔女：「湖心岛……原来在书页里先走了一遍。」"), bgBook, witch),
        narrationBeat(QStringLiteral("（你把书插回架上。铁扣咔的一声合上。）"), bgShelf),
        narrationBeat(QStringLiteral("（退回主厅。外头天光仍旧，像只是进馆逛了一圈。）"), bgHall),
    };
}

inline QVector<DialogueBeat> forbiddenArchiveDeferBeats()
{
    const QString bgPhilosophy = libraryPhilosophyWingBackgroundFile();
    const QString bgHall = libraryHallBackgroundFile();
    const QString william = williamYangPortraitFile();
    const QString witch = witchPortraitFile();

    return {
        narrationBeat(QStringLiteral("William.Yang：「没关系。旧卡和铜牌都在，想好了再来。」"), bgPhilosophy, william),
        narrationBeat(QStringLiteral("小魔女：「园子里别处也值得一走。编号不急。」"), bgPhilosophy, witch),
        narrationBeat(QStringLiteral("（你们从古分馆退出来。收藏馆还是那样静。）"), bgHall),
    };
}

inline QVector<DialogueBeat> ruinGardenFarewellBeats()
{
    const QString witch = witchPortraitFile();
    const QString bgLeave = ruinGardenFarewellBackgroundFile();

    return {
        narrationBeat(QStringLiteral("小魔女：「记不记得都行。它本来就不是用来被记住的。」"), bgLeave, witch),
        narrationBeat(QStringLiteral("（风从园门推过来，像轻轻催你继续走。）"), bgLeave),
        narrationBeat(QStringLiteral("（你没有回头。园子在身后慢慢合拢，像一本翻到一半的书。）"), bgLeave),
    };
}

inline QVector<DialogueBeat> ruinGardenHeartBeats()
{
    const QString witch = witchPortraitFile();
    const QString bgHeart = ruinGardenHeartBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（小径尽头，绿让开一方空地。池面不起波，像铺了一层薄玻璃。）"), bgHeart),
        narrationBeat(QStringLiteral("（将谢未谢的花压着池沿，瓣缘贴水，却不沉下去。）"), bgHeart),
        narrationBeat(QStringLiteral("小魔女：「有些园子，专门收留来不及带走的东西。」"), bgHeart, witch),
        binaryChoiceBeat(DialogueChoiceKind::RuinGardenStayOrLeave,
                         bgHeart,
                         QStringLiteral("在这里多站一会儿"),
                         QStringLiteral("顺着风离开")),
    };
}

inline QVector<DialogueBeat> ruinGardenStayFollowUpBeats()
{
    const QString bgHeart = ruinGardenHeartBackgroundFile();

    QVector<DialogueBeat> beats = {
        narrationBeat(QStringLiteral("你：「在这里多站一会儿」"), bgHeart),
        narrationBeat(QStringLiteral("（你收住脚步。远钟响了一声，余音散进叶里。）"), bgHeart),
        narrationBeat(QStringLiteral("（池面倒映的云，比天上的云更淡。）"), bgHeart),
    };
    beats.append(ruinGardenFarewellBeats());
    return beats;
}

inline QVector<DialogueBeat> ruinGardenLeaveFollowUpBeats()
{
    const QString bgHeart = ruinGardenHeartBackgroundFile();

    QVector<DialogueBeat> beats = {
        narrationBeat(QStringLiteral("你：「顺着风离开」"), bgHeart),
    };
    beats.append(ruinGardenFarewellBeats());
    return beats;
}

inline QVector<DialogueBeat> ruinGardenLightPathFollowUpBeats()
{
    const QString bgFork = ruinGardenLightForkBackgroundFile();
    const QString bgPath = ruinGardenLightPathBackgroundFile();

    QVector<DialogueBeat> beats = {
        narrationBeat(QStringLiteral("你：「往有光的一侧走」"), bgFork),
        narrationBeat(QStringLiteral("（光从拱窗漏下来，落在旧石面上，薄得像一层可以吹走的纱。）"), bgPath),
        narrationBeat(QStringLiteral("（断栏的锈色被照暖，像旧物忽然记起自己曾经亮过。）"), bgPath),
    };
    beats.append(ruinGardenHeartBeats());
    return beats;
}

inline QVector<DialogueBeat> ruinGardenShadePathFollowUpBeats()
{
    const QString bgFork = ruinGardenShadowForkBackgroundFile();
    const QString bgPath = ruinGardenShadowPathBackgroundFile();

    QVector<DialogueBeat> beats = {
        narrationBeat(QStringLiteral("你：「往更静的一侧走」"), bgFork),
        narrationBeat(QStringLiteral("（你走进影里。风铃的铃舌早就不在了，只剩环在风里轻轻碰自己。）"), bgPath),
        narrationBeat(QStringLiteral("（廊下空椅落了几片叶，叶缘被拂到一边——不久之前，这里还坐过人。）"), bgPath),
    };
    beats.append(ruinGardenHeartBeats());
    return beats;
}

inline QVector<DialogueBeat> ruinGardenMainDialogueBeats()
{
    const QString witch = witchPortraitFile();
    const QString bgEntry = ruinGardenEntryBackgroundFile();

    return {
        narrationBeat(QStringLiteral("（铁门半开。藤蔓从栏上垂下来，新叶盖住了锋利的边。）"), bgEntry),
        narrationBeat(QStringLiteral("（园子里没有脚步声，只有风在叶层里慢慢过筛。）"), bgEntry),
        narrationBeat(QStringLiteral("小魔女：「有些路，是用来慢慢走的。」"), bgEntry, witch),

        narrationBeat(QStringLiteral("（石阶缝里长着苔，被午后的光晒得发暖。）"), bgEntry),
        narrationBeat(QStringLiteral("（廊柱断了一截，断口处停着一只蝶，翅轻轻合拢，像一小片将落未落的花。）"), bgEntry),
        narrationBeat(QStringLiteral("（小径在前方轻轻分开——一边更亮，一边更静。）"), bgEntry),
        binaryChoiceBeat(DialogueChoiceKind::RuinGardenLightOrShade,
                         bgEntry,
                         QStringLiteral("往有光的一侧走"),
                         QStringLiteral("往更静的一侧走")),
    };
}

inline QVector<DialogueBeat> dialogueBeatsForSite(int siteId)
{
    if (siteId == kInitialStartSiteId) {
        return spellHallMainDialogueBeats();
    }
    if (siteId == kTianmenSiteId) {
        return tianmenMainDialogueBeats();
    }
    if (siteId == kRuinGardenSiteId) {
        return ruinGardenMainDialogueBeats();
    }
    if (siteId == kOldRealmSiteId) {
        return oldRealmMainDialogueBeats();
    }
    if (siteId == kForbiddenArchiveSiteId) {
        return forbiddenArchiveMainDialogueBeats();
    }
    if (siteId == kTavernSiteId) {
        return tavernMainDialogueBeats();
    }
    if (siteId == kTheaterSiteId) {
        return theaterMainDialogueBeats();
    }
    if (siteId == kArenaSiteId) {
        return arenaMainDialogueBeats();
    }
    if (siteId == kArcaneTowerSiteId) {
        return arcaneTowerMainDialogueBeats();
    }
    if (siteId == kMirrorLakeSiteId) {
        return mirrorLakeMainDialogueBeats();
    }
    if (siteId == kLuIslandSiteId) {
        return luIslandMainDialogueBeats();
    }
    return {};
}

#endif // SITE_DIALOGUES_H
