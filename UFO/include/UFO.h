#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UFO.h"
#include "CSCInterface_dynamicm_loader.h"
#include "ids_peak_comfort_c.h"
#include "PI_GCS2_DLL_dynamicp_loader.h"

class UFO : public QMainWindow
{
    Q_OBJECT

public:
    UFO(QWidget *parent = nullptr);
    ~UFO();

    // 用于 USB 设备描述的 szBuffer 缓冲区
    char szBuffer[17]{};

    // 仅其描述与过滤器匹配的控制器在缓冲区中返回
    char szFilter[17]{};

    // 返回的字符串,包括序列号和设备描述符
    char serialNo[256]{};

private:
    Ui::UFOClass ui;
};
