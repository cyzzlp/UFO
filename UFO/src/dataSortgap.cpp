#include "dataSortgap.h"

dataSortgap::dataSortgap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 读取配置文件
	QString m_FileName = QCoreApplication::applicationDirPath() + "/gapSetting.ini";
	gapInput = new QSettings(m_FileName, QSettings::IniFormat);

	// 读取设置
	xGap = gapInput->value("xGap").toDouble();
	yGap = gapInput->value("yGap").toDouble();
	dataType = gapInput->value("dataType").toBool();

	// 初始化界面
	ui.dspGapx->setValue(xGap);
	ui.dspGapy->setValue(yGap);
	ui.dataXYZ->setChecked(!dataType);
	ui.dataXY->setChecked(dataType);
}

dataSortgap::~dataSortgap()
{

}

//关闭窗口事件
void dataSortgap::closeEvent(QCloseEvent* event)
{
	delete this;
}

// 保存用户设置
void dataSortgap::on_getGapbtn_clicked()
{
	xGap = ui.dspGapx->value();
	yGap = ui.dspGapy->value();

	if (ui.dataXYZ->isChecked())
		dataType = false;

	if (ui.dataXY->isChecked())
		dataType = true;

	gapInput->setValue("xGap", xGap);
	gapInput->setValue("yGap", yGap);
	gapInput->setValue("dataType", dataType);

	// 保存配置
	gapInput->sync();
	delete gapInput;

	// 发送按键确认信号
	emit isPushed();

	// 界面关闭
	this->close();
}

// 关闭界面
void dataSortgap::on_cancelGapbtn_clicked()
{
	// 界面关闭
	this->close();
}