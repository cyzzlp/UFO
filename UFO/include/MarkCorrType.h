#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_MarkCorrType.h"

class MarkCorrType : public QDialog
{
	Q_OBJECT

public:
	MarkCorrType(QWidget *parent = nullptr);
	~MarkCorrType();

private:
	// 校正方法
	bool fixWay{};

	// 标刻完成后的起始点
	bool firstZero{};

private:
	// 配置文件
	QSettings* corrWay{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_getCorrWay_clicked();

	// 关闭界面
	void on_cancelCorrWay_clicked();

private:
	Ui::MarkCorrType ui;
};
