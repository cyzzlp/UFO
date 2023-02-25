#include "SystemInfo.h"
#include "GlobalInfo.h"

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
	QString DataKey1 = "�豸���������";
	QString DataKey2 = "��";
	QString DataKey3 = "PI";
	QString DataKey4 = "���";
	QString DataKey5 = "����";
	QString DataKey6 = "PI���Ӿ��";
	QString DataKey7 = "PI������";
	QString DataKey8 = "���ž��";
	QString DataKey9 = "����ı���Ϣ��";
	QString DataKey10 = "�ı�·��";
	QString DataKey11 = "���������У�";
	QString DataKey12 = "��������";
	QString DataKey13 = "�߳���Ϣ��";
	QString DataKey14 = "�񾵱��";
	QString DataKey15 = "PIʵʱλ��";
	QString DataKey16 = "CCDͼ��ɼ�";

	// ���ñ��
	appendOneRows(DataKey1);

	if (GlobalInfo::m_Connect)
	{
		QString DataValue2 = "������";
		appendOneRow(DataKey2, DataValue2);
	}
	else
	{
		QString DataValue2 = "δ����";
		appendOneRow(DataKey2, DataValue2);
	}

	if (GlobalInfo::p_Connect)
	{
		QString DataValue3 = "������";
		appendOneRow(DataKey3, DataValue3);
	}
	else
	{
		QString DataValue3 = "δ����";
		appendOneRow(DataKey3, DataValue3);
	}

	if (GlobalInfo::c_Connect)
	{
		QString DataValue4 = "������";
		appendOneRow(DataKey4, DataValue4);
	}
	else
	{
		QString DataValue4 = "δ����";
		appendOneRow(DataKey4, DataValue4);
	}

	if (GlobalInfo::s_Connect)
	{
		QString DataValue5 = "������";
		appendOneRow(DataKey5, DataValue5);
	}
	else
	{
		QString DataValue5 = "δ����";
		appendOneRow(DataKey5, DataValue5);
	}

	QString DataValue6 = QString::number(GlobalInfo::ID);
	QString DataValue7 = QString::number(GlobalInfo::szAxes[1]);
	QString DataValue8 = QString::number(GlobalInfo::index);
	QString DataValue10 = GlobalInfo::aFileName;
	QString DataValue11 = QString::number(GlobalInfo::MarkTextRows);

	appendOneRow(DataKey6, DataValue6);
	appendOneRow(DataKey7, DataValue7);
	appendOneRow(DataKey8, DataValue8);
	appendOneRows(DataKey9);
	appendOneRow(DataKey10, DataValue10);
	appendOneRow(DataKey11, DataValue11);

	if (!GlobalInfo::DataType)
	{
		QString DataValue12 = "XYZ";
		appendOneRow(DataKey12, DataValue12);
	}
	else
	{
		QString DataValue12 = "XY";
		appendOneRow(DataKey12, DataValue12);
	}

	appendOneRows(DataKey13);

	if (GlobalInfo::mthread)
	{
		QString DataValue14 = "����������";
		appendOneRow(DataKey14, DataValue14);
	}
	else
	{
		QString DataValue14 = "δ����";
		appendOneRow(DataKey14, DataValue14);
	}

	if (GlobalInfo::pthread)
	{
		QString DataValue15 = "����������";
		appendOneRow(DataKey15, DataValue15);

	}
	else
	{
		QString DataValue15 = "δ����";
		appendOneRow(DataKey15, DataValue15);

	}

	if (GlobalInfo::cthread)
	{
		QString DataValue16 = "����������";
		appendOneRow(DataKey16, DataValue16);
	}
	else
	{
		QString DataValue16 = "δ����";
		appendOneRow(DataKey16, DataValue16);
	}

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
