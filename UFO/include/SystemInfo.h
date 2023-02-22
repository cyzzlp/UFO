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
	//  ���ֶ��ڱ���е��к�
	enum FieldColNum { colx = 0, coly };

	//״̬����������ʾ��Ԫ����кš��к�
	QLabel* labCellIndex{};

private:
	// �����б��ͷ
	void SetTableHeader();

	// ��������,���õ�����Ϊ��������������������ͷ
	void SetTablesSize();

private:
	Ui::SystemInfo ui;
};
