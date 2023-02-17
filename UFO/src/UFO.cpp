#include "UFO.h"

UFO::UFO(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);  

    OpenUSB_Board(0, NULL);
}

UFO::~UFO()
{

}
