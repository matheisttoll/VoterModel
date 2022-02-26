#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "votergrid.h"

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    //void resizeEvent(QResizeEvent*);
    void startAnimation(bool start);

private:
    VoterGrid<2> grid{VoterGrid<2>::GridCoord{470,258}};
    int squareSize = 4;
    VoterGrid<2>::GridCoord last_changed;
    QRect to_redraw;
    unsigned long bla = 0UL;

public slots:
    void next();

signals:

};

#endif // ANIMATIONWIDGET_H
