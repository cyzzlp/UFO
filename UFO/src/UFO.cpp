#include "UFO.h"

UFO::UFO(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);  

    OpenUSB_Board(0, NULL);

    peak_Library_Init();
}

UFO::~UFO()
{

}
