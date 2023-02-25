#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QThread>
#include "MarkData.h"
#include "GlobalInfo.h"
#include "PI_GCS2_DLL_dynamicp_loader.h"

class piRealpos  : public QObject
{
	Q_OBJECT

public:
	piRealpos(QObject *parent);
	~piRealpos();

private:
    // �豸����״̬
    bool P_IsConnected{};

    // PIʵʱλ��
    double p_RealPos{};
    
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

public slots:
    void Start();
    void stop();

signals:
    void PiRealPOS(double u_PiPosition);
    void DelieveWrongInfo(QString WrongText);
};
