#include "UFO.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UFO w;
    w.show();
    return a.exec();
}
