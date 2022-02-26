#include "animationwindow.h"

AnimationWindow::AnimationWindow(int width, int height, double theta, int size, QWidget *parent)
    : QMainWindow(parent), mainWidget{width, height, theta, size, this} {
    setMinimumSize(mainWidget.minimumSize());
    mainWidget.startAnimation(true);
}

AnimationWindow::~AnimationWindow() {

}
