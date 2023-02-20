#pragma once

#include <QWidget>
#include "ui_DireButton.h"

class DireButton : public QWidget
{
	Q_OBJECT

public:
	DireButton(QWidget *parent = nullptr);
	~DireButton();

private:
	Ui::DireButtonClass ui;
};
