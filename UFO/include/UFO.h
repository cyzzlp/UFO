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

    // ���� USB �豸������ szBuffer ������
    char szBuffer[17]{};

    // ���������������ƥ��Ŀ������ڻ������з���
    char szFilter[17]{};

    // ���ص��ַ���,�������кź��豸������
    char serialNo[256]{};

private:
    Ui::UFOClass ui;
};
