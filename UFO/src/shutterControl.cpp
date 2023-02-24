#include "shutterControl.h"

shutterControl::shutterControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ������Ϣ
	QString m_FileName = QCoreApplication::applicationDirPath() + "/systemInfo.ini";
	shutter = new QSettings(m_FileName, QSettings::IniFormat);

	// ������Ϣ
	S_IsConnect = shutter->value("����").toBool();
	indexs = shutter->value("���ž��").toInt();

	// ת��
	index = (ULONG)indexs;

	// ���PI������
	if (!S_IsConnect)
	{
		ui.conectShutter->setEnabled(true);
		ui.openShutter->setEnabled(false);
		ui.closeShutter->setEnabled(false);
	}
	else
	{
		ui.conectShutter->setEnabled(false);
		ui.openShutter->setEnabled(true);
		ui.closeShutter->setEnabled(true);
	}
}

shutterControl::~shutterControl()
{

}

//�رմ����¼�
void shutterControl::closeEvent(QCloseEvent* event)
{
	delete this;
}

// ���ӿ���
void shutterControl::on_connectShutter_clicked()
{
	// �����豸
	HANDLE CH375Open = CH375OpenDevice(index);
	if (CH375Open == INVALID_HANDLE_VALUE)
	{
		QMessageBox::warning(this, "����", "CH375��������ʧ��");
		return;
	}

	// ������ʱ
	CH375SetTimeout(index, 2000, 2000);

	ui.conectShutter->setEnabled(false);
	ui.openShutter->setEnabled(true);
	ui.closeShutter->setEnabled(true);
}

// ���Ŵ�
void shutterControl::on_openShutter_clicked()
{
	unsigned long ioLength = 1;
	unsigned long* p_ioLength = &ioLength;
	int a = 0xea;
	int iBuffer = a & 0xea;
	CH375WriteData(index, &iBuffer, p_ioLength);
}

// ���Źر�
void shutterControl::on_closeShutter_clicked()
{
	unsigned long ioLength = 1;
	unsigned long* p_ioLength = &ioLength;
	int a = 0x0a;
	int iBuffer = a & 0x0a;
	CH375WriteData(index, &iBuffer, p_ioLength);
}
