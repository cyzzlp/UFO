#include <QMessageBox>
#include <QTabwidget>
#include "ids_peak_comfort_c_dynamic_loader.h"
#include "backend.h"
#include "CCDSetUserface.h"

CCDSetUserface::CCDSetUserface(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    CreateConnectandSetValue();

    m_timer = new QTimer(this);
    // 创建一个计时器和一个线程，用于在启用自动功能时监视变化
    connect(m_timer, &QTimer::timeout, this, &CCDSetUserface::CheckForChangedValues);

    m_isMonoCamera = backend_camera_isMono();
    if (m_isMonoCamera)
    {
        ui.m_sliderGainRed->setEnabled(false);
        ui.m_editGainRed->setEnabled(false);
        ui.m_sliderGainGreen->setEnabled(false);
        ui.m_editGainGreen->setEnabled(false);
        ui.m_sliderGainBlue->setEnabled(false);
        ui.m_editGainBlue->setEnabled(false);
    }

    // 实现自动曝光联动
    connect(ui.m_sliderExposureTime, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderExposureTime);
    connect(ui.m_editExposureTime, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditExposureTime);

    // 实现调节帧率
    connect(ui.m_sliderFrameRate, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderFrameRate);
    connect(ui.m_editFrameRate, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditFrameRate);

    // IPL 功能的控件
    connect(this, &CCDSetUserface::error, this, &CCDSetUserface::HandleErrorAndQuit);
    connect(this, &CCDSetUserface::exposureAutoModeChanged, this, &CCDSetUserface::OnExposureAutoModeChanged);
    connect(this, &CCDSetUserface::updateExposureTime, this, &CCDSetUserface::UpdateExposureTimeControl);
    connect(this, &CCDSetUserface::updateExposureTime, this, &CCDSetUserface::UpdateFrameRateControl);

    UpdateControls();
    UpdateBrightnessAutoModes();
    UpdateBrightnessRoi();
    UpdateBrightnessOptions();
    UpdateWhiteBalanceAutoMode();
    UpdateWhiteBalanceRoi();
    UpdateGain();
    UpdateGamma();
    UpdateColorCorrection();
    UpdateTransformations();
    UpdateHotpixel();
}

CCDSetUserface::~CCDSetUserface()
{

}

void CCDSetUserface::CreateConnectandSetValue()
{
    // Brightness Exposure
    ui.m_comboExposureMode->addItems({ "Off", "Once", "Continuous" });
    connect(ui.m_comboExposureMode, &QComboBox::currentTextChanged, this, &CCDSetUserface::OnComboExposureMode);

    // Brightness Gain
    ui.m_comboGainMode->addItems({ "Off", "Once", "Continuous" });
    connect(ui.m_comboGainMode, &QComboBox::currentTextChanged, this, &CCDSetUserface::OnComboGainMode);

    // Brightness ROI Mode
    ui.m_comboBrightnessRoiMode->addItems({ "Full Image", "Manual" });
    connect(ui.m_comboBrightnessRoiMode, &QComboBox::currentTextChanged, this, &CCDSetUserface::OnComboBrightnessRoiMode);

    // Brightness ROI
    connect(ui.m_sliderBrightnessRoiOffsetX, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderBrightnessRoi);
    ui.m_editBrightnessRoiOffsetX->setFixedWidth(80);
    ui.m_editBrightnessRoiOffsetX->setValidator(new QIntValidator(ui.m_editBrightnessRoiOffsetX));
    connect(ui.m_editBrightnessRoiOffsetX, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditBrightnessRoi);

    connect(ui.m_sliderBrightnessRoiOffsetY, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderBrightnessRoi);
    ui.m_editBrightnessRoiOffsetY->setFixedWidth(80);
    ui.m_editBrightnessRoiOffsetY->setValidator(new QIntValidator(ui.m_editBrightnessRoiOffsetY));
    connect(ui.m_editBrightnessRoiOffsetY, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditBrightnessRoi);

    connect(ui.m_sliderBrightnessRoiWidth, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderBrightnessRoi);
    ui.m_editBrightnessRoiWidth->setFixedWidth(80);
    ui.m_editBrightnessRoiWidth->setValidator(new QIntValidator(ui.m_editBrightnessRoiWidth));
    connect(ui.m_editBrightnessRoiWidth, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditBrightnessRoi);

    connect(ui.m_sliderBrightnessRoiHeight, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderBrightnessRoi);
    ui.m_editBrightnessRoiHeight->setFixedWidth(80);
    ui.m_editBrightnessRoiHeight->setValidator(new QIntValidator(ui.m_editBrightnessRoiHeight));
    connect(ui.m_editBrightnessRoiHeight, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditBrightnessRoi);

    // Target
    ui.m_editTarget->setFixedWidth(80);
    auto range = backend_ipl_brightness_target_range();
    ui.m_sliderTarget->setRange(range.min, range.max);
    ui.m_editTarget->setValidator(new QIntValidator(range.min, range.max, ui.m_editTarget));
    connect(ui.m_sliderTarget, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderTarget);
    connect(ui.m_editTarget, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditTarget);

    // Target Percentile
    ui.m_editTargetPercentile->setFixedWidth(80);
    auto doubleRange = backend_ipl_brightness_targetPercentile_range();
    m_targetPercentileMin = doubleRange.min;
    m_targetPercentileMax = doubleRange.max;
    m_targetPercentileInc = doubleRange.inc;
    auto steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    ui.m_sliderTargetPercentile->setRange(0, steps);
    connect(ui.m_sliderTargetPercentile, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderTargetPercentile);
    connect(ui.m_editTargetPercentile, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditTargetPercentile);

    // Target Tolerance
    ui.m_editTargetTolerance->setFixedWidth(80);
    range = backend_ipl_brightness_targetTolerance_range();
    ui.m_sliderTargetTolerance->setRange(range.min, range.max);
    ui.m_editTargetTolerance->setValidator(new QIntValidator(range.min, range.max, ui.m_editTargetTolerance));
    connect(ui.m_sliderTargetTolerance, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderTargetTolerance);
    connect(ui.m_editTargetTolerance, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditTargetTolerance);

    // WhiteBalance Mode
    ui.m_comboWhiteBalanceMode->addItems({ "Off", "Once", "Continuous" });
    connect(ui.m_comboWhiteBalanceMode, &QComboBox::currentTextChanged, this, &CCDSetUserface::OnComboWhiteBalanceMode);

    // WhiteBalance ROI Mode
    ui.m_comboWhiteBalanceRoiMode->addItems({ "Full Image", "Manual" });
    connect(ui.m_comboWhiteBalanceRoiMode, &QComboBox::currentTextChanged, this, &CCDSetUserface::OnComboWhiteBalanceRoiMode);

    // WhiteBalance ROI
    connect(ui.m_sliderWhiteBalanceRoiOffsetX, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderWhiteBalanceRoi);
    ui.m_editWhiteBalanceRoiOffsetX->setFixedWidth(80);
    ui.m_editWhiteBalanceRoiOffsetX->setValidator(new QIntValidator(ui.m_editWhiteBalanceRoiOffsetX));
    connect(ui.m_editWhiteBalanceRoiOffsetX, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditWhiteBalanceRoi);

    connect(ui.m_sliderWhiteBalanceRoiOffsetY, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderWhiteBalanceRoi);
    ui.m_editWhiteBalanceRoiOffsetY->setFixedWidth(80);
    ui.m_editWhiteBalanceRoiOffsetY->setValidator(new QIntValidator(ui.m_editWhiteBalanceRoiOffsetY));
    connect(ui.m_editWhiteBalanceRoiOffsetY, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditWhiteBalanceRoi);

    connect(ui.m_sliderWhiteBalanceRoiWidth, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderWhiteBalanceRoi);
    ui.m_editWhiteBalanceRoiWidth->setFixedWidth(80);
    ui.m_editWhiteBalanceRoiWidth->setValidator(new QIntValidator(ui.m_editWhiteBalanceRoiWidth));
    connect(ui.m_editWhiteBalanceRoiWidth, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditWhiteBalanceRoi);

    connect(ui.m_sliderWhiteBalanceRoiHeight, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderWhiteBalanceRoi);
    ui.m_editWhiteBalanceRoiHeight->setFixedWidth(80);
    ui.m_editWhiteBalanceRoiHeight->setValidator(new QIntValidator(ui.m_editWhiteBalanceRoiHeight));
    connect(ui.m_editWhiteBalanceRoiHeight, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditWhiteBalanceRoi);

    // Master Gain
    ui.m_editGainMaster->setFixedWidth(80);
    doubleRange = backend_ipl_gainMaster_range();
    m_gainMasterMin = doubleRange.min;
    m_gainMasterMax = doubleRange.max;
    m_gainMasterInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    ui.m_sliderGainMaster->setRange(0, steps);
    connect(ui.m_sliderGainMaster, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderGainMaster);
    connect(ui.m_editGainMaster, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditGainMaster);

    // Red Gain
    ui.m_editGainRed->setFixedWidth(80);
    doubleRange = backend_ipl_gainRed_range();
    m_gainRedMin = doubleRange.min;
    m_gainRedMax = doubleRange.max;
    m_gainRedInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    ui.m_sliderGainRed->setRange(0, steps);
    connect(ui.m_sliderGainRed, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderGainRed);
    connect(ui.m_editGainRed, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditGainRed);

    // Green Gain
    ui.m_editGainGreen->setFixedWidth(80);
    doubleRange = backend_ipl_gainGreen_range();
    m_gainGreenMin = doubleRange.min;
    m_gainGreenMax = doubleRange.max;
    m_gainGreenInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    ui.m_sliderGainGreen->setRange(0, steps);
    connect(ui.m_sliderGainGreen, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderGainGreen);
    connect(ui.m_editGainGreen, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditGainGreen);

    // Blue Gain
    ui.m_editGainBlue->setFixedWidth(80);
    doubleRange = backend_ipl_gainBlue_range();
    m_gainBlueMin = doubleRange.min;
    m_gainBlueMax = doubleRange.max;
    m_gainBlueInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    ui.m_sliderGainBlue->setRange(0, steps);
    connect(ui.m_sliderGainBlue, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderGainBlue);
    connect(ui.m_editGainBlue, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditGainBlue);

    // Gamma
    ui.m_editGamma->setFixedWidth(80);
    doubleRange = backend_ipl_gamma_range();
    m_gammaMin = doubleRange.min;
    m_gammaMax = doubleRange.max;
    m_gammaInc = doubleRange.inc;
    steps = static_cast<int>((doubleRange.max - doubleRange.min) / doubleRange.inc) + 1;
    ui.m_sliderGamma->setRange(0, steps);
    connect(ui.m_sliderGamma, &QSlider::valueChanged, this, &CCDSetUserface::OnSliderGamma);
    connect(ui.m_editGamma, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditGamma);

    // Color Correction
    connect(ui.m_checkBoxColorCorrectionEnable, &QCheckBox::stateChanged, this, &CCDSetUserface::OnColorCorrectionEnable);
    connect(ui.m_editCcm00, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm01, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm02, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm10, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm11, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm12, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm20, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm21, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_editCcm22, &QLineEdit::editingFinished, this, &CCDSetUserface::OnEditCcm);
    connect(ui.m_buttonCcmDefault, &QPushButton::clicked, this, &CCDSetUserface::OnButtonCcmDefault);
    connect(ui.m_buttonCcmIdentity, &QPushButton::clicked, this, &CCDSetUserface::OnButtonCcmIdentity);

    // Image transformation
    connect(ui.m_checkBoxMirrorLeftRight, &QCheckBox::stateChanged, this, &CCDSetUserface::OnCheckBoxMirrorLeftRight);
    connect(ui.m_checkBoxMirrorUpDown, &QCheckBox::stateChanged, this, &CCDSetUserface::OnCheckBoxMirrorUpDown);

    // Hotpixel
    connect(ui.m_checkBoxHotpixelEnable, &QCheckBox::stateChanged, this, &CCDSetUserface::OnHotpixelCorrectionEnable);
    ui.m_spinBoxHotpixelSensitivity->setRange(1, 5);
    connect(ui.m_spinBoxHotpixelSensitivity, QOverload<int>::of(&QSpinBox::valueChanged), this,
        &CCDSetUserface::OnSpinBoxHotpixelSensitivity);
    connect(ui.m_buttonHotpixelResetList, &QPushButton::clicked, this, &CCDSetUserface::OnButtonHotpixelResetList);
}

void CCDSetUserface::UpdateControls()
{
    UpdateExposureTimeControl();
    UpdateFrameRateControl();
}

void CCDSetUserface::UpdateBrightnessOptions()
{
    auto targetPercentile = backend_ipl_brightness_targetPercentile_get();
    auto step = static_cast<int>((targetPercentile - m_targetPercentileMin) / m_targetPercentileInc);

    auto target = backend_ipl_brightness_target_get();

    auto targetTolerance = backend_ipl_brightness_targetTolerance_get();

    ui.m_sliderTargetPercentile->blockSignals(true);
    ui.m_editTargetPercentile->blockSignals(true);
    ui.m_sliderTarget->blockSignals(true);
    ui.m_editTarget->blockSignals(true);
    ui.m_sliderTargetTolerance->blockSignals(true);
    ui.m_editTargetTolerance->blockSignals(true);

    ui.m_sliderTargetPercentile->setValue(step);
    ui.m_editTargetPercentile->setText(QString::number(targetPercentile, 'f', 2));

    ui.m_sliderTarget->setValue(target);
    ui.m_editTarget->setText(QString::number(target));

    ui.m_sliderTargetTolerance->setValue(targetTolerance);
    ui.m_editTargetTolerance->setText(QString::number(targetTolerance));

    ui.m_sliderTargetPercentile->blockSignals(false);
    ui.m_editTargetPercentile->blockSignals(false);
    ui.m_sliderTarget->blockSignals(false);
    ui.m_editTarget->blockSignals(false);
    ui.m_sliderTargetTolerance->blockSignals(false);
    ui.m_editTargetTolerance->blockSignals(false);
}

void CCDSetUserface::UpdateExposureTimeControl()
{
    if (backend_exposureTime_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        ui.m_sliderExposureTime->blockSignals(true);
        ui.m_editExposureTime->blockSignals(true);

        struct range_double range = backend_exposureTime_range();
        if (range.min == 0 && range.max == 0 && range.inc == 0)
        {
            HandleErrorAndQuit("Unable to read exposure time range.");
        }
        double exposureTime = backend_exposureTime_get();
        if (exposureTime == 0)
        {
            HandleErrorAndQuit("Unable to read exposure time.");
        }

        m_exposureTimeMin = range.min;

        m_exposureTimeInc = range.inc;

        int steps = static_cast<int>((range.max - m_exposureTimeMin) / m_exposureTimeInc);
        ui.m_sliderExposureTime->setRange(0, steps);

        int value = static_cast<int>((exposureTime - m_exposureTimeMin) / m_exposureTimeInc);

        ui.m_sliderExposureTime->setValue(value);

        ui.m_editExposureTime->setText(QString::number(exposureTime, 'f', 2));

        // Re-establish signals from slider and edit
        ui.m_sliderExposureTime->blockSignals(false);
        ui.m_editExposureTime->blockSignals(false);
    }

    if (backend_exposureTime_isWriteable() && (!m_exposureAutoActive || !m_acquisitionRunning))
    {
        ui.m_sliderExposureTime->setEnabled(true);
        ui.m_editExposureTime->setEnabled(true);
    }
    else
    {
        ;
        ui.m_sliderExposureTime->setEnabled(false);
        ui.m_editExposureTime->setEnabled(false);
    }
}

void CCDSetUserface::UpdateFrameRateControl()
{
    if (backend_frameRate_isReadable())
    {
        // Block signals from slider and edit to avoid signal loops
        ui.m_sliderFrameRate->blockSignals(true);
        ui.m_editFrameRate->blockSignals(true);

        struct range_double range = backend_frameRate_range();
        if (range.min == .0 && range.max == .0 && range.inc == .0)
        {
            HandleErrorAndQuit("Unable to read frame rate range.");
        }
        double frameRate = backend_frameRate_get();
        if (frameRate == 0)
        {
            HandleErrorAndQuit("Unable to read frame rate.");
        }

        m_frameRateMin = range.min;

        m_frameRateInc = range.inc;

        int steps = static_cast<int>((range.max - m_frameRateMin) / m_frameRateInc);
        ui.m_sliderFrameRate->setRange(0, steps);

        int value = static_cast<int>((frameRate - m_frameRateMin) / m_frameRateInc);

        ui.m_sliderFrameRate->setValue(value);

        ui.m_editFrameRate->setText(QString::number(frameRate, 'f', 2));


        // Re-establish signals from slider and edit
        ui.m_sliderFrameRate->blockSignals(false);
        ui.m_editFrameRate->blockSignals(false);
    }

    if (backend_frameRate_isWriteable())
    {
        ui.m_sliderFrameRate->setEnabled(true);
        ui.m_editFrameRate->setEnabled(true);
    }
    else
    {
        ui.m_sliderFrameRate->setEnabled(false);
        ui.m_editFrameRate->setEnabled(false);
    }
}

void CCDSetUserface::HandleErrorAndQuit(QString message)
{
    // block all error messages due to a critical message
    if (m_blockErrorMessages)
        return;

    message += "\n(Error!)";
    message += "\nExiting application";

    QMessageBox::critical(nullptr, "Error", message, QMessageBox::Ok);
    qApp->quit();
}

void CCDSetUserface::OnSliderExposureTime()
{
    int value = ui.m_sliderExposureTime->value();

    double exposureTime = m_exposureTimeMin + static_cast<double>(value) * m_exposureTimeInc;

    if (backend_exposureTime_isWriteable())
    {
        backend_exposureTime_set(exposureTime);

        exposureTime = backend_exposureTime_get();

        ui.m_editExposureTime->blockSignals(true);
        ui.m_editExposureTime->setText(QString::number(exposureTime, 'f', 2));
        ui.m_editExposureTime->blockSignals(false);
    }
    UpdateFrameRateControl();
}

void CCDSetUserface::OnEditExposureTime()
{
    double exposureTime = ui.m_editExposureTime->text().toDouble();

    if (backend_exposureTime_isWriteable())
    {
        backend_exposureTime_set(exposureTime);

        exposureTime = backend_exposureTime_get();

        int value = static_cast<int>((exposureTime - m_exposureTimeMin) / m_exposureTimeInc);

        ui.m_sliderExposureTime->blockSignals(true);
        ui.m_sliderExposureTime->setValue(value);
        ui.m_sliderExposureTime->blockSignals(false);
    }
    UpdateFrameRateControl();
}

void CCDSetUserface::OnSliderFrameRate()
{
    int value = ui.m_sliderFrameRate->value();

    double frameRate = m_frameRateMin + static_cast<double>(value) * m_frameRateInc;

    if (backend_frameRate_isWriteable())
    {
        backend_frameRate_set(frameRate);

        frameRate = backend_frameRate_get();

        ui.m_editFrameRate->blockSignals(true);
        ui.m_editFrameRate->setText(QString::number(frameRate, 'f', 2));
        ui.m_editFrameRate->blockSignals(false);
    }
}

void CCDSetUserface::OnEditFrameRate()
{
    double frameRate = ui.m_editFrameRate->text().toDouble();

    if (backend_frameRate_isWriteable())
    {
        backend_frameRate_set(frameRate);

        frameRate = backend_frameRate_get();

        int value = static_cast<int>((frameRate - m_frameRateMin) / m_frameRateInc);

        ui.m_sliderFrameRate->blockSignals(true);
        ui.m_sliderFrameRate->setValue(value);
        ui.m_sliderFrameRate->blockSignals(false);
    }
}

void CCDSetUserface::UpdateBrightnessAutoModes()
{
    auto exposureMode = backend_ipl_brightness_exposureMode_get();
    if (ui.m_comboExposureMode->currentIndex() != exposureMode)
    {
        ui.m_comboExposureMode->setCurrentIndex(exposureMode);
    }
    auto gainMode = backend_ipl_brightness_gainMode_get();
    if (ui.m_comboGainMode->currentIndex() != gainMode)
    {
        ui.m_comboGainMode->setCurrentIndex(gainMode);
    }
}

void CCDSetUserface::UpdateBrightnessRoi()
{
    auto roiMode = backend_ipl_brightness_roiMode_get();
    if (ui.m_comboBrightnessRoiMode->currentIndex() != roiMode)
    {
        ui.m_comboBrightnessRoiMode->setCurrentIndex(roiMode);
    }

    auto enableManualRoi = (roiMode == 1);
    ui.m_sliderBrightnessRoiOffsetX->setEnabled(enableManualRoi);
    ui.m_editBrightnessRoiOffsetX->setEnabled(enableManualRoi);
    ui.m_sliderBrightnessRoiOffsetY->setEnabled(enableManualRoi);
    ui.m_editBrightnessRoiOffsetY->setEnabled(enableManualRoi);
    ui.m_sliderBrightnessRoiWidth->setEnabled(enableManualRoi);
    ui.m_editBrightnessRoiWidth->setEnabled(enableManualRoi);
    ui.m_sliderBrightnessRoiHeight->setEnabled(enableManualRoi);
    ui.m_editBrightnessRoiHeight->setEnabled(enableManualRoi);

    auto rangeX = backend_ipl_brightness_roiOffsetX_range();
    if (rangeX.min == 0 && rangeX.max == 0 && rangeX.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto rangeY = backend_ipl_brightness_roiOffsetY_range();
    if (rangeY.min == 0 && rangeY.max == 0 && rangeY.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto rangeW = backend_ipl_brightness_roiWidth_range();
    if (rangeW.min == 0 && rangeW.max == 0 && rangeW.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto rangeH = backend_ipl_brightness_roiHeight_range();
    if (rangeH.min == 0 && rangeH.max == 0 && rangeH.inc == 0)
    {
        emit error("Unable to read brightness ROI range.");
        return;
    }
    auto roi = backend_ipl_brightness_roi_get();
    if (roi.offset.x == 0 && roi.offset.y == 0 && roi.size.width == 0 && roi.size.height == 0)
    {
        emit error("Unable to read brightness ROI.");
        return;
    }

    ui.m_sliderBrightnessRoiOffsetX->blockSignals(true);
    ui.m_editBrightnessRoiOffsetX->blockSignals(true);
    ui.m_sliderBrightnessRoiOffsetY->blockSignals(true);
    ui.m_editBrightnessRoiOffsetY->blockSignals(true);
    ui.m_sliderBrightnessRoiWidth->blockSignals(true);
    ui.m_editBrightnessRoiWidth->blockSignals(true);
    ui.m_sliderBrightnessRoiHeight->blockSignals(true);
    ui.m_editBrightnessRoiHeight->blockSignals(true);

    ui.m_sliderBrightnessRoiOffsetX->setRange(rangeX.min, rangeX.max);
    ui.m_sliderBrightnessRoiOffsetX->setSingleStep(rangeX.inc);
    ui.m_sliderBrightnessRoiOffsetX->setValue(roi.offset.x);
    ui.m_editBrightnessRoiOffsetX->setValidator(new QIntValidator(rangeX.min, rangeX.max, ui.m_editBrightnessRoiOffsetX));
    ui.m_editBrightnessRoiOffsetX->setText(QString::number(roi.offset.x));

    ui.m_sliderBrightnessRoiOffsetY->setRange(rangeY.min, rangeY.max);
    ui.m_sliderBrightnessRoiOffsetY->setSingleStep(rangeY.inc);
    ui.m_sliderBrightnessRoiOffsetY->setValue(roi.offset.y);
    ui.m_editBrightnessRoiOffsetY->setValidator(new QIntValidator(rangeY.min, rangeY.max, ui.m_editBrightnessRoiOffsetY));
    ui.m_editBrightnessRoiOffsetY->setText(QString::number(roi.offset.y));

    ui.m_sliderBrightnessRoiWidth->setRange(rangeW.min, rangeW.max);
    ui.m_sliderBrightnessRoiWidth->setSingleStep(rangeW.inc);
    ui.m_sliderBrightnessRoiWidth->setValue(roi.size.width);
    ui.m_editBrightnessRoiWidth->setValidator(new QIntValidator(rangeW.min, rangeW.max, ui.m_editBrightnessRoiWidth));
    ui.m_editBrightnessRoiWidth->setText(QString::number(roi.size.width));

    ui.m_sliderBrightnessRoiHeight->setRange(rangeH.min, rangeH.max);
    ui.m_sliderBrightnessRoiHeight->setSingleStep(rangeH.inc);
    ui.m_sliderBrightnessRoiHeight->setValue(roi.size.height);
    ui.m_editBrightnessRoiHeight->setValidator(new QIntValidator(rangeH.min, rangeH.max, ui.m_editBrightnessRoiHeight));
    ui.m_editBrightnessRoiHeight->setText(QString::number(roi.size.height));

    ui.m_sliderBrightnessRoiOffsetX->blockSignals(false);
    ui.m_editBrightnessRoiOffsetX->blockSignals(false);
    ui.m_sliderBrightnessRoiOffsetY->blockSignals(false);
    ui.m_editBrightnessRoiOffsetY->blockSignals(false);
    ui.m_sliderBrightnessRoiWidth->blockSignals(false);
    ui.m_editBrightnessRoiWidth->blockSignals(false);
    ui.m_sliderBrightnessRoiHeight->blockSignals(false);
    ui.m_editBrightnessRoiHeight->blockSignals(false);
}

void CCDSetUserface::UpdateWhiteBalanceAutoMode()
{
    if (m_isMonoCamera)
        return;

    auto whiteBalanceMode = backend_ipl_whiteBalance_mode_get();
    if (ui.m_comboExposureMode->currentIndex() != whiteBalanceMode)
    {
        ui.m_comboExposureMode->setCurrentIndex(whiteBalanceMode);
    }
}

void CCDSetUserface::UpdateWhiteBalanceRoi()
{
    if (m_isMonoCamera)
        return;

    auto roiMode = backend_ipl_whiteBalance_roiMode_get();
    if (ui.m_comboWhiteBalanceRoiMode->currentIndex() != roiMode)
    {
        ui.m_comboWhiteBalanceRoiMode->setCurrentIndex(roiMode);
    }

    auto enableManualRoi = (roiMode == 1);
    ui.m_sliderWhiteBalanceRoiOffsetX->setEnabled(enableManualRoi);
    ui.m_editWhiteBalanceRoiOffsetX->setEnabled(enableManualRoi);
    ui.m_sliderWhiteBalanceRoiOffsetY->setEnabled(enableManualRoi);
    ui.m_editWhiteBalanceRoiOffsetY->setEnabled(enableManualRoi);
    ui.m_sliderWhiteBalanceRoiWidth->setEnabled(enableManualRoi);
    ui.m_editWhiteBalanceRoiWidth->setEnabled(enableManualRoi);
    ui.m_sliderWhiteBalanceRoiHeight->setEnabled(enableManualRoi);
    ui.m_editWhiteBalanceRoiHeight->setEnabled(enableManualRoi);

    auto rangeX = backend_ipl_whiteBalance_roiOffsetX_range();
    if (rangeX.min == 0 && rangeX.max == 0 && rangeX.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto rangeY = backend_ipl_whiteBalance_roiOffsetY_range();
    if (rangeY.min == 0 && rangeY.max == 0 && rangeY.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto rangeW = backend_ipl_whiteBalance_roiWidth_range();
    if (rangeW.min == 0 && rangeW.max == 0 && rangeW.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto rangeH = backend_ipl_whiteBalance_roiHeight_range();
    if (rangeH.min == 0 && rangeH.max == 0 && rangeH.inc == 0)
    {
        emit error("Unable to read white balance ROI range.");
        return;
    }
    auto roi = backend_ipl_whiteBalance_roi_get();
    if (roi.offset.x == 0 && roi.offset.y == 0 && roi.size.width == 0 && roi.size.height == 0)
    {
        emit error("Unable to read white balance ROI.");
        return;
    }

    ui.m_sliderWhiteBalanceRoiOffsetX->blockSignals(true);
    ui.m_editWhiteBalanceRoiOffsetX->blockSignals(true);
    ui.m_sliderWhiteBalanceRoiOffsetY->blockSignals(true);
    ui.m_editWhiteBalanceRoiOffsetY->blockSignals(true);
    ui.m_sliderWhiteBalanceRoiWidth->blockSignals(true);
    ui.m_editWhiteBalanceRoiWidth->blockSignals(true);
    ui.m_sliderWhiteBalanceRoiHeight->blockSignals(true);
    ui.m_editWhiteBalanceRoiHeight->blockSignals(true);

    ui.m_sliderWhiteBalanceRoiOffsetX->setRange(rangeX.min, rangeX.max);
    ui.m_sliderWhiteBalanceRoiOffsetX->setSingleStep(rangeX.inc);
    ui.m_sliderWhiteBalanceRoiOffsetX->setValue(roi.offset.x);
    ui.m_editWhiteBalanceRoiOffsetX->setValidator(new QIntValidator(rangeX.min, rangeX.max, ui.m_editWhiteBalanceRoiOffsetX));
    ui.m_editWhiteBalanceRoiOffsetX->setText(QString::number(roi.offset.x));

    ui.m_sliderWhiteBalanceRoiOffsetY->setRange(rangeY.min, rangeY.max);
    ui.m_sliderWhiteBalanceRoiOffsetY->setSingleStep(rangeY.inc);
    ui.m_sliderWhiteBalanceRoiOffsetY->setValue(roi.offset.y);
    ui.m_editWhiteBalanceRoiOffsetY->setValidator(new QIntValidator(rangeY.min, rangeY.max, ui.m_editWhiteBalanceRoiOffsetY));
    ui.m_editWhiteBalanceRoiOffsetY->setText(QString::number(roi.offset.y));

    ui.m_sliderWhiteBalanceRoiWidth->setRange(rangeW.min, rangeW.max);
    ui.m_sliderWhiteBalanceRoiWidth->setSingleStep(rangeW.inc);
    ui.m_sliderWhiteBalanceRoiWidth->setValue(roi.size.width);
    ui.m_editWhiteBalanceRoiWidth->setValidator(new QIntValidator(rangeW.min, rangeW.max, ui.m_editWhiteBalanceRoiWidth));
    ui.m_editWhiteBalanceRoiWidth->setText(QString::number(roi.size.width));

    ui.m_sliderWhiteBalanceRoiHeight->setRange(rangeH.min, rangeH.max);
    ui.m_sliderWhiteBalanceRoiHeight->setSingleStep(rangeH.inc);
    ui.m_sliderWhiteBalanceRoiHeight->setValue(roi.size.height);
    ui.m_editWhiteBalanceRoiHeight->setValidator(new QIntValidator(rangeH.min, rangeH.max, ui.m_editWhiteBalanceRoiHeight));
    ui.m_editWhiteBalanceRoiHeight->setText(QString::number(roi.size.height));

    ui.m_sliderWhiteBalanceRoiOffsetX->blockSignals(false);
    ui.m_editWhiteBalanceRoiOffsetX->blockSignals(false);
    ui.m_sliderWhiteBalanceRoiOffsetY->blockSignals(false);
    ui.m_editWhiteBalanceRoiOffsetY->blockSignals(false);
    ui.m_sliderWhiteBalanceRoiWidth->blockSignals(false);
    ui.m_editWhiteBalanceRoiWidth->blockSignals(false);
    ui.m_sliderWhiteBalanceRoiHeight->blockSignals(false);
    ui.m_editWhiteBalanceRoiHeight->blockSignals(false);
}

void CCDSetUserface::UpdateGain()
{
    double gainMaster = backend_ipl_gainMaster_get();
    auto stepMaster = static_cast<int>((gainMaster - m_gainMasterMin) / m_gainMasterInc);

    ui.m_sliderGainMaster->blockSignals(true);
    ui.m_editGainMaster->blockSignals(true);

    ui.m_sliderGainMaster->setValue(stepMaster);
    ui.m_editGainMaster->setText(QString::number(gainMaster, 'f', 2));

    ui.m_sliderGainMaster->blockSignals(false);
    ui.m_editGainMaster->blockSignals(false);

    if (!m_isMonoCamera)
    {
        double gainRed = backend_ipl_gainRed_get();
        double gainGreen = backend_ipl_gainGreen_get();
        double gainBlue = backend_ipl_gainBlue_get();

        auto stepRed = static_cast<int>((gainRed - m_gainRedMin) / m_gainRedInc);
        auto stepGreen = static_cast<int>((gainGreen - m_gainGreenMin) / m_gainGreenInc);
        auto stepBlue = static_cast<int>((gainBlue - m_gainBlueMin) / m_gainBlueInc);

        ui.m_sliderGainRed->blockSignals(true);
        ui.m_editGainRed->blockSignals(true);
        ui.m_sliderGainGreen->blockSignals(true);
        ui.m_editGainGreen->blockSignals(true);
        ui.m_sliderGainBlue->blockSignals(true);
        ui.m_editGainBlue->blockSignals(true);

        ui.m_sliderGainRed->setValue(stepRed);
        ui.m_editGainRed->setText(QString::number(gainRed, 'f', 2));

        ui.m_sliderGainGreen->setValue(stepGreen);
        ui.m_editGainGreen->setText(QString::number(gainGreen, 'f', 2));

        ui.m_sliderGainBlue->setValue(stepBlue);
        ui.m_editGainBlue->setText(QString::number(gainBlue, 'f', 2));

        ui.m_sliderGainRed->blockSignals(false);
        ui.m_editGainRed->blockSignals(false);
        ui.m_sliderGainGreen->blockSignals(false);
        ui.m_editGainGreen->blockSignals(false);
        ui.m_sliderGainBlue->blockSignals(false);
        ui.m_editGainBlue->blockSignals(false);
    }
}

void CCDSetUserface::UpdateGamma()
{
    double gamma = backend_ipl_gamma_get();
    auto step = static_cast<int>((gamma - m_gammaMin) / m_gammaInc);

    ui.m_sliderGamma->blockSignals(true);
    ui.m_editGamma->blockSignals(true);

    ui.m_sliderGamma->setValue(step);
    ui.m_editGamma->setText(QString::number(gamma, 'f', 2));

    ui.m_sliderGamma->blockSignals(false);
    ui.m_editGamma->blockSignals(false);
}


void CCDSetUserface::UpdateColorCorrection()
{
    if (m_isMonoCamera)
        return;

    auto enabled = backend_ipl_colorCorrection_isEnabled();
    ui.m_checkBoxColorCorrectionEnable->blockSignals(true);
    if (enabled)
    {
        ui.m_checkBoxColorCorrectionEnable->setCheckState(Qt::Checked);
    }
    else
    {
        ui.m_checkBoxColorCorrectionEnable->setCheckState(Qt::Unchecked);
    }
    ui.m_checkBoxColorCorrectionEnable->blockSignals(false);

    auto ccm = backend_ipl_colorCorrectionMatrix_get();

    ui.m_editCcm00->setText(QString::number(ccm.elementArray[0][0], 'f', 2));
    ui.m_editCcm01->setText(QString::number(ccm.elementArray[0][1], 'f', 2));
    ui.m_editCcm02->setText(QString::number(ccm.elementArray[0][2], 'f', 2));
    ui.m_editCcm10->setText(QString::number(ccm.elementArray[1][0], 'f', 2));
    ui.m_editCcm11->setText(QString::number(ccm.elementArray[1][1], 'f', 2));
    ui.m_editCcm12->setText(QString::number(ccm.elementArray[1][2], 'f', 2));
    ui.m_editCcm20->setText(QString::number(ccm.elementArray[2][0], 'f', 2));
    ui.m_editCcm21->setText(QString::number(ccm.elementArray[2][1], 'f', 2));
    ui.m_editCcm22->setText(QString::number(ccm.elementArray[2][2], 'f', 2));
}


void CCDSetUserface::UpdateTransformations()
{
    auto enabled = backend_ipl_mirrorLeftRight_isEnabled();
    ui.m_checkBoxMirrorLeftRight->blockSignals(true);
    if (enabled)
    {
        ui.m_checkBoxMirrorLeftRight->setCheckState(Qt::Checked);
    }
    else
    {
        ui.m_checkBoxMirrorLeftRight->setCheckState(Qt::Unchecked);
    }
    ui.m_checkBoxMirrorLeftRight->blockSignals(false);

    enabled = backend_ipl_mirrorUpDown_isEnabled();
    ui.m_checkBoxMirrorUpDown->blockSignals(true);
    if (enabled)
    {
        ui.m_checkBoxMirrorUpDown->setCheckState(Qt::Checked);
    }
    else
    {
        ui.m_checkBoxMirrorUpDown->setCheckState(Qt::Unchecked);
    }
    ui.m_checkBoxMirrorUpDown->blockSignals(false);
}

void CCDSetUserface::UpdateHotpixel()
{
    auto enabled = backend_ipl_hotpixelCorrection_isEnabled();
    ui.m_checkBoxHotpixelEnable->blockSignals(true);
    if (enabled)
    {
        ui.m_checkBoxHotpixelEnable->setCheckState(Qt::Checked);
    }
    else
    {
        ui.m_checkBoxHotpixelEnable->setCheckState(Qt::Unchecked);
    }
    ui.m_checkBoxHotpixelEnable->blockSignals(false);

    int value = backend_ipl_hotpixelCorrection_sensitivity_get();
    ui.m_spinBoxHotpixelSensitivity->blockSignals(true);
    ui.m_spinBoxHotpixelSensitivity->setValue(value);
    ui.m_spinBoxHotpixelSensitivity->blockSignals(false);
}


void CCDSetUserface::OnComboExposureMode(QString text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_exposureMode_set(0);
        emit exposureAutoModeChanged(false);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_exposureMode_set(1);
        emit exposureAutoModeChanged(true);

        // start a timer that checks if the exposure auto algorithm finished 
        // and sends a signal to update the exposure time regularly
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_exposureMode_set(2);
        emit exposureAutoModeChanged(true);

        // start a timer that sends a signal to update the exposure time regularly
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void CCDSetUserface::OnComboGainMode(QString text)
{
    if (text == "Off")
    {
        backend_ipl_brightness_gainMode_set(0);
    }
    else if (text == "Once")
    {
        backend_ipl_brightness_gainMode_set(1);

        // start a timer that checks if the gain auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_brightness_gainMode_set(2);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void CCDSetUserface::OnComboBrightnessRoiMode(QString text)
{
    if (text == "Full Image")
    {
        backend_ipl_brightness_roiMode_set(0);
    }
    else if (text == "Manual")
    {
        backend_ipl_brightness_roiMode_set(1);
    }
    UpdateBrightnessRoi();
}

void CCDSetUserface::OnSliderBrightnessRoi(int value)
{
    auto roi = backend_ipl_brightness_roi_get();
    if (sender() == ui.m_sliderBrightnessRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == ui.m_sliderBrightnessRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == ui.m_sliderBrightnessRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == ui.m_sliderBrightnessRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_brightness_roi_set(roi);
    UpdateBrightnessRoi();
}

void CCDSetUserface::OnEditBrightnessRoi()
{
    QString text = static_cast<QLineEdit*>(sender())->text();
    auto roi = backend_ipl_brightness_roi_get();
    auto value = text.toInt();
    if (sender() == ui.m_editBrightnessRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == ui.m_editBrightnessRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == ui.m_editBrightnessRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == ui.m_editBrightnessRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_brightness_roi_set(roi);
    UpdateBrightnessRoi();
}

void CCDSetUserface::OnSliderTarget(int value)
{
    backend_ipl_brightness_target_set(value);
    UpdateBrightnessOptions();
}

void CCDSetUserface::OnEditTarget()
{
    QString text = ui.m_editTarget->text();
    auto value = text.toInt();
    backend_ipl_brightness_target_set(value);
    UpdateBrightnessOptions();
}

void CCDSetUserface::OnSliderTargetPercentile(int value)
{
    double val = static_cast<double>(value) * m_targetPercentileInc + m_targetPercentileMin;
    if (val > m_targetPercentileMax)
    {
        val = m_targetPercentileMax;
    }
    backend_ipl_brightness_targetPercentile_set(val);
    UpdateBrightnessOptions();
}

void CCDSetUserface::OnEditTargetPercentile()
{
    auto value = ui.m_editTargetPercentile->text().toDouble();
    backend_ipl_brightness_targetPercentile_set(value);
    UpdateBrightnessOptions();
}

void CCDSetUserface::OnSliderTargetTolerance(int value)
{
    backend_ipl_brightness_targetTolerance_set(value);
    UpdateBrightnessOptions();
}

void CCDSetUserface::OnEditTargetTolerance()
{
    QString text = ui.m_editTargetTolerance->text();
    auto value = text.toInt();
    backend_ipl_brightness_targetTolerance_set(value);
    UpdateBrightnessRoi();
}

void CCDSetUserface::CheckForChangedValues()
{
    auto mode = backend_ipl_brightness_exposureMode_get();
    bool keepRunning = false;
    if (mode == 0)
    {
        if (mode != ui.m_comboExposureMode->currentIndex())
        {
            ui.m_comboExposureMode->setCurrentIndex(mode);
            emit exposureAutoModeChanged(false);
            emit updateExposureTime();
        }
    }
    else
    {
        keepRunning = true;
        emit updateExposureTime();
    }

    mode = backend_ipl_brightness_gainMode_get();
    if (mode == 0)
    {
        if (mode != ui.m_comboGainMode->currentIndex())
        {
            ui.m_comboGainMode->setCurrentIndex(mode);
        }
    }
    else
    {
        keepRunning = true;
    }

    mode = backend_ipl_whiteBalance_mode_get();
    if (mode == 0)
    {
        if (mode != ui.m_comboWhiteBalanceMode->currentIndex())
        {
            ui.m_comboWhiteBalanceMode->setCurrentIndex(mode);
            UpdateGain();
        }
    }
    else
    {
        UpdateGain();
        keepRunning = true;
    }

    auto count = backend_ipl_hotpixelCorrection_list_getCount();
    if (count != 0)
    {
        ui.m_labelHotpixelCountValue->setText(QString::number(count));
    }
    else if (ui.m_checkBoxHotpixelEnable->isChecked())
    {
        keepRunning = true;
    }

    if (!keepRunning)
    {
        m_timer->stop();
    }
}

void CCDSetUserface::OnComboWhiteBalanceMode(QString text)
{
    if (text == "Off")
    {
        backend_ipl_whiteBalance_mode_set(0);
    }
    else if (text == "Once")
    {
        backend_ipl_whiteBalance_mode_set(1);

        // start a timer that checks if the white balance auto algorithm finished
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (text == "Continuous")
    {
        backend_ipl_whiteBalance_mode_set(2);

        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
}

void CCDSetUserface::OnComboWhiteBalanceRoiMode(QString text)
{
    if (text == "Full Image")
    {
        backend_ipl_whiteBalance_roiMode_set(0);
    }
    else if (text == "Manual")
    {
        backend_ipl_whiteBalance_roiMode_set(1);
    }
    UpdateWhiteBalanceRoi();
}

void CCDSetUserface::OnSliderWhiteBalanceRoi(int value)
{
    auto roi = backend_ipl_whiteBalance_roi_get();
    if (sender() == ui.m_sliderWhiteBalanceRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == ui.m_sliderWhiteBalanceRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == ui.m_sliderWhiteBalanceRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == ui.m_sliderWhiteBalanceRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_whiteBalance_roi_set(roi);
    UpdateWhiteBalanceRoi();
}

void CCDSetUserface::OnEditWhiteBalanceRoi()
{
    QString text = static_cast<QLineEdit*>(sender())->text();
    auto roi = backend_ipl_whiteBalance_roi_get();
    auto value = text.toInt();
    if (sender() == ui.m_editWhiteBalanceRoiOffsetX)
    {
        roi.offset.x = value;
    }
    else if (sender() == ui.m_editWhiteBalanceRoiOffsetY)
    {
        roi.offset.y = value;
    }
    else if (sender() == ui.m_editWhiteBalanceRoiWidth)
    {
        roi.size.width = value;
    }
    else if (sender() == ui.m_editWhiteBalanceRoiHeight)
    {
        roi.size.height = value;
    }
    backend_ipl_whiteBalance_roi_set(roi);
    UpdateWhiteBalanceRoi();
}

void CCDSetUserface::OnSliderGainMaster(int value)
{
    double val = static_cast<double>(value) * m_gainMasterInc + m_gainMasterMin;
    if (val > m_gainMasterMax)
    {
        val = m_gainMasterMax;
    }
    backend_ipl_gainMaster_set(val);
    UpdateGain();
}

void CCDSetUserface::OnEditGainMaster()
{
    auto value = ui.m_editGainMaster->text().toDouble();
    backend_ipl_gainMaster_set(value);
    UpdateGain();
}

void CCDSetUserface::OnSliderGainRed(int value)
{
    double val = static_cast<double>(value) * m_gainRedInc + m_gainRedMin;
    if (val > m_gainRedMax)
    {
        val = m_gainRedMax;
    }
    backend_ipl_gainRed_set(val);
    UpdateGain();
}

void CCDSetUserface::OnEditGainRed()
{
    auto value = ui.m_editGainRed->text().toDouble();
    backend_ipl_gainRed_set(value);
    UpdateGain();
}

void CCDSetUserface::OnSliderGainGreen(int value)
{
    double val = static_cast<double>(value) * m_gainGreenInc + m_gainGreenMin;
    if (val > m_gainGreenMax)
    {
        val = m_gainGreenMax;
    }
    backend_ipl_gainGreen_set(val);
    UpdateGain();
}

void CCDSetUserface::OnEditGainGreen()
{
    auto value = ui.m_editGainGreen->text().toDouble();
    backend_ipl_gainGreen_set(value);
    UpdateGain();
}

void CCDSetUserface::OnSliderGainBlue(int value)
{
    double val = static_cast<double>(value) * m_gainBlueInc + m_gainBlueMin;
    if (val > m_gainBlueMax)
    {
        val = m_gainBlueMax;
    }
    backend_ipl_gainBlue_set(val);
    UpdateGain();
}

void CCDSetUserface::OnEditGainBlue()
{
    auto value = ui.m_editGainBlue->text().toDouble();
    backend_ipl_gainBlue_set(value);
    UpdateGain();
}

void CCDSetUserface::OnSliderGamma(int value)
{
    double val = static_cast<double>(value) * m_gammaInc + m_gammaMin;
    if (val > m_gammaMax)
    {
        val = m_gammaMax;
    }
    backend_ipl_gamma_set(val);
    UpdateGamma();
}

void CCDSetUserface::OnEditGamma()
{
    auto value = ui.m_editGamma->text().toDouble();
    backend_ipl_gamma_set(value);
    UpdateGamma();
}

void CCDSetUserface::OnColorCorrectionEnable(int state)
{
    if (state == Qt::Checked)
    {
        backend_ipl_colorCorrection_enable(true);
    }
    else if (state == Qt::Unchecked)
    {
        backend_ipl_colorCorrection_enable(false);
    }
    UpdateColorCorrection();
}


void CCDSetUserface::OnEditCcm()
{
    QString text = static_cast<QLineEdit*>(sender())->text();
    auto value = text.toDouble();
    auto ccm = backend_ipl_colorCorrectionMatrix_get();

    if (sender() == ui.m_editCcm00)
    {
        ccm.elementArray[0][0] = value;
    }
    else if (sender() == ui.m_editCcm01)
    {
        ccm.elementArray[0][1] = value;
    }
    else if (sender() == ui.m_editCcm02)
    {
        ccm.elementArray[0][2] = value;
    }
    else if (sender() == ui.m_editCcm10)
    {
        ccm.elementArray[1][0] = value;
    }
    else if (sender() == ui.m_editCcm11)
    {
        ccm.elementArray[1][1] = value;
    }
    else if (sender() == ui.m_editCcm12)
    {
        ccm.elementArray[1][2] = value;
    }
    else if (sender() == ui.m_editCcm20)
    {
        ccm.elementArray[2][0] = value;
    }
    else if (sender() == ui.m_editCcm21)
    {
        ccm.elementArray[2][1] = value;
    }
    else if (sender() == ui.m_editCcm22)
    {
        ccm.elementArray[2][2] = value;
    }

    backend_ipl_colorCorrectionMatrix_set(ccm);
    UpdateColorCorrection();
}

void CCDSetUserface::OnButtonCcmDefault()
{
    backend_ipl_colorCorrectionMatrix_setDefault();
    UpdateColorCorrection();
}

void CCDSetUserface::OnButtonCcmIdentity()
{
    backend_ipl_colorCorrectionMatrix_setIdentity();
    UpdateColorCorrection();
}

void CCDSetUserface::OnCheckBoxMirrorLeftRight(int state)
{
    int status = 0;
    if (state == Qt::Checked)
    {
        status = backend_ipl_mirrorLeftRight_enable(true);
    }
    else if (state == Qt::Unchecked)
    {
        status = backend_ipl_mirrorLeftRight_enable(false);
    }

    UpdateTransformations();
}

void CCDSetUserface::OnCheckBoxMirrorUpDown(int state)
{
    int status = 0;
    if (state == Qt::Checked)
    {
        status = backend_ipl_mirrorUpDown_enable(true);
    }
    else if (state == Qt::Unchecked)
    {
        status = backend_ipl_mirrorUpDown_enable(false);
    }

    UpdateTransformations();
}

void CCDSetUserface::OnHotpixelCorrectionEnable(int state)
{
    int status = 0;
    if (state == Qt::Checked)
    {
        status = backend_ipl_hotpixelCorrection_enable(true);
        ui.m_labelHotpixelCountValue->setText("");
        if (!m_timer->isActive())
        {
            m_timer->start(500);
        }
    }
    else if (state == Qt::Unchecked)
    {
        status = backend_ipl_hotpixelCorrection_enable(false);
        ui.m_labelHotpixelCountValue->setText("");
    }

    UpdateHotpixel();
}

void CCDSetUserface::OnSpinBoxHotpixelSensitivity(int value)
{
    int status = backend_ipl_hotpixelCorrection_sensitivity_set(value);

    ui.m_labelHotpixelCountValue->setText("");
    if (!m_timer->isActive())
    {
        m_timer->start(500);
    }

    UpdateHotpixel();
}

void CCDSetUserface::OnButtonHotpixelResetList()
{
    int status = backend_ipl_hotpixelCorrection_resetList();

    ui.m_labelHotpixelCountValue->setText("");
    if (!m_timer->isActive())
    {
        m_timer->start(500);
    }
}

void CCDSetUserface::OnExposureAutoModeChanged(bool active)
{
    m_exposureAutoActive = active;
    UpdateExposureTimeControl();
    ui.m_sliderExposureTime->setEnabled(!active);
    ui.m_editExposureTime->setEnabled(!active);
}
