#pragma once

//���������������
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QThread>
#include <QtDataVisualization>
#include <QSettings>
#include "PI_GCS2_DLL_dynamicp_loader.h"
#include "CSCInterface_dynamicm_loader.h"
#include "ids_peak_comfort_c.h"
#include "acquisitionworker.h"
#include "CCDSetUserface.h"
#include "backend.h"
#include "display.h"
#include "piRealpos.h"
#include "dataSortgap.h"
#include "MarkCorrType.h"
#include "MarkAreaSet1.h"
#include "MarkAreaSet2.h"
#include "MarkParaSet.h"
#include "laserSet.h"
#include "SystemInfo.h"
#include "DataSortThread.h"
#include "DataVisual.h"
#include "MarkData.h"
#include "piControl.h"
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
    // ����ļ���ַ
    QString aFileName{};

    // ����ı�������
    int DataCounts{};

    // ��������
    int dataRows{};

    // ��������
    int dataColums{};

    // ����ı���������
    bool DataType{};

    // ������״̬
    bool M_IsConnected{};

    // PI����״̬
    bool P_IsConnected{};

    // ��ҵ�������״̬
    bool C_IsConnected{};

    // ��������״̬
    bool S_IsConnected{};

    // ʵ�ֶ���Ч��1
    int mIndex = 1;

    // ʵ�ֶ���Ч��2
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

    // ini�ļ�·��
    QString m_FileName{};

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

    // PIʵʱλ���߳�
    QThread PiThread;

    // PIʵʱλ��
    piRealpos* realpos{};

    // PIʵʱλ���߳�
    QThread MarkThread;

    // Ԥ��������
    dataSortgap* gap{};

    // У����������
    MarkCorrType* corrWay{};

    // У��1����
    MarkAreaSet1* markSet1{};

    // У��2����
    MarkAreaSet2* markSet2{};

    // ����������
    laserSet* laserset{};

    // ��̲�������
    MarkParaSet* paraSet{};

    // Ԥ����ini�ļ�
    QSettings* gapReadini{};

    // У������ini�ļ�
    QSettings* correctWayReadini{};
    
    // У������ini�ļ�
    QSettings* correctReadini{};

    // ������ini�ļ�
    QSettings* laserReadini{};

    // ϵͳ����ini�ļ�
    QSettings* systemReadini{};

    // ϵͳ��Ϣini�ļ�
    QSettings* systemInfoini{};

    // ϵͳ��Ϣ��ʾ
    SystemInfo* sysInfo{};

    // ���ݶ�ȡ�߳�
    DataSortThread* dataRead;

    // ���ݿ��ӻ�
    DataVisual* dataVis{};

    // PI���ƽ���
    piControl* piSet{};

private:
    // �رմ���ʱ�䣬����ѯ���Ƿ��˳�
    void closeEvent(QCloseEvent* event);

    // ����ini�ļ�
    void InitSetting();

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

    // ʵʱ����PIλ��
    void RefreshPiPos(double u_PiPosition);

    // �����̴߳�����Ϣ
    void ResetWrongText(QString dataStatus);

    // ��ʾ���ݼ�����������ô���
    void on_actPreGapInput_triggered();

    // ִ����ʾУ���������ý���
    void on_actCorrectMethod_triggered();

    // ִ����ʾ�������ý���
    void on_actSetLaser_triggered();

    // ִ����ʾ����������ý���
    void on_actSetMarkArea_triggered();

    // ִ��ϵͳ��������
    void on_actSetSystemPara_triggered();

    // �ָ�ϵͳĬ�ϲ�������
    void on_actDefaultPara_triggered();

    // ��ȡ����ļ�
    void on_actOpenFile_triggered();

    // �˳�����
    void on_actQuit_triggered();

    // ϵͳ��Ϣ��ʾ
    void on_actSystemInfo_triggered();

    // ִ����ʾ���ݿ��ӻ�����
    void on_acDataVisual_triggered();

    // ��ʾPI���ý���
    void on_actConnectPI_triggered();

    // �������ݶ�ȡ״̬
    void ResetText(QString dataStatus);

    // ����������״̬
    void ResetDataText(int dataNum);
    
signals:
    // ���ʹ����ź���ʾ
    void libraryError(QString message, int status);

private:
    Ui::UFO ui;
};
