#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_laserSet.h"

class laserSet : public QDialog
{
	Q_OBJECT

public:
	laserSet(QWidget *parent = nullptr);
	~laserSet();

private:
	// 激光器类型
	int LaserType{};

	// 预电离
	int Standby{};

	// 预电离频率
	float StandbyFrequency{};

	// 预电离占空比
	float StandbyPulseWidth{};

private:
	// 配置文件
	QSettings* laserset{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_GetLaserSetting_clicked();

	// 关闭界面
	void on_CancelLaserSetting_clicked();

private:
	Ui::laserSet ui;
};
