#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_MarkAreaSet2.h"

class MarkAreaSet2 : public QDialog
{
	Q_OBJECT

public:
	MarkAreaSet2(QWidget *parent = nullptr);
	~MarkAreaSet2();

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

	// X轴失真校正系数
	double xcorrections{};

	// Y轴失真校正系数
	double ycorrections{};

	// X轴切变校正系数
	double xshear{};

	// Y轴切变校正系数
	double yshear{};

	// X轴梯形校正系数
	double xladder{};

	// Y轴梯形校正系数
	double yladder{};

	// 事件启动
	double startmarkmode{};

	// 调入校正文件
	// correctFile

private:
	// 配置文件
	QSettings* correctRead{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_GetMarkAreaSetting2_clicked();

	// 关闭界面
	void on_CancelMarkAreaSetting2_clicked();

private:
	Ui::MarkAreaSet2 ui;
};
