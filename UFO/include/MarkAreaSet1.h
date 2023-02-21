#pragma once

#include <QDialog>
#include "ui_MarkAreaSet1.h"

class MarkAreaSet1 : public QDialog
{
	Q_OBJECT

public:
	MarkAreaSet1(QWidget *parent = nullptr);
	~MarkAreaSet1();

private:
	Ui::MarkAreaSet1 ui;
};
