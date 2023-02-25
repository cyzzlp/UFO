#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_MarkCorrType.h"

class MarkCorrType : public QDialog
{
	Q_OBJECT

public:
	MarkCorrType(QWidget *parent = nullptr);
	~MarkCorrType();

private:
	// У������
	bool fixWay{};

	// �����ɺ����ʼ��
	bool firstZero{};

private:
	// �����ļ�
	QSettings* corrWay{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_getCorrWay_clicked();

	// �رս���
	void on_cancelCorrWay_clicked();

private:
	Ui::MarkCorrType ui;
};
