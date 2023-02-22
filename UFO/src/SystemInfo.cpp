#include "SystemInfo.h"

SystemInfo::SystemInfo(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SystemInfo::~SystemInfo()
{

}

// �����б��ͷ
void SystemInfo::SetTableHeader()
{
	QTableWidgetItem* headerItem;
	QStringList headerText;

	// ��ͷ
	headerText << "��Ŀ" << "���ϵͳ��Ϣ";

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

// ��������,���õ�����Ϊ��������������������ͷ
void SystemInfo::SetTablesSize()
{

}
