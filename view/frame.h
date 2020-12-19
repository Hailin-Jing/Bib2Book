#ifndef FRAME_H
#define FRAME_H

#include <QFrame>
#include "titlebar.h"

class Frame : public QFrame
{
    Q_OBJECT

    TitleBar *m_titleBar;
    QWidget *m_content;
    QPoint m_old_pos;
    bool m_mouse_down;
    bool left, right, bottom;

public:
    Frame();

    // Allows you to access the content area of the frame
    // where widgets and layouts can be added
    QWidget *contentWidget() const;
    TitleBar *titleBar() const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // FRAME_H
