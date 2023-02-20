#pragma once

//解决汉字乱码问题
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>
#include <QThread>
#include <QtDataVisualization>
#include "PI_GCS2_DLL_dynamicp_loader.h"
#include "CSCInterface_dynamicm_loader.h"
#include "ids_peak_comfort_c.h"
#include "acquisitionworker.h"
#include "CCDSetUserface.h"
#include "backend.h"
#include "display.h"
#include "ui_UFO.h"

using namespace QtDataVisualization;

class UFO : public QMainWindow
{
    Q_OBJECT

public:
    UFO(QWidget *parent = nullptr);
    ~UFO();

public:
    // 设备错误
    bool hasError();

private:
    // 设备连接状态 振镜 PI 工业相机 快门
    bool M_IsConnected{};

    bool P_IsConnected{};

    bool C_IsConnected{};

    bool S_IsConnected{};

    // 实现动画效果
    int mIndex = 1;

    int pIndex = 1;

    // PI句柄
    int ID{};

    // 记录连接轴
    char szAxes[2]{};

    // 用于 USB 设备描述的 szBuffer 缓冲区
    char szBuffer[17]{};

    // 仅其描述与过滤器匹配的控制器在缓冲区中返回
    char szFilter[17]{};

    // 返回的字符串,包括序列号和设备描述符
    char serialNo[256]{};

    // PI错误信息编号
    int iError{};

    // PI错误信息
    char szErrorMesage[1024]{};

    // PI移动位置
    double dPos[3]{};

    // PI轴等待
    BOOL bIsMoving[3]{};

    // CCD错误信息
    bool m_blockErrorMessages{};

    // CCD采集开始
    bool m_acquisitionRunning{};

    // 记录错误
    bool m_hasError{};

    // 图表的容器
    QWidget* graphContainer = nullptr;

    Q3DScatter* graph3D = nullptr;

    // 散点序列
    QScatter3DSeries* series = nullptr;

    // 数据代理
    QScatterDataProxy* proxy = nullptr;

    // 为实现数据共享，公共化参数
    QScatterDataArray* dataArray = nullptr;

    // 实现绘图
    QScatterDataItem* ptrToDataArray = nullptr;


private:
    // 实现数据读取等待提示
    QTimer* DATA_TIMER{};

    // 实现PI连接等待提示
    QTimer* PI_AXIS_TIMER{};

    // 数据读取状态
    QLabel* DataReadState{};

    // PI连接轴
    QLabel* ConnectAxis{};

    // PI实时位置
    QLabel* PiRealPos{};

    // 标刻数据量
    QLabel* MarkDataNum{};

    // 设备连接状态
    QLabel* DeviceConnectState{};

    // 振镜x位置
    QLabel* x_Position{};

    // 振镜y位置
    QLabel* y_Position{};

    // CCD窗口信息显示
    QLabel* m_labelInfo{};

    // CCD显示窗体
    QWidget* m_centralWidget{};

    // 显示图像类
    Display* m_display{};

    // 控件布局
    QHBoxLayout* Vlayout1{};

    // 控件布局
    QHBoxLayout* Vlayout2{};

    // 图像处理类
    AcquisitionWorker* m_acquisitionWorker{};

    // 实现多线程
    QThread m_acquisitionThread{};

    // 相机设置窗口
    CCDSetUserface* CCDSet{};

private:
    // 关闭窗口时间，可以询问是否退出
    void closeEvent(QCloseEvent* event);

    // 连接振镜
    int connectSystemMark();

    // 连接PI
    bool connectSystemPi();

    // 反馈PI连接信息
    void feedBackDevice();

    // 实现动画效果
    void CreateTimer();

    // 定时器1启动
    void startAnimation1();

    // 定时器1停止
    void stopAnimation1();

    // 更新文本
    void updateText1();

    // 定时器2启动
    void startAnimation2();

    // 定时器2停止
    void stopAnimation2();

    // 更新文本
    void updateText2();

    // 初始化实时显示界面
    void InitMarkDataVisual();

    // 初始化CCD界面
    void CreateCCD();

    // CCD开始采集
    void OpenCCDLibrary();

    // 初始化界面控件
    void initButton();

    // 初始化状态栏
    void CreateStatuBar();

    // 创建数据标刻线程
    void CreateMarkWorkerThread();

    // 创建信号槽
    void CreateAcquisitionWorkerThreadCCD();

    // 创建信号槽
    void CreateAcquisitionWorkerThreadPI();

    // 开始采集PI位置
    void StartAcquisitionPI();

    // 启动采集
    void StartAcquisition();

    // 停止采集
    void StopAcquisition();

private slots:
    // 处理错误信息
    void HandleLibraryError(QString message, int status);

    // 发送错误信号
    static void EmitErrorSignal(const char* message, int status, void* errorCallbackContext);

    // Qt about 超链接
    void OnAboutQtLinkActivated(const QString& link);

    // CCD采集控制
    void OnButtonStopStart();

    // 更新错误数量（CCD采集时）
    void OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter);

    // 根据错误的信息，决定是否提前退出程序
    void HandleErrorAndQuit(QString message);

signals:
    // 发送错误信号提示
    void libraryError(QString message, int status);

private:
    Ui::UFO ui;
};
