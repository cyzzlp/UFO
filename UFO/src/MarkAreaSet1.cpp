#include "MarkAreaSet1.h"

MarkAreaSet1::MarkAreaSet1(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ�����ļ�
	QString m_FileName = QCoreApplication::applicationDirPath() + "/correctSetting.ini";
	correctRead = new QSettings(m_FileName, QSettings::IniFormat);

	// ��ȡ����
	xRange = correctRead->value("xRange").toDouble();
	yRange = correctRead->value("yRange").toDouble();
	ExchangeXY = correctRead->value("ExchangeXY").toBool();
	InvertX = correctRead->value("InvertX").toBool();
	InvertY = correctRead->value("InvertY").toBool();
	XCorrection = correctRead->value("XCorrection").toDouble();
	YCorrection = correctRead->value("YCorrection").toDouble();
	ZCorrection = correctRead->value("ZCorrection").toDouble();
	CorrectionShowPath = correctRead->value("CorrectionShowPath").toString();

	// ��ʼ������
	ui.xrange->setValue(xRange);
	ui.yrange->setValue(yRange);
	ui.exchangeXY->setChecked(ExchangeXY);
	ui.invertX->setChecked(InvertX);
	ui.invertY->setChecked(InvertY);
	ui.xCorrectionSpBox->setValue(XCorrection);
	ui.yCorrectionSpBox->setValue(YCorrection);
	ui.zCorrectionSpBox->setValue(ZCorrection);
	ui.CorrectionShowPath->setText(CorrectionShowPath);
}

MarkAreaSet1::~MarkAreaSet1()
{

}

//�رմ����¼�
void MarkAreaSet1::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����û�����
void MarkAreaSet1::on_GetMarkAreaSetting_clicked()
{
	xRange = ui.xrange->value();
	xRange = ui.xrange->value();
	ExchangeXY = ui.exchangeXY->isChecked();
	InvertX = ui.invertX->isChecked();
	InvertY = ui.invertY->isChecked();
	XCorrection = ui.xCorrectionSpBox->value();
	YCorrection = ui.yCorrectionSpBox->value();
	ZCorrection = ui.zCorrectionSpBox->value();
	CorrectionShowPath = ui.CorrectionShowPath->text();

	// ��������
	correctRead->setValue("xRange", 110);
	correctRead->setValue("yRange", 110);
	correctRead->setValue("ExchangeXY", false);
	correctRead->setValue("InvertX", false);
	correctRead->setValue("InvertY", false);
	correctRead->setValue("XCorrection", 1);
	correctRead->setValue("YCorrection", 1);
	correctRead->setValue("ZCorrection", 1);
	correctRead->setValue("CorrectionShowPath", "please choose a file Path!");
	correctRead->sync();
	delete correctRead;

	// �رմ���
	this->close();
}

// �رս���
void MarkAreaSet1::on_CancelMarkAreaSetting_clicked()
{
	this->close();
}
