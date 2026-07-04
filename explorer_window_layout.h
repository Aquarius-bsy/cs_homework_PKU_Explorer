#ifndef EXPLORER_WINDOW_LAYOUT_H
#define EXPLORER_WINDOW_LAYOUT_H

#include <QGuiApplication>
#include <QMainWindow>
#include <QPoint>
#include <QScreen>
#include <QSize>

inline QSize explorerWindowSize()
{
    return QSize(1200, 750);
}

inline QSize storyDialogSize()
{
    return QSize(840, 560);
}

inline QSize explorerWindowMinimumSize(const QSize &preferred = explorerWindowSize())
{
    return QSize(qMin(960, preferred.width()), qMin(640, preferred.height()));
}

inline void centerWindowOnScreen(QMainWindow *window)
{
    const QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen || !window) {
        return;
    }

    const QRect area = screen->availableGeometry();
    const QPoint topLeft(area.center().x() - window->width() / 2,
                         area.center().y() - window->height() / 2);
    window->move(topLeft);
}

inline void applyStoryDialogFrame(QMainWindow *window, const QSize &size = explorerWindowSize())
{
    if (!window) {
        return;
    }

    window->setFixedSize(size);
    centerWindowOnScreen(window);
}

inline void applyExplorerWindowFrame(QMainWindow *window, const QSize &size = explorerWindowSize())
{
    if (!window) {
        return;
    }

    window->resize(size);
    window->setMinimumSize(explorerWindowMinimumSize(size));
    centerWindowOnScreen(window);
}

inline QSize explorerWindowSizeFromParent(const QWidget *parent)
{
    if (!parent) {
        return explorerWindowSize();
    }

    const QWidget *top = parent->window();
    if (top && top->width() > 0 && top->height() > 0) {
        return top->size();
    }

    return explorerWindowSize();
}

#endif // EXPLORER_WINDOW_LAYOUT_H
