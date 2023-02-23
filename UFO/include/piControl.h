#pragma once

#include <QDialog>
#include <QSettings>
#include "PI_GCS2_DLL_dynamicp_loader.h"
#include "ui_piControl.h"

class piControl : public QDialog
{
	Q_OBJECT

public:
	piControl(QWidget *parent = nullptr);
	~piControl();

private:
	// 记录仪器句柄
	int ID{};

	// 记录连接的PI移动轴
	char szAxes[2]{};

	// 记录连接的PI移动轴
	QString szAxe[1]{};

	// 用于 USB 设备描述的 szBuffer 缓冲区
	char szBuffer[17]{};

	// 仅其描述与过滤器匹配的控制器在缓冲区中返回
	char szFilter[17]{};

	// 返回的字符串,包括序列号和设备描述符
	char serialNo[256]{};

	// 错误码
	int iError{};

	// 错误提示
	char szErrorMesage[1024]{};

	// 轴等待
	BOOL bIsMoving[3]{};

	BOOL returnValue{};

	// PI移动位置
	double dPos[3]{};

	// PI连接
	bool P_IsConnect{};

private:
	// 读取PI信息
	QSettings* piInfo{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 连接PI
	void on_ConnectPi_clicked();

private:
	Ui::piControl ui;
};
