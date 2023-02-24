  #include "MarkControl.h"

MarkControl::MarkControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    // ��ȡ�ļ���ַ
    QString m_FileName = QCoreApplication::applicationDirPath();
    QString m_FileName1 = m_FileName + "/626902.jpeg";
    QString m_FileName2 = m_FileName + "/systemInfo.ini";
    
    // ת���ݸ�ʽ
    String imgSrc = m_FileName1.toStdString();

    // ��ȡͼ��
    inputImage = imread(imgSrc, 1);

    // ת��ͼƬ��ʽ
    cv::cvtColor(inputImage, inputImage, COLOR_BGR2RGB);

    // ͼ��cv::MatתQImage
    qImg = QImage((const unsigned char*)(inputImage.data), inputImage.cols,
        inputImage.rows, inputImage.step, QImage::Format_RGB888);

    // ʵ������
    pixmapScale(qImg, ImageData);

    // ��ȡ������Ϣ
    isConnect = new QSettings(m_FileName, QSettings::IniFormat);

    // ��ȡ��������Ϣ
    M_IsConnect = isConnect->value("��").toBool();

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

//�رմ����¼�
void MarkControl::closeEvent(QCloseEvent* event)
{
    delete this;
}

// QImageʵ��ͼƬ��ʧ������
void MarkControl::pixmapScale(const QImage& image, const double& index)
{
    // ��ʾͼ��
    ui.ChoosePhoto->setPixmap(QPixmap::fromImage(image.scaled(image.width() / index, image.height() / index, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    // ͼƬ����
    ui.ChoosePhoto->setAlignment(Qt::AlignCenter);
}

// �����ֹ���
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

// ������
void MarkControl::on_connectMark_clicked()
{
    // ReturnFunc
    int returnValue = 0;

    // ���������ļ����ڵ�λ�ã�����·��
    char fpgaPaths[MAX_PATH + 1]{};
    GetModuleFileNameA(nullptr, fpgaPaths, MAX_PATH);
    std::string FirmwareProgram = const_cast<char*>(fpgaPaths);
    int index = FirmwareProgram.find_last_of("\\");
    std::string folderPath = FirmwareProgram.substr(0, index);
    std::string fpgaPath = folderPath + "\\" + "FpgaFirmware.rbf";

    // stringתchar*
    char* filePath = const_cast<char*>(fpgaPath.c_str());

    // ���Ӱ忨
    returnValue = OpenUSB_Board(0, NULL);
    returnValue = LoadFPGA_FirmwareProgram(filePath);

    // 0 == false  ���� == true
    if (returnValue < 0)
    {
        ui.connectMark->setEnabled(true);
        ui.Jumpto->setEnabled(false);
        ui.Jumptodown->setEnabled(false);
        ui.Jumptoleft->setEnabled(false);
        ui.Jumptoright->setEnabled(false);
        ui.Jumptoup->setEnabled(false);
        QMessageBox::information(this, "��", "������ʧ�ܣ������豸����");
        return;
    }

    // ������ӳɹ�
    ui.connectMark->setEnabled(false);
    ui.Jumpto->setEnabled(true);
    ui.Jumptodown->setEnabled(true);
    ui.Jumptoleft->setEnabled(true);
    ui.Jumptoright->setEnabled(true);
    ui.Jumptoup->setEnabled(true);
}

// ����΢��
void MarkControl::on_Jumptoup_clicked()
{
    // ��ȡ����
    double markStep = ui.markStep->value();

    // ��ǰλ��y���ӣ�x����
    double xPos = ui.xPos->value();
    double yPos = ui.yPos->value() + markStep;

    // ��ת
    Goto_XY(xPos, yPos);

    // ���¿ؼ�ֵ
    ui.yPos->setValue(yPos);
}

// ����΢��
void MarkControl::on_Jumptodown_clicked()
{
    // ��ȡ����
    double markStep = ui.markStep->value();

    // ��ǰλ��y���ӣ�x����
    double xPos = ui.xPos->value();
    double yPos = ui.yPos->value() - markStep;

    // ��ת
    Goto_XY(xPos, yPos);

    // ���¿ؼ�ֵ
    ui.yPos->setValue(yPos);
}

// ����΢��
void MarkControl::on_Jumptoleft_clicked()
{
    // ��ȡ����
    double markStep = ui.markStep->value();

    // ��ǰλ��x���ӣ�y����
    double xPos = ui.xPos->value() - markStep;
    double yPos = ui.yPos->value();

    // ��ת
    Goto_XY(xPos, yPos);

    // ���¿ؼ�ֵ
    ui.xPos->setValue(xPos);
}

// ����΢��
void MarkControl::on_Jumptoright_clicked()
{
    // ��ȡ����
    double markStep = ui.markStep->value();

    // ��ǰλ��x���ӣ�y����
    double xPos = ui.xPos->value() + markStep;
    double yPos = ui.yPos->value();

    // ��ת
    Goto_XY(xPos, yPos);

    // ���¿ؼ�ֵ
    ui.xPos->setValue(xPos);
}

// ��ת��
void MarkControl::on_Jumpto_clicked()
{
    // ��ȡ��תλ��
    double xJump = ui.xJump->value();
    double yJump = ui.yJump->value();

    // ��ת��
    Goto_XY(xJump, yJump);

    // ���¿ؼ�ֵ
    ui.xPos->setValue(xJump);
    ui.yPos->setValue(yJump);
}