#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QLabel>
#include <QCloseEvent>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include "CSCInterface_dynamicm_loader.h"
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

	// 振镜连接状态
	bool M_IsConnect{};

private:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// QImage实现图片不失真缩放
	void pixmapScale(const QImage& image, const double& index);

	// 实现快捷键操作
	void wheelEvent(QWheelEvent* event);

private slots:
	// 连接振镜
	void on_connectMark_clicked();

	// 向上微调
	void on_Jumptoup_clicked();

	// 向下微调
	void on_Jumptodown_clicked();

	// 向左微调
	void on_Jumptoleft_clicked();

	// 向右微调
	void on_Jumptoright_clicked();

	// 跳转至
	void on_Jumpto_clicked();

private:
	Ui::MarkControl ui;
};
