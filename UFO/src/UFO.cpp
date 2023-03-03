#include "UFO.h"
   
UFO::UFO(QWidget* parent)
    : QMainWindow(parent)
{
    // 窗口最大化显示
    setWindowState(Qt::WindowMaximized);

    // 获取Icon文件路径
    QString m_FileName = QCoreApplication::applicationDirPath() + "/Icon/ufo.png";

    // 所以窗口Icon均设为选定的图像
    QApplication::setWindowIcon(QIcon(m_FileName));

    // 连接振镜
    int isConnect = connectSystemMark();
    if (!isConnect)
        QMessageBox::warning(nullptr, "振镜", "没有板卡不能标刻，请检查振镜连接");

    // 连接PI
    isConnect = connectSystemPi();
    if (!isConnect)
        QMessageBox::warning(nullptr, "PI", szErrorMesage);

    // 连接快门
     isConnect = connectSystemShutter();
     if (!isConnect)
         QMessageBox::warning(nullptr, "快门", "CH375快门连接失败，请检查快门连接");

     // 连接CCD
     isConnect = connectSystemCCD();
     if (!isConnect)
         QMessageBox::warning(nullptr, "CCD", "CCD连接失败，请检查快门连接");

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

    // 初始化界面控件
    initButton();

    // 生成配置文件
    InitSetting();

    // 准备标刻线程
    CreateMarkWorkerThread();

    // 如果设备连接失败
    if (!isConnect)
        return;

    // 图像采集准备
    backend_acquisition_prepare();

    // 创建数据采集线程
    CreateAcquisitionWorkerThreadCCD();

    // 启动图像采集
    StartAcquisition();

    // 实时获取PI位置
    CreateAcquisitionWorkerThreadPI();

    // 开始采集PI位置 
    StartAcquisitionPI();

    // 准备标刻线程
    CreateMarkWorkerThread();
}

UFO::~UFO()
{
    if (GlobalInfo::pthread)
    {
        realpos->stop();
        PiThread.quit();
        PiThread.wait();
    }

    if (GlobalInfo::mthread)
    {
        MarkThreads->Stop();
        MarktoThread.quit();
        MarktoThread.wait();
    }

    // CCD图像采集线程退出
    if (GlobalInfo::cthread)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();
    }

    // 振镜断开
    if (GlobalInfo::m_Connect)
        CloseUSB_Board();

    // PI断开
    if (GlobalInfo::p_Connect)
        PI_CloseConnection(GlobalInfo::ID);

    // 相机断开
    if(GlobalInfo::c_Connect)
        backend_exit();
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
    // 记录函数返回值
    int returnValue = 0;

    // 获取FPGA硬件驱动文件所在的位置
    QString fpgaPath = QCoreApplication::applicationDirPath() + "/FpgaFirmware.rbf";
    QByteArray Path = fpgaPath.toLatin1();
    char* filePath = Path.data();
    
    // 连接板卡
    returnValue = OpenUSB_Board(0, NULL);
    returnValue = LoadFPGA_FirmwareProgram(filePath);

    // 0 == false  其他 == true
    if (returnValue < 0)
        return 0;

    // 振镜回零点
    Goto_XY(0, 0);

    // 振镜连接
    GlobalInfo::m_Connect = true;

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
    BOOL returnValue = PI_qSAI(ID, szAxesed, 16);
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
    returnValue = PI_SVO(ID, szAxesed, bFlags);
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
    returnValue = PI_MOV(ID, szAxesed, dPos);
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
        returnValue = PI_qPOS(ID, szAxesed, dPos);
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
    returnValue = PI_IsConnected(ID);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // 保存连接相机句柄
    GlobalInfo::ID = ID;
    GlobalInfo::szAxes[0] = szAxesed[0];
    GlobalInfo::szAxes[1] = szAxesed[1];

    // 保存PI连接状态
    GlobalInfo::p_Connect = true;

    return true;
}

// 连接快门
int UFO::connectSystemShutter()
{
    unsigned long ioLength = 1;
    unsigned long* p_ioLength = &ioLength;
    int a = 0x0a;

    // 连接快门
    HANDLE Shutter = CH375OpenDevice(index);
    if (Shutter == INVALID_HANDLE_VALUE)
    {
        GlobalInfo::s_Connect = false;
        return 0;
    }

    // 设置延时
    CH375SetTimeout(index, 2000, 2000);

    // 向快门写入数据，并关闭快门
    int iBuffer = a & 0x0a;
    CH375WriteData(index, &iBuffer, p_ioLength);

    // 保存快门连接状态
    GlobalInfo::s_Connect = true;

    return 1;
}

// 连接CCD
int UFO::connectSystemCCD()
{
    // 后台启动功能：打开图库，打开相机
    int status = backend_start();
    if (status != 0)
    {
        m_hasError = true;
        m_blockErrorMessages = true;
        backend_exit();
        return 0;
    }

    // CCD连接状态
    GlobalInfo::c_Connect = true;

    return 1;
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

// 处理错误信息
void UFO::HandleLibraryError(QString message, int status)
{
    // 由于关键消息而阻止所有错误消息
    if (m_blockErrorMessages)
        return;

    // 把"Error: "加到message前面
    message.prepend("Error: ");

    // 显示错误
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

// 创建实时显示标刻点位置的窗口
void UFO::InitMarkDataVisual()
{
    // 3D散点图
    Q3DScatter* graph3D;

    // 创建图表
    graph3D = new Q3DScatter();

    // 设定画布
    graphContainer = QWidget::createWindowContainer(graph3D);

    // 数据代理
    proxy = new QScatterDataProxy();

    // 创建序列
    series = new QScatter3DSeries(proxy);

    // 标签
    series->setItemLabelFormat("@xLabel @zLabel @yLabel");
    
    // 光滑性
    series->setMeshSmooth(true);

    // 添加序列
    graph3D->addSeries(series);

    // 创建坐标轴
    graph3D->axisX()->setTitle("axis Y");

    // 坐标轴可见
    graph3D->axisX()->setTitleVisible(true);

    // 创建坐标轴
    graph3D->axisY()->setTitle("axis Z");

    // 坐标轴可见
    graph3D->axisY()->setTitleVisible(true);

    // 创建坐标轴
    graph3D->axisZ()->setTitle("axis X");

    // 坐标轴可见
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    // 数据点为圆球
    series->setMesh(QAbstract3DSeries::MeshSphere);

    // 取值范围0~1 ，自动放缩因子
    series->setItemSize(0.05);

    // 变换视角
    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(Q3DCamera::CameraPresetFront);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);

    // 布局
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
        QMessageBox::aboutQt(nullptr, "About Qt");
    }
}

// 初始化界面控件
void UFO::initButton()
{
    // 如果CCD未连接
    if (!GlobalInfo::c_Connect)
    {
        ui.m_buttonStartStop->setEnabled(false);
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

    if (GlobalInfo::p_Connect)
    {
        // 停止设备连接状态文本更新
        stopAnimation2();

        DeviceConnectState->setText("设备连接成功");

        // 显示PI连接轴
        QString szAxes = szAxesed[0];

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
    // 线程启动
    PiThread.start();

    // 同步状态
    GlobalInfo::pthread = true;
}

// 创建信号槽
void UFO::CreateAcquisitionWorkerThreadCCD()
{
    // CCD参数设置窗口
    CCDSet = new CCDSetUserface();

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
        GlobalInfo::cthread = false;
        StopAcquisition();
    }
    else
    {
        ui.m_buttonStartStop->setText("停止采集");
        GlobalInfo::cthread = true;
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

    // 线程启动
    m_acquisitionThread.start();

    // 同步状态
    m_acquisitionRunning = true;
    GlobalInfo::cthread = m_acquisitionRunning;
}

// 停止采集
void UFO::StopAcquisition()
{
    // 停止执行图像采集线程
    if (m_acquisitionWorker)
    {
        // 线程停止
        m_acquisitionWorker->Stop();

        // 线程退出
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();

        // 停止图像采集
        backend_acquisition_stop();
    }

    // 同步状态
    m_acquisitionRunning = false;
    GlobalInfo::cthread = m_acquisitionRunning;
}

// 创建数据标刻线程
void UFO::CreateMarkWorkerThread()
{
    MarkThreads = new markThread();
    MarkThreads->moveToThread(&MarktoThread);

    // 线程开始时，开始标刻
    connect(&MarktoThread, SIGNAL(started()), MarkThreads, SLOT(Start()), Qt::UniqueConnection);
    
    // 显示标刻中出现的错误
    connect(MarkThreads, &markThread::EmitWrongInfo, this, &UFO::ResetWrongTexts);

    // 实时显示振镜的位置
    connect(MarkThreads, &markThread::MarkRealPos, this, &UFO::showPosition);
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
    // 如果函数调用出现问题，停止读取
    realpos->stop();

    // 线程停止
    PiThread.quit();
    PiThread.wait();

    // 信息提示
    QMessageBox::critical(nullptr, "错误", dataStatus);
}

// 更新线程错误信息
void UFO::ResetWrongTexts(QString dataStatus)
{
    // 线程停止
    MarkThreads->Stop();

    // 信息提示
    QMessageBox::critical(nullptr, "PI", dataStatus);
}

// 生成ini文件
void UFO::InitSetting()
{
    // 读取当前程序可执行程序绝对路径
    m_FileName = QCoreApplication::applicationDirPath();

    // 文件绝对路径
    QString m_FileName1 = m_FileName + "/gapSetting.ini";
    QString m_FileName2 = m_FileName + "/correctWayRead.ini";
    QString m_FileName3 = m_FileName + "/correctSetting.ini";
    QString m_FileName4 = m_FileName + "/laserSetting.ini";
    QString m_FileName5 = m_FileName + "/systemSetting.ini";

    gapReadini = new QSettings(m_FileName1, QSettings::IniFormat);
    correctWayReadini = new QSettings(m_FileName2, QSettings::IniFormat);
    correctReadini = new QSettings(m_FileName3, QSettings::IniFormat);
    laserReadini = new QSettings(m_FileName4, QSettings::IniFormat);
    systemReadini = new QSettings(m_FileName5, QSettings::IniFormat);

    // 设置默认值gapSetting.ini
    gapReadini->setValue("xGap", 1);
    gapReadini->setValue("yGap", 1);
    gapReadini->setValue("dataType", false);

    // correctWayRead.ini
    correctWayReadini->setValue("fixWay", false);
    correctWayReadini->setValue("firstZero", false);

    // correctSetting.ini
    correctReadini->setValue("rangeX", 110.0);
    correctReadini->setValue("rangeY", 110.0);
    correctReadini->setValue("exchangeXY", false);
    correctReadini->setValue("invertX", false);
    correctReadini->setValue("invertY", false);
    correctReadini->setValue("xCorrection", 0.0);
    correctReadini->setValue("yCorrection", 0.0);
    correctReadini->setValue("xShear", 0.0);
    correctReadini->setValue("yShear", 0.0);
    correctReadini->setValue("xLadder", 0.0);
    correctReadini->setValue("yLadder", 0.0);
    correctReadini->setValue("ratioX", 1.0);
    correctReadini->setValue("ratioY", 1.0);
    correctReadini->setValue("ratioZ", 1.0);
    correctReadini->setValue("filePath", "please choose a file Path!");
    correctReadini->setValue("startMarkMode", 0);
    correctReadini->setValue("CorrectFile", 110);

     // laserSetting.ini
    laserReadini->setValue("laserType", 0);
    laserReadini->setValue("standby", 0);
    laserReadini->setValue("frequency", 20);
    laserReadini->setValue("pulseWidth", 10);

    // systemSetting.ini
    systemReadini->setValue("INDEX", 0);
    systemReadini->setValue("markCounts", 1);
    systemReadini->setValue("isBitmap", 0);
    systemReadini->setValue("markSpeed", 5);
    systemReadini->setValue("jumpSpeed", 3000);
    systemReadini->setValue("jumpDelay", 400);
    systemReadini->setValue("polygonDelay", 50);
    systemReadini->setValue("laserOnDelay", 100);
    systemReadini->setValue("laserOffDelay", 200);
    systemReadini->setValue("polygonKillerTime", 25);
    systemReadini->setValue("laserFrequency", 30);
    systemReadini->setValue("current", 55);
    systemReadini->setValue("firstPulseKillerLength", 100);
    systemReadini->setValue("pulseWidth", 30);
    systemReadini->setValue("firstPulseWidth", 10 );
    systemReadini->setValue("incrementStep", 10);
    systemReadini->setValue("dotSpace", 0.1);

    // 保存及关闭配置文件
    gapReadini->sync();
    correctWayReadini->sync();
    correctReadini->sync();
    laserReadini->sync();
    systemReadini->sync();

    // 删除指针
    delete gapReadini;
    delete correctWayReadini;
    delete correctReadini;
    delete laserReadini;
    delete systemReadini;
}

// 显示数据间隔及类型设置窗口
void UFO::on_actPreGapInput_triggered()
{
    // 构造当前窗口
    gap = new dataSortgap();

    // 窗口大小固定
    gap->setFixedSize(gap->width(), gap->height());

    // 阻塞整个应用程序的所有其他窗口响应
    gap->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    gap->show();
}

// 校正方法设置窗口
void UFO::on_actCorrectMethod_triggered()
{
    // 构造当前窗口
    corrWay = new MarkCorrType();

    // 窗口大小固定
    corrWay->setFixedSize(corrWay->width(), corrWay->height());

    // 阻塞整个应用程序的所有其他窗口响应
    corrWay->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    corrWay->show();
}

// 激光器窗口
void UFO::on_actSetLaser_triggered()
{
    // 构造当前窗口
    laserset = new laserSet();

    // 窗口大小固定
    laserset->setFixedSize(laserset->width(), laserset->height());

    // 阻塞整个应用程序的所有其他窗口响应
    laserset->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    laserset->show();
}

// 校正方法设置窗口
void UFO::on_actSetMarkArea_triggered()
{
    // 读取文件
    QString m_FileName2 = m_FileName + "/correctWayRead.ini";
    correctWayReadini = new QSettings(m_FileName2, QSettings::IniFormat);

    // 读取设置参数
    bool correctWay = correctWayReadini->value("fixWay").toBool();
    if (!correctWay)
    {
        markSet2 = new MarkAreaSet2();

        // 窗口大小固定
        markSet2->setFixedSize(markSet2->width(), markSet2->height());

        // 阻塞整个应用程序的所有其他窗口响应
        markSet2->setWindowModality(Qt::ApplicationModal);

        // 显示窗口
        markSet2->show();
    }
    else
    {
        markSet1 = new MarkAreaSet1();

        // 窗口大小固定
        markSet1->setFixedSize(markSet1->width(), markSet1->height());

        // 阻塞整个应用程序的所有其他窗口响应
        markSet1->setWindowModality(Qt::ApplicationModal);

        // 显示窗口
        markSet1->show();
    }
}

// 标刻参数窗口
void UFO::on_actSetSystemPara_triggered()
{
    // 构造当前窗口
    paraSet = new MarkParaSet();

    // 窗口大小固定
    paraSet->setFixedSize(paraSet->width(), paraSet->height());

    // 阻塞整个应用程序的所有其他窗口响应
    paraSet->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    paraSet->show();
}

// 显示PI设置界面
void UFO::on_actConnectPI_triggered()
{
    piSet = new piControl();

    // 窗口大小固定
    piSet->setFixedSize(piSet->width(), piSet->height());

    // 阻塞整个应用程序的所有其他窗口响应
    piSet->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    piSet->show();
}

// 显示快门设置界面
void UFO::on_actConnectShutter_triggered()
{
    shutter = new shutterControl();

    // 窗口大小固定
    shutter->setFixedSize(shutter->width(), shutter->height());

    // 阻塞整个应用程序的所有其他窗口响应
    shutter->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    shutter->show();
}

// 显示振镜设置界面
void UFO::on_actMarkSet_triggered()
{
    markSet = new MarkControl();

    // 窗口大小固定
    markSet->setFixedSize(markSet->width(), markSet->height());

    // 阻塞整个应用程序的所有其他窗口响应
    markSet->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    markSet->show();
}

// 显示相机设置界面
void UFO::on_actConnectCCD_triggered()
{
    CCDSet = new CCDSetUserface();
        
    // 窗口大小固定
    CCDSet->setFixedSize(CCDSet->width(), CCDSet->height());

    // 阻塞整个应用程序的所有其他窗口响应
    CCDSet->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    CCDSet->show();
}

// 恢复系统默认参数设置
void UFO::on_actDefaultPara_triggered()
{
    // 恢复系统参数设置
    InitSetting();
}

// 读取标刻文件
void UFO::on_actOpenFile_triggered()
{
    // 获取加工文本路径
    QString str_Filepath = QDir::currentPath();

    // 对话框标题
    QString dlgTitle = "文件";

    //文件过滤器
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)"; 
    aFileName = QFileDialog::getOpenFileName(this, dlgTitle, str_Filepath, filter);

    // 关闭定时器
    stopAnimation1();

    // 作为判断线程启动的标志
    if (!aFileName.isEmpty())
    {
        GlobalInfo::aFileName = aFileName;

        // 设置文件预设间隔
        gap = new dataSortgap();

        // 阻塞整个应用程序的所有其他窗口响应
        gap->setWindowModality(Qt::ApplicationModal);

        // 窗口大小固定
        gap->setFixedSize(gap->width(), gap->height());

        // 显示窗口
        gap->show();

        // 创建数据读取线程
        dataRead = new DataSortThread();

        // 更新数据读取状态
        connect(dataRead, &DataSortThread::setTextToLabel, this, &UFO::ResetText);

        // 更新线程错误信息
        connect(dataRead, &DataSortThread::DelieveWrongInfo, this, &UFO::ResetWrongText);

        // 显示标刻数据量
        connect(dataRead, &DataSortThread::MarkDataNum, this, &UFO::ResetDataText);

        // 启动线程
        connect(gap, &dataSortgap::isPushed, this, [=]()
            {
                // 执行读取
                dataRead->start();
            });
    }
}

// 执行显示数据可视化界面
void UFO::on_acDataVisual_triggered()
{
    dataVis = new DataVisual();

    if (DataReadState->text() == "读取状态：完成")
    {
        // 窗口大小固定
        dataVis->setFixedSize(dataVis->width(), dataVis->height());

        // 阻塞整个应用程序的所有其他窗口响应
        dataVis->setWindowModality(Qt::ApplicationModal);

        // 显示窗口
        dataVis->show();

        // 绘图
        dataVis->DrawData(MarkData::returnMarkData);
    }
    else
    {
        QMessageBox::warning(nullptr, "警告", "数据未读取或读取中，无法可视化数据！");
    }
}

// 更新数据读取状态
void UFO::ResetText(QString dataStatus)
{
    DataReadState->setText("读取状态：" + dataStatus);

    if (dataStatus == "完成")
    {
        dataRead->quit();
        dataRead->wait();
        delete dataRead;
    }
}

// 更新数据量状态
void UFO::ResetDataText(int dataNum)
{
    // double转QString
    QString Num = QString::number(dataNum);

    // 显示
    MarkDataNum->setText("标刻数据总量：" + Num);
}

// 显示振镜位置
void UFO::showPosition(double x_Pos, double y_Pos)
{
    // double转QString
    QString xPos = QString::number(x_Pos);
    QString yPos = QString::number(y_Pos);

    // 显示
    x_Position->setText("振镜x位置：" + xPos);
    y_Position->setText("振镜y位置：" + yPos);
}

// 系统信息显示
void UFO::on_actSystemInfo_triggered()
{
    on_actDefaultPara_triggered();

    // 构造当前窗口
    sysInfo = new SystemInfo();

    // 窗口大小固定
    sysInfo->setFixedSize(sysInfo->width(), sysInfo->height());

    // 阻塞整个应用程序的所有其他窗口响应
    sysInfo->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    sysInfo->show();
}

// 自定义标刻数据
void UFO::on_actYoursData_triggered()
{
    // 构造当前窗口
    yoursData = new YoursData();

    // 窗口大小固定
    yoursData->setFixedSize(yoursData->width(), yoursData->height());

    // 阻塞整个应用程序的所有其他窗口响应
    yoursData->setWindowModality(Qt::ApplicationModal);

    // 显示窗口
    yoursData->show();
}

// 启动标刻
void UFO::on_actImplementstart_triggered()
{
    // 判断是否具有标刻条件
    if (aFileName == nullptr)
    {
        QMessageBox::warning(nullptr, "系统", "不存在已读取的标刻文件数据");
        return;
    }

    if (DataReadState->text() != "读取状态：完成")
    {
        QMessageBox::warning(nullptr, "系统", "请等待数据读取完毕！");
        return;
    }

    // 振镜标刻前准备
    int isReady = markReady();
    if (isReady < 0)
        isReady = 0;

    if (!isReady)
        return;

    // 启动线程
    MarktoThread.start();

    // 同步状态
    GlobalInfo::mthread = true;
}

// 振镜标刻前准备
int UFO::markReady()
{
    // 读取当前程序可执行程序绝对路径
    m_FileName = QCoreApplication::applicationDirPath();

    // 读取配置
    QString fileName = m_FileName + "/laserSetting.ini";
    ReadSetting = new QSettings(fileName, QSettings::IniFormat);

    // 获取参数设置
    int LaserType = ReadSetting->value("laserType").toInt();
    int Standby = ReadSetting->value("standby").toInt();
    float StandbyFrequency = ReadSetting->value("frequency").toFloat();
    float StandbyPulseWidth = ReadSetting->value("pulseWidth").toFloat();

    fileName = m_FileName + "/correctWayRead.ini";
    ReadSetting = new QSettings(fileName, QSettings::IniFormat);

    bool fixWay = ReadSetting->value("fixWay").toBool();

    fileName = m_FileName + "/correctSetting.ini";
    ReadSetting = new QSettings(fileName, QSettings::IniFormat);

    double rangeX = ReadSetting->value("rangeX").toDouble();
    double rangeY = ReadSetting->value("rangeY").toDouble();
    bool exchangeXY = ReadSetting->value("exchangeXY").toBool();
    bool invertX = ReadSetting->value("invertX").toBool();
    bool invertY = ReadSetting->value("invertY").toBool();
    double xCorrection = ReadSetting->value("xCorrection").toDouble();
    double yCorrection = ReadSetting->value("yCorrection").toDouble();
    double xshear = ReadSetting->value("xShear").toDouble();
    double yshear = ReadSetting->value("yShear").toDouble();
    double xladder = ReadSetting->value("xLadder").toDouble();
    double yladder = ReadSetting->value("yLadder").toDouble();
    double ratioX = ReadSetting->value("ratioX", 1.0).toDouble();
    double ratioY = ReadSetting->value("ratioY", 1.0).toDouble();
    double ratioZ = ReadSetting->value("ratioZ", 1.0).toDouble();
    int startMarkMode = ReadSetting->value("startMarkMode").toInt();

    // QString转char*
    QString CorrectionShowPath = ReadSetting->value("CorrectionShowPath").toString();
    std::string str = CorrectionShowPath.toStdString();
    const char* ch = str.c_str();
    char* filepaths = const_cast<char*>(ch);

    fileName = m_FileName + "/systemSetting.ini";
    ReadSetting = new QSettings(fileName, QSettings::IniFormat);

    int INDEX = ReadSetting->value("INDEX").toDouble();
    int markCounts = ReadSetting->value("markCounts").toDouble();
    int isBitmap = ReadSetting->value("isBitmap").toInt();
    float markSpeed = ReadSetting->value("markSpeed").toDouble();
    float jumpSpeed = ReadSetting->value("jumpSpeed").toDouble();
    float jumpDelay = ReadSetting->value("jumpDelay").toDouble();
    float polygonDelay = ReadSetting->value("polygonDelay").toDouble();
    float laserOnDelay = ReadSetting->value("laserOnDelay").toDouble();
    float laserOffDelay = ReadSetting->value("laserOffDelay").toDouble();
    float polygonKillerTime = ReadSetting->value("polygonKillerTime").toDouble();
    float laserFrequency = ReadSetting->value("laserFrequency").toDouble();
    float current = ReadSetting->value("current").toDouble();
    float firstPulseKillerLength = ReadSetting->value("firstPulseKillerLength").toDouble();
    float pulseWidth = ReadSetting->value("pulseWidth").toDouble();
    float firstPulseWidth = ReadSetting->value("firstPulseWidth").toDouble();
    float incrementStep = ReadSetting->value("incrementStep").toDouble();
    float dotSpace= ReadSetting->value("dotSpace").toDouble();

    int func_Return = 0;

    // 同步标刻次数
    GlobalInfo::MarkCount = markCounts;

    // 初始化系统参数
    func_Return = SetSystemParameters(rangeX, rangeY, exchangeXY, invertX, invertY, startMarkMode);
    if (func_Return != 1)
        return func_Return;

    // 设置校正参数
    if (!fixWay)
    {
        func_Return = SetCorrectParameters_0(xCorrection, yCorrection, xshear, yshear, xladder, yladder, ratioX, ratioY, ratioZ);
        if (func_Return != 1)
            return func_Return;
    }  
    else
    {
        func_Return = SetCorrectParameters_1(ratioX, ratioY, ratioZ, filepaths);
        if (func_Return != 1)
            return func_Return;
    }

    // 设置激光模式
    func_Return = SetLaserMode(LaserType, Standby, StandbyFrequency, StandbyPulseWidth);
    if (func_Return != 1)
        return func_Return;

    // 设置标刻参数
    func_Return = SetMarkParameter(INDEX, markCounts, isBitmap, markSpeed, jumpSpeed, jumpDelay, polygonDelay, laserOnDelay, laserOffDelay, polygonKillerTime, laserFrequency, current, firstPulseKillerLength, pulseWidth, firstPulseWidth, incrementStep, dotSpace);
    if (func_Return != 1)
        return func_Return;

    // 加载标刻参数至板卡
    func_Return = DownloadMarkParameters();
    if (!func_Return)
        return func_Return;

    // 将参数加载到FPGA
    func_Return = SetFirstMarkParameter(INDEX);
    if (!func_Return)
        return func_Return;

    return func_Return;
}

// 错误存在，程序退出
bool UFO::hasError()
{
    return m_hasError;
}

// 标刻次数CheckBox状态改变
void UFO::on_InfMarkCount_stateChanged(int arg1)
{
    if (ui.InfMarkCount->isChecked())
    {
        // 读取当前程序可执行程序绝对路径
        m_FileName = QCoreApplication::applicationDirPath();

        // systemSetting.ini文件绝对地址
        QString m_FileName1 = m_FileName + "/systemSetting.ini";
        systemReadini = new QSettings(m_FileName1, QSettings::IniFormat);

        // 记录当前标刻次数
        systemReadini->setValue("markCounts", 0);
        GlobalInfo::MarkCount = 0;
    } 
}

// 退出程序
void UFO::on_actQuit_triggered()
{
    this->close();
}
