#include "MarkCorrType.h"

MarkCorrType::MarkCorrType(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 读取配置文件
	QString m_FileName = QCoreApplication::applicationDirPath() + "/correctWayRead.ini";
	corrWay = new QSettings(m_FileName, QSettings::IniFormat);

	// 读取设置
	fixWay = corrWay->value("fixWay").toBool();
	firstZero = corrWay->value("firstZero").toBool();

	// 初始化界面
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

//关闭窗口事件
void MarkCorrType::closeEvent(QCloseEvent* event)
{
	delete this;
}

// 保存用户设置
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

	// 保存配置
	corrWay->setValue("fixWay", fixWay);
	corrWay->setValue("firstZero", firstZero);
	corrWay->sync();
	delete corrWay;

	// 界面关闭
	this->close();
}

// 关闭界面
void MarkCorrType::on_cancelCorrWay_clicked()
{
	this->close();
}
