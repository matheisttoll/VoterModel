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
    QPainter painter(this);
    QRect rect = event->rect();
    //std::cout << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height() << std::endl;
    if(rect.width() == squareSize && rect.height() == squareSize) {
        painter.fillRect(rect, grid.get_opinion(last_changed)? Qt::black: Qt::white);
    } else {
        int width = grid.width();
        int height = grid.height();
        QRect curRect{0,0,squareSize, squareSize};
        VoterGrid<2>::GridCoord coords;

        for(coords[1] = 0; coords[1] < height; coords[1]++) {
            for(coords[0] = 0; coords[0] < width; coords[0]++) {
                painter.fillRect(curRect, grid.get_opinion(coords)? Qt::black: Qt::white);
                curRect.translate(squareSize,0);
            }
            curRect.translate(0, squareSize);
            curRect.moveLeft(0);
        }
    }
}




void AnimationWidget::startAnimation(bool) {
    repaint();
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &AnimationWidget::next);
    timer->start();
}

void AnimationWidget::next() {
    if(grid.step()) {
        last_changed = grid.get_recent_opinion_lookaround();
        int row = last_changed[1];
        int col = last_changed[0];
        repaint(QRect{squareSize*col,squareSize*row, squareSize, squareSize});
    }
}
