/*!
 * \file    backend.c
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
 *
 * \brief   The Backend implements an easy way to display images from a
 *          camera in a QT widgets window. It can be used for other applications as well.
 *
 * \version 1.0.0
 *
 * Copyright (C) 2022, IDS Imaging Development Systems GmbH.
 *
 * The information in this document is subject to change without notice
 * and should not be construed as a commitment by IDS Imaging Development Systems GmbH.
 * IDS Imaging Development Systems GmbH does not assume any responsibility for any errors
 * that may appear in this document.
 *
 * This document, or source code, is provided solely as an example of how to utilize
 * IDS Imaging Development Systems GmbH software libraries in a sample application.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for the use or reliability of any portion of this document.
 *
 * General permission to copy or modify is hereby granted.
 */

#define VERSION "1.0.0"

#include "backend.h"
#include <malloc.h>
#include <stdio.h>


static peak_camera_handle hCam = PEAK_INVALID_HANDLE;
static bool isColorConversion = false;
static errorCallback g_callback = NULL;
static int g_status = 0;
static void* g_context = NULL;
static bool acquisitionRunning = false;

static bool checkForSuccess(peak_status status, bool continueExecution);


int backend_start()
{
    // Initialize library
    peak_status status = peak_Library_Init();
    if (!checkForSuccess(status, false))
        return status;

    // Update camera list
    status = peak_CameraList_Update(NULL);
    if (!checkForSuccess(status, false))
        return status;

    // Open first available camera
    status = peak_Camera_OpenFirstAvailable(&hCam);
    if (!checkForSuccess(status, false))
        return status;

    // Reset the camera setting to default to apply the raw pixelformat of the camera
    status = peak_Camera_ResetToDefaultSettings(hCam);
    checkForSuccess(status, true);

    return status;
}


int backend_acquisition_prepare()
{
    if (hCam == PEAK_INVALID_HANDLE)
    {
        if (g_callback)
        {
            g_callback("Trying to configure camera before it was opened. Open camera first.", -1, g_context);
        }
        return -1;
    }
    if (peak_Acquisition_IsStarted(hCam))
    {
        if (g_callback)
        {
            g_callback("Acquisition already running.", -1, g_context);
        }
        return -1;
    }

    ////////////////////////////////
    // Set suitable IPL PixelFormat
    ////////////////////////////////

    // Get current PixelFormat from the camera which should be the raw PixelFormat after the reset to default
    peak_pixel_format currentPixelFormat = PEAK_PIXEL_FORMAT_INVALID;
    peak_status status = peak_PixelFormat_Get(hCam, &currentPixelFormat);
    if (!checkForSuccess(status, true))
        return status;

    // No conversion needed when pixelformat is monochrome
    if (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO8)
    {
        // Set IPL PixelFormat for inplace processing
        status = peak_IPL_PixelFormat_Set(hCam, PEAK_PIXEL_FORMAT_MONO8);
        if (!checkForSuccess(status, true))
        {
            return status;
        }
    }
    else
    {
        isColorConversion = true;

        bool isMono = backend_camera_isMono();

        // Get list of all currently available IPL pixelformats

        // First step: get the number of list items
        size_t pixelFormatCount = 0;
        status = peak_IPL_PixelFormat_GetList(hCam, currentPixelFormat, NULL, &pixelFormatCount);
        if (!checkForSuccess(status, true))
            return status;

        // Second step: get the list
        peak_pixel_format* pixelFormats = (peak_pixel_format*)calloc(
            pixelFormatCount, sizeof(peak_pixel_format));
        status = peak_IPL_PixelFormat_GetList(hCam, currentPixelFormat, pixelFormats, &pixelFormatCount);
        if (!checkForSuccess(status, true))
        {
            free(pixelFormats);
            return status;
        }

        // Check which pixelFormat is supported
        bool mono8Supported = false;
        bool bgra8Supported = false;
        bool rgb8Supported = false;
        bool rgba8Supported = false;
        bool bgr8Supported = false;
        for (size_t i = 0; i < pixelFormatCount; i++)
        {
            if (isMono)
            {
                if (pixelFormats[i] == PEAK_PIXEL_FORMAT_MONO8)
                {
                    mono8Supported = true;
                    break;
                }
            }
            else
            {
                if (pixelFormats[i] == PEAK_PIXEL_FORMAT_BGRA8)
                {
                    // Preferred pixel format found, break
                    bgra8Supported = true;
                    break;
                }
                else if (pixelFormats[i] == PEAK_PIXEL_FORMAT_RGB8)
                {
                    rgb8Supported = true;
                }
                else if (pixelFormats[i] == PEAK_PIXEL_FORMAT_RGBA8)
                {
                    rgba8Supported = true;
                }
                else if (pixelFormats[i] == PEAK_PIXEL_FORMAT_BGR8)
                {
                    bgr8Supported = true;
                }
            }
        }

        // Set IPL PixelFormat for later host image processing
        if (mono8Supported)
        {
            status = peak_IPL_PixelFormat_Set(hCam, PEAK_PIXEL_FORMAT_MONO8);
            if (!checkForSuccess(status, true))
            {
                free(pixelFormats);
                return status;
            }
        }
        else if (bgra8Supported)
        {
            status = peak_IPL_PixelFormat_Set(hCam, PEAK_PIXEL_FORMAT_BGRA8);
            if (!checkForSuccess(status, true))
            {
                free(pixelFormats);
                return status;
            }
        }
        else if (rgb8Supported)
        {
            status = peak_IPL_PixelFormat_Set(hCam, PEAK_PIXEL_FORMAT_RGB8);
            if (!checkForSuccess(status, true))
            {
                free(pixelFormats);
                return status;
            }
        }
        else if (rgba8Supported)
        {
            status = peak_IPL_PixelFormat_Set(hCam, PEAK_PIXEL_FORMAT_RGBA8);
            if (!checkForSuccess(status, true))
            {
                free(pixelFormats);
                return status;
            }
        }
        else if (bgr8Supported)
        {
            status = peak_IPL_PixelFormat_Set(hCam, PEAK_PIXEL_FORMAT_BGR8);
            if (!checkForSuccess(status, true))
            {
                free(pixelFormats);
                return status;
            }
        }
        else
        {
            // Standard pixel formats not supported, use the first available in the list
            status = peak_IPL_PixelFormat_Set(hCam, pixelFormats[0]);
            if (!checkForSuccess(status, true))
            {
                free(pixelFormats);
                return status;
            }
        }

        free(pixelFormats);
    }

    return PEAK_STATUS_SUCCESS;
}


int backend_acquisition_start()
{
    if (hCam == PEAK_INVALID_HANDLE)
    {
        if (g_callback)
        {
            g_callback("Trying to start image acquisition on camera before it was opened. Open camera first.", -1, g_context);
        }
        return -1;
    }
    if (peak_Acquisition_IsStarted(hCam))
    {
        if (g_callback)
        {
            g_callback("Acquisition already running.", -1, g_context);
        }
        return -1;
    }

    // Start acquisition with infinite number of frames,
    // acquisition has to be explicitely stopped
    peak_status status = peak_Acquisition_Start(hCam, PEAK_INFINITE);
    checkForSuccess(status, true);
    acquisitionRunning = (status == PEAK_STATUS_SUCCESS);

    return status;
}


int backend_acquisition_stop()
{
    if (hCam == PEAK_INVALID_HANDLE)
    {
        if (g_callback)
        {
            g_callback(
                "Trying to stop image acquisition on camera before it was opened. Open camera first.", -1, g_context);
        }
        return -1;
    }

    if (!peak_Acquisition_IsStarted(hCam))
    {
        if (g_callback)
        {
            g_callback("No acquisition running.", -1, g_context);
        }
        return 0;
    }

    // check if camera is still connected
    peak_status status = backend_camera_accessStatus();
    if (status == PEAK_ACCESS_INVALID)
    {
        // camera has already been removed, skip acquisition stop
        return status;
    }

    // Stop acquisition
    status = peak_Acquisition_Stop(hCam);
    checkForSuccess(status, true);

    return status;
}

bool backend_camera_isMono()
{
    // Get current PixelFormat from the camera which should be the raw PixelFormat after the reset to default
    peak_pixel_format currentPixelFormat = PEAK_PIXEL_FORMAT_INVALID;
    peak_status status = peak_PixelFormat_Get(hCam, &currentPixelFormat);
    if (!checkForSuccess(status, true))
        return status;

    bool isMono = false;
    // Check if it is a mono format
    if ((currentPixelFormat == PEAK_PIXEL_FORMAT_MONO8)
        || (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO10)
        || (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO10P)
        || (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO10G40_IDS)
        || (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO12)
        || (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO12P)
        || (currentPixelFormat == PEAK_PIXEL_FORMAT_MONO12G24_IDS))
    {
        isMono = true;
    }

    return isMono;
}

peak_access_status backend_camera_accessStatus()
{
    peak_camera_id camID = peak_Camera_ID_FromHandle(hCam);
    peak_CameraList_Update(NULL);

    return peak_Camera_GetAccessStatus(camID);
}


int backend_exit()
{
    // Clean up before exit

    peak_status status = PEAK_STATUS_SUCCESS;

    // Stop acquisition, if running
    if (peak_Acquisition_IsStarted(hCam))
    {
        backend_acquisition_stop();
    }

    // Close camera, if open
    if (hCam != PEAK_INVALID_HANDLE)
    {
        // Close Camera
        status = peak_Camera_Close(hCam);
        checkForSuccess(status, true);
    }

    // Exit library
    status = peak_Library_Exit();
    checkForSuccess(status, true);

    return status;
}


bool backend_exposureTime_isReadable()
{
    return PEAK_IS_READABLE(peak_ExposureTime_GetAccessStatus(hCam));
}


bool backend_exposureTime_isWriteable()
{
    return PEAK_IS_WRITEABLE(peak_ExposureTime_GetAccessStatus(hCam));
}


struct range_double backend_exposureTime_range()
{
    peak_status status = PEAK_STATUS_SUCCESS;

    struct range_double range = { .min = .0, .max = .0, .inc = .0 };
    status = peak_ExposureTime_GetRange(hCam, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_exposureTime_get()
{
    peak_status status = PEAK_STATUS_SUCCESS;

    double value = .0;
    status = peak_ExposureTime_Get(hCam, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_exposureTime_set(double value)
{
    peak_status status = PEAK_STATUS_SUCCESS;

    status = peak_ExposureTime_Set(hCam, value);
    checkForSuccess(status, true);

    return status;
}


bool backend_frameRate_isReadable()
{
    return PEAK_IS_READABLE(peak_FrameRate_GetAccessStatus(hCam));
}


bool backend_frameRate_isWriteable()
{
    return PEAK_IS_WRITEABLE(peak_FrameRate_GetAccessStatus(hCam));
}


struct range_double backend_frameRate_range()
{
    peak_status status = PEAK_STATUS_SUCCESS;

    struct range_double range = { .min = .0, .max = .0, .inc = .0 };
    status = peak_FrameRate_GetRange(hCam, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}


double backend_frameRate_get()
{
    double value = .0;
    peak_status status = peak_FrameRate_Get(hCam, &value);
    checkForSuccess(status, true);

    return value;
}


int backend_frameRate_set(double value)
{
    peak_status status = peak_FrameRate_Set(hCam, value);
    checkForSuccess(status, true);

    return status;
}


peak_roi backend_roi_get()
{
    peak_roi roi = { 0, 0, 0, 0 };

    peak_status status = peak_ROI_Get(hCam, &roi);
    checkForSuccess(status, true);

    return roi;
}

peak_pixel_format backend_pixelFormat_get()
{
    peak_pixel_format currentPixelFormat = PEAK_PIXEL_FORMAT_INVALID;

    // Get current PixelFormat...
    if (isColorConversion)
    {
        // ...from the IPL
        peak_status status = peak_IPL_PixelFormat_Get(hCam, &currentPixelFormat);
        checkForSuccess(status, true);
    }
    else
    {
        // ...from the camera
        peak_status status = peak_PixelFormat_Get(hCam, &currentPixelFormat);
        checkForSuccess(status, true);
    }

    return currentPixelFormat;
}

int backend_acquisition_waitForBuffer(int timeout, peak_frame_handle* frame, peak_buffer* buffer)
{
    peak_status status = PEAK_STATUS_SUCCESS;

    if (isColorConversion)
    {
        peak_frame_handle camera_frame = PEAK_INVALID_HANDLE;

        status = peak_Acquisition_WaitForFrame(hCam, timeout, &camera_frame);
        if (status != PEAK_STATUS_SUCCESS)
        {
            if (acquisitionRunning)
            {
                // check if camera is still connected
                if (backend_camera_accessStatus() == PEAK_ACCESS_INVALID)
                {
                    if (g_callback)
                    {
                        g_callback("Camera was removed...", -1, g_context);
                    }
                    return status;
                }
            }
            else if (status == PEAK_STATUS_ABORTED)
            {
                // Ignore aborted exception due to acquisition stop
                return status;
            }
        }

        if (!checkForSuccess(status, true))
            return status;

        // Process the received frame with the IPL
        status = peak_IPL_ProcessFrame(hCam, camera_frame, frame);
        checkForSuccess(status, true);

        status = peak_Frame_Buffer_Get(*frame, buffer);
        checkForSuccess(status, true);

        status = peak_Frame_Release(hCam, camera_frame);
        checkForSuccess(status, true);
    }
    else
    {
        status = peak_Acquisition_WaitForFrame(hCam, timeout, frame);
        if (status != PEAK_STATUS_SUCCESS)
        {
            if (acquisitionRunning)
            {
                // check if camera is still connected
                if (backend_camera_accessStatus() == PEAK_ACCESS_INVALID)
                {
                    if (g_callback)
                    {
                        g_callback("Camera was removed...", -1, g_context);
                    }
                    return status;
                }
            }
            else if (status == PEAK_STATUS_ABORTED)
            {
                // Ignore aborted exception due to acquisition stop
                return status;
            }
        }

        // Process the received frame with the IPL
        status = peak_IPL_ProcessFrameInplace(hCam, *frame);
        checkForSuccess(status, true);

        status = peak_Frame_Buffer_Get(*frame, buffer);
        checkForSuccess(status, true);
    }

    return status;
}

int backend_releaseFrame(peak_frame_handle* frame)
{
    peak_status status = peak_Frame_Release(hCam, *frame);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_brightness_exposureMode_get()
{
    peak_auto_feature_mode exposureMode = PEAK_AUTO_FEATURE_MODE_INVALID;

    peak_status status = peak_IPL_AutoBrightness_Exposure_Mode_Get(hCam, &exposureMode);
    checkForSuccess(status, true);

    switch (exposureMode)
    {
    case PEAK_AUTO_FEATURE_MODE_INVALID:
        return -1;
    case PEAK_AUTO_FEATURE_MODE_OFF:
        return 0;
    case PEAK_AUTO_FEATURE_MODE_ONCE:
        return 1;
    case PEAK_AUTO_FEATURE_MODE_CONTINUOUS:
        return 2;
    default:
        break;
    }

    return -2;
}

int backend_ipl_brightness_exposureMode_set(int value)
{
    peak_auto_feature_mode exposureMode = PEAK_AUTO_FEATURE_MODE_INVALID;

    switch (value)
    {
    case 0:
        exposureMode = PEAK_AUTO_FEATURE_MODE_OFF;
        break;
    case 1:
        exposureMode = PEAK_AUTO_FEATURE_MODE_ONCE;
        break;
    case 2:
        exposureMode = PEAK_AUTO_FEATURE_MODE_CONTINUOUS;
        break;
    default:
        return 1;
    }

    peak_status status = peak_IPL_AutoBrightness_Exposure_Mode_Set(hCam, exposureMode);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_brightness_gainMode_get()
{
    peak_auto_feature_mode gainMode = PEAK_AUTO_FEATURE_MODE_INVALID;

    peak_status status = peak_IPL_AutoBrightness_Gain_Mode_Get(hCam, &gainMode);
    checkForSuccess(status, true);

    switch (gainMode)
    {
    case PEAK_AUTO_FEATURE_MODE_INVALID:
        return -1;
    case PEAK_AUTO_FEATURE_MODE_OFF:
        return 0;
    case PEAK_AUTO_FEATURE_MODE_ONCE:
        return 1;
    case PEAK_AUTO_FEATURE_MODE_CONTINUOUS:
        return 2;
    default:
        break;
    }

    return -2;
}

int backend_ipl_brightness_gainMode_set(int value)
{
    peak_auto_feature_mode gainMode = PEAK_AUTO_FEATURE_MODE_INVALID;

    switch (value)
    {
    case 0:
        gainMode = PEAK_AUTO_FEATURE_MODE_OFF;
        break;
    case 1:
        gainMode = PEAK_AUTO_FEATURE_MODE_ONCE;
        break;
    case 2:
        gainMode = PEAK_AUTO_FEATURE_MODE_CONTINUOUS;
        break;
    default:
        return 1;
    }

    peak_status status = peak_IPL_AutoBrightness_Gain_Mode_Set(hCam, gainMode);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_brightness_roiMode_get()
{
    peak_auto_feature_roi_mode brightnessROIMode = PEAK_AUTO_FEATURE_ROI_MODE_INVALID;

    peak_status status = peak_IPL_AutoBrightness_ROI_Mode_Get(hCam, &brightnessROIMode);
    checkForSuccess(status, true);

    switch (brightnessROIMode)
    {
    case PEAK_AUTO_FEATURE_ROI_MODE_INVALID:
        return -1;
    case PEAK_AUTO_FEATURE_ROI_MODE_FULL_IMAGE:
        return 0;
    case PEAK_AUTO_FEATURE_ROI_MODE_MANUAL:
        return 1;
    default:
        break;
    }

    return -2;
}

int backend_ipl_brightness_roiMode_set(int value)
{
    peak_auto_feature_roi_mode roiMode = PEAK_AUTO_FEATURE_ROI_MODE_INVALID;

    switch (value)
    {
    case 0:
        roiMode = PEAK_AUTO_FEATURE_ROI_MODE_FULL_IMAGE;
        break;
    case 1:
        roiMode = PEAK_AUTO_FEATURE_ROI_MODE_MANUAL;
        break;
    default:
        return 1;
    }

    peak_status status = peak_IPL_AutoBrightness_ROI_Mode_Set(hCam, roiMode);
    checkForSuccess(status, true);

    return status;
}

struct range_int backend_ipl_brightness_roiOffsetX_range()
{
    peak_position min = { 0, 0 };
    peak_position max = { 0, 0 };
    peak_position inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_ROI_Offset_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.x;
    range.max = max.x;
    range.inc = inc.x;

    return range;
}

struct range_int backend_ipl_brightness_roiOffsetY_range()
{
    peak_position min = { 0, 0 };
    peak_position max = { 0, 0 };
    peak_position inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_ROI_Offset_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.y;
    range.max = max.y;
    range.inc = inc.y;

    return range;
}

struct range_int backend_ipl_brightness_roiWidth_range()
{
    peak_size min = { 0, 0 };
    peak_size max = { 0, 0 };
    peak_size inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_ROI_Size_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.width;
    range.max = max.width;
    range.inc = inc.width;

    return range;
}

struct range_int backend_ipl_brightness_roiHeight_range()
{
    peak_size min = { 0, 0 };
    peak_size max = { 0, 0 };
    peak_size inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_ROI_Size_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.height;
    range.max = max.height;
    range.inc = inc.height;

    return range;
}

peak_roi backend_ipl_brightness_roi_get()
{
    peak_roi roi = { 0, 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_ROI_Get(hCam, &roi);
    checkForSuccess(status, true);

    return roi;
}

int backend_ipl_brightness_roi_set(peak_roi roi)
{
    peak_status status = peak_IPL_AutoBrightness_ROI_Set(hCam, roi);
    checkForSuccess(status, true);

    return status;
}

struct range_int backend_ipl_brightness_target_range()
{
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_Target_GetRange(hCam, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

uint32_t backend_ipl_brightness_target_get()
{
    uint32_t value = 0;

    peak_status status = peak_IPL_AutoBrightness_Target_Get(hCam, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_brightness_target_set(uint32_t value)
{
    peak_status status = peak_IPL_AutoBrightness_Target_Set(hCam, value);
    checkForSuccess(status, true);

    return status;
}

struct range_double backend_ipl_brightness_targetPercentile_range()
{
    struct range_double range = { .0, .0, .0 };

    peak_status status = peak_IPL_AutoBrightness_TargetPercentile_GetRange(hCam, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_ipl_brightness_targetPercentile_get()
{
    double value = .0;

    peak_status status = peak_IPL_AutoBrightness_TargetPercentile_Get(hCam, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_brightness_targetPercentile_set(double value)
{
    peak_status status = peak_IPL_AutoBrightness_TargetPercentile_Set(hCam, value);
    checkForSuccess(status, true);

    return status;
}

struct range_int backend_ipl_brightness_targetTolerance_range()
{
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoBrightness_TargetTolerance_GetRange(hCam, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

uint32_t backend_ipl_brightness_targetTolerance_get()
{
    uint32_t value = 0;

    peak_status status = peak_IPL_AutoBrightness_TargetTolerance_Get(hCam, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_brightness_targetTolerance_set(uint32_t value)
{
    peak_status status = peak_IPL_AutoBrightness_TargetTolerance_Set(hCam, value);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_whiteBalance_mode_get()
{
    peak_auto_feature_mode whiteBalanceMode = PEAK_AUTO_FEATURE_MODE_INVALID;

    peak_status status = peak_IPL_AutoWhiteBalance_Mode_Get(hCam, &whiteBalanceMode);
    checkForSuccess(status, true);

    switch (whiteBalanceMode)
    {
    case PEAK_AUTO_FEATURE_MODE_INVALID:
        return -1;
    case PEAK_AUTO_FEATURE_MODE_OFF:
        return 0;
    case PEAK_AUTO_FEATURE_MODE_ONCE:
        return 1;
    case PEAK_AUTO_FEATURE_MODE_CONTINUOUS:
        return 2;
    default:
        break;
    }

    return -2;
}

int backend_ipl_whiteBalance_mode_set(int value)
{
    peak_auto_feature_mode whiteBalanceMode = PEAK_AUTO_FEATURE_MODE_INVALID;

    switch (value)
    {
    case 0:
        whiteBalanceMode = PEAK_AUTO_FEATURE_MODE_OFF;
        break;
    case 1:
        whiteBalanceMode = PEAK_AUTO_FEATURE_MODE_ONCE;
        break;
    case 2:
        whiteBalanceMode = PEAK_AUTO_FEATURE_MODE_CONTINUOUS;
        break;
    default:
        return 1;
    }

    peak_status status = peak_IPL_AutoWhiteBalance_Mode_Set(hCam, whiteBalanceMode);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_whiteBalance_roiMode_get()
{
    peak_auto_feature_roi_mode whiteBalanceROIMode = PEAK_AUTO_FEATURE_ROI_MODE_INVALID;

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Mode_Get(hCam, &whiteBalanceROIMode);
    checkForSuccess(status, true);

    switch (whiteBalanceROIMode)
    {
    case PEAK_AUTO_FEATURE_ROI_MODE_INVALID:
        return -1;
    case PEAK_AUTO_FEATURE_ROI_MODE_FULL_IMAGE:
        return 0;
    case PEAK_AUTO_FEATURE_ROI_MODE_MANUAL:
        return 1;
    default:
        break;
    }

    return -2;
}

int backend_ipl_whiteBalance_roiMode_set(int value)
{
    peak_auto_feature_roi_mode roiMode = PEAK_AUTO_FEATURE_ROI_MODE_INVALID;

    switch (value)
    {
    case 0:
        roiMode = PEAK_AUTO_FEATURE_ROI_MODE_FULL_IMAGE;
        break;
    case 1:
        roiMode = PEAK_AUTO_FEATURE_ROI_MODE_MANUAL;
        break;
    default:
        return 1;
    }

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Mode_Set(hCam, roiMode);
    checkForSuccess(status, true);

    return status;
}

struct range_int backend_ipl_whiteBalance_roiOffsetX_range()
{
    peak_position min = { 0, 0 };
    peak_position max = { 0, 0 };
    peak_position inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.x;
    range.max = max.x;
    range.inc = inc.x;

    return range;
}

struct range_int backend_ipl_whiteBalance_roiOffsetY_range()
{
    peak_position min = { 0, 0 };
    peak_position max = { 0, 0 };
    peak_position inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.y;
    range.max = max.y;
    range.inc = inc.y;

    return range;
}

struct range_int backend_ipl_whiteBalance_roiWidth_range()
{
    peak_size min = { 0, 0 };
    peak_size max = { 0, 0 };
    peak_size inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Size_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.width;
    range.max = max.width;
    range.inc = inc.width;

    return range;
}

struct range_int backend_ipl_whiteBalance_roiHeight_range()
{
    peak_size min = { 0, 0 };
    peak_size max = { 0, 0 };
    peak_size inc = { 0, 0 };
    struct range_int range = { 0, 0, 0 };

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Size_GetRange(hCam, &min, &max, &inc);
    if (!checkForSuccess(status, true))
    {
        return range;
    }

    range.min = min.height;
    range.max = max.height;
    range.inc = inc.height;

    return range;
}

peak_roi backend_ipl_whiteBalance_roi_get()
{
    peak_roi roi = { 0, 0, 0, 0 };

    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Get(hCam, &roi);
    checkForSuccess(status, true);

    return roi;
}

int backend_ipl_whiteBalance_roi_set(peak_roi roi)
{
    peak_status status = peak_IPL_AutoWhiteBalance_ROI_Set(hCam, roi);
    checkForSuccess(status, true);

    return status;
}

struct range_double backend_ipl_gainMaster_range()
{
    struct range_double range = { .min = .0, .max = .0, .inc = .0 };

    peak_status status = peak_IPL_Gain_GetRange(
        hCam, PEAK_GAIN_CHANNEL_MASTER, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_ipl_gainMaster_get()
{
    double value = .0;
    peak_status status = peak_IPL_Gain_Get(hCam, PEAK_GAIN_CHANNEL_MASTER, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_gainMaster_set(double value)
{
    peak_status status = peak_IPL_Gain_Set(hCam, PEAK_GAIN_CHANNEL_MASTER, value);
    checkForSuccess(status, true);

    return status;
}


struct range_double backend_ipl_gainRed_range()
{
    struct range_double range = { .min = .0, .max = .0, .inc = .0 };

    peak_status status = peak_IPL_Gain_GetRange(
        hCam, PEAK_GAIN_CHANNEL_RED, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_ipl_gainRed_get()
{
    double value = .0;
    peak_status status = peak_IPL_Gain_Get(hCam, PEAK_GAIN_CHANNEL_RED, & value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_gainRed_set(double value)
{
    peak_status status = peak_IPL_Gain_Set(hCam, PEAK_GAIN_CHANNEL_RED, value);
    checkForSuccess(status, true);

    return status;
}

struct range_double backend_ipl_gainGreen_range()
{
    struct range_double range = { .min = .0, .max = .0, .inc = .0 };

    peak_status status = peak_IPL_Gain_GetRange(
        hCam, PEAK_GAIN_CHANNEL_RED, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_ipl_gainGreen_get()
{
    double value = .0;
    peak_status status = peak_IPL_Gain_Get(hCam, PEAK_GAIN_CHANNEL_GREEN, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_gainGreen_set(double value)
{
    peak_status status = peak_IPL_Gain_Set(hCam, PEAK_GAIN_CHANNEL_GREEN, value);
    checkForSuccess(status, true);

    return status;
}

struct range_double backend_ipl_gainBlue_range()
{
    struct range_double range = { .min = .0, .max = .0, .inc = .0 };

    peak_status status = peak_IPL_Gain_GetRange(
        hCam, PEAK_GAIN_CHANNEL_BLUE, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_ipl_gainBlue_get()
{
    double value = .0;
    peak_status status = peak_IPL_Gain_Get(hCam, PEAK_GAIN_CHANNEL_BLUE, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_gainBlue_set(double value)
{
    peak_status status = peak_IPL_Gain_Set(hCam, PEAK_GAIN_CHANNEL_BLUE, value);
    checkForSuccess(status, true);

    return status;
}

struct range_double backend_ipl_gamma_range()
{
    struct range_double range = { .min = .0, .max = .0, .inc = .0 };

    peak_status status = peak_IPL_Gamma_GetRange(hCam, &range.min, &range.max, &range.inc);
    checkForSuccess(status, true);

    return range;
}

double backend_ipl_gamma_get()
{
    double value = .0;
    peak_status status = peak_IPL_Gamma_Get(hCam, &value);
    checkForSuccess(status, true);

    return value;
}

int backend_ipl_gamma_set(double value)
{
    peak_status status = peak_IPL_Gamma_Set(hCam, value);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_colorCorrection_enable(bool enable)
{
    peak_status status = peak_IPL_ColorCorrection_Enable(hCam, enable);
    checkForSuccess(status, true);

    return status;
}

bool backend_ipl_colorCorrection_isEnabled()
{
    return peak_IPL_ColorCorrection_IsEnabled(hCam);
}


peak_matrix backend_ipl_colorCorrectionMatrix_get()
{
    peak_matrix ccm = { .0, .0, .0, .0, .0, .0, .0, .0, .0 };

    peak_status status = peak_IPL_ColorCorrection_Matrix_Get(hCam, &ccm);
    checkForSuccess(status, true);

    return ccm;
}

int backend_ipl_colorCorrectionMatrix_set(peak_matrix ccm)
{
    peak_status status = peak_IPL_ColorCorrection_Matrix_Set(hCam, ccm);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_colorCorrectionMatrix_setDefault()
{
    // Get default matrix from camera

    // Check if current mode is already 'HQ'
    peak_color_correction_mode currentMode = PEAK_COLOR_CORRECTION_MODE_INVALID;
    peak_status status = peak_ColorCorrection_Mode_Get(hCam, &currentMode);
    if (!checkForSuccess(status, true))
        return status;

    // If not, try to set the mode
    if (currentMode != PEAK_COLOR_CORRECTION_MODE_HQ)
    {
        // First step: get the number of list items
        size_t count = 0;
        status = peak_ColorCorrection_Mode_GetList(hCam, NULL, &count);
        if (!checkForSuccess(status, true))
            return status;

        // Second step: get the list
        peak_color_correction_mode* modes = (peak_color_correction_mode*)calloc(
            count, sizeof(peak_color_correction_mode));
        status = peak_ColorCorrection_Mode_GetList(hCam, modes, &count);
        if (!checkForSuccess(status, true))
            return status;

        // Find the mode 'HQ'
        bool hqSupported = false;
        for (size_t i = 0; i < count; i++)
        {
            if (modes[i] == PEAK_COLOR_CORRECTION_MODE_HQ)
            {
                // Preferred pixel format found, break
                hqSupported = true;
                break;
            }
        }
        free(modes);

        if (!hqSupported)
            return -1;

        // Set camera to 'HQ' mode
        status = peak_ColorCorrection_Mode_Set(hCam, PEAK_COLOR_CORRECTION_MODE_HQ);
        if (!checkForSuccess(status, true))
            return status;
    }

    // Get the color correction matrix for 'HQ' as default matrix
    peak_matrix ccm = { .0, .0, .0, .0, .0, .0, .0, .0, .0 };
    status = peak_ColorCorrection_Matrix_Get(hCam, &ccm);
    if (!checkForSuccess(status, true))
        return status;

    // Set the matrix to the IPL CCM
    status = peak_IPL_ColorCorrection_Matrix_Set(hCam, ccm);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_colorCorrectionMatrix_setIdentity()
{
    // Define an identity matrix
    peak_matrix ccm = { 1.0, .0, .0, .0, 1.0, .0, .0, .0, 1.0 };

    // Set the matrix to the IPL CCM
    peak_status status = peak_IPL_ColorCorrection_Matrix_Set(hCam, ccm);
    checkForSuccess(status, true);

    return status;
}


bool backend_ipl_mirrorLeftRight_isEnabled()
{
    return peak_IPL_Mirror_LeftRight_IsEnabled(hCam);
}

int backend_ipl_mirrorLeftRight_enable(bool enable)
{
    peak_status status = peak_IPL_Mirror_LeftRight_Enable(hCam, enable);
    checkForSuccess(status, true);

    return status;
}


bool backend_ipl_mirrorUpDown_isEnabled()
{
    return peak_IPL_Mirror_UpDown_IsEnabled(hCam);
}

int backend_ipl_mirrorUpDown_enable(bool enable)
{
    peak_status status = peak_IPL_Mirror_UpDown_Enable(hCam, enable);
    checkForSuccess(status, true);

    return status;
}


bool backend_ipl_hotpixelCorrection_isEnabled()
{
    return peak_IPL_HotpixelCorrection_IsEnabled(hCam);
}

int backend_ipl_hotpixelCorrection_enable(bool enable)
{
    peak_status status = peak_IPL_HotpixelCorrection_Enable(hCam, enable);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_hotpixelCorrection_resetList()
{
    peak_status status = peak_IPL_HotpixelCorrection_ResetList(hCam);
    checkForSuccess(status, true);

    return status;
}

int backend_ipl_hotpixelCorrection_sensitivity_get()
{
    peak_hotpixel_correction_sensitivity sensitivity = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_INVALID;
    peak_status status = peak_IPL_HotpixelCorrection_Sensitivity_Get(hCam, &sensitivity);
    if (!checkForSuccess(status, true))
        return status;

    switch (sensitivity)
    {
    case PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_1:
        return 1;
    case PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_2:
        return 2;
    case PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_3:
        return 3;
    case PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_4:
        return 4;
    case PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_5:
        return 5;
    default:
        return -1;
    }
}


int backend_ipl_hotpixelCorrection_sensitivity_set(int sensitivity)
{
    peak_hotpixel_correction_sensitivity sens = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_INVALID;

    switch (sensitivity)
    {
    case 1:
        sens = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_1;
        break;
    case 2:
        sens = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_2;
        break;
    case 3:
        sens = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_3;
        break;
    case 4:
        sens = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_4;
        break;
    case 5:
        sens = PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_5;
        break;
    default:
        break;
    }

    peak_status status = peak_IPL_HotpixelCorrection_Sensitivity_Set(hCam, sens);
    checkForSuccess(status, true);

    return status;
}


size_t backend_ipl_hotpixelCorrection_list_getCount()
{
    size_t count = 0;
    peak_status status = peak_IPL_HotpixelCorrection_GetList(hCam, NULL, &count);
    checkForSuccess(status, true);

    return count;
}


void backend_errorCallback_connect(void* receiver, errorCallback slot)
{
    g_context = receiver;
    g_callback = slot;
}


// Returns true, if function was successful.
// Returns false, if function returned with an error.
// If continueExecution == false, the backend is exited.
static bool checkForSuccess(peak_status status, bool continueExecution)
{
    if (PEAK_ERROR(status))
    {
        size_t lastErrorMessageSize = 0;

        // Get size of error message
        peak_Library_GetLastError(NULL, NULL, &lastErrorMessageSize);

        // Allocate and zero-initialize the char array for the error message
        char* errorMessage = (char*)calloc((lastErrorMessageSize) / sizeof(char), sizeof(char));

        // Get the error message
        peak_Library_GetLastError(&status, errorMessage, &lastErrorMessageSize);

        // Connect error handling mechanism, in this case a callback that can be used from C++ class
        if (g_callback)
        {
            g_callback(errorMessage, status, g_context);
        }
        free(errorMessage);

        if (!continueExecution)
        {
            backend_exit();
        }

        return false;
    }
    return true;
}

