#include "UFO.h"
#include <QMessageBox>

UFO::UFO(QWidget *parent)
    : QMainWindow(parent)
{
    // 窗口最大化显示
    setWindowState(Qt::WindowMaximized);

    ui.setupUi(this);   

    connectSystemMark();
}

UFO::~UFO()
{

}


// 连接振镜
int UFO::connectSystemMark()
{
    // ReturnFunc
    int returnValue = 0;

    // 搜索驱动文件所在的位置，绝对路径
    char fpgaPaths[MAX_PATH + 1]{};
    GetModuleFileNameA(nullptr, fpgaPaths, MAX_PATH);
    std::string FirmwareProgram = const_cast<char*>(fpgaPaths);
    int index = FirmwareProgram.find_last_of("\\");
    std::string folderPath = FirmwareProgram.substr(0, index);
    std::string fpgaPath = folderPath + "" + "FpgaFirmware.rbf";

    // string转char*
    char* filePath = const_cast<char*>(fpgaPath.c_str());
    
    // 连接板卡
    returnValue = CSC_MARK::dynamicm::DynamicLoaderc::OpenUSB_Board(0, NULL);
    returnValue = CSC_MARK::dynamicm::DynamicLoaderc::LoadFPGA_FirmwareProgram(filePath);

    return returnValue;
}

// 连接PI
bool UFO::connectSystemPi()
{
    return true;
}

