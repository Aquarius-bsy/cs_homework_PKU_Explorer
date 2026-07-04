#ifndef EXPLORER_SITE_PIN_H
#define EXPLORER_SITE_PIN_H

#include "site_state.h"

#include <QPushButton>

class ExplorerSitePin : public QPushButton
{
    Q_OBJECT

public:
    explicit ExplorerSitePin(int siteId, QWidget *parent = nullptr);

    void setPinState(SiteState state, qreal progressFill = 0.0, bool colorful = false);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void paintStandardPin(QPainter &painter, const QRect &rect);
    void paintLuIslandPin(QPainter &painter, const QRect &rect);

    int m_siteId = 0;
    SiteState m_state = SiteState::Locked;
    qreal m_progress = 0.0;
    bool m_colorful = false;
};

#endif // EXPLORER_SITE_PIN_H
