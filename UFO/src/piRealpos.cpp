#include "piRealpos.h"

piRealpos::piRealpos(QObject* parent)
	: QObject(parent)
{

}

piRealpos::~piRealpos()
{

}

// 这个线程用于不断读取PI的实时位置(PI的实时位置一直在改变)
void piRealpos::Start()
{
	// 选择等待轴
    BOOL bIsMoving[3] = { 0 };

    // 持续读取，所以放在While内
    while (P_IsConnected)
    {
        // 获得连接轴的位置
        bool PI_qPOS_status = PI_qPOS(ID, szAxes, dPos);
        if (!PI_qPOS_status)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            emit DelieveWrongInfo(szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }

        // 获取实际位置
        p_RealPos = dPos[0];

        bool PI_IsMoving_status = PI_IsMoving(ID, NULL, bIsMoving);
        if (!PI_IsMoving_status)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            emit DelieveWrongInfo(szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }

        emit PiRealPOS(p_RealPos);

        // 500ms延时
        QThread::msleep(500);
    }
}

// 线程重新启动
void piRealpos::start()
{
    P_IsConnected = true;
}

// 线程停止
void piRealpos::stop()
{
	P_IsConnected = false;
}