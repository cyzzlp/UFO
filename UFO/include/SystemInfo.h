#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QLabel>
#include "MarkData.h"
#include "ui_SystemInfo.h"

class SystemInfo : public QDialog
{
	Q_OBJECT

public:
	SystemInfo(QWidget *parent = nullptr);
	~SystemInfo();

private:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 设置列表表头
	void SetTableHeader();

	// 设置列表参数
	void SetTables();

	// 添加一行
	void appendOneRow(QString DataKey, QString DataValue);

	// 添加一行
	void appendOneRows(QString DataKey);

private:
	Ui::SystemInfo ui;
};
