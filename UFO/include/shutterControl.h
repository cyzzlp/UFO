#pragma once

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include "CH375DLL_dynamics_loader.h"
#include "ui_shutterControl.h"

class shutterControl : public QDialog
{
	Q_OBJECT

public:
	shutterControl(QWidget *parent = nullptr);
	~shutterControl();

private:
	// ���ž��
	ULONG index{};

	// ���ž��
	int indexs{};

	// ��������
	bool S_IsConnect{};

private:
	// ��ȡ������Ϣ
	QSettings* shutter{};

private slots:
	// ���ӿ���
	void on_connectShutter_clicked();

	// ���Ŵ�
	void on_openShutter_clicked();

	// ���Źر�
	void on_closeShutter_clicked();

private:
	Ui::shutterControl ui;
};