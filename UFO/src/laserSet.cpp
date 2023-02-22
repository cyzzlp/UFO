#include "laserSet.h"

laserSet::laserSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 读取配置文件
	QString m_FileName = QCoreApplication::applicationDirPath() + "/laserSetting.ini";
	laserset = new QSettings(m_FileName, QSettings::IniFormat);

	// 读取文件
	LaserType = laserset->value("LaserType").toInt();
	Standby = laserset->value("Standby").toInt();
	StandbyFrequency = laserset->value("Standby").toFloat();
	StandbyPulseWidth = laserset->value("Standby").toFloat();

	// 初始化界面
	switch (LaserType)
	{
	case 0:
		ui.YAGSettingrBtn->setChecked(true);

	case 1:
		ui.CO2SettingrBtn->setChecked(true);

	case 2:
		ui.FIBER1SettingrBtn->setChecked(true);

	case 3:
		ui.FIBER2SettingrBtn->setChecked(true);
	}

	ui.StandbySpBox->setValue(Standby);
	ui.FrequencySpBox->setValue(StandbyFrequency);
	ui.PluseWidthSpBox->setValue(StandbyPulseWidth);
}

laserSet::~laserSet()
{

}

//关闭窗口事件
void laserSet::closeEvent(QCloseEvent* event)
{
	delete this;
}

// 保存用户设置
void laserSet::on_GetLaserSetting_clicked()
{
	Standby = ui.StandbySpBox->value();
	StandbyFrequency = ui.FrequencySpBox->value();
	StandbyPulseWidth = ui.PluseWidthSpBox->value();

	if (ui.YAGSettingrBtn->isChecked())
		LaserType = 0;

	if (ui.CO2SettingrBtn->isChecked())
		LaserType = 1;

	if (ui.FIBER1SettingrBtn->isChecked())
		LaserType = 2;

	if (ui.FIBER2SettingrBtn->isChecked())
		LaserType = 3;

	laserset->setValue("LaserType", LaserType);
	laserset->setValue("Standby", Standby);
	laserset->setValue("StandbyFrequency", StandbyFrequency);
	laserset->setValue("StandbyPulseWidth", StandbyPulseWidth);

	// 保存配置
	laserset->sync();
	delete laserset;

	this->close();
}

// 关闭界面
void laserSet::on_CancelLaserSetting_clicked()
{
	this->close();
}
