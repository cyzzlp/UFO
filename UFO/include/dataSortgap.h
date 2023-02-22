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
	bool dataType{};

private:
	// 配置文件
	QSettings* gapInput{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_getGapbtn_clicked();

	// 关闭界面
	void on_cancelGapbtn_clicked();

signals:
	// 发送按键确认信号
	void isPushed();

private:
	Ui::dataSortgap ui;
};
