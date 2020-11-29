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
    VoterGrid grid{};
    int squareSize = 3;
    voter last_changed{0.0f,-1};
    void paintAll();
    bool fullRedraw = true;
    unsigned long bla = 0UL;

public slots:
    void next();

signals:

};

#endif // ANIMATIONWIDGET_H
