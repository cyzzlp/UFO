#pragma once

#include <QObject>
#include <QVector>

class MarkData  : public QObject
{
	Q_OBJECT

public:
    // ��¼�ı�����
    static QVector<QVector<double>> returnMarkData;

    // ������ݵ��ǩ
    static QVector<QVector<int>> MarkTextDataType;

public:
	MarkData(QObject *parent);
	~MarkData();
};
