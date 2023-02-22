#include "laserSet.h"

laserSet::laserSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ�����ļ�
	QString m_FileName = QCoreApplication::applicationDirPath() + "/laserSetting.ini";
	laserset = new QSettings(m_FileName, QSettings::IniFormat);

	// ��ȡ�ļ�
	LaserType = laserset->value("LaserType").toInt();
	Standby = laserset->value("Standby").toInt();
	StandbyFrequency = laserset->value("Standby").toFloat();
	StandbyPulseWidth = laserset->value("Standby").toFloat();

	// ��ʼ������
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

//�رմ����¼�
void laserSet::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����û�����
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

	// ��������
	laserset->sync();
	delete laserset;

	this->close();
}

// �رս���
void laserSet::on_CancelLaserSetting_clicked()
{
	this->close();
}