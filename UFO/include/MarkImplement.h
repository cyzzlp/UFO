#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include "ui_MarkImplement.h"

class MarkImplement : public QDialog
{
	Q_OBJECT

public:
	MarkImplement(QWidget *parent = nullptr);
	~MarkImplement();

private:
	Ui::MarkImplement ui;
};
