#include "SystemInfo.h"

SystemInfo::SystemInfo(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SystemInfo::~SystemInfo()
{

}

// 设置列表表头
void SystemInfo::SetTableHeader()
{
	QTableWidgetItem* headerItem;
	QStringList headerText;

	// 表头
	headerText << "项目" << "相机系统信息";

	// 设置表格列数
	ui.systemTabelInfo->setColumnCount(headerText.count());

	// 设置表格参数
	for (int i = 0; i < ui.systemTabelInfo->columnCount(); i++)
	{
		headerItem = new QTableWidgetItem(headerText.at(i));
		QFont font = ui.systemTabelInfo->font();

		// 字体加粗
		font.setBold(true);

		// 字体大小：9号
		font.setPointSize(9);

		// 设置字体
		headerItem->setFont(font);

		// 每行都按照上述设置
		ui.systemTabelInfo->setHorizontalHeaderItem(i, headerItem);
	}
}

// 设置行数,设置的行数为数据区的行数，不含表头
void SystemInfo::SetTablesSize()
{

}
