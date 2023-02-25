#pragma once

#include <QDialog>
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
	// 快门句柄
	ULONG index{};

	// 快门连接
	bool S_IsConnect{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 连接快门
	void on_connectShutter_clicked();

	// 快门打开
	void on_openShutter_clicked();

	// 快门关闭
	void on_closeShutter_clicked();

private:
	Ui::shutterControl ui;
};
