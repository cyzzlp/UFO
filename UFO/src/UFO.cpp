#include "UFO.h"
#include <QMessageBox>

UFO::UFO(QWidget *parent)
    : QMainWindow(parent)
{
    // ���������ʾ
    setWindowState(Qt::WindowMaximized);

    ui.setupUi(this);   

    connectSystemMark();
}

UFO::~UFO()
{

}


// ������
int UFO::connectSystemMark()
{
    // ReturnFunc
    int returnValue = 0;

    // ���������ļ����ڵ�λ�ã�����·��
    char fpgaPaths[MAX_PATH + 1]{};
    GetModuleFileNameA(nullptr, fpgaPaths, MAX_PATH);
    std::string FirmwareProgram = const_cast<char*>(fpgaPaths);
    int index = FirmwareProgram.find_last_of("\\");
    std::string folderPath = FirmwareProgram.substr(0, index);
    std::string fpgaPath = folderPath + "" + "FpgaFirmware.rbf";

    // stringתchar*
    char* filePath = const_cast<char*>(fpgaPath.c_str());
    
    // ���Ӱ忨
    returnValue = CSC_MARK::dynamicm::DynamicLoaderc::OpenUSB_Board(0, NULL);
    returnValue = CSC_MARK::dynamicm::DynamicLoaderc::LoadFPGA_FirmwareProgram(filePath);

    return returnValue;
}

// ����PI
bool UFO::connectSystemPi()
{
    return true;
}

