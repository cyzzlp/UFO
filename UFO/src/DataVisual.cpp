#include "DataVisual.h"
#include "GlobalInfo.h"

DataVisual::DataVisual(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// 初始化图表
	InitGraph3D();
}

DataVisual::~DataVisual()
{

}

// 删除占用的内存空间
void DataVisual::closeEvent(QCloseEvent* event)
{
    delete this;
}

void DataVisual::InitGraph3D()
{
    // 创建图表
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D);

    QScatterDataProxy* proxy = new QScatterDataProxy(); //数据代理
    series = new QScatter3DSeries(proxy); //创建序列
    series->setItemLabelFormat("@xLabel @yLabel @zLabel");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);

    //创建坐标轴
    graph3D->axisX()->setTitle("X轴");
    graph3D->axisX()->setTitleVisible(true);

    graph3D->axisY()->setTitle("Y轴");
    graph3D->axisY()->setTitleVisible(true);

    graph3D->axisZ()->setTitle("Z轴");
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    // 数据点为圆球
    series->setMesh(QAbstract3DSeries::MeshSphere);

    // 取值范围0~1 ，自动放缩因子
    series->setItemSize(0.2);

    // 设置点选中时的高亮颜色
    series->setSingleHighlightColor(QColor(0, 0, 255));
}

// 绘图
void DataVisual::DrawData(QVector<QVector<double>> PointArr)
{
    int cutnum = 0;
    int itemCount = GlobalInfo::MarkTextRows;
    int itemCountColums = GlobalInfo::MarkTextColumns;
    if (itemCount > 50000)
    {
        cutnum = itemCount / 50000;
        dataArray = new QScatterDataArray();
        // MarkTextRows个点
        int sub_num = itemCount / (cutnum + 5);
        dataArray->resize(sub_num);
        ptrToDataArray = &dataArray->first();

        // 坐标点坐标值
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

                    // 添加点数据
                    ptrToDataArray->setPosition(QVector3D(x, y, z));

                    // 指针加一
                    ptrToDataArray++;
                }
            }
        }
        series->dataProxy()->resetArray(dataArray);

        // 绘图
        ui.verticalLayout_graph3D->addWidget(graphContainer);
    }

    if (itemCount < 50000)
    {
        dataArray = new QScatterDataArray();
        // MarkTextRows个点
        dataArray->resize(itemCount);
        ptrToDataArray = &dataArray->first();

        // 坐标点坐标值
        double x, y, z;

        if (itemCountColums == 3)
        {
            for (int i = 0; i < itemCount; i++)
            {
                x = PointArr[i][0];
                y = PointArr[i][1];
                z = PointArr[i][2];

                // 添加点数据
                ptrToDataArray->setPosition(QVector3D(x, y, z));

                // 指针加一
                ptrToDataArray++;
            }
        }
        series->dataProxy()->resetArray(dataArray);

        // 绘图
        ui.verticalLayout_graph3D->addWidget(graphContainer);
    }
}

// 选择视角
void DataVisual::on_comboCamera_currentIndexChanged(int index)
{
    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(index);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);
}

// 实现点样式设置
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

// 实现水平旋转
void DataVisual::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui.sliderH->value();  // 水平旋转
    int yRot = ui.sliderV->value();  // 垂直旋转
    int zoom = ui.sliderZoom->value();  // 图像缩放

    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}

// 实现垂直旋转
void DataVisual::on_sliderV_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui.sliderH->value();  // 水平旋转
    int yRot = ui.sliderV->value();  // 垂直旋转
    int zoom = ui.sliderZoom->value();  // 图像缩放

    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}

// 实现坐标点缩放
void DataVisual::on_sliderPoint_valueChanged(int value)
{
    Q_UNUSED(value);
    int point = ui.sliderPoint->value();
    double PointSize = point / 100;

    series->setItemSize(PointSize); //取值范围0~1 ，自动放缩因子
}

// 实现图像缩放
void DataVisual::on_sliderZoom_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot = ui.sliderH->value();  // 水平旋转
    int yRot = ui.sliderV->value();  // 垂直旋转
    int zoom = ui.sliderZoom->value();  // 图像缩放

    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot, zoom);
}

// 实现切换图像主题
void DataVisual::on_comboTheme_currentIndexChanged(int index)
{
    //设置主题
    Q3DTheme* currentTheme = graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

// 实现背景的取消和设置
void DataVisual::on_checkBoxBackground_clicked(bool checked)
{
    //图表的背景
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

// 实现背景网的取消和设置
void DataVisual::on_checkBoxGrid_clicked(bool checked)
{
    //图标的网格
    graph3D->activeTheme()->setGridEnabled(checked);
}

// 实现坐标轴标签背景可见
void DataVisual::on_checkBoxAxisBackground_clicked(bool checked)
{
    //轴标签背景
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}
