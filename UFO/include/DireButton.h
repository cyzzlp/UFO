#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_DireButton.h"

class DireButton : public QWidget
{
	Q_OBJECT

public:
	DireButton(QWidget *parent = nullptr);
	~DireButton();

private:
	Ui::DireButton ui;
};
