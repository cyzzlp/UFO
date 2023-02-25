#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QSettings>
#include "ui_MarkParaSet.h"

class MarkParaSet : public QDialog
{
	Q_OBJECT

public:
	MarkParaSet(QWidget *parent = nullptr);
	~MarkParaSet();

private:
    // 笔号
    int index{};

    // 标刻次数
    int markCount{};

    // 标刻速度
    float markSpeed{};

    // 跳转速度
    float jumpSpeed{};

    // 跳转延时
    float jumpDelay{};

    // 开光延时
    float laserOnDelay{};

    // 关光延时
    float laserOffDelay{};

    // 拐点延时
    float polygonDelay{};

    // 电流
    float current{};

    // 激光频率
    float laserFrequency{};

    // 脉冲宽度
    float pulseWidth{};

    // 首脉冲抑制宽度
    float firstPulseWidth{};

    // 拐点抑制时间
    float polygonKillerTime{};

    // YAG抑制脉宽
    float firstPulseKillerLength{};

    // CO2抑制增量步长
    float incrementStep{};

    // 点间距
    float dotSpace{};

    // 是否是位图
    bool isBitmap{};

private:
	// 配置文件
	QSettings* systemSet{};

private slots:
	//关闭窗口事件
	void closeEvent(QCloseEvent* event);

	// 保存用户设置
	void on_GetMarkParaSetting_clicked();

	// 关闭界面
	void on_CancelMarkParaSetting_clicked();

private:
	Ui::MarkParaSet ui;
};
