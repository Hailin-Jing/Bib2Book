#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QApplication>
#include <QtGui>
#include <QLayout>
#include <QStyle>
#include <QWidget>
#include <QToolButton>
#include <QLabel>

class TitleBar : public QWidget
{
    Q_OBJECT

    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;

public:
    TitleBar(QWidget *parent);

public slots:
    void showSmall();
    void showMaxRestore();

protected:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
};

#endif // TITLEBAR_H
