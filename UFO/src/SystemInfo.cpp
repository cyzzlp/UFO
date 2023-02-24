#include "SystemInfo.h"

SystemInfo::SystemInfo(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 设置表格头标题
	SetTableHeader();

	// 设置表格
	SetTables();
}

SystemInfo::~SystemInfo()
{

}

//关闭窗口事件
void SystemInfo::closeEvent(QCloseEvent* event)
{
	delete this;
}

// 设置列表表头
void SystemInfo::SetTableHeader()
{
	QTableWidgetItem* headerItem;
	QStringList headerText;

	// 表头
	headerText << "项目" << "系统信息";

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

// 设置列表参数
void SystemInfo::SetTables()
{
	// 读取系统信息
	QString FileName = QCoreApplication::applicationDirPath() + "/systemInfo.ini";
	TableInfo = new QSettings(FileName, QSettings::IniFormat);

	// 读取当前系统信息
	QString DataKey1 = "设备连接情况：";
	QString DataKey2 = "振镜";
	QString DataKey3 = "PI";
	QString DataKey4 = "相机";
	QString DataKey5 = "快门";
	QString DataKey6 = "PI设备句柄";
	QString DataKey7 = "PI连接轴";
	QString DataKey8 = "快门句柄";
	QString DataKey9 = "标刻文本信息：";
	QString DataKey10 = "文本路径";
	QString DataKey11 = "数据量（行）";
	QString DataKey12 = "数据类型";
	QString DataKey13 = "线程信息：";

	QString DataValue2 = TableInfo->value("振镜").toString();
	QString DataValue3 = TableInfo->value("PI").toString();
	QString DataValue4 = TableInfo->value("相机").toString();
	QString DataValue5 = TableInfo->value("快门").toString();
	QString DataValue6 = TableInfo->value("PI设备句柄").toString();
	QString DataValue7 = TableInfo->value("PI连接轴").toString();
	QString DataValue8 = TableInfo->value("快门句柄").toString();
	QString DataValue10 = TableInfo->value("文本路径").toString();
	QString DataValue11 = TableInfo->value("数据量（行）").toString();
	QString DataValue12 = TableInfo->value("数据类型").toString();

	// 设置参数
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

	// 设置交替行背景颜色
	ui.systemTabelInfo->setAlternatingRowColors(true);

	// 表格不可编辑
	ui.systemTabelInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.systemTabelInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// 添加一行
void SystemInfo::appendOneRow(QString DataKey, QString DataValue)
{
	// 获取当前行数
	int count = ui.systemTabelInfo->rowCount();

	// 当前行数加1
	ui.systemTabelInfo->setRowCount(count + 1);

	// 数据指针
	QTableWidgetItem* DataKeyItem = new QTableWidgetItem(DataKey);
	QTableWidgetItem* DataValueItem = new QTableWidgetItem(DataValue);

	// 设置参数
	ui.systemTabelInfo->setItem(count, 0, DataKeyItem);
	ui.systemTabelInfo->setItem(count, 1, DataValueItem); 

	// 当前位置文字居中
	ui.systemTabelInfo->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.systemTabelInfo->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

// 添加一行
void SystemInfo::appendOneRows(QString DataKey)
{
	// 获取当前行数
	int count = ui.systemTabelInfo->rowCount();

	// 当前行数加1
	ui.systemTabelInfo->setRowCount(count + 1);

	// 数据指针
	QTableWidgetItem* DataKeyItem = new QTableWidgetItem(DataKey);

	// 设置参数
	ui.systemTabelInfo->setItem(count, 0, DataKeyItem);
}
