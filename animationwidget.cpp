#include "animationwidget.h"

#include <QPainter>
#include <QTimer>

AnimationWidget::AnimationWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(grid.get_width()*squareSize, grid.get_height()*squareSize);
}

void AnimationWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    int width = grid.get_width();
    int height = grid.get_height();
    int size = squareSize;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if(grid.get_opinion(x,y)) {
                painter.fillRect(size*x,size*y,size,size, Qt::black);
            } else {
                painter.fillRect(size*x,size*y,size,size, Qt::white);
            }

        }
    }
}

void AnimationWidget::startAnimation(bool) {
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &AnimationWidget::next);
    timer->start();
}

void AnimationWidget::next() {
    grid.step();
    this->repaint();
}
