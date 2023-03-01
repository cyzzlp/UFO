#include "calaRatio.h"

calaRatio::calaRatio(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// �������ÿؼ���ֵ��ʼ��
	ui.ProportionIn1->setValue(1);
	ui.ProportionIn2->setValue(1);
}

calaRatio::~calaRatio()
{

}

// �������ֵ
void calaRatio::on_GetProportion_clicked()
{
	double input1 = ui.ProportionIn1->value();
	double input2 = ui.ProportionIn2->value();

	// ����ó��ı���
	double ProportIn = input1 / input2;

	emit sendProport(ProportIn);

	// �رմ���
	this->close();
}

// �رմ����¼�
void calaRatio::closeEvent(QCloseEvent* event)
{
	delete this;
}