#include "UFO.h"

UFO::UFO(QWidget* parent)
    : QMainWindow(parent)
{
    // ���������ʾ
    setWindowState(Qt::WindowMaximized);

    // ������
    int isConnect = connectSystemMark();
    if (!isConnect)
        QMessageBox::critical(nullptr, "Mark", "û�а忨���ܱ��");

    // ����PI
    isConnect = connectSystemPi();
    if (!isConnect)
        QMessageBox::critical(nullptr, "PI", szErrorMesage);

    // ��¼������Ϣ
    feedBackDevice();

    ui.setupUi(this);

    // ����˵Ĵ���ص����ӵ�UFO
    connect(this, &UFO::libraryError, this, &UFO::HandleLibraryError);
    backend_errorCallback_connect(this, &UFO::EmitErrorSignal);

    // ��ʼ��ʵʱ��ʾ����
    InitMarkDataVisual();

    // ʵ�ֶ���Ч��
    CreateTimer();

    // ��ʼ��״̬��
    CreateStatuBar();

    // ��ʼ��CCD����
    CreateCCD();

    // ����CCD�ɼ�
    OpenCCDLibrary();

    // ��ʼ������ؼ�
    initButton();

    // ����豸����ʧ��
    if (!C_IsConnected)
        return;

    // ʵʱ��ȡPIλ��
    CreateAcquisitionWorkerThreadPI();

    // ��ʼ�ɼ�PIλ�� 
    StartAcquisitionPI();

    // ͼ��ɼ�׼��
    backend_acquisition_prepare();

    // �������ݲɼ��߳�
    CreateAcquisitionWorkerThreadCCD();

    // ����ͼ��ɼ�
    StartAcquisition();

    // �������ݱ���߳�
    CreateMarkWorkerThread();
}

UFO::~UFO()
{

}

// �رմ���ʱ�䣬����ѯ���Ƿ��˳�
void UFO::closeEvent(QCloseEvent* event)
{
    // ���ڹر�ʱѯ���Ƿ��˳�
    QMessageBox::StandardButton result = QMessageBox::question(this, "ϵͳ", "ȷ��Ҫ�˳���������",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
        QMessageBox::Yes);

    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

// ������
int UFO::connectSystemMark()
{
    // ReturnFunc
    int returnValue = 0;

    // ���������ļ����ڵ�λ�ã�����·��
    char fpgaPaths[MAX_PATH + 1]{};
    GetModuleFileNameA(nullptr, fpgaPaths, MAX_PATH);
    std::string FirmwareProgram = const_cast<char*>(fpgaPaths);
    int index = FirmwareProgram.find_last_of("\\");
    std::string folderPath = FirmwareProgram.substr(0, index);
    std::string fpgaPath = folderPath + "\\" + "FpgaFirmware.rbf";

    // stringתchar*
    char* filePath = const_cast<char*>(fpgaPath.c_str());
    
    // ���Ӱ忨
    returnValue = OpenUSB_Board(0, NULL);
    returnValue = LoadFPGA_FirmwareProgram(filePath);

    // 0 == false  ���� == true
    if (returnValue < 0)
        return 0;

    // �񾵻����
    Goto_XY(0, 0);

    // ������
    M_IsConnected = true;

    return 1;
}

// ����PI
bool UFO::connectSystemPi()
{
    // ���USB��Ҫ�Ĳ���
    PI_EnumerateUSB(szBuffer, 17, szFilter);

    // ͨ��USB����
    ID = PI_ConnectUSB(szBuffer);
    if (ID < 0)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // ��ȡ������������ı�ʶ��
    BOOL returnValue = PI_qSAI(ID, szAxes, 16);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // Ϊ�ַ�����axes���е��������ŷ�
    BOOL bFlags[3] = { 0 };
    bFlags[0] = TRUE;

    // �����ŷ�ģʽ����
    returnValue = PI_SVO(ID, szAxes, bFlags);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // PI����
    dPos[0] = 0.0;

    // ����(�ƶ�z��λ��)
    returnValue = PI_MOV(ID, szAxes, dPos);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }
    // ѡ��ȴ���
    bIsMoving[0] = TRUE;
    while (bIsMoving[0] == TRUE)
    {
        returnValue = PI_qPOS(ID, szAxes, dPos);
        // ����������λ��
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

    // PI�Ƿ�����
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

// ʵ�ֶ���Ч��
void UFO::CreateTimer()
{
    // ʵ�ֵȴ�����
    DATA_TIMER = new QTimer();

    // ʵ�ֵȴ�����
    PI_AXIS_TIMER = new QTimer();

    // �趨��ʱʱ��500����
    DATA_TIMER->setInterval(500);
    connect(DATA_TIMER, &QTimer::timeout, this, &UFO::updateText1);

    // �趨��ʱʱ��500����
    PI_AXIS_TIMER->setInterval(500);
    connect(PI_AXIS_TIMER, &QTimer::timeout, this, &UFO::updateText2);
}

// �豸������Ϣ
void UFO::feedBackDevice()
{

}

// ���������Ϣ
void UFO::HandleLibraryError(QString message, int status)
{
    // ���ڹؼ���Ϣ����ֹ���д�����Ϣ
    if (m_blockErrorMessages)
        return;

    message.prepend("Error: ");

    QMessageBox::warning(nullptr, "Error", message, QMessageBox::Ok);
}

// ���ʹ����ź�
void UFO::EmitErrorSignal(const char* message, int status, void* errorCallbackContext)
{
    emit static_cast<UFO*>(errorCallbackContext)->libraryError(QString::fromStdString(message), status);
};

// ������ʱ��
void UFO::startAnimation1()
{
    DATA_TIMER->start();
}

// ������ʱ��
void UFO::startAnimation2()
{
    PI_AXIS_TIMER->start();
}

// ֹͣ��ʱ��
void UFO::stopAnimation1()
{
    DATA_TIMER->stop();
}

// ֹͣ��ʱ��
void UFO::stopAnimation2()
{
    PI_AXIS_TIMER->stop();
}

// �����ı�
void UFO::updateText1()
{
    // ����ǰ����4��ʾ����ĩβ
    ++mIndex;

    if (mIndex > 4)
        mIndex = 1;

    if (mIndex == 1)
    {
        DataReadState->setText("��ȡ״̬���ȴ�");
    }

    if (mIndex == 2)
    {
        DataReadState->setText("��ȡ״̬���ȴ�.");
    }

    if (mIndex == 3)
    {
        DataReadState->setText("��ȡ״̬���ȴ�..");
    }

    if (mIndex == 4)
    {
        DataReadState->setText("��ȡ״̬���ȴ�...");
    }
}

// �����ı�
void UFO::updateText2()
{
    // ����ǰ����4��ʾ����ĩβ
    ++pIndex;

    if (pIndex > 4)
        pIndex = 1;

    if (pIndex == 1)
    {
        ConnectAxis->setText("PI�����᣺�ȴ�����");
    }

    if (pIndex == 2)
    {
        ConnectAxis->setText("PI�����᣺�ȴ�����.");
    }

    if (pIndex == 3)
    {
        ConnectAxis->setText("PI�����᣺�ȴ�����..");
    }

    if (pIndex == 4)
    {
        ConnectAxis->setText("PI�����᣺�ȴ�����...");
    }
}

// CCD��ʼ�ɼ�
void UFO::OpenCCDLibrary()
{
    // ��̨�������ܣ���ͼ�⣬�����
    int status = backend_start();
    if (status != 0)
    {
        m_hasError = true;
        m_blockErrorMessages = true;
        backend_exit();
        return;
    }

    // CCD����״̬
    C_IsConnected = true;
}

// ����ʵʱ��ʾ��̵�λ�õĴ���
void UFO::InitMarkDataVisual()
{
    Q3DScatter* graph3D;
    // ����ͼ��
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D);

    // ���ݴ���
    proxy = new QScatterDataProxy();

    // ��������
    series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat("@xLabel @zLabel @yLabel");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);

    // ����������
    graph3D->axisX()->setTitle("axis Y");
    graph3D->axisX()->setTitleVisible(true);

    graph3D->axisY()->setTitle("axis Z");
    graph3D->axisY()->setTitleVisible(true);

    graph3D->axisZ()->setTitle("axis X");
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    // ���ݵ�ΪԲ��
    series->setMesh(QAbstract3DSeries::MeshSphere);

    // ȡֵ��Χ0~1 ���Զ���������
    series->setItemSize(0.05);

    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(Q3DCamera::CameraPresetFront);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);

    ui.verticalLayout_graph3D->addWidget(graphContainer);
}

// ��ʼ��CCD����
void UFO::CreateCCD()
{
    // ����ͼ����ʾ����
    m_centralWidget = new QWidget(this);
    ui.ccdLayout ->addWidget(m_centralWidget);

    // Ϊ���ͼ�񴴽���ʾ������CCD��Ϣ��ʾ�ؼ�
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

// Qt��about
void UFO::OnAboutQtLinkActivated(const QString& link)
{
    if (link == "#aboutQt")
    {
        QMessageBox::aboutQt(this, "About Qt");
    }
}

// ��ʼ������ؼ�
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

// ��ʼ��״̬��
void UFO::CreateStatuBar()
{
    startAnimation1();
    startAnimation2();

    // ��ʾ���ݶ�ȡ״̬
    DataReadState = new QLabel;
    DataReadState->setMaximumWidth(175);
    DataReadState->setMinimumWidth(175);

    // PI������
    ConnectAxis = new QLabel;
    ConnectAxis->setMaximumWidth(175);
    ConnectAxis->setMinimumWidth(175);

    // PIʵʱλ��
    PiRealPos = new QLabel;
    PiRealPos->setMaximumWidth(175);
    PiRealPos->setMinimumWidth(175);

    // ���������
    MarkDataNum = new QLabel;
    MarkDataNum->setMaximumWidth(200);
    MarkDataNum->setMinimumWidth(200);

    // �豸����״̬
    DeviceConnectState = new QLabel;
    DeviceConnectState->setMaximumWidth(175);
    DeviceConnectState->setMinimumWidth(175);

    // ��λ��
    x_Position = new QLabel;
    y_Position = new QLabel;
    x_Position->setMaximumWidth(200);
    x_Position->setMinimumWidth(200);
    y_Position->setMaximumWidth(200);
    y_Position->setMinimumWidth(200);


    // ���õ�ǰ״̬
    MarkDataNum->setText("�������������");
    PiRealPos->setText("PIʵʱλ�ã�");
    x_Position->setText("��xλ�ã�0.00");
    y_Position->setText("��yλ�ã�0.00");

    if (P_IsConnected)
    {
        // ֹͣ�豸����״̬�ı�����
        stopAnimation2();

        DeviceConnectState->setText("�豸���ӳɹ�");

        // ��ʾPI������
        QString szAxes = QString(szAxes[0]);

        ConnectAxis->setText("PI�����᣺" + szAxes);
    }
    else
    {
        DeviceConnectState->setText("�豸����ʧ��");
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

    // �����Ҳ಼��
    ui.statusBar->addPermanentWidget(widget1);
}

// �����źŲ�
void UFO::CreateAcquisitionWorkerThreadPI()
{
    // �����߳���
    realpos = new piRealpos();
    realpos->moveToThread(&PiThread);

    // �߳̿�ʼʱ����ʼ��ȡλ��
    connect(&PiThread, SIGNAL(started()), realpos, SLOT(Start()), Qt::UniqueConnection);

    // ����PIλ�ã�ʵʱ����
    connect(realpos, &piRealpos::PiRealPOS, this, &UFO::RefreshPiPos);

    // �������ݶ�ȡ״̬
    connect(realpos, &piRealpos::DelieveWrongInfo, this, &UFO::ResetWrongText);
}

// ��ʼ�ɼ�PIλ��
void UFO::StartAcquisitionPI()
{
    // whileѭ��ΪTrue
    realpos->start();

    // �߳�����
    PiThread.start();
}

// �����źŲ�
void UFO::CreateAcquisitionWorkerThreadCCD()
{
    // CCD�������ô���
    CCDSet = new CCDSetUserface;

    // ��������ͼ��ɼ������߳�
    m_acquisitionWorker = new AcquisitionWorker();
    m_acquisitionWorker->moveToThread(&m_acquisitionThread);

    // ʵ��PushButton����ͼ��ɼ�
    connect(ui.m_buttonStartStop, &QPushButton::clicked, this, &UFO::OnButtonStopStart);

    // worker�������������ɼ���ʼʱ
    connect(&m_acquisitionThread, SIGNAL(started()), m_acquisitionWorker, SLOT(Start()), Qt::UniqueConnection);

    // �����յ���ͼ��ʱ�������Թ����̵߳��ź�
    // ��ʾ��
    connect(m_acquisitionWorker, &AcquisitionWorker::imageReceived, m_display, &Display::OnImageReceived);

    // ������������ MainWindow �еĸ��²�۷����仯ʱ���������Թ����̵߳��ź�
    // ��
    connect(m_acquisitionWorker, &AcquisitionWorker::counterUpdated, this, &UFO::OnCounterUpdated);

    // �ڲɼ���ʼʱ�������Թ����̵߳��ź�
    connect(m_acquisitionWorker, &AcquisitionWorker::started, CCDSet, &CCDSetUserface::UpdateControls);

    // ���ɼ�ֹͣʱ�������Թ����̵߳��ź�
    connect(m_acquisitionWorker, &AcquisitionWorker::stopped, CCDSet, &CCDSetUserface::UpdateControls);

    // �������̵߳Ĵ����ź����ӵ� MarkControl ���еĲ��
    connect(m_acquisitionWorker, &AcquisitionWorker::error, this, &UFO::HandleErrorAndQuit);
}

// CCD�ɼ�����
void UFO::OnButtonStopStart()
{
    if ("ֹͣ�ɼ�" == ui.m_buttonStartStop->text())
    {
        ui.m_buttonStartStop->setText("��ʼ�ɼ�");
        StopAcquisition();
    }
    else
    {
        ui.m_buttonStartStop->setText("ֹͣ�ɼ�");
        StartAcquisition();
    }
}

// ���´���������CCD�ɼ�ʱ��
void UFO::OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter)
{
    QString strText;
    strText.sprintf("Acquired: %d, errors: %d", frameCounter, errorCounter);
    m_labelInfo->setText(strText);
}

// ���ݴ������Ϣ�������Ƿ���ǰ�˳�����
void UFO::HandleErrorAndQuit(QString message)
{
    // ���ڹؼ���Ϣ����ֹ���д�����Ϣ
    if (m_blockErrorMessages)
        return;

    message += "\n(Error!)";
    message += "\nExiting application";

    QMessageBox::critical(nullptr, "Error", message, QMessageBox::Ok);
    qApp->quit();
}

// �����ɼ�
void UFO::StartAcquisition()
{
    // ��ʼִ��ͼ��ɼ��߳�
    backend_acquisition_start();

    m_acquisitionThread.start();
    m_acquisitionRunning = true;
}

// ֹͣ�ɼ�
void UFO::StopAcquisition()
{
    // ִֹͣ��ͼ��ɼ��߳�
    if (m_acquisitionWorker)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();

        backend_acquisition_stop();
    }
    m_acquisitionRunning = false;
}

// �������ݱ���߳�
void UFO::CreateMarkWorkerThread()
{

}

// ʵʱ����PIλ��
void UFO::RefreshPiPos(double u_PiPosition)
{
    // ��u_PiPositionת��ΪQstring��ʮ������ʾ��4λ����
    PiRealPos->setText("PIʵʱλ�ã�" + QString::number(u_PiPosition, 10, 4));
}

// �����̴߳�����Ϣ
void UFO::ResetWrongText(QString dataStatus)
{
    // ֹͣ��ȡ
    realpos->stop();

    // �߳�ֹͣ
    PiThread.quit();
    PiThread.wait();

    // ��Ϣ��ʾ
    QMessageBox::critical(this, "����", dataStatus);
}


// �����˳�
bool UFO::hasError()
{
    return m_hasError;
}