#pragma once

#include <QDialog>
#include "ui_laserSet.h"

class laserSet : public QDialog
{
	Q_OBJECT

public:
	laserSet(QWidget *parent = nullptr);
	~laserSet();

private:
	Ui::laserSet ui;
};
