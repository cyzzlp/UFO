#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_laserSet.h"

class laserSet : public QDialog
{
	Q_OBJECT

public:
	laserSet(QWidget *parent = nullptr);
	~laserSet();

private:
	// ����������
	int LaserType{};

	// Ԥ����
	int Standby{};

	// Ԥ����Ƶ��
	float StandbyFrequency{};

	// Ԥ����ռ�ձ�
	float StandbyPulseWidth{};

private:
	// �����ļ�
	QSettings* laserset{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_GetLaserSetting_clicked();

	// �رս���
	void on_CancelLaserSetting_clicked();

private:
	Ui::laserSet ui;
};
