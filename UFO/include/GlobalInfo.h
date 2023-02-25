#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>

class GlobalInfo  : public QObject
{
	Q_OBJECT

public:
	// �ļ�·��
	static QString aFileName;

	// ������
	static bool m_Connect;

	// PI����
	static bool p_Connect;

	// ��������
	static bool s_Connect;

	// �������
	static bool c_Connect;

	// PI���
	static int ID;

	// ��¼������
	static char szAxes[2];

	// ���ž��
	static unsigned long index;

	// ��������
	static int MarkTextRows;

	// ��������
	static int MarkTextColumns;

	// ��������
	static bool DataType;

	// �񾵱���߳�
	static bool mthread;

	// CCDͼ��ɼ��߳�
	static bool cthread;

	// PIλ���߳�
	static bool pthread;

	// �������
	static int MarkCount;

	// PI���λ��
	static double presentSetZero;

public:
	GlobalInfo(QObject *parent);
	~GlobalInfo();
};
