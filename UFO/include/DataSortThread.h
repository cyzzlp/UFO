#pragma once
#pragma execution_character_set("utf-8")

#include <QCoreApplication>
#include <QVector>
#include <QThread>
#include <QFile>
#include <QTextstream>
#include <QSettings>


class DataSortThread  : public QThread
{
	Q_OBJECT

private:
	// 记录文本绝对地址
	QString FileName;

	// 记录文本数据列数
	int MarkTextColumns{};

	// x预设间隔
	double xGap{};

	// y预设间隔
	double yGap{};

	// 数据类型
	bool DataType{};

	// 判断数据无错误点
	int IsErrorTextColumns{};

private:
	// 读取预设间隔ini文件
	QSettings* gap{};

	// 读取文件路径ini文件
	QSettings* filePath{};

protected:
	// 线程函数
	void run();

signals:
	// 提示文本处理的进度
	void setTextToLabel(QString DataStatus);

	// 显示标刻数据量
	void MarkDataNum(int MarkNum);

	// 显示错误信息
	void DelieveWrongInfo(QString WrongInfo);

public:
	DataSortThread(QObject *parent);
	~DataSortThread();
};
