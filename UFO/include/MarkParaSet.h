#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_MarkParaSet.h"

class MarkParaSet : public QDialog
{
	Q_OBJECT

public:
	MarkParaSet(QWidget *parent = nullptr);
	~MarkParaSet();

private:
    // �ʺ�
    int index{};

    // ��̴���
    int markCount{};

    // ����ٶ�
    float markSpeed{};

    // ��ת�ٶ�
    float jumpSpeed{};

    // ��ת��ʱ
    float jumpDelay{};

    // ������ʱ
    float laserOnDelay{};

    // �ع���ʱ
    float laserOffDelay{};

    // �յ���ʱ
    float polygonDelay{};

    // ����
    float current{};

    // ����Ƶ��
    float laserFrequency{};

    // ������
    float pulseWidth{};

    // ���������ƿ��
    float firstPulseWidth{};

    // �յ�����ʱ��
    float polygonKillerTime{};

    // YAG��������
    float firstPulseKillerLength{};

    // CO2������������
    float incrementStep{};

    // ����
    float dotSpace{};

    // �Ƿ���λͼ
    bool isBitmap{};

private:
	// �����ļ�
	QSettings* systemSet{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_GetMarkParaSetting_clicked();

	// �رս���
	void on_CancelMarkParaSetting_clicked();

private:
	Ui::MarkParaSet ui;
};
