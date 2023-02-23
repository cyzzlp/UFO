#include "MarkControl.h"

MarkControl::MarkControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    // ��ȡ�ļ���ַ
    QString m_FileName = QCoreApplication::applicationDirPath() + "/626902.jpeg";
    
    // ת���ݸ�ʽ
    String imgSrc = m_FileName.toStdString();

    // ��ȡͼ��
    inputImage = imread(imgSrc, 1);

    // ת��ͼƬ��ʽ
    cv::cvtColor(inputImage, inputImage, COLOR_BGR2RGB);

    // ͼ��cv::MatתQImage
    qImg = QImage((const unsigned char*)(inputImage.data), inputImage.cols,
        inputImage.rows, inputImage.step, QImage::Format_RGB888);

    // ʵ������
    pixmapScale(qImg, ImageData);
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
