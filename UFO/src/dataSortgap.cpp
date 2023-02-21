#include "dataSortgap.h"

dataSortgap::dataSortgap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 读取配置文件
	gapInput = new QSettings("gapSetting.ini", QSettings::IniFormat);

	// 读取设置
	xGap = gapInput->value("xGap").toDouble();
	yGap = gapInput->value("yGap").toDouble();
	dataType = gapInput->value("dataType", 0).toInt();

	// 初始化界面
	ui.dspGapx->setValue(xGap);
	ui.dspGapy->setValue(yGap);
	ui.dataXY->setChecked(dataType);
	ui.dataXYZ->setChecked(!dataType);
}

dataSortgap::~dataSortgap()
{

}
