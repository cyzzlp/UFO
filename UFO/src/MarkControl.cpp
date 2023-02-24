  #include "MarkControl.h"

MarkControl::MarkControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    // 读取文件地址
    QString m_FileName = QCoreApplication::applicationDirPath();
    QString m_FileName1 = m_FileName + "/626902.jpeg";
    QString m_FileName2 = m_FileName + "/systemInfo.ini";
    
    // 转数据格式
    String imgSrc = m_FileName1.toStdString();

    // 读取图像
    inputImage = imread(imgSrc, 1);

    // 转换图片格式
    cv::cvtColor(inputImage, inputImage, COLOR_BGR2RGB);

    // 图像cv::Mat转QImage
    qImg = QImage((const unsigned char*)(inputImage.data), inputImage.cols,
        inputImage.rows, inputImage.step, QImage::Format_RGB888);

    // 实现缩放
    pixmapScale(qImg, ImageData);

    // 读取连接信息
    isConnect = new QSettings(m_FileName, QSettings::IniFormat);

    // 读取振镜连接信息
    M_IsConnect = isConnect->value("振镜").toBool();

    if (!M_IsConnect)
    {
        ui.connectMark->setEnabled(true);
        ui.Jumpto->setEnabled(false);
        ui.Jumptodown->setEnabled(false);
        ui.Jumptoleft->setEnabled(false);
        ui.Jumptoright->setEnabled(false);
        ui.Jumptoup->setEnabled(false);
    }
    else
    {
        ui.connectMark->setEnabled(false);
        ui.Jumpto->setEnabled(true);
        ui.Jumptodown->setEnabled(true);
        ui.Jumptoleft->setEnabled(true);
        ui.Jumptoright->setEnabled(true);
        ui.Jumptoup->setEnabled(true);
    }
}

MarkControl::~MarkControl()
{

}

//关闭窗口事件
void MarkControl::closeEvent(QCloseEvent* event)
{
    delete this;
}

// QImage实现图片不失真缩放
void MarkControl::pixmapScale(const QImage& image, const double& index)
{
    // 显示图像
    ui.ChoosePhoto->setPixmap(QPixmap::fromImage(image.scaled(image.width() / index, image.height() / index, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    // 图片居中
    ui.ChoosePhoto->setAlignment(Qt::AlignCenter);
}

// 鼠标滚轮滚动
void MarkControl::wheelEvent(QWheelEvent* event)
{
    if (!inputImage.empty())
    {
        if (event->delta() < 0)
        {
            ImageData = ImageData + 0.05;
            pixmapScale(qImg, ImageData);
        }
        else
        {
            ImageData = ImageData - 0.05;
            pixmapScale(qImg, ImageData);
        }
        event->accept();
    }
}

// 连接振镜
void MarkControl::on_connectMark_clicked()
{
    // ReturnFunc
    int returnValue = 0;

    // 搜索驱动文件所在的位置，绝对路径
    char fpgaPaths[MAX_PATH + 1]{};
    GetModuleFileNameA(nullptr, fpgaPaths, MAX_PATH);
    std::string FirmwareProgram = const_cast<char*>(fpgaPaths);
    int index = FirmwareProgram.find_last_of("\\");
    std::string folderPath = FirmwareProgram.substr(0, index);
    std::string fpgaPath = folderPath + "\\" + "FpgaFirmware.rbf";

    // string转char*
    char* filePath = const_cast<char*>(fpgaPath.c_str());

    // 连接板卡
    returnValue = OpenUSB_Board(0, NULL);
    returnValue = LoadFPGA_FirmwareProgram(filePath);

    // 0 == false  其他 == true
    if (returnValue < 0)
    {
        ui.connectMark->setEnabled(true);
        ui.Jumpto->setEnabled(false);
        ui.Jumptodown->setEnabled(false);
        ui.Jumptoleft->setEnabled(false);
        ui.Jumptoright->setEnabled(false);
        ui.Jumptoup->setEnabled(false);
        QMessageBox::information(this, "振镜", "振镜连接失败，请检查设备连接");
        return;
    }

    // 如果连接成功
    ui.connectMark->setEnabled(false);
    ui.Jumpto->setEnabled(true);
    ui.Jumptodown->setEnabled(true);
    ui.Jumptoleft->setEnabled(true);
    ui.Jumptoright->setEnabled(true);
    ui.Jumptoup->setEnabled(true);
}

// 向上微调
void MarkControl::on_Jumptoup_clicked()
{
    // 读取步长
    double markStep = ui.markStep->value();

    // 当前位置y增加，x不变
    double xPos = ui.xPos->value();
    double yPos = ui.yPos->value() + markStep;

    // 跳转
    Goto_XY(xPos, yPos);

    // 更新控件值
    ui.yPos->setValue(yPos);
}

// 向下微调
void MarkControl::on_Jumptodown_clicked()
{
    // 读取步长
    double markStep = ui.markStep->value();

    // 当前位置y增加，x不变
    double xPos = ui.xPos->value();
    double yPos = ui.yPos->value() - markStep;

    // 跳转
    Goto_XY(xPos, yPos);

    // 更新控件值
    ui.yPos->setValue(yPos);
}

// 向左微调
void MarkControl::on_Jumptoleft_clicked()
{
    // 读取步长
    double markStep = ui.markStep->value();

    // 当前位置x增加，y不变
    double xPos = ui.xPos->value() - markStep;
    double yPos = ui.yPos->value();

    // 跳转
    Goto_XY(xPos, yPos);

    // 更新控件值
    ui.xPos->setValue(xPos);
}

// 向右微调
void MarkControl::on_Jumptoright_clicked()
{
    // 读取步长
    double markStep = ui.markStep->value();

    // 当前位置x增加，y不变
    double xPos = ui.xPos->value() + markStep;
    double yPos = ui.yPos->value();

    // 跳转
    Goto_XY(xPos, yPos);

    // 更新控件值
    ui.xPos->setValue(xPos);
}

// 跳转至
void MarkControl::on_Jumpto_clicked()
{
    // 获取跳转位置
    double xJump = ui.xJump->value();
    double yJump = ui.yJump->value();

    // 跳转至
    Goto_XY(xJump, yJump);

    // 更新控件值
    ui.xPos->setValue(xJump);
    ui.yPos->setValue(yJump);
}