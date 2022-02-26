#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QMainWindow>
#include "votergrid.h"
#include "animationwidget.h"

class AnimationWindow : public QMainWindow
{
    Q_OBJECT

public:
    AnimationWindow(int width, int height, double theta, int size, QWidget *parent = nullptr);
    ~AnimationWindow();

private:
    AnimationWidget mainWidget;
};
#endif // ANIMATIONWINDOW_H
