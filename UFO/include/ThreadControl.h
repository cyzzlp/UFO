#pragma once

#include <QDialog>
#include "ui_ThreadControl.h"

class ThreadControl : public QDialog
{
	Q_OBJECT

public:
	ThreadControl(QWidget *parent = nullptr);
	~ThreadControl();

private slots:
	//

private:
	Ui::ThreadControl ui;
};
