#include "MarkData.h"

// ��̬��Ա������ʼ��
QVector<QVector<double>> MarkData::returnMarkData;
QVector<QVector<int>> MarkData::MarkTextDataType;
int MarkData::MarkTextRows = 0;
int MarkData::MarkTextColumns = 0;

MarkData::MarkData(QObject *parent)
	: QObject(parent)
{}

MarkData::~MarkData()
{

}
