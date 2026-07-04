#include "game_answers.h"

#include "site_answer_book.h"
#include "site_dialogues.h"
#include "site_graph.h"

void configureGameAnswers()
{
    auto &book = SiteAnswerBook::instance();
    book.resetAllToDefaults();

    // 各地点探索完成后的答题（Site_Window 挑战阶段）
    for (int i = 1; i <= kSiteCount; ++i) {
        if (i == kRuinGardenSiteId || i == kOldRealmSiteId || i == kForbiddenArchiveSiteId || i == kMirrorLakeSiteId
            || i == kTavernSiteId || i == kTheaterSiteId || i == kArcaneTowerSiteId) {
            continue;
        }
        book.setAnswer(i, siteName(i));
    }

    // 旧日之境·无门小店：写对店名后门才会出现（可多选其一）
    book.setAcceptedAnswers(kOldRealmSiteId, {QStringLiteral("燕南五十")});

    // 禁书收藏馆·《原神之力》索书号（可多选其一）
    book.setAcceptedAnswers(kForbiddenArchiveSiteId,
                            {QStringLiteral("B923.536"),
                             QStringLiteral("b923.536")});

    book.setAcceptedAnswers(kMirrorLakeSiteId,
                            {QStringLiteral("13"),
                             QStringLiteral("26"),
                             QStringLiteral("十三"),
                             QStringLiteral("二十六")});

    // 行者酒馆：花神庙碑问答（可多选其一）
    book.setAcceptedAnswers(kTavernSiteId,
                            {QStringLiteral("燕南园"), QStringLiteral("旧日之境")});

    // 吟游剧场：另一时空壁画《踏秋图》的作者
    book.setAcceptedAnswers(kTheaterSiteId, {QStringLiteral("林祥雄")});
}
