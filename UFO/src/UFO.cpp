#include "UFO.h"

UFO::UFO(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);  

    //CSC_Mark::dynamicm::DynamicLoaderc dynamicLoaderc;
   // OpenUSB_Board(0, NULL);

    long j = PI_EnumerateUSB(szBuffer, 17, szFilter);

    peak_status i = peak_Library_Init();

}

UFO::~UFO()
{

}
