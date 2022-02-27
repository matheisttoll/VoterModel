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

#include "animationwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include "votergrid.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("Voter Model Simulation");


    QCommandLineParser parser;
    parser.setApplicationDescription("Simulation of the Voter Model");
    parser.addHelpOption();

    parser.addPositionalArgument("width", "Width of simulation window.");
    parser.addPositionalArgument("height", "Height of simulation window.");

    QCommandLineOption theta_option(QStringList() << "theta" << "probability" << "p",
                                    "Initial probability for black.",
                                    "theta",
                                    "0.5");
    parser.addOption(theta_option);

    QCommandLineOption size_option(QStringList() << "s" << "size",
                                    "Edge length of voter sqares in pixel.",
                                    "size",
                                    "2");
    parser.addOption(size_option);

    parser.process(app);
    const QStringList args = parser.positionalArguments();
    int width = args.at(0).toInt();
    int height = args.at(1).toInt();
    int size = parser.value(size_option).toInt();
    double theta = parser.value(theta_option).toDouble();

    std::cout << "width = " << width << ", height = " << height << ", size = " << size << ", theta = " << theta << std::endl;

    AnimationWindow w{width, height, theta, size};
    w.show();
    return app.exec();
}
