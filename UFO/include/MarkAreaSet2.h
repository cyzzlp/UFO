#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "calaRatio.h"
#include "ui_MarkAreaSet2.h"

class MarkAreaSet2 : public QDialog
{
	Q_OBJECT

public:
	MarkAreaSet2(QWidget *parent = nullptr);
	~MarkAreaSet2();

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

	// X��ʧ��У��ϵ��
	double xcorrections{};

	// Y��ʧ��У��ϵ��
	double ycorrections{};

	// X���б�У��ϵ��
	double xshear{};

	// Y���б�У��ϵ��
	double yshear{};

	// X������У��ϵ��
	double xladder{};

	// Y������У��ϵ��
	double yladder{};

	// �¼�����
	int startmarkmode{};

	// ����У���ļ�
	// correctFile

private:
	// �����ļ�
	QSettings* correctRead{};

	// ��������
	calaRatio* calaR{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_GetMarkAreaSetting2_clicked();

	// �رս���
	void on_CancelMarkAreaSetting2_clicked();

	// ����x����ϵ��
	void on_clxpBtn_clicked();

	// ����y����ϵ��
	void on_clypBtn_clicked();

	// ���ñ����ؼ�ֵ
	void SetxSpinBoxValue(double Proport);

	// ���ñ����ؼ�ֵ
	void SetySpinBoxValue(double Proport);


private:
	Ui::MarkAreaSet2 ui;
};
