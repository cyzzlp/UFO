#pragma once

//���������������
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
    // �豸����
    bool hasError();

private:
    // �豸����״̬ �� PI ��ҵ��� ����
    bool M_IsConnected{};

    bool P_IsConnected{};

    bool C_IsConnected{};

    bool S_IsConnected{};

    // ʵ�ֶ���Ч��
    int mIndex = 1;

    int pIndex = 1;

    // PI���
    int ID{};

    // ��¼������
    char szAxes[2]{};

    // ���� USB �豸������ szBuffer ������
    char szBuffer[17]{};

    // ���������������ƥ��Ŀ������ڻ������з���
    char szFilter[17]{};

    // ���ص��ַ���,�������кź��豸������
    char serialNo[256]{};

    // PI������Ϣ���
    int iError{};

    // PI������Ϣ
    char szErrorMesage[1024]{};

    // PI�ƶ�λ��
    double dPos[3]{};

    // PI��ȴ�
    BOOL bIsMoving[3]{};

    // CCD������Ϣ
    bool m_blockErrorMessages{};

    // CCD�ɼ���ʼ
    bool m_acquisitionRunning{};

    // ��¼����
    bool m_hasError{};

    // ͼ�������
    QWidget* graphContainer = nullptr;

    Q3DScatter* graph3D = nullptr;

    // ɢ������
    QScatter3DSeries* series = nullptr;

    // ���ݴ���
    QScatterDataProxy* proxy = nullptr;

    // Ϊʵ�����ݹ�������������
    QScatterDataArray* dataArray = nullptr;

    // ʵ�ֻ�ͼ
    QScatterDataItem* ptrToDataArray = nullptr;


private:
    // ʵ�����ݶ�ȡ�ȴ���ʾ
    QTimer* DATA_TIMER{};

    // ʵ��PI���ӵȴ���ʾ
    QTimer* PI_AXIS_TIMER{};

    // ���ݶ�ȡ״̬
    QLabel* DataReadState{};

    // PI������
    QLabel* ConnectAxis{};

    // PIʵʱλ��
    QLabel* PiRealPos{};

    // ���������
    QLabel* MarkDataNum{};

    // �豸����״̬
    QLabel* DeviceConnectState{};

    // ��xλ��
    QLabel* x_Position{};

    // ��yλ��
    QLabel* y_Position{};

    // CCD������Ϣ��ʾ
    QLabel* m_labelInfo{};

    // CCD��ʾ����
    QWidget* m_centralWidget{};

    // ��ʾͼ����
    Display* m_display{};

    // �ؼ�����
    QHBoxLayout* Vlayout1{};

    // �ؼ�����
    QHBoxLayout* Vlayout2{};

    // ͼ������
    AcquisitionWorker* m_acquisitionWorker{};

    // ʵ�ֶ��߳�
    QThread m_acquisitionThread{};

    // ������ô���
    CCDSetUserface* CCDSet{};

private:
    // �رմ���ʱ�䣬����ѯ���Ƿ��˳�
    void closeEvent(QCloseEvent* event);

    // ������
    int connectSystemMark();

    // ����PI
    bool connectSystemPi();

    // ����PI������Ϣ
    void feedBackDevice();

    // ʵ�ֶ���Ч��
    void CreateTimer();

    // ��ʱ��1����
    void startAnimation1();

    // ��ʱ��1ֹͣ
    void stopAnimation1();

    // �����ı�
    void updateText1();

    // ��ʱ��2����
    void startAnimation2();

    // ��ʱ��2ֹͣ
    void stopAnimation2();

    // �����ı�
    void updateText2();

    // ��ʼ��ʵʱ��ʾ����
    void InitMarkDataVisual();

    // ��ʼ��CCD����
    void CreateCCD();

    // CCD��ʼ�ɼ�
    void OpenCCDLibrary();

    // ��ʼ������ؼ�
    void initButton();

    // ��ʼ��״̬��
    void CreateStatuBar();

    // �������ݱ���߳�
    void CreateMarkWorkerThread();

    // �����źŲ�
    void CreateAcquisitionWorkerThreadCCD();

    // �����źŲ�
    void CreateAcquisitionWorkerThreadPI();

    // ��ʼ�ɼ�PIλ��
    void StartAcquisitionPI();

    // �����ɼ�
    void StartAcquisition();

    // ֹͣ�ɼ�
    void StopAcquisition();

private slots:
    // ���������Ϣ
    void HandleLibraryError(QString message, int status);

    // ���ʹ����ź�
    static void EmitErrorSignal(const char* message, int status, void* errorCallbackContext);

    // Qt about ������
    void OnAboutQtLinkActivated(const QString& link);

    // CCD�ɼ�����
    void OnButtonStopStart();

    // ���´���������CCD�ɼ�ʱ��
    void OnCounterUpdated(unsigned int frameCounter, unsigned int errorCounter);

    // ���ݴ������Ϣ�������Ƿ���ǰ�˳�����
    void HandleErrorAndQuit(QString message);

signals:
    // ���ʹ����ź���ʾ
    void libraryError(QString message, int status);

private:
    Ui::UFO ui;
};
