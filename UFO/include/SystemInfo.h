#pragma once

#include <QDialog>
#include <QLabel>
#include "ui_SystemInfo.h"

class SystemInfo : public QDialog
{
	Q_OBJECT

public:
	SystemInfo(QWidget *parent = nullptr);
	~SystemInfo();

private:
	//  各字段在表格中的列号
	enum FieldColNum { colx = 0, coly };

	//状态栏上用于显示单元格的行号、列号
	QLabel* labCellIndex{};

private:
	// 设置列表表头
	void SetTableHeader();

	// 设置行数,设置的行数为数据区的行数，不含表头
	void SetTablesSize();

private:
	Ui::SystemInfo ui;
};
