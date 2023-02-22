#pragma once

#include <QDialog>
#include <QSettings>
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
	double XCorrection{};

	// Y��У��ϵ��
	double YCorrection{};

	// Z��У��ϵ��
	double ZCorrection{};

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
	double startmarkmode{};

	// ����У���ļ�
	// correctFile

private:
	// �����ļ�
	QSettings* correctRead{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_GetMarkAreaSetting2_clicked();

	// �رս���
	void on_CancelMarkAreaSetting2_clicked();

private:
	Ui::MarkAreaSet2 ui;
};
