#include "shutterControl.h"

shutterControl::shutterControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 读取快门信息
	QString m_FileName = QCoreApplication::applicationDirPath() + "/systemInfo.ini";
	shutter = new QSettings(m_FileName, QSettings::IniFormat);

	// 快门信息
	S_IsConnect = shutter->value("快门").toBool();
	indexs = shutter->value("快门句柄").toInt();

	// 转换
	index = (ULONG)indexs;

	// 如果PI已连接
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

//关闭窗口事件
void shutterControl::closeEvent(QCloseEvent* event)
{
	delete this;
}

// 连接快门
void shutterControl::on_connectShutter_clicked()
{
	// 连接设备
	HANDLE CH375Open = CH375OpenDevice(index);
	if (CH375Open == INVALID_HANDLE_VALUE)
	{
		QMessageBox::warning(this, "快门", "CH375快门连接失败");
		return;
	}

	// 设置延时
	CH375SetTimeout(index, 2000, 2000);

	ui.conectShutter->setEnabled(false);
	ui.openShutter->setEnabled(true);
	ui.closeShutter->setEnabled(true);
}

// 快门打开
void shutterControl::on_openShutter_clicked()
{
	unsigned long ioLength = 1;
	unsigned long* p_ioLength = &ioLength;
	int a = 0xea;
	int iBuffer = a & 0xea;
	CH375WriteData(index, &iBuffer, p_ioLength);
}

// 快门关闭
void shutterControl::on_closeShutter_clicked()
{
	unsigned long ioLength = 1;
	unsigned long* p_ioLength = &ioLength;
	int a = 0x0a;
	int iBuffer = a & 0x0a;
	CH375WriteData(index, &iBuffer, p_ioLength);
}
