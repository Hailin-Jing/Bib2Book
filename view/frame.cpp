#include "frame.h"

Frame::Frame()
{
    m_mouse_down = false;
    setFrameShape(Panel);

    // Make this a borderless window which can't
    // be resized or moved via the window system
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    m_titleBar = new TitleBar(this);
    m_content = new QWidget(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(m_titleBar);
    vbox->setMargin(0);
    vbox->setSpacing(0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_content);
    layout->setMargin(5);
    layout->setSpacing(0);
    vbox->addLayout(layout);
}

QWidget *Frame::contentWidget() const
{
    return m_content;
}

TitleBar *Frame::titleBar() const
{
    return m_titleBar;
}

void Frame::mousePressEvent(QMouseEvent *event)
{
    m_old_pos = event->pos();
    m_mouse_down = event->button() == Qt::LeftButton;
}

void Frame::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    if (m_mouse_down) {
        int dx = x - m_old_pos.x();
        int dy = y - m_old_pos.y();

        QRect g = geometry();

        if (left)
            g.setLeft(g.left() + dx);
        if (right)
            g.setRight(g.right() + dx);
        if (bottom)
            g.setBottom(g.bottom() + dy);

        setGeometry(g);

        m_old_pos = QPoint(!left ? event->x() : m_old_pos.x(), event->y());
    } else {
        QRect r = rect();
        left = qAbs(x - r.left()) <= 5;
        right = qAbs(x - r.right()) <= 5;
        bottom = qAbs(y - r.bottom()) <= 5;
        bool hor = left | right;

        if (hor && bottom) {
            if (left)
                setCursor(Qt::SizeBDiagCursor);
            else
                setCursor(Qt::SizeFDiagCursor);
        } else if (hor) {
            setCursor(Qt::SizeHorCursor);
        } else if (bottom) {
            setCursor(Qt::SizeVerCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }
}

void Frame::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_mouse_down = false;
}
