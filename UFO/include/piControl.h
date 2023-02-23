#pragma once

#include <QDialog>
#include <QSettings>
#include "PI_GCS2_DLL_dynamicp_loader.h"
#include "ui_piControl.h"

class piControl : public QDialog
{
	Q_OBJECT

public:
	piControl(QWidget *parent = nullptr);
	~piControl();

private:
	// ��¼�������
	int ID{};

	// ��¼���ӵ�PI�ƶ���
	char szAxes[2]{};

	// ��¼���ӵ�PI�ƶ���
	QString szAxe[1]{};

	// ���� USB �豸������ szBuffer ������
	char szBuffer[17]{};

	// ���������������ƥ��Ŀ������ڻ������з���
	char szFilter[17]{};

	// ���ص��ַ���,�������кź��豸������
	char serialNo[256]{};

	// ������
	int iError{};

	// ������ʾ
	char szErrorMesage[1024]{};

	// ��ȴ�
	BOOL bIsMoving[3]{};

	BOOL returnValue{};

	// PI�ƶ�λ��
	double dPos[3]{};

	// PI����
	bool P_IsConnect{};

private:
	// ��ȡPI��Ϣ
	QSettings* piInfo{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// ����PI
	void on_ConnectPi_clicked();

private:
	Ui::piControl ui;
};
