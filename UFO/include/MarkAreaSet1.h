#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "calaRatio.h"
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
	double ratioX{};

	// Y��У��ϵ��
	double ratioY{};

	// Z��У��ϵ��
	double ratioZ{};

	// ����У���ļ�
	QString CorrectionShowPath{};

private:
	// �����ļ�
	QSettings* correctRead{};

	// ��������
	calaRatio* calaR{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_GetMarkAreaSetting_clicked();

	// �رս���
	void on_CancelMarkAreaSetting_clicked();

	// ����x����
	void on_clxpBtn_clicked();

	// ����y����
	void on_clypBtn_clicked();

	// ���ñ����ؼ�ֵ
	void SetxSpinBoxValue(double Proport);

	// ���ñ����ؼ�ֵ
	void SetySpinBoxValue(double Proport);

private:
	Ui::MarkAreaSet1 ui;
};
