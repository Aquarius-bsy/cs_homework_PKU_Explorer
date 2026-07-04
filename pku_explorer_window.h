#ifndef PKU_EXPLORER_WINDOW_H
#define PKU_EXPLORER_WINDOW_H

#include "site_graph.h"
#include "site_state.h"
#include "ending_window.h"

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QString>
#include <array>

class ExplorerMapWidget;
class Finish_Window;
class QListWidget;
class Site_Window;

QT_BEGIN_NAMESPACE
namespace Ui {
class PKU_Explorer_Window;
}
QT_END_NAMESPACE

class PKU_Explorer_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit PKU_Explorer_Window(QWidget *parent = nullptr);
    ~PKU_Explorer_Window() override;

    void setSiteAnswer(int siteId, const QString &answer);
    void setSiteAnswers(const QMap<int, QString> &answers);
    QString siteAnswer(int siteId) const;
    void resetSiteAnswer(int siteId);
    void resetAllSiteAnswers();
    void openInitialSiteIfAvailable(int siteId);
    const std::array<SiteState, kSiteCount> &siteStates() const { return m_siteStates; }

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupConnections();
    void onLocationButtonClicked(int index);
    void onSiteCompleted(int siteIndex);
    void onDreamWakeEnding();
    void onLuIslandReturnEnding();
    void onLuIslandStayEnding();
    void completeLuIslandAndShowEnding(StoryEndingKind kind);
    void onResetClicked();
    void loadProgress();
    void saveProgress() const;
    void refreshMap();
    void setInitialSiteStates();
    void unlockNeighbors(int siteIndex);
    void syncLuIslandUnlockState();
    int exploredCount() const;
    void updateExploredProgressDisplay() const;
    void appendLog(const QString &line);
    void checkAllExploredAndShowFinish();

    Ui::PKU_Explorer_Window *ui;
    ExplorerMapWidget *m_mapWidget = nullptr;
    QListWidget *m_logList = nullptr;
    QLabel *m_lblExploredProgress = nullptr;
    QPushButton *m_btnReset = nullptr;
    std::array<SiteState, kSiteCount> m_siteStates{};
    bool m_finishWindowShown = false;
};

#endif // PKU_EXPLORER_WINDOW_H
