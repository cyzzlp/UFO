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
	// 原始图像
	QImage qImg;

	// 图像矩阵    
	cv::Mat inputImage;

	// 图片放大缩小系数
	double ImageData = 5.05;

private:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// QImage实现图片不失真缩放
	void pixmapScale(const QImage& image, const double& index);

	// 实现快捷键操作
	void wheelEvent(QWheelEvent* event);


private:
	Ui::MarkControl ui;
};
