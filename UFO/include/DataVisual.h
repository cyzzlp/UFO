#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QtDataVisualization>
#include <QSplitter>
#include "MarkData.h"
#include "ui_DataVisual.h"

using namespace QtDataVisualization;

class DataVisual : public QDialog
{
	Q_OBJECT

public:
    DataVisual(QWidget* parent = nullptr);
	~DataVisual();

public slots:
	// 绘图
	void DrawData(QVector<QVector<double>> PointArr);

private:
    // 为实现数据共享，公共化参数
    QScatterDataArray* dataArray = nullptr;

    QScatterDataItem* ptrToDataArray = nullptr;

    // 图表的容器
    QWidget* graphContainer{};

    // 散点图
    Q3DScatter* graph3D{};

    // 散点序列
    QScatter3DSeries* series{};

    // 读取数据信息
    QSettings* DataInfo{};

private slots:
    // 关闭窗口事件
    void closeEvent(QCloseEvent* event);

    // 初始化
    void InitGraph3D();

    // 选择视角
    void on_comboCamera_currentIndexChanged(int index);

    // 实现水平旋转
    void on_sliderH_valueChanged(int value);

    // 实现垂直旋转
    void on_sliderV_valueChanged(int value);

    // 实现坐标点缩放
    void on_sliderPoint_valueChanged(int value);

    // 实现图像缩放
    void on_sliderZoom_valueChanged(int value);

    // 实现点样式设置
    void on_comboPointType_currentIndexChanged(int index);

    // 实现切换图像主题
    void on_comboTheme_currentIndexChanged(int index);

    // 实现背景的取消和设置
    void on_checkBoxBackground_clicked(bool checked);

    // 实现背景网的取消和设置
    void on_checkBoxGrid_clicked(bool checked);

    // 实现坐标轴标签背景可见
    void on_checkBoxAxisBackground_clicked(bool checked);

private:
	Ui::DataVisualClass ui;
};
