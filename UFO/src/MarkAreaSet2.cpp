#include "MarkAreaSet2.h"

MarkAreaSet2::MarkAreaSet2(QWidget *parent)
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
	xcorrections = correctRead->value("Xcorrections").toDouble();
	ycorrections = correctRead->value("Ycorrections").toDouble();
	xshear = correctRead->value("Xshear").toDouble();
	yshear = correctRead->value("Yshear").toDouble();
	xladder = correctRead->value("Xladder").toDouble();
	yladder = correctRead->value("Yladder").toDouble();
	startmarkmode = correctRead->value("Startmarkmode").toBool();

	// ��ʼ������
	ui.xrange->setValue(xRange);
	ui.yrange->setValue(yRange);
	ui.exchangeXY->setChecked(ExchangeXY);
	ui.invertX->setChecked(InvertX);
	ui.invertY->setChecked(InvertY);
	ui.xCorrectionSpBox->setValue(XCorrection);
	ui.yCorrectionSpBox->setValue(YCorrection);
	ui.zCorrectionSpBox->setValue(ZCorrection);
	ui.xcorrections->setValue(xcorrections);
	ui.ycorrections->setValue(ycorrections);
	ui.xshear->setValue(xshear);
	ui.yshear->setValue(yshear);
	ui.xladder->setValue(xladder);
	ui.yladder->setValue(yladder);
	ui.startmarkmode->setChecked(startmarkmode);
}

MarkAreaSet2::~MarkAreaSet2()
{

}

//�رմ����¼�
void MarkAreaSet2::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����û�����
void MarkAreaSet2::on_GetMarkAreaSetting2_clicked()
{
	// ��ȡ�û�����
	xRange = ui.xrange->value();
	yRange = ui.yrange->value();
	ExchangeXY = ui.invertX->isChecked();
	InvertX = ui.invertX->isChecked();
	InvertY = ui.invertY->isChecked();
	XCorrection = ui.xCorrectionSpBox->value();
	YCorrection = ui.yCorrectionSpBox->value();
	ZCorrection = ui.zCorrectionSpBox->value();
	xcorrections = ui.xcorrections->value();
	ycorrections = ui.ycorrections->value();
	xshear = ui.xshear->value();
	yshear = ui.yshear->value();
	xladder = ui.xladder->value();
	yladder = ui.yladder->value();
	startmarkmode = ui.startmarkmode->isChecked();

	correctRead->setValue("xRange", xRange);
	correctRead->setValue("yRange", yRange);
	correctRead->setValue("ExchangeXY", ExchangeXY);
	correctRead->setValue("InvertX", InvertX);
	correctRead->setValue("InvertY", InvertY);
	correctRead->setValue("XCorrection", XCorrection);
	correctRead->setValue("YCorrection", YCorrection);
	correctRead->setValue("ZCorrection", ZCorrection);
	correctRead->setValue("Xcorrections", xcorrections);
	correctRead->setValue("Ycorrections", ycorrections);
	correctRead->setValue("Xshear", xshear);
	correctRead->setValue("Yshear", yshear);
	correctRead->setValue("Xladder", xladder);
	correctRead->setValue("Yladder", yladder);
	correctRead->setValue("Startmarkmode", startmarkmode);
	correctRead->setValue("CorrectFile", 1);

	correctRead->sync();
	delete correctRead;



	// �رմ���
	this->close();
}

// �رս���
void MarkAreaSet2::on_CancelMarkAreaSetting2_clicked()
{
	// �رմ���
	this->close();
}
