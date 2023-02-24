#include "SystemInfo.h"

SystemInfo::SystemInfo(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ���ñ��ͷ����
	SetTableHeader();

	// ���ñ��
	SetTables();
}

SystemInfo::~SystemInfo()
{

}

//�رմ����¼�
void SystemInfo::closeEvent(QCloseEvent* event)
{
	delete this;
}

// �����б��ͷ
void SystemInfo::SetTableHeader()
{
	QTableWidgetItem* headerItem;
	QStringList headerText;

	// ��ͷ
	headerText << "��Ŀ" << "ϵͳ��Ϣ";

	// ���ñ������
	ui.systemTabelInfo->setColumnCount(headerText.count());

	// ���ñ�����
	for (int i = 0; i < ui.systemTabelInfo->columnCount(); i++)
	{
		headerItem = new QTableWidgetItem(headerText.at(i));
		QFont font = ui.systemTabelInfo->font();

		// ����Ӵ�
		font.setBold(true);

		// �����С��9��
		font.setPointSize(9);

		// ��������
		headerItem->setFont(font);

		// ÿ�ж�������������
		ui.systemTabelInfo->setHorizontalHeaderItem(i, headerItem);
	}
}

// �����б����
void SystemInfo::SetTables()
{
	// ��ȡϵͳ��Ϣ
	QString FileName = QCoreApplication::applicationDirPath() + "/systemInfo.ini";
	TableInfo = new QSettings(FileName, QSettings::IniFormat);

	// ��ȡ��ǰϵͳ��Ϣ
	QString DataKey1 = "�豸���������";
	QString DataKey2 = "��";
	QString DataKey3 = "PI";
	QString DataKey4 = "���";
	QString DataKey5 = "����";
	QString DataKey6 = "PI�豸���";
	QString DataKey7 = "PI������";
	QString DataKey8 = "���ž��";
	QString DataKey9 = "����ı���Ϣ��";
	QString DataKey10 = "�ı�·��";
	QString DataKey11 = "���������У�";
	QString DataKey12 = "��������";
	QString DataKey13 = "�߳���Ϣ��";

	QString DataValue2 = TableInfo->value("��").toString();
	QString DataValue3 = TableInfo->value("PI").toString();
	QString DataValue4 = TableInfo->value("���").toString();
	QString DataValue5 = TableInfo->value("����").toString();
	QString DataValue6 = TableInfo->value("PI�豸���").toString();
	QString DataValue7 = TableInfo->value("PI������").toString();
	QString DataValue8 = TableInfo->value("���ž��").toString();
	QString DataValue10 = TableInfo->value("�ı�·��").toString();
	QString DataValue11 = TableInfo->value("���������У�").toString();
	QString DataValue12 = TableInfo->value("��������").toString();

	// ���ò���
	appendOneRows(DataKey1);
	appendOneRow(DataKey2, DataValue2);
	appendOneRow(DataKey3, DataValue3);
	appendOneRow(DataKey4, DataValue4);
	appendOneRow(DataKey5, DataValue5);
	appendOneRow(DataKey6, DataValue6);
	appendOneRow(DataKey7, DataValue7);
	appendOneRow(DataKey8, DataValue8);
	appendOneRows(DataKey9);
	appendOneRow(DataKey10, DataValue10);
	appendOneRow(DataKey11, DataValue11);
	appendOneRow(DataKey12, DataValue12);
	appendOneRows(DataKey13);

	// ���ý����б�����ɫ
	ui.systemTabelInfo->setAlternatingRowColors(true);

	// ��񲻿ɱ༭
	ui.systemTabelInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.systemTabelInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// ���һ��
void SystemInfo::appendOneRow(QString DataKey, QString DataValue)
{
	// ��ȡ��ǰ����
	int count = ui.systemTabelInfo->rowCount();

	// ��ǰ������1
	ui.systemTabelInfo->setRowCount(count + 1);

	// ����ָ��
	QTableWidgetItem* DataKeyItem = new QTableWidgetItem(DataKey);
	QTableWidgetItem* DataValueItem = new QTableWidgetItem(DataValue);

	// ���ò���
	ui.systemTabelInfo->setItem(count, 0, DataKeyItem);
	ui.systemTabelInfo->setItem(count, 1, DataValueItem); 

	// ��ǰλ�����־���
	ui.systemTabelInfo->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.systemTabelInfo->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

// ���һ��
void SystemInfo::appendOneRows(QString DataKey)
{
	// ��ȡ��ǰ����
	int count = ui.systemTabelInfo->rowCount();

	// ��ǰ������1
	ui.systemTabelInfo->setRowCount(count + 1);

	// ����ָ��
	QTableWidgetItem* DataKeyItem = new QTableWidgetItem(DataKey);

	// ���ò���
	ui.systemTabelInfo->setItem(count, 0, DataKeyItem);
}
