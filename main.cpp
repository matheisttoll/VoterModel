#include "animationwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include "votergrid.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("Voter Model Simulation");


    QCommandLineParser parser;
    parser.setApplicationDescription("Simulation of the Voter Model");
//    parser.addHelpOption();

    QCommandLineOption width_option(QStringList() << "w" << "width",
                                    "Width of simulation window."
                                    "width"
                                    "512");
    parser.addOption(width_option);

    QCommandLineOption height_option(QStringList() << "h" << "height",
                                    "Height of simulation window."
                                    "height"
                                    "512");
    parser.addOption(height_option);

    QCommandLineOption theta_option(QStringList() << "theta" << "probability" << "p",
                                    "Initial probability for black."
                                    "theta"
                                    "0.5");
    parser.addOption(theta_option);

    QCommandLineOption size_option(QStringList() << "s" << "size",
                                    "Edge length of voter sqares in pixel."
                                    "size"
                                    "2");
    parser.addOption(size_option);

    parser.process(app);
    int width = parser.value(width_option).toInt();
    int height = parser.value(height_option).toInt();
    int size = parser.value(size_option).toInt();
    double theta = parser.value(theta_option).toDouble();

    AnimationWindow w;
    w.show();
    return app.exec();
}
