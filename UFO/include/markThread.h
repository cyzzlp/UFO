#pragma once

#include <QObject>
#include <QThread>
#include <QMessageBox>
#include "MarkData.h"
#include "GlobalInfo.h"
#include "PI_GCS2_DLL_dynamicp_loader.h"
#include "CSCInterface_dynamicm_loader.h"

class markThread  : public QObject
{
	Q_OBJECT

public:
	markThread(QObject *parent);
	~markThread();

private:
    // PI���
    int ID{};

    // ��¼������
    char szAxes[2]{};

    // PI������Ϣ���
    int iError{};

    // PI������Ϣ
    char szErrorMesage[1024]{};

    // PI�ƶ�λ��
    double dPos[3]{};

    // PI��ȴ�
    BOOL bIsMoving[3]{};

    // ���б�ǩ
    bool m_running{};

    // ��¼��ת��x����
    double x_jump{};

    // ��¼��ת��y����
    double y_jump{};

    // ��xλ��
    float xpos{};

    // ��yλ��
    float ypos{};

    // PIλ��
    float zpos{};

    // x�������
    double* xMarkData{};

    // y�������
    double* yMarkData{};

    // ������
    int count{};

    // ����յ�
    int m_count{};

    // ��¼�ϴα�����
    int counts{};

    // ��¼�ϴα���յ�
    int m_counts{};

    // �������
    int labels{};

public slots:
    void Start();
    void Stop();

signals:
    void MarkRealPos(double x_Pos, double y_Pos);
};
