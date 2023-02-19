#pragma once

//解决汉字乱码问题
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "PI_GCS2_DLL_dynamicp_loader.h"
#include "CSCInterface_dynamicm_loader.h"
#include "ids_peak_comfort_c.h"
#include "ui_UFO.h"

class UFO : public QMainWindow
{
    Q_OBJECT

public:
    UFO(QWidget *parent = nullptr);
    ~UFO();

private:
    // 设备连接状态 振镜 PI 工业相机 快门
    bool M_IsConnected{};
    bool P_IsConnected{};
    bool C_IsConnected{};
    bool S_IsConnected{};

    // FPGA硬件程序绝对地址


private:
    // 连接振镜
    int connectSystemMark();

    // 连接PI
    bool connectSystemPi();



    // 用于 USB 设备描述的 szBuffer 缓冲区
    char szBuffer[17]{};

    // 仅其描述与过滤器匹配的控制器在缓冲区中返回
    char szFilter[17]{};

    // 返回的字符串,包括序列号和设备描述符
    char serialNo[256]{};

private:
    Ui::UFO ui;
};
