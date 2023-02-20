/*!
 * \file    acquisitionworker.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
 *
 * \brief   The AcquisitionWorker class is used in a worker thread to capture
 *          images from the device continuously and do an image conversion into
 *          a desired pixel format.
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

#include "acquisitionworker.h"

#include "backend.h"

#include <ids_peak_comfort_c.h>

#include <QDebug>
#include <QThread>
#include <QPixelFormat>

#include <cmath>
#include <cstring>


AcquisitionWorker::AcquisitionWorker(QObject * parent)
    : QObject(parent)
{
    m_running = false;
    m_frameCounter = 0;
    m_errorCounter = 0;
}

void AcquisitionWorker::Start()
{
    peak_roi roi = backend_roi_get();
    if (roi.size.width == 0 || roi.size.height == 0)
    {
        // Zero-size ROI
        emit error(QString("Could not read ROI of camera (zero size)."));
        return;
    }

    peak_pixel_format pixelFormat = backend_pixelFormat_get();
    if (pixelFormat == PEAK_PIXEL_FORMAT_INVALID)
    {
        // Unhandled PixelFormat
        emit error(QString("Could not read PixelFormat of camera (invalid)."));
        return;
    }
    


    m_running = true;

    emit started();

    while (m_running)
    {
        peak_buffer buffer;
        peak_frame_handle frame = PEAK_INVALID_HANDLE;
        int stat = backend_acquisition_waitForBuffer(5000, &frame, &buffer);

        if (stat == PEAK_STATUS_ABORTED)
        {
            if (!m_running)
            {
                // expected abort due to acquisition stop
                emit stopped();
                return;
            }
            else if (backend_camera_accessStatus() == PEAK_ACCESS_INVALID)
            {
                // check if camera is still connected
                m_running = false;
                return;
            }
        }

        if (PEAK_STATUS_SUCCESS == stat)
        {
            QImage::Format imageFormat = QImage::Format_Invalid;

            // Note: Choosing the right format for your image display depends on the type of camera,
            // on the compile system and on the graphical library for displaying the images.

            bool doSwapRgb = false;

            // Use QImage::Format_Grayscale8 for 8 bit Bayer or 8 bit mono images
            if ((PEAK_PIXEL_FORMAT_BAYER_RG8 == pixelFormat) || (PEAK_PIXEL_FORMAT_BAYER_GR8 == pixelFormat)
                || (PEAK_PIXEL_FORMAT_BAYER_BG8 == pixelFormat) || (PEAK_PIXEL_FORMAT_BAYER_GB8 == pixelFormat)
                || (PEAK_PIXEL_FORMAT_MONO8 == pixelFormat))
            {
                imageFormat = QImage::Format_Grayscale8;
            }
            // Use QImage::Format_RGB888, if the camera provides 24 bit RGB images
            else if (PEAK_PIXEL_FORMAT_RGB8 == pixelFormat) 
            {
                imageFormat = QImage::Format_RGB888;
            }
            else if (PEAK_PIXEL_FORMAT_BGR8 == pixelFormat)
            {
                imageFormat = QImage::Format_RGB888;
                doSwapRgb = true;
            }
            else if (PEAK_PIXEL_FORMAT_BGRA8 == pixelFormat)
            {
                imageFormat = QImage::Format_RGB32;
            }
            else if (PEAK_PIXEL_FORMAT_RGBA8 == pixelFormat)
            {
                imageFormat = QImage::Format_RGB32;
                doSwapRgb = true;
            }
            else
            {
                // Unhandled PixelFormat
                emit error(QString("Unknown PixelFormat (Format ID ") + QString::number(PEAK_PIXEL_FORMAT_RGB8) + ")");
                backend_releaseFrame(&frame);
                return;
            }

            if (QImage::Format_Invalid != imageFormat)
            {
                QImage qImage((unsigned char*)buffer.memoryAddress, roi.size.width, roi.size.height, imageFormat);
                qImage.size();
                if (doSwapRgb)
                {
                    qImage = qImage.rgbSwapped();
                }

                emit imageReceived(qImage);

                m_frameCounter++;
            }
            else
            {
                m_errorCounter++;
            }

            stat = backend_releaseFrame(&frame);
        }
        else
        {
            m_errorCounter++;

            QThread::msleep(100);
        }

        emit counterUpdated(m_frameCounter, m_errorCounter);
    }

    emit stopped();
}

void AcquisitionWorker::Stop()
{
    m_running = false;
}
