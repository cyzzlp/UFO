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
	// ԭʼͼ��
	QImage qImg;

	// ͼ�����    
	cv::Mat inputImage;

	// ͼƬ�Ŵ���Сϵ��
	double ImageData = 5.05;

	// ������״̬
	bool M_IsConnect{};

private:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// QImageʵ��ͼƬ��ʧ������
	void pixmapScale(const QImage& image, const double& index);

	// ʵ�ֿ�ݼ�����
	void wheelEvent(QWheelEvent* event);

private slots:
	// ������
	void on_connectMark_clicked();

	// ����΢��
	void on_Jumptoup_clicked();

	// ����΢��
	void on_Jumptodown_clicked();

	// ����΢��
	void on_Jumptoleft_clicked();

	// ����΢��
	void on_Jumptoright_clicked();

	// ��ת��
	void on_Jumpto_clicked();

private:
	Ui::MarkControl ui;
};
