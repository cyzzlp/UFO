#pragma once

#include <QObject>
#include <QThread>
#include <QMessageBox>
#include "MarkData.h"
#include "GlobalInfo.h"
#include "CSCInterface_dynamicm_loader.h"
#include "PI_GCS2_DLL.h"

class markThread  : public QObject
{
	Q_OBJECT

public:
    markThread(QObject* parent = nullptr);
	~markThread();

private:
    // ��¼�������
    int ID{};

    // ��¼���ӵ�PI�ƶ���
    char szAxes[2]{};

    // ��¼���ӵ�PI�ƶ���
    QString szAxe[1]{};

    // ���� USB �豸������ szBuffer ������
    char szBuffer[17]{};

    // ���������������ƥ��Ŀ������ڻ������з���
    char szFilter[17]{};

    // ���ص��ַ���,�������кź��豸������
    char serialNo[256]{};

    // ������
    int iError{};

    // ������ʾ
    char szErrorMesage[1024]{};

    // ��ȴ�
    BOOL bIsMoving[3]{};

    // ��������ֵ
    BOOL returnValue{};

    // PI�ƶ�λ��
    double dPos[3]{};
    // ���б�ǩ
    bool m_running{};

    // ��¼��ת��x����
    double x_jump{};

    // ��¼��ת��y����
    double y_jump{};

    // ��xλ��
    float xPos{};

    // ��yλ��
    float yPos{};

    // PIλ��
    float zPos{};

    // x�������
    double* xMarkData{};

    // y�������
    double* yMarkData{};

    // ������
    int count{};

    // ����յ�
    int m_count{};

    // �������
    int labels{};

public slots:
    // �߳̿�ʼ
    void Start();

    // �߳�ֹͣ
    void Stop();

signals:
    // ������ʵʱλ��
    void MarkRealPos(double x_Pos, double y_Pos);

    // ����PI����
    void EmitWrongInfo(QString WrongText);
};
