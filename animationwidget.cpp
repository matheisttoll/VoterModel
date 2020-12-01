#include "animationwidget.h"

#include <QPainter>
#include <QTimer>
#include <QThread>
#include <QRect>
#include <iostream>

AnimationWidget::AnimationWidget(QWidget *parent) : QWidget(parent) {
    VoterGrid<2>::GridCoord dimensions = grid.get_dimensions();
    setMinimumSize(dimensions[0]*squareSize, dimensions[1]*squareSize);
}

void AnimationWidget::paintEvent(QPaintEvent* event) {
    QRect rect = event->rect();
    //std::cout << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height() << std::endl;
    if(rect.width() == squareSize && rect.height() == squareSize) {
        QPainter painter(this);
        int index = std::get<1>(last_changed);
        painter.fillRect(rect, grid.get_opinion(index)? Qt::black: Qt::white);
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
    VoterGrid<2>::GridCoord dimensions = grid.get_dimensions();
    int width = dimensions[0];
    int height = dimensions[1];
    int size = squareSize;
    VoterGrid<2>::GridCoord coords;

    for(coords[1] = 0; coords[1] < height; coords[1]++) {
        for(coords[0] = 0; coords[0] < width; coords[0]++) {
            //std::cout << "Paint: " << coords[0] << " " << coords[1] << std::endl;
            painter.fillRect(size*coords[0],size*coords[1],size,size, grid.get_opinion(coords)? Qt::black: Qt::white);
        }
    }
}

void AnimationWidget::next() {
    last_changed = grid.step();
    int index = std::get<1>(last_changed);
    VoterGrid<2>::GridCoord coords = grid.coordinates(index);
    int row = coords[1];
    int col = coords[0];
    int size = squareSize;
    //std::cout << "Next: " << coords[0] << " " << coords[1] << std::endl;
    QRect rect{size*col,size*row, size,size};
    //std::cout << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height() << std::endl;
    this->repaint(rect);
}
