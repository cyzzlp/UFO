#include "UFO.h"
   
UFO::UFO(QWidget* parent)
    : QMainWindow(parent)
{
    // ���������ʾ
    setWindowState(Qt::WindowMaximized);

    // ��ȡIcon�ļ�·��
    QString m_FileName = QCoreApplication::applicationDirPath() + "/Icon/ufo.png";

    // ���Դ���Icon����Ϊѡ����ͼ��
    QApplication::setWindowIcon(QIcon(m_FileName));

    // ������
    int isConnect = connectSystemMark();
    if (!isConnect)
        QMessageBox::warning(nullptr, "��", "û�а忨���ܱ�̣�����������");

    // ����PI
    isConnect = connectSystemPi();
    if (!isConnect)
        QMessageBox::warning(nullptr, "PI", szErrorMesage);

    // ���ӿ���
     isConnect = connectSystemShutter();
     if (!isConnect)
         QMessageBox::warning(nullptr, "����", "CH375��������ʧ�ܣ������������");

     // ����CCD
     isConnect = connectSystemCCD();
     if (!isConnect)
         QMessageBox::warning(nullptr, "CCD", "CCD����ʧ�ܣ������������");

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

    // ��ʼ������ؼ�
    initButton();

    // ���������ļ�
    InitSetting();

    // ׼������߳�
    CreateMarkWorkerThread();

    // ����豸����ʧ��
    if (!isConnect)
        return;

    // ͼ��ɼ�׼��
    backend_acquisition_prepare();

    // �������ݲɼ��߳�
    CreateAcquisitionWorkerThreadCCD();

    // ����ͼ��ɼ�
    StartAcquisition();

    // ʵʱ��ȡPIλ��
    CreateAcquisitionWorkerThreadPI();

    // ��ʼ�ɼ�PIλ�� 
    StartAcquisitionPI();

    // ׼������߳�
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

    // CCDͼ��ɼ��߳��˳�
    if (GlobalInfo::cthread)
    {
        m_acquisitionWorker->Stop();
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();
    }

    // �񾵶Ͽ�
    if (GlobalInfo::m_Connect)
        CloseUSB_Board();

    // PI�Ͽ�
    if (GlobalInfo::p_Connect)
        PI_CloseConnection(GlobalInfo::ID);

    // ����Ͽ�
    if(GlobalInfo::c_Connect)
        backend_exit();
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
    // ��¼��������ֵ
    int returnValue = 0;

    // ��ȡFPGAӲ�������ļ����ڵ�λ��
    QString fpgaPath = QCoreApplication::applicationDirPath() + "/FpgaFirmware.rbf";
    QByteArray Path = fpgaPath.toLatin1();
    char* filePath = Path.data();
    
    // ���Ӱ忨
    returnValue = OpenUSB_Board(0, NULL);
    returnValue = LoadFPGA_FirmwareProgram(filePath);

    // 0 == false  ���� == true
    if (returnValue < 0)
        return 0;

    // �񾵻����
    Goto_XY(0, 0);

    // ������
    GlobalInfo::m_Connect = true;

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
    BOOL returnValue = PI_qSAI(ID, szAxesed, 16);
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
    returnValue = PI_SVO(ID, szAxesed, bFlags);
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
    returnValue = PI_MOV(ID, szAxesed, dPos);
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
        returnValue = PI_qPOS(ID, szAxesed, dPos);
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
    returnValue = PI_IsConnected(ID);
    if (!returnValue)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        PI_CloseConnection(ID);
        return false;
    }

    // ��������������
    GlobalInfo::ID = ID;
    GlobalInfo::szAxes[0] = szAxesed[0];
    GlobalInfo::szAxes[1] = szAxesed[1];

    // ����PI����״̬
    GlobalInfo::p_Connect = true;

    return true;
}

// ���ӿ���
int UFO::connectSystemShutter()
{
    unsigned long ioLength = 1;
    unsigned long* p_ioLength = &ioLength;
    int a = 0x0a;

    // ���ӿ���
    HANDLE Shutter = CH375OpenDevice(index);
    if (Shutter == INVALID_HANDLE_VALUE)
    {
        GlobalInfo::s_Connect = false;
        return 0;
    }

    // ������ʱ
    CH375SetTimeout(index, 2000, 2000);

    // �����д�����ݣ����رտ���
    int iBuffer = a & 0x0a;
    CH375WriteData(index, &iBuffer, p_ioLength);

    // �����������״̬
    GlobalInfo::s_Connect = true;

    return 1;
}

// ����CCD
int UFO::connectSystemCCD()
{
    // ��̨�������ܣ���ͼ�⣬�����
    int status = backend_start();
    if (status != 0)
    {
        m_hasError = true;
        m_blockErrorMessages = true;
        backend_exit();
        return 0;
    }

    // CCD����״̬
    GlobalInfo::c_Connect = true;

    return 1;
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

// ���������Ϣ
void UFO::HandleLibraryError(QString message, int status)
{
    // ���ڹؼ���Ϣ����ֹ���д�����Ϣ
    if (m_blockErrorMessages)
        return;

    // ��"Error: "�ӵ�messageǰ��
    message.prepend("Error: ");

    // ��ʾ����
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

// ����ʵʱ��ʾ��̵�λ�õĴ���
void UFO::InitMarkDataVisual()
{
    // 3Dɢ��ͼ
    Q3DScatter* graph3D;

    // ����ͼ��
    graph3D = new Q3DScatter();

    // �趨����
    graphContainer = QWidget::createWindowContainer(graph3D);

    // ���ݴ���
    proxy = new QScatterDataProxy();

    // ��������
    series = new QScatter3DSeries(proxy);

    // ��ǩ
    series->setItemLabelFormat("@xLabel @zLabel @yLabel");
    
    // �⻬��
    series->setMeshSmooth(true);

    // �������
    graph3D->addSeries(series);

    // ����������
    graph3D->axisX()->setTitle("axis Y");

    // ������ɼ�
    graph3D->axisX()->setTitleVisible(true);

    // ����������
    graph3D->axisY()->setTitle("axis Z");

    // ������ɼ�
    graph3D->axisY()->setTitleVisible(true);

    // ����������
    graph3D->axisZ()->setTitle("axis X");

    // ������ɼ�
    graph3D->axisZ()->setTitleVisible(true);

    graph3D->activeTheme()->setLabelBackgroundEnabled(false);

    // ���ݵ�ΪԲ��
    series->setMesh(QAbstract3DSeries::MeshSphere);

    // ȡֵ��Χ0~1 ���Զ���������
    series->setItemSize(0.05);

    // �任�ӽ�
    Q3DCamera::CameraPreset cameraPos = Q3DCamera::CameraPreset(Q3DCamera::CameraPresetFront);
    graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);

    // ����
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
        QMessageBox::aboutQt(nullptr, "About Qt");
    }
}

// ��ʼ������ؼ�
void UFO::initButton()
{
    // ���CCDδ����
    if (!GlobalInfo::c_Connect)
    {
        ui.m_buttonStartStop->setEnabled(false);
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

    if (GlobalInfo::p_Connect)
    {
        // ֹͣ�豸����״̬�ı�����
        stopAnimation2();

        DeviceConnectState->setText("�豸���ӳɹ�");

        // ��ʾPI������
        QString szAxes = szAxesed[0];

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
    // �߳�����
    PiThread.start();

    // ͬ��״̬
    GlobalInfo::pthread = true;
}

// �����źŲ�
void UFO::CreateAcquisitionWorkerThreadCCD()
{
    // CCD�������ô���
    CCDSet = new CCDSetUserface();

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
        GlobalInfo::cthread = false;
        StopAcquisition();
    }
    else
    {
        ui.m_buttonStartStop->setText("ֹͣ�ɼ�");
        GlobalInfo::cthread = true;
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

    // �߳�����
    m_acquisitionThread.start();

    // ͬ��״̬
    m_acquisitionRunning = true;
    GlobalInfo::cthread = m_acquisitionRunning;
}

// ֹͣ�ɼ�
void UFO::StopAcquisition()
{
    // ִֹͣ��ͼ��ɼ��߳�
    if (m_acquisitionWorker)
    {
        // �߳�ֹͣ
        m_acquisitionWorker->Stop();

        // �߳��˳�
        m_acquisitionThread.quit();
        m_acquisitionThread.wait();

        // ֹͣͼ��ɼ�
        backend_acquisition_stop();
    }

    // ͬ��״̬
    m_acquisitionRunning = false;
    GlobalInfo::cthread = m_acquisitionRunning;
}

// �������ݱ���߳�
void UFO::CreateMarkWorkerThread()
{
    MarkThreads = new markThread();
    MarkThreads->moveToThread(&MarktoThread);

    // �߳̿�ʼʱ����ʼ���
    connect(&MarktoThread, SIGNAL(started()), MarkThreads, SLOT(Start()), Qt::UniqueConnection);
    
    // ��ʾ����г��ֵĴ���
    connect(MarkThreads, &markThread::EmitWrongInfo, this, &UFO::ResetWrongTexts);

    // ʵʱ��ʾ�񾵵�λ��
    connect(MarkThreads, &markThread::MarkRealPos, this, &UFO::showPosition);
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
    // ����������ó������⣬ֹͣ��ȡ
    realpos->stop();

    // �߳�ֹͣ
    PiThread.quit();
    PiThread.wait();

    // ��Ϣ��ʾ
    QMessageBox::critical(nullptr, "����", dataStatus);
}

// �����̴߳�����Ϣ
void UFO::ResetWrongTexts(QString dataStatus)
{
    // �߳�ֹͣ
    MarkThreads->Stop();

    // ��Ϣ��ʾ
    QMessageBox::critical(nullptr, "PI", dataStatus);
}

// ����ini�ļ�
void UFO::InitSetting()
{
    // ��ȡ��ǰ�����ִ�г������·��
    m_FileName = QCoreApplication::applicationDirPath();

    // �ļ�����·��
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

    // ����Ĭ��ֵgapSetting.ini
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

    // ���漰�ر������ļ�
    gapReadini->sync();
    correctWayReadini->sync();
    correctReadini->sync();
    laserReadini->sync();
    systemReadini->sync();

    // ɾ��ָ��
    delete gapReadini;
    delete correctWayReadini;
    delete correctReadini;
    delete laserReadini;
    delete systemReadini;
}

// ��ʾ���ݼ�����������ô���
void UFO::on_actPreGapInput_triggered()
{
    // ���쵱ǰ����
    gap = new dataSortgap();

    // ���ڴ�С�̶�
    gap->setFixedSize(gap->width(), gap->height());

    // ��������Ӧ�ó������������������Ӧ
    gap->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    gap->show();
}

// У���������ô���
void UFO::on_actCorrectMethod_triggered()
{
    // ���쵱ǰ����
    corrWay = new MarkCorrType();

    // ���ڴ�С�̶�
    corrWay->setFixedSize(corrWay->width(), corrWay->height());

    // ��������Ӧ�ó������������������Ӧ
    corrWay->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    corrWay->show();
}

// ����������
void UFO::on_actSetLaser_triggered()
{
    // ���쵱ǰ����
    laserset = new laserSet();

    // ���ڴ�С�̶�
    laserset->setFixedSize(laserset->width(), laserset->height());

    // ��������Ӧ�ó������������������Ӧ
    laserset->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    laserset->show();
}

// У���������ô���
void UFO::on_actSetMarkArea_triggered()
{
    // ��ȡ�ļ�
    QString m_FileName2 = m_FileName + "/correctWayRead.ini";
    correctWayReadini = new QSettings(m_FileName2, QSettings::IniFormat);

    // ��ȡ���ò���
    bool correctWay = correctWayReadini->value("fixWay").toBool();
    if (!correctWay)
    {
        markSet2 = new MarkAreaSet2();

        // ���ڴ�С�̶�
        markSet2->setFixedSize(markSet2->width(), markSet2->height());

        // ��������Ӧ�ó������������������Ӧ
        markSet2->setWindowModality(Qt::ApplicationModal);

        // ��ʾ����
        markSet2->show();
    }
    else
    {
        markSet1 = new MarkAreaSet1();

        // ���ڴ�С�̶�
        markSet1->setFixedSize(markSet1->width(), markSet1->height());

        // ��������Ӧ�ó������������������Ӧ
        markSet1->setWindowModality(Qt::ApplicationModal);

        // ��ʾ����
        markSet1->show();
    }
}

// ��̲�������
void UFO::on_actSetSystemPara_triggered()
{
    // ���쵱ǰ����
    paraSet = new MarkParaSet();

    // ���ڴ�С�̶�
    paraSet->setFixedSize(paraSet->width(), paraSet->height());

    // ��������Ӧ�ó������������������Ӧ
    paraSet->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    paraSet->show();
}

// ��ʾPI���ý���
void UFO::on_actConnectPI_triggered()
{
    piSet = new piControl();

    // ���ڴ�С�̶�
    piSet->setFixedSize(piSet->width(), piSet->height());

    // ��������Ӧ�ó������������������Ӧ
    piSet->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    piSet->show();
}

// ��ʾ�������ý���
void UFO::on_actConnectShutter_triggered()
{
    shutter = new shutterControl();

    // ���ڴ�С�̶�
    shutter->setFixedSize(shutter->width(), shutter->height());

    // ��������Ӧ�ó������������������Ӧ
    shutter->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    shutter->show();
}

// ��ʾ�����ý���
void UFO::on_actMarkSet_triggered()
{
    markSet = new MarkControl();

    // ���ڴ�С�̶�
    markSet->setFixedSize(markSet->width(), markSet->height());

    // ��������Ӧ�ó������������������Ӧ
    markSet->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    markSet->show();
}

// ��ʾ������ý���
void UFO::on_actConnectCCD_triggered()
{
    CCDSet = new CCDSetUserface();
        
    // ���ڴ�С�̶�
    CCDSet->setFixedSize(CCDSet->width(), CCDSet->height());

    // ��������Ӧ�ó������������������Ӧ
    CCDSet->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    CCDSet->show();
}

// �ָ�ϵͳĬ�ϲ�������
void UFO::on_actDefaultPara_triggered()
{
    // �ָ�ϵͳ��������
    InitSetting();
}

// ��ȡ����ļ�
void UFO::on_actOpenFile_triggered()
{
    // ��ȡ�ӹ��ı�·��
    QString str_Filepath = QDir::currentPath();

    // �Ի������
    QString dlgTitle = "�ļ�";

    //�ļ�������
    QString filter = "�ı��ļ�(*.txt);;ͼƬ�ļ�(*.jpg *.gif *.png);;�����ļ�(*.*)"; 
    aFileName = QFileDialog::getOpenFileName(this, dlgTitle, str_Filepath, filter);

    // �رն�ʱ��
    stopAnimation1();

    // ��Ϊ�ж��߳������ı�־
    if (!aFileName.isEmpty())
    {
        GlobalInfo::aFileName = aFileName;

        // �����ļ�Ԥ����
        gap = new dataSortgap();

        // ��������Ӧ�ó������������������Ӧ
        gap->setWindowModality(Qt::ApplicationModal);

        // ���ڴ�С�̶�
        gap->setFixedSize(gap->width(), gap->height());

        // ��ʾ����
        gap->show();

        // �������ݶ�ȡ�߳�
        dataRead = new DataSortThread();

        // �������ݶ�ȡ״̬
        connect(dataRead, &DataSortThread::setTextToLabel, this, &UFO::ResetText);

        // �����̴߳�����Ϣ
        connect(dataRead, &DataSortThread::DelieveWrongInfo, this, &UFO::ResetWrongText);

        // ��ʾ���������
        connect(dataRead, &DataSortThread::MarkDataNum, this, &UFO::ResetDataText);

        // �����߳�
        connect(gap, &dataSortgap::isPushed, this, [=]()
            {
                // ִ�ж�ȡ
                dataRead->start();
            });
    }
}

// ִ����ʾ���ݿ��ӻ�����
void UFO::on_acDataVisual_triggered()
{
    dataVis = new DataVisual();

    if (DataReadState->text() == "��ȡ״̬�����")
    {
        // ���ڴ�С�̶�
        dataVis->setFixedSize(dataVis->width(), dataVis->height());

        // ��������Ӧ�ó������������������Ӧ
        dataVis->setWindowModality(Qt::ApplicationModal);

        // ��ʾ����
        dataVis->show();

        // ��ͼ
        dataVis->DrawData(MarkData::returnMarkData);
    }
    else
    {
        QMessageBox::warning(nullptr, "����", "����δ��ȡ���ȡ�У��޷����ӻ����ݣ�");
    }
}

// �������ݶ�ȡ״̬
void UFO::ResetText(QString dataStatus)
{
    DataReadState->setText("��ȡ״̬��" + dataStatus);

    if (dataStatus == "���")
    {
        dataRead->quit();
        dataRead->wait();
        delete dataRead;
    }
}

// ����������״̬
void UFO::ResetDataText(int dataNum)
{
    // doubleתQString
    QString Num = QString::number(dataNum);

    // ��ʾ
    MarkDataNum->setText("�������������" + Num);
}

// ��ʾ��λ��
void UFO::showPosition(double x_Pos, double y_Pos)
{
    // doubleתQString
    QString xPos = QString::number(x_Pos);
    QString yPos = QString::number(y_Pos);

    // ��ʾ
    x_Position->setText("��xλ�ã�" + xPos);
    y_Position->setText("��yλ�ã�" + yPos);
}

// ϵͳ��Ϣ��ʾ
void UFO::on_actSystemInfo_triggered()
{
    on_actDefaultPara_triggered();

    // ���쵱ǰ����
    sysInfo = new SystemInfo();

    // ���ڴ�С�̶�
    sysInfo->setFixedSize(sysInfo->width(), sysInfo->height());

    // ��������Ӧ�ó������������������Ӧ
    sysInfo->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    sysInfo->show();
}

// �Զ���������
void UFO::on_actYoursData_triggered()
{
    // ���쵱ǰ����
    yoursData = new YoursData();

    // ���ڴ�С�̶�
    yoursData->setFixedSize(yoursData->width(), yoursData->height());

    // ��������Ӧ�ó������������������Ӧ
    yoursData->setWindowModality(Qt::ApplicationModal);

    // ��ʾ����
    yoursData->show();
}

// �������
void UFO::on_actImplementstart_triggered()
{
    // �ж��Ƿ���б������
    if (aFileName == nullptr)
    {
        QMessageBox::warning(nullptr, "ϵͳ", "�������Ѷ�ȡ�ı���ļ�����");
        return;
    }

    if (DataReadState->text() != "��ȡ״̬�����")
    {
        QMessageBox::warning(nullptr, "ϵͳ", "��ȴ����ݶ�ȡ��ϣ�");
        return;
    }

    // �񾵱��ǰ׼��
    int isReady = markReady();
    if (isReady < 0)
        isReady = 0;

    if (!isReady)
        return;

    // �����߳�
    MarktoThread.start();

    // ͬ��״̬
    GlobalInfo::mthread = true;
}

// �񾵱��ǰ׼��
int UFO::markReady()
{
    // ��ȡ��ǰ�����ִ�г������·��
    m_FileName = QCoreApplication::applicationDirPath();

    // ��ȡ����
    QString fileName = m_FileName + "/laserSetting.ini";
    ReadSetting = new QSettings(fileName, QSettings::IniFormat);

    // ��ȡ��������
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

    // QStringתchar*
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

    // ͬ����̴���
    GlobalInfo::MarkCount = markCounts;

    // ��ʼ��ϵͳ����
    func_Return = SetSystemParameters(rangeX, rangeY, exchangeXY, invertX, invertY, startMarkMode);
    if (func_Return != 1)
        return func_Return;

    // ����У������
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

    // ���ü���ģʽ
    func_Return = SetLaserMode(LaserType, Standby, StandbyFrequency, StandbyPulseWidth);
    if (func_Return != 1)
        return func_Return;

    // ���ñ�̲���
    func_Return = SetMarkParameter(INDEX, markCounts, isBitmap, markSpeed, jumpSpeed, jumpDelay, polygonDelay, laserOnDelay, laserOffDelay, polygonKillerTime, laserFrequency, current, firstPulseKillerLength, pulseWidth, firstPulseWidth, incrementStep, dotSpace);
    if (func_Return != 1)
        return func_Return;

    // ���ر�̲������忨
    func_Return = DownloadMarkParameters();
    if (!func_Return)
        return func_Return;

    // ���������ص�FPGA
    func_Return = SetFirstMarkParameter(INDEX);
    if (!func_Return)
        return func_Return;

    return func_Return;
}

// ������ڣ������˳�
bool UFO::hasError()
{
    return m_hasError;
}

// ��̴���CheckBox״̬�ı�
void UFO::on_InfMarkCount_stateChanged(int arg1)
{
    if (ui.InfMarkCount->isChecked())
    {
        // ��ȡ��ǰ�����ִ�г������·��
        m_FileName = QCoreApplication::applicationDirPath();

        // systemSetting.ini�ļ����Ե�ַ
        QString m_FileName1 = m_FileName + "/systemSetting.ini";
        systemReadini = new QSettings(m_FileName1, QSettings::IniFormat);

        // ��¼��ǰ��̴���
        systemReadini->setValue("markCounts", 0);
        GlobalInfo::MarkCount = 0;
    } 
}

// �˳�����
void UFO::on_actQuit_triggered()
{
    this->close();
}
