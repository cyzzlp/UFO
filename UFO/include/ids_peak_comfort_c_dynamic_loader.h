/*!
 * \file    ids_peak_comfort_c_dynamic_loader.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019, IDS Imaging Development Systems GmbH. All rights reserved.
 */
#pragma once

#include "ids_peak_comfort_c.h"
#include <string>
#include <cstdint>

#ifdef __linux__
    #include <dlfcn.h>
#else
    #include <vector>
    #include <windows.h>
    #include <tchar.h>
#endif
 
#include <stdexcept>

#undef PEAK_EXPORT
#define PEAK_EXPORT
#undef PEAK_CALLCONV
#define PEAK_CALLCONV


namespace peak_comfortC
{
namespace dynamic
{

typedef PEAK_API_STATUS (*dyn_peak_Library_Init)();
typedef PEAK_API_STATUS (*dyn_peak_Library_Exit)();
typedef PEAK_API_STATUS (*dyn_peak_Library_GetVersion)(uint32_t * majorVersion, uint32_t * minorVersion, uint32_t * subminorVersion, uint32_t * patchVersion);
typedef PEAK_API_STATUS (*dyn_peak_Library_GetLastError)(peak_status * lastErrorCode, char * lastErrorMessage, size_t * lastErrorMessageSize);
typedef PEAK_API_STATUS (*dyn_peak_CameraList_Update)(size_t * cameraCount);
typedef PEAK_API_STATUS (*dyn_peak_CameraList_Get)(peak_camera_descriptor * cameraList, size_t * cameraCount);
typedef PEAK_API_CAMERA_ID (*dyn_peak_Camera_ID_FromHandle)(peak_camera_handle hCam);
typedef PEAK_API_CAMERA_ID (*dyn_peak_Camera_ID_FromSerialNumber)(const char * serialNumber);
typedef PEAK_API_CAMERA_ID (*dyn_peak_Camera_ID_FromMAC)(peak_mac_address macAddress);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Camera_GetAccessStatus)(peak_camera_id cameraID);
typedef PEAK_API_STATUS (*dyn_peak_Camera_GetDescriptor)(peak_camera_id cameraID, peak_camera_descriptor * cameraDescriptor);
typedef PEAK_API_STATUS (*dyn_peak_Camera_Open)(peak_camera_id cameraID, peak_camera_handle * hCam);
typedef PEAK_API_STATUS (*dyn_peak_Camera_OpenFirstAvailable)(peak_camera_handle * hCam);
typedef PEAK_API_STATUS (*dyn_peak_Camera_Close)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Camera_ResetToDefaultSettings)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_EthernetConfig_GetAccessStatus)(peak_camera_id cameraID);
typedef PEAK_API_STATUS (*dyn_peak_EthernetConfig_GetInfo)(peak_camera_id cameraID, peak_ethernet_info * ethernetInfo);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_EthernetConfig_DHCP_GetAccessStatus)(peak_camera_id cameraID);
typedef PEAK_API_STATUS (*dyn_peak_EthernetConfig_DHCP_Enable)(peak_camera_id cameraID, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_EthernetConfig_DHCP_IsEnabled)(peak_camera_id cameraID);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_EthernetConfig_PersistentIP_GetAccessStatus)(peak_camera_id cameraID);
typedef PEAK_API_STATUS (*dyn_peak_EthernetConfig_PersistentIP_Set)(peak_camera_id cameraID, peak_ip_config persistentIP);
typedef PEAK_API_STATUS (*dyn_peak_EthernetConfig_PersistentIP_Get)(peak_camera_id cameraID, peak_ip_config * persistentIP);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Start)(peak_camera_handle hCam, uint32_t numberOfFrames);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Stop)(peak_camera_handle hCam);
typedef PEAK_API_BOOL (*dyn_peak_Acquisition_IsStarted)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_WaitForFrame)(peak_camera_handle hCam, uint32_t timeout_ms, peak_frame_handle * hFrame);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_GetInfo)(peak_camera_handle hCam, peak_acquisition_info * acquisitionInfo);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Buffer_GetRequiredSize)(peak_camera_handle hCam, size_t * requiredBufferSize);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Buffer_GetRequiredCount)(peak_camera_handle hCam, size_t * requiredBufferCount);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Buffer_Announce)(peak_camera_handle hCam, uint8_t * memoryAddress, size_t memorySize, void * userContext);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Buffer_Revoke)(peak_camera_handle hCam, uint8_t * memoryAddress);
typedef PEAK_API_STATUS (*dyn_peak_Acquisition_Buffer_RevokeAll)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_PixelFormat_GetInfo)(peak_pixel_format pixelFormat, peak_pixel_format_info * pixelFormatInfo);
typedef PEAK_API_STATUS (*dyn_peak_Frame_Release)(peak_camera_handle hCam, peak_frame_handle hFrame);
typedef PEAK_API_STATUS (*dyn_peak_Frame_GetInfo)(peak_frame_handle hFrame, peak_frame_info * frameInfo);
typedef PEAK_API_STATUS (*dyn_peak_Frame_Type_Get)(peak_frame_handle hFrame, peak_frame_type * frameType);
typedef PEAK_API_STATUS (*dyn_peak_Frame_Buffer_Get)(peak_frame_handle hFrame, peak_buffer * buffer);
typedef PEAK_API_STATUS (*dyn_peak_Frame_ID_Get)(peak_frame_handle hFrame, uint64_t * frameID);
typedef PEAK_API_STATUS (*dyn_peak_Frame_Timestamp_Get)(peak_frame_handle hFrame, uint64_t * timestamp_ns);
typedef PEAK_API_STATUS (*dyn_peak_Frame_ROI_Get)(peak_frame_handle hFrame, peak_roi * roi);
typedef PEAK_API_STATUS (*dyn_peak_Frame_PixelFormat_Get)(peak_frame_handle hFrame, peak_pixel_format * pixelFormat);
typedef PEAK_API_BOOL (*dyn_peak_Frame_IsComplete)(peak_frame_handle hFrame);
typedef PEAK_API_STATUS (*dyn_peak_Frame_BytesExpected_Get)(peak_frame_handle hFrame, size_t * bytesExpected);
typedef PEAK_API_STATUS (*dyn_peak_Frame_BytesWritten_Get)(peak_frame_handle hFrame, size_t * bytesWritten);
typedef PEAK_API_STATUS (*dyn_peak_Frame_ProcessingTime_Get)(peak_frame_handle hFrame, uint32_t * processingTime_ms);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_CameraSettings_ParameterSet_GetAccessStatus)(peak_camera_handle hCam, peak_parameter_set parameterSet);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_ParameterSet_GetList)(peak_camera_handle hCam, peak_parameter_set * parameterSetList, size_t * parameterSetCount);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_ParameterSet_Store)(peak_camera_handle hCam, peak_parameter_set parameterSet);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_ParameterSet_Apply)(peak_camera_handle hCam, peak_parameter_set parameterSet);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_ParameterSet_Startup_Set)(peak_camera_handle hCam, peak_parameter_set parameterSet);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_ParameterSet_Startup_Get)(peak_camera_handle hCam, peak_parameter_set * parameterSet);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_CameraSettings_DiskFile_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_DiskFile_Store)(peak_camera_handle hCam, const char * file);
typedef PEAK_API_STATUS (*dyn_peak_CameraSettings_DiskFile_Apply)(peak_camera_handle hCam, const char * file);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_FrameRate_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_FrameRate_GetRange)(peak_camera_handle hCam, double * minFrameRate_fps, double * maxFrameRate_fps, double * incFrameRate_fps);
typedef PEAK_API_STATUS (*dyn_peak_FrameRate_Set)(peak_camera_handle hCam, double frameRate_fps);
typedef PEAK_API_STATUS (*dyn_peak_FrameRate_Get)(peak_camera_handle hCam, double * frameRate_fps);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_ExposureTime_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_ExposureTime_GetRange)(peak_camera_handle hCam, double * minExposureTime_us, double * maxExposureTime_us, double * incExposureTime_us);
typedef PEAK_API_STATUS (*dyn_peak_ExposureTime_Set)(peak_camera_handle hCam, double exposureTime_us);
typedef PEAK_API_STATUS (*dyn_peak_ExposureTime_Get)(peak_camera_handle hCam, double * exposureTime_us);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_PixelClock_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_BOOL (*dyn_peak_PixelClock_HasRange)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_PixelClock_GetRange)(peak_camera_handle hCam, double * minPixelClock_MHz, double * maxPixelClock_MHz, double * incPixelClock_MHz);
typedef PEAK_API_STATUS (*dyn_peak_PixelClock_GetList)(peak_camera_handle hCam, double * pixelClockList, size_t * pixelClockCount);
typedef PEAK_API_STATUS (*dyn_peak_PixelClock_Set)(peak_camera_handle hCam, double pixelClock_MHz);
typedef PEAK_API_STATUS (*dyn_peak_PixelClock_Get)(peak_camera_handle hCam, double * pixelClock_MHz);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_IOChannel_GetAccessStatus)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_STATUS (*dyn_peak_IOChannel_GetList)(peak_camera_handle hCam, peak_io_channel * ioChannelList, size_t * ioChannelCount);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_IOChannel_Level_GetAccessStatus)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_BOOL (*dyn_peak_IOChannel_Level_IsHigh)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_IOChannel_Inverter_GetAccessStatus)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_STATUS (*dyn_peak_IOChannel_Inverter_Enable)(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_IOChannel_Inverter_IsEnabled)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_IOChannel_NoiseFilter_GetAccessStatus)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_STATUS (*dyn_peak_IOChannel_NoiseFilter_Enable)(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_IOChannel_NoiseFilter_IsEnabled)(peak_camera_handle hCam, peak_io_channel ioChannel);
typedef PEAK_API_STATUS (*dyn_peak_IOChannel_NoiseFilter_Duration_GetRange)(peak_camera_handle hCam, peak_io_channel ioChannel, double * minNoiseFilterDuration_us, double * maxNoiseFilterDuration_us, double * incNoiseFilterDuration_us);
typedef PEAK_API_STATUS (*dyn_peak_IOChannel_NoiseFilter_Duration_Set)(peak_camera_handle hCam, peak_io_channel ioChannel, double noiseFilterDuration_us);
typedef PEAK_API_STATUS (*dyn_peak_IOChannel_NoiseFilter_Duration_Get)(peak_camera_handle hCam, peak_io_channel ioChannel, double * noiseFilterDuration_us);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Trigger_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_Trigger_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_BOOL (*dyn_peak_Trigger_IsExecutable)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Execute)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Trigger_Mode_GetAccessStatus)(peak_camera_handle hCam, peak_trigger_mode triggerMode);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Mode_Set)(peak_camera_handle hCam, peak_trigger_mode triggerMode);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Mode_Get)(peak_camera_handle hCam, peak_trigger_mode * triggerMode);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Trigger_Edge_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Edge_GetList)(peak_camera_handle hCam, peak_trigger_edge * triggerEdgeList, size_t * triggerEdgeCount);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Edge_Set)(peak_camera_handle hCam, peak_trigger_edge triggerEdge);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Edge_Get)(peak_camera_handle hCam, peak_trigger_edge * triggerEdge);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Trigger_Delay_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Delay_GetRange)(peak_camera_handle hCam, double * minTriggerDelay_us, double * maxTriggerDelay_us, double * incTriggerDelay_us);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Delay_Set)(peak_camera_handle hCam, double triggerDelay_us);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Delay_Get)(peak_camera_handle hCam, double * triggerDelay_us);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Trigger_Divider_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Divider_GetRange)(peak_camera_handle hCam, uint32_t * minTriggerDivider, uint32_t * maxTriggerDivider, uint32_t * incTriggerDivider);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Divider_Set)(peak_camera_handle hCam, uint32_t triggerDivider);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Divider_Get)(peak_camera_handle hCam, uint32_t * triggerDivider);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Trigger_Burst_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Burst_GetRange)(peak_camera_handle hCam, uint32_t * minTriggerBurst, uint32_t * maxTriggerBurst, uint32_t * incTriggerBurst);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Burst_Set)(peak_camera_handle hCam, uint32_t triggerBurst);
typedef PEAK_API_STATUS (*dyn_peak_Trigger_Burst_Get)(peak_camera_handle hCam, uint32_t * triggerBurst);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Flash_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Flash_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_Flash_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Flash_Mode_GetAccessStatus)(peak_camera_handle hCam, peak_flash_mode flashMode);
typedef PEAK_API_STATUS (*dyn_peak_Flash_Mode_Set)(peak_camera_handle hCam, peak_flash_mode flashMode);
typedef PEAK_API_STATUS (*dyn_peak_Flash_Mode_Get)(peak_camera_handle hCam, peak_flash_mode * flashMode);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Flash_StartDelay_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Flash_StartDelay_GetRange)(peak_camera_handle hCam, double * minFlashStartDelay_us, double * maxFlashStartDelay_us, double * incFlashStartDelay_us);
typedef PEAK_API_STATUS (*dyn_peak_Flash_StartDelay_Set)(peak_camera_handle hCam, double flashStartDelay_us);
typedef PEAK_API_STATUS (*dyn_peak_Flash_StartDelay_Get)(peak_camera_handle hCam, double * flashStartDelay_us);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Flash_EndDelay_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Flash_EndDelay_GetRange)(peak_camera_handle hCam, double * minFlashEndDelay_us, double * maxFlashEndDelay_us, double * incFlashEndDelay_us);
typedef PEAK_API_STATUS (*dyn_peak_Flash_EndDelay_Set)(peak_camera_handle hCam, double flashEndDelay_us);
typedef PEAK_API_STATUS (*dyn_peak_Flash_EndDelay_Get)(peak_camera_handle hCam, double * flashEndDelay_us);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Flash_Duration_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Flash_Duration_GetRange)(peak_camera_handle hCam, double * minFlashDuration_us, double * maxFlashDuration_us, double * incFlashDuration_us);
typedef PEAK_API_STATUS (*dyn_peak_Flash_Duration_Set)(peak_camera_handle hCam, double flashDuration_us);
typedef PEAK_API_STATUS (*dyn_peak_Flash_Duration_Get)(peak_camera_handle hCam, double * flashDuration_us);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_PixelFormat_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_PixelFormat_GetList)(peak_camera_handle hCam, peak_pixel_format * pixelFormatList, size_t * pixelFormatCount);
typedef PEAK_API_STATUS (*dyn_peak_PixelFormat_Set)(peak_camera_handle hCam, peak_pixel_format pixelFormat);
typedef PEAK_API_STATUS (*dyn_peak_PixelFormat_Get)(peak_camera_handle hCam, peak_pixel_format * pixelFormat);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Gain_GetAccessStatus)(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel);
typedef PEAK_API_STATUS (*dyn_peak_Gain_GetChannelList)(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel * gainChannelList, size_t * gainChannelCount);
typedef PEAK_API_STATUS (*dyn_peak_Gain_GetRange)(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double * minGain, double * maxGain, double * incGain);
typedef PEAK_API_STATUS (*dyn_peak_Gain_Set)(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double gain);
typedef PEAK_API_STATUS (*dyn_peak_Gain_Get)(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double * gain);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Gamma_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Gamma_GetRange)(peak_camera_handle hCam, double * minGamma, double * maxGamma, double * incGamma);
typedef PEAK_API_STATUS (*dyn_peak_Gamma_Set)(peak_camera_handle hCam, double gamma);
typedef PEAK_API_STATUS (*dyn_peak_Gamma_Get)(peak_camera_handle hCam, double * gamma);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_ColorCorrection_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Mode_GetList)(peak_camera_handle hCam, peak_color_correction_mode * colorCorrectionModeList, size_t * colorCorrectionModeCount);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Mode_Set)(peak_camera_handle hCam, peak_color_correction_mode colorCorrectionMode);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Mode_Get)(peak_camera_handle hCam, peak_color_correction_mode * colorCorrectionMode);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_ColorCorrection_Matrix_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Matrix_GetRange)(peak_camera_handle hCam, double * minMatrixElementValue, double * maxMatrixElementValue, double * incMatrixElementValue);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Matrix_Set)(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Matrix_Get)(peak_camera_handle hCam, peak_matrix * colorCorrectionMatrix);
typedef PEAK_API_STATUS (*dyn_peak_ColorCorrection_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_ColorCorrection_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_AutoBrightness_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Target_GetRange)(peak_camera_handle hCam, uint32_t * minAutoBrightnessTarget, uint32_t * maxAutoBrightnessTarget, uint32_t * incAutoBrightnessTarget);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Target_Set)(peak_camera_handle hCam, uint32_t autoBrightnessTarget);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Target_Get)(peak_camera_handle hCam, uint32_t * autoBrightnessTarget);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_TargetTolerance_GetRange)(peak_camera_handle hCam, uint32_t * minAutoBrightnessTargetTolerance, uint32_t * maxAutoBrightnessTargetTolerance, uint32_t * incAutoBrightnessTargetTolerance);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_TargetTolerance_Set)(peak_camera_handle hCam, uint32_t autoBrightnessTargetTolerance);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_TargetTolerance_Get)(peak_camera_handle hCam, uint32_t * autoBrightnessTargetTolerance);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_TargetPercentile_GetRange)(peak_camera_handle hCam, double * minAutoBrightnessTargetPercentile, double * maxAutoBrightnessTargetPercentile, double * incAutoBrightnessTargetPercentile);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_TargetPercentile_Set)(peak_camera_handle hCam, double autoBrightnessTargetPercentile);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_TargetPercentile_Get)(peak_camera_handle hCam, double * autoBrightnessTargetPercentile);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_ROI_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_roi_mode autoBrightnessROIMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_ROI_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoBrightnessROIMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_ROI_Offset_GetRange)(peak_camera_handle hCam, peak_position * minAutoBrightnessROIOffset, peak_position * maxAutoBrightnessROIOffset, peak_position * incAutoBrightnessROIOffset);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_ROI_Size_GetRange)(peak_camera_handle hCam, peak_size * minAutoBrightnessROISize, peak_size * maxAutoBrightnessROISize, peak_size * incAutoBrightnessROISize);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_ROI_Set)(peak_camera_handle hCam, peak_roi autoBrightnessROI);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_ROI_Get)(peak_camera_handle hCam, peak_roi * autoBrightnessROI);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_AutoBrightness_Exposure_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Exposure_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Exposure_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_mode * autoExposureMode);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_AutoBrightness_Gain_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Gain_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoBrightness_Gain_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_mode * autoGainMode);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_AutoWhiteBalance_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_ROI_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_roi_mode autoWhiteBalanceROIMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_ROI_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoWhiteBalanceROIMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_ROI_Offset_GetRange)(peak_camera_handle hCam, peak_position * minAutoWhiteBalanceROIOffset, peak_position * maxAutoWhiteBalanceROIOffset, peak_position * incAutoWhiteBalanceROIOffset);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_ROI_Size_GetRange)(peak_camera_handle hCam, peak_size * minAutoWhiteBalanceROISize, peak_size * maxAutoWhiteBalanceROISize, peak_size * incAutoWhiteBalanceROISize);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_ROI_Set)(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_ROI_Get)(peak_camera_handle hCam, peak_roi * autoWhiteBalanceROI);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode);
typedef PEAK_API_STATUS (*dyn_peak_AutoWhiteBalance_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_mode * autoWhiteBalanceMode);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_ROI_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_ROI_Offset_GetRange)(peak_camera_handle hCam, peak_position * minROIOffset, peak_position * maxROIOffset, peak_position * incROIOffset);
typedef PEAK_API_STATUS (*dyn_peak_ROI_Size_GetRange)(peak_camera_handle hCam, peak_size * minROISize, peak_size * maxROISize, peak_size * incROISize);
typedef PEAK_API_STATUS (*dyn_peak_ROI_Set)(peak_camera_handle hCam, peak_roi roi);
typedef PEAK_API_STATUS (*dyn_peak_ROI_Get)(peak_camera_handle hCam, peak_roi * roi);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Binning_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Binning_FactorX_GetList)(peak_camera_handle hCam, uint32_t * binningFactorXList, size_t * binningFactorXCount);
typedef PEAK_API_STATUS (*dyn_peak_Binning_FactorY_GetList)(peak_camera_handle hCam, uint32_t * binningFactorYList, size_t * binningFactorYCount);
typedef PEAK_API_STATUS (*dyn_peak_Binning_Set)(peak_camera_handle hCam, uint32_t binningFactorX, uint32_t binningFactorY);
typedef PEAK_API_STATUS (*dyn_peak_Binning_Get)(peak_camera_handle hCam, uint32_t * binningFactorX, uint32_t * binningFactorY);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Decimation_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Decimation_FactorX_GetList)(peak_camera_handle hCam, uint32_t * decimationFactorXList, size_t * decimationFactorXCount);
typedef PEAK_API_STATUS (*dyn_peak_Decimation_FactorY_GetList)(peak_camera_handle hCam, uint32_t * decimationFactorYList, size_t * decimationFactorYCount);
typedef PEAK_API_STATUS (*dyn_peak_Decimation_Set)(peak_camera_handle hCam, uint32_t decimationFactorX, uint32_t decimationFactorY);
typedef PEAK_API_STATUS (*dyn_peak_Decimation_Get)(peak_camera_handle hCam, uint32_t * decimationFactorX, uint32_t * decimationFactorY);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Mirror_LeftRight_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Mirror_LeftRight_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_Mirror_LeftRight_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_Mirror_UpDown_GetAccessStatus)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_Mirror_UpDown_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_Mirror_UpDown_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_CameraMemory_Area_GetAccessStatus)(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea);
typedef PEAK_API_STATUS (*dyn_peak_CameraMemory_Area_GetList)(peak_camera_handle hCam, peak_camera_memory_area * cameraMemoryAreaList, size_t * cameraMemoryAreaCount);
typedef PEAK_API_STATUS (*dyn_peak_CameraMemory_Area_Size_Get)(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, size_t * cameraMemoryAreaSize);
typedef PEAK_API_STATUS (*dyn_peak_CameraMemory_Area_Data_Clear)(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea);
typedef PEAK_API_STATUS (*dyn_peak_CameraMemory_Area_Data_Write)(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, const uint8_t * data, size_t dataSize);
typedef PEAK_API_STATUS (*dyn_peak_CameraMemory_Area_Data_Read)(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, uint8_t * data, size_t dataSize);
typedef PEAK_API_STATUS (*dyn_peak_GFA_EnableWriteAccess)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_GFA_IsWriteAccessEnabled)(peak_camera_handle hCam);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_GFA_Feature_GetAccessStatus)(peak_camera_handle hCam, peak_gfa_module module, const char * featureName);
typedef PEAK_API_BOOL (*dyn_peak_GFA_Float_HasRange)(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Float_GetRange)(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * minFloatValue, double * maxFloatValue, double * incFloatValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Float_GetList)(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * floatList, size_t * floatCount);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Float_Set)(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double floatValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Float_Get)(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * floatValue);
typedef PEAK_API_BOOL (*dyn_peak_GFA_Integer_HasRange)(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Integer_GetRange)(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * minIntegerValue, int64_t * maxIntegerValue, int64_t * incIntegerValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Integer_GetList)(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * integerList, size_t * integerCount);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Integer_Set)(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t integerValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Integer_Get)(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * integerValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Boolean_Set)(peak_camera_handle hCam, peak_gfa_module module, const char * booleanFeatureName, peak_bool booleanValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Boolean_Get)(peak_camera_handle hCam, peak_gfa_module module, const char * booleanFeatureName, peak_bool * booleanValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_String_Set)(peak_camera_handle hCam, peak_gfa_module module, const char * stringFeatureName, const char * stringValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_String_Get)(peak_camera_handle hCam, peak_gfa_module module, const char * stringFeatureName, char * stringValue, size_t * stringValueSize);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Command_Execute)(peak_camera_handle hCam, peak_gfa_module module, const char * commandFeatureName);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Command_WaitForDone)(peak_camera_handle hCam, peak_gfa_module module, const char * commandFeatureName, uint32_t timeout_ms);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Enumeration_GetList)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, peak_gfa_enumeration_entry * enumerationEntryList, size_t * enumerationEntryCount);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_GFA_EnumerationEntry_GetAccessStatus)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const peak_gfa_enumeration_entry * enumerationEntry);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const char * enumerationEntrySymbolicValue);
typedef PEAK_API_ACCESS_STATUS (*dyn_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, int64_t enumerationEntryIntegerValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Enumeration_Set)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const peak_gfa_enumeration_entry * enumerationEntry);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Enumeration_SetBySymbolicValue)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const char * enumerationEntrySymbolicValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Enumeration_SetByIntegerValue)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, int64_t enumerationEntryIntegerValue);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Enumeration_Get)(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, peak_gfa_enumeration_entry * enumerationEntry);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Register_Set)(peak_camera_handle hCam, peak_gfa_module module, const char * registerFeatureName, const uint8_t * registerValue, size_t registerValueSize);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Register_Get)(peak_camera_handle hCam, peak_gfa_module module, const char * registerFeatureName, uint8_t * registerValue, size_t * registerValueSize);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Data_Write)(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, const uint8_t * data, size_t dataSize);
typedef PEAK_API_STATUS (*dyn_peak_GFA_Data_Read)(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, uint8_t * data, size_t dataSize);
typedef PEAK_API_STATUS (*dyn_peak_IPL_PixelFormat_GetList)(peak_camera_handle hCam, peak_pixel_format inputPixelFormat, peak_pixel_format * outputPixelFormatList, size_t * outputPixelFormatCount);
typedef PEAK_API_STATUS (*dyn_peak_IPL_PixelFormat_Set)(peak_camera_handle hCam, peak_pixel_format pixelFormat);
typedef PEAK_API_STATUS (*dyn_peak_IPL_PixelFormat_Get)(peak_camera_handle hCam, peak_pixel_format * pixelFormat);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Gain_GetRange)(peak_camera_handle hCam, peak_gain_channel gainChannel, double * minGain, double * maxGain, double * incGain);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Gain_Set)(peak_camera_handle hCam, peak_gain_channel gainChannel, double gain);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Gain_Get)(peak_camera_handle hCam, peak_gain_channel gainChannel, double * gain);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Gamma_GetRange)(peak_camera_handle hCam, double * minGamma, double * maxGamma, double * incGamma);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Gamma_Set)(peak_camera_handle hCam, double gamma);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Gamma_Get)(peak_camera_handle hCam, double * gamma);
typedef PEAK_API_STATUS (*dyn_peak_IPL_ColorCorrection_Matrix_Set)(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix);
typedef PEAK_API_STATUS (*dyn_peak_IPL_ColorCorrection_Matrix_Get)(peak_camera_handle hCam, peak_matrix * colorCorrectionMatrix);
typedef PEAK_API_STATUS (*dyn_peak_IPL_ColorCorrection_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_IPL_ColorCorrection_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Target_GetRange)(peak_camera_handle hCam, uint32_t * minAutoBrightnessTarget, uint32_t * maxAutoBrightnessTarget, uint32_t * incAutoBrightnessTarget);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Target_Set)(peak_camera_handle hCam, uint32_t autoBrightnessTarget);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Target_Get)(peak_camera_handle hCam, uint32_t * autoBrightnessTarget);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_TargetTolerance_GetRange)(peak_camera_handle hCam, uint32_t * minAutoBrightnessTargetTolerance, uint32_t * maxAutoBrightnessTargetTolerance, uint32_t * incAutoBrightnessTargetTolerance);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_TargetTolerance_Set)(peak_camera_handle hCam, uint32_t autoBrightnessTargetTolerance);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_TargetTolerance_Get)(peak_camera_handle hCam, uint32_t * autoBrightnessTargetTolerance);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_TargetPercentile_GetRange)(peak_camera_handle hCam, double * minAutoBrightnessTargetPercentile, double * maxAutoBrightnessTargetPercentile, double * incAutoBrightnessTargetPercentile);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_TargetPercentile_Set)(peak_camera_handle hCam, double autoBrightnessTargetPercentile);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_TargetPercentile_Get)(peak_camera_handle hCam, double * autoBrightnessTargetPercentile);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_ROI_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_roi_mode autoBrightnessROIMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_ROI_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoBrightnessROIMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_ROI_Offset_GetRange)(peak_camera_handle hCam, peak_position * minAutoBrightnessROIOffset, peak_position * maxAutoBrightnessROIOffset, peak_position * incAutoBrightnessROIOffset);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_ROI_Size_GetRange)(peak_camera_handle hCam, peak_size * minAutoBrightnessROISize, peak_size * maxAutoBrightnessROISize, peak_size * incAutoBrightnessROISize);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_ROI_Set)(peak_camera_handle hCam, peak_roi autoBrightnessROI);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_ROI_Get)(peak_camera_handle hCam, peak_roi * autoBrightnessROI);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Exposure_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Exposure_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_mode * autoExposureMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Gain_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoBrightness_Gain_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_mode * autoGainMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_ROI_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_roi_mode autoWhiteBalanceROIMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_ROI_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoWhiteBalanceROIMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange)(peak_camera_handle hCam, peak_position * minAutoWhiteBalanceROIOffset, peak_position * maxAutoWhiteBalanceROIOffset, peak_position * incAutoWhiteBalanceROIOffset);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange)(peak_camera_handle hCam, peak_size * minAutoWhiteBalanceROISize, peak_size * maxAutoWhiteBalanceROISize, peak_size * incAutoWhiteBalanceROISize);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_ROI_Set)(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_ROI_Get)(peak_camera_handle hCam, peak_roi * autoWhiteBalanceROI);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_Mode_Set)(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_AutoWhiteBalance_Mode_Get)(peak_camera_handle hCam, peak_auto_feature_mode * autoWhiteBalanceMode);
typedef PEAK_API_STATUS (*dyn_peak_IPL_HotpixelCorrection_Sensitivity_Set)(peak_camera_handle hCam, peak_hotpixel_correction_sensitivity hotpixelCorrectionSensitivity);
typedef PEAK_API_STATUS (*dyn_peak_IPL_HotpixelCorrection_Sensitivity_Get)(peak_camera_handle hCam, peak_hotpixel_correction_sensitivity * hotpixelCorrectionSensitivity);
typedef PEAK_API_STATUS (*dyn_peak_IPL_HotpixelCorrection_GetList)(peak_camera_handle hCam, peak_position * hotpixelList, size_t * hotpixelCount);
typedef PEAK_API_STATUS (*dyn_peak_IPL_HotpixelCorrection_SetList)(peak_camera_handle hCam, peak_position * hotpixelList, size_t hotpixelCount);
typedef PEAK_API_STATUS (*dyn_peak_IPL_HotpixelCorrection_ResetList)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_IPL_HotpixelCorrection_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_IPL_HotpixelCorrection_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Mirror_UpDown_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_IPL_Mirror_UpDown_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_IPL_Mirror_LeftRight_Enable)(peak_camera_handle hCam, peak_bool enabled);
typedef PEAK_API_BOOL (*dyn_peak_IPL_Mirror_LeftRight_IsEnabled)(peak_camera_handle hCam);
typedef PEAK_API_STATUS (*dyn_peak_IPL_ProcessFrame)(peak_camera_handle hCam, peak_frame_handle hFrame, peak_frame_handle * hResultFrame);
typedef PEAK_API_STATUS (*dyn_peak_IPL_ProcessFrameInplace)(peak_camera_handle hCam, peak_frame_handle hFrame);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Open)(peak_video_handle * hVideo, const char * fileName, peak_video_container container, peak_video_encoder encoder);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Close)(peak_video_handle hVideo);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_AddFrame)(peak_video_handle hVideo, peak_frame_handle hFrame);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Container_GetEncoderList)(peak_video_container container, peak_video_encoder * encoderList, size_t * encoderCount);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Encoder_GetPixelFormatList)(peak_video_encoder encoder, peak_pixel_format * pixelFormatList, size_t * pixelFormatCount);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Encoder_GetContainerList)(peak_video_encoder encoder, peak_video_container * containerList, size_t * containerCount);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_GetInfo)(peak_video_handle hVideo, peak_video_info * videoInfo);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Container_Option_Set)(peak_video_handle hVideo, peak_video_container_option containerOption, const void * value, size_t count);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Container_Option_Get)(peak_video_handle hVideo, peak_video_container_option containerOption, void * value, size_t count, size_t * outCount);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Encoder_Option_Set)(peak_video_handle hVideo, peak_video_encoder_option encoderOption, const void * value, size_t count);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_Encoder_Option_Get)(peak_video_handle hVideo, peak_video_encoder_option encoderOption, void * value, size_t count, size_t * outCount);
typedef PEAK_API_STATUS (*dyn_peak_VideoWriter_WaitUntilQueueEmpty)(peak_video_handle hVideo, int32_t timeout_ms);

                        
class DynamicLoader
{
private:
    DynamicLoader();
    
    static DynamicLoader& instance()
    {
        static DynamicLoader dynamicLoader{};
        return dynamicLoader;
    }
    bool loadLib(const char* file);
    void unload();
    bool setPointers(bool load);

public:
    ~DynamicLoader();
    
    static bool isLoaded();
    
    static PEAK_API_STATUS peak_Library_Init();
    static PEAK_API_STATUS peak_Library_Exit();
    static PEAK_API_STATUS peak_Library_GetVersion(uint32_t * majorVersion, uint32_t * minorVersion, uint32_t * subminorVersion, uint32_t * patchVersion);
    static PEAK_API_STATUS peak_Library_GetLastError(peak_status * lastErrorCode, char * lastErrorMessage, size_t * lastErrorMessageSize);
    static PEAK_API_STATUS peak_CameraList_Update(size_t * cameraCount);
    static PEAK_API_STATUS peak_CameraList_Get(peak_camera_descriptor * cameraList, size_t * cameraCount);
    static PEAK_API_CAMERA_ID peak_Camera_ID_FromHandle(peak_camera_handle hCam);
    static PEAK_API_CAMERA_ID peak_Camera_ID_FromSerialNumber(const char * serialNumber);
    static PEAK_API_CAMERA_ID peak_Camera_ID_FromMAC(peak_mac_address macAddress);
    static PEAK_API_ACCESS_STATUS peak_Camera_GetAccessStatus(peak_camera_id cameraID);
    static PEAK_API_STATUS peak_Camera_GetDescriptor(peak_camera_id cameraID, peak_camera_descriptor * cameraDescriptor);
    static PEAK_API_STATUS peak_Camera_Open(peak_camera_id cameraID, peak_camera_handle * hCam);
    static PEAK_API_STATUS peak_Camera_OpenFirstAvailable(peak_camera_handle * hCam);
    static PEAK_API_STATUS peak_Camera_Close(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Camera_ResetToDefaultSettings(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_EthernetConfig_GetAccessStatus(peak_camera_id cameraID);
    static PEAK_API_STATUS peak_EthernetConfig_GetInfo(peak_camera_id cameraID, peak_ethernet_info * ethernetInfo);
    static PEAK_API_ACCESS_STATUS peak_EthernetConfig_DHCP_GetAccessStatus(peak_camera_id cameraID);
    static PEAK_API_STATUS peak_EthernetConfig_DHCP_Enable(peak_camera_id cameraID, peak_bool enabled);
    static PEAK_API_BOOL peak_EthernetConfig_DHCP_IsEnabled(peak_camera_id cameraID);
    static PEAK_API_ACCESS_STATUS peak_EthernetConfig_PersistentIP_GetAccessStatus(peak_camera_id cameraID);
    static PEAK_API_STATUS peak_EthernetConfig_PersistentIP_Set(peak_camera_id cameraID, peak_ip_config persistentIP);
    static PEAK_API_STATUS peak_EthernetConfig_PersistentIP_Get(peak_camera_id cameraID, peak_ip_config * persistentIP);
    static PEAK_API_STATUS peak_Acquisition_Start(peak_camera_handle hCam, uint32_t numberOfFrames);
    static PEAK_API_STATUS peak_Acquisition_Stop(peak_camera_handle hCam);
    static PEAK_API_BOOL peak_Acquisition_IsStarted(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Acquisition_WaitForFrame(peak_camera_handle hCam, uint32_t timeout_ms, peak_frame_handle * hFrame);
    static PEAK_API_STATUS peak_Acquisition_GetInfo(peak_camera_handle hCam, peak_acquisition_info * acquisitionInfo);
    static PEAK_API_STATUS peak_Acquisition_Buffer_GetRequiredSize(peak_camera_handle hCam, size_t * requiredBufferSize);
    static PEAK_API_STATUS peak_Acquisition_Buffer_GetRequiredCount(peak_camera_handle hCam, size_t * requiredBufferCount);
    static PEAK_API_STATUS peak_Acquisition_Buffer_Announce(peak_camera_handle hCam, uint8_t * memoryAddress, size_t memorySize, void * userContext);
    static PEAK_API_STATUS peak_Acquisition_Buffer_Revoke(peak_camera_handle hCam, uint8_t * memoryAddress);
    static PEAK_API_STATUS peak_Acquisition_Buffer_RevokeAll(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_PixelFormat_GetInfo(peak_pixel_format pixelFormat, peak_pixel_format_info * pixelFormatInfo);
    static PEAK_API_STATUS peak_Frame_Release(peak_camera_handle hCam, peak_frame_handle hFrame);
    static PEAK_API_STATUS peak_Frame_GetInfo(peak_frame_handle hFrame, peak_frame_info * frameInfo);
    static PEAK_API_STATUS peak_Frame_Type_Get(peak_frame_handle hFrame, peak_frame_type * frameType);
    static PEAK_API_STATUS peak_Frame_Buffer_Get(peak_frame_handle hFrame, peak_buffer * buffer);
    static PEAK_API_STATUS peak_Frame_ID_Get(peak_frame_handle hFrame, uint64_t * frameID);
    static PEAK_API_STATUS peak_Frame_Timestamp_Get(peak_frame_handle hFrame, uint64_t * timestamp_ns);
    static PEAK_API_STATUS peak_Frame_ROI_Get(peak_frame_handle hFrame, peak_roi * roi);
    static PEAK_API_STATUS peak_Frame_PixelFormat_Get(peak_frame_handle hFrame, peak_pixel_format * pixelFormat);
    static PEAK_API_BOOL peak_Frame_IsComplete(peak_frame_handle hFrame);
    static PEAK_API_STATUS peak_Frame_BytesExpected_Get(peak_frame_handle hFrame, size_t * bytesExpected);
    static PEAK_API_STATUS peak_Frame_BytesWritten_Get(peak_frame_handle hFrame, size_t * bytesWritten);
    static PEAK_API_STATUS peak_Frame_ProcessingTime_Get(peak_frame_handle hFrame, uint32_t * processingTime_ms);
    static PEAK_API_ACCESS_STATUS peak_CameraSettings_ParameterSet_GetAccessStatus(peak_camera_handle hCam, peak_parameter_set parameterSet);
    static PEAK_API_STATUS peak_CameraSettings_ParameterSet_GetList(peak_camera_handle hCam, peak_parameter_set * parameterSetList, size_t * parameterSetCount);
    static PEAK_API_STATUS peak_CameraSettings_ParameterSet_Store(peak_camera_handle hCam, peak_parameter_set parameterSet);
    static PEAK_API_STATUS peak_CameraSettings_ParameterSet_Apply(peak_camera_handle hCam, peak_parameter_set parameterSet);
    static PEAK_API_ACCESS_STATUS peak_CameraSettings_ParameterSet_Startup_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_CameraSettings_ParameterSet_Startup_Set(peak_camera_handle hCam, peak_parameter_set parameterSet);
    static PEAK_API_STATUS peak_CameraSettings_ParameterSet_Startup_Get(peak_camera_handle hCam, peak_parameter_set * parameterSet);
    static PEAK_API_ACCESS_STATUS peak_CameraSettings_DiskFile_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_CameraSettings_DiskFile_Store(peak_camera_handle hCam, const char * file);
    static PEAK_API_STATUS peak_CameraSettings_DiskFile_Apply(peak_camera_handle hCam, const char * file);
    static PEAK_API_ACCESS_STATUS peak_FrameRate_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_FrameRate_GetRange(peak_camera_handle hCam, double * minFrameRate_fps, double * maxFrameRate_fps, double * incFrameRate_fps);
    static PEAK_API_STATUS peak_FrameRate_Set(peak_camera_handle hCam, double frameRate_fps);
    static PEAK_API_STATUS peak_FrameRate_Get(peak_camera_handle hCam, double * frameRate_fps);
    static PEAK_API_ACCESS_STATUS peak_ExposureTime_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_ExposureTime_GetRange(peak_camera_handle hCam, double * minExposureTime_us, double * maxExposureTime_us, double * incExposureTime_us);
    static PEAK_API_STATUS peak_ExposureTime_Set(peak_camera_handle hCam, double exposureTime_us);
    static PEAK_API_STATUS peak_ExposureTime_Get(peak_camera_handle hCam, double * exposureTime_us);
    static PEAK_API_ACCESS_STATUS peak_PixelClock_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_BOOL peak_PixelClock_HasRange(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_PixelClock_GetRange(peak_camera_handle hCam, double * minPixelClock_MHz, double * maxPixelClock_MHz, double * incPixelClock_MHz);
    static PEAK_API_STATUS peak_PixelClock_GetList(peak_camera_handle hCam, double * pixelClockList, size_t * pixelClockCount);
    static PEAK_API_STATUS peak_PixelClock_Set(peak_camera_handle hCam, double pixelClock_MHz);
    static PEAK_API_STATUS peak_PixelClock_Get(peak_camera_handle hCam, double * pixelClock_MHz);
    static PEAK_API_ACCESS_STATUS peak_IOChannel_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_STATUS peak_IOChannel_GetList(peak_camera_handle hCam, peak_io_channel * ioChannelList, size_t * ioChannelCount);
    static PEAK_API_ACCESS_STATUS peak_IOChannel_Level_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_BOOL peak_IOChannel_Level_IsHigh(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_ACCESS_STATUS peak_IOChannel_Inverter_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_STATUS peak_IOChannel_Inverter_Enable(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled);
    static PEAK_API_BOOL peak_IOChannel_Inverter_IsEnabled(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_ACCESS_STATUS peak_IOChannel_NoiseFilter_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_STATUS peak_IOChannel_NoiseFilter_Enable(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled);
    static PEAK_API_BOOL peak_IOChannel_NoiseFilter_IsEnabled(peak_camera_handle hCam, peak_io_channel ioChannel);
    static PEAK_API_STATUS peak_IOChannel_NoiseFilter_Duration_GetRange(peak_camera_handle hCam, peak_io_channel ioChannel, double * minNoiseFilterDuration_us, double * maxNoiseFilterDuration_us, double * incNoiseFilterDuration_us);
    static PEAK_API_STATUS peak_IOChannel_NoiseFilter_Duration_Set(peak_camera_handle hCam, peak_io_channel ioChannel, double noiseFilterDuration_us);
    static PEAK_API_STATUS peak_IOChannel_NoiseFilter_Duration_Get(peak_camera_handle hCam, peak_io_channel ioChannel, double * noiseFilterDuration_us);
    static PEAK_API_ACCESS_STATUS peak_Trigger_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Trigger_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_Trigger_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_BOOL peak_Trigger_IsExecutable(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Trigger_Execute(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_Trigger_Mode_GetAccessStatus(peak_camera_handle hCam, peak_trigger_mode triggerMode);
    static PEAK_API_STATUS peak_Trigger_Mode_Set(peak_camera_handle hCam, peak_trigger_mode triggerMode);
    static PEAK_API_STATUS peak_Trigger_Mode_Get(peak_camera_handle hCam, peak_trigger_mode * triggerMode);
    static PEAK_API_ACCESS_STATUS peak_Trigger_Edge_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Trigger_Edge_GetList(peak_camera_handle hCam, peak_trigger_edge * triggerEdgeList, size_t * triggerEdgeCount);
    static PEAK_API_STATUS peak_Trigger_Edge_Set(peak_camera_handle hCam, peak_trigger_edge triggerEdge);
    static PEAK_API_STATUS peak_Trigger_Edge_Get(peak_camera_handle hCam, peak_trigger_edge * triggerEdge);
    static PEAK_API_ACCESS_STATUS peak_Trigger_Delay_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Trigger_Delay_GetRange(peak_camera_handle hCam, double * minTriggerDelay_us, double * maxTriggerDelay_us, double * incTriggerDelay_us);
    static PEAK_API_STATUS peak_Trigger_Delay_Set(peak_camera_handle hCam, double triggerDelay_us);
    static PEAK_API_STATUS peak_Trigger_Delay_Get(peak_camera_handle hCam, double * triggerDelay_us);
    static PEAK_API_ACCESS_STATUS peak_Trigger_Divider_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Trigger_Divider_GetRange(peak_camera_handle hCam, uint32_t * minTriggerDivider, uint32_t * maxTriggerDivider, uint32_t * incTriggerDivider);
    static PEAK_API_STATUS peak_Trigger_Divider_Set(peak_camera_handle hCam, uint32_t triggerDivider);
    static PEAK_API_STATUS peak_Trigger_Divider_Get(peak_camera_handle hCam, uint32_t * triggerDivider);
    static PEAK_API_ACCESS_STATUS peak_Trigger_Burst_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Trigger_Burst_GetRange(peak_camera_handle hCam, uint32_t * minTriggerBurst, uint32_t * maxTriggerBurst, uint32_t * incTriggerBurst);
    static PEAK_API_STATUS peak_Trigger_Burst_Set(peak_camera_handle hCam, uint32_t triggerBurst);
    static PEAK_API_STATUS peak_Trigger_Burst_Get(peak_camera_handle hCam, uint32_t * triggerBurst);
    static PEAK_API_ACCESS_STATUS peak_Flash_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Flash_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_Flash_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_Flash_Mode_GetAccessStatus(peak_camera_handle hCam, peak_flash_mode flashMode);
    static PEAK_API_STATUS peak_Flash_Mode_Set(peak_camera_handle hCam, peak_flash_mode flashMode);
    static PEAK_API_STATUS peak_Flash_Mode_Get(peak_camera_handle hCam, peak_flash_mode * flashMode);
    static PEAK_API_ACCESS_STATUS peak_Flash_StartDelay_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Flash_StartDelay_GetRange(peak_camera_handle hCam, double * minFlashStartDelay_us, double * maxFlashStartDelay_us, double * incFlashStartDelay_us);
    static PEAK_API_STATUS peak_Flash_StartDelay_Set(peak_camera_handle hCam, double flashStartDelay_us);
    static PEAK_API_STATUS peak_Flash_StartDelay_Get(peak_camera_handle hCam, double * flashStartDelay_us);
    static PEAK_API_ACCESS_STATUS peak_Flash_EndDelay_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Flash_EndDelay_GetRange(peak_camera_handle hCam, double * minFlashEndDelay_us, double * maxFlashEndDelay_us, double * incFlashEndDelay_us);
    static PEAK_API_STATUS peak_Flash_EndDelay_Set(peak_camera_handle hCam, double flashEndDelay_us);
    static PEAK_API_STATUS peak_Flash_EndDelay_Get(peak_camera_handle hCam, double * flashEndDelay_us);
    static PEAK_API_ACCESS_STATUS peak_Flash_Duration_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Flash_Duration_GetRange(peak_camera_handle hCam, double * minFlashDuration_us, double * maxFlashDuration_us, double * incFlashDuration_us);
    static PEAK_API_STATUS peak_Flash_Duration_Set(peak_camera_handle hCam, double flashDuration_us);
    static PEAK_API_STATUS peak_Flash_Duration_Get(peak_camera_handle hCam, double * flashDuration_us);
    static PEAK_API_ACCESS_STATUS peak_PixelFormat_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_PixelFormat_GetList(peak_camera_handle hCam, peak_pixel_format * pixelFormatList, size_t * pixelFormatCount);
    static PEAK_API_STATUS peak_PixelFormat_Set(peak_camera_handle hCam, peak_pixel_format pixelFormat);
    static PEAK_API_STATUS peak_PixelFormat_Get(peak_camera_handle hCam, peak_pixel_format * pixelFormat);
    static PEAK_API_ACCESS_STATUS peak_Gain_GetAccessStatus(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel);
    static PEAK_API_STATUS peak_Gain_GetChannelList(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel * gainChannelList, size_t * gainChannelCount);
    static PEAK_API_STATUS peak_Gain_GetRange(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double * minGain, double * maxGain, double * incGain);
    static PEAK_API_STATUS peak_Gain_Set(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double gain);
    static PEAK_API_STATUS peak_Gain_Get(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double * gain);
    static PEAK_API_ACCESS_STATUS peak_Gamma_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Gamma_GetRange(peak_camera_handle hCam, double * minGamma, double * maxGamma, double * incGamma);
    static PEAK_API_STATUS peak_Gamma_Set(peak_camera_handle hCam, double gamma);
    static PEAK_API_STATUS peak_Gamma_Get(peak_camera_handle hCam, double * gamma);
    static PEAK_API_ACCESS_STATUS peak_ColorCorrection_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_ColorCorrection_Mode_GetList(peak_camera_handle hCam, peak_color_correction_mode * colorCorrectionModeList, size_t * colorCorrectionModeCount);
    static PEAK_API_STATUS peak_ColorCorrection_Mode_Set(peak_camera_handle hCam, peak_color_correction_mode colorCorrectionMode);
    static PEAK_API_STATUS peak_ColorCorrection_Mode_Get(peak_camera_handle hCam, peak_color_correction_mode * colorCorrectionMode);
    static PEAK_API_ACCESS_STATUS peak_ColorCorrection_Matrix_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_ColorCorrection_Matrix_GetRange(peak_camera_handle hCam, double * minMatrixElementValue, double * maxMatrixElementValue, double * incMatrixElementValue);
    static PEAK_API_STATUS peak_ColorCorrection_Matrix_Set(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix);
    static PEAK_API_STATUS peak_ColorCorrection_Matrix_Get(peak_camera_handle hCam, peak_matrix * colorCorrectionMatrix);
    static PEAK_API_STATUS peak_ColorCorrection_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_ColorCorrection_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_AutoBrightness_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_AutoBrightness_Target_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTarget, uint32_t * maxAutoBrightnessTarget, uint32_t * incAutoBrightnessTarget);
    static PEAK_API_STATUS peak_AutoBrightness_Target_Set(peak_camera_handle hCam, uint32_t autoBrightnessTarget);
    static PEAK_API_STATUS peak_AutoBrightness_Target_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTarget);
    static PEAK_API_STATUS peak_AutoBrightness_TargetTolerance_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTargetTolerance, uint32_t * maxAutoBrightnessTargetTolerance, uint32_t * incAutoBrightnessTargetTolerance);
    static PEAK_API_STATUS peak_AutoBrightness_TargetTolerance_Set(peak_camera_handle hCam, uint32_t autoBrightnessTargetTolerance);
    static PEAK_API_STATUS peak_AutoBrightness_TargetTolerance_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTargetTolerance);
    static PEAK_API_STATUS peak_AutoBrightness_TargetPercentile_GetRange(peak_camera_handle hCam, double * minAutoBrightnessTargetPercentile, double * maxAutoBrightnessTargetPercentile, double * incAutoBrightnessTargetPercentile);
    static PEAK_API_STATUS peak_AutoBrightness_TargetPercentile_Set(peak_camera_handle hCam, double autoBrightnessTargetPercentile);
    static PEAK_API_STATUS peak_AutoBrightness_TargetPercentile_Get(peak_camera_handle hCam, double * autoBrightnessTargetPercentile);
    static PEAK_API_STATUS peak_AutoBrightness_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoBrightnessROIMode);
    static PEAK_API_STATUS peak_AutoBrightness_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoBrightnessROIMode);
    static PEAK_API_STATUS peak_AutoBrightness_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoBrightnessROIOffset, peak_position * maxAutoBrightnessROIOffset, peak_position * incAutoBrightnessROIOffset);
    static PEAK_API_STATUS peak_AutoBrightness_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoBrightnessROISize, peak_size * maxAutoBrightnessROISize, peak_size * incAutoBrightnessROISize);
    static PEAK_API_STATUS peak_AutoBrightness_ROI_Set(peak_camera_handle hCam, peak_roi autoBrightnessROI);
    static PEAK_API_STATUS peak_AutoBrightness_ROI_Get(peak_camera_handle hCam, peak_roi * autoBrightnessROI);
    static PEAK_API_ACCESS_STATUS peak_AutoBrightness_Exposure_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_AutoBrightness_Exposure_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode);
    static PEAK_API_STATUS peak_AutoBrightness_Exposure_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoExposureMode);
    static PEAK_API_ACCESS_STATUS peak_AutoBrightness_Gain_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_AutoBrightness_Gain_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode);
    static PEAK_API_STATUS peak_AutoBrightness_Gain_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoGainMode);
    static PEAK_API_ACCESS_STATUS peak_AutoWhiteBalance_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoWhiteBalanceROIMode);
    static PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoWhiteBalanceROIMode);
    static PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoWhiteBalanceROIOffset, peak_position * maxAutoWhiteBalanceROIOffset, peak_position * incAutoWhiteBalanceROIOffset);
    static PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoWhiteBalanceROISize, peak_size * maxAutoWhiteBalanceROISize, peak_size * incAutoWhiteBalanceROISize);
    static PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Set(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI);
    static PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Get(peak_camera_handle hCam, peak_roi * autoWhiteBalanceROI);
    static PEAK_API_STATUS peak_AutoWhiteBalance_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode);
    static PEAK_API_STATUS peak_AutoWhiteBalance_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoWhiteBalanceMode);
    static PEAK_API_ACCESS_STATUS peak_ROI_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minROIOffset, peak_position * maxROIOffset, peak_position * incROIOffset);
    static PEAK_API_STATUS peak_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minROISize, peak_size * maxROISize, peak_size * incROISize);
    static PEAK_API_STATUS peak_ROI_Set(peak_camera_handle hCam, peak_roi roi);
    static PEAK_API_STATUS peak_ROI_Get(peak_camera_handle hCam, peak_roi * roi);
    static PEAK_API_ACCESS_STATUS peak_Binning_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Binning_FactorX_GetList(peak_camera_handle hCam, uint32_t * binningFactorXList, size_t * binningFactorXCount);
    static PEAK_API_STATUS peak_Binning_FactorY_GetList(peak_camera_handle hCam, uint32_t * binningFactorYList, size_t * binningFactorYCount);
    static PEAK_API_STATUS peak_Binning_Set(peak_camera_handle hCam, uint32_t binningFactorX, uint32_t binningFactorY);
    static PEAK_API_STATUS peak_Binning_Get(peak_camera_handle hCam, uint32_t * binningFactorX, uint32_t * binningFactorY);
    static PEAK_API_ACCESS_STATUS peak_Decimation_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Decimation_FactorX_GetList(peak_camera_handle hCam, uint32_t * decimationFactorXList, size_t * decimationFactorXCount);
    static PEAK_API_STATUS peak_Decimation_FactorY_GetList(peak_camera_handle hCam, uint32_t * decimationFactorYList, size_t * decimationFactorYCount);
    static PEAK_API_STATUS peak_Decimation_Set(peak_camera_handle hCam, uint32_t decimationFactorX, uint32_t decimationFactorY);
    static PEAK_API_STATUS peak_Decimation_Get(peak_camera_handle hCam, uint32_t * decimationFactorX, uint32_t * decimationFactorY);
    static PEAK_API_ACCESS_STATUS peak_Mirror_LeftRight_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Mirror_LeftRight_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_Mirror_LeftRight_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_Mirror_UpDown_GetAccessStatus(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_Mirror_UpDown_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_Mirror_UpDown_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_CameraMemory_Area_GetAccessStatus(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea);
    static PEAK_API_STATUS peak_CameraMemory_Area_GetList(peak_camera_handle hCam, peak_camera_memory_area * cameraMemoryAreaList, size_t * cameraMemoryAreaCount);
    static PEAK_API_STATUS peak_CameraMemory_Area_Size_Get(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, size_t * cameraMemoryAreaSize);
    static PEAK_API_STATUS peak_CameraMemory_Area_Data_Clear(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea);
    static PEAK_API_STATUS peak_CameraMemory_Area_Data_Write(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, const uint8_t * data, size_t dataSize);
    static PEAK_API_STATUS peak_CameraMemory_Area_Data_Read(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, uint8_t * data, size_t dataSize);
    static PEAK_API_STATUS peak_GFA_EnableWriteAccess(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_GFA_IsWriteAccessEnabled(peak_camera_handle hCam);
    static PEAK_API_ACCESS_STATUS peak_GFA_Feature_GetAccessStatus(peak_camera_handle hCam, peak_gfa_module module, const char * featureName);
    static PEAK_API_BOOL peak_GFA_Float_HasRange(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName);
    static PEAK_API_STATUS peak_GFA_Float_GetRange(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * minFloatValue, double * maxFloatValue, double * incFloatValue);
    static PEAK_API_STATUS peak_GFA_Float_GetList(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * floatList, size_t * floatCount);
    static PEAK_API_STATUS peak_GFA_Float_Set(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double floatValue);
    static PEAK_API_STATUS peak_GFA_Float_Get(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * floatValue);
    static PEAK_API_BOOL peak_GFA_Integer_HasRange(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName);
    static PEAK_API_STATUS peak_GFA_Integer_GetRange(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * minIntegerValue, int64_t * maxIntegerValue, int64_t * incIntegerValue);
    static PEAK_API_STATUS peak_GFA_Integer_GetList(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * integerList, size_t * integerCount);
    static PEAK_API_STATUS peak_GFA_Integer_Set(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t integerValue);
    static PEAK_API_STATUS peak_GFA_Integer_Get(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * integerValue);
    static PEAK_API_STATUS peak_GFA_Boolean_Set(peak_camera_handle hCam, peak_gfa_module module, const char * booleanFeatureName, peak_bool booleanValue);
    static PEAK_API_STATUS peak_GFA_Boolean_Get(peak_camera_handle hCam, peak_gfa_module module, const char * booleanFeatureName, peak_bool * booleanValue);
    static PEAK_API_STATUS peak_GFA_String_Set(peak_camera_handle hCam, peak_gfa_module module, const char * stringFeatureName, const char * stringValue);
    static PEAK_API_STATUS peak_GFA_String_Get(peak_camera_handle hCam, peak_gfa_module module, const char * stringFeatureName, char * stringValue, size_t * stringValueSize);
    static PEAK_API_STATUS peak_GFA_Command_Execute(peak_camera_handle hCam, peak_gfa_module module, const char * commandFeatureName);
    static PEAK_API_STATUS peak_GFA_Command_WaitForDone(peak_camera_handle hCam, peak_gfa_module module, const char * commandFeatureName, uint32_t timeout_ms);
    static PEAK_API_STATUS peak_GFA_Enumeration_GetList(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, peak_gfa_enumeration_entry * enumerationEntryList, size_t * enumerationEntryCount);
    static PEAK_API_ACCESS_STATUS peak_GFA_EnumerationEntry_GetAccessStatus(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const peak_gfa_enumeration_entry * enumerationEntry);
    static PEAK_API_ACCESS_STATUS peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const char * enumerationEntrySymbolicValue);
    static PEAK_API_ACCESS_STATUS peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, int64_t enumerationEntryIntegerValue);
    static PEAK_API_STATUS peak_GFA_Enumeration_Set(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const peak_gfa_enumeration_entry * enumerationEntry);
    static PEAK_API_STATUS peak_GFA_Enumeration_SetBySymbolicValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const char * enumerationEntrySymbolicValue);
    static PEAK_API_STATUS peak_GFA_Enumeration_SetByIntegerValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, int64_t enumerationEntryIntegerValue);
    static PEAK_API_STATUS peak_GFA_Enumeration_Get(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, peak_gfa_enumeration_entry * enumerationEntry);
    static PEAK_API_STATUS peak_GFA_Register_Set(peak_camera_handle hCam, peak_gfa_module module, const char * registerFeatureName, const uint8_t * registerValue, size_t registerValueSize);
    static PEAK_API_STATUS peak_GFA_Register_Get(peak_camera_handle hCam, peak_gfa_module module, const char * registerFeatureName, uint8_t * registerValue, size_t * registerValueSize);
    static PEAK_API_STATUS peak_GFA_Data_Write(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, const uint8_t * data, size_t dataSize);
    static PEAK_API_STATUS peak_GFA_Data_Read(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, uint8_t * data, size_t dataSize);
    static PEAK_API_STATUS peak_IPL_PixelFormat_GetList(peak_camera_handle hCam, peak_pixel_format inputPixelFormat, peak_pixel_format * outputPixelFormatList, size_t * outputPixelFormatCount);
    static PEAK_API_STATUS peak_IPL_PixelFormat_Set(peak_camera_handle hCam, peak_pixel_format pixelFormat);
    static PEAK_API_STATUS peak_IPL_PixelFormat_Get(peak_camera_handle hCam, peak_pixel_format * pixelFormat);
    static PEAK_API_STATUS peak_IPL_Gain_GetRange(peak_camera_handle hCam, peak_gain_channel gainChannel, double * minGain, double * maxGain, double * incGain);
    static PEAK_API_STATUS peak_IPL_Gain_Set(peak_camera_handle hCam, peak_gain_channel gainChannel, double gain);
    static PEAK_API_STATUS peak_IPL_Gain_Get(peak_camera_handle hCam, peak_gain_channel gainChannel, double * gain);
    static PEAK_API_STATUS peak_IPL_Gamma_GetRange(peak_camera_handle hCam, double * minGamma, double * maxGamma, double * incGamma);
    static PEAK_API_STATUS peak_IPL_Gamma_Set(peak_camera_handle hCam, double gamma);
    static PEAK_API_STATUS peak_IPL_Gamma_Get(peak_camera_handle hCam, double * gamma);
    static PEAK_API_STATUS peak_IPL_ColorCorrection_Matrix_Set(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix);
    static PEAK_API_STATUS peak_IPL_ColorCorrection_Matrix_Get(peak_camera_handle hCam, peak_matrix * colorCorrectionMatrix);
    static PEAK_API_STATUS peak_IPL_ColorCorrection_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_IPL_ColorCorrection_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Target_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTarget, uint32_t * maxAutoBrightnessTarget, uint32_t * incAutoBrightnessTarget);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Target_Set(peak_camera_handle hCam, uint32_t autoBrightnessTarget);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Target_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTarget);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_TargetTolerance_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTargetTolerance, uint32_t * maxAutoBrightnessTargetTolerance, uint32_t * incAutoBrightnessTargetTolerance);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_TargetTolerance_Set(peak_camera_handle hCam, uint32_t autoBrightnessTargetTolerance);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_TargetTolerance_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTargetTolerance);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_TargetPercentile_GetRange(peak_camera_handle hCam, double * minAutoBrightnessTargetPercentile, double * maxAutoBrightnessTargetPercentile, double * incAutoBrightnessTargetPercentile);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_TargetPercentile_Set(peak_camera_handle hCam, double autoBrightnessTargetPercentile);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_TargetPercentile_Get(peak_camera_handle hCam, double * autoBrightnessTargetPercentile);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoBrightnessROIMode);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoBrightnessROIMode);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoBrightnessROIOffset, peak_position * maxAutoBrightnessROIOffset, peak_position * incAutoBrightnessROIOffset);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoBrightnessROISize, peak_size * maxAutoBrightnessROISize, peak_size * incAutoBrightnessROISize);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Set(peak_camera_handle hCam, peak_roi autoBrightnessROI);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Get(peak_camera_handle hCam, peak_roi * autoBrightnessROI);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Exposure_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Exposure_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoExposureMode);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Gain_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode);
    static PEAK_API_STATUS peak_IPL_AutoBrightness_Gain_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoGainMode);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoWhiteBalanceROIMode);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoWhiteBalanceROIMode);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoWhiteBalanceROIOffset, peak_position * maxAutoWhiteBalanceROIOffset, peak_position * incAutoWhiteBalanceROIOffset);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoWhiteBalanceROISize, peak_size * maxAutoWhiteBalanceROISize, peak_size * incAutoWhiteBalanceROISize);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Set(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Get(peak_camera_handle hCam, peak_roi * autoWhiteBalanceROI);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode);
    static PEAK_API_STATUS peak_IPL_AutoWhiteBalance_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoWhiteBalanceMode);
    static PEAK_API_STATUS peak_IPL_HotpixelCorrection_Sensitivity_Set(peak_camera_handle hCam, peak_hotpixel_correction_sensitivity hotpixelCorrectionSensitivity);
    static PEAK_API_STATUS peak_IPL_HotpixelCorrection_Sensitivity_Get(peak_camera_handle hCam, peak_hotpixel_correction_sensitivity * hotpixelCorrectionSensitivity);
    static PEAK_API_STATUS peak_IPL_HotpixelCorrection_GetList(peak_camera_handle hCam, peak_position * hotpixelList, size_t * hotpixelCount);
    static PEAK_API_STATUS peak_IPL_HotpixelCorrection_SetList(peak_camera_handle hCam, peak_position * hotpixelList, size_t hotpixelCount);
    static PEAK_API_STATUS peak_IPL_HotpixelCorrection_ResetList(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_IPL_HotpixelCorrection_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_IPL_HotpixelCorrection_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_IPL_Mirror_UpDown_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_IPL_Mirror_UpDown_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_IPL_Mirror_LeftRight_Enable(peak_camera_handle hCam, peak_bool enabled);
    static PEAK_API_BOOL peak_IPL_Mirror_LeftRight_IsEnabled(peak_camera_handle hCam);
    static PEAK_API_STATUS peak_IPL_ProcessFrame(peak_camera_handle hCam, peak_frame_handle hFrame, peak_frame_handle * hResultFrame);
    static PEAK_API_STATUS peak_IPL_ProcessFrameInplace(peak_camera_handle hCam, peak_frame_handle hFrame);
    static PEAK_API_STATUS peak_VideoWriter_Open(peak_video_handle * hVideo, const char * fileName, peak_video_container container, peak_video_encoder encoder);
    static PEAK_API_STATUS peak_VideoWriter_Close(peak_video_handle hVideo);
    static PEAK_API_STATUS peak_VideoWriter_AddFrame(peak_video_handle hVideo, peak_frame_handle hFrame);
    static PEAK_API_STATUS peak_VideoWriter_Container_GetEncoderList(peak_video_container container, peak_video_encoder * encoderList, size_t * encoderCount);
    static PEAK_API_STATUS peak_VideoWriter_Encoder_GetPixelFormatList(peak_video_encoder encoder, peak_pixel_format * pixelFormatList, size_t * pixelFormatCount);
    static PEAK_API_STATUS peak_VideoWriter_Encoder_GetContainerList(peak_video_encoder encoder, peak_video_container * containerList, size_t * containerCount);
    static PEAK_API_STATUS peak_VideoWriter_GetInfo(peak_video_handle hVideo, peak_video_info * videoInfo);
    static PEAK_API_STATUS peak_VideoWriter_Container_Option_Set(peak_video_handle hVideo, peak_video_container_option containerOption, const void * value, size_t count);
    static PEAK_API_STATUS peak_VideoWriter_Container_Option_Get(peak_video_handle hVideo, peak_video_container_option containerOption, void * value, size_t count, size_t * outCount);
    static PEAK_API_STATUS peak_VideoWriter_Encoder_Option_Set(peak_video_handle hVideo, peak_video_encoder_option encoderOption, const void * value, size_t count);
    static PEAK_API_STATUS peak_VideoWriter_Encoder_Option_Get(peak_video_handle hVideo, peak_video_encoder_option encoderOption, void * value, size_t count, size_t * outCount);
    static PEAK_API_STATUS peak_VideoWriter_WaitUntilQueueEmpty(peak_video_handle hVideo, int32_t timeout_ms);
       
private:
    void* m_handle = nullptr;
    dyn_peak_Library_Init m_peak_Library_Init{};
    dyn_peak_Library_Exit m_peak_Library_Exit{};
    dyn_peak_Library_GetVersion m_peak_Library_GetVersion{};
    dyn_peak_Library_GetLastError m_peak_Library_GetLastError{};
    dyn_peak_CameraList_Update m_peak_CameraList_Update{};
    dyn_peak_CameraList_Get m_peak_CameraList_Get{};
    dyn_peak_Camera_ID_FromHandle m_peak_Camera_ID_FromHandle{};
    dyn_peak_Camera_ID_FromSerialNumber m_peak_Camera_ID_FromSerialNumber{};
    dyn_peak_Camera_ID_FromMAC m_peak_Camera_ID_FromMAC{};
    dyn_peak_Camera_GetAccessStatus m_peak_Camera_GetAccessStatus{};
    dyn_peak_Camera_GetDescriptor m_peak_Camera_GetDescriptor{};
    dyn_peak_Camera_Open m_peak_Camera_Open{};
    dyn_peak_Camera_OpenFirstAvailable m_peak_Camera_OpenFirstAvailable{};
    dyn_peak_Camera_Close m_peak_Camera_Close{};
    dyn_peak_Camera_ResetToDefaultSettings m_peak_Camera_ResetToDefaultSettings{};
    dyn_peak_EthernetConfig_GetAccessStatus m_peak_EthernetConfig_GetAccessStatus{};
    dyn_peak_EthernetConfig_GetInfo m_peak_EthernetConfig_GetInfo{};
    dyn_peak_EthernetConfig_DHCP_GetAccessStatus m_peak_EthernetConfig_DHCP_GetAccessStatus{};
    dyn_peak_EthernetConfig_DHCP_Enable m_peak_EthernetConfig_DHCP_Enable{};
    dyn_peak_EthernetConfig_DHCP_IsEnabled m_peak_EthernetConfig_DHCP_IsEnabled{};
    dyn_peak_EthernetConfig_PersistentIP_GetAccessStatus m_peak_EthernetConfig_PersistentIP_GetAccessStatus{};
    dyn_peak_EthernetConfig_PersistentIP_Set m_peak_EthernetConfig_PersistentIP_Set{};
    dyn_peak_EthernetConfig_PersistentIP_Get m_peak_EthernetConfig_PersistentIP_Get{};
    dyn_peak_Acquisition_Start m_peak_Acquisition_Start{};
    dyn_peak_Acquisition_Stop m_peak_Acquisition_Stop{};
    dyn_peak_Acquisition_IsStarted m_peak_Acquisition_IsStarted{};
    dyn_peak_Acquisition_WaitForFrame m_peak_Acquisition_WaitForFrame{};
    dyn_peak_Acquisition_GetInfo m_peak_Acquisition_GetInfo{};
    dyn_peak_Acquisition_Buffer_GetRequiredSize m_peak_Acquisition_Buffer_GetRequiredSize{};
    dyn_peak_Acquisition_Buffer_GetRequiredCount m_peak_Acquisition_Buffer_GetRequiredCount{};
    dyn_peak_Acquisition_Buffer_Announce m_peak_Acquisition_Buffer_Announce{};
    dyn_peak_Acquisition_Buffer_Revoke m_peak_Acquisition_Buffer_Revoke{};
    dyn_peak_Acquisition_Buffer_RevokeAll m_peak_Acquisition_Buffer_RevokeAll{};
    dyn_peak_PixelFormat_GetInfo m_peak_PixelFormat_GetInfo{};
    dyn_peak_Frame_Release m_peak_Frame_Release{};
    dyn_peak_Frame_GetInfo m_peak_Frame_GetInfo{};
    dyn_peak_Frame_Type_Get m_peak_Frame_Type_Get{};
    dyn_peak_Frame_Buffer_Get m_peak_Frame_Buffer_Get{};
    dyn_peak_Frame_ID_Get m_peak_Frame_ID_Get{};
    dyn_peak_Frame_Timestamp_Get m_peak_Frame_Timestamp_Get{};
    dyn_peak_Frame_ROI_Get m_peak_Frame_ROI_Get{};
    dyn_peak_Frame_PixelFormat_Get m_peak_Frame_PixelFormat_Get{};
    dyn_peak_Frame_IsComplete m_peak_Frame_IsComplete{};
    dyn_peak_Frame_BytesExpected_Get m_peak_Frame_BytesExpected_Get{};
    dyn_peak_Frame_BytesWritten_Get m_peak_Frame_BytesWritten_Get{};
    dyn_peak_Frame_ProcessingTime_Get m_peak_Frame_ProcessingTime_Get{};
    dyn_peak_CameraSettings_ParameterSet_GetAccessStatus m_peak_CameraSettings_ParameterSet_GetAccessStatus{};
    dyn_peak_CameraSettings_ParameterSet_GetList m_peak_CameraSettings_ParameterSet_GetList{};
    dyn_peak_CameraSettings_ParameterSet_Store m_peak_CameraSettings_ParameterSet_Store{};
    dyn_peak_CameraSettings_ParameterSet_Apply m_peak_CameraSettings_ParameterSet_Apply{};
    dyn_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus m_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus{};
    dyn_peak_CameraSettings_ParameterSet_Startup_Set m_peak_CameraSettings_ParameterSet_Startup_Set{};
    dyn_peak_CameraSettings_ParameterSet_Startup_Get m_peak_CameraSettings_ParameterSet_Startup_Get{};
    dyn_peak_CameraSettings_DiskFile_GetAccessStatus m_peak_CameraSettings_DiskFile_GetAccessStatus{};
    dyn_peak_CameraSettings_DiskFile_Store m_peak_CameraSettings_DiskFile_Store{};
    dyn_peak_CameraSettings_DiskFile_Apply m_peak_CameraSettings_DiskFile_Apply{};
    dyn_peak_FrameRate_GetAccessStatus m_peak_FrameRate_GetAccessStatus{};
    dyn_peak_FrameRate_GetRange m_peak_FrameRate_GetRange{};
    dyn_peak_FrameRate_Set m_peak_FrameRate_Set{};
    dyn_peak_FrameRate_Get m_peak_FrameRate_Get{};
    dyn_peak_ExposureTime_GetAccessStatus m_peak_ExposureTime_GetAccessStatus{};
    dyn_peak_ExposureTime_GetRange m_peak_ExposureTime_GetRange{};
    dyn_peak_ExposureTime_Set m_peak_ExposureTime_Set{};
    dyn_peak_ExposureTime_Get m_peak_ExposureTime_Get{};
    dyn_peak_PixelClock_GetAccessStatus m_peak_PixelClock_GetAccessStatus{};
    dyn_peak_PixelClock_HasRange m_peak_PixelClock_HasRange{};
    dyn_peak_PixelClock_GetRange m_peak_PixelClock_GetRange{};
    dyn_peak_PixelClock_GetList m_peak_PixelClock_GetList{};
    dyn_peak_PixelClock_Set m_peak_PixelClock_Set{};
    dyn_peak_PixelClock_Get m_peak_PixelClock_Get{};
    dyn_peak_IOChannel_GetAccessStatus m_peak_IOChannel_GetAccessStatus{};
    dyn_peak_IOChannel_GetList m_peak_IOChannel_GetList{};
    dyn_peak_IOChannel_Level_GetAccessStatus m_peak_IOChannel_Level_GetAccessStatus{};
    dyn_peak_IOChannel_Level_IsHigh m_peak_IOChannel_Level_IsHigh{};
    dyn_peak_IOChannel_Inverter_GetAccessStatus m_peak_IOChannel_Inverter_GetAccessStatus{};
    dyn_peak_IOChannel_Inverter_Enable m_peak_IOChannel_Inverter_Enable{};
    dyn_peak_IOChannel_Inverter_IsEnabled m_peak_IOChannel_Inverter_IsEnabled{};
    dyn_peak_IOChannel_NoiseFilter_GetAccessStatus m_peak_IOChannel_NoiseFilter_GetAccessStatus{};
    dyn_peak_IOChannel_NoiseFilter_Enable m_peak_IOChannel_NoiseFilter_Enable{};
    dyn_peak_IOChannel_NoiseFilter_IsEnabled m_peak_IOChannel_NoiseFilter_IsEnabled{};
    dyn_peak_IOChannel_NoiseFilter_Duration_GetRange m_peak_IOChannel_NoiseFilter_Duration_GetRange{};
    dyn_peak_IOChannel_NoiseFilter_Duration_Set m_peak_IOChannel_NoiseFilter_Duration_Set{};
    dyn_peak_IOChannel_NoiseFilter_Duration_Get m_peak_IOChannel_NoiseFilter_Duration_Get{};
    dyn_peak_Trigger_GetAccessStatus m_peak_Trigger_GetAccessStatus{};
    dyn_peak_Trigger_Enable m_peak_Trigger_Enable{};
    dyn_peak_Trigger_IsEnabled m_peak_Trigger_IsEnabled{};
    dyn_peak_Trigger_IsExecutable m_peak_Trigger_IsExecutable{};
    dyn_peak_Trigger_Execute m_peak_Trigger_Execute{};
    dyn_peak_Trigger_Mode_GetAccessStatus m_peak_Trigger_Mode_GetAccessStatus{};
    dyn_peak_Trigger_Mode_Set m_peak_Trigger_Mode_Set{};
    dyn_peak_Trigger_Mode_Get m_peak_Trigger_Mode_Get{};
    dyn_peak_Trigger_Edge_GetAccessStatus m_peak_Trigger_Edge_GetAccessStatus{};
    dyn_peak_Trigger_Edge_GetList m_peak_Trigger_Edge_GetList{};
    dyn_peak_Trigger_Edge_Set m_peak_Trigger_Edge_Set{};
    dyn_peak_Trigger_Edge_Get m_peak_Trigger_Edge_Get{};
    dyn_peak_Trigger_Delay_GetAccessStatus m_peak_Trigger_Delay_GetAccessStatus{};
    dyn_peak_Trigger_Delay_GetRange m_peak_Trigger_Delay_GetRange{};
    dyn_peak_Trigger_Delay_Set m_peak_Trigger_Delay_Set{};
    dyn_peak_Trigger_Delay_Get m_peak_Trigger_Delay_Get{};
    dyn_peak_Trigger_Divider_GetAccessStatus m_peak_Trigger_Divider_GetAccessStatus{};
    dyn_peak_Trigger_Divider_GetRange m_peak_Trigger_Divider_GetRange{};
    dyn_peak_Trigger_Divider_Set m_peak_Trigger_Divider_Set{};
    dyn_peak_Trigger_Divider_Get m_peak_Trigger_Divider_Get{};
    dyn_peak_Trigger_Burst_GetAccessStatus m_peak_Trigger_Burst_GetAccessStatus{};
    dyn_peak_Trigger_Burst_GetRange m_peak_Trigger_Burst_GetRange{};
    dyn_peak_Trigger_Burst_Set m_peak_Trigger_Burst_Set{};
    dyn_peak_Trigger_Burst_Get m_peak_Trigger_Burst_Get{};
    dyn_peak_Flash_GetAccessStatus m_peak_Flash_GetAccessStatus{};
    dyn_peak_Flash_Enable m_peak_Flash_Enable{};
    dyn_peak_Flash_IsEnabled m_peak_Flash_IsEnabled{};
    dyn_peak_Flash_Mode_GetAccessStatus m_peak_Flash_Mode_GetAccessStatus{};
    dyn_peak_Flash_Mode_Set m_peak_Flash_Mode_Set{};
    dyn_peak_Flash_Mode_Get m_peak_Flash_Mode_Get{};
    dyn_peak_Flash_StartDelay_GetAccessStatus m_peak_Flash_StartDelay_GetAccessStatus{};
    dyn_peak_Flash_StartDelay_GetRange m_peak_Flash_StartDelay_GetRange{};
    dyn_peak_Flash_StartDelay_Set m_peak_Flash_StartDelay_Set{};
    dyn_peak_Flash_StartDelay_Get m_peak_Flash_StartDelay_Get{};
    dyn_peak_Flash_EndDelay_GetAccessStatus m_peak_Flash_EndDelay_GetAccessStatus{};
    dyn_peak_Flash_EndDelay_GetRange m_peak_Flash_EndDelay_GetRange{};
    dyn_peak_Flash_EndDelay_Set m_peak_Flash_EndDelay_Set{};
    dyn_peak_Flash_EndDelay_Get m_peak_Flash_EndDelay_Get{};
    dyn_peak_Flash_Duration_GetAccessStatus m_peak_Flash_Duration_GetAccessStatus{};
    dyn_peak_Flash_Duration_GetRange m_peak_Flash_Duration_GetRange{};
    dyn_peak_Flash_Duration_Set m_peak_Flash_Duration_Set{};
    dyn_peak_Flash_Duration_Get m_peak_Flash_Duration_Get{};
    dyn_peak_PixelFormat_GetAccessStatus m_peak_PixelFormat_GetAccessStatus{};
    dyn_peak_PixelFormat_GetList m_peak_PixelFormat_GetList{};
    dyn_peak_PixelFormat_Set m_peak_PixelFormat_Set{};
    dyn_peak_PixelFormat_Get m_peak_PixelFormat_Get{};
    dyn_peak_Gain_GetAccessStatus m_peak_Gain_GetAccessStatus{};
    dyn_peak_Gain_GetChannelList m_peak_Gain_GetChannelList{};
    dyn_peak_Gain_GetRange m_peak_Gain_GetRange{};
    dyn_peak_Gain_Set m_peak_Gain_Set{};
    dyn_peak_Gain_Get m_peak_Gain_Get{};
    dyn_peak_Gamma_GetAccessStatus m_peak_Gamma_GetAccessStatus{};
    dyn_peak_Gamma_GetRange m_peak_Gamma_GetRange{};
    dyn_peak_Gamma_Set m_peak_Gamma_Set{};
    dyn_peak_Gamma_Get m_peak_Gamma_Get{};
    dyn_peak_ColorCorrection_GetAccessStatus m_peak_ColorCorrection_GetAccessStatus{};
    dyn_peak_ColorCorrection_Mode_GetList m_peak_ColorCorrection_Mode_GetList{};
    dyn_peak_ColorCorrection_Mode_Set m_peak_ColorCorrection_Mode_Set{};
    dyn_peak_ColorCorrection_Mode_Get m_peak_ColorCorrection_Mode_Get{};
    dyn_peak_ColorCorrection_Matrix_GetAccessStatus m_peak_ColorCorrection_Matrix_GetAccessStatus{};
    dyn_peak_ColorCorrection_Matrix_GetRange m_peak_ColorCorrection_Matrix_GetRange{};
    dyn_peak_ColorCorrection_Matrix_Set m_peak_ColorCorrection_Matrix_Set{};
    dyn_peak_ColorCorrection_Matrix_Get m_peak_ColorCorrection_Matrix_Get{};
    dyn_peak_ColorCorrection_Enable m_peak_ColorCorrection_Enable{};
    dyn_peak_ColorCorrection_IsEnabled m_peak_ColorCorrection_IsEnabled{};
    dyn_peak_AutoBrightness_GetAccessStatus m_peak_AutoBrightness_GetAccessStatus{};
    dyn_peak_AutoBrightness_Target_GetRange m_peak_AutoBrightness_Target_GetRange{};
    dyn_peak_AutoBrightness_Target_Set m_peak_AutoBrightness_Target_Set{};
    dyn_peak_AutoBrightness_Target_Get m_peak_AutoBrightness_Target_Get{};
    dyn_peak_AutoBrightness_TargetTolerance_GetRange m_peak_AutoBrightness_TargetTolerance_GetRange{};
    dyn_peak_AutoBrightness_TargetTolerance_Set m_peak_AutoBrightness_TargetTolerance_Set{};
    dyn_peak_AutoBrightness_TargetTolerance_Get m_peak_AutoBrightness_TargetTolerance_Get{};
    dyn_peak_AutoBrightness_TargetPercentile_GetRange m_peak_AutoBrightness_TargetPercentile_GetRange{};
    dyn_peak_AutoBrightness_TargetPercentile_Set m_peak_AutoBrightness_TargetPercentile_Set{};
    dyn_peak_AutoBrightness_TargetPercentile_Get m_peak_AutoBrightness_TargetPercentile_Get{};
    dyn_peak_AutoBrightness_ROI_Mode_Set m_peak_AutoBrightness_ROI_Mode_Set{};
    dyn_peak_AutoBrightness_ROI_Mode_Get m_peak_AutoBrightness_ROI_Mode_Get{};
    dyn_peak_AutoBrightness_ROI_Offset_GetRange m_peak_AutoBrightness_ROI_Offset_GetRange{};
    dyn_peak_AutoBrightness_ROI_Size_GetRange m_peak_AutoBrightness_ROI_Size_GetRange{};
    dyn_peak_AutoBrightness_ROI_Set m_peak_AutoBrightness_ROI_Set{};
    dyn_peak_AutoBrightness_ROI_Get m_peak_AutoBrightness_ROI_Get{};
    dyn_peak_AutoBrightness_Exposure_GetAccessStatus m_peak_AutoBrightness_Exposure_GetAccessStatus{};
    dyn_peak_AutoBrightness_Exposure_Mode_Set m_peak_AutoBrightness_Exposure_Mode_Set{};
    dyn_peak_AutoBrightness_Exposure_Mode_Get m_peak_AutoBrightness_Exposure_Mode_Get{};
    dyn_peak_AutoBrightness_Gain_GetAccessStatus m_peak_AutoBrightness_Gain_GetAccessStatus{};
    dyn_peak_AutoBrightness_Gain_Mode_Set m_peak_AutoBrightness_Gain_Mode_Set{};
    dyn_peak_AutoBrightness_Gain_Mode_Get m_peak_AutoBrightness_Gain_Mode_Get{};
    dyn_peak_AutoWhiteBalance_GetAccessStatus m_peak_AutoWhiteBalance_GetAccessStatus{};
    dyn_peak_AutoWhiteBalance_ROI_Mode_Set m_peak_AutoWhiteBalance_ROI_Mode_Set{};
    dyn_peak_AutoWhiteBalance_ROI_Mode_Get m_peak_AutoWhiteBalance_ROI_Mode_Get{};
    dyn_peak_AutoWhiteBalance_ROI_Offset_GetRange m_peak_AutoWhiteBalance_ROI_Offset_GetRange{};
    dyn_peak_AutoWhiteBalance_ROI_Size_GetRange m_peak_AutoWhiteBalance_ROI_Size_GetRange{};
    dyn_peak_AutoWhiteBalance_ROI_Set m_peak_AutoWhiteBalance_ROI_Set{};
    dyn_peak_AutoWhiteBalance_ROI_Get m_peak_AutoWhiteBalance_ROI_Get{};
    dyn_peak_AutoWhiteBalance_Mode_Set m_peak_AutoWhiteBalance_Mode_Set{};
    dyn_peak_AutoWhiteBalance_Mode_Get m_peak_AutoWhiteBalance_Mode_Get{};
    dyn_peak_ROI_GetAccessStatus m_peak_ROI_GetAccessStatus{};
    dyn_peak_ROI_Offset_GetRange m_peak_ROI_Offset_GetRange{};
    dyn_peak_ROI_Size_GetRange m_peak_ROI_Size_GetRange{};
    dyn_peak_ROI_Set m_peak_ROI_Set{};
    dyn_peak_ROI_Get m_peak_ROI_Get{};
    dyn_peak_Binning_GetAccessStatus m_peak_Binning_GetAccessStatus{};
    dyn_peak_Binning_FactorX_GetList m_peak_Binning_FactorX_GetList{};
    dyn_peak_Binning_FactorY_GetList m_peak_Binning_FactorY_GetList{};
    dyn_peak_Binning_Set m_peak_Binning_Set{};
    dyn_peak_Binning_Get m_peak_Binning_Get{};
    dyn_peak_Decimation_GetAccessStatus m_peak_Decimation_GetAccessStatus{};
    dyn_peak_Decimation_FactorX_GetList m_peak_Decimation_FactorX_GetList{};
    dyn_peak_Decimation_FactorY_GetList m_peak_Decimation_FactorY_GetList{};
    dyn_peak_Decimation_Set m_peak_Decimation_Set{};
    dyn_peak_Decimation_Get m_peak_Decimation_Get{};
    dyn_peak_Mirror_LeftRight_GetAccessStatus m_peak_Mirror_LeftRight_GetAccessStatus{};
    dyn_peak_Mirror_LeftRight_Enable m_peak_Mirror_LeftRight_Enable{};
    dyn_peak_Mirror_LeftRight_IsEnabled m_peak_Mirror_LeftRight_IsEnabled{};
    dyn_peak_Mirror_UpDown_GetAccessStatus m_peak_Mirror_UpDown_GetAccessStatus{};
    dyn_peak_Mirror_UpDown_Enable m_peak_Mirror_UpDown_Enable{};
    dyn_peak_Mirror_UpDown_IsEnabled m_peak_Mirror_UpDown_IsEnabled{};
    dyn_peak_CameraMemory_Area_GetAccessStatus m_peak_CameraMemory_Area_GetAccessStatus{};
    dyn_peak_CameraMemory_Area_GetList m_peak_CameraMemory_Area_GetList{};
    dyn_peak_CameraMemory_Area_Size_Get m_peak_CameraMemory_Area_Size_Get{};
    dyn_peak_CameraMemory_Area_Data_Clear m_peak_CameraMemory_Area_Data_Clear{};
    dyn_peak_CameraMemory_Area_Data_Write m_peak_CameraMemory_Area_Data_Write{};
    dyn_peak_CameraMemory_Area_Data_Read m_peak_CameraMemory_Area_Data_Read{};
    dyn_peak_GFA_EnableWriteAccess m_peak_GFA_EnableWriteAccess{};
    dyn_peak_GFA_IsWriteAccessEnabled m_peak_GFA_IsWriteAccessEnabled{};
    dyn_peak_GFA_Feature_GetAccessStatus m_peak_GFA_Feature_GetAccessStatus{};
    dyn_peak_GFA_Float_HasRange m_peak_GFA_Float_HasRange{};
    dyn_peak_GFA_Float_GetRange m_peak_GFA_Float_GetRange{};
    dyn_peak_GFA_Float_GetList m_peak_GFA_Float_GetList{};
    dyn_peak_GFA_Float_Set m_peak_GFA_Float_Set{};
    dyn_peak_GFA_Float_Get m_peak_GFA_Float_Get{};
    dyn_peak_GFA_Integer_HasRange m_peak_GFA_Integer_HasRange{};
    dyn_peak_GFA_Integer_GetRange m_peak_GFA_Integer_GetRange{};
    dyn_peak_GFA_Integer_GetList m_peak_GFA_Integer_GetList{};
    dyn_peak_GFA_Integer_Set m_peak_GFA_Integer_Set{};
    dyn_peak_GFA_Integer_Get m_peak_GFA_Integer_Get{};
    dyn_peak_GFA_Boolean_Set m_peak_GFA_Boolean_Set{};
    dyn_peak_GFA_Boolean_Get m_peak_GFA_Boolean_Get{};
    dyn_peak_GFA_String_Set m_peak_GFA_String_Set{};
    dyn_peak_GFA_String_Get m_peak_GFA_String_Get{};
    dyn_peak_GFA_Command_Execute m_peak_GFA_Command_Execute{};
    dyn_peak_GFA_Command_WaitForDone m_peak_GFA_Command_WaitForDone{};
    dyn_peak_GFA_Enumeration_GetList m_peak_GFA_Enumeration_GetList{};
    dyn_peak_GFA_EnumerationEntry_GetAccessStatus m_peak_GFA_EnumerationEntry_GetAccessStatus{};
    dyn_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue m_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue{};
    dyn_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue m_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue{};
    dyn_peak_GFA_Enumeration_Set m_peak_GFA_Enumeration_Set{};
    dyn_peak_GFA_Enumeration_SetBySymbolicValue m_peak_GFA_Enumeration_SetBySymbolicValue{};
    dyn_peak_GFA_Enumeration_SetByIntegerValue m_peak_GFA_Enumeration_SetByIntegerValue{};
    dyn_peak_GFA_Enumeration_Get m_peak_GFA_Enumeration_Get{};
    dyn_peak_GFA_Register_Set m_peak_GFA_Register_Set{};
    dyn_peak_GFA_Register_Get m_peak_GFA_Register_Get{};
    dyn_peak_GFA_Data_Write m_peak_GFA_Data_Write{};
    dyn_peak_GFA_Data_Read m_peak_GFA_Data_Read{};
    dyn_peak_IPL_PixelFormat_GetList m_peak_IPL_PixelFormat_GetList{};
    dyn_peak_IPL_PixelFormat_Set m_peak_IPL_PixelFormat_Set{};
    dyn_peak_IPL_PixelFormat_Get m_peak_IPL_PixelFormat_Get{};
    dyn_peak_IPL_Gain_GetRange m_peak_IPL_Gain_GetRange{};
    dyn_peak_IPL_Gain_Set m_peak_IPL_Gain_Set{};
    dyn_peak_IPL_Gain_Get m_peak_IPL_Gain_Get{};
    dyn_peak_IPL_Gamma_GetRange m_peak_IPL_Gamma_GetRange{};
    dyn_peak_IPL_Gamma_Set m_peak_IPL_Gamma_Set{};
    dyn_peak_IPL_Gamma_Get m_peak_IPL_Gamma_Get{};
    dyn_peak_IPL_ColorCorrection_Matrix_Set m_peak_IPL_ColorCorrection_Matrix_Set{};
    dyn_peak_IPL_ColorCorrection_Matrix_Get m_peak_IPL_ColorCorrection_Matrix_Get{};
    dyn_peak_IPL_ColorCorrection_Enable m_peak_IPL_ColorCorrection_Enable{};
    dyn_peak_IPL_ColorCorrection_IsEnabled m_peak_IPL_ColorCorrection_IsEnabled{};
    dyn_peak_IPL_AutoBrightness_Target_GetRange m_peak_IPL_AutoBrightness_Target_GetRange{};
    dyn_peak_IPL_AutoBrightness_Target_Set m_peak_IPL_AutoBrightness_Target_Set{};
    dyn_peak_IPL_AutoBrightness_Target_Get m_peak_IPL_AutoBrightness_Target_Get{};
    dyn_peak_IPL_AutoBrightness_TargetTolerance_GetRange m_peak_IPL_AutoBrightness_TargetTolerance_GetRange{};
    dyn_peak_IPL_AutoBrightness_TargetTolerance_Set m_peak_IPL_AutoBrightness_TargetTolerance_Set{};
    dyn_peak_IPL_AutoBrightness_TargetTolerance_Get m_peak_IPL_AutoBrightness_TargetTolerance_Get{};
    dyn_peak_IPL_AutoBrightness_TargetPercentile_GetRange m_peak_IPL_AutoBrightness_TargetPercentile_GetRange{};
    dyn_peak_IPL_AutoBrightness_TargetPercentile_Set m_peak_IPL_AutoBrightness_TargetPercentile_Set{};
    dyn_peak_IPL_AutoBrightness_TargetPercentile_Get m_peak_IPL_AutoBrightness_TargetPercentile_Get{};
    dyn_peak_IPL_AutoBrightness_ROI_Mode_Set m_peak_IPL_AutoBrightness_ROI_Mode_Set{};
    dyn_peak_IPL_AutoBrightness_ROI_Mode_Get m_peak_IPL_AutoBrightness_ROI_Mode_Get{};
    dyn_peak_IPL_AutoBrightness_ROI_Offset_GetRange m_peak_IPL_AutoBrightness_ROI_Offset_GetRange{};
    dyn_peak_IPL_AutoBrightness_ROI_Size_GetRange m_peak_IPL_AutoBrightness_ROI_Size_GetRange{};
    dyn_peak_IPL_AutoBrightness_ROI_Set m_peak_IPL_AutoBrightness_ROI_Set{};
    dyn_peak_IPL_AutoBrightness_ROI_Get m_peak_IPL_AutoBrightness_ROI_Get{};
    dyn_peak_IPL_AutoBrightness_Exposure_Mode_Set m_peak_IPL_AutoBrightness_Exposure_Mode_Set{};
    dyn_peak_IPL_AutoBrightness_Exposure_Mode_Get m_peak_IPL_AutoBrightness_Exposure_Mode_Get{};
    dyn_peak_IPL_AutoBrightness_Gain_Mode_Set m_peak_IPL_AutoBrightness_Gain_Mode_Set{};
    dyn_peak_IPL_AutoBrightness_Gain_Mode_Get m_peak_IPL_AutoBrightness_Gain_Mode_Get{};
    dyn_peak_IPL_AutoWhiteBalance_ROI_Mode_Set m_peak_IPL_AutoWhiteBalance_ROI_Mode_Set{};
    dyn_peak_IPL_AutoWhiteBalance_ROI_Mode_Get m_peak_IPL_AutoWhiteBalance_ROI_Mode_Get{};
    dyn_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange m_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange{};
    dyn_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange m_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange{};
    dyn_peak_IPL_AutoWhiteBalance_ROI_Set m_peak_IPL_AutoWhiteBalance_ROI_Set{};
    dyn_peak_IPL_AutoWhiteBalance_ROI_Get m_peak_IPL_AutoWhiteBalance_ROI_Get{};
    dyn_peak_IPL_AutoWhiteBalance_Mode_Set m_peak_IPL_AutoWhiteBalance_Mode_Set{};
    dyn_peak_IPL_AutoWhiteBalance_Mode_Get m_peak_IPL_AutoWhiteBalance_Mode_Get{};
    dyn_peak_IPL_HotpixelCorrection_Sensitivity_Set m_peak_IPL_HotpixelCorrection_Sensitivity_Set{};
    dyn_peak_IPL_HotpixelCorrection_Sensitivity_Get m_peak_IPL_HotpixelCorrection_Sensitivity_Get{};
    dyn_peak_IPL_HotpixelCorrection_GetList m_peak_IPL_HotpixelCorrection_GetList{};
    dyn_peak_IPL_HotpixelCorrection_SetList m_peak_IPL_HotpixelCorrection_SetList{};
    dyn_peak_IPL_HotpixelCorrection_ResetList m_peak_IPL_HotpixelCorrection_ResetList{};
    dyn_peak_IPL_HotpixelCorrection_Enable m_peak_IPL_HotpixelCorrection_Enable{};
    dyn_peak_IPL_HotpixelCorrection_IsEnabled m_peak_IPL_HotpixelCorrection_IsEnabled{};
    dyn_peak_IPL_Mirror_UpDown_Enable m_peak_IPL_Mirror_UpDown_Enable{};
    dyn_peak_IPL_Mirror_UpDown_IsEnabled m_peak_IPL_Mirror_UpDown_IsEnabled{};
    dyn_peak_IPL_Mirror_LeftRight_Enable m_peak_IPL_Mirror_LeftRight_Enable{};
    dyn_peak_IPL_Mirror_LeftRight_IsEnabled m_peak_IPL_Mirror_LeftRight_IsEnabled{};
    dyn_peak_IPL_ProcessFrame m_peak_IPL_ProcessFrame{};
    dyn_peak_IPL_ProcessFrameInplace m_peak_IPL_ProcessFrameInplace{};
    dyn_peak_VideoWriter_Open m_peak_VideoWriter_Open{};
    dyn_peak_VideoWriter_Close m_peak_VideoWriter_Close{};
    dyn_peak_VideoWriter_AddFrame m_peak_VideoWriter_AddFrame{};
    dyn_peak_VideoWriter_Container_GetEncoderList m_peak_VideoWriter_Container_GetEncoderList{};
    dyn_peak_VideoWriter_Encoder_GetPixelFormatList m_peak_VideoWriter_Encoder_GetPixelFormatList{};
    dyn_peak_VideoWriter_Encoder_GetContainerList m_peak_VideoWriter_Encoder_GetContainerList{};
    dyn_peak_VideoWriter_GetInfo m_peak_VideoWriter_GetInfo{};
    dyn_peak_VideoWriter_Container_Option_Set m_peak_VideoWriter_Container_Option_Set{};
    dyn_peak_VideoWriter_Container_Option_Get m_peak_VideoWriter_Container_Option_Get{};
    dyn_peak_VideoWriter_Encoder_Option_Set m_peak_VideoWriter_Encoder_Option_Set{};
    dyn_peak_VideoWriter_Encoder_Option_Get m_peak_VideoWriter_Encoder_Option_Get{};
    dyn_peak_VideoWriter_WaitUntilQueueEmpty m_peak_VideoWriter_WaitUntilQueueEmpty{};

};

inline void* import_function(void *module, const char* proc_name)
{
#ifdef __linux__
    return dlsym(module, proc_name);
#else
    return GetProcAddress(static_cast<HMODULE>(module), proc_name);
#endif
}
            
inline DynamicLoader::DynamicLoader()
{
#if defined _WIN32 || defined _WIN64
    size_t sz = 0;
    if (_wgetenv_s(&sz, NULL, 0, L"IDS_PEAK_COMFORT_SDK_PATH") == 0
        && sz > 0)
    {
        std::vector<wchar_t> env_ids_peak_comfort_c(sz);
        if (_wgetenv_s(&sz, env_ids_peak_comfort_c.data(), sz, L"IDS_PEAK_COMFORT_SDK_PATH") == 0)
        {
            if (_wgetenv_s(&sz, NULL, 0, L"PATH") == 0
                && sz > 0)
            {
                std::vector<wchar_t> env_path(sz);
                if (_wgetenv_s(&sz, env_path.data(), sz, L"PATH") == 0)
                {
                    std::wstring ids_peak_comfort_c_path(env_ids_peak_comfort_c.data());
#ifdef _WIN64
                    ids_peak_comfort_c_path.append(L"\\api\\lib\\x86_64");
#else
                    ids_peak_comfort_c_path.append(L"\\api\\lib\\x86_32");
#endif
                    std::wstring path_var(env_path.data());
                    path_var.append(L";").append(ids_peak_comfort_c_path);
                    _wputenv_s(L"PATH", path_var.c_str());
                }
            }
        }
    }
    
    loadLib("ids_peak_comfort_c.dll");
#else
    loadLib("libids_peak_comfort_c.so");
#endif
}

inline DynamicLoader::~DynamicLoader()
{
    if(m_handle != nullptr)
    {
        unload();
    }
}

inline bool DynamicLoader::isLoaded()
{
    auto&& inst = instance();
    return inst.m_handle != nullptr;
}

inline void DynamicLoader::unload()
{
    setPointers(false);
    
    if (m_handle != nullptr)
    {
#ifdef __linux__
        dlclose(m_handle);
#else
        FreeLibrary(static_cast<HMODULE>(m_handle));
#endif
    }
    m_handle = nullptr;
}


inline bool DynamicLoader::loadLib(const char* file)
{
    bool ret = false;
    
    if (file)
    {
#ifdef __linux__
        m_handle = dlopen(file, RTLD_NOW);
#else
        m_handle = LoadLibraryA(file);
#endif
        if (m_handle != nullptr)
        {
            try {
                setPointers(true);
                ret = true;
            } catch (const std::exception&) {
                unload();
                throw;
            }
        }
        else
        {
            throw std::runtime_error(std::string("Lib load failed: ") + file);
        }
    }
    else
    {
        throw std::runtime_error("Filename empty");
    }

    return ret;
}

inline bool DynamicLoader::setPointers(bool load)
{

    m_peak_Library_Init = (dyn_peak_Library_Init) (load ?  import_function(m_handle, "peak_Library_Init") : nullptr);
    if(m_peak_Library_Init == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Library_Init");
    }        

    m_peak_Library_Exit = (dyn_peak_Library_Exit) (load ?  import_function(m_handle, "peak_Library_Exit") : nullptr);
    if(m_peak_Library_Exit == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Library_Exit");
    }        

    m_peak_Library_GetVersion = (dyn_peak_Library_GetVersion) (load ?  import_function(m_handle, "peak_Library_GetVersion") : nullptr);
    if(m_peak_Library_GetVersion == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Library_GetVersion");
    }        

    m_peak_Library_GetLastError = (dyn_peak_Library_GetLastError) (load ?  import_function(m_handle, "peak_Library_GetLastError") : nullptr);
    if(m_peak_Library_GetLastError == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Library_GetLastError");
    }        

    m_peak_CameraList_Update = (dyn_peak_CameraList_Update) (load ?  import_function(m_handle, "peak_CameraList_Update") : nullptr);
    if(m_peak_CameraList_Update == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraList_Update");
    }        

    m_peak_CameraList_Get = (dyn_peak_CameraList_Get) (load ?  import_function(m_handle, "peak_CameraList_Get") : nullptr);
    if(m_peak_CameraList_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraList_Get");
    }        

    m_peak_Camera_ID_FromHandle = (dyn_peak_Camera_ID_FromHandle) (load ?  import_function(m_handle, "peak_Camera_ID_FromHandle") : nullptr);
    if(m_peak_Camera_ID_FromHandle == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_ID_FromHandle");
    }        

    m_peak_Camera_ID_FromSerialNumber = (dyn_peak_Camera_ID_FromSerialNumber) (load ?  import_function(m_handle, "peak_Camera_ID_FromSerialNumber") : nullptr);
    if(m_peak_Camera_ID_FromSerialNumber == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_ID_FromSerialNumber");
    }        

    m_peak_Camera_ID_FromMAC = (dyn_peak_Camera_ID_FromMAC) (load ?  import_function(m_handle, "peak_Camera_ID_FromMAC") : nullptr);
    if(m_peak_Camera_ID_FromMAC == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_ID_FromMAC");
    }        

    m_peak_Camera_GetAccessStatus = (dyn_peak_Camera_GetAccessStatus) (load ?  import_function(m_handle, "peak_Camera_GetAccessStatus") : nullptr);
    if(m_peak_Camera_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_GetAccessStatus");
    }        

    m_peak_Camera_GetDescriptor = (dyn_peak_Camera_GetDescriptor) (load ?  import_function(m_handle, "peak_Camera_GetDescriptor") : nullptr);
    if(m_peak_Camera_GetDescriptor == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_GetDescriptor");
    }        

    m_peak_Camera_Open = (dyn_peak_Camera_Open) (load ?  import_function(m_handle, "peak_Camera_Open") : nullptr);
    if(m_peak_Camera_Open == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_Open");
    }        

    m_peak_Camera_OpenFirstAvailable = (dyn_peak_Camera_OpenFirstAvailable) (load ?  import_function(m_handle, "peak_Camera_OpenFirstAvailable") : nullptr);
    if(m_peak_Camera_OpenFirstAvailable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_OpenFirstAvailable");
    }        

    m_peak_Camera_Close = (dyn_peak_Camera_Close) (load ?  import_function(m_handle, "peak_Camera_Close") : nullptr);
    if(m_peak_Camera_Close == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_Close");
    }        

    m_peak_Camera_ResetToDefaultSettings = (dyn_peak_Camera_ResetToDefaultSettings) (load ?  import_function(m_handle, "peak_Camera_ResetToDefaultSettings") : nullptr);
    if(m_peak_Camera_ResetToDefaultSettings == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Camera_ResetToDefaultSettings");
    }        

    m_peak_EthernetConfig_GetAccessStatus = (dyn_peak_EthernetConfig_GetAccessStatus) (load ?  import_function(m_handle, "peak_EthernetConfig_GetAccessStatus") : nullptr);
    if(m_peak_EthernetConfig_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_GetAccessStatus");
    }        

    m_peak_EthernetConfig_GetInfo = (dyn_peak_EthernetConfig_GetInfo) (load ?  import_function(m_handle, "peak_EthernetConfig_GetInfo") : nullptr);
    if(m_peak_EthernetConfig_GetInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_GetInfo");
    }        

    m_peak_EthernetConfig_DHCP_GetAccessStatus = (dyn_peak_EthernetConfig_DHCP_GetAccessStatus) (load ?  import_function(m_handle, "peak_EthernetConfig_DHCP_GetAccessStatus") : nullptr);
    if(m_peak_EthernetConfig_DHCP_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_DHCP_GetAccessStatus");
    }        

    m_peak_EthernetConfig_DHCP_Enable = (dyn_peak_EthernetConfig_DHCP_Enable) (load ?  import_function(m_handle, "peak_EthernetConfig_DHCP_Enable") : nullptr);
    if(m_peak_EthernetConfig_DHCP_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_DHCP_Enable");
    }        

    m_peak_EthernetConfig_DHCP_IsEnabled = (dyn_peak_EthernetConfig_DHCP_IsEnabled) (load ?  import_function(m_handle, "peak_EthernetConfig_DHCP_IsEnabled") : nullptr);
    if(m_peak_EthernetConfig_DHCP_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_DHCP_IsEnabled");
    }        

    m_peak_EthernetConfig_PersistentIP_GetAccessStatus = (dyn_peak_EthernetConfig_PersistentIP_GetAccessStatus) (load ?  import_function(m_handle, "peak_EthernetConfig_PersistentIP_GetAccessStatus") : nullptr);
    if(m_peak_EthernetConfig_PersistentIP_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_PersistentIP_GetAccessStatus");
    }        

    m_peak_EthernetConfig_PersistentIP_Set = (dyn_peak_EthernetConfig_PersistentIP_Set) (load ?  import_function(m_handle, "peak_EthernetConfig_PersistentIP_Set") : nullptr);
    if(m_peak_EthernetConfig_PersistentIP_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_PersistentIP_Set");
    }        

    m_peak_EthernetConfig_PersistentIP_Get = (dyn_peak_EthernetConfig_PersistentIP_Get) (load ?  import_function(m_handle, "peak_EthernetConfig_PersistentIP_Get") : nullptr);
    if(m_peak_EthernetConfig_PersistentIP_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_EthernetConfig_PersistentIP_Get");
    }        

    m_peak_Acquisition_Start = (dyn_peak_Acquisition_Start) (load ?  import_function(m_handle, "peak_Acquisition_Start") : nullptr);
    if(m_peak_Acquisition_Start == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Start");
    }        

    m_peak_Acquisition_Stop = (dyn_peak_Acquisition_Stop) (load ?  import_function(m_handle, "peak_Acquisition_Stop") : nullptr);
    if(m_peak_Acquisition_Stop == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Stop");
    }        

    m_peak_Acquisition_IsStarted = (dyn_peak_Acquisition_IsStarted) (load ?  import_function(m_handle, "peak_Acquisition_IsStarted") : nullptr);
    if(m_peak_Acquisition_IsStarted == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_IsStarted");
    }        

    m_peak_Acquisition_WaitForFrame = (dyn_peak_Acquisition_WaitForFrame) (load ?  import_function(m_handle, "peak_Acquisition_WaitForFrame") : nullptr);
    if(m_peak_Acquisition_WaitForFrame == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_WaitForFrame");
    }        

    m_peak_Acquisition_GetInfo = (dyn_peak_Acquisition_GetInfo) (load ?  import_function(m_handle, "peak_Acquisition_GetInfo") : nullptr);
    if(m_peak_Acquisition_GetInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_GetInfo");
    }        

    m_peak_Acquisition_Buffer_GetRequiredSize = (dyn_peak_Acquisition_Buffer_GetRequiredSize) (load ?  import_function(m_handle, "peak_Acquisition_Buffer_GetRequiredSize") : nullptr);
    if(m_peak_Acquisition_Buffer_GetRequiredSize == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Buffer_GetRequiredSize");
    }        

    m_peak_Acquisition_Buffer_GetRequiredCount = (dyn_peak_Acquisition_Buffer_GetRequiredCount) (load ?  import_function(m_handle, "peak_Acquisition_Buffer_GetRequiredCount") : nullptr);
    if(m_peak_Acquisition_Buffer_GetRequiredCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Buffer_GetRequiredCount");
    }        

    m_peak_Acquisition_Buffer_Announce = (dyn_peak_Acquisition_Buffer_Announce) (load ?  import_function(m_handle, "peak_Acquisition_Buffer_Announce") : nullptr);
    if(m_peak_Acquisition_Buffer_Announce == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Buffer_Announce");
    }        

    m_peak_Acquisition_Buffer_Revoke = (dyn_peak_Acquisition_Buffer_Revoke) (load ?  import_function(m_handle, "peak_Acquisition_Buffer_Revoke") : nullptr);
    if(m_peak_Acquisition_Buffer_Revoke == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Buffer_Revoke");
    }        

    m_peak_Acquisition_Buffer_RevokeAll = (dyn_peak_Acquisition_Buffer_RevokeAll) (load ?  import_function(m_handle, "peak_Acquisition_Buffer_RevokeAll") : nullptr);
    if(m_peak_Acquisition_Buffer_RevokeAll == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Acquisition_Buffer_RevokeAll");
    }        

    m_peak_PixelFormat_GetInfo = (dyn_peak_PixelFormat_GetInfo) (load ?  import_function(m_handle, "peak_PixelFormat_GetInfo") : nullptr);
    if(m_peak_PixelFormat_GetInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelFormat_GetInfo");
    }        

    m_peak_Frame_Release = (dyn_peak_Frame_Release) (load ?  import_function(m_handle, "peak_Frame_Release") : nullptr);
    if(m_peak_Frame_Release == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_Release");
    }        

    m_peak_Frame_GetInfo = (dyn_peak_Frame_GetInfo) (load ?  import_function(m_handle, "peak_Frame_GetInfo") : nullptr);
    if(m_peak_Frame_GetInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_GetInfo");
    }        

    m_peak_Frame_Type_Get = (dyn_peak_Frame_Type_Get) (load ?  import_function(m_handle, "peak_Frame_Type_Get") : nullptr);
    if(m_peak_Frame_Type_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_Type_Get");
    }        

    m_peak_Frame_Buffer_Get = (dyn_peak_Frame_Buffer_Get) (load ?  import_function(m_handle, "peak_Frame_Buffer_Get") : nullptr);
    if(m_peak_Frame_Buffer_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_Buffer_Get");
    }        

    m_peak_Frame_ID_Get = (dyn_peak_Frame_ID_Get) (load ?  import_function(m_handle, "peak_Frame_ID_Get") : nullptr);
    if(m_peak_Frame_ID_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_ID_Get");
    }        

    m_peak_Frame_Timestamp_Get = (dyn_peak_Frame_Timestamp_Get) (load ?  import_function(m_handle, "peak_Frame_Timestamp_Get") : nullptr);
    if(m_peak_Frame_Timestamp_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_Timestamp_Get");
    }        

    m_peak_Frame_ROI_Get = (dyn_peak_Frame_ROI_Get) (load ?  import_function(m_handle, "peak_Frame_ROI_Get") : nullptr);
    if(m_peak_Frame_ROI_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_ROI_Get");
    }        

    m_peak_Frame_PixelFormat_Get = (dyn_peak_Frame_PixelFormat_Get) (load ?  import_function(m_handle, "peak_Frame_PixelFormat_Get") : nullptr);
    if(m_peak_Frame_PixelFormat_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_PixelFormat_Get");
    }        

    m_peak_Frame_IsComplete = (dyn_peak_Frame_IsComplete) (load ?  import_function(m_handle, "peak_Frame_IsComplete") : nullptr);
    if(m_peak_Frame_IsComplete == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_IsComplete");
    }        

    m_peak_Frame_BytesExpected_Get = (dyn_peak_Frame_BytesExpected_Get) (load ?  import_function(m_handle, "peak_Frame_BytesExpected_Get") : nullptr);
    if(m_peak_Frame_BytesExpected_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_BytesExpected_Get");
    }        

    m_peak_Frame_BytesWritten_Get = (dyn_peak_Frame_BytesWritten_Get) (load ?  import_function(m_handle, "peak_Frame_BytesWritten_Get") : nullptr);
    if(m_peak_Frame_BytesWritten_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_BytesWritten_Get");
    }        

    m_peak_Frame_ProcessingTime_Get = (dyn_peak_Frame_ProcessingTime_Get) (load ?  import_function(m_handle, "peak_Frame_ProcessingTime_Get") : nullptr);
    if(m_peak_Frame_ProcessingTime_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Frame_ProcessingTime_Get");
    }        

    m_peak_CameraSettings_ParameterSet_GetAccessStatus = (dyn_peak_CameraSettings_ParameterSet_GetAccessStatus) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_GetAccessStatus") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_GetAccessStatus");
    }        

    m_peak_CameraSettings_ParameterSet_GetList = (dyn_peak_CameraSettings_ParameterSet_GetList) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_GetList") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_GetList");
    }        

    m_peak_CameraSettings_ParameterSet_Store = (dyn_peak_CameraSettings_ParameterSet_Store) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_Store") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_Store == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_Store");
    }        

    m_peak_CameraSettings_ParameterSet_Apply = (dyn_peak_CameraSettings_ParameterSet_Apply) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_Apply") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_Apply == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_Apply");
    }        

    m_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus = (dyn_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_Startup_GetAccessStatus") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_Startup_GetAccessStatus");
    }        

    m_peak_CameraSettings_ParameterSet_Startup_Set = (dyn_peak_CameraSettings_ParameterSet_Startup_Set) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_Startup_Set") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_Startup_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_Startup_Set");
    }        

    m_peak_CameraSettings_ParameterSet_Startup_Get = (dyn_peak_CameraSettings_ParameterSet_Startup_Get) (load ?  import_function(m_handle, "peak_CameraSettings_ParameterSet_Startup_Get") : nullptr);
    if(m_peak_CameraSettings_ParameterSet_Startup_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_ParameterSet_Startup_Get");
    }        

    m_peak_CameraSettings_DiskFile_GetAccessStatus = (dyn_peak_CameraSettings_DiskFile_GetAccessStatus) (load ?  import_function(m_handle, "peak_CameraSettings_DiskFile_GetAccessStatus") : nullptr);
    if(m_peak_CameraSettings_DiskFile_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_DiskFile_GetAccessStatus");
    }        

    m_peak_CameraSettings_DiskFile_Store = (dyn_peak_CameraSettings_DiskFile_Store) (load ?  import_function(m_handle, "peak_CameraSettings_DiskFile_Store") : nullptr);
    if(m_peak_CameraSettings_DiskFile_Store == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_DiskFile_Store");
    }        

    m_peak_CameraSettings_DiskFile_Apply = (dyn_peak_CameraSettings_DiskFile_Apply) (load ?  import_function(m_handle, "peak_CameraSettings_DiskFile_Apply") : nullptr);
    if(m_peak_CameraSettings_DiskFile_Apply == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraSettings_DiskFile_Apply");
    }        

    m_peak_FrameRate_GetAccessStatus = (dyn_peak_FrameRate_GetAccessStatus) (load ?  import_function(m_handle, "peak_FrameRate_GetAccessStatus") : nullptr);
    if(m_peak_FrameRate_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_FrameRate_GetAccessStatus");
    }        

    m_peak_FrameRate_GetRange = (dyn_peak_FrameRate_GetRange) (load ?  import_function(m_handle, "peak_FrameRate_GetRange") : nullptr);
    if(m_peak_FrameRate_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_FrameRate_GetRange");
    }        

    m_peak_FrameRate_Set = (dyn_peak_FrameRate_Set) (load ?  import_function(m_handle, "peak_FrameRate_Set") : nullptr);
    if(m_peak_FrameRate_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_FrameRate_Set");
    }        

    m_peak_FrameRate_Get = (dyn_peak_FrameRate_Get) (load ?  import_function(m_handle, "peak_FrameRate_Get") : nullptr);
    if(m_peak_FrameRate_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_FrameRate_Get");
    }        

    m_peak_ExposureTime_GetAccessStatus = (dyn_peak_ExposureTime_GetAccessStatus) (load ?  import_function(m_handle, "peak_ExposureTime_GetAccessStatus") : nullptr);
    if(m_peak_ExposureTime_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ExposureTime_GetAccessStatus");
    }        

    m_peak_ExposureTime_GetRange = (dyn_peak_ExposureTime_GetRange) (load ?  import_function(m_handle, "peak_ExposureTime_GetRange") : nullptr);
    if(m_peak_ExposureTime_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ExposureTime_GetRange");
    }        

    m_peak_ExposureTime_Set = (dyn_peak_ExposureTime_Set) (load ?  import_function(m_handle, "peak_ExposureTime_Set") : nullptr);
    if(m_peak_ExposureTime_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ExposureTime_Set");
    }        

    m_peak_ExposureTime_Get = (dyn_peak_ExposureTime_Get) (load ?  import_function(m_handle, "peak_ExposureTime_Get") : nullptr);
    if(m_peak_ExposureTime_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ExposureTime_Get");
    }        

    m_peak_PixelClock_GetAccessStatus = (dyn_peak_PixelClock_GetAccessStatus) (load ?  import_function(m_handle, "peak_PixelClock_GetAccessStatus") : nullptr);
    if(m_peak_PixelClock_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelClock_GetAccessStatus");
    }        

    m_peak_PixelClock_HasRange = (dyn_peak_PixelClock_HasRange) (load ?  import_function(m_handle, "peak_PixelClock_HasRange") : nullptr);
    if(m_peak_PixelClock_HasRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelClock_HasRange");
    }        

    m_peak_PixelClock_GetRange = (dyn_peak_PixelClock_GetRange) (load ?  import_function(m_handle, "peak_PixelClock_GetRange") : nullptr);
    if(m_peak_PixelClock_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelClock_GetRange");
    }        

    m_peak_PixelClock_GetList = (dyn_peak_PixelClock_GetList) (load ?  import_function(m_handle, "peak_PixelClock_GetList") : nullptr);
    if(m_peak_PixelClock_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelClock_GetList");
    }        

    m_peak_PixelClock_Set = (dyn_peak_PixelClock_Set) (load ?  import_function(m_handle, "peak_PixelClock_Set") : nullptr);
    if(m_peak_PixelClock_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelClock_Set");
    }        

    m_peak_PixelClock_Get = (dyn_peak_PixelClock_Get) (load ?  import_function(m_handle, "peak_PixelClock_Get") : nullptr);
    if(m_peak_PixelClock_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelClock_Get");
    }        

    m_peak_IOChannel_GetAccessStatus = (dyn_peak_IOChannel_GetAccessStatus) (load ?  import_function(m_handle, "peak_IOChannel_GetAccessStatus") : nullptr);
    if(m_peak_IOChannel_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_GetAccessStatus");
    }        

    m_peak_IOChannel_GetList = (dyn_peak_IOChannel_GetList) (load ?  import_function(m_handle, "peak_IOChannel_GetList") : nullptr);
    if(m_peak_IOChannel_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_GetList");
    }        

    m_peak_IOChannel_Level_GetAccessStatus = (dyn_peak_IOChannel_Level_GetAccessStatus) (load ?  import_function(m_handle, "peak_IOChannel_Level_GetAccessStatus") : nullptr);
    if(m_peak_IOChannel_Level_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_Level_GetAccessStatus");
    }        

    m_peak_IOChannel_Level_IsHigh = (dyn_peak_IOChannel_Level_IsHigh) (load ?  import_function(m_handle, "peak_IOChannel_Level_IsHigh") : nullptr);
    if(m_peak_IOChannel_Level_IsHigh == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_Level_IsHigh");
    }        

    m_peak_IOChannel_Inverter_GetAccessStatus = (dyn_peak_IOChannel_Inverter_GetAccessStatus) (load ?  import_function(m_handle, "peak_IOChannel_Inverter_GetAccessStatus") : nullptr);
    if(m_peak_IOChannel_Inverter_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_Inverter_GetAccessStatus");
    }        

    m_peak_IOChannel_Inverter_Enable = (dyn_peak_IOChannel_Inverter_Enable) (load ?  import_function(m_handle, "peak_IOChannel_Inverter_Enable") : nullptr);
    if(m_peak_IOChannel_Inverter_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_Inverter_Enable");
    }        

    m_peak_IOChannel_Inverter_IsEnabled = (dyn_peak_IOChannel_Inverter_IsEnabled) (load ?  import_function(m_handle, "peak_IOChannel_Inverter_IsEnabled") : nullptr);
    if(m_peak_IOChannel_Inverter_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_Inverter_IsEnabled");
    }        

    m_peak_IOChannel_NoiseFilter_GetAccessStatus = (dyn_peak_IOChannel_NoiseFilter_GetAccessStatus) (load ?  import_function(m_handle, "peak_IOChannel_NoiseFilter_GetAccessStatus") : nullptr);
    if(m_peak_IOChannel_NoiseFilter_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_NoiseFilter_GetAccessStatus");
    }        

    m_peak_IOChannel_NoiseFilter_Enable = (dyn_peak_IOChannel_NoiseFilter_Enable) (load ?  import_function(m_handle, "peak_IOChannel_NoiseFilter_Enable") : nullptr);
    if(m_peak_IOChannel_NoiseFilter_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_NoiseFilter_Enable");
    }        

    m_peak_IOChannel_NoiseFilter_IsEnabled = (dyn_peak_IOChannel_NoiseFilter_IsEnabled) (load ?  import_function(m_handle, "peak_IOChannel_NoiseFilter_IsEnabled") : nullptr);
    if(m_peak_IOChannel_NoiseFilter_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_NoiseFilter_IsEnabled");
    }        

    m_peak_IOChannel_NoiseFilter_Duration_GetRange = (dyn_peak_IOChannel_NoiseFilter_Duration_GetRange) (load ?  import_function(m_handle, "peak_IOChannel_NoiseFilter_Duration_GetRange") : nullptr);
    if(m_peak_IOChannel_NoiseFilter_Duration_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_NoiseFilter_Duration_GetRange");
    }        

    m_peak_IOChannel_NoiseFilter_Duration_Set = (dyn_peak_IOChannel_NoiseFilter_Duration_Set) (load ?  import_function(m_handle, "peak_IOChannel_NoiseFilter_Duration_Set") : nullptr);
    if(m_peak_IOChannel_NoiseFilter_Duration_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_NoiseFilter_Duration_Set");
    }        

    m_peak_IOChannel_NoiseFilter_Duration_Get = (dyn_peak_IOChannel_NoiseFilter_Duration_Get) (load ?  import_function(m_handle, "peak_IOChannel_NoiseFilter_Duration_Get") : nullptr);
    if(m_peak_IOChannel_NoiseFilter_Duration_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IOChannel_NoiseFilter_Duration_Get");
    }        

    m_peak_Trigger_GetAccessStatus = (dyn_peak_Trigger_GetAccessStatus) (load ?  import_function(m_handle, "peak_Trigger_GetAccessStatus") : nullptr);
    if(m_peak_Trigger_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_GetAccessStatus");
    }        

    m_peak_Trigger_Enable = (dyn_peak_Trigger_Enable) (load ?  import_function(m_handle, "peak_Trigger_Enable") : nullptr);
    if(m_peak_Trigger_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Enable");
    }        

    m_peak_Trigger_IsEnabled = (dyn_peak_Trigger_IsEnabled) (load ?  import_function(m_handle, "peak_Trigger_IsEnabled") : nullptr);
    if(m_peak_Trigger_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_IsEnabled");
    }        

    m_peak_Trigger_IsExecutable = (dyn_peak_Trigger_IsExecutable) (load ?  import_function(m_handle, "peak_Trigger_IsExecutable") : nullptr);
    if(m_peak_Trigger_IsExecutable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_IsExecutable");
    }        

    m_peak_Trigger_Execute = (dyn_peak_Trigger_Execute) (load ?  import_function(m_handle, "peak_Trigger_Execute") : nullptr);
    if(m_peak_Trigger_Execute == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Execute");
    }        

    m_peak_Trigger_Mode_GetAccessStatus = (dyn_peak_Trigger_Mode_GetAccessStatus) (load ?  import_function(m_handle, "peak_Trigger_Mode_GetAccessStatus") : nullptr);
    if(m_peak_Trigger_Mode_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Mode_GetAccessStatus");
    }        

    m_peak_Trigger_Mode_Set = (dyn_peak_Trigger_Mode_Set) (load ?  import_function(m_handle, "peak_Trigger_Mode_Set") : nullptr);
    if(m_peak_Trigger_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Mode_Set");
    }        

    m_peak_Trigger_Mode_Get = (dyn_peak_Trigger_Mode_Get) (load ?  import_function(m_handle, "peak_Trigger_Mode_Get") : nullptr);
    if(m_peak_Trigger_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Mode_Get");
    }        

    m_peak_Trigger_Edge_GetAccessStatus = (dyn_peak_Trigger_Edge_GetAccessStatus) (load ?  import_function(m_handle, "peak_Trigger_Edge_GetAccessStatus") : nullptr);
    if(m_peak_Trigger_Edge_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Edge_GetAccessStatus");
    }        

    m_peak_Trigger_Edge_GetList = (dyn_peak_Trigger_Edge_GetList) (load ?  import_function(m_handle, "peak_Trigger_Edge_GetList") : nullptr);
    if(m_peak_Trigger_Edge_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Edge_GetList");
    }        

    m_peak_Trigger_Edge_Set = (dyn_peak_Trigger_Edge_Set) (load ?  import_function(m_handle, "peak_Trigger_Edge_Set") : nullptr);
    if(m_peak_Trigger_Edge_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Edge_Set");
    }        

    m_peak_Trigger_Edge_Get = (dyn_peak_Trigger_Edge_Get) (load ?  import_function(m_handle, "peak_Trigger_Edge_Get") : nullptr);
    if(m_peak_Trigger_Edge_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Edge_Get");
    }        

    m_peak_Trigger_Delay_GetAccessStatus = (dyn_peak_Trigger_Delay_GetAccessStatus) (load ?  import_function(m_handle, "peak_Trigger_Delay_GetAccessStatus") : nullptr);
    if(m_peak_Trigger_Delay_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Delay_GetAccessStatus");
    }        

    m_peak_Trigger_Delay_GetRange = (dyn_peak_Trigger_Delay_GetRange) (load ?  import_function(m_handle, "peak_Trigger_Delay_GetRange") : nullptr);
    if(m_peak_Trigger_Delay_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Delay_GetRange");
    }        

    m_peak_Trigger_Delay_Set = (dyn_peak_Trigger_Delay_Set) (load ?  import_function(m_handle, "peak_Trigger_Delay_Set") : nullptr);
    if(m_peak_Trigger_Delay_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Delay_Set");
    }        

    m_peak_Trigger_Delay_Get = (dyn_peak_Trigger_Delay_Get) (load ?  import_function(m_handle, "peak_Trigger_Delay_Get") : nullptr);
    if(m_peak_Trigger_Delay_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Delay_Get");
    }        

    m_peak_Trigger_Divider_GetAccessStatus = (dyn_peak_Trigger_Divider_GetAccessStatus) (load ?  import_function(m_handle, "peak_Trigger_Divider_GetAccessStatus") : nullptr);
    if(m_peak_Trigger_Divider_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Divider_GetAccessStatus");
    }        

    m_peak_Trigger_Divider_GetRange = (dyn_peak_Trigger_Divider_GetRange) (load ?  import_function(m_handle, "peak_Trigger_Divider_GetRange") : nullptr);
    if(m_peak_Trigger_Divider_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Divider_GetRange");
    }        

    m_peak_Trigger_Divider_Set = (dyn_peak_Trigger_Divider_Set) (load ?  import_function(m_handle, "peak_Trigger_Divider_Set") : nullptr);
    if(m_peak_Trigger_Divider_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Divider_Set");
    }        

    m_peak_Trigger_Divider_Get = (dyn_peak_Trigger_Divider_Get) (load ?  import_function(m_handle, "peak_Trigger_Divider_Get") : nullptr);
    if(m_peak_Trigger_Divider_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Divider_Get");
    }        

    m_peak_Trigger_Burst_GetAccessStatus = (dyn_peak_Trigger_Burst_GetAccessStatus) (load ?  import_function(m_handle, "peak_Trigger_Burst_GetAccessStatus") : nullptr);
    if(m_peak_Trigger_Burst_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Burst_GetAccessStatus");
    }        

    m_peak_Trigger_Burst_GetRange = (dyn_peak_Trigger_Burst_GetRange) (load ?  import_function(m_handle, "peak_Trigger_Burst_GetRange") : nullptr);
    if(m_peak_Trigger_Burst_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Burst_GetRange");
    }        

    m_peak_Trigger_Burst_Set = (dyn_peak_Trigger_Burst_Set) (load ?  import_function(m_handle, "peak_Trigger_Burst_Set") : nullptr);
    if(m_peak_Trigger_Burst_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Burst_Set");
    }        

    m_peak_Trigger_Burst_Get = (dyn_peak_Trigger_Burst_Get) (load ?  import_function(m_handle, "peak_Trigger_Burst_Get") : nullptr);
    if(m_peak_Trigger_Burst_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Trigger_Burst_Get");
    }        

    m_peak_Flash_GetAccessStatus = (dyn_peak_Flash_GetAccessStatus) (load ?  import_function(m_handle, "peak_Flash_GetAccessStatus") : nullptr);
    if(m_peak_Flash_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_GetAccessStatus");
    }        

    m_peak_Flash_Enable = (dyn_peak_Flash_Enable) (load ?  import_function(m_handle, "peak_Flash_Enable") : nullptr);
    if(m_peak_Flash_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Enable");
    }        

    m_peak_Flash_IsEnabled = (dyn_peak_Flash_IsEnabled) (load ?  import_function(m_handle, "peak_Flash_IsEnabled") : nullptr);
    if(m_peak_Flash_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_IsEnabled");
    }        

    m_peak_Flash_Mode_GetAccessStatus = (dyn_peak_Flash_Mode_GetAccessStatus) (load ?  import_function(m_handle, "peak_Flash_Mode_GetAccessStatus") : nullptr);
    if(m_peak_Flash_Mode_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Mode_GetAccessStatus");
    }        

    m_peak_Flash_Mode_Set = (dyn_peak_Flash_Mode_Set) (load ?  import_function(m_handle, "peak_Flash_Mode_Set") : nullptr);
    if(m_peak_Flash_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Mode_Set");
    }        

    m_peak_Flash_Mode_Get = (dyn_peak_Flash_Mode_Get) (load ?  import_function(m_handle, "peak_Flash_Mode_Get") : nullptr);
    if(m_peak_Flash_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Mode_Get");
    }        

    m_peak_Flash_StartDelay_GetAccessStatus = (dyn_peak_Flash_StartDelay_GetAccessStatus) (load ?  import_function(m_handle, "peak_Flash_StartDelay_GetAccessStatus") : nullptr);
    if(m_peak_Flash_StartDelay_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_StartDelay_GetAccessStatus");
    }        

    m_peak_Flash_StartDelay_GetRange = (dyn_peak_Flash_StartDelay_GetRange) (load ?  import_function(m_handle, "peak_Flash_StartDelay_GetRange") : nullptr);
    if(m_peak_Flash_StartDelay_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_StartDelay_GetRange");
    }        

    m_peak_Flash_StartDelay_Set = (dyn_peak_Flash_StartDelay_Set) (load ?  import_function(m_handle, "peak_Flash_StartDelay_Set") : nullptr);
    if(m_peak_Flash_StartDelay_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_StartDelay_Set");
    }        

    m_peak_Flash_StartDelay_Get = (dyn_peak_Flash_StartDelay_Get) (load ?  import_function(m_handle, "peak_Flash_StartDelay_Get") : nullptr);
    if(m_peak_Flash_StartDelay_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_StartDelay_Get");
    }        

    m_peak_Flash_EndDelay_GetAccessStatus = (dyn_peak_Flash_EndDelay_GetAccessStatus) (load ?  import_function(m_handle, "peak_Flash_EndDelay_GetAccessStatus") : nullptr);
    if(m_peak_Flash_EndDelay_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_EndDelay_GetAccessStatus");
    }        

    m_peak_Flash_EndDelay_GetRange = (dyn_peak_Flash_EndDelay_GetRange) (load ?  import_function(m_handle, "peak_Flash_EndDelay_GetRange") : nullptr);
    if(m_peak_Flash_EndDelay_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_EndDelay_GetRange");
    }        

    m_peak_Flash_EndDelay_Set = (dyn_peak_Flash_EndDelay_Set) (load ?  import_function(m_handle, "peak_Flash_EndDelay_Set") : nullptr);
    if(m_peak_Flash_EndDelay_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_EndDelay_Set");
    }        

    m_peak_Flash_EndDelay_Get = (dyn_peak_Flash_EndDelay_Get) (load ?  import_function(m_handle, "peak_Flash_EndDelay_Get") : nullptr);
    if(m_peak_Flash_EndDelay_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_EndDelay_Get");
    }        

    m_peak_Flash_Duration_GetAccessStatus = (dyn_peak_Flash_Duration_GetAccessStatus) (load ?  import_function(m_handle, "peak_Flash_Duration_GetAccessStatus") : nullptr);
    if(m_peak_Flash_Duration_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Duration_GetAccessStatus");
    }        

    m_peak_Flash_Duration_GetRange = (dyn_peak_Flash_Duration_GetRange) (load ?  import_function(m_handle, "peak_Flash_Duration_GetRange") : nullptr);
    if(m_peak_Flash_Duration_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Duration_GetRange");
    }        

    m_peak_Flash_Duration_Set = (dyn_peak_Flash_Duration_Set) (load ?  import_function(m_handle, "peak_Flash_Duration_Set") : nullptr);
    if(m_peak_Flash_Duration_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Duration_Set");
    }        

    m_peak_Flash_Duration_Get = (dyn_peak_Flash_Duration_Get) (load ?  import_function(m_handle, "peak_Flash_Duration_Get") : nullptr);
    if(m_peak_Flash_Duration_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Flash_Duration_Get");
    }        

    m_peak_PixelFormat_GetAccessStatus = (dyn_peak_PixelFormat_GetAccessStatus) (load ?  import_function(m_handle, "peak_PixelFormat_GetAccessStatus") : nullptr);
    if(m_peak_PixelFormat_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelFormat_GetAccessStatus");
    }        

    m_peak_PixelFormat_GetList = (dyn_peak_PixelFormat_GetList) (load ?  import_function(m_handle, "peak_PixelFormat_GetList") : nullptr);
    if(m_peak_PixelFormat_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelFormat_GetList");
    }        

    m_peak_PixelFormat_Set = (dyn_peak_PixelFormat_Set) (load ?  import_function(m_handle, "peak_PixelFormat_Set") : nullptr);
    if(m_peak_PixelFormat_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelFormat_Set");
    }        

    m_peak_PixelFormat_Get = (dyn_peak_PixelFormat_Get) (load ?  import_function(m_handle, "peak_PixelFormat_Get") : nullptr);
    if(m_peak_PixelFormat_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_PixelFormat_Get");
    }        

    m_peak_Gain_GetAccessStatus = (dyn_peak_Gain_GetAccessStatus) (load ?  import_function(m_handle, "peak_Gain_GetAccessStatus") : nullptr);
    if(m_peak_Gain_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gain_GetAccessStatus");
    }        

    m_peak_Gain_GetChannelList = (dyn_peak_Gain_GetChannelList) (load ?  import_function(m_handle, "peak_Gain_GetChannelList") : nullptr);
    if(m_peak_Gain_GetChannelList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gain_GetChannelList");
    }        

    m_peak_Gain_GetRange = (dyn_peak_Gain_GetRange) (load ?  import_function(m_handle, "peak_Gain_GetRange") : nullptr);
    if(m_peak_Gain_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gain_GetRange");
    }        

    m_peak_Gain_Set = (dyn_peak_Gain_Set) (load ?  import_function(m_handle, "peak_Gain_Set") : nullptr);
    if(m_peak_Gain_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gain_Set");
    }        

    m_peak_Gain_Get = (dyn_peak_Gain_Get) (load ?  import_function(m_handle, "peak_Gain_Get") : nullptr);
    if(m_peak_Gain_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gain_Get");
    }        

    m_peak_Gamma_GetAccessStatus = (dyn_peak_Gamma_GetAccessStatus) (load ?  import_function(m_handle, "peak_Gamma_GetAccessStatus") : nullptr);
    if(m_peak_Gamma_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gamma_GetAccessStatus");
    }        

    m_peak_Gamma_GetRange = (dyn_peak_Gamma_GetRange) (load ?  import_function(m_handle, "peak_Gamma_GetRange") : nullptr);
    if(m_peak_Gamma_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gamma_GetRange");
    }        

    m_peak_Gamma_Set = (dyn_peak_Gamma_Set) (load ?  import_function(m_handle, "peak_Gamma_Set") : nullptr);
    if(m_peak_Gamma_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gamma_Set");
    }        

    m_peak_Gamma_Get = (dyn_peak_Gamma_Get) (load ?  import_function(m_handle, "peak_Gamma_Get") : nullptr);
    if(m_peak_Gamma_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Gamma_Get");
    }        

    m_peak_ColorCorrection_GetAccessStatus = (dyn_peak_ColorCorrection_GetAccessStatus) (load ?  import_function(m_handle, "peak_ColorCorrection_GetAccessStatus") : nullptr);
    if(m_peak_ColorCorrection_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_GetAccessStatus");
    }        

    m_peak_ColorCorrection_Mode_GetList = (dyn_peak_ColorCorrection_Mode_GetList) (load ?  import_function(m_handle, "peak_ColorCorrection_Mode_GetList") : nullptr);
    if(m_peak_ColorCorrection_Mode_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Mode_GetList");
    }        

    m_peak_ColorCorrection_Mode_Set = (dyn_peak_ColorCorrection_Mode_Set) (load ?  import_function(m_handle, "peak_ColorCorrection_Mode_Set") : nullptr);
    if(m_peak_ColorCorrection_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Mode_Set");
    }        

    m_peak_ColorCorrection_Mode_Get = (dyn_peak_ColorCorrection_Mode_Get) (load ?  import_function(m_handle, "peak_ColorCorrection_Mode_Get") : nullptr);
    if(m_peak_ColorCorrection_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Mode_Get");
    }        

    m_peak_ColorCorrection_Matrix_GetAccessStatus = (dyn_peak_ColorCorrection_Matrix_GetAccessStatus) (load ?  import_function(m_handle, "peak_ColorCorrection_Matrix_GetAccessStatus") : nullptr);
    if(m_peak_ColorCorrection_Matrix_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Matrix_GetAccessStatus");
    }        

    m_peak_ColorCorrection_Matrix_GetRange = (dyn_peak_ColorCorrection_Matrix_GetRange) (load ?  import_function(m_handle, "peak_ColorCorrection_Matrix_GetRange") : nullptr);
    if(m_peak_ColorCorrection_Matrix_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Matrix_GetRange");
    }        

    m_peak_ColorCorrection_Matrix_Set = (dyn_peak_ColorCorrection_Matrix_Set) (load ?  import_function(m_handle, "peak_ColorCorrection_Matrix_Set") : nullptr);
    if(m_peak_ColorCorrection_Matrix_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Matrix_Set");
    }        

    m_peak_ColorCorrection_Matrix_Get = (dyn_peak_ColorCorrection_Matrix_Get) (load ?  import_function(m_handle, "peak_ColorCorrection_Matrix_Get") : nullptr);
    if(m_peak_ColorCorrection_Matrix_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Matrix_Get");
    }        

    m_peak_ColorCorrection_Enable = (dyn_peak_ColorCorrection_Enable) (load ?  import_function(m_handle, "peak_ColorCorrection_Enable") : nullptr);
    if(m_peak_ColorCorrection_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_Enable");
    }        

    m_peak_ColorCorrection_IsEnabled = (dyn_peak_ColorCorrection_IsEnabled) (load ?  import_function(m_handle, "peak_ColorCorrection_IsEnabled") : nullptr);
    if(m_peak_ColorCorrection_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ColorCorrection_IsEnabled");
    }        

    m_peak_AutoBrightness_GetAccessStatus = (dyn_peak_AutoBrightness_GetAccessStatus) (load ?  import_function(m_handle, "peak_AutoBrightness_GetAccessStatus") : nullptr);
    if(m_peak_AutoBrightness_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_GetAccessStatus");
    }        

    m_peak_AutoBrightness_Target_GetRange = (dyn_peak_AutoBrightness_Target_GetRange) (load ?  import_function(m_handle, "peak_AutoBrightness_Target_GetRange") : nullptr);
    if(m_peak_AutoBrightness_Target_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Target_GetRange");
    }        

    m_peak_AutoBrightness_Target_Set = (dyn_peak_AutoBrightness_Target_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_Target_Set") : nullptr);
    if(m_peak_AutoBrightness_Target_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Target_Set");
    }        

    m_peak_AutoBrightness_Target_Get = (dyn_peak_AutoBrightness_Target_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_Target_Get") : nullptr);
    if(m_peak_AutoBrightness_Target_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Target_Get");
    }        

    m_peak_AutoBrightness_TargetTolerance_GetRange = (dyn_peak_AutoBrightness_TargetTolerance_GetRange) (load ?  import_function(m_handle, "peak_AutoBrightness_TargetTolerance_GetRange") : nullptr);
    if(m_peak_AutoBrightness_TargetTolerance_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_TargetTolerance_GetRange");
    }        

    m_peak_AutoBrightness_TargetTolerance_Set = (dyn_peak_AutoBrightness_TargetTolerance_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_TargetTolerance_Set") : nullptr);
    if(m_peak_AutoBrightness_TargetTolerance_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_TargetTolerance_Set");
    }        

    m_peak_AutoBrightness_TargetTolerance_Get = (dyn_peak_AutoBrightness_TargetTolerance_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_TargetTolerance_Get") : nullptr);
    if(m_peak_AutoBrightness_TargetTolerance_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_TargetTolerance_Get");
    }        

    m_peak_AutoBrightness_TargetPercentile_GetRange = (dyn_peak_AutoBrightness_TargetPercentile_GetRange) (load ?  import_function(m_handle, "peak_AutoBrightness_TargetPercentile_GetRange") : nullptr);
    if(m_peak_AutoBrightness_TargetPercentile_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_TargetPercentile_GetRange");
    }        

    m_peak_AutoBrightness_TargetPercentile_Set = (dyn_peak_AutoBrightness_TargetPercentile_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_TargetPercentile_Set") : nullptr);
    if(m_peak_AutoBrightness_TargetPercentile_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_TargetPercentile_Set");
    }        

    m_peak_AutoBrightness_TargetPercentile_Get = (dyn_peak_AutoBrightness_TargetPercentile_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_TargetPercentile_Get") : nullptr);
    if(m_peak_AutoBrightness_TargetPercentile_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_TargetPercentile_Get");
    }        

    m_peak_AutoBrightness_ROI_Mode_Set = (dyn_peak_AutoBrightness_ROI_Mode_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_ROI_Mode_Set") : nullptr);
    if(m_peak_AutoBrightness_ROI_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_ROI_Mode_Set");
    }        

    m_peak_AutoBrightness_ROI_Mode_Get = (dyn_peak_AutoBrightness_ROI_Mode_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_ROI_Mode_Get") : nullptr);
    if(m_peak_AutoBrightness_ROI_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_ROI_Mode_Get");
    }        

    m_peak_AutoBrightness_ROI_Offset_GetRange = (dyn_peak_AutoBrightness_ROI_Offset_GetRange) (load ?  import_function(m_handle, "peak_AutoBrightness_ROI_Offset_GetRange") : nullptr);
    if(m_peak_AutoBrightness_ROI_Offset_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_ROI_Offset_GetRange");
    }        

    m_peak_AutoBrightness_ROI_Size_GetRange = (dyn_peak_AutoBrightness_ROI_Size_GetRange) (load ?  import_function(m_handle, "peak_AutoBrightness_ROI_Size_GetRange") : nullptr);
    if(m_peak_AutoBrightness_ROI_Size_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_ROI_Size_GetRange");
    }        

    m_peak_AutoBrightness_ROI_Set = (dyn_peak_AutoBrightness_ROI_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_ROI_Set") : nullptr);
    if(m_peak_AutoBrightness_ROI_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_ROI_Set");
    }        

    m_peak_AutoBrightness_ROI_Get = (dyn_peak_AutoBrightness_ROI_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_ROI_Get") : nullptr);
    if(m_peak_AutoBrightness_ROI_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_ROI_Get");
    }        

    m_peak_AutoBrightness_Exposure_GetAccessStatus = (dyn_peak_AutoBrightness_Exposure_GetAccessStatus) (load ?  import_function(m_handle, "peak_AutoBrightness_Exposure_GetAccessStatus") : nullptr);
    if(m_peak_AutoBrightness_Exposure_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Exposure_GetAccessStatus");
    }        

    m_peak_AutoBrightness_Exposure_Mode_Set = (dyn_peak_AutoBrightness_Exposure_Mode_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_Exposure_Mode_Set") : nullptr);
    if(m_peak_AutoBrightness_Exposure_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Exposure_Mode_Set");
    }        

    m_peak_AutoBrightness_Exposure_Mode_Get = (dyn_peak_AutoBrightness_Exposure_Mode_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_Exposure_Mode_Get") : nullptr);
    if(m_peak_AutoBrightness_Exposure_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Exposure_Mode_Get");
    }        

    m_peak_AutoBrightness_Gain_GetAccessStatus = (dyn_peak_AutoBrightness_Gain_GetAccessStatus) (load ?  import_function(m_handle, "peak_AutoBrightness_Gain_GetAccessStatus") : nullptr);
    if(m_peak_AutoBrightness_Gain_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Gain_GetAccessStatus");
    }        

    m_peak_AutoBrightness_Gain_Mode_Set = (dyn_peak_AutoBrightness_Gain_Mode_Set) (load ?  import_function(m_handle, "peak_AutoBrightness_Gain_Mode_Set") : nullptr);
    if(m_peak_AutoBrightness_Gain_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Gain_Mode_Set");
    }        

    m_peak_AutoBrightness_Gain_Mode_Get = (dyn_peak_AutoBrightness_Gain_Mode_Get) (load ?  import_function(m_handle, "peak_AutoBrightness_Gain_Mode_Get") : nullptr);
    if(m_peak_AutoBrightness_Gain_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoBrightness_Gain_Mode_Get");
    }        

    m_peak_AutoWhiteBalance_GetAccessStatus = (dyn_peak_AutoWhiteBalance_GetAccessStatus) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_GetAccessStatus") : nullptr);
    if(m_peak_AutoWhiteBalance_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_GetAccessStatus");
    }        

    m_peak_AutoWhiteBalance_ROI_Mode_Set = (dyn_peak_AutoWhiteBalance_ROI_Mode_Set) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_ROI_Mode_Set") : nullptr);
    if(m_peak_AutoWhiteBalance_ROI_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_ROI_Mode_Set");
    }        

    m_peak_AutoWhiteBalance_ROI_Mode_Get = (dyn_peak_AutoWhiteBalance_ROI_Mode_Get) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_ROI_Mode_Get") : nullptr);
    if(m_peak_AutoWhiteBalance_ROI_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_ROI_Mode_Get");
    }        

    m_peak_AutoWhiteBalance_ROI_Offset_GetRange = (dyn_peak_AutoWhiteBalance_ROI_Offset_GetRange) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_ROI_Offset_GetRange") : nullptr);
    if(m_peak_AutoWhiteBalance_ROI_Offset_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_ROI_Offset_GetRange");
    }        

    m_peak_AutoWhiteBalance_ROI_Size_GetRange = (dyn_peak_AutoWhiteBalance_ROI_Size_GetRange) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_ROI_Size_GetRange") : nullptr);
    if(m_peak_AutoWhiteBalance_ROI_Size_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_ROI_Size_GetRange");
    }        

    m_peak_AutoWhiteBalance_ROI_Set = (dyn_peak_AutoWhiteBalance_ROI_Set) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_ROI_Set") : nullptr);
    if(m_peak_AutoWhiteBalance_ROI_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_ROI_Set");
    }        

    m_peak_AutoWhiteBalance_ROI_Get = (dyn_peak_AutoWhiteBalance_ROI_Get) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_ROI_Get") : nullptr);
    if(m_peak_AutoWhiteBalance_ROI_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_ROI_Get");
    }        

    m_peak_AutoWhiteBalance_Mode_Set = (dyn_peak_AutoWhiteBalance_Mode_Set) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_Mode_Set") : nullptr);
    if(m_peak_AutoWhiteBalance_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_Mode_Set");
    }        

    m_peak_AutoWhiteBalance_Mode_Get = (dyn_peak_AutoWhiteBalance_Mode_Get) (load ?  import_function(m_handle, "peak_AutoWhiteBalance_Mode_Get") : nullptr);
    if(m_peak_AutoWhiteBalance_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_AutoWhiteBalance_Mode_Get");
    }        

    m_peak_ROI_GetAccessStatus = (dyn_peak_ROI_GetAccessStatus) (load ?  import_function(m_handle, "peak_ROI_GetAccessStatus") : nullptr);
    if(m_peak_ROI_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ROI_GetAccessStatus");
    }        

    m_peak_ROI_Offset_GetRange = (dyn_peak_ROI_Offset_GetRange) (load ?  import_function(m_handle, "peak_ROI_Offset_GetRange") : nullptr);
    if(m_peak_ROI_Offset_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ROI_Offset_GetRange");
    }        

    m_peak_ROI_Size_GetRange = (dyn_peak_ROI_Size_GetRange) (load ?  import_function(m_handle, "peak_ROI_Size_GetRange") : nullptr);
    if(m_peak_ROI_Size_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ROI_Size_GetRange");
    }        

    m_peak_ROI_Set = (dyn_peak_ROI_Set) (load ?  import_function(m_handle, "peak_ROI_Set") : nullptr);
    if(m_peak_ROI_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ROI_Set");
    }        

    m_peak_ROI_Get = (dyn_peak_ROI_Get) (load ?  import_function(m_handle, "peak_ROI_Get") : nullptr);
    if(m_peak_ROI_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_ROI_Get");
    }        

    m_peak_Binning_GetAccessStatus = (dyn_peak_Binning_GetAccessStatus) (load ?  import_function(m_handle, "peak_Binning_GetAccessStatus") : nullptr);
    if(m_peak_Binning_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Binning_GetAccessStatus");
    }        

    m_peak_Binning_FactorX_GetList = (dyn_peak_Binning_FactorX_GetList) (load ?  import_function(m_handle, "peak_Binning_FactorX_GetList") : nullptr);
    if(m_peak_Binning_FactorX_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Binning_FactorX_GetList");
    }        

    m_peak_Binning_FactorY_GetList = (dyn_peak_Binning_FactorY_GetList) (load ?  import_function(m_handle, "peak_Binning_FactorY_GetList") : nullptr);
    if(m_peak_Binning_FactorY_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Binning_FactorY_GetList");
    }        

    m_peak_Binning_Set = (dyn_peak_Binning_Set) (load ?  import_function(m_handle, "peak_Binning_Set") : nullptr);
    if(m_peak_Binning_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Binning_Set");
    }        

    m_peak_Binning_Get = (dyn_peak_Binning_Get) (load ?  import_function(m_handle, "peak_Binning_Get") : nullptr);
    if(m_peak_Binning_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Binning_Get");
    }        

    m_peak_Decimation_GetAccessStatus = (dyn_peak_Decimation_GetAccessStatus) (load ?  import_function(m_handle, "peak_Decimation_GetAccessStatus") : nullptr);
    if(m_peak_Decimation_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Decimation_GetAccessStatus");
    }        

    m_peak_Decimation_FactorX_GetList = (dyn_peak_Decimation_FactorX_GetList) (load ?  import_function(m_handle, "peak_Decimation_FactorX_GetList") : nullptr);
    if(m_peak_Decimation_FactorX_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Decimation_FactorX_GetList");
    }        

    m_peak_Decimation_FactorY_GetList = (dyn_peak_Decimation_FactorY_GetList) (load ?  import_function(m_handle, "peak_Decimation_FactorY_GetList") : nullptr);
    if(m_peak_Decimation_FactorY_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Decimation_FactorY_GetList");
    }        

    m_peak_Decimation_Set = (dyn_peak_Decimation_Set) (load ?  import_function(m_handle, "peak_Decimation_Set") : nullptr);
    if(m_peak_Decimation_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Decimation_Set");
    }        

    m_peak_Decimation_Get = (dyn_peak_Decimation_Get) (load ?  import_function(m_handle, "peak_Decimation_Get") : nullptr);
    if(m_peak_Decimation_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Decimation_Get");
    }        

    m_peak_Mirror_LeftRight_GetAccessStatus = (dyn_peak_Mirror_LeftRight_GetAccessStatus) (load ?  import_function(m_handle, "peak_Mirror_LeftRight_GetAccessStatus") : nullptr);
    if(m_peak_Mirror_LeftRight_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Mirror_LeftRight_GetAccessStatus");
    }        

    m_peak_Mirror_LeftRight_Enable = (dyn_peak_Mirror_LeftRight_Enable) (load ?  import_function(m_handle, "peak_Mirror_LeftRight_Enable") : nullptr);
    if(m_peak_Mirror_LeftRight_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Mirror_LeftRight_Enable");
    }        

    m_peak_Mirror_LeftRight_IsEnabled = (dyn_peak_Mirror_LeftRight_IsEnabled) (load ?  import_function(m_handle, "peak_Mirror_LeftRight_IsEnabled") : nullptr);
    if(m_peak_Mirror_LeftRight_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Mirror_LeftRight_IsEnabled");
    }        

    m_peak_Mirror_UpDown_GetAccessStatus = (dyn_peak_Mirror_UpDown_GetAccessStatus) (load ?  import_function(m_handle, "peak_Mirror_UpDown_GetAccessStatus") : nullptr);
    if(m_peak_Mirror_UpDown_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Mirror_UpDown_GetAccessStatus");
    }        

    m_peak_Mirror_UpDown_Enable = (dyn_peak_Mirror_UpDown_Enable) (load ?  import_function(m_handle, "peak_Mirror_UpDown_Enable") : nullptr);
    if(m_peak_Mirror_UpDown_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Mirror_UpDown_Enable");
    }        

    m_peak_Mirror_UpDown_IsEnabled = (dyn_peak_Mirror_UpDown_IsEnabled) (load ?  import_function(m_handle, "peak_Mirror_UpDown_IsEnabled") : nullptr);
    if(m_peak_Mirror_UpDown_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_Mirror_UpDown_IsEnabled");
    }        

    m_peak_CameraMemory_Area_GetAccessStatus = (dyn_peak_CameraMemory_Area_GetAccessStatus) (load ?  import_function(m_handle, "peak_CameraMemory_Area_GetAccessStatus") : nullptr);
    if(m_peak_CameraMemory_Area_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraMemory_Area_GetAccessStatus");
    }        

    m_peak_CameraMemory_Area_GetList = (dyn_peak_CameraMemory_Area_GetList) (load ?  import_function(m_handle, "peak_CameraMemory_Area_GetList") : nullptr);
    if(m_peak_CameraMemory_Area_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraMemory_Area_GetList");
    }        

    m_peak_CameraMemory_Area_Size_Get = (dyn_peak_CameraMemory_Area_Size_Get) (load ?  import_function(m_handle, "peak_CameraMemory_Area_Size_Get") : nullptr);
    if(m_peak_CameraMemory_Area_Size_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraMemory_Area_Size_Get");
    }        

    m_peak_CameraMemory_Area_Data_Clear = (dyn_peak_CameraMemory_Area_Data_Clear) (load ?  import_function(m_handle, "peak_CameraMemory_Area_Data_Clear") : nullptr);
    if(m_peak_CameraMemory_Area_Data_Clear == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraMemory_Area_Data_Clear");
    }        

    m_peak_CameraMemory_Area_Data_Write = (dyn_peak_CameraMemory_Area_Data_Write) (load ?  import_function(m_handle, "peak_CameraMemory_Area_Data_Write") : nullptr);
    if(m_peak_CameraMemory_Area_Data_Write == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraMemory_Area_Data_Write");
    }        

    m_peak_CameraMemory_Area_Data_Read = (dyn_peak_CameraMemory_Area_Data_Read) (load ?  import_function(m_handle, "peak_CameraMemory_Area_Data_Read") : nullptr);
    if(m_peak_CameraMemory_Area_Data_Read == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_CameraMemory_Area_Data_Read");
    }        

    m_peak_GFA_EnableWriteAccess = (dyn_peak_GFA_EnableWriteAccess) (load ?  import_function(m_handle, "peak_GFA_EnableWriteAccess") : nullptr);
    if(m_peak_GFA_EnableWriteAccess == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_EnableWriteAccess");
    }        

    m_peak_GFA_IsWriteAccessEnabled = (dyn_peak_GFA_IsWriteAccessEnabled) (load ?  import_function(m_handle, "peak_GFA_IsWriteAccessEnabled") : nullptr);
    if(m_peak_GFA_IsWriteAccessEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_IsWriteAccessEnabled");
    }        

    m_peak_GFA_Feature_GetAccessStatus = (dyn_peak_GFA_Feature_GetAccessStatus) (load ?  import_function(m_handle, "peak_GFA_Feature_GetAccessStatus") : nullptr);
    if(m_peak_GFA_Feature_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Feature_GetAccessStatus");
    }        

    m_peak_GFA_Float_HasRange = (dyn_peak_GFA_Float_HasRange) (load ?  import_function(m_handle, "peak_GFA_Float_HasRange") : nullptr);
    if(m_peak_GFA_Float_HasRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Float_HasRange");
    }        

    m_peak_GFA_Float_GetRange = (dyn_peak_GFA_Float_GetRange) (load ?  import_function(m_handle, "peak_GFA_Float_GetRange") : nullptr);
    if(m_peak_GFA_Float_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Float_GetRange");
    }        

    m_peak_GFA_Float_GetList = (dyn_peak_GFA_Float_GetList) (load ?  import_function(m_handle, "peak_GFA_Float_GetList") : nullptr);
    if(m_peak_GFA_Float_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Float_GetList");
    }        

    m_peak_GFA_Float_Set = (dyn_peak_GFA_Float_Set) (load ?  import_function(m_handle, "peak_GFA_Float_Set") : nullptr);
    if(m_peak_GFA_Float_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Float_Set");
    }        

    m_peak_GFA_Float_Get = (dyn_peak_GFA_Float_Get) (load ?  import_function(m_handle, "peak_GFA_Float_Get") : nullptr);
    if(m_peak_GFA_Float_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Float_Get");
    }        

    m_peak_GFA_Integer_HasRange = (dyn_peak_GFA_Integer_HasRange) (load ?  import_function(m_handle, "peak_GFA_Integer_HasRange") : nullptr);
    if(m_peak_GFA_Integer_HasRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Integer_HasRange");
    }        

    m_peak_GFA_Integer_GetRange = (dyn_peak_GFA_Integer_GetRange) (load ?  import_function(m_handle, "peak_GFA_Integer_GetRange") : nullptr);
    if(m_peak_GFA_Integer_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Integer_GetRange");
    }        

    m_peak_GFA_Integer_GetList = (dyn_peak_GFA_Integer_GetList) (load ?  import_function(m_handle, "peak_GFA_Integer_GetList") : nullptr);
    if(m_peak_GFA_Integer_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Integer_GetList");
    }        

    m_peak_GFA_Integer_Set = (dyn_peak_GFA_Integer_Set) (load ?  import_function(m_handle, "peak_GFA_Integer_Set") : nullptr);
    if(m_peak_GFA_Integer_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Integer_Set");
    }        

    m_peak_GFA_Integer_Get = (dyn_peak_GFA_Integer_Get) (load ?  import_function(m_handle, "peak_GFA_Integer_Get") : nullptr);
    if(m_peak_GFA_Integer_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Integer_Get");
    }        

    m_peak_GFA_Boolean_Set = (dyn_peak_GFA_Boolean_Set) (load ?  import_function(m_handle, "peak_GFA_Boolean_Set") : nullptr);
    if(m_peak_GFA_Boolean_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Boolean_Set");
    }        

    m_peak_GFA_Boolean_Get = (dyn_peak_GFA_Boolean_Get) (load ?  import_function(m_handle, "peak_GFA_Boolean_Get") : nullptr);
    if(m_peak_GFA_Boolean_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Boolean_Get");
    }        

    m_peak_GFA_String_Set = (dyn_peak_GFA_String_Set) (load ?  import_function(m_handle, "peak_GFA_String_Set") : nullptr);
    if(m_peak_GFA_String_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_String_Set");
    }        

    m_peak_GFA_String_Get = (dyn_peak_GFA_String_Get) (load ?  import_function(m_handle, "peak_GFA_String_Get") : nullptr);
    if(m_peak_GFA_String_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_String_Get");
    }        

    m_peak_GFA_Command_Execute = (dyn_peak_GFA_Command_Execute) (load ?  import_function(m_handle, "peak_GFA_Command_Execute") : nullptr);
    if(m_peak_GFA_Command_Execute == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Command_Execute");
    }        

    m_peak_GFA_Command_WaitForDone = (dyn_peak_GFA_Command_WaitForDone) (load ?  import_function(m_handle, "peak_GFA_Command_WaitForDone") : nullptr);
    if(m_peak_GFA_Command_WaitForDone == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Command_WaitForDone");
    }        

    m_peak_GFA_Enumeration_GetList = (dyn_peak_GFA_Enumeration_GetList) (load ?  import_function(m_handle, "peak_GFA_Enumeration_GetList") : nullptr);
    if(m_peak_GFA_Enumeration_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Enumeration_GetList");
    }        

    m_peak_GFA_EnumerationEntry_GetAccessStatus = (dyn_peak_GFA_EnumerationEntry_GetAccessStatus) (load ?  import_function(m_handle, "peak_GFA_EnumerationEntry_GetAccessStatus") : nullptr);
    if(m_peak_GFA_EnumerationEntry_GetAccessStatus == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_EnumerationEntry_GetAccessStatus");
    }        

    m_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue = (dyn_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue) (load ?  import_function(m_handle, "peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue") : nullptr);
    if(m_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue");
    }        

    m_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue = (dyn_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue) (load ?  import_function(m_handle, "peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue") : nullptr);
    if(m_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue");
    }        

    m_peak_GFA_Enumeration_Set = (dyn_peak_GFA_Enumeration_Set) (load ?  import_function(m_handle, "peak_GFA_Enumeration_Set") : nullptr);
    if(m_peak_GFA_Enumeration_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Enumeration_Set");
    }        

    m_peak_GFA_Enumeration_SetBySymbolicValue = (dyn_peak_GFA_Enumeration_SetBySymbolicValue) (load ?  import_function(m_handle, "peak_GFA_Enumeration_SetBySymbolicValue") : nullptr);
    if(m_peak_GFA_Enumeration_SetBySymbolicValue == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Enumeration_SetBySymbolicValue");
    }        

    m_peak_GFA_Enumeration_SetByIntegerValue = (dyn_peak_GFA_Enumeration_SetByIntegerValue) (load ?  import_function(m_handle, "peak_GFA_Enumeration_SetByIntegerValue") : nullptr);
    if(m_peak_GFA_Enumeration_SetByIntegerValue == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Enumeration_SetByIntegerValue");
    }        

    m_peak_GFA_Enumeration_Get = (dyn_peak_GFA_Enumeration_Get) (load ?  import_function(m_handle, "peak_GFA_Enumeration_Get") : nullptr);
    if(m_peak_GFA_Enumeration_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Enumeration_Get");
    }        

    m_peak_GFA_Register_Set = (dyn_peak_GFA_Register_Set) (load ?  import_function(m_handle, "peak_GFA_Register_Set") : nullptr);
    if(m_peak_GFA_Register_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Register_Set");
    }        

    m_peak_GFA_Register_Get = (dyn_peak_GFA_Register_Get) (load ?  import_function(m_handle, "peak_GFA_Register_Get") : nullptr);
    if(m_peak_GFA_Register_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Register_Get");
    }        

    m_peak_GFA_Data_Write = (dyn_peak_GFA_Data_Write) (load ?  import_function(m_handle, "peak_GFA_Data_Write") : nullptr);
    if(m_peak_GFA_Data_Write == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Data_Write");
    }        

    m_peak_GFA_Data_Read = (dyn_peak_GFA_Data_Read) (load ?  import_function(m_handle, "peak_GFA_Data_Read") : nullptr);
    if(m_peak_GFA_Data_Read == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_GFA_Data_Read");
    }        

    m_peak_IPL_PixelFormat_GetList = (dyn_peak_IPL_PixelFormat_GetList) (load ?  import_function(m_handle, "peak_IPL_PixelFormat_GetList") : nullptr);
    if(m_peak_IPL_PixelFormat_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_PixelFormat_GetList");
    }        

    m_peak_IPL_PixelFormat_Set = (dyn_peak_IPL_PixelFormat_Set) (load ?  import_function(m_handle, "peak_IPL_PixelFormat_Set") : nullptr);
    if(m_peak_IPL_PixelFormat_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_PixelFormat_Set");
    }        

    m_peak_IPL_PixelFormat_Get = (dyn_peak_IPL_PixelFormat_Get) (load ?  import_function(m_handle, "peak_IPL_PixelFormat_Get") : nullptr);
    if(m_peak_IPL_PixelFormat_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_PixelFormat_Get");
    }        

    m_peak_IPL_Gain_GetRange = (dyn_peak_IPL_Gain_GetRange) (load ?  import_function(m_handle, "peak_IPL_Gain_GetRange") : nullptr);
    if(m_peak_IPL_Gain_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Gain_GetRange");
    }        

    m_peak_IPL_Gain_Set = (dyn_peak_IPL_Gain_Set) (load ?  import_function(m_handle, "peak_IPL_Gain_Set") : nullptr);
    if(m_peak_IPL_Gain_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Gain_Set");
    }        

    m_peak_IPL_Gain_Get = (dyn_peak_IPL_Gain_Get) (load ?  import_function(m_handle, "peak_IPL_Gain_Get") : nullptr);
    if(m_peak_IPL_Gain_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Gain_Get");
    }        

    m_peak_IPL_Gamma_GetRange = (dyn_peak_IPL_Gamma_GetRange) (load ?  import_function(m_handle, "peak_IPL_Gamma_GetRange") : nullptr);
    if(m_peak_IPL_Gamma_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Gamma_GetRange");
    }        

    m_peak_IPL_Gamma_Set = (dyn_peak_IPL_Gamma_Set) (load ?  import_function(m_handle, "peak_IPL_Gamma_Set") : nullptr);
    if(m_peak_IPL_Gamma_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Gamma_Set");
    }        

    m_peak_IPL_Gamma_Get = (dyn_peak_IPL_Gamma_Get) (load ?  import_function(m_handle, "peak_IPL_Gamma_Get") : nullptr);
    if(m_peak_IPL_Gamma_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Gamma_Get");
    }        

    m_peak_IPL_ColorCorrection_Matrix_Set = (dyn_peak_IPL_ColorCorrection_Matrix_Set) (load ?  import_function(m_handle, "peak_IPL_ColorCorrection_Matrix_Set") : nullptr);
    if(m_peak_IPL_ColorCorrection_Matrix_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_ColorCorrection_Matrix_Set");
    }        

    m_peak_IPL_ColorCorrection_Matrix_Get = (dyn_peak_IPL_ColorCorrection_Matrix_Get) (load ?  import_function(m_handle, "peak_IPL_ColorCorrection_Matrix_Get") : nullptr);
    if(m_peak_IPL_ColorCorrection_Matrix_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_ColorCorrection_Matrix_Get");
    }        

    m_peak_IPL_ColorCorrection_Enable = (dyn_peak_IPL_ColorCorrection_Enable) (load ?  import_function(m_handle, "peak_IPL_ColorCorrection_Enable") : nullptr);
    if(m_peak_IPL_ColorCorrection_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_ColorCorrection_Enable");
    }        

    m_peak_IPL_ColorCorrection_IsEnabled = (dyn_peak_IPL_ColorCorrection_IsEnabled) (load ?  import_function(m_handle, "peak_IPL_ColorCorrection_IsEnabled") : nullptr);
    if(m_peak_IPL_ColorCorrection_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_ColorCorrection_IsEnabled");
    }        

    m_peak_IPL_AutoBrightness_Target_GetRange = (dyn_peak_IPL_AutoBrightness_Target_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Target_GetRange") : nullptr);
    if(m_peak_IPL_AutoBrightness_Target_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Target_GetRange");
    }        

    m_peak_IPL_AutoBrightness_Target_Set = (dyn_peak_IPL_AutoBrightness_Target_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Target_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_Target_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Target_Set");
    }        

    m_peak_IPL_AutoBrightness_Target_Get = (dyn_peak_IPL_AutoBrightness_Target_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Target_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_Target_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Target_Get");
    }        

    m_peak_IPL_AutoBrightness_TargetTolerance_GetRange = (dyn_peak_IPL_AutoBrightness_TargetTolerance_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_TargetTolerance_GetRange") : nullptr);
    if(m_peak_IPL_AutoBrightness_TargetTolerance_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_TargetTolerance_GetRange");
    }        

    m_peak_IPL_AutoBrightness_TargetTolerance_Set = (dyn_peak_IPL_AutoBrightness_TargetTolerance_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_TargetTolerance_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_TargetTolerance_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_TargetTolerance_Set");
    }        

    m_peak_IPL_AutoBrightness_TargetTolerance_Get = (dyn_peak_IPL_AutoBrightness_TargetTolerance_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_TargetTolerance_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_TargetTolerance_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_TargetTolerance_Get");
    }        

    m_peak_IPL_AutoBrightness_TargetPercentile_GetRange = (dyn_peak_IPL_AutoBrightness_TargetPercentile_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_TargetPercentile_GetRange") : nullptr);
    if(m_peak_IPL_AutoBrightness_TargetPercentile_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_TargetPercentile_GetRange");
    }        

    m_peak_IPL_AutoBrightness_TargetPercentile_Set = (dyn_peak_IPL_AutoBrightness_TargetPercentile_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_TargetPercentile_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_TargetPercentile_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_TargetPercentile_Set");
    }        

    m_peak_IPL_AutoBrightness_TargetPercentile_Get = (dyn_peak_IPL_AutoBrightness_TargetPercentile_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_TargetPercentile_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_TargetPercentile_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_TargetPercentile_Get");
    }        

    m_peak_IPL_AutoBrightness_ROI_Mode_Set = (dyn_peak_IPL_AutoBrightness_ROI_Mode_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_ROI_Mode_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_ROI_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_ROI_Mode_Set");
    }        

    m_peak_IPL_AutoBrightness_ROI_Mode_Get = (dyn_peak_IPL_AutoBrightness_ROI_Mode_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_ROI_Mode_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_ROI_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_ROI_Mode_Get");
    }        

    m_peak_IPL_AutoBrightness_ROI_Offset_GetRange = (dyn_peak_IPL_AutoBrightness_ROI_Offset_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_ROI_Offset_GetRange") : nullptr);
    if(m_peak_IPL_AutoBrightness_ROI_Offset_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_ROI_Offset_GetRange");
    }        

    m_peak_IPL_AutoBrightness_ROI_Size_GetRange = (dyn_peak_IPL_AutoBrightness_ROI_Size_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_ROI_Size_GetRange") : nullptr);
    if(m_peak_IPL_AutoBrightness_ROI_Size_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_ROI_Size_GetRange");
    }        

    m_peak_IPL_AutoBrightness_ROI_Set = (dyn_peak_IPL_AutoBrightness_ROI_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_ROI_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_ROI_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_ROI_Set");
    }        

    m_peak_IPL_AutoBrightness_ROI_Get = (dyn_peak_IPL_AutoBrightness_ROI_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_ROI_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_ROI_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_ROI_Get");
    }        

    m_peak_IPL_AutoBrightness_Exposure_Mode_Set = (dyn_peak_IPL_AutoBrightness_Exposure_Mode_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Exposure_Mode_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_Exposure_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Exposure_Mode_Set");
    }        

    m_peak_IPL_AutoBrightness_Exposure_Mode_Get = (dyn_peak_IPL_AutoBrightness_Exposure_Mode_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Exposure_Mode_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_Exposure_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Exposure_Mode_Get");
    }        

    m_peak_IPL_AutoBrightness_Gain_Mode_Set = (dyn_peak_IPL_AutoBrightness_Gain_Mode_Set) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Gain_Mode_Set") : nullptr);
    if(m_peak_IPL_AutoBrightness_Gain_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Gain_Mode_Set");
    }        

    m_peak_IPL_AutoBrightness_Gain_Mode_Get = (dyn_peak_IPL_AutoBrightness_Gain_Mode_Get) (load ?  import_function(m_handle, "peak_IPL_AutoBrightness_Gain_Mode_Get") : nullptr);
    if(m_peak_IPL_AutoBrightness_Gain_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoBrightness_Gain_Mode_Get");
    }        

    m_peak_IPL_AutoWhiteBalance_ROI_Mode_Set = (dyn_peak_IPL_AutoWhiteBalance_ROI_Mode_Set) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_ROI_Mode_Set") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_ROI_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_ROI_Mode_Set");
    }        

    m_peak_IPL_AutoWhiteBalance_ROI_Mode_Get = (dyn_peak_IPL_AutoWhiteBalance_ROI_Mode_Get) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_ROI_Mode_Get") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_ROI_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_ROI_Mode_Get");
    }        

    m_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange = (dyn_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange");
    }        

    m_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange = (dyn_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_ROI_Size_GetRange") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_ROI_Size_GetRange");
    }        

    m_peak_IPL_AutoWhiteBalance_ROI_Set = (dyn_peak_IPL_AutoWhiteBalance_ROI_Set) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_ROI_Set") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_ROI_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_ROI_Set");
    }        

    m_peak_IPL_AutoWhiteBalance_ROI_Get = (dyn_peak_IPL_AutoWhiteBalance_ROI_Get) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_ROI_Get") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_ROI_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_ROI_Get");
    }        

    m_peak_IPL_AutoWhiteBalance_Mode_Set = (dyn_peak_IPL_AutoWhiteBalance_Mode_Set) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_Mode_Set") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_Mode_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_Mode_Set");
    }        

    m_peak_IPL_AutoWhiteBalance_Mode_Get = (dyn_peak_IPL_AutoWhiteBalance_Mode_Get) (load ?  import_function(m_handle, "peak_IPL_AutoWhiteBalance_Mode_Get") : nullptr);
    if(m_peak_IPL_AutoWhiteBalance_Mode_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_AutoWhiteBalance_Mode_Get");
    }        

    m_peak_IPL_HotpixelCorrection_Sensitivity_Set = (dyn_peak_IPL_HotpixelCorrection_Sensitivity_Set) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_Sensitivity_Set") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_Sensitivity_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_Sensitivity_Set");
    }        

    m_peak_IPL_HotpixelCorrection_Sensitivity_Get = (dyn_peak_IPL_HotpixelCorrection_Sensitivity_Get) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_Sensitivity_Get") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_Sensitivity_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_Sensitivity_Get");
    }        

    m_peak_IPL_HotpixelCorrection_GetList = (dyn_peak_IPL_HotpixelCorrection_GetList) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_GetList") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_GetList");
    }        

    m_peak_IPL_HotpixelCorrection_SetList = (dyn_peak_IPL_HotpixelCorrection_SetList) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_SetList") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_SetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_SetList");
    }        

    m_peak_IPL_HotpixelCorrection_ResetList = (dyn_peak_IPL_HotpixelCorrection_ResetList) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_ResetList") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_ResetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_ResetList");
    }        

    m_peak_IPL_HotpixelCorrection_Enable = (dyn_peak_IPL_HotpixelCorrection_Enable) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_Enable") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_Enable");
    }        

    m_peak_IPL_HotpixelCorrection_IsEnabled = (dyn_peak_IPL_HotpixelCorrection_IsEnabled) (load ?  import_function(m_handle, "peak_IPL_HotpixelCorrection_IsEnabled") : nullptr);
    if(m_peak_IPL_HotpixelCorrection_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_HotpixelCorrection_IsEnabled");
    }        

    m_peak_IPL_Mirror_UpDown_Enable = (dyn_peak_IPL_Mirror_UpDown_Enable) (load ?  import_function(m_handle, "peak_IPL_Mirror_UpDown_Enable") : nullptr);
    if(m_peak_IPL_Mirror_UpDown_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Mirror_UpDown_Enable");
    }        

    m_peak_IPL_Mirror_UpDown_IsEnabled = (dyn_peak_IPL_Mirror_UpDown_IsEnabled) (load ?  import_function(m_handle, "peak_IPL_Mirror_UpDown_IsEnabled") : nullptr);
    if(m_peak_IPL_Mirror_UpDown_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Mirror_UpDown_IsEnabled");
    }        

    m_peak_IPL_Mirror_LeftRight_Enable = (dyn_peak_IPL_Mirror_LeftRight_Enable) (load ?  import_function(m_handle, "peak_IPL_Mirror_LeftRight_Enable") : nullptr);
    if(m_peak_IPL_Mirror_LeftRight_Enable == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Mirror_LeftRight_Enable");
    }        

    m_peak_IPL_Mirror_LeftRight_IsEnabled = (dyn_peak_IPL_Mirror_LeftRight_IsEnabled) (load ?  import_function(m_handle, "peak_IPL_Mirror_LeftRight_IsEnabled") : nullptr);
    if(m_peak_IPL_Mirror_LeftRight_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_Mirror_LeftRight_IsEnabled");
    }        

    m_peak_IPL_ProcessFrame = (dyn_peak_IPL_ProcessFrame) (load ?  import_function(m_handle, "peak_IPL_ProcessFrame") : nullptr);
    if(m_peak_IPL_ProcessFrame == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_ProcessFrame");
    }        

    m_peak_IPL_ProcessFrameInplace = (dyn_peak_IPL_ProcessFrameInplace) (load ?  import_function(m_handle, "peak_IPL_ProcessFrameInplace") : nullptr);
    if(m_peak_IPL_ProcessFrameInplace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_IPL_ProcessFrameInplace");
    }        

    m_peak_VideoWriter_Open = (dyn_peak_VideoWriter_Open) (load ?  import_function(m_handle, "peak_VideoWriter_Open") : nullptr);
    if(m_peak_VideoWriter_Open == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Open");
    }        

    m_peak_VideoWriter_Close = (dyn_peak_VideoWriter_Close) (load ?  import_function(m_handle, "peak_VideoWriter_Close") : nullptr);
    if(m_peak_VideoWriter_Close == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Close");
    }        

    m_peak_VideoWriter_AddFrame = (dyn_peak_VideoWriter_AddFrame) (load ?  import_function(m_handle, "peak_VideoWriter_AddFrame") : nullptr);
    if(m_peak_VideoWriter_AddFrame == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_AddFrame");
    }        

    m_peak_VideoWriter_Container_GetEncoderList = (dyn_peak_VideoWriter_Container_GetEncoderList) (load ?  import_function(m_handle, "peak_VideoWriter_Container_GetEncoderList") : nullptr);
    if(m_peak_VideoWriter_Container_GetEncoderList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Container_GetEncoderList");
    }        

    m_peak_VideoWriter_Encoder_GetPixelFormatList = (dyn_peak_VideoWriter_Encoder_GetPixelFormatList) (load ?  import_function(m_handle, "peak_VideoWriter_Encoder_GetPixelFormatList") : nullptr);
    if(m_peak_VideoWriter_Encoder_GetPixelFormatList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Encoder_GetPixelFormatList");
    }        

    m_peak_VideoWriter_Encoder_GetContainerList = (dyn_peak_VideoWriter_Encoder_GetContainerList) (load ?  import_function(m_handle, "peak_VideoWriter_Encoder_GetContainerList") : nullptr);
    if(m_peak_VideoWriter_Encoder_GetContainerList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Encoder_GetContainerList");
    }        

    m_peak_VideoWriter_GetInfo = (dyn_peak_VideoWriter_GetInfo) (load ?  import_function(m_handle, "peak_VideoWriter_GetInfo") : nullptr);
    if(m_peak_VideoWriter_GetInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_GetInfo");
    }        

    m_peak_VideoWriter_Container_Option_Set = (dyn_peak_VideoWriter_Container_Option_Set) (load ?  import_function(m_handle, "peak_VideoWriter_Container_Option_Set") : nullptr);
    if(m_peak_VideoWriter_Container_Option_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Container_Option_Set");
    }        

    m_peak_VideoWriter_Container_Option_Get = (dyn_peak_VideoWriter_Container_Option_Get) (load ?  import_function(m_handle, "peak_VideoWriter_Container_Option_Get") : nullptr);
    if(m_peak_VideoWriter_Container_Option_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Container_Option_Get");
    }        

    m_peak_VideoWriter_Encoder_Option_Set = (dyn_peak_VideoWriter_Encoder_Option_Set) (load ?  import_function(m_handle, "peak_VideoWriter_Encoder_Option_Set") : nullptr);
    if(m_peak_VideoWriter_Encoder_Option_Set == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Encoder_Option_Set");
    }        

    m_peak_VideoWriter_Encoder_Option_Get = (dyn_peak_VideoWriter_Encoder_Option_Get) (load ?  import_function(m_handle, "peak_VideoWriter_Encoder_Option_Get") : nullptr);
    if(m_peak_VideoWriter_Encoder_Option_Get == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_Encoder_Option_Get");
    }        

    m_peak_VideoWriter_WaitUntilQueueEmpty = (dyn_peak_VideoWriter_WaitUntilQueueEmpty) (load ?  import_function(m_handle, "peak_VideoWriter_WaitUntilQueueEmpty") : nullptr);
    if(m_peak_VideoWriter_WaitUntilQueueEmpty == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_VideoWriter_WaitUntilQueueEmpty");
    }        

            
            return true;
}

inline PEAK_API_STATUS DynamicLoader::peak_Library_Init()
{
    auto& inst = instance();
    if(inst.m_peak_Library_Init)
    {
        return inst.m_peak_Library_Init();
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Library_Exit()
{
    auto& inst = instance();
    if(inst.m_peak_Library_Exit)
    {
        return inst.m_peak_Library_Exit();
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Library_GetVersion(uint32_t * majorVersion, uint32_t * minorVersion, uint32_t * subminorVersion, uint32_t * patchVersion)
{
    auto& inst = instance();
    if(inst.m_peak_Library_GetVersion)
    {
        return inst.m_peak_Library_GetVersion(majorVersion, minorVersion, subminorVersion, patchVersion);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Library_GetLastError(peak_status * lastErrorCode, char * lastErrorMessage, size_t * lastErrorMessageSize)
{
    auto& inst = instance();
    if(inst.m_peak_Library_GetLastError)
    {
        return inst.m_peak_Library_GetLastError(lastErrorCode, lastErrorMessage, lastErrorMessageSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraList_Update(size_t * cameraCount)
{
    auto& inst = instance();
    if(inst.m_peak_CameraList_Update)
    {
        return inst.m_peak_CameraList_Update(cameraCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraList_Get(peak_camera_descriptor * cameraList, size_t * cameraCount)
{
    auto& inst = instance();
    if(inst.m_peak_CameraList_Get)
    {
        return inst.m_peak_CameraList_Get(cameraList, cameraCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_CAMERA_ID DynamicLoader::peak_Camera_ID_FromHandle(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_ID_FromHandle)
    {
        return inst.m_peak_Camera_ID_FromHandle(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_CAMERA_ID DynamicLoader::peak_Camera_ID_FromSerialNumber(const char * serialNumber)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_ID_FromSerialNumber)
    {
        return inst.m_peak_Camera_ID_FromSerialNumber(serialNumber);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_CAMERA_ID DynamicLoader::peak_Camera_ID_FromMAC(peak_mac_address macAddress)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_ID_FromMAC)
    {
        return inst.m_peak_Camera_ID_FromMAC(macAddress);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Camera_GetAccessStatus(peak_camera_id cameraID)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_GetAccessStatus)
    {
        return inst.m_peak_Camera_GetAccessStatus(cameraID);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Camera_GetDescriptor(peak_camera_id cameraID, peak_camera_descriptor * cameraDescriptor)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_GetDescriptor)
    {
        return inst.m_peak_Camera_GetDescriptor(cameraID, cameraDescriptor);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Camera_Open(peak_camera_id cameraID, peak_camera_handle * hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_Open)
    {
        return inst.m_peak_Camera_Open(cameraID, hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Camera_OpenFirstAvailable(peak_camera_handle * hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_OpenFirstAvailable)
    {
        return inst.m_peak_Camera_OpenFirstAvailable(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Camera_Close(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_Close)
    {
        return inst.m_peak_Camera_Close(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Camera_ResetToDefaultSettings(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Camera_ResetToDefaultSettings)
    {
        return inst.m_peak_Camera_ResetToDefaultSettings(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_EthernetConfig_GetAccessStatus(peak_camera_id cameraID)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_GetAccessStatus)
    {
        return inst.m_peak_EthernetConfig_GetAccessStatus(cameraID);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_EthernetConfig_GetInfo(peak_camera_id cameraID, peak_ethernet_info * ethernetInfo)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_GetInfo)
    {
        return inst.m_peak_EthernetConfig_GetInfo(cameraID, ethernetInfo);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_EthernetConfig_DHCP_GetAccessStatus(peak_camera_id cameraID)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_DHCP_GetAccessStatus)
    {
        return inst.m_peak_EthernetConfig_DHCP_GetAccessStatus(cameraID);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_EthernetConfig_DHCP_Enable(peak_camera_id cameraID, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_DHCP_Enable)
    {
        return inst.m_peak_EthernetConfig_DHCP_Enable(cameraID, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_EthernetConfig_DHCP_IsEnabled(peak_camera_id cameraID)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_DHCP_IsEnabled)
    {
        return inst.m_peak_EthernetConfig_DHCP_IsEnabled(cameraID);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_EthernetConfig_PersistentIP_GetAccessStatus(peak_camera_id cameraID)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_PersistentIP_GetAccessStatus)
    {
        return inst.m_peak_EthernetConfig_PersistentIP_GetAccessStatus(cameraID);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_EthernetConfig_PersistentIP_Set(peak_camera_id cameraID, peak_ip_config persistentIP)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_PersistentIP_Set)
    {
        return inst.m_peak_EthernetConfig_PersistentIP_Set(cameraID, persistentIP);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_EthernetConfig_PersistentIP_Get(peak_camera_id cameraID, peak_ip_config * persistentIP)
{
    auto& inst = instance();
    if(inst.m_peak_EthernetConfig_PersistentIP_Get)
    {
        return inst.m_peak_EthernetConfig_PersistentIP_Get(cameraID, persistentIP);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Start(peak_camera_handle hCam, uint32_t numberOfFrames)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Start)
    {
        return inst.m_peak_Acquisition_Start(hCam, numberOfFrames);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Stop(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Stop)
    {
        return inst.m_peak_Acquisition_Stop(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Acquisition_IsStarted(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_IsStarted)
    {
        return inst.m_peak_Acquisition_IsStarted(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_WaitForFrame(peak_camera_handle hCam, uint32_t timeout_ms, peak_frame_handle * hFrame)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_WaitForFrame)
    {
        return inst.m_peak_Acquisition_WaitForFrame(hCam, timeout_ms, hFrame);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_GetInfo(peak_camera_handle hCam, peak_acquisition_info * acquisitionInfo)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_GetInfo)
    {
        return inst.m_peak_Acquisition_GetInfo(hCam, acquisitionInfo);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Buffer_GetRequiredSize(peak_camera_handle hCam, size_t * requiredBufferSize)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Buffer_GetRequiredSize)
    {
        return inst.m_peak_Acquisition_Buffer_GetRequiredSize(hCam, requiredBufferSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Buffer_GetRequiredCount(peak_camera_handle hCam, size_t * requiredBufferCount)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Buffer_GetRequiredCount)
    {
        return inst.m_peak_Acquisition_Buffer_GetRequiredCount(hCam, requiredBufferCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Buffer_Announce(peak_camera_handle hCam, uint8_t * memoryAddress, size_t memorySize, void * userContext)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Buffer_Announce)
    {
        return inst.m_peak_Acquisition_Buffer_Announce(hCam, memoryAddress, memorySize, userContext);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Buffer_Revoke(peak_camera_handle hCam, uint8_t * memoryAddress)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Buffer_Revoke)
    {
        return inst.m_peak_Acquisition_Buffer_Revoke(hCam, memoryAddress);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Acquisition_Buffer_RevokeAll(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Acquisition_Buffer_RevokeAll)
    {
        return inst.m_peak_Acquisition_Buffer_RevokeAll(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelFormat_GetInfo(peak_pixel_format pixelFormat, peak_pixel_format_info * pixelFormatInfo)
{
    auto& inst = instance();
    if(inst.m_peak_PixelFormat_GetInfo)
    {
        return inst.m_peak_PixelFormat_GetInfo(pixelFormat, pixelFormatInfo);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_Release(peak_camera_handle hCam, peak_frame_handle hFrame)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_Release)
    {
        return inst.m_peak_Frame_Release(hCam, hFrame);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_GetInfo(peak_frame_handle hFrame, peak_frame_info * frameInfo)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_GetInfo)
    {
        return inst.m_peak_Frame_GetInfo(hFrame, frameInfo);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_Type_Get(peak_frame_handle hFrame, peak_frame_type * frameType)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_Type_Get)
    {
        return inst.m_peak_Frame_Type_Get(hFrame, frameType);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_Buffer_Get(peak_frame_handle hFrame, peak_buffer * buffer)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_Buffer_Get)
    {
        return inst.m_peak_Frame_Buffer_Get(hFrame, buffer);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_ID_Get(peak_frame_handle hFrame, uint64_t * frameID)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_ID_Get)
    {
        return inst.m_peak_Frame_ID_Get(hFrame, frameID);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_Timestamp_Get(peak_frame_handle hFrame, uint64_t * timestamp_ns)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_Timestamp_Get)
    {
        return inst.m_peak_Frame_Timestamp_Get(hFrame, timestamp_ns);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_ROI_Get(peak_frame_handle hFrame, peak_roi * roi)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_ROI_Get)
    {
        return inst.m_peak_Frame_ROI_Get(hFrame, roi);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_PixelFormat_Get(peak_frame_handle hFrame, peak_pixel_format * pixelFormat)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_PixelFormat_Get)
    {
        return inst.m_peak_Frame_PixelFormat_Get(hFrame, pixelFormat);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Frame_IsComplete(peak_frame_handle hFrame)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_IsComplete)
    {
        return inst.m_peak_Frame_IsComplete(hFrame);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_BytesExpected_Get(peak_frame_handle hFrame, size_t * bytesExpected)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_BytesExpected_Get)
    {
        return inst.m_peak_Frame_BytesExpected_Get(hFrame, bytesExpected);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_BytesWritten_Get(peak_frame_handle hFrame, size_t * bytesWritten)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_BytesWritten_Get)
    {
        return inst.m_peak_Frame_BytesWritten_Get(hFrame, bytesWritten);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Frame_ProcessingTime_Get(peak_frame_handle hFrame, uint32_t * processingTime_ms)
{
    auto& inst = instance();
    if(inst.m_peak_Frame_ProcessingTime_Get)
    {
        return inst.m_peak_Frame_ProcessingTime_Get(hFrame, processingTime_ms);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_GetAccessStatus(peak_camera_handle hCam, peak_parameter_set parameterSet)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_GetAccessStatus)
    {
        return inst.m_peak_CameraSettings_ParameterSet_GetAccessStatus(hCam, parameterSet);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_GetList(peak_camera_handle hCam, peak_parameter_set * parameterSetList, size_t * parameterSetCount)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_GetList)
    {
        return inst.m_peak_CameraSettings_ParameterSet_GetList(hCam, parameterSetList, parameterSetCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_Store(peak_camera_handle hCam, peak_parameter_set parameterSet)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_Store)
    {
        return inst.m_peak_CameraSettings_ParameterSet_Store(hCam, parameterSet);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_Apply(peak_camera_handle hCam, peak_parameter_set parameterSet)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_Apply)
    {
        return inst.m_peak_CameraSettings_ParameterSet_Apply(hCam, parameterSet);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_Startup_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus)
    {
        return inst.m_peak_CameraSettings_ParameterSet_Startup_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_Startup_Set(peak_camera_handle hCam, peak_parameter_set parameterSet)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_Startup_Set)
    {
        return inst.m_peak_CameraSettings_ParameterSet_Startup_Set(hCam, parameterSet);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_ParameterSet_Startup_Get(peak_camera_handle hCam, peak_parameter_set * parameterSet)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_ParameterSet_Startup_Get)
    {
        return inst.m_peak_CameraSettings_ParameterSet_Startup_Get(hCam, parameterSet);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_CameraSettings_DiskFile_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_DiskFile_GetAccessStatus)
    {
        return inst.m_peak_CameraSettings_DiskFile_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_DiskFile_Store(peak_camera_handle hCam, const char * file)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_DiskFile_Store)
    {
        return inst.m_peak_CameraSettings_DiskFile_Store(hCam, file);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraSettings_DiskFile_Apply(peak_camera_handle hCam, const char * file)
{
    auto& inst = instance();
    if(inst.m_peak_CameraSettings_DiskFile_Apply)
    {
        return inst.m_peak_CameraSettings_DiskFile_Apply(hCam, file);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_FrameRate_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_FrameRate_GetAccessStatus)
    {
        return inst.m_peak_FrameRate_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_FrameRate_GetRange(peak_camera_handle hCam, double * minFrameRate_fps, double * maxFrameRate_fps, double * incFrameRate_fps)
{
    auto& inst = instance();
    if(inst.m_peak_FrameRate_GetRange)
    {
        return inst.m_peak_FrameRate_GetRange(hCam, minFrameRate_fps, maxFrameRate_fps, incFrameRate_fps);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_FrameRate_Set(peak_camera_handle hCam, double frameRate_fps)
{
    auto& inst = instance();
    if(inst.m_peak_FrameRate_Set)
    {
        return inst.m_peak_FrameRate_Set(hCam, frameRate_fps);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_FrameRate_Get(peak_camera_handle hCam, double * frameRate_fps)
{
    auto& inst = instance();
    if(inst.m_peak_FrameRate_Get)
    {
        return inst.m_peak_FrameRate_Get(hCam, frameRate_fps);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_ExposureTime_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_ExposureTime_GetAccessStatus)
    {
        return inst.m_peak_ExposureTime_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ExposureTime_GetRange(peak_camera_handle hCam, double * minExposureTime_us, double * maxExposureTime_us, double * incExposureTime_us)
{
    auto& inst = instance();
    if(inst.m_peak_ExposureTime_GetRange)
    {
        return inst.m_peak_ExposureTime_GetRange(hCam, minExposureTime_us, maxExposureTime_us, incExposureTime_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ExposureTime_Set(peak_camera_handle hCam, double exposureTime_us)
{
    auto& inst = instance();
    if(inst.m_peak_ExposureTime_Set)
    {
        return inst.m_peak_ExposureTime_Set(hCam, exposureTime_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ExposureTime_Get(peak_camera_handle hCam, double * exposureTime_us)
{
    auto& inst = instance();
    if(inst.m_peak_ExposureTime_Get)
    {
        return inst.m_peak_ExposureTime_Get(hCam, exposureTime_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_PixelClock_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_PixelClock_GetAccessStatus)
    {
        return inst.m_peak_PixelClock_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_PixelClock_HasRange(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_PixelClock_HasRange)
    {
        return inst.m_peak_PixelClock_HasRange(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelClock_GetRange(peak_camera_handle hCam, double * minPixelClock_MHz, double * maxPixelClock_MHz, double * incPixelClock_MHz)
{
    auto& inst = instance();
    if(inst.m_peak_PixelClock_GetRange)
    {
        return inst.m_peak_PixelClock_GetRange(hCam, minPixelClock_MHz, maxPixelClock_MHz, incPixelClock_MHz);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelClock_GetList(peak_camera_handle hCam, double * pixelClockList, size_t * pixelClockCount)
{
    auto& inst = instance();
    if(inst.m_peak_PixelClock_GetList)
    {
        return inst.m_peak_PixelClock_GetList(hCam, pixelClockList, pixelClockCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelClock_Set(peak_camera_handle hCam, double pixelClock_MHz)
{
    auto& inst = instance();
    if(inst.m_peak_PixelClock_Set)
    {
        return inst.m_peak_PixelClock_Set(hCam, pixelClock_MHz);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelClock_Get(peak_camera_handle hCam, double * pixelClock_MHz)
{
    auto& inst = instance();
    if(inst.m_peak_PixelClock_Get)
    {
        return inst.m_peak_PixelClock_Get(hCam, pixelClock_MHz);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_IOChannel_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_GetAccessStatus)
    {
        return inst.m_peak_IOChannel_GetAccessStatus(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IOChannel_GetList(peak_camera_handle hCam, peak_io_channel * ioChannelList, size_t * ioChannelCount)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_GetList)
    {
        return inst.m_peak_IOChannel_GetList(hCam, ioChannelList, ioChannelCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_IOChannel_Level_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_Level_GetAccessStatus)
    {
        return inst.m_peak_IOChannel_Level_GetAccessStatus(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IOChannel_Level_IsHigh(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_Level_IsHigh)
    {
        return inst.m_peak_IOChannel_Level_IsHigh(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_IOChannel_Inverter_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_Inverter_GetAccessStatus)
    {
        return inst.m_peak_IOChannel_Inverter_GetAccessStatus(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IOChannel_Inverter_Enable(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_Inverter_Enable)
    {
        return inst.m_peak_IOChannel_Inverter_Enable(hCam, ioChannel, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IOChannel_Inverter_IsEnabled(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_Inverter_IsEnabled)
    {
        return inst.m_peak_IOChannel_Inverter_IsEnabled(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_IOChannel_NoiseFilter_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_NoiseFilter_GetAccessStatus)
    {
        return inst.m_peak_IOChannel_NoiseFilter_GetAccessStatus(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IOChannel_NoiseFilter_Enable(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_NoiseFilter_Enable)
    {
        return inst.m_peak_IOChannel_NoiseFilter_Enable(hCam, ioChannel, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IOChannel_NoiseFilter_IsEnabled(peak_camera_handle hCam, peak_io_channel ioChannel)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_NoiseFilter_IsEnabled)
    {
        return inst.m_peak_IOChannel_NoiseFilter_IsEnabled(hCam, ioChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IOChannel_NoiseFilter_Duration_GetRange(peak_camera_handle hCam, peak_io_channel ioChannel, double * minNoiseFilterDuration_us, double * maxNoiseFilterDuration_us, double * incNoiseFilterDuration_us)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_NoiseFilter_Duration_GetRange)
    {
        return inst.m_peak_IOChannel_NoiseFilter_Duration_GetRange(hCam, ioChannel, minNoiseFilterDuration_us, maxNoiseFilterDuration_us, incNoiseFilterDuration_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IOChannel_NoiseFilter_Duration_Set(peak_camera_handle hCam, peak_io_channel ioChannel, double noiseFilterDuration_us)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_NoiseFilter_Duration_Set)
    {
        return inst.m_peak_IOChannel_NoiseFilter_Duration_Set(hCam, ioChannel, noiseFilterDuration_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IOChannel_NoiseFilter_Duration_Get(peak_camera_handle hCam, peak_io_channel ioChannel, double * noiseFilterDuration_us)
{
    auto& inst = instance();
    if(inst.m_peak_IOChannel_NoiseFilter_Duration_Get)
    {
        return inst.m_peak_IOChannel_NoiseFilter_Duration_Get(hCam, ioChannel, noiseFilterDuration_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Trigger_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_GetAccessStatus)
    {
        return inst.m_peak_Trigger_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Enable)
    {
        return inst.m_peak_Trigger_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Trigger_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_IsEnabled)
    {
        return inst.m_peak_Trigger_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Trigger_IsExecutable(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_IsExecutable)
    {
        return inst.m_peak_Trigger_IsExecutable(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Execute(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Execute)
    {
        return inst.m_peak_Trigger_Execute(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Trigger_Mode_GetAccessStatus(peak_camera_handle hCam, peak_trigger_mode triggerMode)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Mode_GetAccessStatus)
    {
        return inst.m_peak_Trigger_Mode_GetAccessStatus(hCam, triggerMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Mode_Set(peak_camera_handle hCam, peak_trigger_mode triggerMode)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Mode_Set)
    {
        return inst.m_peak_Trigger_Mode_Set(hCam, triggerMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Mode_Get(peak_camera_handle hCam, peak_trigger_mode * triggerMode)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Mode_Get)
    {
        return inst.m_peak_Trigger_Mode_Get(hCam, triggerMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Trigger_Edge_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Edge_GetAccessStatus)
    {
        return inst.m_peak_Trigger_Edge_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Edge_GetList(peak_camera_handle hCam, peak_trigger_edge * triggerEdgeList, size_t * triggerEdgeCount)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Edge_GetList)
    {
        return inst.m_peak_Trigger_Edge_GetList(hCam, triggerEdgeList, triggerEdgeCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Edge_Set(peak_camera_handle hCam, peak_trigger_edge triggerEdge)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Edge_Set)
    {
        return inst.m_peak_Trigger_Edge_Set(hCam, triggerEdge);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Edge_Get(peak_camera_handle hCam, peak_trigger_edge * triggerEdge)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Edge_Get)
    {
        return inst.m_peak_Trigger_Edge_Get(hCam, triggerEdge);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Trigger_Delay_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Delay_GetAccessStatus)
    {
        return inst.m_peak_Trigger_Delay_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Delay_GetRange(peak_camera_handle hCam, double * minTriggerDelay_us, double * maxTriggerDelay_us, double * incTriggerDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Delay_GetRange)
    {
        return inst.m_peak_Trigger_Delay_GetRange(hCam, minTriggerDelay_us, maxTriggerDelay_us, incTriggerDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Delay_Set(peak_camera_handle hCam, double triggerDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Delay_Set)
    {
        return inst.m_peak_Trigger_Delay_Set(hCam, triggerDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Delay_Get(peak_camera_handle hCam, double * triggerDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Delay_Get)
    {
        return inst.m_peak_Trigger_Delay_Get(hCam, triggerDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Trigger_Divider_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Divider_GetAccessStatus)
    {
        return inst.m_peak_Trigger_Divider_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Divider_GetRange(peak_camera_handle hCam, uint32_t * minTriggerDivider, uint32_t * maxTriggerDivider, uint32_t * incTriggerDivider)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Divider_GetRange)
    {
        return inst.m_peak_Trigger_Divider_GetRange(hCam, minTriggerDivider, maxTriggerDivider, incTriggerDivider);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Divider_Set(peak_camera_handle hCam, uint32_t triggerDivider)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Divider_Set)
    {
        return inst.m_peak_Trigger_Divider_Set(hCam, triggerDivider);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Divider_Get(peak_camera_handle hCam, uint32_t * triggerDivider)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Divider_Get)
    {
        return inst.m_peak_Trigger_Divider_Get(hCam, triggerDivider);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Trigger_Burst_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Burst_GetAccessStatus)
    {
        return inst.m_peak_Trigger_Burst_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Burst_GetRange(peak_camera_handle hCam, uint32_t * minTriggerBurst, uint32_t * maxTriggerBurst, uint32_t * incTriggerBurst)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Burst_GetRange)
    {
        return inst.m_peak_Trigger_Burst_GetRange(hCam, minTriggerBurst, maxTriggerBurst, incTriggerBurst);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Burst_Set(peak_camera_handle hCam, uint32_t triggerBurst)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Burst_Set)
    {
        return inst.m_peak_Trigger_Burst_Set(hCam, triggerBurst);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Trigger_Burst_Get(peak_camera_handle hCam, uint32_t * triggerBurst)
{
    auto& inst = instance();
    if(inst.m_peak_Trigger_Burst_Get)
    {
        return inst.m_peak_Trigger_Burst_Get(hCam, triggerBurst);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Flash_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_GetAccessStatus)
    {
        return inst.m_peak_Flash_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Enable)
    {
        return inst.m_peak_Flash_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Flash_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_IsEnabled)
    {
        return inst.m_peak_Flash_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Flash_Mode_GetAccessStatus(peak_camera_handle hCam, peak_flash_mode flashMode)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Mode_GetAccessStatus)
    {
        return inst.m_peak_Flash_Mode_GetAccessStatus(hCam, flashMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_Mode_Set(peak_camera_handle hCam, peak_flash_mode flashMode)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Mode_Set)
    {
        return inst.m_peak_Flash_Mode_Set(hCam, flashMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_Mode_Get(peak_camera_handle hCam, peak_flash_mode * flashMode)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Mode_Get)
    {
        return inst.m_peak_Flash_Mode_Get(hCam, flashMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Flash_StartDelay_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_StartDelay_GetAccessStatus)
    {
        return inst.m_peak_Flash_StartDelay_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_StartDelay_GetRange(peak_camera_handle hCam, double * minFlashStartDelay_us, double * maxFlashStartDelay_us, double * incFlashStartDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_StartDelay_GetRange)
    {
        return inst.m_peak_Flash_StartDelay_GetRange(hCam, minFlashStartDelay_us, maxFlashStartDelay_us, incFlashStartDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_StartDelay_Set(peak_camera_handle hCam, double flashStartDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_StartDelay_Set)
    {
        return inst.m_peak_Flash_StartDelay_Set(hCam, flashStartDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_StartDelay_Get(peak_camera_handle hCam, double * flashStartDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_StartDelay_Get)
    {
        return inst.m_peak_Flash_StartDelay_Get(hCam, flashStartDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Flash_EndDelay_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_EndDelay_GetAccessStatus)
    {
        return inst.m_peak_Flash_EndDelay_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_EndDelay_GetRange(peak_camera_handle hCam, double * minFlashEndDelay_us, double * maxFlashEndDelay_us, double * incFlashEndDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_EndDelay_GetRange)
    {
        return inst.m_peak_Flash_EndDelay_GetRange(hCam, minFlashEndDelay_us, maxFlashEndDelay_us, incFlashEndDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_EndDelay_Set(peak_camera_handle hCam, double flashEndDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_EndDelay_Set)
    {
        return inst.m_peak_Flash_EndDelay_Set(hCam, flashEndDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_EndDelay_Get(peak_camera_handle hCam, double * flashEndDelay_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_EndDelay_Get)
    {
        return inst.m_peak_Flash_EndDelay_Get(hCam, flashEndDelay_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Flash_Duration_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Duration_GetAccessStatus)
    {
        return inst.m_peak_Flash_Duration_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_Duration_GetRange(peak_camera_handle hCam, double * minFlashDuration_us, double * maxFlashDuration_us, double * incFlashDuration_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Duration_GetRange)
    {
        return inst.m_peak_Flash_Duration_GetRange(hCam, minFlashDuration_us, maxFlashDuration_us, incFlashDuration_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_Duration_Set(peak_camera_handle hCam, double flashDuration_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Duration_Set)
    {
        return inst.m_peak_Flash_Duration_Set(hCam, flashDuration_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Flash_Duration_Get(peak_camera_handle hCam, double * flashDuration_us)
{
    auto& inst = instance();
    if(inst.m_peak_Flash_Duration_Get)
    {
        return inst.m_peak_Flash_Duration_Get(hCam, flashDuration_us);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_PixelFormat_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_PixelFormat_GetAccessStatus)
    {
        return inst.m_peak_PixelFormat_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelFormat_GetList(peak_camera_handle hCam, peak_pixel_format * pixelFormatList, size_t * pixelFormatCount)
{
    auto& inst = instance();
    if(inst.m_peak_PixelFormat_GetList)
    {
        return inst.m_peak_PixelFormat_GetList(hCam, pixelFormatList, pixelFormatCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelFormat_Set(peak_camera_handle hCam, peak_pixel_format pixelFormat)
{
    auto& inst = instance();
    if(inst.m_peak_PixelFormat_Set)
    {
        return inst.m_peak_PixelFormat_Set(hCam, pixelFormat);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_PixelFormat_Get(peak_camera_handle hCam, peak_pixel_format * pixelFormat)
{
    auto& inst = instance();
    if(inst.m_peak_PixelFormat_Get)
    {
        return inst.m_peak_PixelFormat_Get(hCam, pixelFormat);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Gain_GetAccessStatus(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel)
{
    auto& inst = instance();
    if(inst.m_peak_Gain_GetAccessStatus)
    {
        return inst.m_peak_Gain_GetAccessStatus(hCam, gainType, gainChannel);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gain_GetChannelList(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel * gainChannelList, size_t * gainChannelCount)
{
    auto& inst = instance();
    if(inst.m_peak_Gain_GetChannelList)
    {
        return inst.m_peak_Gain_GetChannelList(hCam, gainType, gainChannelList, gainChannelCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gain_GetRange(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double * minGain, double * maxGain, double * incGain)
{
    auto& inst = instance();
    if(inst.m_peak_Gain_GetRange)
    {
        return inst.m_peak_Gain_GetRange(hCam, gainType, gainChannel, minGain, maxGain, incGain);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gain_Set(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double gain)
{
    auto& inst = instance();
    if(inst.m_peak_Gain_Set)
    {
        return inst.m_peak_Gain_Set(hCam, gainType, gainChannel, gain);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gain_Get(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel, double * gain)
{
    auto& inst = instance();
    if(inst.m_peak_Gain_Get)
    {
        return inst.m_peak_Gain_Get(hCam, gainType, gainChannel, gain);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Gamma_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Gamma_GetAccessStatus)
    {
        return inst.m_peak_Gamma_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gamma_GetRange(peak_camera_handle hCam, double * minGamma, double * maxGamma, double * incGamma)
{
    auto& inst = instance();
    if(inst.m_peak_Gamma_GetRange)
    {
        return inst.m_peak_Gamma_GetRange(hCam, minGamma, maxGamma, incGamma);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gamma_Set(peak_camera_handle hCam, double gamma)
{
    auto& inst = instance();
    if(inst.m_peak_Gamma_Set)
    {
        return inst.m_peak_Gamma_Set(hCam, gamma);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Gamma_Get(peak_camera_handle hCam, double * gamma)
{
    auto& inst = instance();
    if(inst.m_peak_Gamma_Get)
    {
        return inst.m_peak_Gamma_Get(hCam, gamma);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_ColorCorrection_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_GetAccessStatus)
    {
        return inst.m_peak_ColorCorrection_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Mode_GetList(peak_camera_handle hCam, peak_color_correction_mode * colorCorrectionModeList, size_t * colorCorrectionModeCount)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Mode_GetList)
    {
        return inst.m_peak_ColorCorrection_Mode_GetList(hCam, colorCorrectionModeList, colorCorrectionModeCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Mode_Set(peak_camera_handle hCam, peak_color_correction_mode colorCorrectionMode)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Mode_Set)
    {
        return inst.m_peak_ColorCorrection_Mode_Set(hCam, colorCorrectionMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Mode_Get(peak_camera_handle hCam, peak_color_correction_mode * colorCorrectionMode)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Mode_Get)
    {
        return inst.m_peak_ColorCorrection_Mode_Get(hCam, colorCorrectionMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_ColorCorrection_Matrix_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Matrix_GetAccessStatus)
    {
        return inst.m_peak_ColorCorrection_Matrix_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Matrix_GetRange(peak_camera_handle hCam, double * minMatrixElementValue, double * maxMatrixElementValue, double * incMatrixElementValue)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Matrix_GetRange)
    {
        return inst.m_peak_ColorCorrection_Matrix_GetRange(hCam, minMatrixElementValue, maxMatrixElementValue, incMatrixElementValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Matrix_Set(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Matrix_Set)
    {
        return inst.m_peak_ColorCorrection_Matrix_Set(hCam, colorCorrectionMatrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Matrix_Get(peak_camera_handle hCam, peak_matrix * colorCorrectionMatrix)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Matrix_Get)
    {
        return inst.m_peak_ColorCorrection_Matrix_Get(hCam, colorCorrectionMatrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ColorCorrection_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_Enable)
    {
        return inst.m_peak_ColorCorrection_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_ColorCorrection_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_ColorCorrection_IsEnabled)
    {
        return inst.m_peak_ColorCorrection_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_AutoBrightness_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_GetAccessStatus)
    {
        return inst.m_peak_AutoBrightness_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Target_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTarget, uint32_t * maxAutoBrightnessTarget, uint32_t * incAutoBrightnessTarget)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Target_GetRange)
    {
        return inst.m_peak_AutoBrightness_Target_GetRange(hCam, minAutoBrightnessTarget, maxAutoBrightnessTarget, incAutoBrightnessTarget);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Target_Set(peak_camera_handle hCam, uint32_t autoBrightnessTarget)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Target_Set)
    {
        return inst.m_peak_AutoBrightness_Target_Set(hCam, autoBrightnessTarget);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Target_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTarget)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Target_Get)
    {
        return inst.m_peak_AutoBrightness_Target_Get(hCam, autoBrightnessTarget);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_TargetTolerance_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTargetTolerance, uint32_t * maxAutoBrightnessTargetTolerance, uint32_t * incAutoBrightnessTargetTolerance)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_TargetTolerance_GetRange)
    {
        return inst.m_peak_AutoBrightness_TargetTolerance_GetRange(hCam, minAutoBrightnessTargetTolerance, maxAutoBrightnessTargetTolerance, incAutoBrightnessTargetTolerance);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_TargetTolerance_Set(peak_camera_handle hCam, uint32_t autoBrightnessTargetTolerance)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_TargetTolerance_Set)
    {
        return inst.m_peak_AutoBrightness_TargetTolerance_Set(hCam, autoBrightnessTargetTolerance);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_TargetTolerance_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTargetTolerance)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_TargetTolerance_Get)
    {
        return inst.m_peak_AutoBrightness_TargetTolerance_Get(hCam, autoBrightnessTargetTolerance);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_TargetPercentile_GetRange(peak_camera_handle hCam, double * minAutoBrightnessTargetPercentile, double * maxAutoBrightnessTargetPercentile, double * incAutoBrightnessTargetPercentile)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_TargetPercentile_GetRange)
    {
        return inst.m_peak_AutoBrightness_TargetPercentile_GetRange(hCam, minAutoBrightnessTargetPercentile, maxAutoBrightnessTargetPercentile, incAutoBrightnessTargetPercentile);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_TargetPercentile_Set(peak_camera_handle hCam, double autoBrightnessTargetPercentile)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_TargetPercentile_Set)
    {
        return inst.m_peak_AutoBrightness_TargetPercentile_Set(hCam, autoBrightnessTargetPercentile);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_TargetPercentile_Get(peak_camera_handle hCam, double * autoBrightnessTargetPercentile)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_TargetPercentile_Get)
    {
        return inst.m_peak_AutoBrightness_TargetPercentile_Get(hCam, autoBrightnessTargetPercentile);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoBrightnessROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_ROI_Mode_Set)
    {
        return inst.m_peak_AutoBrightness_ROI_Mode_Set(hCam, autoBrightnessROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoBrightnessROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_ROI_Mode_Get)
    {
        return inst.m_peak_AutoBrightness_ROI_Mode_Get(hCam, autoBrightnessROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoBrightnessROIOffset, peak_position * maxAutoBrightnessROIOffset, peak_position * incAutoBrightnessROIOffset)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_ROI_Offset_GetRange)
    {
        return inst.m_peak_AutoBrightness_ROI_Offset_GetRange(hCam, minAutoBrightnessROIOffset, maxAutoBrightnessROIOffset, incAutoBrightnessROIOffset);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoBrightnessROISize, peak_size * maxAutoBrightnessROISize, peak_size * incAutoBrightnessROISize)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_ROI_Size_GetRange)
    {
        return inst.m_peak_AutoBrightness_ROI_Size_GetRange(hCam, minAutoBrightnessROISize, maxAutoBrightnessROISize, incAutoBrightnessROISize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_ROI_Set(peak_camera_handle hCam, peak_roi autoBrightnessROI)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_ROI_Set)
    {
        return inst.m_peak_AutoBrightness_ROI_Set(hCam, autoBrightnessROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_ROI_Get(peak_camera_handle hCam, peak_roi * autoBrightnessROI)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_ROI_Get)
    {
        return inst.m_peak_AutoBrightness_ROI_Get(hCam, autoBrightnessROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_AutoBrightness_Exposure_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Exposure_GetAccessStatus)
    {
        return inst.m_peak_AutoBrightness_Exposure_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Exposure_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Exposure_Mode_Set)
    {
        return inst.m_peak_AutoBrightness_Exposure_Mode_Set(hCam, autoExposureMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Exposure_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoExposureMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Exposure_Mode_Get)
    {
        return inst.m_peak_AutoBrightness_Exposure_Mode_Get(hCam, autoExposureMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_AutoBrightness_Gain_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Gain_GetAccessStatus)
    {
        return inst.m_peak_AutoBrightness_Gain_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Gain_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Gain_Mode_Set)
    {
        return inst.m_peak_AutoBrightness_Gain_Mode_Set(hCam, autoGainMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoBrightness_Gain_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoGainMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoBrightness_Gain_Mode_Get)
    {
        return inst.m_peak_AutoBrightness_Gain_Mode_Get(hCam, autoGainMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_AutoWhiteBalance_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_GetAccessStatus)
    {
        return inst.m_peak_AutoWhiteBalance_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoWhiteBalanceROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_ROI_Mode_Set)
    {
        return inst.m_peak_AutoWhiteBalance_ROI_Mode_Set(hCam, autoWhiteBalanceROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoWhiteBalanceROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_ROI_Mode_Get)
    {
        return inst.m_peak_AutoWhiteBalance_ROI_Mode_Get(hCam, autoWhiteBalanceROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoWhiteBalanceROIOffset, peak_position * maxAutoWhiteBalanceROIOffset, peak_position * incAutoWhiteBalanceROIOffset)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_ROI_Offset_GetRange)
    {
        return inst.m_peak_AutoWhiteBalance_ROI_Offset_GetRange(hCam, minAutoWhiteBalanceROIOffset, maxAutoWhiteBalanceROIOffset, incAutoWhiteBalanceROIOffset);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoWhiteBalanceROISize, peak_size * maxAutoWhiteBalanceROISize, peak_size * incAutoWhiteBalanceROISize)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_ROI_Size_GetRange)
    {
        return inst.m_peak_AutoWhiteBalance_ROI_Size_GetRange(hCam, minAutoWhiteBalanceROISize, maxAutoWhiteBalanceROISize, incAutoWhiteBalanceROISize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_ROI_Set(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_ROI_Set)
    {
        return inst.m_peak_AutoWhiteBalance_ROI_Set(hCam, autoWhiteBalanceROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_ROI_Get(peak_camera_handle hCam, peak_roi * autoWhiteBalanceROI)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_ROI_Get)
    {
        return inst.m_peak_AutoWhiteBalance_ROI_Get(hCam, autoWhiteBalanceROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_Mode_Set)
    {
        return inst.m_peak_AutoWhiteBalance_Mode_Set(hCam, autoWhiteBalanceMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_AutoWhiteBalance_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoWhiteBalanceMode)
{
    auto& inst = instance();
    if(inst.m_peak_AutoWhiteBalance_Mode_Get)
    {
        return inst.m_peak_AutoWhiteBalance_Mode_Get(hCam, autoWhiteBalanceMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_ROI_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_ROI_GetAccessStatus)
    {
        return inst.m_peak_ROI_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minROIOffset, peak_position * maxROIOffset, peak_position * incROIOffset)
{
    auto& inst = instance();
    if(inst.m_peak_ROI_Offset_GetRange)
    {
        return inst.m_peak_ROI_Offset_GetRange(hCam, minROIOffset, maxROIOffset, incROIOffset);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minROISize, peak_size * maxROISize, peak_size * incROISize)
{
    auto& inst = instance();
    if(inst.m_peak_ROI_Size_GetRange)
    {
        return inst.m_peak_ROI_Size_GetRange(hCam, minROISize, maxROISize, incROISize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ROI_Set(peak_camera_handle hCam, peak_roi roi)
{
    auto& inst = instance();
    if(inst.m_peak_ROI_Set)
    {
        return inst.m_peak_ROI_Set(hCam, roi);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_ROI_Get(peak_camera_handle hCam, peak_roi * roi)
{
    auto& inst = instance();
    if(inst.m_peak_ROI_Get)
    {
        return inst.m_peak_ROI_Get(hCam, roi);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Binning_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Binning_GetAccessStatus)
    {
        return inst.m_peak_Binning_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Binning_FactorX_GetList(peak_camera_handle hCam, uint32_t * binningFactorXList, size_t * binningFactorXCount)
{
    auto& inst = instance();
    if(inst.m_peak_Binning_FactorX_GetList)
    {
        return inst.m_peak_Binning_FactorX_GetList(hCam, binningFactorXList, binningFactorXCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Binning_FactorY_GetList(peak_camera_handle hCam, uint32_t * binningFactorYList, size_t * binningFactorYCount)
{
    auto& inst = instance();
    if(inst.m_peak_Binning_FactorY_GetList)
    {
        return inst.m_peak_Binning_FactorY_GetList(hCam, binningFactorYList, binningFactorYCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Binning_Set(peak_camera_handle hCam, uint32_t binningFactorX, uint32_t binningFactorY)
{
    auto& inst = instance();
    if(inst.m_peak_Binning_Set)
    {
        return inst.m_peak_Binning_Set(hCam, binningFactorX, binningFactorY);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Binning_Get(peak_camera_handle hCam, uint32_t * binningFactorX, uint32_t * binningFactorY)
{
    auto& inst = instance();
    if(inst.m_peak_Binning_Get)
    {
        return inst.m_peak_Binning_Get(hCam, binningFactorX, binningFactorY);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Decimation_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Decimation_GetAccessStatus)
    {
        return inst.m_peak_Decimation_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Decimation_FactorX_GetList(peak_camera_handle hCam, uint32_t * decimationFactorXList, size_t * decimationFactorXCount)
{
    auto& inst = instance();
    if(inst.m_peak_Decimation_FactorX_GetList)
    {
        return inst.m_peak_Decimation_FactorX_GetList(hCam, decimationFactorXList, decimationFactorXCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Decimation_FactorY_GetList(peak_camera_handle hCam, uint32_t * decimationFactorYList, size_t * decimationFactorYCount)
{
    auto& inst = instance();
    if(inst.m_peak_Decimation_FactorY_GetList)
    {
        return inst.m_peak_Decimation_FactorY_GetList(hCam, decimationFactorYList, decimationFactorYCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Decimation_Set(peak_camera_handle hCam, uint32_t decimationFactorX, uint32_t decimationFactorY)
{
    auto& inst = instance();
    if(inst.m_peak_Decimation_Set)
    {
        return inst.m_peak_Decimation_Set(hCam, decimationFactorX, decimationFactorY);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Decimation_Get(peak_camera_handle hCam, uint32_t * decimationFactorX, uint32_t * decimationFactorY)
{
    auto& inst = instance();
    if(inst.m_peak_Decimation_Get)
    {
        return inst.m_peak_Decimation_Get(hCam, decimationFactorX, decimationFactorY);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Mirror_LeftRight_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Mirror_LeftRight_GetAccessStatus)
    {
        return inst.m_peak_Mirror_LeftRight_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Mirror_LeftRight_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_Mirror_LeftRight_Enable)
    {
        return inst.m_peak_Mirror_LeftRight_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Mirror_LeftRight_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Mirror_LeftRight_IsEnabled)
    {
        return inst.m_peak_Mirror_LeftRight_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_Mirror_UpDown_GetAccessStatus(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Mirror_UpDown_GetAccessStatus)
    {
        return inst.m_peak_Mirror_UpDown_GetAccessStatus(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_Mirror_UpDown_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_Mirror_UpDown_Enable)
    {
        return inst.m_peak_Mirror_UpDown_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_Mirror_UpDown_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_Mirror_UpDown_IsEnabled)
    {
        return inst.m_peak_Mirror_UpDown_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_CameraMemory_Area_GetAccessStatus(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea)
{
    auto& inst = instance();
    if(inst.m_peak_CameraMemory_Area_GetAccessStatus)
    {
        return inst.m_peak_CameraMemory_Area_GetAccessStatus(hCam, cameraMemoryArea);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraMemory_Area_GetList(peak_camera_handle hCam, peak_camera_memory_area * cameraMemoryAreaList, size_t * cameraMemoryAreaCount)
{
    auto& inst = instance();
    if(inst.m_peak_CameraMemory_Area_GetList)
    {
        return inst.m_peak_CameraMemory_Area_GetList(hCam, cameraMemoryAreaList, cameraMemoryAreaCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraMemory_Area_Size_Get(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, size_t * cameraMemoryAreaSize)
{
    auto& inst = instance();
    if(inst.m_peak_CameraMemory_Area_Size_Get)
    {
        return inst.m_peak_CameraMemory_Area_Size_Get(hCam, cameraMemoryArea, cameraMemoryAreaSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraMemory_Area_Data_Clear(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea)
{
    auto& inst = instance();
    if(inst.m_peak_CameraMemory_Area_Data_Clear)
    {
        return inst.m_peak_CameraMemory_Area_Data_Clear(hCam, cameraMemoryArea);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraMemory_Area_Data_Write(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, const uint8_t * data, size_t dataSize)
{
    auto& inst = instance();
    if(inst.m_peak_CameraMemory_Area_Data_Write)
    {
        return inst.m_peak_CameraMemory_Area_Data_Write(hCam, cameraMemoryArea, data, dataSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_CameraMemory_Area_Data_Read(peak_camera_handle hCam, peak_camera_memory_area cameraMemoryArea, uint8_t * data, size_t dataSize)
{
    auto& inst = instance();
    if(inst.m_peak_CameraMemory_Area_Data_Read)
    {
        return inst.m_peak_CameraMemory_Area_Data_Read(hCam, cameraMemoryArea, data, dataSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_EnableWriteAccess(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_EnableWriteAccess)
    {
        return inst.m_peak_GFA_EnableWriteAccess(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_GFA_IsWriteAccessEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_IsWriteAccessEnabled)
    {
        return inst.m_peak_GFA_IsWriteAccessEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_GFA_Feature_GetAccessStatus(peak_camera_handle hCam, peak_gfa_module module, const char * featureName)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Feature_GetAccessStatus)
    {
        return inst.m_peak_GFA_Feature_GetAccessStatus(hCam, module, featureName);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_GFA_Float_HasRange(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Float_HasRange)
    {
        return inst.m_peak_GFA_Float_HasRange(hCam, module, floatFeatureName);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Float_GetRange(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * minFloatValue, double * maxFloatValue, double * incFloatValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Float_GetRange)
    {
        return inst.m_peak_GFA_Float_GetRange(hCam, module, floatFeatureName, minFloatValue, maxFloatValue, incFloatValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Float_GetList(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * floatList, size_t * floatCount)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Float_GetList)
    {
        return inst.m_peak_GFA_Float_GetList(hCam, module, floatFeatureName, floatList, floatCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Float_Set(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double floatValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Float_Set)
    {
        return inst.m_peak_GFA_Float_Set(hCam, module, floatFeatureName, floatValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Float_Get(peak_camera_handle hCam, peak_gfa_module module, const char * floatFeatureName, double * floatValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Float_Get)
    {
        return inst.m_peak_GFA_Float_Get(hCam, module, floatFeatureName, floatValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_GFA_Integer_HasRange(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Integer_HasRange)
    {
        return inst.m_peak_GFA_Integer_HasRange(hCam, module, integerFeatureName);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Integer_GetRange(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * minIntegerValue, int64_t * maxIntegerValue, int64_t * incIntegerValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Integer_GetRange)
    {
        return inst.m_peak_GFA_Integer_GetRange(hCam, module, integerFeatureName, minIntegerValue, maxIntegerValue, incIntegerValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Integer_GetList(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * integerList, size_t * integerCount)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Integer_GetList)
    {
        return inst.m_peak_GFA_Integer_GetList(hCam, module, integerFeatureName, integerList, integerCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Integer_Set(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t integerValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Integer_Set)
    {
        return inst.m_peak_GFA_Integer_Set(hCam, module, integerFeatureName, integerValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Integer_Get(peak_camera_handle hCam, peak_gfa_module module, const char * integerFeatureName, int64_t * integerValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Integer_Get)
    {
        return inst.m_peak_GFA_Integer_Get(hCam, module, integerFeatureName, integerValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Boolean_Set(peak_camera_handle hCam, peak_gfa_module module, const char * booleanFeatureName, peak_bool booleanValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Boolean_Set)
    {
        return inst.m_peak_GFA_Boolean_Set(hCam, module, booleanFeatureName, booleanValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Boolean_Get(peak_camera_handle hCam, peak_gfa_module module, const char * booleanFeatureName, peak_bool * booleanValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Boolean_Get)
    {
        return inst.m_peak_GFA_Boolean_Get(hCam, module, booleanFeatureName, booleanValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_String_Set(peak_camera_handle hCam, peak_gfa_module module, const char * stringFeatureName, const char * stringValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_String_Set)
    {
        return inst.m_peak_GFA_String_Set(hCam, module, stringFeatureName, stringValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_String_Get(peak_camera_handle hCam, peak_gfa_module module, const char * stringFeatureName, char * stringValue, size_t * stringValueSize)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_String_Get)
    {
        return inst.m_peak_GFA_String_Get(hCam, module, stringFeatureName, stringValue, stringValueSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Command_Execute(peak_camera_handle hCam, peak_gfa_module module, const char * commandFeatureName)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Command_Execute)
    {
        return inst.m_peak_GFA_Command_Execute(hCam, module, commandFeatureName);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Command_WaitForDone(peak_camera_handle hCam, peak_gfa_module module, const char * commandFeatureName, uint32_t timeout_ms)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Command_WaitForDone)
    {
        return inst.m_peak_GFA_Command_WaitForDone(hCam, module, commandFeatureName, timeout_ms);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Enumeration_GetList(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, peak_gfa_enumeration_entry * enumerationEntryList, size_t * enumerationEntryCount)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Enumeration_GetList)
    {
        return inst.m_peak_GFA_Enumeration_GetList(hCam, module, enumerationFeatureName, enumerationEntryList, enumerationEntryCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_GFA_EnumerationEntry_GetAccessStatus(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const peak_gfa_enumeration_entry * enumerationEntry)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_EnumerationEntry_GetAccessStatus)
    {
        return inst.m_peak_GFA_EnumerationEntry_GetAccessStatus(hCam, module, enumerationFeatureName, enumerationEntry);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const char * enumerationEntrySymbolicValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue)
    {
        return inst.m_peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue(hCam, module, enumerationFeatureName, enumerationEntrySymbolicValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_ACCESS_STATUS DynamicLoader::peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, int64_t enumerationEntryIntegerValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue)
    {
        return inst.m_peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue(hCam, module, enumerationFeatureName, enumerationEntryIntegerValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Enumeration_Set(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const peak_gfa_enumeration_entry * enumerationEntry)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Enumeration_Set)
    {
        return inst.m_peak_GFA_Enumeration_Set(hCam, module, enumerationFeatureName, enumerationEntry);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Enumeration_SetBySymbolicValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, const char * enumerationEntrySymbolicValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Enumeration_SetBySymbolicValue)
    {
        return inst.m_peak_GFA_Enumeration_SetBySymbolicValue(hCam, module, enumerationFeatureName, enumerationEntrySymbolicValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Enumeration_SetByIntegerValue(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, int64_t enumerationEntryIntegerValue)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Enumeration_SetByIntegerValue)
    {
        return inst.m_peak_GFA_Enumeration_SetByIntegerValue(hCam, module, enumerationFeatureName, enumerationEntryIntegerValue);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Enumeration_Get(peak_camera_handle hCam, peak_gfa_module module, const char * enumerationFeatureName, peak_gfa_enumeration_entry * enumerationEntry)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Enumeration_Get)
    {
        return inst.m_peak_GFA_Enumeration_Get(hCam, module, enumerationFeatureName, enumerationEntry);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Register_Set(peak_camera_handle hCam, peak_gfa_module module, const char * registerFeatureName, const uint8_t * registerValue, size_t registerValueSize)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Register_Set)
    {
        return inst.m_peak_GFA_Register_Set(hCam, module, registerFeatureName, registerValue, registerValueSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Register_Get(peak_camera_handle hCam, peak_gfa_module module, const char * registerFeatureName, uint8_t * registerValue, size_t * registerValueSize)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Register_Get)
    {
        return inst.m_peak_GFA_Register_Get(hCam, module, registerFeatureName, registerValue, registerValueSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Data_Write(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, const uint8_t * data, size_t dataSize)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Data_Write)
    {
        return inst.m_peak_GFA_Data_Write(hCam, module, address, data, dataSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_GFA_Data_Read(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, uint8_t * data, size_t dataSize)
{
    auto& inst = instance();
    if(inst.m_peak_GFA_Data_Read)
    {
        return inst.m_peak_GFA_Data_Read(hCam, module, address, data, dataSize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_PixelFormat_GetList(peak_camera_handle hCam, peak_pixel_format inputPixelFormat, peak_pixel_format * outputPixelFormatList, size_t * outputPixelFormatCount)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_PixelFormat_GetList)
    {
        return inst.m_peak_IPL_PixelFormat_GetList(hCam, inputPixelFormat, outputPixelFormatList, outputPixelFormatCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_PixelFormat_Set(peak_camera_handle hCam, peak_pixel_format pixelFormat)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_PixelFormat_Set)
    {
        return inst.m_peak_IPL_PixelFormat_Set(hCam, pixelFormat);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_PixelFormat_Get(peak_camera_handle hCam, peak_pixel_format * pixelFormat)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_PixelFormat_Get)
    {
        return inst.m_peak_IPL_PixelFormat_Get(hCam, pixelFormat);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Gain_GetRange(peak_camera_handle hCam, peak_gain_channel gainChannel, double * minGain, double * maxGain, double * incGain)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Gain_GetRange)
    {
        return inst.m_peak_IPL_Gain_GetRange(hCam, gainChannel, minGain, maxGain, incGain);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Gain_Set(peak_camera_handle hCam, peak_gain_channel gainChannel, double gain)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Gain_Set)
    {
        return inst.m_peak_IPL_Gain_Set(hCam, gainChannel, gain);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Gain_Get(peak_camera_handle hCam, peak_gain_channel gainChannel, double * gain)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Gain_Get)
    {
        return inst.m_peak_IPL_Gain_Get(hCam, gainChannel, gain);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Gamma_GetRange(peak_camera_handle hCam, double * minGamma, double * maxGamma, double * incGamma)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Gamma_GetRange)
    {
        return inst.m_peak_IPL_Gamma_GetRange(hCam, minGamma, maxGamma, incGamma);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Gamma_Set(peak_camera_handle hCam, double gamma)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Gamma_Set)
    {
        return inst.m_peak_IPL_Gamma_Set(hCam, gamma);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Gamma_Get(peak_camera_handle hCam, double * gamma)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Gamma_Get)
    {
        return inst.m_peak_IPL_Gamma_Get(hCam, gamma);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_ColorCorrection_Matrix_Set(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_ColorCorrection_Matrix_Set)
    {
        return inst.m_peak_IPL_ColorCorrection_Matrix_Set(hCam, colorCorrectionMatrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_ColorCorrection_Matrix_Get(peak_camera_handle hCam, peak_matrix * colorCorrectionMatrix)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_ColorCorrection_Matrix_Get)
    {
        return inst.m_peak_IPL_ColorCorrection_Matrix_Get(hCam, colorCorrectionMatrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_ColorCorrection_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_ColorCorrection_Enable)
    {
        return inst.m_peak_IPL_ColorCorrection_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IPL_ColorCorrection_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_ColorCorrection_IsEnabled)
    {
        return inst.m_peak_IPL_ColorCorrection_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Target_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTarget, uint32_t * maxAutoBrightnessTarget, uint32_t * incAutoBrightnessTarget)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Target_GetRange)
    {
        return inst.m_peak_IPL_AutoBrightness_Target_GetRange(hCam, minAutoBrightnessTarget, maxAutoBrightnessTarget, incAutoBrightnessTarget);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Target_Set(peak_camera_handle hCam, uint32_t autoBrightnessTarget)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Target_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_Target_Set(hCam, autoBrightnessTarget);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Target_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTarget)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Target_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_Target_Get(hCam, autoBrightnessTarget);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_TargetTolerance_GetRange(peak_camera_handle hCam, uint32_t * minAutoBrightnessTargetTolerance, uint32_t * maxAutoBrightnessTargetTolerance, uint32_t * incAutoBrightnessTargetTolerance)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_TargetTolerance_GetRange)
    {
        return inst.m_peak_IPL_AutoBrightness_TargetTolerance_GetRange(hCam, minAutoBrightnessTargetTolerance, maxAutoBrightnessTargetTolerance, incAutoBrightnessTargetTolerance);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_TargetTolerance_Set(peak_camera_handle hCam, uint32_t autoBrightnessTargetTolerance)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_TargetTolerance_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_TargetTolerance_Set(hCam, autoBrightnessTargetTolerance);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_TargetTolerance_Get(peak_camera_handle hCam, uint32_t * autoBrightnessTargetTolerance)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_TargetTolerance_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_TargetTolerance_Get(hCam, autoBrightnessTargetTolerance);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_TargetPercentile_GetRange(peak_camera_handle hCam, double * minAutoBrightnessTargetPercentile, double * maxAutoBrightnessTargetPercentile, double * incAutoBrightnessTargetPercentile)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_TargetPercentile_GetRange)
    {
        return inst.m_peak_IPL_AutoBrightness_TargetPercentile_GetRange(hCam, minAutoBrightnessTargetPercentile, maxAutoBrightnessTargetPercentile, incAutoBrightnessTargetPercentile);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_TargetPercentile_Set(peak_camera_handle hCam, double autoBrightnessTargetPercentile)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_TargetPercentile_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_TargetPercentile_Set(hCam, autoBrightnessTargetPercentile);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_TargetPercentile_Get(peak_camera_handle hCam, double * autoBrightnessTargetPercentile)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_TargetPercentile_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_TargetPercentile_Get(hCam, autoBrightnessTargetPercentile);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoBrightnessROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_ROI_Mode_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_ROI_Mode_Set(hCam, autoBrightnessROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoBrightnessROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_ROI_Mode_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_ROI_Mode_Get(hCam, autoBrightnessROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoBrightnessROIOffset, peak_position * maxAutoBrightnessROIOffset, peak_position * incAutoBrightnessROIOffset)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_ROI_Offset_GetRange)
    {
        return inst.m_peak_IPL_AutoBrightness_ROI_Offset_GetRange(hCam, minAutoBrightnessROIOffset, maxAutoBrightnessROIOffset, incAutoBrightnessROIOffset);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoBrightnessROISize, peak_size * maxAutoBrightnessROISize, peak_size * incAutoBrightnessROISize)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_ROI_Size_GetRange)
    {
        return inst.m_peak_IPL_AutoBrightness_ROI_Size_GetRange(hCam, minAutoBrightnessROISize, maxAutoBrightnessROISize, incAutoBrightnessROISize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_ROI_Set(peak_camera_handle hCam, peak_roi autoBrightnessROI)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_ROI_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_ROI_Set(hCam, autoBrightnessROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_ROI_Get(peak_camera_handle hCam, peak_roi * autoBrightnessROI)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_ROI_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_ROI_Get(hCam, autoBrightnessROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Exposure_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Exposure_Mode_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_Exposure_Mode_Set(hCam, autoExposureMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Exposure_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoExposureMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Exposure_Mode_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_Exposure_Mode_Get(hCam, autoExposureMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Gain_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Gain_Mode_Set)
    {
        return inst.m_peak_IPL_AutoBrightness_Gain_Mode_Set(hCam, autoGainMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoBrightness_Gain_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoGainMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoBrightness_Gain_Mode_Get)
    {
        return inst.m_peak_IPL_AutoBrightness_Gain_Mode_Get(hCam, autoGainMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_ROI_Mode_Set(peak_camera_handle hCam, peak_auto_feature_roi_mode autoWhiteBalanceROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_ROI_Mode_Set)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_ROI_Mode_Set(hCam, autoWhiteBalanceROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_ROI_Mode_Get(peak_camera_handle hCam, peak_auto_feature_roi_mode * autoWhiteBalanceROIMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_ROI_Mode_Get)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_ROI_Mode_Get(hCam, autoWhiteBalanceROIMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position * minAutoWhiteBalanceROIOffset, peak_position * maxAutoWhiteBalanceROIOffset, peak_position * incAutoWhiteBalanceROIOffset)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange(hCam, minAutoWhiteBalanceROIOffset, maxAutoWhiteBalanceROIOffset, incAutoWhiteBalanceROIOffset);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_ROI_Size_GetRange(peak_camera_handle hCam, peak_size * minAutoWhiteBalanceROISize, peak_size * maxAutoWhiteBalanceROISize, peak_size * incAutoWhiteBalanceROISize)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_ROI_Size_GetRange(hCam, minAutoWhiteBalanceROISize, maxAutoWhiteBalanceROISize, incAutoWhiteBalanceROISize);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_ROI_Set(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_ROI_Set)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_ROI_Set(hCam, autoWhiteBalanceROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_ROI_Get(peak_camera_handle hCam, peak_roi * autoWhiteBalanceROI)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_ROI_Get)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_ROI_Get(hCam, autoWhiteBalanceROI);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_Mode_Set)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_Mode_Set(hCam, autoWhiteBalanceMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_AutoWhiteBalance_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode * autoWhiteBalanceMode)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_AutoWhiteBalance_Mode_Get)
    {
        return inst.m_peak_IPL_AutoWhiteBalance_Mode_Get(hCam, autoWhiteBalanceMode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_HotpixelCorrection_Sensitivity_Set(peak_camera_handle hCam, peak_hotpixel_correction_sensitivity hotpixelCorrectionSensitivity)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_Sensitivity_Set)
    {
        return inst.m_peak_IPL_HotpixelCorrection_Sensitivity_Set(hCam, hotpixelCorrectionSensitivity);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_HotpixelCorrection_Sensitivity_Get(peak_camera_handle hCam, peak_hotpixel_correction_sensitivity * hotpixelCorrectionSensitivity)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_Sensitivity_Get)
    {
        return inst.m_peak_IPL_HotpixelCorrection_Sensitivity_Get(hCam, hotpixelCorrectionSensitivity);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_HotpixelCorrection_GetList(peak_camera_handle hCam, peak_position * hotpixelList, size_t * hotpixelCount)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_GetList)
    {
        return inst.m_peak_IPL_HotpixelCorrection_GetList(hCam, hotpixelList, hotpixelCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_HotpixelCorrection_SetList(peak_camera_handle hCam, peak_position * hotpixelList, size_t hotpixelCount)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_SetList)
    {
        return inst.m_peak_IPL_HotpixelCorrection_SetList(hCam, hotpixelList, hotpixelCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_HotpixelCorrection_ResetList(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_ResetList)
    {
        return inst.m_peak_IPL_HotpixelCorrection_ResetList(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_HotpixelCorrection_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_Enable)
    {
        return inst.m_peak_IPL_HotpixelCorrection_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IPL_HotpixelCorrection_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_HotpixelCorrection_IsEnabled)
    {
        return inst.m_peak_IPL_HotpixelCorrection_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Mirror_UpDown_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Mirror_UpDown_Enable)
    {
        return inst.m_peak_IPL_Mirror_UpDown_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IPL_Mirror_UpDown_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Mirror_UpDown_IsEnabled)
    {
        return inst.m_peak_IPL_Mirror_UpDown_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_Mirror_LeftRight_Enable(peak_camera_handle hCam, peak_bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Mirror_LeftRight_Enable)
    {
        return inst.m_peak_IPL_Mirror_LeftRight_Enable(hCam, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_BOOL DynamicLoader::peak_IPL_Mirror_LeftRight_IsEnabled(peak_camera_handle hCam)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_Mirror_LeftRight_IsEnabled)
    {
        return inst.m_peak_IPL_Mirror_LeftRight_IsEnabled(hCam);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_ProcessFrame(peak_camera_handle hCam, peak_frame_handle hFrame, peak_frame_handle * hResultFrame)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_ProcessFrame)
    {
        return inst.m_peak_IPL_ProcessFrame(hCam, hFrame, hResultFrame);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_IPL_ProcessFrameInplace(peak_camera_handle hCam, peak_frame_handle hFrame)
{
    auto& inst = instance();
    if(inst.m_peak_IPL_ProcessFrameInplace)
    {
        return inst.m_peak_IPL_ProcessFrameInplace(hCam, hFrame);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Open(peak_video_handle * hVideo, const char * fileName, peak_video_container container, peak_video_encoder encoder)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Open)
    {
        return inst.m_peak_VideoWriter_Open(hVideo, fileName, container, encoder);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Close(peak_video_handle hVideo)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Close)
    {
        return inst.m_peak_VideoWriter_Close(hVideo);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_AddFrame(peak_video_handle hVideo, peak_frame_handle hFrame)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_AddFrame)
    {
        return inst.m_peak_VideoWriter_AddFrame(hVideo, hFrame);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Container_GetEncoderList(peak_video_container container, peak_video_encoder * encoderList, size_t * encoderCount)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Container_GetEncoderList)
    {
        return inst.m_peak_VideoWriter_Container_GetEncoderList(container, encoderList, encoderCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Encoder_GetPixelFormatList(peak_video_encoder encoder, peak_pixel_format * pixelFormatList, size_t * pixelFormatCount)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Encoder_GetPixelFormatList)
    {
        return inst.m_peak_VideoWriter_Encoder_GetPixelFormatList(encoder, pixelFormatList, pixelFormatCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Encoder_GetContainerList(peak_video_encoder encoder, peak_video_container * containerList, size_t * containerCount)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Encoder_GetContainerList)
    {
        return inst.m_peak_VideoWriter_Encoder_GetContainerList(encoder, containerList, containerCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_GetInfo(peak_video_handle hVideo, peak_video_info * videoInfo)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_GetInfo)
    {
        return inst.m_peak_VideoWriter_GetInfo(hVideo, videoInfo);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Container_Option_Set(peak_video_handle hVideo, peak_video_container_option containerOption, const void * value, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Container_Option_Set)
    {
        return inst.m_peak_VideoWriter_Container_Option_Set(hVideo, containerOption, value, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Container_Option_Get(peak_video_handle hVideo, peak_video_container_option containerOption, void * value, size_t count, size_t * outCount)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Container_Option_Get)
    {
        return inst.m_peak_VideoWriter_Container_Option_Get(hVideo, containerOption, value, count, outCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Encoder_Option_Set(peak_video_handle hVideo, peak_video_encoder_option encoderOption, const void * value, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Encoder_Option_Set)
    {
        return inst.m_peak_VideoWriter_Encoder_Option_Set(hVideo, encoderOption, value, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_Encoder_Option_Get(peak_video_handle hVideo, peak_video_encoder_option encoderOption, void * value, size_t count, size_t * outCount)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_Encoder_Option_Get)
    {
        return inst.m_peak_VideoWriter_Encoder_Option_Get(hVideo, encoderOption, value, count, outCount);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_API_STATUS DynamicLoader::peak_VideoWriter_WaitUntilQueueEmpty(peak_video_handle hVideo, int32_t timeout_ms)
{
    auto& inst = instance();
    if(inst.m_peak_VideoWriter_WaitUntilQueueEmpty)
    {
        return inst.m_peak_VideoWriter_WaitUntilQueueEmpty(hVideo, timeout_ms);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

} /* namespace dynamic */
} /* namespace peak_comfortC */

