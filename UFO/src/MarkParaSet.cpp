#include "MarkParaSet.h"

MarkParaSet::MarkParaSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// �����ʺ�ComBox
	QList<int> pen_index;
	for (int i = 0; i <= 255; i++)
	{
		pen_index.insert(i, i);
	}

	ui.indexPara->clear();
	foreach(int i, pen_index)
	{
		QString Str = QString::number(i);
		ui.indexPara->addItem(Str, i);
	}

	// ��ȡ�����ļ�
	QString m_FileName = QCoreApplication::applicationDirPath() + "/systemSetting.ini";
	systemSet = new QSettings(m_FileName, QSettings::IniFormat);

	// ��ȡ����
	index = systemSet->value("INDEX").toInt();
	markCount = systemSet->value("markCounts").toInt();
	markSpeed = systemSet->value("markSpeed").toFloat();
	jumpSpeed = systemSet->value("jumpSpeed").toFloat();
	jumpDelay = systemSet->value("jumpDelay").toFloat();
	laserOnDelay = systemSet->value("laserOnDelay").toFloat();
	laserOffDelay = systemSet->value("laserOffDelay").toFloat();
	polygonDelay = systemSet->value("polygonDelay").toFloat();
	current = systemSet->value("current").toFloat();
	laserFrequency = systemSet->value("laserFrequency").toFloat();
	pulseWidth = systemSet->value("pulseWidth").toFloat();
	firstPulseWidth = systemSet->value("firstPulseWidth").toFloat();
	polygonKillerTime = systemSet->value("polygonKillerTime").toFloat();
	firstPulseKillerLength = systemSet->value("firstPulseKillerLength").toFloat();
	incrementStep = systemSet->value("incrementStep").toFloat();
	dotSpace = systemSet->value("dotSpace").toFloat();
	isBitmap = systemSet->value("isBitmap").toBool();

	// ��ʼ������
	ui.indexPara->setCurrentIndex(index);
	ui.markCountsPara->setValue(markCount);
	ui.markSpeedPara->setValue(markSpeed);
	ui.jumpSpeedPara->setValue(jumpSpeed);
	ui.jumpDelayPara->setValue(jumpDelay);
	ui.laserOnDelayPara->setValue(laserOnDelay);
	ui.laserOffDelayPara->setValue(laserOffDelay);
	ui.polygonDelayPara->setValue(polygonDelay);
	ui.currentPara->setValue(current);
	ui.laserFrequencyPara->setValue(laserFrequency);
	ui.pulseWidthPara->setValue(pulseWidth);
	ui.firstPulseWidthPara->setValue(firstPulseWidth);
	ui.polygonKillerTimePara->setValue(polygonKillerTime);
	ui.firstPulseKillerLengthPara->setValue(firstPulseKillerLength);
	ui.incrementStepPara->setValue(incrementStep);
	ui.dotSpacePara->setValue(dotSpace);
	ui.isBitmapPara->setChecked(isBitmap);
}

MarkParaSet::~MarkParaSet()
{

}

//�رմ����¼�
void MarkParaSet::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����û�����
void MarkParaSet::on_GetMarkParaSetting_clicked()
{
	// ��ȡ��������
	index = ui.indexPara->currentIndex();
	markCount = ui.markCountsPara->value();
	markSpeed = ui.markSpeedPara->value();
	jumpSpeed = ui.jumpSpeedPara->value();
	jumpDelay = ui.jumpDelayPara->value();
	laserOnDelay = ui.laserOnDelayPara->value();
	laserOffDelay = ui.laserOffDelayPara->value();
	polygonDelay = ui.polygonDelayPara->value();
	current = ui.currentPara->value();
	laserFrequency = ui.laserFrequencyPara->value();
	pulseWidth = ui.pulseWidthPara->value();
	firstPulseWidth = ui.firstPulseWidthPara->value();
	polygonKillerTime = ui.polygonKillerTimePara->value();
	firstPulseKillerLength = ui.firstPulseKillerLengthPara->value();
	incrementStep = ui.incrementStepPara->value();
	dotSpace = ui.dotSpacePara->value();
	isBitmap = ui.isBitmapPara->isChecked();

	// ��������
	systemSet->setValue("INDEX", index);
	systemSet->setValue("markCounts", markCount);
	systemSet->setValue("markSpeed", markSpeed);
	systemSet->setValue("jumpSpeed", jumpSpeed);
	systemSet->setValue("jumpDelay", jumpDelay);
	systemSet->setValue("laserOnDelay", laserOnDelay);
	systemSet->setValue("laserOffDelay", laserOffDelay);
	systemSet->setValue("polygonDelay", polygonDelay);
	systemSet->setValue("current", current);
	systemSet->setValue("laserFrequency", laserFrequency);
	systemSet->setValue("pulseWidth", pulseWidth);
	systemSet->setValue("firstPulseWidth", firstPulseWidth);
	systemSet->setValue("polygonKillerTime", polygonKillerTime);
	systemSet->setValue("firstPulseKillerLength", firstPulseKillerLength);
	systemSet->setValue("incrementStep", incrementStep);
	systemSet->setValue("dotSpace", dotSpace);
	systemSet->setValue("isBitmap", isBitmap);

	// ���������ļ�
	systemSet->sync();
	delete systemSet;

	// �رմ���
	this->close();
}

// �رս���
void MarkParaSet::on_CancelMarkParaSetting_clicked()
{
	// �رմ���
	this->close();
}