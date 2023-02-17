#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UFO.h"
#include "CSCInterface_dynamicm_loader.h"
#include "ids_peak_comfort_c_dynamic_loader.h"
#include "PI_GCS2_DLL_dynamicp_loader.h"

class UFO : public QMainWindow
{
    Q_OBJECT

public:
    UFO(QWidget *parent = nullptr);
    ~UFO();

private:
    Ui::UFOClass ui;
};
