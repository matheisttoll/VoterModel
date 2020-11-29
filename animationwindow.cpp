#include "animationwindow.h"

AnimationWindow::AnimationWindow(QWidget *parent) : QMainWindow(parent) {
    mainWidget.startAnimation(true);
}

AnimationWindow::~AnimationWindow() {

}

void AnimationWindow::next() {
    mainWidget.repaint();
}

