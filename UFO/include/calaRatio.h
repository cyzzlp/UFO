#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_calaRatio.h"

class calaRatio : public QDialog
{
	Q_OBJECT

public:
	calaRatio(QWidget *parent = nullptr);
	~calaRatio();

private:
	// ��ȡ����
	QSettings* correctReadini{};

	// X��У��ϵ��
	double ratioX{};

	// Y��У��ϵ��
	double ratioY{};

	// �жϼ���x,y�����ĸ�����
	bool WhichButton{};

private:
	// �رմ����¼�
	void closeEvent(QCloseEvent* event);

public slots:
	// �������ֵ
	void on_GetProportion_clicked();

signals:
	// ���ͱ���ֵ
	void sendProport(double Proport);

private:
	Ui::calaRatio ui;
};
