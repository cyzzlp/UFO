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
    // 记录仪器句柄
    int ID{};

    // 记录连接的PI移动轴
    char szAxes[2]{};

    // 记录连接的PI移动轴
    QString szAxe[1]{};

    // 用于 USB 设备描述的 szBuffer 缓冲区
    char szBuffer[17]{};

    // 仅其描述与过滤器匹配的控制器在缓冲区中返回
    char szFilter[17]{};

    // 返回的字符串,包括序列号和设备描述符
    char serialNo[256]{};

    // 错误码
    int iError{};

    // 错误提示
    char szErrorMesage[1024]{};

    // 轴等待
    BOOL bIsMoving[3]{};

    // 函数返回值
    BOOL returnValue{};

    // PI移动位置
    double dPos[3]{};
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

    // 标刻起点
    int count{};

    // 标刻终点
    int m_count{};

    // 标刻类型
    int labels{};

public slots:
    // 线程开始
    void Start();

    // 线程停止
    void Stop();

signals:
    // 发送振镜实时位置
    void MarkRealPos(double x_Pos, double y_Pos);

    // 发送PI错误
    void EmitWrongInfo(QString WrongText);
};
