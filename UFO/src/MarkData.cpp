#include "MarkData.h"

// 静态成员变量初始化
QVector<QVector<double>> MarkData::returnMarkData;
QVector<QVector<int>> MarkData::MarkTextDataType;

MarkData::MarkData(QObject *parent)
	: QObject(parent)
{}

MarkData::~MarkData()
{

}
