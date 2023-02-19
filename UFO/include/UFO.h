#pragma once

//���������������
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
    // �豸����״̬ �� PI ��ҵ��� ����
    bool M_IsConnected{};
    bool P_IsConnected{};
    bool C_IsConnected{};
    bool S_IsConnected{};

    // FPGAӲ��������Ե�ַ


private:
    // ������
    int connectSystemMark();

    // ����PI
    bool connectSystemPi();



    // ���� USB �豸������ szBuffer ������
    char szBuffer[17]{};

    // ���������������ƥ��Ŀ������ڻ������з���
    char szFilter[17]{};

    // ���ص��ַ���,�������кź��豸������
    char serialNo[256]{};

private:
    Ui::UFO ui;
};
