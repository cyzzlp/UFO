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
	// ��¼�ı����Ե�ַ
	QString FileName;

	// ��¼�ı���������
	int MarkTextColumns{};

	// xԤ����
	double xGap{};

	// yԤ����
	double yGap{};

	// ��������
	bool DataType{};

	// �ж������޴����
	int IsErrorTextColumns{};

private:
	// ��ȡԤ����ini�ļ�
	QSettings* gap{};

	// ��ȡ�ļ�·��ini�ļ�
	QSettings* filePath{};

protected:
	// �̺߳���
	void run();

signals:
	// ��ʾ�ı�����Ľ���
	void setTextToLabel(QString DataStatus);

	// ��ʾ���������
	void MarkDataNum(int MarkNum);

	// ��ʾ������Ϣ
	void DelieveWrongInfo(QString WrongInfo);

public:
	DataSortThread(QObject *parent);
	~DataSortThread();
};
