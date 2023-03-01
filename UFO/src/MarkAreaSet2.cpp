#include "MarkAreaSet2.h"

MarkAreaSet2::MarkAreaSet2(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ�����ļ�
	QString m_FileName = QCoreApplication::applicationDirPath() + "/correctSetting.ini";
	correctRead = new QSettings(m_FileName, QSettings::IniFormat);

	// ��ȡ����
	xRange = correctRead->value("rangeX").toDouble();
	yRange = correctRead->value("rangeY").toDouble();
	ExchangeXY = correctRead->value("exchangeXY").toBool();
	InvertX = correctRead->value("invertX").toBool();
	InvertY = correctRead->value("invertY").toBool();
	ratioX = correctRead->value("ratioX").toDouble();
	ratioY = correctRead->value("ratioY").toDouble();
	ratioZ = correctRead->value("ratioZ").toDouble();
	xcorrections = correctRead->value("xCorrection").toDouble();
	ycorrections = correctRead->value("yCorrection").toDouble();
	xshear = correctRead->value("xShear").toDouble();
	yshear = correctRead->value("yShear").toDouble();
	xladder = correctRead->value("xLadder").toDouble();
	yladder = correctRead->value("yLadder").toDouble();
	startmarkmode = correctRead->value("startMarkMode").toBool();

	// ��ʼ������
	ui.xrange->setValue(xRange);
	ui.yrange->setValue(yRange);
	ui.exchangeXY->setChecked(ExchangeXY);
	ui.invertX->setChecked(InvertX);
	ui.invertY->setChecked(InvertY);
	ui.xCorrectionSpBox->setValue(ratioX);
	ui.yCorrectionSpBox->setValue(ratioY);
	ui.zCorrectionSpBox->setValue(ratioZ);
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
	ratioX = ui.xCorrectionSpBox->value();
	ratioY = ui.yCorrectionSpBox->value();
	ratioZ = ui.zCorrectionSpBox->value();
	xcorrections = ui.xcorrections->value();
	ycorrections = ui.ycorrections->value();
	xshear = ui.xshear->value();
	yshear = ui.yshear->value();
	xladder = ui.xladder->value();
	yladder = ui.yladder->value();
	startmarkmode = ui.startmarkmode->isChecked();

	correctRead->setValue("rangeX", xRange);
	correctRead->setValue("rangeY", yRange);
	correctRead->setValue("exchangeXY", ExchangeXY);
	correctRead->setValue("invertX", InvertX);
	correctRead->setValue("invertY", InvertY);
	correctRead->setValue("ratioX", ratioX);
	correctRead->setValue("ratioY", ratioY);
	correctRead->setValue("ratioZ", ratioZ);
	correctRead->setValue("xCorrection", xcorrections);
	correctRead->setValue("yCorrection", ycorrections);
	correctRead->setValue("xShear", xshear);
	correctRead->setValue("yShear", yshear);
	correctRead->setValue("xLadder", xladder);
	correctRead->setValue("yLadder", yladder);
	correctRead->setValue("startMarkMode", startmarkmode);
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

// ����x����ı���
void MarkAreaSet2::on_clxpBtn_clicked()
{
	calaR = new calaRatio();
	calaR->setWindowModality(Qt::ApplicationModal);
	calaR->setFixedSize(calaR->width(), calaR->height());
	calaR->show();

	connect(calaR, &calaRatio::sendProport, this, &MarkAreaSet2::SetxSpinBoxValue);
}

// ����y����ı���
void MarkAreaSet2::on_clypBtn_clicked()
{
	calaR = new calaRatio();
	calaR->setWindowModality(Qt::ApplicationModal);
	calaR->setFixedSize(calaR->width(), calaR->height());
	calaR->show();

	connect(calaR, &calaRatio::sendProport, this, &MarkAreaSet2::SetySpinBoxValue);
}

// ���ñ����ؼ�ֵ
void MarkAreaSet2::SetxSpinBoxValue(double Proport)
{
	ui.xCorrectionSpBox->setValue(Proport);
}

// ���ñ����ؼ�ֵ
void MarkAreaSet2::SetySpinBoxValue(double Proport)
{
	ui.yCorrectionSpBox->setValue(Proport);
}