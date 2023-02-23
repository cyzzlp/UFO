#include "MarkControl.h"

MarkControl::MarkControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    // 读取文件地址
    QString m_FileName = QCoreApplication::applicationDirPath() + "/626902.jpeg";
    
    // 转数据格式
    String imgSrc = m_FileName.toStdString();

    // 读取图像
    inputImage = imread(imgSrc, 1);

    // 转换图片格式
    cv::cvtColor(inputImage, inputImage, COLOR_BGR2RGB);

    // 图像cv::Mat转QImage
    qImg = QImage((const unsigned char*)(inputImage.data), inputImage.cols,
        inputImage.rows, inputImage.step, QImage::Format_RGB888);

    // 实现缩放
    pixmapScale(qImg, ImageData);
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
