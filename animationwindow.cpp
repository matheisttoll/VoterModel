#include "animationwindow.h"

AnimationWindow::AnimationWindow(QWidget *parent) : QMainWindow(parent) {
    setMinimumSize(mainWidget.minimumSize());
    mainWidget.startAnimation(true);
}

AnimationWindow::~AnimationWindow() {

}
