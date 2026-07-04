#include "site_answer_book.h"

#include "site_graph.h"

SiteAnswerBook &SiteAnswerBook::instance()
{
    static SiteAnswerBook book;
    return book;
}

SiteAnswerBook::SiteAnswerBook() = default;

bool SiteAnswerBook::isValidSiteId(int siteId)
{
    return siteId >= 1 && siteId <= kSiteCount;
}

QString SiteAnswerBook::defaultAnswerFor(int siteId) const
{
    return QString::number(siteId);
}

void SiteAnswerBook::setAnswer(int siteId, const QString &answer)
{
    if (!isValidSiteId(siteId)) {
        return;
    }
    m_customAnswers.insert(siteId, answer.trimmed());
}

void SiteAnswerBook::setAcceptedAnswers(int siteId, const QStringList &answers)
{
    if (!isValidSiteId(siteId)) {
        return;
    }

    QStringList normalized;
    normalized.reserve(answers.size());
    for (const QString &answer : answers) {
        const QString trimmed = answer.trimmed();
        if (!trimmed.isEmpty()) {
            normalized.append(trimmed);
        }
    }
    m_acceptedAnswers.insert(siteId, normalized);
}

void SiteAnswerBook::setAnswers(const QMap<int, QString> &answers)
{
    for (auto it = answers.constBegin(); it != answers.constEnd(); ++it) {
        setAnswer(it.key(), it.value());
    }
}

void SiteAnswerBook::setAllAnswers(const QMap<int, QString> &primaryAnswers,
                                   const QMap<int, QStringList> &acceptedAnswers)
{
    for (auto it = primaryAnswers.constBegin(); it != primaryAnswers.constEnd(); ++it) {
        setAnswer(it.key(), it.value());
    }
    for (auto it = acceptedAnswers.constBegin(); it != acceptedAnswers.constEnd(); ++it) {
        setAcceptedAnswers(it.key(), it.value());
    }
}

QString SiteAnswerBook::answerFor(int siteId) const
{
    if (!isValidSiteId(siteId)) {
        return {};
    }

    if (m_acceptedAnswers.contains(siteId) && !m_acceptedAnswers.value(siteId).isEmpty()) {
        return m_acceptedAnswers.value(siteId).constFirst();
    }
    return m_customAnswers.value(siteId, defaultAnswerFor(siteId));
}

QStringList SiteAnswerBook::acceptedAnswersFor(int siteId) const
{
    if (!isValidSiteId(siteId)) {
        return {};
    }
    return m_acceptedAnswers.value(siteId);
}

bool SiteAnswerBook::hasCustomAnswer(int siteId) const
{
    return isValidSiteId(siteId) && m_customAnswers.contains(siteId);
}

bool SiteAnswerBook::hasAcceptedAnswers(int siteId) const
{
    return isValidSiteId(siteId) && m_acceptedAnswers.contains(siteId);
}

bool SiteAnswerBook::checkAnswer(int siteId, const QString &userInput) const
{
    if (!isValidSiteId(siteId)) {
        return false;
    }

    const QString trimmed = userInput.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }

    if (m_acceptedAnswers.contains(siteId)) {
        for (const QString &answer : m_acceptedAnswers.value(siteId)) {
            if (trimmed == answer) {
                return true;
            }
        }
        return false;
    }

    return trimmed == answerFor(siteId);
}

void SiteAnswerBook::resetAnswer(int siteId)
{
    if (!isValidSiteId(siteId)) {
        return;
    }
    m_customAnswers.remove(siteId);
}

void SiteAnswerBook::resetAcceptedAnswers(int siteId)
{
    if (!isValidSiteId(siteId)) {
        return;
    }
    m_acceptedAnswers.remove(siteId);
}

void SiteAnswerBook::resetAllToDefaults()
{
    m_customAnswers.clear();
    m_acceptedAnswers.clear();
}
