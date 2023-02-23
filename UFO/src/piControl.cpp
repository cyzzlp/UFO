#include <QMessageBox>
#include <QTimer>
#include "piControl.h"

piControl::piControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    // ��ȡPI��Ϣ
    QString m_FileName = QCoreApplication::applicationDirPath() + "/systemInfo.ini";
    piInfo = new QSettings(m_FileName, QSettings::IniFormat);

    // PI��Ϣ
    P_IsConnect = piInfo->value("PI").toBool();
    ID = piInfo->value("PI�豸���").toInt();
    szAxes[0] = piInfo->value("PI������").toChar().unicode();

    // ���PI������
    if (!P_IsConnect)
    {
        ui.ConnectPi->setEnabled(true);
        ui.inplementMove->setEnabled(false);
        ui.AddPiStep->setEnabled(false);
        ui.CutPiStep->setEnabled(false);
        ui.presentSetZero->setEnabled(false);
    }   
    else
    {
        ui.ConnectPi->setEnabled(false);
        ui.inplementMove->setEnabled(true);
        ui.AddPiStep->setEnabled(true);
        ui.CutPiStep->setEnabled(true);
        ui.presentSetZero->setEnabled(true);
    }
}

piControl::~piControl()
{

}

// ����PI
void piControl::on_ConnectPi_clicked()
{
    // ���USB��Ҫ�Ĳ���
    PI_EnumerateUSB(szBuffer, 17, szFilter);

    // ͨ��USB����
    ID = PI_ConnectUSB(szBuffer);
    if (ID < 0)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return;
    }

    // ��ȡ������������ı�ʶ��
    BOOL returnValue = PI_qSAI(ID, szAxes, 16);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return;
    }

    // Ϊ�ַ�����axes���е��������ŷ�
    BOOL bFlags[3] = { 0 };
    bFlags[0] = TRUE;

    // �����ŷ�ģʽ����
    returnValue = PI_SVO(ID, szAxes, bFlags);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return;
    }

    // ����(�ƶ�z��λ��)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(nullptr, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }
    // ѡ��ȴ���
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // ����������λ��
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            QMessageBox::critical(nullptr, "PI", szErrorMesage);
            return;
        }

        returnValue = PI_IsMoving(ID, NULL, bIsMoving);
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            QMessageBox::critical(nullptr, "PI", szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }
    }

    // PI�Ƿ�����
    int p_hasError = PI_IsConnected(ID);
    if (!p_hasError)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return;
    }

    // ��ʾ��ǰλ��
    ui.aimPos->setValue(0);
}
