#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_MarkAreaSet1.h"

class MarkAreaSet1 : public QDialog
{
	Q_OBJECT

public:
	MarkAreaSet1(QWidget *parent = nullptr);
	~MarkAreaSet1();

private:
	// X��̷�Χ
	double xRange{};

	// Y��̷�Χ
	double yRange{}; 
	
	// XY����
	bool ExchangeXY{};

	// X����
	bool InvertX{};

	// Y����
	bool InvertY{};

	// X��У��ϵ��
	double XCorrection{};

	// Y��У��ϵ��
	double YCorrection{};

	// Z��У��ϵ��
	double ZCorrection{};

	// ����У���ļ�
	QString CorrectionShowPath{};

private:
	// �����ļ�
	QSettings* correctRead{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_GetMarkAreaSetting_clicked();

	// �رս���
	void on_CancelMarkAreaSetting_clicked();

private:
	Ui::MarkAreaSet1 ui;
};
