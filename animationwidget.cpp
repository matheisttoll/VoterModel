#include "animationwidget.h"

#include <QPainter>
#include <QTimer>
#include <QThread>
#include <QRect>
#include <iostream>

AnimationWidget::AnimationWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(grid.get_width()*squareSize, grid.get_height()*squareSize);
}

void AnimationWidget::paintEvent(QPaintEvent* event) {
    QRect rect = event->rect();
    //std::cout << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height() << std::endl;
    if(rect.width() == squareSize && rect.height() == squareSize) {
        QPainter painter(this);
        int index = std::get<1>(last_changed);
        int row = grid.get_row(index);
        int col = grid.get_col(index);
        if(grid.get_opinion(row,col)) {
            painter.fillRect(rect, Qt::black);
        } else {
            painter.fillRect(rect, Qt::white);
        }
    } else {
        paintAll();
        //fullRedraw = false;
    }
}

//void AnimationWidget::resizeEvent(QResizeEvent *) {
//    fullRedraw = true;
//}




void AnimationWidget::startAnimation(bool) {
    repaint();
    fullRedraw = false;
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &AnimationWidget::next);
    timer->start();
}

void AnimationWidget::paintAll() {
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

void AnimationWidget::next() {
    last_changed = grid.step();
    int index = std::get<1>(last_changed);
    int row = grid.get_row(index);
    int col = grid.get_col(index);
    int size = squareSize;
    QRect rect{size*col,size*row, size,size};
    //std::cout << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height() << std::endl;
    this->repaint(rect);
}
