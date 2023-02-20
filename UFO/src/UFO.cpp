#include "UFO.h"

UFO::UFO(QWidget* parent)
    : QMainWindow(parent)
{
    // 窗口最大化显示
    setWindowState(Qt::WindowMaximized);

    // 连接振镜
    int isConnect = connectSystemMark();
    if (!isConnect)
        QMessageBox::critical(nullptr, "Mark", "没有板卡不能标刻");

    // 连接PI
    isConnect = connectSystemPi();
    if (!isConnect)
        QMessageBox::critical(nullptr, "PI", szErrorMesage);

    // 记录连接信息
    feedBackDevice();

    ui.setupUi(this);

    // 将后端的错误回调连接到UFO
    connect(this, &UFO::libraryError, this, &UFO::HandleLibraryError);
    backend_errorCallback_connect(this, &UFO::EmitErrorSignal);

    // 初始化实时显示界面
    InitMarkDataVisual();

    // 实现动画效果
    CreateTimer();

    // 初始化状态栏
    CreateStatuBar();

    // 初始化CCD界面
    CreateCCD();

    // 启动CCD采集
    OpenCCDLibrary();

    // 初始化界面控件
    initButton();

    // 如果设备连接失败
    if (!C_IsConnected)
        return;

    // 实时获取PI位置
    CreateAcquisitionWorkerThreadPI();

    // 开始采集PI位置 
    StartAcquisitionPI();

    // 图像采集准备
    backend_acquisition_prepare();

    // 创建数据采集线程
    CreateAcquisitionWorkerThreadCCD();

    // 启动图像采集
    StartAcquisition();

    // 创建数据标刻线程
    CreateMarkWorkerThread();
}

UFO::~UFO()
{

}

// 关闭窗口时间，可以询问是否退出
void UFO::closeEvent(QCloseEvent* event)
{
    // 窗口关闭时询问是否退出
    QMessageBox::StandardButton result = QMessageBox::question(this, "系统", "确定要退出本程序吗？",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
        QMessageBox::Yes);

    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

// 连接振镜
int UFO::connectSystemMark()
{
    // ReturnFunc
    int returnValue = 0;

    // 搜索驱动文件所在的位置，绝对路径
    char fpgaPaths[MAX_PATH + 1]{};
    GetModuleFileNameA(nullptr, fpgaPaths, MAX_PATH);
    std::string FirmwareProgram = const_cast<char*>(fpgaPaths);
    int index = FirmwareProgram.find_last_of("\\");
    std::string folderPath = FirmwareProgram.substr(0, index);
    std::string fpgaPath = folderPath + "\\" + "FpgaFirmware.rbf";

    // string转char*
    char* filePath = const_cast<char*>(fpgaPath.c_str());
    
    // 连接板卡
    returnValue = OpenUSB_Board(0, NULL);
    returnValue = LoadFPGA_FirmwareProgram(filePath);

    // 0 == false  其他 == true
    if (returnValue < 0)
        return 0;

    // 振镜回零点
    Goto_XY(0, 0);

    // 振镜连接
    M_IsConnected = true;

    return 1;
}

// 连接PI
bool UFO::connectSystemPi()
{
    // 获得USB需要的参数
    PI_EnumerateUSB(szBuffer, 17, szFilter);

    // 通过USB连接
    ID = PI_ConnectUSB(szBuffer);
    if (ID < 0)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // 获取所有已配置轴的标识符
    BOOL returnValue = PI_qSAI(ID, szAxes, 16);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // 为字符串“axes”中的轴启用伺服
    BOOL bFlags[3] = { 0 };
    bFlags[0] = TRUE;

    // 调用伺服模式命令
    returnValue = PI_SVO(ID, szAxes, bFlags);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // PI归零
    dPos[0] = 0.0;

    // 换层(移动z轴位置)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }
    // 选择等待轴
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // 获得连接轴的位置
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            return false;
        }

        returnValue = PI_IsMoving(ID, NULL, bIsMoving);
        if (!returnValue)
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            PI_CloseConnection(ID);
            return false;
        }
    }

    // PI是否连接
    P_IsConnected = PI_IsConnected(ID);
    if (!P_IsConnected)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    return true;
}

// 实现动画效果
void UFO::CreateTimer()
{
    // 实现等待动画
    DATA_TIMER = new QTimer();

    // 实现等待动画
    PI_AXIS_TIMER = new QTimer();

    // 设定超时时间500毫秒
    DATA_TIMER->setInterval(500);
    connect(DATA_TIMER, &QTimer::timeout, this, &UFO::updateText1);

    // 设定超时时间500毫秒
    PI_AXIS_TIMER->setInterval(500);
    connect(PI_AXIS_TIMER, &QTimer::timeout, this, &UFO::updateText2);
}

// 设备连接信息
void UFO::feedBackDevice()
{

}

// 处理错误信息
void UFO::HandleLibraryError(QString message, int status)
{
    // 由于关键消息而阻止所有错误消息
    if (m_blockErrorMessages)
        return;

    message.prepend("Error: ");

    QMessageBox::warning(nullptr, "Error", message, QMessageBox::Ok);
}

// 发送错误信号
void UFO::EmitErrorSignal(const char* message, int status, void* errorCallbackContext)
{
    emit static_cast<UFO*>(errorCallbackContext)->libraryError(QString::fromStdString(message), status);
};

// 启动定时器
void UFO::startAnimation1()
{
    DATA_TIMER->start();
}

// 启动定时器
void UFO::startAnimation2()
{
    PI_AXIS_TIMER->start();
}

// 停止定时器
void UFO::stopAnimation1()
{
    DATA_TIMER->stop();
}

// 停止定时器
void UFO::stopAnimation2()
{
    PI_AXIS_TIMER->stop();
}

// 更新文本
void UFO::updateText1()
{
    // 若当前超过4表示到达末尾
    ++mIndex;

    if (mIndex > 4)
        mIndex = 1;

    if (mIndex == 1)
    {
        DataReadState->setText("读取状态：等待");
    }

    if (mIndex == 2)
    {
        DataReadState->setText("读取状态：等待.");
    }

    if (mIndex == 3)
    {
        DataReadState->setText("读取状态：等待..");
    }

    if (mIndex == 4)
    {
        DataReadState->setText("读取状态：等待...");
    }
}

// 更新文本
void UFO::updateText2()
{
    // 若当前超过4表示到达末尾
    ++pIndex;

    if (pIndex > 4)
        pIndex = 1;

    if (pIndex == 1)
    {
        ConnectAxis->setText("PI连接轴：等待连接");
    }

    if (pIndex == 2)
    {
        ConnectAxis->setText("PI连接轴：等待连接.");
    }

    if (pIndex == 3)
    {
        ConnectAxis->setText("PI连接轴：等待连接..");
    }

    if (pIndex == 4)
    {
        ConnectAxis->setText("PI连接轴：等待连接...");
    }
}

// CCD开始采集
void UFO::OpenCCDLibrary()
{
    // 后台启动功能：打开图库，打开相机
    int status = backend_start();
    if (status != 0)
    {
        m_hasError = true;
        m_blockErrorMessages = true;
        backend_exit();
        return;
    }

    // CCD连接状态
    C_IsConnected = true;
}

// 创建实时显示标刻点位置的窗口
void UFO::InitMarkDataVisual()
{
    Q3DScatter* graph3D;
    // 创建图表
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D);

    // 数据代理
    proxy = new QScatterDataProxy();

    // 创建序列
    series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat("@xLabel @zLabel @yLabel");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);

    // 创建坐标轴
    graph3D->axisX()->setTitle("axis Y");
    graph3D->axisX()->setTitleVisible(true);

    graph3D->axisY()->setTitle("axis Z");
    graph3D->axisY()->setTitleVisible(true);

    graph3D->axisZ()->setTitle("axis X");
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    // 数据点为圆球
    series->setMesh(QAbstract3DSeries::MeshSphere);

    // 取值范围0~1 ，自动放缩因子
    series->setItemSize(0.05);

    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(Q3DCamera::CameraPresetFront);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);

    ui.verticalLayout_graph3D->addWidget(graphContainer);
}

// 初始化CCD界面
void UFO::CreateCCD()
{
    // 创建图像显示窗口
    m_centralWidget = new QWidget(this);
    ui.ccdLayout ->addWidget(m_centralWidget);

    // 为相机图像创建显示，创建CCD信息显示控件
    m_display = new Display(m_centralWidget);
    ui.ccdLayout->addWidget(m_display);

    auto hLayoutInfo = new QHBoxLayout();
    ui.ccdLayout->addLayout(hLayoutInfo);

    m_labelInfo = new QLabel(this);
    hLayoutInfo->addWidget(m_labelInfo);
    hLayoutInfo->addStretch();

    auto m_labelVersion = new QLabel(("ipl_features_live_qtwidgets_c v" VERSION), this);
    hLayoutInfo->addWidget(m_labelVersion);

    auto m_labelAboutQt = new QLabel(R"(<a href="#aboutQt">About Qt</a>)", this);
    connect(m_labelAboutQt, &QLabel::linkActivated, this, &UFO::OnAboutQtLinkActivated);
    hLayoutInfo->addWidget(m_labelAboutQt);

    this->show();
}

// Qt的about
void UFO::OnAboutQtLinkActivated(const QString& link)
{
    if (link == "#aboutQt")
    {
        QMessageBox::aboutQt(this, "About Qt");
    }
}

// 初始化界面控件
void UFO::initButton()
{
    if (!M_IsConnected)
    {
    }

    if (!P_IsConnected)
    {
    }

    if (!C_IsConnected)
    {

    }
}

// 初始化状态栏
void UFO::CreateStatuBar()
{
    startAnimation1();
    startAnimation2();

    // 提示数据读取状态
    DataReadState = new QLabel;
    DataReadState->setMaximumWidth(175);
    DataReadState->setMinimumWidth(175);

    // PI连接轴
    ConnectAxis = new QLabel;
    ConnectAxis->setMaximumWidth(175);
    ConnectAxis->setMinimumWidth(175);

    // PI实时位置
    PiRealPos = new QLabel;
    PiRealPos->setMaximumWidth(175);
    PiRealPos->setMinimumWidth(175);

    // 标刻数据量
    MarkDataNum = new QLabel;
    MarkDataNum->setMaximumWidth(200);
    MarkDataNum->setMinimumWidth(200);

    // 设备连接状态
    DeviceConnectState = new QLabel;
    DeviceConnectState->setMaximumWidth(175);
    DeviceConnectState->setMinimumWidth(175);

    // 振镜位置
    x_Position = new QLabel;
    y_Position = new QLabel;
    x_Position->setMaximumWidth(200);
    x_Position->setMinimumWidth(200);
    y_Position->setMaximumWidth(200);
    y_Position->setMinimumWidth(200);


    // 设置当前状态
    MarkDataNum->setText("标刻数据总量：");
    PiRealPos->setText("PI实时位置：");
    x_Position->setText("振镜x位置：0.00");
    y_Position->setText("振镜y位置：0.00");

    if (P_IsConnected)
    {
        // 停止设备连接状态文本更新
        stopAnimation2();

        DeviceConnectState->setText("设备连接成功");

        // 显示PI连接轴
        QString szAxes = QString(szAxes[0]);

        ConnectAxis->setText("PI连接轴：" + szAxes);
    }
    else
    {
        DeviceConnectState->setText("设备连接失败");
    }

    QWidget* widget = new QWidget();
    Vlayout1 = new QHBoxLayout();
    Vlayout1->addWidget(DataReadState);
    Vlayout1->addWidget(ConnectAxis);
    Vlayout1->addWidget(PiRealPos);
    Vlayout1->addWidget(MarkDataNum);
    widget->setLayout(Vlayout1);
    ui.statusBar->addWidget(widget);

    QWidget* widget1 = new QWidget();
    Vlayout2 = new QHBoxLayout();
    Vlayout2->addWidget(x_Position);
    Vlayout2->addWidget(y_Position);
    Vlayout2->addWidget(DeviceConnectState);
    widget1->setLayout(Vlayout2);

    // 在最右侧布局
    ui.statusBar->addPermanentWidget(widget1);
}

// 创建信号槽
void UFO::CreateAcquisitionWorkerThreadPI()
{
    // 创建线程类
    realpos = new piRealpos();
    realpos->moveToThread(&PiThread);

    // 线程开始时，开始获取位置
    connect(&PiThread, SIGNAL(started()), realpos, SLOT(Start()), Qt::UniqueConnection);

    // 接收PI位置，实时更新
    connect(realpos, &piRealpos::PiRealPOS, this, &UFO::RefreshPiPos);

    // 更新数据读取状态
    connect(realpos, &piRealpos::DelieveWrongInfo, this, &UFO::ResetWrongText);
}

// 开始采集PI位置
void UFO::StartAcquisitionPI()
{
    // while循环为True
    realpos->start();

    // 线程启动
    PiThread.start();
}

// 创建信号槽
void UFO::CreateAcquisitionWorkerThreadCCD()
{
    // CCD参数设置窗口
    CCDSet = new CCDSetUserface;

    // 创建用于图像采集工作线程
    m_acquisitionWorker = new AcquisitionWorker();
    m_acquisitionWorker->moveToThread(&m_acquisitionThread);

    // 实现PushButton控制图像采集
    connect(ui.m_buttonStartStop, &QPushButton::clicked, this, &UFO::OnButtonStopStart);

    // worker必须启动，当采集开始时
    connect(&m_acquisitionThread, SIGNAL(started()), m_acquisitionWorker, SLOT(Start()), Qt::UniqueConnection);

    // 当接收到新图像时连接来自工作线程的信号
    // 显示类
    connect(m_acquisitionWorker, &AcquisitionWorker::imageReceived, m_display, &Display::OnImageReceived);

    // 当计数器随着 MainWindow 中的更新插槽发生变化时，连接来自工作线程的信号
    // 类
    connect(m_acquisitionWorker, &AcquisitionWorker::counterUpdated, this, &UFO::OnCounterUpdated);

    // 在采集开始时连接来自工作线程的信号
    connect(m_acquisitionWorker, &AcquisitionWorker::started, CCDSet, &CCDSetUserface::UpdateControls);

    // 当采集停止时连接来自工作线程的信号
    connect(m_acquisitionWorker, &AcquisitionWorker::stopped, CCDSet, &CCDSetUserface::UpdateControls);

    // 将工作线程的错误信号连接到 MarkControl 类中的插槽
    connect(m_acquisitionWorker, &AcquisitionWorker::error, this, &UFO::HandleErrorAndQuit);
}

// CCD采集控制
void UFO::OnButtonStopStart()
{
    if ("停止采集" == ui.m_buttonStartStop->text())
    {
        ui.m_buttonStartStop->setText("开始采集");
        StopAcquisition();
    }
    else
    {
        ui.m_buttonStartStop->setText("停止采集");
        StartAcquisition();
    }
}

// 更新错误数量（CCD采集时）
void UFO::OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter)
{
    QString strText;
    strText.sprintf("Acquired: %d, errors: %d", frameCounter, errorCounter);
    m_labelInfo->setText(strText);
}

// 根据错误的信息，决定是否提前退出程序
void UFO::HandleErrorAndQuit(QString message)
{
    // 由于关键消息而阻止所有错误消息
    if (m_blockErrorMessages)
        return;

    message += "\n(Error!)";
    message += "\nExiting application";

    QMessageBox::critical(nullptr, "Error", message, QMessageBox::Ok);
    qApp->quit();
}

// 启动采集
void UFO::StartAcquisition()
{
    // 开始执行图像采集线程
    backend_acquisition_start();

    m_acquisitionThread.start();
    m_acquisitionRunning = true;
}

// 停止采集
void UFO::StopAcquisition()
{
    // 停止执行图像采集线程
    if (m_acquisitionWorker)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();

        backend_acquisition_stop();
    }
    m_acquisitionRunning = false;
}

// 创建数据标刻线程
void UFO::CreateMarkWorkerThread()
{

}

// 实时更新PI位置
void UFO::RefreshPiPos(double u_PiPosition)
{
    // 将u_PiPosition转换为Qstring，十进制显示，4位精度
    PiRealPos->setText("PI实时位置：" + QString::number(u_PiPosition, 10, 4));
}

// 更新线程错误信息
void UFO::ResetWrongText(QString dataStatus)
{
    // 停止读取
    realpos->stop();

    // 线程停止
    PiThread.quit();
    PiThread.wait();

    // 信息提示
    QMessageBox::critical(this, "错误", dataStatus);
}


// 程序退出
bool UFO::hasError()
{
    return m_hasError;
}