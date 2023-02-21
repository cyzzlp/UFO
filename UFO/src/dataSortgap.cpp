#include "dataSortgap.h"

dataSortgap::dataSortgap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ�����ļ�
	gapInput = new QSettings("gapSetting.ini", QSettings::IniFormat);

	// ��ȡ����
	xGap = gapInput->value("xGap").toDouble();
	yGap = gapInput->value("yGap").toDouble();
	dataType = gapInput->value("dataType", 0).toInt();

	// ��ʼ������
	ui.dspGapx->setValue(xGap);
	ui.dspGapy->setValue(yGap);
	ui.dataXY->setChecked(dataType);
	ui.dataXYZ->setChecked(!dataType);
}

dataSortgap::~dataSortgap()
{

}
