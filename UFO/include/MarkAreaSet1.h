#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_MarkAreaSet1.h"

class MarkAreaSet1 : public QDialog
{
	Q_OBJECT

public:
	MarkAreaSet1(QWidget *parent = nullptr);
	~MarkAreaSet1();

private:
	// X标刻范围
	double xRange{};

	// Y标刻范围
	double yRange{}; 
	
	// XY互换
	bool ExchangeXY{};

	// X反向
	bool InvertX{};

	// Y反向
	bool InvertY{};

	// X轴校正系数
	double XCorrection{};

	// Y轴校正系数
	double YCorrection{};

	// Z轴校正系数
	double ZCorrection{};

	// 调入校正文件
	QString CorrectionShowPath{};

private:
	// 配置文件
	QSettings* correctRead{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_GetMarkAreaSetting_clicked();

	// 关闭界面
	void on_CancelMarkAreaSetting_clicked();

private:
	Ui::MarkAreaSet1 ui;
};
