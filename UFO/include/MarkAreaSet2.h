#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "calaRatio.h"
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
	double ratioX{};

	// Y轴校正系数
	double ratioY{};

	// Z轴校正系数
	double ratioZ{};

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
	int startmarkmode{};

	// 调入校正文件
	// correctFile

private:
	// 配置文件
	QSettings* correctRead{};

	// 比例界面
	calaRatio* calaR{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_GetMarkAreaSetting2_clicked();

	// 关闭界面
	void on_CancelMarkAreaSetting2_clicked();

	// 计算x比例系数
	void on_clxpBtn_clicked();

	// 计算y比例系数
	void on_clypBtn_clicked();

	// 设置比例控件值
	void SetxSpinBoxValue(double Proport);

	// 设置比例控件值
	void SetySpinBoxValue(double Proport);


private:
	Ui::MarkAreaSet2 ui;
};
