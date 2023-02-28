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

    // 函数返回值
    BOOL returnValue{};

    // 运行标签
    bool m_running{};

    // 记录跳转点x坐标
    double x_jump{};

    // 记录跳转点y坐标
    double y_jump{};

    // 振镜x位置
    float xPos{};

    // 振镜y位置
    float yPos{};

    // PI位置
    float zPos{};

    // x标刻数组
    double* xMarkData{};

    // y标刻数组
    double* yMarkData{};

public slots:
    void Start();
    void Stop();

signals:
    void MarkRealPos(double x_Pos, double y_Pos);
};
