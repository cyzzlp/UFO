#pragma once

#include <QDialog>
#include <QLabel>
#include <QCloseEvent>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include "ui_MarkControl.h"

using namespace cv;

class MarkControl : public QDialog
{
	Q_OBJECT

public:
	MarkControl(QWidget *parent = nullptr);
	~MarkControl();

private:
	// ԭʼͼ��
	QImage qImg;

	// ͼ�����    
	cv::Mat inputImage;

	// ͼƬ�Ŵ���Сϵ��
	double ImageData = 5.05;

private:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// QImageʵ��ͼƬ��ʧ������
	void pixmapScale(const QImage& image, const double& index);

	// ʵ�ֿ�ݼ�����
	void wheelEvent(QWheelEvent* event);


private:
	Ui::MarkControl ui;
};
