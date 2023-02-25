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
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����б��ͷ
	void SetTableHeader();

	// �����б����
	void SetTables();

	// ���һ��
	void appendOneRow(QString DataKey, QString DataValue);

	// ���һ��
	void appendOneRows(QString DataKey);

private:
	Ui::SystemInfo ui;
};
