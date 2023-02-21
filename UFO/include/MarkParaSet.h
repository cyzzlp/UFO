#pragma once

#include <QDialog>
#include "ui_MarkParaSet.h"

class MarkParaSet : public QDialog
{
	Q_OBJECT

public:
	MarkParaSet(QWidget *parent = nullptr);
	~MarkParaSet();

private:
	Ui::MarkParaSet ui;
};
