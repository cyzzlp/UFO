#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "calaRatio.h"
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
	double ratioX{};

	// Y轴校正系数
	double ratioY{};

	// Z轴校正系数
	double ratioZ{};

	// 调入校正文件
	QString CorrectionShowPath{};

private:
	// 配置文件
	QSettings* correctRead{};

	// 比例界面
	calaRatio* calaR{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_GetMarkAreaSetting_clicked();

	// 关闭界面
	void on_CancelMarkAreaSetting_clicked();

	// 计算x比例
	void on_clxpBtn_clicked();

	// 计算y比例
	void on_clypBtn_clicked();

	// 设置比例控件值
	void SetxSpinBoxValue(double Proport);

	// 设置比例控件值
	void SetySpinBoxValue(double Proport);

private:
	Ui::MarkAreaSet1 ui;
};
