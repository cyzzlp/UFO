#include "MarkAreaSet1.h"

MarkAreaSet1::MarkAreaSet1(QWidget *parent)
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
	InvertX = correctRead->value("invertY").toBool();
	InvertY = correctRead->value("InvertY").toBool();
	ratioX = correctRead->value("ratioX").toDouble();
	ratioY = correctRead->value("ratioY").toDouble();
	ratioZ = correctRead->value("ratioZ").toDouble();
	CorrectionShowPath = correctRead->value("filePath").toString();

	// ��ʼ������
	ui.xrange->setValue(xRange);
	ui.yrange->setValue(yRange);
	ui.exchangeXY->setChecked(ExchangeXY);
	ui.invertX->setChecked(InvertX);
	ui.invertY->setChecked(InvertY);
	ui.xCorrectionSpBox->setValue(ratioX);
	ui.yCorrectionSpBox->setValue(ratioY);
	ui.zCorrectionSpBox->setValue(ratioZ);
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
	ratioX = ui.xCorrectionSpBox->value();
	ratioY = ui.yCorrectionSpBox->value();
	ratioZ = ui.zCorrectionSpBox->value();
	CorrectionShowPath = ui.CorrectionShowPath->text();

	// ��������
	correctRead->setValue("rangeX", xRange);
	correctRead->setValue("rangeY", xRange);
	correctRead->setValue("exchangeXY", ExchangeXY);
	correctRead->setValue("invertX", InvertX);
	correctRead->setValue("invertY", InvertY);
	correctRead->setValue("ratioX", ratioX);
	correctRead->setValue("ratioY", ratioX);
	correctRead->setValue("ratioZ", ratioX);
	correctRead->setValue("filePath", CorrectionShowPath);
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

// ����x����ı���
void MarkAreaSet1::on_clxpBtn_clicked()
{
	calaR = new calaRatio();
	calaR->setWindowModality(Qt::ApplicationModal);
	calaR->setFixedSize(calaR->width(), calaR->height());
	calaR->show();

	connect(calaR, &calaRatio::sendProport, this, &MarkAreaSet1::SetxSpinBoxValue);
}

// ����y����ı���
void MarkAreaSet1::on_clypBtn_clicked()
{
	calaR = new calaRatio();
	calaR->setWindowModality(Qt::ApplicationModal);
	calaR->setFixedSize(calaR->width(), calaR->height());
	calaR->show();

	connect(calaR, &calaRatio::sendProport, this, &MarkAreaSet1::SetySpinBoxValue);
}

// ���ñ����ؼ�ֵ
void MarkAreaSet1::SetxSpinBoxValue(double Proport)
{
	ui.xCorrectionSpBox->setValue(Proport);
}

// ���ñ����ؼ�ֵ
void MarkAreaSet1::SetySpinBoxValue(double Proport)
{
	ui.yCorrectionSpBox->setValue(Proport);
}