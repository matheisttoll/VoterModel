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

private:
    AnimationWidget mainWidget;
};
#endif // ANIMATIONWINDOW_H
