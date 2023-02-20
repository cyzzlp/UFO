#pragma once
//解决汉字乱码问题
#pragma execution_character_set("utf-8")

#include "acquisitionworker.h"
#include <QTimer>
#include <QThread>
#include <QDialog>
#include "ui_CCDSetUserface.h"

class CCDSetUserface : public QDialog
{
    Q_OBJECT

public:
    CCDSetUserface(QWidget* parent = nullptr);
    ~CCDSetUserface();

public slots:
    void CheckForChangedValues();

signals:
    void error(QString message);
    void exposureAutoModeChanged(bool active);
    void updateExposureTime();

private:
    // Timer to update controls
    QTimer* m_timer;

    // Variables to calculate slider positions for double values
    double m_targetPercentileMin = 0;
    double m_targetPercentileMax = 0;
    double m_targetPercentileInc = 0;

    double m_gainMasterMin = 0;
    double m_gainMasterMax = 0;
    double m_gainMasterInc = 0;
    double m_gainRedMin = 0;
    double m_gainRedMax = 0;
    double m_gainRedInc = 0;
    double m_gainGreenMin = 0;
    double m_gainGreenMax = 0;
    double m_gainGreenInc = 0;
    double m_gainBlueMin = 0;
    double m_gainBlueMax = 0;
    double m_gainBlueInc = 0;

    double m_gammaMin = 0;
    double m_gammaMax = 0;
    double m_gammaInc = 0;

    bool m_isMonoCamera = false;

private:
    void UpdateBrightnessAutoModes();
    void UpdateBrightnessRoi();
    void UpdateBrightnessOptions();

    void UpdateWhiteBalanceAutoMode();
    void UpdateWhiteBalanceRoi();

    void UpdateGain();
    void UpdateGamma();

    void UpdateColorCorrection();

    void UpdateTransformations();

    void UpdateHotpixel();

    // Handler functions when GUI controls are manipulated
    void OnComboExposureMode(QString text);
    void OnComboGainMode(QString text);

    void OnComboBrightnessRoiMode(QString text);
    void OnSliderBrightnessRoi(int value);
    void OnEditBrightnessRoi();

    void OnSliderTarget(int value);
    void OnEditTarget();

    void OnSliderTargetPercentile(int value);
    void OnEditTargetPercentile();

    void OnSliderTargetTolerance(int value);
    void OnEditTargetTolerance();

    void OnComboWhiteBalanceMode(QString text);

    void OnComboWhiteBalanceRoiMode(QString text);
    void OnSliderWhiteBalanceRoi(int value);
    void OnEditWhiteBalanceRoi();

    void OnSliderGainMaster(int value);
    void OnEditGainMaster();

    void OnSliderGainRed(int value);
    void OnEditGainRed();

    void OnSliderGainGreen(int value);
    void OnEditGainGreen();

    void OnSliderGainBlue(int value);
    void OnEditGainBlue();

    void OnSliderGamma(int value);
    void OnEditGamma();

    void OnColorCorrectionEnable(int state);
    void OnEditCcm();

    void OnButtonCcmDefault();
    void OnButtonCcmIdentity();

    void OnCheckBoxMirrorLeftRight(int state);
    void OnCheckBoxMirrorUpDown(int state);

    void OnHotpixelCorrectionEnable(int state);
    void OnSpinBoxHotpixelSensitivity(int value);
    void OnButtonHotpixelResetList();

    void CreateConnectandSetValue();

private:
    double m_exposureTime{};
    double m_exposureTimeMin{};
    double m_exposureTimeMax{};
    double m_exposureTimeInc{};

    double m_frameRate{};
    double m_frameRateMin{};
    double m_frameRateMax{};
    double m_frameRateInc{};

    bool m_exposureAutoActive{};
    bool m_acquisitionRunning{};

    bool m_hasError{};
    bool m_blockErrorMessages{};

    QThread m_acquisitionThread;
    AcquisitionWorker* m_acquisitionWorker;

private:
    void UpdateExposureTimeControl();
    void UpdateFrameRateControl();

public slots:
    void UpdateControls();
    void HandleErrorAndQuit(QString message);
    void OnSliderExposureTime();
    void OnEditExposureTime();
    void OnSliderFrameRate();
    void OnEditFrameRate();
    void OnExposureAutoModeChanged(bool active);

private:
    Ui::CCDSetUserface ui;
};
