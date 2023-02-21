#pragma once

#include <QDialog>
#include "ui_MarkAreaSet2.h"

class MarkAreaSet2 : public QDialog
{
	Q_OBJECT

public:
	MarkAreaSet2(QWidget *parent = nullptr);
	~MarkAreaSet2();

private:
	Ui::MarkAreaSet2 ui;
};
