#include "UFO.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UFO w;

    //if (w.hasError())
    //{
    //    return -1;
    //}

    w.show();
    return a.exec();
}
