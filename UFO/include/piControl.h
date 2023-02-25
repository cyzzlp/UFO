#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "PI_GCS2_DLL.h"
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

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 连接PI
	void on_ConnectPi_clicked();

	// PI移动至
	void on_inplementMove_clicked();

	// PI增加
	void on_AddPiStep_clicked();

	// PI减少
	void on_CutPiStep_clicked();

	// 当前至设为z = 0
	void on_presentSetZero_clicked();

signals:
	// 发送PI位置
	void piPos(double zPos);

private:
	Ui::piControl ui;
};
