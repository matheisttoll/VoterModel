/*
Copyright 2022 Paul Fuhrmann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "animationwidget.h"

#include <QPainter>
#include <QTimer>
#include <QThread>
#include <QRect>
#include <iostream>

AnimationWidget::AnimationWidget(int width, int height, double theta, int size, QWidget *parent)
    : QWidget(parent), grid{VoterGrid<2>::GridCoord{width,height}, theta}, squareSize(size) {
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
