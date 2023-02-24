#include <QMessageBox>
#include <QTimer>
#include "piControl.h"

piControl::piControl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    // 读取PI信息
    QString m_FileName = QCoreApplication::applicationDirPath() + "/systemInfo.ini";
    piInfo = new QSettings(m_FileName, QSettings::IniFormat);

    // PI信息
    P_IsConnect = piInfo->value("PI").toBool();
    ID = piInfo->value("PI设备句柄").toInt();
    szAxes[0] = piInfo->value("PI连接轴").toChar().unicode();

    // 如果PI已连接
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

//关闭窗口事件
void piControl::closeEvent(QCloseEvent* event)
{
    delete this;
}

// 连接PI
void piControl::on_ConnectPi_clicked()
{
    // 获得USB需要的参数
    PI_EnumerateUSB(szBuffer, 17, szFilter);

    // 通过USB连接
    ID = PI_ConnectUSB(szBuffer);
    if (ID < 0)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }

    // 获取所有已配置轴的标识符
    BOOL returnValue = PI_qSAI(ID, szAxes, 16);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }

    // 为字符串“axes”中的轴启用伺服
    BOOL bFlags[3] = { 0 };
    bFlags[0] = TRUE;

    // 调用伺服模式命令
    returnValue = PI_SVO(ID, szAxes, bFlags);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }

    // 回零
    dPos[0] = 0.0;

    // 换层(移动z轴位置)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }
    // 选择等待轴
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // 获得连接轴的位置
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            QMessageBox::critical(this, "PI", szErrorMesage);
            return;
        }

        returnValue = PI_IsMoving(ID, NULL, bIsMoving);
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            QMessageBox::critical(this, "PI", szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }
    }

    // PI是否连接
    int p_hasError = PI_IsConnected(ID);
    if (!p_hasError)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return;
    }

    // 按键恢复
    ui.ConnectPi->setEnabled(false);
    ui.inplementMove->setEnabled(true);
    ui.AddPiStep->setEnabled(true);
    ui.CutPiStep->setEnabled(true);
    ui.presentSetZero->setEnabled(true);

    // 显示当前位置
    ui.aimPos->setValue(0);
}

// PI移动至
void piControl::on_inplementMove_clicked()
{
    // 获取移动值
    double zPos = ui.PiPosto->value();

    // 移动至
    dPos[0] = zPos;

    // 换层(移动z轴位置)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }
    // 选择等待轴
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // 获得连接轴的位置
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            QMessageBox::critical(this, "PI", szErrorMesage);
            return;
        }

        returnValue = PI_IsMoving(ID, NULL, bIsMoving);
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            QMessageBox::critical(this, "PI", szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }
    }

    // 更新控件值
    ui.aimPos->setValue(zPos);
}

// PI增加
void piControl::on_AddPiStep_clicked()
{
    // 读取移动步长
    double zStep = ui.PiMoveStep->value();

    // PI移动后位置
    double zPos = ui.aimPos->value() + zStep;

    // 防止超程
    if (zPos > 250)
        zPos = 250;
    if (zPos < 0)
        zPos = 0;

    // 移动至
    dPos[0] = zPos;

    // 换层(移动z轴位置)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }
    // 选择等待轴
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // 获得连接轴的位置
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            QMessageBox::critical(this, "PI", szErrorMesage);
            return;
        }

        returnValue = PI_IsMoving(ID, NULL, bIsMoving);
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            QMessageBox::critical(this, "PI", szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }
    }

    // 更新控件值
    ui.aimPos->setValue(zPos);
}

// PI减少
void piControl::on_CutPiStep_clicked()
{
    // 读取移动步长
    double zStep = ui.PiMoveStep->value();

    // PI移动后位置
    double zPos = ui.aimPos->value() - zStep;

    // 防止超程
    if (zPos > 250)
        zPos = 250;
    if (zPos < 0)
        zPos = 0;

    // 移动至
    dPos[0] = zPos;

    // 换层(移动z轴位置)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        QMessageBox::critical(this, "PI", szErrorMesage);
        PI_CloseConnection(ID);
        return;
    }
    // 选择等待轴
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // 获得连接轴的位置
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            QMessageBox::critical(this, "PI", szErrorMesage);
            return;
        }

        returnValue = PI_IsMoving(ID, NULL, bIsMoving);
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            QMessageBox::critical(this, "PI", szErrorMesage);
            PI_CloseConnection(ID);
            return;
        }
    }

    // 更新控件值
    ui.aimPos->setValue(zPos);
}

// 当前至设为z = 0
void piControl::on_presentSetZero_clicked()
{
    // 获取PI当前位置
    double zPos = ui.aimPos->value();

    // 发送信号
    emit piPos(zPos);
}