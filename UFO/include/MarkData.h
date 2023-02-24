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

    // ��������
    static int MarkTextRows;

    // ��������
    static int MarkTextColumns;

    // PI���
    static int ID;

    // ��¼������
    static char szAxes[2];

public:
	MarkData(QObject *parent);
	~MarkData();
};
