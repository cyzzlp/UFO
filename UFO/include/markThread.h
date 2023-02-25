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

    // 运行标签
    bool m_running{};

    // 记录跳转点x坐标
    double x_jump{};

    // 记录跳转点y坐标
    double y_jump{};

    // 振镜x位置
    float xpos{};

    // 振镜y位置
    float ypos{};

    // PI位置
    float zpos{};

    // x标刻数组
    double* xMarkData{};

    // y标刻数组
    double* yMarkData{};

    // 标刻起点
    int count{};

    // 标刻终点
    int m_count{};

    // 记录上次标刻起点
    int counts{};

    // 记录上次标刻终点
    int m_counts{};

    // 标刻类型
    int labels{};

public slots:
    void Start();
    void Stop();

signals:
    void MarkRealPos(double x_Pos, double y_Pos);
};
