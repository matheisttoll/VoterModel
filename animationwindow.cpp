#include "animationwindow.h"

AnimationWindow::AnimationWindow(QWidget *parent)
    : QMainWindow(parent), mainWidget{200, 200, 0.1, 5, this} {
    setMinimumSize(mainWidget.minimumSize());
    mainWidget.startAnimation(true);
}

AnimationWindow::~AnimationWindow() {

}
