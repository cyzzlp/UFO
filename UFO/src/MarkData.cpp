#include "MarkData.h"

// 静态成员变量初始化
QVector<QVector<double>> MarkData::returnMarkData;
QVector<QVector<int>> MarkData::MarkTextDataType;
int MarkData::MarkTextRows = 0;
int MarkData::MarkTextColumns = 0;
int MarkData::ID = -1;
char MarkData::szAxes[2] = { 'c'};

MarkData::MarkData(QObject *parent)
	: QObject(parent)
{}

MarkData::~MarkData()
{

}
