#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QMainWindow>
#include "votergrid.h"
#include "animationwidget.h"

class AnimationWindow : public QMainWindow
{
    Q_OBJECT

public:
    AnimationWindow(QWidget *parent = nullptr);
    ~AnimationWindow();
    void next();

private:
    AnimationWidget mainWidget{this};
};
#endif // ANIMATIONWINDOW_H
