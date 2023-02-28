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

    // ��������ֵ
    BOOL returnValue{};

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

public slots:
    void Start();
    void Stop();

signals:
    void MarkRealPos(double x_Pos, double y_Pos);
};
