#pragma once

#include <QObject>
#include <QThread>
#include "PI_GCS2_DLL_dynamicp_loader.h"

class piRealpos  : public QObject
{
	Q_OBJECT

public:
	piRealpos(QObject *parent = nullptr);
	~piRealpos();

private:
    // 设备连接状态
    bool P_IsConnected{};

    // PI实时位置
    double p_RealPos{};
    
    // PI句柄
    int ID{};

    // 记录连接轴
    char szAxes[2]{};

    // PI错误信息编号
    int iError{};

    // PI错误信息
    char szErrorMesage[1024]{};

    // PI移动位置
    double dPos[3]{};

    // PI轴等待
    BOOL bIsMoving[3]{};

public slots:
    void Start();
    void start();
    void stop();

signals:
    void started();
    void stopped();
    void PiRealPOS(double u_PiPosition);
    void DelieveWrongInfo(QString WrongText);
};
