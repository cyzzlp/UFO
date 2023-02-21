#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_dataSortgap.h"

class dataSortgap : public QDialog
{
	Q_OBJECT

public:
	dataSortgap(QWidget *parent = nullptr);
	~dataSortgap();

private:
	// x预设间隔
	double xGap{};

	// y预设间隔
	double yGap{};

	// 数据类型
	int dataType{};

private:
	// 配置文件
	QSettings* gapInput{};

private:
	Ui::dataSortgap ui;
};
