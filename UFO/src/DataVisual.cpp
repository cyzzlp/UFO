#include "DataVisual.h"
#include "GlobalInfo.h"

DataVisual::DataVisual(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// ��ʼ��ͼ��
	InitGraph3D();
}

DataVisual::~DataVisual()
{

}

// ɾ��ռ�õ��ڴ�ռ�
void DataVisual::closeEvent(QCloseEvent* event)
{
    delete this;
}

void DataVisual::InitGraph3D()
{
    // ����ͼ��
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D);

    QScatterDataProxy* proxy = new QScatterDataProxy(); //���ݴ���
    series = new QScatter3DSeries(proxy); //��������
    series->setItemLabelFormat("@xLabel @yLabel @zLabel");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);

    //����������
    graph3D->axisX()->setTitle("X��");
    graph3D->axisX()->setTitleVisible(true);

    graph3D->axisY()->setTitle("Y��");
    graph3D->axisY()->setTitleVisible(true);

    graph3D->axisZ()->setTitle("Z��");
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    // ���ݵ�ΪԲ��
    series->setMesh(QAbstract3DSeries::MeshSphere);

    // ȡֵ��Χ0~1 ���Զ���������
    series->setItemSize(0.2);

    // ���õ�ѡ��ʱ�ĸ�����ɫ
    series->setSingleHighlightColor(QColor(0, 0, 255));
}

// ��ͼ
void DataVisual::DrawData(QVector<QVector<double>> PointArr)
{
    int cutnum = 0;
    int itemCount = GlobalInfo::MarkTextRows;
    int itemCountColums = GlobalInfo::MarkTextColumns;
    if (itemCount > 50000)
    {
        cutnum = itemCount / 50000;
        dataArray = new QScatterDataArray();
        // MarkTextRows����
        int sub_num = itemCount / (cutnum + 5);
        dataArray->resize(sub_num);
        ptrToDataArray = &dataArray->first();

        // ���������ֵ
        double x, y, z;
        if (itemCountColums == 3)
        {
            for (int i = 0; i < itemCount; i++)
            {
                if (i % (cutnum + 5) == 0)
                {
                    x = PointArr[i][0];
                    y = PointArr[i][1];
                    z = PointArr[i][2];

                    // ��ӵ�����
                    ptrToDataArray->setPosition(QVector3D(x, y, z));

                    // ָ���һ
                    ptrToDataArray++;
                }
            }
        }
        series->dataProxy()->resetArray(dataArray);

        // ��ͼ
        ui.verticalLayout_graph3D->addWidget(graphContainer);
    }

    if (itemCount < 50000)
    {
        dataArray = new QScatterDataArray();
        // MarkTextRows����
        dataArray->resize(itemCount);
        ptrToDataArray = &dataArray->first();

        // ���������ֵ
        double x, y, z;

        if (itemCountColums == 3)
        {
            for (int i = 0; i < itemCount; i++)
            {
                x = PointArr[i][0];
                y = PointArr[i][1];
                z = PointArr[i][2];

                // ��ӵ�����
                ptrToDataArray->setPosition(QVector3D(x, y, z));

                // ָ���һ
                ptrToDataArray++;
            }
        }
        series->dataProxy()->resetArray(dataArray);

        // ��ͼ
        ui.verticalLayout_graph3D->addWidget(graphContainer);
    }
}

// ѡ���ӽ�
void DataVisual::on_comboCamera_currentIndexChanged(int index)
{
    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(index);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);
}

// ʵ�ֵ���ʽ����
void DataVisual::on_comboPointType_currentIndexChanged(int index)
{
    if (index == 0)
        series->setMesh(QAbstract3DSeries::MeshSphere);

    if (index == 1)
        series->setMesh(QAbstract3DSeries::MeshBar);

    if (index == 2)
        series->setMesh(QAbstract3DSeries::MeshBevelCube);

    if (index == 3)
        series->setMesh(QAbstract3DSeries::MeshCube);

    if (index == 4)
        series->setMesh(QAbstract3DSeries::MeshCone);

    if (index == 5)
        series->setMesh(QAbstract3DSeries::MeshPyramid);
}

// ʵ��ˮƽ��ת
void DataVisual::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui.sliderH->value();  // ˮƽ��ת
    int yRot = ui.sliderV->value();  // ��ֱ��ת
    int zoom = ui.sliderZoom->value();  // ͼ������

    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}

// ʵ�ִ�ֱ��ת
void DataVisual::on_sliderV_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui.sliderH->value();  // ˮƽ��ת
    int yRot = ui.sliderV->value();  // ��ֱ��ת
    int zoom = ui.sliderZoom->value();  // ͼ������

    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}

// ʵ�����������
void DataVisual::on_sliderPoint_valueChanged(int value)
{
    Q_UNUSED(value);
    int point = ui.sliderPoint->value();
    double PointSize = point / 100;

    series->setItemSize(PointSize); //ȡֵ��Χ0~1 ���Զ���������
}

// ʵ��ͼ������
void DataVisual::on_sliderZoom_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui.sliderH->value();  // ˮƽ��ת
    int yRot = ui.sliderV->value();  // ��ֱ��ת
    int zoom = ui.sliderZoom->value();  // ͼ������

    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}

// ʵ���л�ͼ������
void DataVisual::on_comboTheme_currentIndexChanged(int index)
{
    //��������
    Q3DTheme* currentTheme = graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

// ʵ�ֱ�����ȡ��������
void DataVisual::on_checkBoxBackground_clicked(bool checked)
{
    //ͼ��ı���
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

// ʵ�ֱ�������ȡ��������
void DataVisual::on_checkBoxGrid_clicked(bool checked)
{
    //ͼ�������
    graph3D->activeTheme()->setGridEnabled(checked);
}

// ʵ���������ǩ�����ɼ�
void DataVisual::on_checkBoxAxisBackground_clicked(bool checked)
{
    //���ǩ����
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}
