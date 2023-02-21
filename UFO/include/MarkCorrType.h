#pragma once

#include <QDialog>
#include "ui_MarkCorrType.h"

class MarkCorrType : public QDialog
{
	Q_OBJECT

public:
	MarkCorrType(QWidget *parent = nullptr);
	~MarkCorrType();

private:
	Ui::MarkCorrType ui;
};
