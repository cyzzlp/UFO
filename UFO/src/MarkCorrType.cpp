#include "MarkCorrType.h"

MarkCorrType::MarkCorrType(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ�����ļ�
	QString m_FileName = QCoreApplication::applicationDirPath() + "/correctWayRead.ini";
	corrWay = new QSettings(m_FileName, QSettings::IniFormat);

	// ��ȡ����
	fixWay = corrWay->value("fixWay").toBool();
	firstZero = corrWay->value("firstZero").toBool();

	// ��ʼ������
	if (!fixWay)
	{
		ui.funcWay->setChecked(!fixWay);
	}

	if (fixWay)
	{
		ui.tabWay->setChecked(fixWay);
	}

	if (!firstZero)
	{
		ui.axisDataZero->setChecked(!firstZero);
	}

	if (firstZero)
	{
		ui.markDataZero->setChecked(firstZero);
	}
}

MarkCorrType::~MarkCorrType()
{

}

//�رմ����¼�
void MarkCorrType::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����û�����
void MarkCorrType::on_getCorrWay_clicked()
{
	if (ui.funcWay->isChecked())
		fixWay = false;

	if (ui.tabWay->isChecked())
		fixWay = true;

	if (ui.axisDataZero->isChecked())
		firstZero = false;

	if (ui.markDataZero->isChecked())
		firstZero = true;

	// ��������
	corrWay->setValue("fixWay", fixWay);
	corrWay->setValue("firstZero", firstZero);
	corrWay->sync();
	delete corrWay;

	// ����ر�
	this->close();
}

// �رս���
void MarkCorrType::on_cancelCorrWay_clicked()
{
	this->close();
}
