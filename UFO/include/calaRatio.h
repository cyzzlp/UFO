#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_calaRatio.h"

class calaRatio : public QDialog
{
	Q_OBJECT

public:
	calaRatio(QWidget *parent = nullptr);
	~calaRatio();

private:
	// 读取设置
	QSettings* correctReadini{};

	// X轴校正系数
	double ratioX{};

	// Y轴校正系数
	double ratioY{};

	// 判断计算x,y其中哪个比例
	bool WhichButton{};

private:
	// 关闭窗口事件
	void closeEvent(QCloseEvent* event);

public slots:
	// 计算比例值
	void on_GetProportion_clicked();

signals:
	// 发送比例值
	void sendProport(double Proport);

private:
	Ui::calaRatio ui;
};
