#pragma once

#include <QObject>
#include <QVector>

class MarkData  : public QObject
{
	Q_OBJECT

public:
    // 记录文本数据
    static QVector<QVector<double>> returnMarkData;

    // 标刻数据点标签
    static QVector<QVector<int>> MarkTextDataType;

public:
	MarkData(QObject *parent);
	~MarkData();
};
