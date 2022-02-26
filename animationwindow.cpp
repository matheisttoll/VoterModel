#include "animationwindow.h"

AnimationWindow::AnimationWindow(QWidget *parent) : QMainWindow(parent), mainWidget{this} {
    setMinimumSize(mainWidget.minimumSize());
    mainWidget.startAnimation(true);
}

AnimationWindow::~AnimationWindow() {

}
