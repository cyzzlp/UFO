#pragma once

#include <QDialog>
#include "ui_YoursData.h"

class YoursData : public QDialog
{
	Q_OBJECT

public:
	YoursData(QWidget *parent = nullptr);
	~YoursData();

private:
	Ui::YoursData ui;
};
