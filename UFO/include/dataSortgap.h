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
	// xԤ����
	double xGap{};

	// yԤ����
	double yGap{};

	// ��������
	int dataType{};

private:
	// �����ļ�
	QSettings* gapInput{};

private:
	Ui::dataSortgap ui;
};
