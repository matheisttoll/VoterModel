#include "animationwindow.h"

#include <QApplication>
#include "votergrid.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    AnimationWindow w;
    w.show();
    return a.exec();
}
