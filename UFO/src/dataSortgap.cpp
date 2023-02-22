#include "dataSortgap.h"

dataSortgap::dataSortgap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ȡ�����ļ�
	QString m_FileName = QCoreApplication::applicationDirPath() + "/gapSetting.ini";
	gapInput = new QSettings(m_FileName, QSettings::IniFormat);

	// ��ȡ����
	xGap = gapInput->value("xGap").toDouble();
	yGap = gapInput->value("yGap").toDouble();
	dataType = gapInput->value("dataType").toBool();

	// ��ʼ������
	ui.dspGapx->setValue(xGap);
	ui.dspGapy->setValue(yGap);
	ui.dataXYZ->setChecked(!dataType);
	ui.dataXY->setChecked(dataType);
}

dataSortgap::~dataSortgap()
{

}

//�رմ����¼�
void dataSortgap::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����û�����
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

	// ��������
	gapInput->sync();
	delete gapInput;

	// ���Ͱ���ȷ���ź�
	emit isPushed();

	// ����ر�
	this->close();
}

// �رս���
void dataSortgap::on_cancelGapbtn_clicked()
{
	// ����ر�
	this->close();
}