#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "votergrid.h"

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(int width, int height, double theta, int size, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    //void resizeEvent(QResizeEvent*);
    void startAnimation(bool start);

private:
    VoterGrid<2> grid;
    int squareSize;
    VoterGrid<2>::GridCoord last_changed;
    QRect to_redraw;
    unsigned long bla = 0UL;

public slots:
    void next();

signals:

};

#endif // ANIMATIONWIDGET_H
