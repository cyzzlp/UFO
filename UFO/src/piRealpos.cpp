#include "piRealpos.h"

piRealpos::piRealpos(QObject* parent)
	: QObject(parent)
{

}

piRealpos::~piRealpos()
{

}

// ����߳����ڲ��϶�ȡPI��ʵʱλ��(PI��ʵʱλ��һֱ�ڸı�)
void piRealpos::Start()
{
	// ѡ��ȴ���
    BOOL bIsMoving[3] = { 0 };

    // ������ȡ�����Է���While��
    while (P_IsConnected)
    {
        // ����������λ��
        bool PI_qPOS_status = PI_qPOS(ID, szAxes, dPos);
        if (!PI_qPOS_status)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            emit DelieveWrongInfo(szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }

        // ��ȡʵ��λ��
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

        // 500ms��ʱ
        QThread::msleep(500);
    }
}

// �߳���������
void piRealpos::start()
{
    P_IsConnected = true;
}

// �߳�ֹͣ
void piRealpos::stop()
{
	P_IsConnected = false;
}