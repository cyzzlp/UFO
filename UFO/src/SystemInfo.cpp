#include "SystemInfo.h"
#include "GlobalInfo.h"

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
	QString DataKey1 = "设备连接情况：";
	QString DataKey2 = "振镜";
	QString DataKey3 = "PI";
	QString DataKey4 = "相机";
	QString DataKey5 = "快门";
	QString DataKey6 = "PI连接句柄";
	QString DataKey7 = "PI连接轴";
	QString DataKey8 = "快门句柄";
	QString DataKey9 = "标刻文本信息：";
	QString DataKey10 = "文本路径";
	QString DataKey11 = "数据量（行）";
	QString DataKey12 = "数据类型";
	QString DataKey13 = "线程信息：";
	QString DataKey14 = "振镜标刻";
	QString DataKey15 = "PI实时位置";
	QString DataKey16 = "CCD图像采集";

	// 设置表格
	appendOneRows(DataKey1);

	if (GlobalInfo::m_Connect)
	{
		QString DataValue2 = "已连接";
		appendOneRow(DataKey2, DataValue2);
	}
	else
	{
		QString DataValue2 = "未连接";
		appendOneRow(DataKey2, DataValue2);
	}

	if (GlobalInfo::p_Connect)
	{
		QString DataValue3 = "已连接";
		appendOneRow(DataKey3, DataValue3);
	}
	else
	{
		QString DataValue3 = "未连接";
		appendOneRow(DataKey3, DataValue3);
	}

	if (GlobalInfo::c_Connect)
	{
		QString DataValue4 = "已连接";
		appendOneRow(DataKey4, DataValue4);
	}
	else
	{
		QString DataValue4 = "未连接";
		appendOneRow(DataKey4, DataValue4);
	}

	if (GlobalInfo::s_Connect)
	{
		QString DataValue5 = "已连接";
		appendOneRow(DataKey5, DataValue5);
	}
	else
	{
		QString DataValue5 = "未连接";
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
		QString DataValue14 = "正在运行中";
		appendOneRow(DataKey14, DataValue14);
	}
	else
	{
		QString DataValue14 = "未运行";
		appendOneRow(DataKey14, DataValue14);
	}

	if (GlobalInfo::pthread)
	{
		QString DataValue15 = "正在运行中";
		appendOneRow(DataKey15, DataValue15);

	}
	else
	{
		QString DataValue15 = "未运行";
		appendOneRow(DataKey15, DataValue15);

	}

	if (GlobalInfo::cthread)
	{
		QString DataValue16 = "正在运行中";
		appendOneRow(DataKey16, DataValue16);
	}
	else
	{
		QString DataValue16 = "未运行";
		appendOneRow(DataKey16, DataValue16);
	}

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
