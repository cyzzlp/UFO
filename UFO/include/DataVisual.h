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
	// ��ͼ
	void DrawData(QVector<QVector<double>> PointArr);

private:
    // Ϊʵ�����ݹ�������������
    QScatterDataArray* dataArray = nullptr;

    QScatterDataItem* ptrToDataArray = nullptr;

    // ͼ�������
    QWidget* graphContainer{};

    // ɢ��ͼ
    Q3DScatter* graph3D{};

    // ɢ������
    QScatter3DSeries* series{};

    // ��ȡ������Ϣ
    QSettings* DataInfo{};

private slots:
    // �رմ����¼�
    void closeEvent(QCloseEvent* event);

    // ��ʼ��
    void InitGraph3D();

    // ѡ���ӽ�
    void on_comboCamera_currentIndexChanged(int index);

    // ʵ��ˮƽ��ת
    void on_sliderH_valueChanged(int value);

    // ʵ�ִ�ֱ��ת
    void on_sliderV_valueChanged(int value);

    // ʵ�����������
    void on_sliderPoint_valueChanged(int value);

    // ʵ��ͼ������
    void on_sliderZoom_valueChanged(int value);

    // ʵ�ֵ���ʽ����
    void on_comboPointType_currentIndexChanged(int index);

    // ʵ���л�ͼ������
    void on_comboTheme_currentIndexChanged(int index);

    // ʵ�ֱ�����ȡ��������
    void on_checkBoxBackground_clicked(bool checked);

    // ʵ�ֱ�������ȡ��������
    void on_checkBoxGrid_clicked(bool checked);

    // ʵ���������ǩ�����ɼ�
    void on_checkBoxAxisBackground_clicked(bool checked);

private:
	Ui::DataVisualClass ui;
};
