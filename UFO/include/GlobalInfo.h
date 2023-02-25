#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>

class GlobalInfo  : public QObject
{
	Q_OBJECT

public:
	// 文件路径
	static QString aFileName;

	// 振镜连接
	static bool m_Connect;

	// PI连接
	static bool p_Connect;

	// 快门连接
	static bool s_Connect;

	// 相机连接
	static bool c_Connect;

	// PI句柄
	static int ID;

	// 记录连接轴
	static char szAxes[2];

	// 快门句柄
	static unsigned long index;

	// 数据行数
	static int MarkTextRows;

	// 数据列数
	static int MarkTextColumns;

	// 数据类型
	static bool DataType;

	// 振镜标刻线程
	static bool mthread;

	// CCD图像采集线程
	static bool cthread;

	// PI位置线程
	static bool pthread;

	// 标刻数量
	static int MarkCount;

	// PI零点位置
	static double presentSetZero;

public:
	GlobalInfo(QObject *parent);
	~GlobalInfo();
};
