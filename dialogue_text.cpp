#include "dialogue_text.h"

#include "site_graph.h"

#include <QStringList>
namespace {

QString escapeHtml(const QString &text)
{
    QString escaped = text;
    escaped.replace(QLatin1Char('&'), QStringLiteral("&amp;"));
    escaped.replace(QLatin1Char('<'), QStringLiteral("&lt;"));
    escaped.replace(QLatin1Char('>'), QStringLiteral("&gt;"));
    return escaped;
}

QString boldKeyword(QString html, const QString &keyword)
{
    const QString bold = QStringLiteral("<b>%1</b>").arg(keyword);
    html.replace(keyword, bold);
    return html;
}

} // namespace

QString formatDialogueHtml(const QString &plainText, int siteId)
{
    QString html = escapeHtml(plainText);
    const QStringList keywords = {
        QStringLiteral("花神庙碑"),
        QStringLiteral("花神庙"),
        QStringLiteral("85 决斗"),
        QStringLiteral("DDL"),
        QStringLiteral("角斗士令牌"),
        QStringLiteral("禁演本"),
        QStringLiteral("《星坠燕园》"),
        QStringLiteral("双星坠落"),
        QStringLiteral("另一个时空"),
        QStringLiteral("这次的探索便到此为止"),
        QStringLiteral("园子里的路，不会为你留着"),
        QStringLiteral("确认离开魔法世界"),
        QStringLiteral("你在燕园的探索记录也会一并清空"),
    };
    for (const QString &keyword : keywords) {
        html = boldKeyword(html, keyword);
    }

    if (siteId == kMirrorLakeSiteId) {
        const QStringList mirrorLakeKeywords = {
            QStringLiteral("镜湖"),
            QStringLiteral("镜面"),
            QStringLiteral("镜子"),
            QStringLiteral("水面"),
            QStringLiteral("湖面"),
        };
        for (const QString &keyword : mirrorLakeKeywords) {
            html = boldKeyword(html, keyword);
        }
    }

    return html;
}