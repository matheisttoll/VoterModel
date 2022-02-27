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

#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "votergrid.h"

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(int width, int height, double theta, int size, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    //void resizeEvent(QResizeEvent*);
    void startAnimation(bool start);

private:
    VoterGrid<2> grid;
    int squareSize;
    VoterGrid<2>::GridCoord last_changed;
    QRect to_redraw;
    unsigned long bla = 0UL;

public slots:
    void next();

signals:

};

#endif // ANIMATIONWIDGET_H
