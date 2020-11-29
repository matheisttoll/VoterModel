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
    void startAnimation(bool start);

private:
    VoterGrid grid{};
    int squareSize = 5;

public slots:
    void next();

signals:

};

#endif // ANIMATIONWIDGET_H
