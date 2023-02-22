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
	bool dataType{};

private:
	// �����ļ�
	QSettings* gapInput{};

private slots:
	//�رմ����¼�
	void closeEvent(QCloseEvent* event);

	// �����û�����
	void on_getGapbtn_clicked();

	// �رս���
	void on_cancelGapbtn_clicked();

signals:
	// ���Ͱ���ȷ���ź�
	void isPushed();

private:
	Ui::dataSortgap ui;
};
