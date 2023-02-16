#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UFO.h"
#include "CSCInterface_dynamics_c_loader.h"
#include "ids_peak_comfort_c_dynamic_loader.h"
#include"PI_dynamic_c_loader.h"

class UFO : public QMainWindow
{
    Q_OBJECT

public:
    UFO(QWidget *parent = nullptr);
    ~UFO();

private:
    Ui::UFOClass ui;
};
