#include "calaRatio.h"

calaRatio::calaRatio(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 比例设置控件数值初始化
	ui.ProportionIn1->setValue(1);
	ui.ProportionIn2->setValue(1);
}

calaRatio::~calaRatio()
{

}

// 计算比例值
void calaRatio::on_GetProportion_clicked()
{
	double input1 = ui.ProportionIn1->value();
	double input2 = ui.ProportionIn2->value();

	// 计算得出的比例
	double ProportIn = input1 / input2;

	emit sendProport(ProportIn);

	// 关闭窗口
	this->close();
}

// 关闭窗口事件
void calaRatio::closeEvent(QCloseEvent* event)
{
	delete this;
}