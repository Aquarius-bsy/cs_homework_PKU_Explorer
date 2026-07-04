#ifndef SITE_ANSWER_BOOK_H
#define SITE_ANSWER_BOOK_H

#include <QHash>
#include <QMap>
#include <QString>
#include <QStringList>

// 各地点通关答案的统一配置入口。
// 在 game_answers.cpp 的 configureGameAnswers() 中修改，或运行时调用：
//   SiteAnswerBook::instance().setAnswer(siteId, "答案");
//   SiteAnswerBook::instance().setAcceptedAnswers(siteId, {"答案1", "答案2"});
class SiteAnswerBook
{
public:
    static SiteAnswerBook &instance();

    void setAnswer(int siteId, const QString &answer);
    void setAcceptedAnswers(int siteId, const QStringList &answers);
    void setAnswers(const QMap<int, QString> &answers);
    void setAllAnswers(const QMap<int, QString> &primaryAnswers,
                       const QMap<int, QStringList> &acceptedAnswers = {});

    QString answerFor(int siteId) const;
    QStringList acceptedAnswersFor(int siteId) const;
    bool hasCustomAnswer(int siteId) const;
    bool hasAcceptedAnswers(int siteId) const;
    bool checkAnswer(int siteId, const QString &userInput) const;

    void resetAnswer(int siteId);
    void resetAcceptedAnswers(int siteId);
    void resetAllToDefaults();

private:
    SiteAnswerBook();

    static bool isValidSiteId(int siteId);
    QString defaultAnswerFor(int siteId) const;

    QHash<int, QString> m_customAnswers;
    QHash<int, QStringList> m_acceptedAnswers;
};

#endif // SITE_ANSWER_BOOK_H
