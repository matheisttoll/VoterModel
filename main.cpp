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
