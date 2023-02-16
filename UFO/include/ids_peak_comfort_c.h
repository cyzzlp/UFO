/*!
 * \file ids_peak_comfort_c.h
 * 
 * \brief Interface definition file for IDS peak comfortC
 * 
 * Copyright (C) 2022, IDS Imaging Development Systems GmbH.
 */

#ifndef PEAK_COMFORT_C_H
#define PEAK_COMFORT_C_H

/* Function declaration modifiers */
#if defined(_WIN32)
#    ifndef PEAK_NO_DECLSPEC_STATEMENTS
#        ifdef paiconstant_EXPORTING
#            define PEAK_EXPORT __declspec(dllexport)
#        else
#            define PEAK_EXPORT __declspec(dllimport)
#        endif
#    else
#        define PEAK_EXPORT
#    endif
#    if defined(_M_IX86) || defined(__i386__)
#        define PEAK_CALLCONV __cdecl
#    else
#        define PEAK_CALLCONV
#    endif
#elif defined(__linux__)
#    define PEAK_EXPORT
#    if defined(__i386__)
#        define PEAK_CALLCONV __attribute__((cdecl))
#    else
#        define PEAK_CALLCONV
#    endif
#else
#    error Platform is not supported yet!
#endif

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>

extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/* helper entities */
struct peak_camera;
struct peak_frame;
struct peak_video;

#define PEAK_VERSION_CODE(major,minor,subminor,patch) (((major) << 24) + ((minor) << 16) + ((subminor) << 8) + (patch))
#define PEAK_API_STATUS PEAK_EXPORT peak_status PEAK_CALLCONV
#define PEAK_API_ACCESS_STATUS PEAK_EXPORT peak_access_status PEAK_CALLCONV
#define PEAK_API_BOOL PEAK_EXPORT peak_bool PEAK_CALLCONV
#define PEAK_API_CAMERA_ID PEAK_EXPORT peak_camera_id PEAK_CALLCONV

/*! \defgroup generics Generic functions, types, and values
 *
 * This basic functions, types, and values are used throughout the whole library interface.
 */

/*! \defgroup numeric Numeric types and values
 *
 * \ingroup generics
 *
 * Definitions on numeric types and values.
 */

/*! \defgroup status Status types and values
 *
 * \ingroup generics
 *
 * Definitions on status types and values.
 */

/*! \defgroup library Library
 *
 * Library level functions and types.
 */

/*! \defgroup version Library version
 *
 * \ingroup library
 *
 * Definitions on library version information.
 */

/*! \defgroup camera Camera
 *
 * Camera related functions and types.
 */

/*! \defgroup camera_connection Camera connection
 *
 * Camera connection related functions and types.
 */

/*! \defgroup ethernet_config Ethernet configuration
 *
 * \ingroup camera_connection
 *
 * Ethernet configuration related functions and types.
 */

/*! \defgroup acquisition_and_buffer_preparation Acquisition and buffer preparation
 *
 * Acquisition and buffer preparation related functions and types.
 * 
 * For a description of the libraries buffer preparation concept see \ref concept_buffer_preparation.
 */

/*! \defgroup manual_buffer_preparation Manual buffer preparation
 *
 * \ingroup acquisition_and_buffer_preparation
 *
 * Manual buffer preparation related functions and types.
 *
 * For a description of the libraries manual buffer preparation concept see \ref concept_manual_buffer_preparation.
 */

/*! \defgroup frame Frame
 *
 * Frame related functions and types.
 */

/*! \defgroup camera_control Camera control
 *
 * Camera control related functions and types.
 */

/*! \defgroup image_color_and_brightness Image color and brightness
 *
 * Image color and brightness related functions and types.
 */

/*! \defgroup image_size_and_transformation Image size and transformation
 *
 * Image size and transformation related functions and types.
 */

/*! \defgroup camera_memory Camera memory
 *
 * Camera memory related functions and types.
 */

/*! \defgroup camera_settings Camera settings
 *
 * \ingroup camera_control
 *
 * Camera settings related functions and types.
 */

/*! \defgroup frame_info Frame info
 *
 * \ingroup frame
 *
 * Frame info related functions and types.
 */

/*! \defgroup framerate Frame rate
 *
 * \ingroup camera_control
 *
 * Frame rate related functions and types.
 */

/*! \defgroup exposuretime Exposure time
 *
 * \ingroup camera_control
 *
 * Exposure time related functions and types.
 */

/*! \defgroup pixelclock Pixel clock
 *
 * \ingroup camera_control
 *
 * Pixel clock related functions and types.
 */

/*! \defgroup io_channel IO channel
 *
 * \ingroup camera_control
 *
 * IO channel related functions and types.
 */

/*! \defgroup trigger Trigger
 *
 * \ingroup camera_control
 *
 * Trigger related functions and types.
 */

/*! \defgroup trigger_edge Trigger edge property
 *
 * \ingroup trigger
 *
 * Trigger edge property related functions.
 */

/*! \defgroup trigger_delay Trigger delay property
 *
 * \ingroup trigger
 *
 * Trigger delay property related functions.
 */

/*! \defgroup trigger_divider Trigger divider property
 *
 * \ingroup trigger
 *
 * Trigger divider property related functions.
 */

/*! \defgroup trigger_burst Trigger burst property
 *
 * \ingroup trigger
 *
 * Trigger burst property related functions.
 */

/*! \defgroup flash Flash
 *
 * \ingroup camera_control
 *
 * Flash related functions and types.
 */

/*! \defgroup flash_start_delay Flash start delay property
 *
 * \ingroup flash
 *
 * Flash start delay property related functions.
 */

/*! \defgroup flash_end_delay Flash end delay property
 *
 * \ingroup flash
 *
 * Flash end delay property related functions.
 */

/*! \defgroup flash_duration Flash duration property
 *
 * \ingroup flash
 *
 * Flash end duration property related functions.
 */

/*! \defgroup pixelformat Pixel format
 *
 * \ingroup image_color_and_brightness
 *
 * Pixel format related functions and types.
 *
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_pixelformat.
 */

/*! \defgroup gain Gain
 *
 * \ingroup image_color_and_brightness
 *
 * Gain related functions and types.
 * 
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_gain.
 */

/*! \defgroup gamma Gamma
 *
 * \ingroup image_color_and_brightness
 *
 * Gamma related functions and types.
 *
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_gamma.
 */

/*! \defgroup color_correction Color correction
 *
 * \ingroup image_color_and_brightness
 *
 * Color correction related functions and types.
 *
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_color_correction.
 */

 /*! \defgroup auto_brightness Auto brightness control
 *
 * \ingroup image_color_and_brightness
 *
 * Auto brightness control related functions and types.
 *
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_auto_brightness.
 */

/*! \defgroup auto_white_balance Auto white balance control
 *
 * \ingroup image_color_and_brightness
 *
 * Auto white balance control related functions and types.
 *
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_auto_white_balance.
 */

/*! \defgroup roi ROI (Region Of Interest)
 *
 * \ingroup image_size_and_transformation
 *
 * ROI (Region Of Interest) related functions and types.
 */

/*! \defgroup binning Binning
 *
 * \ingroup image_size_and_transformation
 *
 * Pixel binning related functions and types.
 */

/*! \defgroup decimation Decimation
 *
 * \ingroup image_size_and_transformation
 *
 * Pixel decimation related functions and types. \n
 * Pixel decimation is also referred to as pixel skipping.
 */

/*! \defgroup mirror Mirror
 *
 * \ingroup image_size_and_transformation
 *
 * Image mirroring related functions and types.
 *
 * This feature is applied in the camera. \n
 * There is also a host implementation. See \ref host_features / \ref host_mirror.
 */

/*! \defgroup gfa Generic Feature Access (GFA)
 *
 * Generic feature access related functions and types.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */

/*! \defgroup gfa_float GFA Float
 *
 * \ingroup gfa
 *
 * Generic float feature access related functions and types.
 */

/*! \defgroup gfa_integer GFA Integer
 *
 * \ingroup gfa
 *
 * Generic integer feature access related functions and types.
 */

/*! \defgroup gfa_boolean GFA Boolean
 *
 * \ingroup gfa
 *
 * Generic boolean feature access related functions and types.
 */

/*! \defgroup gfa_string GFA String
 *
 * \ingroup gfa
 *
 * Generic string feature access related functions and types.
 */

/*! \defgroup gfa_command GFA Command
 *
 * \ingroup gfa
 *
 * Generic command feature access related functions and types.
 */

/*! \defgroup gfa_enumeration GFA Enumeration
 *
 * \ingroup gfa
 *
 * Generic enumeration feature access related functions and types.
 */

/*! \defgroup gfa_register GFA Register
 *
 * \ingroup gfa
 *
 * Generic register access related functions and types.
 */

/*! \defgroup gfa_data GFA Data
 *
 * \ingroup gfa
 *
 * Generic data access related functions and types.
 */

/*! \defgroup host_features Host Features
 *
 * Image processing functions, executed on the host system.
 */

/*! \defgroup host_pixelformat Pixel format
 *
 * \ingroup host_features
 *
 * Pixel format related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref pixelformat.
 */

/*! \defgroup host_gain Gain
 *
 * \ingroup host_features
 *
 * Gain related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref gain.
 */

/*! \defgroup host_gamma Gamma
 *
 * \ingroup host_features
 *
 * Gamma related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref gamma.
 */

/*! \defgroup host_color_correction Color correction
 *
 * \ingroup host_features
 *
 * Color correction related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref color_correction.
 */

 /*! \defgroup host_auto_brightness Auto brightness control
 *
 * \ingroup host_features
 *
 * Auto brightness control related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref auto_brightness.
 */

/*! \defgroup host_auto_white_balance Auto white balance control
 *
 * \ingroup host_features
 *
 * Auto white balance control related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref auto_white_balance.
 */

/*! \defgroup host_hotpixel Hotpixel Correction
 *
 * \ingroup host_features
 *
 * Hotpixel correction related functions and types.
 */

/*! \defgroup host_mirror Mirror
 *
 * \ingroup host_features
 *
 * Image mirroring related functions and types.
 *
 * This feature is applied in the host. \n
 * There is also a camera implementation. See \ref mirror.
 */

 /*! \defgroup video Video
 *
 * \ingroup host_features
 *
 * Functions for saving images as video file.
 */

/*!
 * \ingroup numeric
 * \brief peak Invalid handle value
 *
 * Use this value for the initialization of variables of handle type,
 * i.e. #peak_camera_handle, #peak_frame_handle.
 */
#define PEAK_INVALID_HANDLE NULL

/*!
 * \ingroup numeric
 * \brief peak Infinite value
 *
 * This value can be used to specify infinity in several function calls.
 * The value can be used for timeout parameters as well as for count parameters, where documented.
 *
 * For example this value can be used for the timeout_ms parameter in #peak_Acquisition_WaitForFrame
 * to specify an infinite wait timeout.
 * It also can be used for the numberOfFrames parameter in #peak_Acquisition_Start
 * to specify an infinite acquisition_and_buffer_preparation.
 */
#define PEAK_INFINITE 0xffffffff

/*!
 * \ingroup numeric
 * \brief peak Boolean type
 * 
 * This type is for boolean decisions, i.e. 'true' and 'false' or 'yes' and 'no'.
 * Possible values for this type are #PEAK_TRUE and #PEAK_FALSE.
 */
typedef uint8_t peak_bool;

/*!
 * \ingroup numeric
 * \brief peak Boolean value for 'true' or 'yes'
 *
 * This value reflects a positive decision, i.e. 'true' or 'yes'.
 * It is used for variables of type #peak_bool.
 */
#define PEAK_TRUE 1

/*!
 * \ingroup numeric
 * \brief peak Boolean value for 'false' or 'no'
 *
 * This value reflects a negative decision, i.e. 'false' or 'no'.
 * It is used for variables of type #peak_bool.
 */
#define PEAK_FALSE 0

#pragma pack(push, 1)
/*!
 * \ingroup numeric
 * \brief peak Buffer descriptor
 *
 * The buffer descriptor describes a memory buffer.
 */
typedef struct
{
    /*! \brief The memory address at which the buffer starts */
    uint8_t* memoryAddress;

    /*! \brief The size of allocated buffer memory */
    size_t memorySize;

    /*! \brief User context pointer
     *
     * The user context allows to bind a pointer to a data object to the buffer.
     * NULL if not used.
     * 
     * \note In \ref concept_automatic_buffer_preparation mode this value is always NULL.
     */
    void* userContext;

} peak_buffer;
#pragma pack(pop)

#pragma pack(push, 1)
/*!
 * \ingroup numeric
 * \brief peak Size (2D)
 *
 * Defines a size in a 2-dimensional coordinate space.
 * 
 * This type is used in several library functions and types.
 */
typedef struct
{
    /*! \brief Width */
    uint32_t width;

    /*! \brief Height */
    uint32_t height;

} peak_size;
#pragma pack(pop)

#pragma pack(push, 1)
/*!
 * \ingroup numeric
 * \brief peak Position (2D)
 *
 * Defines a position in a 2-dimensional coordinate space.
 *
 * This type is used in several library functions and types.
 */
typedef struct
{
    /*! \brief X-Position */
    uint32_t x;

    /*! \brief Y-Position */
    uint32_t y;

} peak_position;
#pragma pack(pop)

#pragma pack(push, 1)
/*!
 * \ingroup numeric
 * \brief The peak ROI (2D)
 */
typedef struct
{
    /*! \brief ROI offset */
    peak_position offset;

    /*! \brief ROI size */
    peak_size size;

} peak_roi;
#pragma pack(pop)

#pragma pack(push, 1)
/*!
 * \ingroup numeric
 * \brief The peak 3x3 Matrix
 *
 * The matrix is a rectangular array or table of floating point numbers with 3 rows and 3 columns. \n
 * A matrix is used for several calculations.
 * The library uses it for the color correction feature. See \ref color_correction.
 *
 * The following table shows the indices of the elements in the matrix.
 * |    |    |    |
 * |----|----|----|
 * | 00 | 01 | 02 |
 * | 10 | 11 | 12 |
 * | 20 | 21 | 22 |
 */
typedef union
{
    /*! \brief The matrix elements in struct format. */
    struct
    {
        /*! \brief Element 00 */
        double element_00;

        /*! \brief Element 01 */
        double element_01;

        /*! \brief Element 02 */
        double element_02;

        /*! \brief Element 10 */
        double element_10;

        /*! \brief Element 11 */
        double element_11;

        /*! \brief Element 12 */
        double element_12;

        /*! \brief Element 20 */
        double element_20;

        /*! \brief Element 21 */
        double element_21;

        /*! \brief Element 22 */
        double element_22;

    } elements;

    /*! \brief The matrix elements in 2-dimensional array format. */
    double elementArray[3][3];

} peak_matrix;
#pragma pack(pop)

/*!
 * \ingroup numeric
 * \brief The peak Identity matrix preset
 *
 * Use this preset to set a peak_matrix for the identity.
 */
#define PEAK_IDENTITY_MATRIX    { 1.0, 0.0, 0.0, \
                                  0.0, 1.0, 0.0, \
                                  0.0, 0.0, 1.0 }

/*!
 * \ingroup status
 * \brief peak Status codes
 *
 * The majority of the peak functions return a status code.
 */
typedef enum
{
    /*! \brief Success */
    PEAK_STATUS_SUCCESS                     = 0,

    /*! \brief Unspecified warning */
    PEAK_STATUS_WARNING                     = 0x4000,

    /*! \brief The set value was auto-adjusted
     *
     * This status code indicates that a value which was set to a feature was automatically adjusted by
     * the implementation or the camera.
     */
    PEAK_STATUS_VALUE_ADJUSTED              = 0x4001,

    /*! \brief Unspecified error
     *
     * This status code is typically returned on an unexpected error in the library implementation
     * and should not show up.
     */
    PEAK_STATUS_ERROR                       = 0x8000,

    /*! \brief The library is not initialized
     *
     * Call #peak_Library_Init.
     */
    PEAK_STATUS_NOT_INITIALIZED             = 0x8001,

    /*! \brief The function is not implemented */
    PEAK_STATUS_NOT_IMPLEMENTED             = 0x8002,

    /*! \brief The access to the requested feature was denied due to the current system status */
    PEAK_STATUS_ACCESS_DENIED               = 0x8003,

    /*! \brief There is no such camera */
    PEAK_STATUS_CAMERA_NOT_FOUND            = 0x8004,

    /*! \brief The specified camera is not available */
    PEAK_STATUS_CAMERA_NOT_AVAILABLE        = 0x8005,

    /*! \brief The handle is invalid */
    PEAK_STATUS_INVALID_HANDLE              = 0x8006,

    /*! \brief One or more parameters are invalid */
    PEAK_STATUS_INVALID_PARAMETER           = 0x8007,

    /*! \brief The value or configuration is out of the valid range */
    PEAK_STATUS_OUT_OF_RANGE                = 0x8008,

    /*! \brief The buffer is too small to take the complete data */
    PEAK_STATUS_BUFFER_TOO_SMALL            = 0x8009,

    /*! \brief The current configuration of an addressed module does not allow the requested operation to be executed */
    PEAK_STATUS_INVALID_CONFIGURATION       = 0x800A,

    /*! \brief A timeout occurred */
    PEAK_STATUS_TIMEOUT                     = 0x800B,

    /*! \brief The operation was aborted */
    PEAK_STATUS_ABORTED                     = 0x800C,

    /*! \brief The specified or requested data is not present */
    PEAK_STATUS_NO_DATA                     = 0x800D,

    /*! \brief The peak installation is corrupted */
    PEAK_STATUS_INVALID_PEAK_INSTALLATION   = 0x800E,

    /*! \brief Device or resource is busy */
    PEAK_STATUS_BUSY                       = 0x800F

} peak_status;

/*!
 * \ingroup status
 * \brief Check for the status code to indicate success
 *
 * Evaluates the specified #peak_status code to indicate success.
 *
 * \param[in] status The status code to evaluate.
 *
 * \return #PEAK_TRUE   \p status indicates success.
 * \return #PEAK_FALSE  \p status does not indicate success.
 */
#define PEAK_SUCCESS(status) ((((status) & 0xf000) == 0x0000) ? PEAK_TRUE : PEAK_FALSE)

/*!
 * \ingroup status
 * \brief Check for the status code to indicate a warning
 *
 * Evaluates the specified #peak_status code to indicate a warning.
 *
 * \param[in] status The status code to evaluate.
 *
 * \return #PEAK_TRUE   \p status indicates a warning.
 * \return #PEAK_FALSE  \p status does not indicate a warning.
 */
#define PEAK_WARNING(status) ((((status) & 0xf000) == 0x4000) ? PEAK_TRUE : PEAK_FALSE)

/*!
 * \ingroup status
 * \brief Check for the status code to indicate an error
 *
 * Evaluates the specified #peak_status code to indicate an error.
 *
 * \param[in] status The status code to evaluate.
 *
 * \return #PEAK_TRUE   \p status indicates an error.
 * \return #PEAK_FALSE  \p status does not indicate an error.
 */
#define PEAK_ERROR(status) ((((status) & 0xf000) == 0x8000) ? PEAK_TRUE : PEAK_FALSE)

/*!
 * \ingroup status
 * \brief peak Access status codes
 *
 * The access status can be queried for several features and for a camera.
 *
 * \see \ref term_access_status
 */
typedef enum
{
    /*! \brief Invalid access status code
     *
     * Use this value for the initialization of variables of type peak_access_status.
     *
     * \note This access status code is also used by the library to indicate a failed access status query.
     *       See \ref principle_access_status_query on this.
     */
    PEAK_ACCESS_INVALID         = 0,

    /*! \brief Not supported
     *
     * The feature is not supported.
     *
     * Not all cameras support all features.
     */
    PEAK_ACCESS_NOT_SUPPORTED   = 0x0001,

    /*! \brief No access
     *
     * The feature or the camera is currently not accessible at all.
     */
    PEAK_ACCESS_NONE            = 0x0101,

    /*! \brief No access
     *
     * The feature or the camera is currently not accessible due to the status of the GFA write access. \n
     * The \ref term_convenience_interface functions are not accessible if the GFA write lock is enabled.
     */
    PEAK_ACCESS_GFA_LOCK        = 0x0201,

    /*! \brief Read only access
     *
     * The feature is currently available for read only access.
     */
    PEAK_ACCESS_READONLY        = 0x1101,

    /*! \brief Write only access
     *
     * The feature is currently available for write only access.
     */
    PEAK_ACCESS_WRITEONLY       = 0x2101,

    /*! \brief Read write access
     *
     * The feature or the camera is currently available for read and for write access.
     */
    PEAK_ACCESS_READWRITE       = 0x3101

} peak_access_status;

/*!
 * \ingroup status
 * \brief Check for the access status code to indicate write access to be possible
 *
 * Evaluates the specified #peak_access_status code to indicate write access to be possible.
 *
 * \param[in] accessStatus The access status code to evaluate.
 *
 * \return #PEAK_TRUE   \p accessStatus indicates write access to be possible.
 * \return #PEAK_FALSE  \p accessStatus does not indicate write access to be possible. Consider that the access status
 *                      may indicate a failed access status query.
 *
 * \see \ref principle_access_status_query, especially \ref principle_access_status_query_simple
 */
#define PEAK_IS_WRITEABLE(accessStatus) ((((accessStatus) & 0x2000) == 0x2000) ? PEAK_TRUE : PEAK_FALSE)

/*!
 * \ingroup status
 * \brief Check for the access status code to indicate read access to be possible
 *
 * Evaluates the specified #peak_access_status code to indicate read access to be possible.
 * 
 * \param[in] accessStatus The access status code to evaluate.
 * 
 * \return #PEAK_TRUE   \p accessStatus indicates read access to be possible.
 * \return #PEAK_FALSE  \p accessStatus does not indicate read access to be possible. Consider that the access status
 *                      may indicate a failed access status query.
 *
 * \see \ref principle_access_status_query, especially \ref principle_access_status_query_simple
 */
#define PEAK_IS_READABLE(accessStatus) ((((accessStatus) & 0x1000) == 0x1000) ? PEAK_TRUE : PEAK_FALSE)

/*!
 * \ingroup library
 * \brief Init the peak comfortC library
 *
 * Initializes the internal library status.
 *
 * This function must be called prior to any other function call.\n
 * The function may be called multiple times from a single client process.
 * For each call there must be a corresponding call to #peak_Library_Exit
 * to ensure proper deinitialization of the library status.
 *
 * \return #PEAK_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ERROR   An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Library_Init();

/*! 
 * \ingroup library
 * \brief Exit the peak comfortC library
 *
 * Deinitializes the internal library status.
 *
 * For each call to #peak_Library_Init there must be a corresponding call to this function
 * to ensure proper deinitialization of the library status. \n
 * After the library has been exited its functions (besides #peak_Library_Init) will not be operable
 * until #peak_Library_Init has been called again.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Library_Exit();

/*!
* \ingroup library
* \brief Query the library version
*
* Provides the version of the library divided in major, minor, subminor and patch, in that order of magnitude.
*
* You are allowed to pass NULL for parts you are not interested in.
*
* \param[out] majorVersion      Major Version. NULL if not required.
* \param[out] minorVersion      Minor Version. NULL if not required.
* \param[out] subminorVersion   Subminor Version. NULL if not required.
* \param[out] patchVersion      Patch Version. NULL if not required.
*
* \return #PEAK_STATUS_SUCCESS  Operation was successful; no error occurred.
*
* \note This function can be used even if the library is not initialized.
*/
PEAK_API_STATUS peak_Library_GetVersion(uint32_t* majorVersion, uint32_t* minorVersion, uint32_t* subminorVersion,
    uint32_t* patchVersion);

/*!
 * \ingroup library
 * \brief Query the last error
 * 
 * Provides a readable text description of the last error occurred in the local thread context.
 * 
 * The library stores the last error thread local, i.e. for each thread separately. \n
 * If any library function fails and reports an error status this function can be used to query a text message
 * which gives details on the error that occurred. \n
 * In case an error occurs and after that several other function calls return without error the
 * last error value and description is returned and the successful calls are ignored. \n
 * If there has not been any error in the given thread context since startup the function will return
 * #PEAK_STATUS_SUCCESS with \p *peak_status also set to #PEAK_STATUS_SUCCESS and \p lastErrorMessage containing
 * "No Error". \n
 * In case peak_Library_GetLastError itself generates an error it will return the according error code
 * but it will not store the error internally so that succeeding calls to peak_Library_GetLastError will still be able
 * to report the stored error code.
 * \see \ref principle_last_error_handling
 *
 * This function implements the \ref principle_two_stage_query principle.
 * 
 * \param[out] lastErrorCode            The error code of the last error. NULL if not required.
 * \param[out] lastErrorMessage         Pointer to a user allocated C string buffer to receive the last error text.
 *                                      If this parameter is NULL, \p lastErrorMessageSize will contain the needed size
 *                                      of \p lastErrorMessage in bytes. The size includes the terminating 0.
 * \param[in,out] lastErrorMessageSize  \li \p lastErrorMessage equal NULL: \n
 *                                          out: minimal size of \p lastErrorMessage in bytes to hold all information \n
 *                                      \li \p lastErrorMessage unequal NULL: \n
 *                                          in: size of the provided \p lastErrorMessage in bytes \n
 *                                          out: number of bytes filled by the function
 * 
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p lastErrorMessage is not NULL and the value of \p *lastErrorMessageSize is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p lastErrorMessageSize is an invalid pointer.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 * \note This function can be used even if the library is not initialized.
 *       This is useful in the case that #peak_Library_Init fails.
 */
PEAK_API_STATUS peak_Library_GetLastError(peak_status* lastErrorCode, char* lastErrorMessage,
    size_t* lastErrorMessageSize);

/*!
 * \ingroup camera
 * \brief peak Camera types
 *
 * The camera type defines the camera family and the bus interface / protocol.
 */
typedef enum
{
    /*! \brief Invalid camera type
     *
     * Use this value for the initialization of variables of type peak_camera_type.
     */
    PEAK_CAMERA_TYPE_INVALID        = 0,

    /*! \brief uEye USB camera */
    PEAK_CAMERA_TYPE_UEYE_USB       = 0x1101,

    /*! \brief uEye Eth camera */
    PEAK_CAMERA_TYPE_UEYE_ETH       = 0x1202,

    /*! \brief uEye+ USB3 Vision camera */
    PEAK_CAMERA_TYPE_UEYE_PLUS_U3V  = 0x2101,

    /*! \brief uEye+ GigE Vision camera */
    PEAK_CAMERA_TYPE_UEYE_PLUS_GEV  = 0x2202

} peak_camera_type;

/*!
 * \ingroup camera
 * \brief peak Camera handle
 *
 * The camera handle represents an opened camera. \n
 * The camera handle is provided by the peak_Camera_Open_Xxx functions and
 * must be released by #peak_Camera_Close. \n
 * The camera handle is required in every function which controls a camera of its features.
 *
 * The value for an invalid camera handle is #PEAK_INVALID_HANDLE.
 */
typedef struct peak_camera* peak_camera_handle;

/*!
 * \ingroup camera
 * \brief peak Camera ID
 *
 * The camera id is a unique identifier for a camera.
 *
 * The camera related functions which can be used without opening a camera require the camera id as identifier. \n
 * The id for a certain camera will not change over the session runtime as long as the camera is not re-connected.
 * A re-connected camera will be assigned a new unique camera id on its re-appearance. \n
 * I.e. a once assigned camera id is considered as burnt and will not be reused for a later (re-)connected camera.
 *
 * The value for an invalid camera id is #PEAK_INVALID_CAMERA_ID.
 */
typedef uint64_t peak_camera_id;

/*!
 * \ingroup camera
 * \brief peak Invalid camera ID value
 *
 * Use this value for the initialization of variables of type #peak_camera_id.
 */
#define PEAK_INVALID_CAMERA_ID UINT64_C(0)

#pragma pack(push, 1)
/*!
 * \ingroup camera
 * \brief peak Camera descriptor
 *
 * The camera descriptor collects information on a camera.
 * 
 * Use #peak_Camera_GetDescriptor to query the camera descriptor for an individual camera. \n
 * Use #peak_CameraList_Get to query the list of camera descriptors for all detected cameras.
 */
typedef struct
{
    /*! \brief The camera id */
    peak_camera_id cameraID;

    /*! \brief The camera type */
    peak_camera_type cameraType;

    /*! \brief The cameras model name
     *
     * Zero-terminated string.
     */
    char modelName[64];

    /*! \brief The cameras serial number
     *
     * Zero-terminated string.
     */
    char serialNumber[64];

    uint8_t reserved[512];

} peak_camera_descriptor;
#pragma pack(pop)

/*!
 * \ingroup camera
 * \brief Update the camera list
 * 
 * Initiates a camera discovery and an update of the camera list.
 * 
 * This function is required to be called to create or update the camera list.
 * The camera list does not change unless this function is called again.
 * 
 * \param[out] cameraCount The number of connected cameras. NULL if not required.
 * 
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 * 
 * \note Depending on the installed transport layers the camera list may take some hundred milliseconds.
 *       This is because the discovery of cameras via so called connectionless network protocols like ethernet requires
 *       a timeout controlled procedure.
 */
PEAK_API_STATUS peak_CameraList_Update(size_t* cameraCount);

/*!
 * \ingroup camera
 * \brief Query the current camera list
 * 
 * Provides the current list of detected cameras.
 *
 * This function implements the \ref principle_two_stage_query principle.
 * 
 * \param[out] cameraList       Pointer to a user allocated array buffer to receive the camera list.
 *                              If this parameter is NULL, \p cameraCount will contain the current number of cameras. \n
 *                              The needed size of \p cameraList in bytes is
 *                              \p cameraCount x sizeof(#peak_camera_descriptor).
 * \param[in,out] cameraCount   \li \p cameraList equal NULL: \n
 *                                  out: minimal number of cameras \p cameraList must be large enough to hold \n
 *                              \li \p cameraList unequal NULL: \n
 *                                  in: number of cameras \p cameraList can hold \n
 *                                  out: number of cameras filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p cameraList is not NULL and the value of \p *cameraCount is too small to
 *                                          receive the expected amount of data.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraCount is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 * \note Consider that the camera list might change between the size query call and the list query call.
 *       This may be the case if #peak_CameraList_Update is called and cameras have been attached or detached
 *       in the time between the two function calls.
 *       To eliminate this issue you may want to use an array for \p cameraList which is large enough to hold
 *       all possibly connected cameras and to spare the size query call.
 */
PEAK_API_STATUS peak_CameraList_Get(peak_camera_descriptor* cameraList, size_t* cameraCount);

/*!
 * \ingroup camera
 * \brief Query the camera id by the camera handle
 *
 * Provides the camera id of the camera which the specified camera handle.
 *
 * This function implements the \ref principle_camera_id_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return The camera id of the camera with the handle \p hCam.
 * \return #PEAK_INVALID_CAMERA_ID The function failed.
 *                                 Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_INVALID_CAMERA_ID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_CAMERA_ID peak_Camera_ID_FromHandle(peak_camera_handle hCam);

/*!
 * \ingroup camera
 * \brief Query the camera id by the serial number
 *
 * Provides the camera id of the camera which the specified serial number.
 *
 * This function implements the \ref principle_camera_id_query principle.
 *
 * \param[in] serialNumber The serial number of the camera. Zero-terminated C string.
 *
 * \return The camera id of the camera with the serial number \p serialNumber.
 * \return #PEAK_INVALID_CAMERA_ID The function failed.
 *                                 Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_INVALID_CAMERA_ID, these are the possible errors:
 * \li #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified serial number.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p serialNumber is an invalid pointer or it is not zero-terminated.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_CAMERA_ID peak_Camera_ID_FromSerialNumber(const char* serialNumber);

#pragma pack(push, 1)
/*!
 * \ingroup ethernet_config
 * \brief peak MAC-48 address
 *
 * Bsp: 98-3B-8F-9D-2C-3B
 * octet[0] = 0x98
 * octet[1] = 0x3B
 * octet[2] = 0x8F
 * octet[3] = 0x9D
 * octet[4] = 0x2C
 * octet[5] = 0x3B
 */
typedef union
{
    /*! \brief The octets, i.e. the MAC address in byte array representation */
    uint8_t octets[6];

    /*! \brief parts */
    struct
    {
        /*! \brief Upper 2 bytes of the MAC address */
        uint16_t high_part;

        /*! \brief Lower 4 bytes of the MAC address */
        uint32_t low_part;

    } parts;

} peak_mac_address;
#pragma pack(pop)

/*!
 * \ingroup camera
 * \brief Query the camera id by the mac address
 *
 * Provides the camera id of the camera which the specified mac address.
 *
 * This function implements the \ref principle_camera_id_query principle.
 *
 * \param[in] macAddress The macAddress of the camera.
 *
 * \return The camera id of the camera with the mac address \p macAddress.
 * \return #PEAK_INVALID_CAMERA_ID The function failed.
 *                                 Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_INVALID_CAMERA_ID, these are the possible errors:
 * \li #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified mac address.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_CAMERA_ID peak_Camera_ID_FromMAC(peak_mac_address macAddress);

/*!
 * \ingroup camera
 * \brief Query the camera access status
 *
 * Provides the current access status for a camera which is specified by its camera id.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] cameraID The camera id.
 *
 * \return #PEAK_ACCESS_READWRITE   The camera is available for read access and for write access and can be opened.
 * \return #PEAK_ACCESS_NONE        The camera is not available for opening.
 * \return #PEAK_ACCESS_INVALID     The function failed.
 *                                  Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified ID.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Camera_GetAccessStatus(peak_camera_id cameraID);

/*!
 * \ingroup camera
 * \brief Query the camera descriptor
 *
 * Provides the camera descriptor for the camera which is specified by its camera id.
 *
 * \param[in] cameraID          The camera id.
 * \param[out] cameraDescriptor The camera descriptor.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified id.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraDescriptor an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Camera_GetDescriptor(peak_camera_id cameraID, peak_camera_descriptor* cameraDescriptor);

/*!
 * \ingroup camera
 * \brief Open the camera by the Camera id
 *
 * Opens the camera with the specified camera id.
 *
 * \param[in] cameraID  The camera id of the camera to open.
 * \param[out] hCam     The camera handle.
 *
 * \return #PEAK_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_STATUS_CAMERA_NOT_FOUND        There is no camera with the specified camera id.
 * \return #PEAK_STATUS_CAMERA_NOT_AVAILABLE    The specified camera is currently not available.
 * \return #PEAK_STATUS_INVALID_PARAMETER       \p hCam is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED         The library is not initialized.
 * \return #PEAK_STATUS_ERROR                   An unexpected internal error occurred.
 * 
 * \note If the function fails it will set * \p hCam to #PEAK_STATUS_INVALID_HANDLE.
 */
PEAK_API_STATUS peak_Camera_Open(peak_camera_id cameraID, peak_camera_handle* hCam);

/*!
 * \ingroup camera
 * \brief Open the first available camera
 *
 * Opens the first available camera.
 * The implementation selects a camera with the access status #PEAK_ACCESS_READWRITE and opens it.
 *
 * \param[out] hCam The camera handle.
 *
 * \return #PEAK_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_STATUS_CAMERA_NOT_AVAILABLE    There is currently no available camera.
 * \return #PEAK_STATUS_INVALID_PARAMETER       \p hCam is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED         The library is not initialized.
 * \return #PEAK_STATUS_ERROR                   An unexpected internal error occurred.
 *
 * \note If the function fails it will set * \p hCam to #PEAK_STATUS_INVALID_HANDLE.
 */
PEAK_API_STATUS peak_Camera_OpenFirstAvailable(peak_camera_handle* hCam);

/*!
 * \ingroup camera
 * \brief Close the camera
 * 
 * Closes the specified camera.
 * 
 * \param[in] hCam The handle of the camera to close.
 * 
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 * 
 * \note The camera handle is no longer valid after the function has returned.
 */
PEAK_API_STATUS peak_Camera_Close(peak_camera_handle hCam);

/*!
 * \ingroup camera
 * \brief Reset the camera configuration
 *
 * Resets the specified camera to its default configuration.
 *
 * \param[in] hCam The handle of the camera to reset.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_ACCESS_DENIED   The feature is currently not accessible. Check for a running acquisition.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Camera_ResetToDefaultSettings(peak_camera_handle hCam);

#pragma pack(push, 1)
/*!
 * \ingroup ethernet_config
 * \brief peak IPv4 address
 *
 * The peak ip v4 address defines an ip v4 address in little-endian byte order.
 * 
 * Bsp: 192.168.10.1
 * part[0] = 192
 * part[1] = 168
 * part[2] = 10
 * part[3] = 1
 */
typedef union
{
    /*! \brief The IP address in little-endian word representation */
    uint32_t addr;

    /*! \brief The IP address in little-endian byte array representation */
    uint8_t parts[4];

} peak_ip_address;
#pragma pack (pop)

#pragma pack (push, 1)
/*!
 * \ingroup ethernet_config
 * \brief peak IP configuration
 *
 * The ip configuration combines an ip address and an ip subnet mask.
 */
typedef struct
{
    /*! \brief The ip address */
    peak_ip_address address;

    /*! \brief The subnet mask */
    peak_ip_address subnetMask;

    uint8_t reserved[4];

} peak_ip_config;
#pragma pack (pop)

/*!
 * \ingroup ethernet_config
 * \brief peak Ethernet status
 *
 * The ethernet status defines the current status of a cameras ethernet configuration.
 */
typedef enum
{
    /*! \brief Invalid ethernet status
     *
     * Use this value for the initialization of variables of type peak_ethernet_status.
     */
    PEAK_ETHERNET_STATUS_INVALID            = 0,

    /*! \brief The cameras ethernet status is ok
     *
     * The ethernet configuration is operable.
     */
    PEAK_ETHERNET_STATUS_OK                 = 0x0001,

    /*! \brief The cameras ethernet status is not ok
     *
     * The ethernet configuration is not operable.
     */
    PEAK_ETHERNET_STATUS_NOK                = 0x8001,

    /*! \brief The camera persistent IP is not in the hosts subnet
     *
     * The hosts subnet is the hosts ip address AND-ed with the hosts subnet mask. \n
     * The cameras subnet is the cameras ip address AND-ed with the cameras subnet mask. \n
     * In order to have an operable ethernet connection the hosts subnet and the cameras subnet must match.
     */
    PEAK_ETHERNET_STATUS_SUBNET_MISMATCH    = 0x8002,

    /*! \brief The camera IP is not applicable
     *
     * The camera ip is not applicable on the network.
     * 
     * Make sure that the cameras persistent ip address is not used by any other device that is connected to
     * the same network.
     */
    PEAK_ETHERNET_STATUS_INAPPLICABLE_IP    = 0x8003

} peak_ethernet_status;

#pragma pack (push, 1)
/*!
 * \ingroup ethernet_config
 * \brief peak Ethernet info
 *
 * The ethernet info collects information on the ethernet configuration of a camera.
 *
 * Use #peak_EthernetConfig_GetInfo to query the ethernet info for an individual camera.
 */
typedef struct
{
    /*! \brief The mac address of the camera */
    peak_mac_address cameraMAC;

    /*! \brief The current ip address of the camera */
    peak_ip_config cameraIP;

    /*! \brief The current DHCP enabled status of the camera */
    peak_bool cameraDHCPEnabled;

    /*! \brief The current persistent ip address of the camera */
    peak_ip_config cameraPersistentIP;

    /*! \brief The current ethernet status of the camera */
    peak_ethernet_status cameraEthernetStatus;

    uint8_t reservedCamera[64];

    /*! \brief The current subnet mask of the host */
    peak_ip_config hostIP;

    /*! \brief The mac address of the host */
    peak_mac_address hostMAC;

    uint8_t reserved[64];

} peak_ethernet_info;
#pragma pack (pop)

/*!
 * \ingroup ethernet_config
 * \brief Query the ethernet configuration access status
 *
 * Provides the current access status for the ethernet configuration of the specified camera.
 * 
 * \note The ethernet configuration is supported only for cameras of
 *       the types #PEAK_CAMERA_TYPE_UEYE_ETH and #PEAK_CAMERA_TYPE_UEYE_PLUS_GEV.
 * \note The ethernet configuration is available only for change if the camera is not opened.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] cameraID The camera id.
 *
 * \return #PEAK_ACCESS_READWRITE       The ethernet configuration is supported and currently available for change.
 * \return #PEAK_ACCESS_READONLY        The ethernet configuration is supported but currently not available for change.
 *                                      Check for the camera to be not opened.
 * \return #PEAK_ACCESS_GFA_LOCK        The ethernet configuration is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The ethernet configuration is not supported.
 *                                      Check for the camera to be of one of
 *                                      the types #PEAK_CAMERA_TYPE_UEYE_ETH and #PEAK_CAMERA_TYPE_UEYE_PLUS_GEV.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified camera id.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_EthernetConfig_GetAccessStatus(peak_camera_id cameraID);

/*!
 * \ingroup ethernet_config
 * \brief Query the ethernet information
 *
 * Provides the ethernet information for the camera which is specified by its camera id.
 *
 * \param[in] cameraID      The camera id.
 * \param[out] ethernetInfo The ethernet info.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The ethernet info feature is not accessible for read.
 *                                          Check the access status via #peak_EthernetConfig_GetAccessStatus.
 * \return #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified id.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p ethernetInfo is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_EthernetConfig_GetInfo(peak_camera_id cameraID, peak_ethernet_info* ethernetInfo);

/*!
 * \ingroup ethernet_config
 * \brief Query the dhcp access status
 *
 * Provides the current access status for the dhcp setting of the specified camera.
 *
 * \note The dhcp setting is supported only for cameras of
 *       the types #PEAK_CAMERA_TYPE_UEYE_ETH and #PEAK_CAMERA_TYPE_UEYE_PLUS_GEV.
 * \note The dhcp setting is available only for change if the camera is not opened.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] cameraID The camera id.
 *
 * \return #PEAK_ACCESS_READWRITE       The dhcp setting is supported and currently available for change.
 * \return #PEAK_ACCESS_READONLY        The dhcp setting is supported but currently not available for change.
 *                                      Check for the camera to be not opened.
 * \return #PEAK_ACCESS_GFA_LOCK        The dhcp setting is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The dhcp setting is not supported.
 *                                              Check for the camera type to be #PEAK_CAMERA_TYPE_UEYE_PLUS_GEV.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                              Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified camera id.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_EthernetConfig_DHCP_GetAccessStatus(peak_camera_id cameraID);

/*!
 * \ingroup ethernet_config
 * \brief Enable/Disable dhcp
 *
 * Sets dhcp to enabled or disabled.
 * 
 * \note If dhcp is enabled the camera will not use a possibly configured persistent ip. \n
 *       If dhcp is enabled and the camera fails to acquire an address from a dhcp server in the network it may
 *       fall back to a so called link-local address. Or it may get into a configuration state with an
 *       inapplicable ip address. \n
 *       Whether the camera implements the link-local fall back depends on its model and firmware implementation.
 *
 * \param[in] cameraID  The camera id.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The dhcp feature is not accessible for write.
 *                                          Check the access status via #peak_EthernetConfig_DHCP_GetAccessStatus.
 * \return #PEAK_STATUS_ABORTED             The could not be moved to the current subnet because no available IP was 
 *                                          found. Therefore, dhcp could not be enabled.
 * \return #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified camera id.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 * \note A change of the dhcp enabled status results in the camera re-connecting to the ethernet. For the system this
 *       is the same as if the camera is removed and re-attached. \n
 *       This means that the camera needs to be newly discovered and the #peak_camera_id changes after the dhcp status 
 *       change. \n
 *       Use #peak_CameraList_Update() to initiate an update of the camera list. \n
 *       Consider that the camera may need some time to re-connect to the ethernet.
 */
PEAK_API_STATUS peak_EthernetConfig_DHCP_Enable(peak_camera_id cameraID, peak_bool enabled);

/*!
 * \ingroup ethernet_config
 * \brief Get the enabled status of dhcp
 *
 * Queries whether dhcp is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] cameraID The camera id.
 *
 * \return #PEAK_TRUE   The dhcp feature is currently enabled.
 * \return #PEAK_FALSE  The dhcp feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_EthernetConfig_DHCP_IsEnabled(peak_camera_id cameraID);

/*!
 * \ingroup ethernet_config
 * \brief Query the persistent ip access status
 *
 * Provides the current access status for the persistent ip setting of the specified camera.
 *
 * \note The persistent ip setting is supported only for cameras of
 *       the types #PEAK_CAMERA_TYPE_UEYE_ETH and #PEAK_CAMERA_TYPE_UEYE_PLUS_GEV.
 * \note The persistent ip setting is available only for change if the camera is not opened.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] cameraID The camera id.
 *
 * \return #PEAK_ACCESS_READWRITE       The persistent ip setting is supported and currently available for change.
 * \return #PEAK_ACCESS_READONLY        The persistent ip setting is supported but currently not available for change.
 *                                      Check for the camera to be not opened.
 * \return #PEAK_ACCESS_WRITEONLY       The persistent ip cannot be read from the camera, but a new IP can be assigned.
 * \return #PEAK_ACCESS_GFA_LOCK        The persistent ip setting is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The persistent ip setting is not supported.
 *                                      Check for the camera to be of one of
 *                                      the types #PEAK_CAMERA_TYPE_UEYE_ETH and #PEAK_CAMERA_TYPE_UEYE_PLUS_GEV.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified camera id.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_EthernetConfig_PersistentIP_GetAccessStatus(peak_camera_id cameraID);

/*!
 * \ingroup ethernet_config
 * \brief Set the persistent ip
 *
 * Sets the persistent ip address.
 *
 * \param[in] cameraID      The camera id.
 * \param[in] persistentIP  The desired persistent ip.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The persistent ip feature is not accessible for write.
 *                                          Check the access status via
 *                                          #peak_EthernetConfig_PersistentIP_GetAccessStatus.
 * \return #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified camera id.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p persistentIP is an invalid ip.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note A change of the persistent ip while dhcp is not enabled results in the camera re-connecting to the ethernet.
 *       For the system this is the same as if the camera is removed and re-attached. \n
 *       This means that the camera needs to be newly discovered and the #peak_camera_id changes after the persistent 
 *       ip change. \n
 *       Use #peak_CameraList_Update() to initiate an update of the camera list. \n
 *       Consider that the camera may need some time to re-connect to the ethernet.
 */
PEAK_API_STATUS peak_EthernetConfig_PersistentIP_Set(peak_camera_id cameraID, peak_ip_config persistentIP);

/*!
 * \ingroup ethernet_config
 * \brief Get the persistent ip
 *
 * Reads the current persistent ip.
 *
 * \param[in] cameraID      The camera id.
 * \param[out] persistentIP The persistent ip.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The persistent ip feature is not available for read access.
 *                                          Check the access status via
 *                                          #peak_EthernetConfig_PersistentIP_GetAccessStatus.
 * \return #PEAK_STATUS_CAMERA_NOT_FOUND    There is no camera with the specified camera id.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p persistentIP is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_EthernetConfig_PersistentIP_Get(peak_camera_id cameraID, peak_ip_config* persistentIP);

/*!
 * \ingroup frame
 * \brief peak Frame handle
 *
 * A frame represents an image or other types of bulk data received from a camera.
 * It collects all information on the received data. \see peak_frame_info.
 *
 * The frame handle represents a frame which is delivered to the user. \n
 * The frame handle is provided by #peak_Acquisition_WaitForFrame and
 * must be released by #peak_Frame_Release. \n
 * The frame handle is required by the peak_Frame_Xxx functions to query information on the received frame.
 *
 * As long as a frame is in the hands of the user (i.e. delivered) the implementation will not store any data
 * to the associated buffer. \n
 * As soon as the frame is released via #peak_Frame_Release new data can be stored in the associated buffer.
 *
 * \note #peak_Acquisition_Start will be rejected as long as there are unreleased frame handles.
 *
 * The value for an invalid frame handle is #PEAK_INVALID_HANDLE.
 */
typedef struct peak_frame* peak_frame_handle;

/*!
 * \ingroup acquisition_and_buffer_preparation
 * \brief peak Acquisition info
 * 
 * The acquisition info reflects the status of the current or the most recent acquisition
 * by several counters and measures.
 */
#pragma pack(push, 1)
typedef struct
{
    /*! \brief Number of buffer underruns
     * 
     * The counter is reset to zero on acquisition start.
     * 
     * \see \ref term_buffer_underrun
     */
    uint32_t numUnderrun;

    /*! \brief Number of dropped frames
     *
     * The counter is reset to zero on acquisition start.
     * 
     * \see \ref term_dropped_frame
     */
    uint32_t numDropped;

    /*! \brief Number of incomplete frame transmissions
     *
     * The counter is reset to zero on acquisition start.
     * 
     * \see \ref term_incomplete_frame
     */
    uint32_t numIncomplete;

    /*! \brief Measured framerate
     *
     * The measured rate of incoming frames in Hz.
     *
     * \note The framerate measuring is currently not implemented!
     */
    double fps;

    uint8_t reserved[256];

} peak_acquisition_info;
#pragma pack(pop)

/*!
 * \ingroup acquisition_and_buffer_preparation
 * \brief Start an acquisition
 * 
 * Starts an acquisition session for the specified number of frames.
 * 
 * The acquisition can be stopped at any time via #peak_Acquisition_Stop. \n
 * If \p numberOfFrames is not #PEAK_INFINITE the acquisition is automatically stopped when the specified number
 * of frames has been acquired.
 * 
 * \param[in] hCam              The camera handle.
 * \param[in] numberOfFrames    The number of frames to acquire. #PEAK_INFINITE for infinite.
 * 
 * \return #PEAK_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED           There is already a running acquisition
 *                                              or the camera does not provide a data stream
 *                                              or not all frames from a previous acquisition have been released.
 * \return #PEAK_STATUS_INVALID_CONFIGURATION   Only relevant in the \ref concept_manual_buffer_preparation mode. \n
 *                                              The buffers are not sufficiently sized to receive the image data that
 *                                              results from the current image properties
 *                                              (see #peak_Acquisition_Buffer_GetRequiredSize)
 *                                              or the number of announced buffers is not sufficient to run an
 *                                              efficient data transfer
 *                                              (see #peak_Acquisition_Buffer_GetRequiredCount).
 * \return #PEAK_STATUS_INVALID_PARAMETER       \p numberOfFrames is 0.
 * \return #PEAK_STATUS_INVALID_HANDLE          \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED         The library is not initialized.
 * \return #PEAK_STATUS_ERROR                   An unexpected internal error occurred.
 * 
 * \note Make sure that you have completed the configuration of all features, which have an impact on the image size,
 *       before you call peak_Acquisition_Start.
 * \note The library will automatically stop the acquisition when the number of requested frames has been received.
 *       This automatic acquisition stop is run asynchronously to have #peak_Acquisition_WaitForFrame return
 *       the last frame without any delay.
 *       In order to be sure that a finite acquisition sequence is stopped, call #peak_Acquisition_Stop, which will
 *       block until the acquisition has been stopped.
 *       As some features are not accessible while an acquisition is running, this is useful to synchronize the
 *       applications control flow with the libraries internal status.
 * \note The acquisition can not be started if there are any unreleased frames from an earlier acquisition sequence.
 * \note If you decide upon \ref concept_manual_buffer_preparation make sure that all buffers are
 *       allocated and announced before you call peak_Acquisition_Start.
 *       The buffer memory must be valid for the time the acquisition runs.
 */
PEAK_API_STATUS peak_Acquisition_Start(peak_camera_handle hCam, uint32_t numberOfFrames);

/*!
 * \ingroup acquisition_and_buffer_preparation
 * \brief Stops an acquisition
 * 
 * Stops an acquisition before the number of frames that was specified for #peak_Acquisition_Start has been acquired.
 * 
 * The acquisition is stopped immediately. If there is a frame in transmission at the time peak_Acquisition_Stop is
 * called, this frame is discarded.
 * 
 * All pending calls to #peak_Acquisition_WaitForFrame will immediately return with #PEAK_STATUS_ABORTED.
 * 
 * This function will always block until the acquisition has actually been stopped.
 * 
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 * 
 * \note This function will return #PEAK_STATUS_SUCCESS if there is no running acquisition.
 */
PEAK_API_STATUS peak_Acquisition_Stop(peak_camera_handle hCam);

/*!
 * \ingroup acquisition_and_buffer_preparation
 * \brief Check whether the acquisition is currently started or not
 *
 * Checks whether the acquisition is currently started or not.
 *
 * This function implements the \ref principle_valid_values_organization_query principle.
 * 
 * Parallel calls to peak_Acquisition_IsStarted return true until the blocking peak_Acquisition_Stop returns!
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The acquisition is currently started.
 * \return #PEAK_FALSE  The acquisition is currently not started or the query failed.
 */
PEAK_API_BOOL peak_Acquisition_IsStarted(peak_camera_handle hCam);

/*!
 * \ingroup acquisition_and_buffer_preparation
 * \brief Wait for an acquired frame
 * 
 * Delivers the oldest acquired frame.
 * 
 * The implementation queues the acquired frames in chronological order for delivery to the client application.
 * peak_Acquisition_WaitForFrame delivers the oldest queued frame.
 * 
 * A frame that was received from peak_Acquisition_WaitForFrame is considered as 'delivered'. \n
 * The buffer that is bound to a delivered frame is locked for the reception of incoming image data until
 * #peak_Frame_Release has been called for the frame. \n
 * #peak_Acquisition_Start will be rejected as long as there are unreleased frame handles for frames that were received
 * from peak_Acquisition_WaitForFrame.
 * 
 * If there is no frame in the delivery queue by the time of the call the function blocks until a frame was acquired
 * or the specified timeout has elapsed.
 * 
 * A pending call returns with #PEAK_STATUS_ABORTED when the acquisition is stopped (automatically or by a call to
 * #peak_Acquisition_Stop).
 * 
 * \param[in] hCam          The camera handle.
 * \param[in] timeout_ms    The wait timeout in milliseconds. #PEAK_INFINITE for infinite.
 * \param[out] hFrame       Handle to the acquired frame.
 * 
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_TIMEOUT             The wait timeout has elapsed and no frame has been acquired.
 * \return #PEAK_STATUS_ABORTED             The wait was abandoned because the acquisition was stopped.
 * \return #PEAK_STATUS_ACCESS_DENIED       There is no running acquisition.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p timeout_ms is 0 or \p hFrame is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Acquisition_WaitForFrame(peak_camera_handle hCam, uint32_t timeout_ms, peak_frame_handle* hFrame);

/*!
 * \ingroup acquisition_and_buffer_preparation
 * \brief Query the acquisition info
 * 
 * Provides the status of the current acquisition session or, if there is no active
 * acquisition at the time of the call, of the last acquisition session, if any.
 * 
 * \param[in] hCam              The camera handle.
 * \param[out] acquisitionInfo  The acquisition info.
 * 
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p acquisitionInfo is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_ACCESS_DENIED       There has been no acquisition session yet.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Acquisition_GetInfo(peak_camera_handle hCam, peak_acquisition_info* acquisitionInfo);

/*!
 * \ingroup manual_buffer_preparation
 * \brief Query the required image buffer size
 *
 * Provides the buffer size that is required to receive the image data that results from the current feature
 * configuration.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] requiredBufferSize   The required buffer size in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p requiredBufferSize is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Acquisition_Buffer_GetRequiredSize(peak_camera_handle hCam, size_t* requiredBufferSize);

/*!
 * \ingroup manual_buffer_preparation
 * \brief Query the required image buffer count
 *
 * Provides the number of buffers that is required for an image acquisition.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] requiredBufferCount  The required number of buffer.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p requiredBufferCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Acquisition_Buffer_GetRequiredCount(peak_camera_handle hCam, size_t* requiredBufferCount);

/*!
 * \ingroup manual_buffer_preparation
 * \brief Announce an image buffer
 *
 * Announces a user-allocated buffer for the receival of image data.
 *
 * This function must be used only if \ref concept_manual_buffer_preparation is desired. \n
 * As long as there is at least one buffer announced via peak_Acquisition_Buffer_Announce the implementation will
 * completely rely on user-allocated buffers.
 *
 * Call #peak_Acquisition_Buffer_Revoke to revoke an announced buffer from the implementation.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] memoryAddress The memory address at which the buffer starts.
 * \param[in] memorySize    The size of allocated buffer memory.
 * \param[in] userContext   User context pointer. The user context allows to bind a pointer to a data object to the
 *                          buffer. NULL if not used.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The acquisition is active.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p memoryAddress is an invalid pointer and/or \p memorySize is 0.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note If there is at least one buffer announced via peak_Acquisition_Buffer_Announce #peak_Acquisition_Start will
 *       succeed only
 *       \li if all announced buffers are capable of storing a complete image, and
 *       \li if the number of announced buffers is sufficient to run an acquisition.
 * \note The required buffer size can be queried via #peak_Acquisition_Buffer_GetRequiredSize and the required number
 *       of buffers can be queried via #peak_Acquisition_Buffer_GetRequiredCount.
 * \note The client application is responsible for the deallocation of the announced memory. The memory must be valid
 *       until #peak_Acquisition_Buffer_Revoke is called for the related memory address.
 */
PEAK_API_STATUS peak_Acquisition_Buffer_Announce(peak_camera_handle hCam, uint8_t* memoryAddress, size_t memorySize,
    void* userContext);

/*!
 * \ingroup manual_buffer_preparation
 * \brief Revoke an image buffer
 *
 * Revokes a previously announced buffer.
 *
 * This function must be used only if \ref concept_manual_buffer_preparation is desired.
 *
 * Call #peak_Acquisition_Buffer_Announce to announce a buffer to the implementation.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] memoryAddress The memory address at which the buffer starts.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The acquisition is active
 *                                          or the frame handle for this buffer is not released.
 * \return #PEAK_STATUS_NO_DATA             There is no announced buffer with the specified memory address.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p memoryAddress is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Acquisition_Buffer_Revoke(peak_camera_handle hCam, uint8_t* memoryAddress);

/*!
 * \ingroup manual_buffer_preparation
 * \brief Revoke all image buffers
 *
 * Revokes all previously announced buffers.
 *
 * This function must be used only if \ref concept_manual_buffer_preparation is desired.
 *
 * Call #peak_Acquisition_Buffer_Announce to announce a buffer to the implementation.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The acquisition is active or at least one frame handle is not released.
 * \return #PEAK_STATUS_NO_DATA             There are no announced buffers.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Acquisition_Buffer_RevokeAll(peak_camera_handle hCam);

/*!
 * \ingroup pixelformat
 * \brief peak Pixel format
 *
 * The pixel format specifies the representation of a pixel in an image.
 */
typedef enum
{
    /*! \brief Invalid pixel format
     *
     * Use this value for the initialization of variables of type peak_pixel_format.
     */
    PEAK_PIXEL_FORMAT_INVALID           = 0,

    /*! \brief BayerGR8 */
    PEAK_PIXEL_FORMAT_BAYER_GR8         = 0x01080008,

    /*! \brief BayerGR10 */
    PEAK_PIXEL_FORMAT_BAYER_GR10        = 0x0110000C,

    /*! \brief BayerGR12 */
    PEAK_PIXEL_FORMAT_BAYER_GR12        = 0x01100010,

    /*! \brief BayerRG8 */
    PEAK_PIXEL_FORMAT_BAYER_RG8         = 0x01080009,

    /*! \brief BayerRG10 */
    PEAK_PIXEL_FORMAT_BAYER_RG10        = 0x0110000D,

    /*! \brief BayerRG12 */
    PEAK_PIXEL_FORMAT_BAYER_RG12        = 0x01100011,

    /*! \brief BayerGB8 */
    PEAK_PIXEL_FORMAT_BAYER_GB8         = 0x0108000A,

    /*! \brief BayerGB10 */
    PEAK_PIXEL_FORMAT_BAYER_GB10        = 0x0110000E,

    /*! \brief BayerGB12 */
    PEAK_PIXEL_FORMAT_BAYER_GB12        = 0x01100012,

    /*! \brief BayerBG8 */
    PEAK_PIXEL_FORMAT_BAYER_BG8         = 0x0108000B,

    /*! \brief BayerBG10 */
    PEAK_PIXEL_FORMAT_BAYER_BG10        = 0x0110000F,

    /*! \brief BayerBG12 */
    PEAK_PIXEL_FORMAT_BAYER_BG12        = 0x01100013,

    /*! \brief Mono8 */
    PEAK_PIXEL_FORMAT_MONO8             = 0x01080001,

    /*! \brief Mono10 */
    PEAK_PIXEL_FORMAT_MONO10            = 0x01100003,

    /*! \brief Mono12 */
    PEAK_PIXEL_FORMAT_MONO12            = 0x01100005,

    /*! \brief RGB8 */
    PEAK_PIXEL_FORMAT_RGB8              = 0x02180014,

    /*! \brief RGB10 */
    PEAK_PIXEL_FORMAT_RGB10             = 0x02300018,

    /*! \brief RGB12 */
    PEAK_PIXEL_FORMAT_RGB12             = 0x0230001A,

    /*! \brief BGR8 */
    PEAK_PIXEL_FORMAT_BGR8              = 0x02180015,

    /*! \brief BGR10 */
    PEAK_PIXEL_FORMAT_BGR10             = 0x02300019,

    /*! \brief BGR12 */
    PEAK_PIXEL_FORMAT_BGR12             = 0x0230001B,

    /*! \brief RGBa8 */
    PEAK_PIXEL_FORMAT_RGBA8             = 0x02200016,

    /*! \brief RGBa10 */
    PEAK_PIXEL_FORMAT_RGBA10            = 0x0240005F,

    /*! \brief RGBa12 */
    PEAK_PIXEL_FORMAT_RGBA12            = 0x02400061,

    /*! \brief BGRa8 */
    PEAK_PIXEL_FORMAT_BGRA8             = 0x02200017,

    /*! \brief BGRa10 */
    PEAK_PIXEL_FORMAT_BGRA10            = 0x0240004C,

    /*! \brief BGRa12 */
    PEAK_PIXEL_FORMAT_BGRA12            = 0x0240004E,

    /*! \brief BayerGR10 packed */
    PEAK_PIXEL_FORMAT_BAYER_GR10P       = 0x010A0056,

    /*! \brief BayerGR12 packed */
    PEAK_PIXEL_FORMAT_BAYER_GR12P       = 0x010C0057,

    /*! \brief BayerRG10 packed */
    PEAK_PIXEL_FORMAT_BAYER_RG10P       = 0x010A0058,

    /*! \brief BayerRG12 packed */
    PEAK_PIXEL_FORMAT_BAYER_RG12P       = 0x010C0059,

    /*! \brief BayerGB10 packed */
    PEAK_PIXEL_FORMAT_BAYER_GB10P       = 0x010A0054,

    /*! \brief BayerGB12 packed */
    PEAK_PIXEL_FORMAT_BAYER_GB12P       = 0x010C0055,

    /*! \brief BayerBG10 packed */
    PEAK_PIXEL_FORMAT_BAYER_BG10P       = 0x010A0052,

    /*! \brief BayerBG12 packed */
    PEAK_PIXEL_FORMAT_BAYER_BG12P       = 0x010C0053,

    /*! \brief Mono10 packed */
    PEAK_PIXEL_FORMAT_MONO10P           = 0x010A0046,

    /*! \brief Mono12 packed */
    PEAK_PIXEL_FORMAT_MONO12P           = 0x010C0047,

    /*! \brief RGB10 packed 32 */
    PEAK_PIXEL_FORMAT_RGB10P32          = 0x0220001D,

    /*! \brief BGR10 packed 32 */
    PEAK_PIXEL_FORMAT_BGR10P32          = 0x0220001E,

    /*! \brief BayerGR10 grouped 40
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_GR10G40_IDS = 0x40000003,

    /*! \brief BayerRG10 grouped 40
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_RG10G40_IDS = 0x40000001,

    /*! \brief BayerGB10 grouped 40
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_GB10G40_IDS = 0x40000002,

    /*! \brief BayerBG grouped 40
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_BG10G40_IDS = 0x40000004,

    /*! \brief BayerGR12 grouped 24
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_GR12G24_IDS = 0x40000013,

    /*! \brief BayerRG12 grouped 24
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_RG12G24_IDS = 0x40000011,

    /*! \brief BayerGB12 grouped 24
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_GB12G24_IDS = 0x40000012,

    /*! \brief BayerBG12 grouped 24
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_BAYER_BG12G24_IDS = 0x40000014,

    /*! \brief Mono10 grouped 40
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_MONO10G40_IDS     = 0x4000000f,

    /*! \brief Mono12 grouped 24
     *
     * \note This pixel format is preliminary and its name and value may change in a future product version.
     */
    PEAK_PIXEL_FORMAT_MONO12G24_IDS     = 0x4000001f

} peak_pixel_format;

#pragma pack(push, 1)
/*!
 * \ingroup pixelformat
 * \brief peak Pixel format info
 * 
 * The pixel format info delivers information on a specific pixel format.
 */
typedef struct
{
    /*! \brief Bits per pixel
     * 
     * The number of bits that one pixel occupies in memory.
     */
    uint32_t numBitsPerPixel;

    /*! \brief Significant bits per pixel
     * 
     * The number of bits that carry significant information on the pixel value.
     */
    uint32_t numSignificantBitsPerPixel;

    /*! \brief Number of channels
     *
     * The number of separate channels of a pixel.
     */
    uint32_t numChannels;

    /*! \brief Bits per channel
     *
     * The number of bits that one channel of the pixel occupies in memory.
     */
    uint32_t numBitsPerChannel;

    /*! \brief Significant bits per channel
     *
     * The number of bits that carry significant information on the pixel channel value.
     */
    uint32_t numSignificantBitsPerChannel;

    /*! \brief Maximum value per channel
     *
     * The maximum value for a pixel channel.
     */
    uint32_t maxValuePerChannel;

    uint8_t reserved[64];

} peak_pixel_format_info;
#pragma pack(pop)

/*!
 * \ingroup pixelformat
 * \brief Query the pixel format info
 * 
 * Provides the pixel format information on the specified pixel format.
 * 
 * \param[in] pixelFormat       The pixel format of interest.
 * \param[out] pixelFormatInfo  The pixel format info.
 * 
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelFormat is an invalid pixel format
 *                                          or \p pixelFormatInfo is an invalid pointer.
 *                                          Check #peak_pixel_format.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_PixelFormat_GetInfo(peak_pixel_format pixelFormat, peak_pixel_format_info* pixelFormatInfo);

/*!
 * \ingroup frame
 * \brief Release a frame
 *
 * Releases a frame that was previously received from #peak_Acquisition_WaitForFrame or from Xxx.
 *
 * The buffer that is bound to the specified frame is unlocked, so that ist can receive new image data.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] hFrame    Handle to the frame to release.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam and/or \p hFrame are invalid handles.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 *
 * \note The frame handle is no longer valid after the function has returned.
 * \note #peak_Acquisition_Start will be rejected as long as there are unreleased frame handles for frames that were
 *       received from #peak_Acquisition_WaitForFrame.
 */
PEAK_API_STATUS peak_Frame_Release(peak_camera_handle hCam, peak_frame_handle hFrame);

/*!
 * \ingroup frame_info
 * \brief peak Frame type
 *
 * The type and format of the contents of a received frame.
 */
typedef enum
{
    /*! \brief Invalid frame type
     *
     * Use this value for the initialization of variables of type peak_frame_type.
     */
    PEAK_FRAME_TYPE_INVALID = 0,

    /*! \brief Image data
     *
     * The frame contains image data, i.e. an ordered sequence of image pixels
     * beginning at the first pixel of the image.
     */
    PEAK_FRAME_TYPE_IMAGE   = 0x1001

} peak_frame_type;

/*!
 * \ingroup frame_info
 * \brief peak Frame info
 *
 * The frame info collects information on an acquired frame.
 */
#pragma pack(push, 1)
typedef struct
{
    /*! \brief The type and format of the contents of the frame */
    peak_frame_type type;

    /*! \brief The memory buffer that stores the frame contents */
    peak_buffer buffer;

    /*! \brief The frame id
     * 
     * The frame id is incremented with every acquired frame. It is reset to 0 on #peak_Acquisition_Start.
     * 
     * The frame id may jump forwards from one delivered frame to another. A jump in the frame id indicates a
     * \ref term_dropped_frame.
     */
    uint64_t frameID;

    /*! \brief The timestamp in nanoseconds
     *
     * The point in camera time at which the image was exposed.
     */
    uint64_t timestamp_ns;

    /*! \brief The ROI of the frame */
    peak_roi roi;

    /*! \brief The pixel format */
    peak_pixel_format pixelFormat;

    /*! \brief 'Complete' flag
     * 
     * \see \ref term_incomplete_frame
     */
    peak_bool isComplete;

    /*! \brief The number of bytes expected for a complete image.
     *
     * This value may be smaller than \p buffer.memorySize
     * \li if the buffer was announced via #peak_Acquisition_Buffer_Announce and is larger than required.
     */
    size_t bytesExpected;

    /*! \brief The number of bytes actually written to the buffer.
     *
     * This value may be smaller than \p buffer.memorySize
     * \li if the frame is incomplete (see \p isIncomplete), or
     * \li if the buffer was announced via #peak_Acquisition_Buffer_Announce and is larger than required.
     *     See \p bytesExpected.
     */
    size_t bytesWritten;

    /*! \brief The host side processing time
     * 
     * The time in milliseconds that the host side pixel processing took in total.
     */
    uint32_t processingTime_ms;

    uint8_t reserved[256];

} peak_frame_info;
#pragma pack(pop)

/*!
 * \ingroup frame_info
 * \brief Query the frame info
 * 
 * Provides the frame info data of the specified frame.
 * 
 * \param[in] hFrame        The frame handle.
 * \param[out] frameInfo    The frame info.
 * 
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p frameInfo is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_GetInfo(peak_frame_handle hFrame, peak_frame_info* frameInfo);

/*!
 * \ingroup frame_info
 * \brief Query the type of a frame
 *
 * Provides the type of the specified frame.
 *
 * \param[in] hFrame        The frame handle.
 * \param[out] frameType    The frame type.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p frameType is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_Type_Get(peak_frame_handle hFrame, peak_frame_type* frameType);

/*!
 * \ingroup frame_info
 * \brief Query the buffer of a frame
 *
 * Provides the memory buffer that stores the contents of the specified frame.
 *
 * \param[in] hFrame    The frame handle.
 * \param[out] buffer   The buffer.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p buffer is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_Buffer_Get(peak_frame_handle hFrame, peak_buffer* buffer);

/*!
 * \ingroup frame_info
 * \brief Query the frame id of a frame
 *
 * Provides the frame id of the specified frame.
 *
 * \param[in] hFrame    The frame handle.
 * \param[out] frameID  The frame id.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p frameID is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_ID_Get(peak_frame_handle hFrame, uint64_t* frameID);

/*!
 * \ingroup frame_info
 * \brief Query the timestamp of a frame
 *
 * Provides the timestamp of the specified frame.
 *
 * \param[in] hFrame        The frame handle.
 * \param[out] timestamp_ns The timestamp in nanoseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p timestamp is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_Timestamp_Get(peak_frame_handle hFrame, uint64_t* timestamp_ns);

/*!
 * \ingroup frame_info
 * \brief Query the size parameters of a frame
 *
 * Provides the image size parameters of the specified frame.
 *
 * \param[in] hFrame    The frame handle.
 * \param[out] roi      The ROI.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p roi is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_ROI_Get(peak_frame_handle hFrame, peak_roi* roi);

/*!
 * \ingroup frame_info
 * \brief Query the pixel format of a frame
 *
 * Provides the pixel format of the specified frame.
 *
 * \param[in] hFrame        The frame handle.
 * \param[out] pixelFormat  The pixel format.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelFormat is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_PixelFormat_Get(peak_frame_handle hFrame, peak_pixel_format* pixelFormat);

/*!
 * \ingroup frame_info
 * \brief Check whether the frame is complete
 *
 * Checks whether the frame was completely transmitted from the camera to the host.
 * \see \ref term_incomplete_frame
 *
 * This function implements the \ref principle_valid_values_organization_query principle.
 *
 * \param[in] hFrame The frame handle.
 *
 * \return #PEAK_TRUE   The frame is complete.
 * \return #PEAK_FALSE  The frame is incomplete or the query failed.
 */
PEAK_API_BOOL peak_Frame_IsComplete(peak_frame_handle hFrame);

/*!
 * \ingroup frame_info
 * \brief Query the bytes expected for a complete image
 *
 * Provides the bytes expected for a complete image.
 *
 * \param[in] hFrame         The frame handle.
 * \param[out] bytesExpected The bytes expected for a complete image.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p bytesExpected is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_BytesExpected_Get(peak_frame_handle hFrame, size_t* bytesExpected);

/*!
 * \ingroup frame_info
 * \brief Query the bytes written to the buffer of a frame
 *
 * Provides the bytes written to the buffer of a frame.
 *
 * \param[in] hFrame        The frame handle.
 * \param[out] bytesWritten The bytes written.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p bytesWritten is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_BytesWritten_Get(peak_frame_handle hFrame, size_t* bytesWritten);

/*!
 * \ingroup frame_info
 * \brief Query the processing time of a frame
 *
 * Provides the host side processing time of the specified frame.
 *
 * \param[in] hFrame                The frame handle.
 * \param[out] processingTime_ms    The processing time in milliseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p processingTime_ms is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Frame_ProcessingTime_Get(peak_frame_handle hFrame, uint32_t* processingTime_ms);

/*!
 * \ingroup camera_settings
 * \brief peak Parameter set
 *
 * A parameter set describes a specific camera configuration. \n
 * A camera may provide a number of pre-defined parameter sets that can be applied to set the camera to a
 * basic configuration for a certain use case. \n
 * A camera may also provide a number of user-definable parameter sets that can be used to store a
 * certain configuration in the cameras persistent memory and to restore/apply it from the cameras persistent memory.
 * A user-definable set can be applied only if it has been stored before. \n
 *
 * A parameter set may also be selectable to be automatically applied at the time of camera startup.
 *
 * The set of supported parameter sets depends on the camera model.
 */
typedef enum
{
    /*! \brief Invalid parameter set
     *
     * Use this value for the initialization of variables of type peak_parameter_set.
     */
    PEAK_PARAMETER_SET_INVALID          = 0,

    /*! \brief Default set
     *
     * The default set can be used to set the camera to its default configuration.
     */
    PEAK_PARAMETER_SET_DEFAULT          = 0x1001,

    /*! \brief Linescan set
     *
     * The linescan set can be used to set the camera to a basic configuration for the linescan use case.
     */
    PEAK_PARAMETER_SET_LINESCAN         = 0x1002,

    /*! \brief Long exposure set
     *
     * The long exposure set can be used to set the camera to a basic configuration for the long exposure use case.
     */
    PEAK_PARAMETER_SET_LONG_EXPOSURE    = 0x1003,

    /*! \brief User set 1
     *
     * The user set 1 can be used to store a certain camera configuration in the cameras persistent memory and to
     * restore it from the cameras persistent memory.
     */
    PEAK_PARAMETER_SET_USER_1           = 0x2001,

    /*! \brief User set 2
     *
     * The user set 2 can be used to store a certain camera configuration in the cameras persistent memory and to
     * restore it from the cameras persistent memory.
     */
    PEAK_PARAMETER_SET_USER_2           = 0x2002

} peak_parameter_set;

/*!
 * \ingroup camera_settings
 * \brief Query the parameter set access status
 *
 * Provides the current access status for the specified parameter set.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] parameterSet  The parameter set.
 *
 * \return #PEAK_ACCESS_READWRITE       The parameter set can be stored and applied.
 * \return #PEAK_ACCESS_READONLY        The parameter set can be applied only.
 * \return #PEAK_ACCESS_WRITEONLY       The parameter set can be stored only.
 * \return #PEAK_ACCESS_GFA_LOCK        The parameter set is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The parameter set is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The parameter set is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p parameterSet is an invalid parameter set. Check #peak_parameter_set.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_CameraSettings_ParameterSet_GetAccessStatus(peak_camera_handle hCam,
    peak_parameter_set parameterSet);

/*!
 * \ingroup camera_settings
 * \brief Get the list of currently usable parameter sets
 *
 * Queries the list of currently selectable parameter sets.
 *
 * The list of usable parameter sets may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] parameterSetList     Pointer to a user allocated array buffer to receive the parameter set list.
 *                                  If this parameter is NULL, \p parameterSetCount will contain the current
 *                                  number of parameter sets. \n
 *                                  The required size of \p parameterSetList in bytes is
 *                                  \p parameterSetCount x sizeof(peak_parameter_set).
 * \param[in,out] parameterSetCount \li \p parameterSetList equal NULL: \n
 *                                      out: minimal number of parameter sets \p parameterSetList must be
 *                                           large enough to hold \n
 *                                  \li \p parameterSetList unequal NULL: \n
 *                                      in: number of parameter sets \p parameterSetList can hold \n
 *                                      out: number of parameter sets filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p parameterSetList is not NULL and the value of \p *parameterSetCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The parameter set feature is not supported
 *                                          or the GFA write mode is enabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p parameterSetCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Please consider that the parameter set list might change between the size query call and the
 *       list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_CameraSettings_ParameterSet_GetList(peak_camera_handle hCam, peak_parameter_set* parameterSetList,
    size_t* parameterSetCount);

/*!
 * \ingroup camera_settings
 * \brief Store the current camera configuration in a user-definable parameter set
 *
 * Writes the current camera configuration to the specified parameter set.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] parameterSet  The parameter set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The parameter set is not storable.
 *                                          Check the access status via
 *                                          #peak_CameraSettings_ParameterSet_GetAccessStatus.
 *                                          Check the list of currently usable parameter sets via
 *                                          #peak_CameraSettings_ParameterSet_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p parameterSet is an invalid parameter set. Check #peak_parameter_set.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note In general only the user-definable parameter sets can be stored.
 */
PEAK_API_STATUS peak_CameraSettings_ParameterSet_Store(peak_camera_handle hCam, peak_parameter_set parameterSet);

/*!
 * \ingroup camera_settings
 * \brief Apply the specified parameter set
 *
 * Reads the specified parameter set from the cameras persistent storage and applies it.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] parameterSet The parameter set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The parameter set is not applicable.
 *                                          Check the access status via
 *                                          #peak_CameraSettings_ParameterSet_GetAccessStatus.
 *                                          Check the list of currently usable parameter sets via
 *                                          #peak_CameraSettings_ParameterSet_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p parameterSet is an invalid parameter set. Check #peak_parameter_set.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraSettings_ParameterSet_Apply(peak_camera_handle hCam, peak_parameter_set parameterSet);

/*!
 * \ingroup camera_settings
 * \brief Query the startup parameter set access status
 *
 * Provides the current access status for the startup parameter set.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The startup parameter set is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The startup parameter set is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The startup parameter set is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The startup parameter set is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The startup parameter set is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_CameraSettings_ParameterSet_Startup_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup camera_settings
 * \brief Set the startup parameter set
 *
 * Sets the specified parameter set to be automatically applied at the time of camera startup.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] parameterSet  The startup parameter set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The startup parameter set is not accessible
 *                                          or the specified parameter set is not applicable.
 *                                          Check the access status of the startup parameter set via
 *                                          #peak_CameraSettings_ParameterSet_Startup_GetAccessStatus.
 *                                          Check the access status of the specified parameter set via
 *                                          #peak_CameraSettings_ParameterSet_GetAccessStatus.
 *                                          Check the list of currently usable parameter sets via
 *                                          #peak_CameraSettings_ParameterSet_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p parameterSet is an invalid parameter set. Check #peak_parameter_set.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraSettings_ParameterSet_Startup_Set(peak_camera_handle hCam, peak_parameter_set parameterSet);

/*!
 * \ingroup camera_settings
 * \brief Get the startup parameter set
 *
 * Queries the current startup parameter set.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] parameterSet The startup parameter set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The startup parameter set is not available for read access.
 *                                          Check the access status of the startup parameter set via
 *                                          #peak_CameraSettings_ParameterSet_Startup_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p parameterSet is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraSettings_ParameterSet_Startup_Get(peak_camera_handle hCam, peak_parameter_set* parameterSet);

/*!
 * \ingroup camera_settings
 * \brief Query the disk file settings access status
 *
 * Provides the current access status for the disk file settings feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The camera settings can be stored to a disk file and applied from a disk file.
 * \return #PEAK_ACCESS_WRITEONLY       The camera settings can be stored to a disk file only.
 * \return #PEAK_ACCESS_GFA_LOCK        The camera settings can not be stored to a disk file because the GFA write
 *                                      access is enabled.
 * \return #PEAK_ACCESS_NONE            The camera settings can not be stored to a disk file nor can they be applied
 *                                      from a disk file.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The disk file settings feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_CameraSettings_DiskFile_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup camera_settings
 * \brief Store the current camera configuration to a disk file
 *
 * Writes the current camera configuration to the specified disk file.
 * If a path of an .ini file is given and the camera is either of type #PEAK_CAMERA_TYPE_UEYE_ETH 
 * or #PEAK_CAMERA_TYPE_UEYE_USB, the function will save a uEye parameterset file.
 *
 * \param[in] hCam  The camera handle.
 * \param[in] file  The file (path + name) as a zero-terminated string.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       Either the provided file format is not supported, 
 *                                          or the camera configuration is not storable.
 *                                          Check the disk file settings features access status via
 *                                          #peak_CameraSettings_DiskFile_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p file is an invalid pointer, it is not zero-terminated, or it is not
 *                                          a valid and accessible file.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraSettings_DiskFile_Store(peak_camera_handle hCam, const char* file);

/*!
 * \ingroup camera_settings
 * \brief Apply the camera configuration from the specified disk file
 *
 * Reads the camera configuration from the specified disk file and applies it.
 * If a path of an .ini file is given and the camera is either of type #PEAK_CAMERA_TYPE_UEYE_ETH 
 * or #PEAK_CAMERA_TYPE_UEYE_USB, the function will load a uEye parameterset file.
 *
 * \param[in] hCam  The camera handle.
 * \param[in] file  The file (path + name) as a zero-terminated string.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       Either the provided file format is not supported, 
 *                                          or the camera configuration is not storable.
 *                                          check the disk file settings features access status via
 *                                          #peak_CameraSettings_DiskFile_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p file is an invalid pointer, it is not zero-terminated, or it is not
 *                                          a valid and accessible file.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraSettings_DiskFile_Apply(peak_camera_handle hCam, const char* file);

/*!
 * \ingroup framerate
 * \brief Query the frame rate access status
 *
 * Provides the current access status for the frame rate control.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The frame rate control is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The frame rate control is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The frame rate control is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The frame rate control is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The frame rate control is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_FrameRate_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup framerate
 * \brief Get the current range of valid frame rate values
 *
 * Queries the current range of valid values for the frame rate control.
 *
 * The range of valid frame rate values may depend on the camera configuration and the camera status.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] minFrameRate_fps The minimum frame rate in frames per second.
 * \param[out] maxFrameRate_fps The maximum frame rate in frames per second.
 * \param[out] incFrameRate_fps The frame rate increment in frames per second.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The frame rate control is not accessible.
 *                                          Check the access status via #peak_FrameRate_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minFrameRate_fps, \p maxFrameRate_fps, and
 *                                          \p incFrameRate_fps is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_FrameRate_GetRange(peak_camera_handle hCam, double* minFrameRate_fps, double* maxFrameRate_fps,
    double* incFrameRate_fps);

/*!
 * \ingroup framerate
 * \brief Set the frame rate
 *
 * Writes the desired frame rate.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] frameRate_fps The frame rate to set in frames per second.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p frameRate_fps is out of range.
 *                                      Check the range of valid values via #peak_FrameRate_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The frame rate control is not available for write access.
 *                                      Check the access status via #peak_FrameRate_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_FrameRate_Set(peak_camera_handle hCam, double frameRate_fps);

/*!
 * \ingroup framerate
 * \brief Get the frame rate
 *
 * Reads the current frame rate.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] frameRate_fps    The frame rate in frames per second.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The frame rate control is not available for read access.
 *                                          Check the access status via #peak_FrameRate_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p frameRate_fps is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_FrameRate_Get(peak_camera_handle hCam, double* frameRate_fps);

/*!
 * \ingroup exposuretime
 * \brief Query the exposure time access status
 *
 * Provides the current access status for the exposure time control.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The exposure time control is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The exposure time control is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The exposure time control is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The exposure time control is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The exposure time control is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_ExposureTime_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup exposuretime
 * \brief Get the current range of valid exposure time values
 *
 * Queries the current range of valid values for the exposure time control.
 *
 * The range of valid exposure time values may depend on the camera configuration and the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] minExposureTime_us   The minimum exposure time in microseconds.
 * \param[out] maxExposureTime_us   The maximum exposure time in microseconds.
 * \param[out] incExposureTime_us   The exposure time increment in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The exposure time control is not accessible.
 *                                          Check the access status via #peak_ExposureTime_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minExposureTime_us, \p maxExposureTime_us, and
 *                                          \p incExposureTime_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ExposureTime_GetRange(peak_camera_handle hCam, double* minExposureTime_us,
    double* maxExposureTime_us, double* incExposureTime_us);

/*!
 * \ingroup exposuretime
 * \brief Set the exposure time
 *
 * Writes the desired exposure time.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] exposureTime_us   The exposure time to set in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p exposureTime_us is out of range.
 *                                          Check the range of valid values via #peak_ExposureTime_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED       The exposure time control is not available for write access.
 *                                          Check the access status via #peak_ExposureTime_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ExposureTime_Set(peak_camera_handle hCam, double exposureTime_us);

/*!
 * \ingroup exposuretime
 * \brief Get the exposure time
 *
 * Reads the current exposure time.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] exposureTime_us  The exposure time in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The exposure time control is not available for read access.
 *                                          Check the access status via #peak_ExposureTime_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p exposureTime_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ExposureTime_Get(peak_camera_handle hCam, double* exposureTime_us);

/*!
 * \ingroup pixelclock
 * \brief Query the pixel clock access status
 *
 * Provides the current access status for the pixel clock control.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The pixel clock control is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The pixel clock control is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The pixel clock control is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The pixel clock control is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The pixel clock control is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_PixelClock_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup pixelclock
 * \brief Check whether the valid values for the pixel clock feature are organized as a range
 *
 * Checks whether the valid values for the pixel clock feature are organized as a range or as a list.
 *
 * This function implements the \ref principle_valid_values_organization_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The valid values are organized as a range. Use #peak_PixelClock_GetRange.
 * \return #PEAK_FALSE  The valid values are organized as a list. Use #peak_PixelClock_GetList.
 */
PEAK_API_BOOL peak_PixelClock_HasRange(peak_camera_handle hCam);

/*!
 * \ingroup pixelclock
 * \brief Get the current range of valid pixel clock values
 *
 * Queries the current range of valid values for the pixel clock control.
 *
 * The range of valid pixel clock values may depend on the camera configuration and the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] minPixelClock_MHz    The minimum pixel clock in megahertz.
 * \param[out] maxPixelClock_MHz    The maximum pixel clock in megahertz.
 * \param[out] incPixelClock_MHz    The pixel clock increment in megahertz.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NO_DATA             The valid values for the pixelclock feature are organized as list 
 *                                          rather than as a range.\n
 *                                          Use #peak_PixelClock_GetList to query the valid pixelclock values.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel clock control is not accessible.
 *                                          Check the access status via #peak_PixelClock_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minPixelClock_MHz, \p maxPixelClock_MHz, and
 *                                          \p incPixelClock_MHz is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_PixelClock_GetRange(peak_camera_handle hCam, double* minPixelClock_MHz, double* maxPixelClock_MHz,
    double* incPixelClock_MHz);

/*!
 * \ingroup pixelclock
 * \brief Get the list of currently selectable pixel clock values
 *
 * Queries the list of currently selectable pixel clock values.
 *
 * The list of selectable pixel clock values may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] pixelClockList       Pointer to a user allocated array buffer to receive the pixel clock list.
 *                                  If this parameter is NULL, \p pixelClockCount will contain the current
 *                                  number of pixel formats. \n
 *                                  The required size of \p pixelClockList in bytes is
 *                                  \p pixelClockCount x sizeof(uint32_t).
 * \param[in,out] pixelClockCount   \li \p pixelClockList equal NULL: \n
 *                                      out: minimal number of pixel clocks \p pixelClockList must be
 *                                           large enough to hold \n
 *                                  \li \p pixelClockList unequal NULL: \n
 *                                      in: number of pixel clocks \p pixelClockList can hold \n
 *                                      out: number of pixel clocks filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NO_DATA             The valid values for the pixel clock feature are organized as range 
 *                                          rather than as a list.\n
 *                                          Use #peak_PixelClock_GetRange to query the valid pixel clock values.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p pixelClockList is not NULL and the value of \p *pixelClockCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel clock feature is not accessible.
 *                                          Check the access status via #peak_PixelClock_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelClockCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the pixel clock list might change between the size query call and the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_PixelClock_GetList(peak_camera_handle hCam, double* pixelClockList, size_t* pixelClockCount);

/*!
 * \ingroup pixelclock
 * \brief Set the pixel clock
 *
 * Writes the desired pixel clock.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] pixelClock_MHz    The pixel clock to set in megahertz.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_VALUE_ADJUSTED      Value was automatically adjusted.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p pixelClock_MHz is out of range.
 *                                          Check the range of valid values
 *                                          via #peak_PixelClock_GetRange or #peak_PixelClock_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel clock control is not available for write access.
 *                                          Check the access status via #peak_PixelClock_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_PixelClock_Set(peak_camera_handle hCam, double pixelClock_MHz);

/*!
 * \ingroup pixelclock
 * \brief Get the pixel clock
 *
 * Reads the current pixel clock.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] pixelClock_MHz   The pixel clock in megahertz.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel clock control is not available for read access.
 *                                          Check the access status via #peak_PixelClock_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelClock_MHz is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_PixelClock_Get(peak_camera_handle hCam, double* pixelClock_MHz);

/*!
 * \ingroup io_channel
 * \brief peak IO channel
 *
 * The io channel specifies the channel at which a certain signal or event is received or transmitted.
 * It is used for several features like trigger and flash.
 *
 * Not all channels are applicable for all features.
 */
typedef enum
{
    /*! \brief Invalid io channel
     *
     * Use this value for the initialization of variables of type peak_io_channel;.
     */
    PEAK_IO_CHANNEL_INVALID         = 0,

    /*! \brief None
     *
     * No channel configured.
     */
    PEAK_IO_CHANNEL_NONE            = 0x0001,

    /*! \brief Software
     *
     * The signal or event is initiated by a software function.
     */
    PEAK_IO_CHANNEL_SOFTWARE        = 0x1101,

    /*! \brief Trigger input pin
     *
     * The signal or event is initiated by an electrical signal at the cameras trigger connector.
     */
    PEAK_IO_CHANNEL_TRIGGER_INPUT   = 0x2101,

    /*! \brief Flash output pin
     *
     * The signal or event is initiated by an electrical signal at the cameras flash connector.
     */
    PEAK_IO_CHANNEL_FLASH_OUTPUT    = 0x2201,

    /*! \brief GPIO 1 pin
     *
     * The signal or event is initiated by an electrical signal at the cameras GPIO 1 connector.
     */
    PEAK_IO_CHANNEL_GPIO_1          = 0x6301,

    /*! \brief GPIO 2 pin
     *
     * The signal or event is initiated by an electrical signal at the cameras GPIO 2 connector.
     */
    PEAK_IO_CHANNEL_GPIO_2          = 0x6302

} peak_io_channel;

/*!
 * \ingroup io_channel
 * \brief Query the io channel access status
 *
 * Provides the current access status for the specified io channel.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_ACCESS_READWRITE       The io channel is supported
 *                                      and currently available for use by trigger/flash.
 * \return #PEAK_ACCESS_READONLY        The io channel is supported
 *                                      but currently used in an enabled trigger/flash configuration.
 * \return #PEAK_ACCESS_GFA_LOCK        The io channel is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The io channel is not supported.
 *                                      Check the list of supported io channels via #peak_IOChannel_GetList.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_ACCESS_DENIED       The io channel feature is not supported.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid io channel. Check #peak_io_channel.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_IOChannel_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Get the list of supported io channels
 *
 * Queries the list of supported io channels.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] ioChannelList        Pointer to a user allocated array buffer to receive the io channel list.
 *                                  If this parameter is NULL, \p ioChannelCount will contain the current
 *                                  number of io channels. \n
 *                                  The required size of \p ioChannelList in bytes is
 *                                  \p ioChannelCount x sizeof(#peak_io_channel).
 * \param[in,out] ioChannelCount    \li \p ioChannelList equal NULL: \n
 *                                      out: minimal number of io channels \p ioChannelList must be
 *                                           large enough to hold \n
 *                                  \li \p ioChannelList unequal NULL: \n
 *                                      in: number of io channels \p ioChannelList can hold \n
 *                                      out: number of io channels filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p ioChannelList is not NULL and the value of \p *ioChannelCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The io channel feature is not supported
 *                                          or the GFA write access is enabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p ioChannelCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IOChannel_GetList(peak_camera_handle hCam, peak_io_channel* ioChannelList, size_t* ioChannelCount);

/*!
 * \ingroup io_channel
 * \brief Query the io channel level property access status
 *
 * Provides the current access status for the level property for the specified io channel.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_ACCESS_READWRITE       The level property is readable and writeable for the specified io channel.
 * \return #PEAK_ACCESS_READONLY        The level property is readable only for the specified io channel.
 * \return #PEAK_ACCESS_GFA_LOCK        The level property is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The level property is not accessible for the specified io channel.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The level property is not supported for the specified io channel.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The specified io channel is not accessible.
 *                                      Check the access status of the io channel via #peak_IOChannel_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid io channel. Check #peak_io_channel.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_IOChannel_Level_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Get the level of the io channel
 *
 * Queries whether the io channels level is currently high or low.
 *
 * This function implements the \ref principle_boolean_status_queries principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_TRUE   The io channels level is currently high.
 * \return #PEAK_FALSE  The io channels level is currently low or the query failed.
 */
PEAK_API_BOOL peak_IOChannel_Level_IsHigh(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Query the io channel inverter property access status
 *
 * Provides the current access status for the inverter property for the specified io channel.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_ACCESS_READWRITE       The inverter property is readable and writeable for the specified io channel.
 * \return #PEAK_ACCESS_READONLY        The inverter property is readable only for the specified io channel.
 * \return #PEAK_ACCESS_GFA_LOCK        The inverter property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The inverter property is not accessible for the specified io channel.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The inverter property is not supported for the specified io channel.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The specified io channel is not accessible.
 *                                      Check the access status of the io channel via #peak_IOChannel_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid channel.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_IOChannel_Inverter_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Enable/Disable the io channel inverter property
 *
 * Sets the io channel inverter property to enabled or disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The io channel inverter property is not accessible for write.
 *                                          Check the access status via #peak_IOChannel_Inverter_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IOChannel_Inverter_Enable(peak_camera_handle hCam, peak_io_channel ioChannel, peak_bool enabled);

/*!
 * \ingroup io_channel
 * \brief Get the enabled status of the io channel inverter property
 *
 * Queries whether the io channel inverter property is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_TRUE   The io channel inverter property is currently enabled.
 * \return #PEAK_FALSE  The io channel inverter property is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_IOChannel_Inverter_IsEnabled(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Query the io channel noise filter property access status
 *
 * Provides the current access status for the noise filter property for the specified io channel.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_ACCESS_READWRITE       The noise filter property is readable and writeable for the
 *                                      specified io channel.
 * \return #PEAK_ACCESS_READONLY        The noise filter property is readable only for the specified io channel.
 * \return #PEAK_ACCESS_GFA_LOCK        The noise filter property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The noise filter property is not accessible for the specified io channel.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The noise filter property is not supported for the specified io channel.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The specified io channel is not accessible.
 *                                      Check the access status of the io channel via #peak_IOChannel_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid channel.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_IOChannel_NoiseFilter_GetAccessStatus(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Enable/Disable the io channel noise filter property
 *
 * Sets the io channel noise filter property to enabled or disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The io channel noise filter property is not accessible for write.
 *                                          Check the access status via #peak_IOChannel_NoiseFilter_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IOChannel_NoiseFilter_Enable(peak_camera_handle hCam, peak_io_channel ioChannel,
    peak_bool enabled);

/*!
 * \ingroup io_channel
 * \brief Get the enabled status of the io channel noise filter property
 *
 * Queries whether the io channel noise filter property is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] ioChannel The io channel.
 *
 * \return #PEAK_TRUE   The io channel noise filter property is currently enabled.
 * \return #PEAK_FALSE  The io channel noise filter property is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_IOChannel_NoiseFilter_IsEnabled(peak_camera_handle hCam, peak_io_channel ioChannel);

/*!
 * \ingroup io_channel
 * \brief Get the current range of valid io channel noise filter duration values
 *
 * Queries the current range of valid values for the io channel noise filter duration for the specified io channel.
 *
 * The range of valid io channel noise filter duration delay values may depend on the camera configuration and
 * the camera status.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] ioChannel                     The io channel.
 * \param[out] minNoiseFilterDuration_us    The minimum noise filter duration value in microseconds.
 * \param[out] maxNoiseFilterDuration_us    The maximum noise filter duration value in microseconds.
 * \param[out] incNoiseFilterDuration_us    The noise filter duration value increment in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The noise filter duration is not accessible.
 *                                          Check the access status via #peak_IOChannel_NoiseFilter_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minNoiseFilterDuration_us, \p maxNoiseFilterDuration_us,
 *                                          and \p incNoiseFilterDuration_us is an invalid pointer
 *                                          or \p ioChannel is an invalid channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IOChannel_NoiseFilter_Duration_GetRange(peak_camera_handle hCam, peak_io_channel ioChannel,
    double* minNoiseFilterDuration_us, double* maxNoiseFilterDuration_us, double* incNoiseFilterDuration_us);

/*!
 * \ingroup io_channel
 * \brief Set the io channel noise filter duration
 *
 * Writes the desired io channel noise filter duration for the specified io channel.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] ioChannel                 The io channel.
 * \param[out] noiseFilterDuration_us   The noise filter duration to set in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The noise filter duration is not accessible for write.
 *                                          Check the access status via #peak_IOChannel_NoiseFilter_GetAccessStatus.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p noiseFilterDuration_us is out of range.
 *                                          Check the range of valid values via
 *                                          #peak_IOChannel_NoiseFilter_Duration_GetRange.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p ioChannel is an invalid channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IOChannel_NoiseFilter_Duration_Set(peak_camera_handle hCam, peak_io_channel ioChannel,
    double noiseFilterDuration_us);

/*!
 * \ingroup io_channel
 * \brief Get the io channel noise filter duration
 *
 * Reads the current io channel noise filter duration for the specified io channel.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] ioChannel                 The io channel.
 * \param[out] noiseFilterDuration_us   The noise filter duration in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The noise filter duration is not accessible for read.
 *                                          Check the access status via #peak_IOChannel_NoiseFilter_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p noiseFilterDuration_us is an invalid pointer
 *                                          or \p ioChannel is an invalid channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IOChannel_NoiseFilter_Duration_Get(peak_camera_handle hCam, peak_io_channel ioChannel,
    double* noiseFilterDuration_us);

/*!
 * \ingroup trigger
 * \brief peak Trigger target
 *
 * The trigger target specifies which operation a trigger signal initiates or defines.
 */
typedef enum
{
    /*! \brief Invalid trigger target
     *
     * Use this value for the initialization of variables of type peak_trigger_target.
     */
    PEAK_TRIGGER_TARGET_INVALID                     = 0,

    /*! \brief Frame start
     *
     * A trigger signal will initiate the start of a frame acquisition.
     */
    PEAK_TRIGGER_TARGET_FRAME_START                 = 0x1001,

    /*! \brief Level controlled exposure
     *
     * The trigger signal will define the exposure duration.
     */
    PEAK_TRIGGER_TARGET_LEVEL_CONTROLLED_EXPOSURE   = 0x2001

} peak_trigger_target;

/*!
 * \ingroup trigger
 * \brief peak Trigger mode
 *
 * A trigger mode defines a combination of a trigger target and an io channel.
 * 
 * In order to set up a trigger the desired basic configuration is specified by this struct. \n
 * Then the mode is passed to #peak_Trigger_Mode_Set to set the desired trigger mode. \n
 * Any further configuration for the trigger feature is then done via the dedicated functions.
 * 
 * \note The library defines several trigger mode presets which can be used to initialize a
 *       #peak_trigger_mode. \n
 *       See
 *       \li #PEAK_TRIGGER_MODE_HARDWARE_TRIGGER
 *       \li #PEAK_TRIGGER_MODE_SOFTWARE_TRIGGER
 *
 * \note The default trigger mode is #PEAK_TRIGGER_MODE_HARDWARE_TRIGGER,
 *       i.e. frame start is triggered by the trigger input channel. \n
 *       The default trigger mode is configured after the camera has been opened and as long as no other mode is
 *       explicitly set via #peak_Trigger_Mode_Set.
 */
typedef struct
{
    /*! \brief The trigger target
     * 
     * The trigger target defines the operation that a trigger signal on the IO channel initiates.
     */
    peak_trigger_target triggerTarget;

    /*! \brief The iO channel
     * 
     * The io channel defines the signal that initiates the operation that the trigger target defines.
     */
    peak_io_channel ioChannel;

} peak_trigger_mode;

/*!
 * \ingroup trigger
 * \brief peak Trigger mode preset: Frame start by trigger input
 *
 * Initialize a #peak_trigger_mode with this preset and pass it to #peak_Trigger_Mode_Set to configure a
 * hardware trigger for frame start. \n
 * See the following example code.
 *
 * \code
 * const peak_trigger_mode triggerMode = PEAK_TRIGGER_MODE_HARDWARE_TRIGGER;
 * peak_status status = peak_Trigger_Mode_Set(cameraHandle, triggerMode);
 * \endcode
 *
 * \note This is the default trigger mode which is configured until #peak_Trigger_Mode_Set has been called.
 */
#define PEAK_TRIGGER_MODE_HARDWARE_TRIGGER { PEAK_TRIGGER_TARGET_FRAME_START, PEAK_IO_CHANNEL_TRIGGER_INPUT }

/*!
 * \ingroup trigger
 * \brief peak Trigger mode preset: Frame start by software trigger
 * 
 * Initialize a #peak_trigger_mode with this preset and pass it to #peak_Trigger_Mode_Set to configure a
 * software trigger for frame start. \n
 * See the following example code.
 *
 * \code
 * const peak_trigger_mode triggerMode = PEAK_TRIGGER_MODE_SOFTWARE_TRIGGER;
 * peak_status status = peak_Trigger_Mode_Set(cameraHandle, triggerMode);
 * \endcode
 */
#define PEAK_TRIGGER_MODE_SOFTWARE_TRIGGER { PEAK_TRIGGER_TARGET_FRAME_START, PEAK_IO_CHANNEL_SOFTWARE }

/*!
 * \ingroup trigger
 * \brief Query the trigger feature access status
 *
 * Provides the current access status for the trigger feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The trigger feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The trigger feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The trigger feature is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The trigger feature is not accessible.
 *                                      Check for a running acquisition.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The trigger feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Trigger_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup trigger
 * \brief Enable/Disable the trigger
 *
 * Sets the trigger to enabled or disabled.
 *
 * A trigger can be enabled or disabled if there is no running acquisition only.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The trigger feature is not accessible for write.
 *                                      Check the access status of the trigger feature via
 *                                      #peak_Trigger_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup trigger
 * \brief Get the enabled status of the trigger
 *
 * Queries whether the trigger is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The trigger is currently enabled.
 * \return #PEAK_FALSE  The trigger is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_Trigger_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup trigger
 * \brief Check whether the trigger is executable or not
 *
 * Queries whether the trigger is executable or not.
 *
 * If a trigger is executable it can be issued via #peak_Trigger_Execute.
 *
 * This function implements the \ref principle_boolean_status_queries principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The trigger is executable.
 * \return #PEAK_FALSE  The trigger is not executable or the query failed.
 */
PEAK_API_BOOL peak_Trigger_IsExecutable(peak_camera_handle hCam);

/*!
 * \ingroup trigger
 * \brief Execute the trigger
 *
 * Executes the trigger.
 *
 * If a trigger is executed the configured trigger target is issued. \n
 * For a hardware trigger this means that an appropriate signal on the configured io channel is simulated.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The trigger is not enabled or it is not executable
 *                                      or the trigger feature is not accessible.
 *                                      Check for the trigger to be enabled via #peak_Trigger_IsEnabled.
 *                                      Check for the trigger to be executable via #peak_Trigger_IsExecutable.
 *                                      Check the access status of the trigger feature via
 *                                      #peak_Trigger_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Execute(peak_camera_handle hCam);

/*!
 * \ingroup trigger
 * \brief Query the trigger mode access status
 *
 * Provides the access status for the given trigger mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] triggerMode   The trigger mode.
 *
 * \return #PEAK_ACCESS_READWRITE       The trigger mode is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The trigger mode is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The trigger mode is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The trigger mode is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The trigger mode is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The trigger feature is not accessible.
 *                                      Check the access status of the trigger feature via
 *                                      #peak_Trigger_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p triggerMode is an invalid trigger mode.
 *                                      Check #peak_trigger_target and #peak_io_channel.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Trigger_Mode_GetAccessStatus(peak_camera_handle hCam, peak_trigger_mode triggerMode);

/*!
 * \ingroup trigger
 * \brief Set the trigger mode
 *
 * Changes the trigger mode.
 *
 * The properties of the trigger will be reset to the following default values:
 * \li The trigger edge will be set to #PEAK_TRIGGER_EDGE_RISING.
 * \li The trigger delay will be set to 0.
 * \li The trigger divider will be set to 1.
 * \li The trigger burst size will be set to 1.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] triggerMode   The trigger mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger mode is not available for write access
 *                                          or the io channel is not available for write access.
 *                                          Check the access status of the trigger mode via
 *                                          #peak_Trigger_Mode_GetAccessStatus.
 *                                          Check the access status of the io channel via
 *                                          #peak_IOChannel_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerMode is an invalid trigger mode.
 *                                          Check #peak_trigger_target and #peak_io_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Mode_Set(peak_camera_handle hCam, peak_trigger_mode triggerMode);

/*!
 * \ingroup trigger
 * \brief Get the trigger mode
 *
 * Reads the current trigger mode.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] triggerMode  The trigger mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger mode is not available for read access.
 *                                          Check the access status of the trigger mode via
 *                                          #peak_Trigger_Mode_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Mode_Get(peak_camera_handle hCam, peak_trigger_mode* triggerMode);

/*!
 * \ingroup trigger_edge
 * \brief peak Trigger edge
 *
 * The trigger edge specifies which edge of an electrical signal initiates a trigger.
 *
 * \note The trigger edge is not effective for software trigger.
 */
typedef enum
{
    /*! \brief Invalid trigger edge
     *
     * Use this value for the initialization of variables of type peak_trigger_edge.
     */
    PEAK_TRIGGER_EDGE_INVALID   = 0,

    /*! \brief Rising edge
     *
     * A trigger is raised by the electrical signal changing from low level to high level.
     */
    PEAK_TRIGGER_EDGE_RISING    = 0x0001,

    /*! \brief Falling edge
     *
     * A trigger is raised by the electrical signal changing from high level to low level.
     */
    PEAK_TRIGGER_EDGE_FALLING   = 0x0002,

    /*! \brief Any edge
     *
     * A trigger is raised by the electrical signal changing its level in any direction.
     */
    PEAK_TRIGGER_EDGE_ANY       = 0x0003

} peak_trigger_edge;

/*!
 * \ingroup trigger_edge
 * \brief Query the trigger edge property access status
 *
 * Provides the current access status for the trigger edge property for the configured trigger mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The trigger edge property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The trigger edge property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The trigger edge property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The trigger edge property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The trigger edge property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The trigger feature is not accessible.
 *                                  Check the access status of the trigger feature via #peak_Trigger_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Trigger_Edge_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup trigger_edge
 * \brief Get the list of currently selectable trigger edges
 *
 * Queries the list of currently selectable trigger edges for the configured trigger mode.
 *
 * The list of selectable trigger edges may depend on the trigger mode, the camera configuration, and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] triggerEdgeList      Pointer to a user allocated array buffer to receive the trigger edge list.
 *                                  If this parameter is NULL, \p triggerEdgeCount will contain the current
 *                                  number of trigger edges. \n
 *                                  The required size of \p triggerEdgeList in bytes is
 *                                  \p triggerEdgeCount x sizeof(#peak_trigger_edge).
 * \param[in,out] triggerEdgeCount  \li \p triggerEdgeList equal NULL: \n
 *                                      out: minimal number of pixel formats \p triggerEdgeList must be
 *                                           large enough to hold \n
 *                                  \li \p triggerEdgeList unequal NULL: \n
 *                                      in: number of trigger edges \p triggerEdgeList can hold \n
 *                                      out: number of trigger edges filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p triggerEdgeList is not NULL and the value of \p *triggerEdgeCount
 *                                          is too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger edge property is not accessible.
 *                                          Check the access status of the trigger edge via
 *                                          #peak_Trigger_Edge_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerEdgeCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the trigger edge list might change between the size query call and the list query call. \n
 *       This may be the case if the trigger mode, the camera configuration, or the camera status have changed in the
 *       time between the two function calls.
 */
PEAK_API_STATUS peak_Trigger_Edge_GetList(peak_camera_handle hCam, peak_trigger_edge* triggerEdgeList,
    size_t* triggerEdgeCount);

/*!
 * \ingroup trigger_edge
 * \brief Set the trigger edge
 *
 * Writes the desired trigger edge.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] triggerEdge   The trigger edge to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger edge property is not available for write access.
 *                                          Check the access status of the trigger edge via
 *                                          #peak_Trigger_Edge_GetAccessStatus.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p triggerEdge is out of range.
 *                                          Check the range of valid values via #peak_Trigger_Edge_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerEdge is an invalid trigger edge. Check #peak_trigger_edge.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Edge_Set(peak_camera_handle hCam, peak_trigger_edge triggerEdge);

/*!
 * \ingroup trigger_edge
 * \brief Get the trigger edge
 *
 * Reads the current trigger edge.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] triggerEdge  The trigger edge.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger edge property is not available for read access.
 *                                          Check the access status of the trigger edge via
 *                                          #peak_Trigger_Edge_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerEdge is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Edge_Get(peak_camera_handle hCam, peak_trigger_edge* triggerEdge);

/*!
 * \ingroup trigger_delay
 * \brief Query the trigger delay property access status
 *
 * Provides the current access status for the trigger delay property for the configured trigger mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The trigger delay property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The trigger delay property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The trigger delay property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The trigger delay property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The trigger delay property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The trigger feature is not accessible.
 *                                  Check the access status of the trigger feature via #peak_Trigger_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Trigger_Delay_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup trigger_delay
 * \brief Get the current range of valid trigger delay values
 *
 * Queries the current range of valid values for the trigger delay for the configured trigger mode.
 *
 * The range of valid trigger delay values may depend on the trigger mode, the camera configuration, and
 * the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] minTriggerDelay_us   The minimum trigger delay value.
 * \param[out] maxTriggerDelay_us   The maximum trigger delay value.
 * \param[out] incTriggerDelay_us   The trigger delay value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger delay property is not accessible.
 *                                          Check the access status of the trigger delay via
 *                                          #peak_Trigger_Delay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minTriggerDelay_us, \p maxTriggerDelay_us, and
 *                                          \p incTriggerDelay_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Delay_GetRange(peak_camera_handle hCam, double* minTriggerDelay_us,
    double* maxTriggerDelay_us, double* incTriggerDelay_us);

/*!
 * \ingroup trigger_delay
 * \brief Set the trigger delay
 *
 * Writes the desired trigger delay.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] triggerDelay_us   The trigger delay in microseconds to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p triggerDelay_us is out of range.
 *                                      Check the range of valid values via #peak_Trigger_Delay_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The trigger delay property is not available for write access.
 *                                      Check the access status of the trigger delay via
 *                                      #peak_Trigger_Delay_GetAccessStatus.
 *                                      Check the availability of the trigger feature via #peak_Trigger_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Delay_Set(peak_camera_handle hCam, double triggerDelay_us);

/*!
 * \ingroup trigger_delay
 * \brief Get the trigger delay
 *
 * Reads the current trigger delay.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] triggerDelay_us  The trigger delay in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger delay property is not available for read access.
 *                                          Check the access status of the trigger delay via
 *                                          #peak_Trigger_Delay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerDelay_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Delay_Get(peak_camera_handle hCam, double* triggerDelay_us);

/*!
 * \ingroup trigger_divider
 * \brief Query the trigger divider property access status
 *
 * Provides the current access status for the trigger divider property for the configured trigger mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The trigger divider property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The trigger divider property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The trigger divider property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The trigger divider property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The trigger divider property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The trigger feature is not accessible.
 *                                  Check the access status of the trigger feature via #peak_Trigger_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Trigger_Divider_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup trigger_divider
 * \brief Get the current range of valid trigger divider values
 *
 * Queries the current range of valid values for the trigger divider for the configured trigger mode.
 *
 * The range of valid trigger divider values may depend on the trigger mode, the camera configuration, and
 * the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] minTriggerDivider    The minimum trigger divider value.
 * \param[out] maxTriggerDivider    The maximum trigger divider value.
 * \param[out] incTriggerDivider    The trigger divider value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger divider property is not accessible.
 *                                          Check the access status of the trigger divider via
 *                                          #peak_Trigger_Divider_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minTriggerDivider, \p maxTriggerDivider, and
 *                                          \p incTriggerDivider is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Divider_GetRange(peak_camera_handle hCam, uint32_t* minTriggerDivider,
    uint32_t* maxTriggerDivider, uint32_t* incTriggerDivider);

/*!
 * \ingroup trigger_divider
 * \brief Set the trigger divider
 *
 * Writes the desired trigger divider.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] triggerDivider    The trigger divider.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p triggerDivider is out of range.
 *                                      Check the range of valid values via #peak_Trigger_Divider_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The trigger divider property is not available for write access.
 *                                      Check the access status of the trigger divider via
 *                                      #peak_Trigger_Divider_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Divider_Set(peak_camera_handle hCam, uint32_t triggerDivider);

/*!
 * \ingroup trigger_divider
 * \brief Get the trigger divider
 *
 * Reads the current trigger divider.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] triggerDivider   The trigger divider.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger divider property is not available for read access.
 *                                          Check the access status of the trigger divider via
 *                                          #peak_Trigger_Divider_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerDivider is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Divider_Get(peak_camera_handle hCam, uint32_t* triggerDivider);

/*!
 * \ingroup trigger_burst
 * \brief Query the trigger burst property access status
 *
 * Provides the current access status for the trigger burst property for the configured trigger mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The trigger burst property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The trigger burst property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The trigger burst property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The trigger burst property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The trigger burst property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The trigger feature is not accessible.
 *                                  Check the access status of the trigger feature via #peak_Trigger_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Trigger_Burst_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup trigger_burst
 * \brief Get the current range of valid trigger burst values
 *
 * Queries the current range of valid values for the trigger burst for the configured trigger mode.
 *
 * The range of valid trigger burst values may depend on the trigger mode, the camera configuration, and
 * the camera status.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] minTriggerBurst  The minimum trigger burst value.
 * \param[out] maxTriggerBurst  The maximum trigger burst value.
 * \param[out] incTriggerBurst  The trigger burst value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger burst property is not accessible.
 *                                          Check the access status of the trigger burst via
 *                                          #peak_Trigger_Burst_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minTriggerBurst, \p maxTriggerBurst, and
 *                                          \p incTriggerBurst is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Burst_GetRange(peak_camera_handle hCam, uint32_t* minTriggerBurst,
    uint32_t* maxTriggerBurst, uint32_t* incTriggerBurst);

/*!
 * \ingroup trigger_burst
 * \brief Set the trigger burst
 *
 * Writes the desired trigger burst.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] triggerBurst  The trigger burst.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p triggerBurst is out of range.
 *                                      Check the range of valid values via #peak_Trigger_Burst_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The trigger burst property is not available for write access.
 *                                      Check the access status of the trigger burst via
 *                                      #peak_Trigger_Burst_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Burst_Set(peak_camera_handle hCam, uint32_t triggerBurst);

/*!
 * \ingroup trigger_burst
 * \brief Get the trigger burst
 *
 * Reads the current trigger burst.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] triggerBurst The trigger burst.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The trigger burst property is not available for read access.
 *                                          Check the access status of the trigger burst via
 *                                          #peak_Trigger_Burst_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p triggerBurst is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Trigger_Burst_Get(peak_camera_handle hCam, uint32_t* triggerBurst);

/*!
 * \ingroup flash
 * \brief peak Flash reference
 *
 * The flash reference specifies which operation is represented by the flash signal.
 */
typedef enum
{
    /*! \brief Invalid flash reference
     *
     * Use this value for the initialization of variables of type peak_flash_reference.
     */
    PEAK_FLASH_REFERENCE_INVALID                = 0,

    /*! \brief Exposure active
     *
     * The flash is active while the exposure is active.
     */
    PEAK_FLASH_REFERENCE_EXPOSURE_ACTIVE        = 0x1001,

    /*! \brief Global start window
     *
     * The flash is active for the length of the global start window.
     */
    PEAK_FLASH_REFERENCE_GLOBAL_START_WINDOW    = 0x1002,

    /*! \brief Acquisition active
     *
     * The flash is active while the acquisition is active.
     */
    PEAK_FLASH_REFERENCE_ACQUISITION_ACTIVE     = 0x2001

} peak_flash_reference;

/*!
 * \ingroup flash
 * \brief peak Flash mode
 *
 * A flash mode defines a combination of a flash reference and an io channel.
 *
 * In order to set up a flash the desired basic configuration is specified by this struct. \n
 * Then the mode is passed to #peak_Flash_Mode_Set to set the desired flash mode. \n
 * Any further configuration for the flash feature is then done via the dedicated functions.
 *
 * \note The library defines several flash mode presets which can be used to initialize a
 *       #peak_flash_mode. \n
 *       See
 *       \li #PEAK_FLASH_MODE_EXPOSURE_ACTIVE
 *       \li #PEAK_FLASH_MODE_ACQUISITION_ACTIVE
 *       \li #PEAK_FLASH_MODE_GLOBAL_START_WINDOW
 *
 * \note The default flash mode is #PEAK_FLASH_MODE_EXPOSURE_ACTIVE,
 *       i.e. the exposure time is reflected by the signal on the flash output channel. \n
 *       The default flash mode is configured after the camera has been opened and as long as no other mode is
 *       explicitly set via #peak_Flash_Mode_Set.
 */
typedef struct
{
    /*! \brief Flash reference
     *
     * The flash reference defines the operation that a flash signal represents.
     */
    peak_flash_reference flashReference;

    /*! \brief IO channel
     *
     * The io channel defines the signal that drives the signal that the flash reference defines.
     */
    peak_io_channel ioChannel;

} peak_flash_mode;

/*!
 * \ingroup flash
 * \brief peak Flash mode preset: Exposure active on flash output
 *
 * Initialize a #peak_flash_mode with this preset and pass it to #peak_Flash_Mode_Set to configure a flash signal for
 * the exposure time. \n
 * See the following example code.
 *
 * \code
 * const peak_flash_mode flashMode = PEAK_FLASH_MODE_EXPOSURE_ACTIVE;
 * peak_status status = peak_Flash_Mode_Set(cameraHandle, flashMode);
 * \endcode
 *
 * \note This is the default flash mode which is configured until #peak_Flash_Mode_Set has been called.
 */
#define PEAK_FLASH_MODE_EXPOSURE_ACTIVE { PEAK_FLASH_REFERENCE_EXPOSURE_ACTIVE, PEAK_IO_CHANNEL_FLASH_OUTPUT }

 /*!
  * \ingroup flash
  * \brief peak Flash mode preset: Acquisition active on flash output
  *
  * Initialize a #peak_flash_mode with this preset and pass it to #peak_Flash_Mode_Set to configure a flash signal for
  * the acquisition duration. \n
  * See the following example code.
  *
  * \code
  * const peak_flash_mode flashMode = PEAK_FLASH_MODE_ACQUISITION_ACTIVE;
  * peak_status status = peak_Flash_Mode_Set(cameraHandle, flashMode);
  * \endcode
  */
#define PEAK_FLASH_MODE_ACQUISITION_ACTIVE { PEAK_FLASH_REFERENCE_ACQUISITION_ACTIVE, PEAK_IO_CHANNEL_FLASH_OUTPUT }

 /*!
  * \ingroup flash
  * \brief peak Flash mode preset: Global start window on flash output
  *
  * Initialize a #peak_flash_mode with this preset and pass it to #peak_Flash_Mode_Set to configure a flash signal for
  * the global start window duration. \n
  * See the following example code.
  *
  * \code
  * const peak_flash_mode flashMode = FLASH_GLOBAL_START_WINDOW_ON_FLASH_OUTPUT;
  * peak_status status = peak_Flash_Mode_Set(cameraHandle, flashMode);
  * \endcode
  */
#define PEAK_FLASH_MODE_GLOBAL_START_WINDOW { PEAK_FLASH_REFERENCE_GLOBAL_START_WINDOW, PEAK_IO_CHANNEL_FLASH_OUTPUT }

/*!
 * \ingroup flash
 * \brief Query the flash feature access status
 *
 * Provides the current access status for the flash feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The flash feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The flash feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The flash feature is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The flash feature is not accessible.
 *                                      Check for a running acquisition.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The flash feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Flash_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup flash
 * \brief Enable/Disable the flash
 *
 * Sets the flash to enabled or disabled.
 *
 * A flash can be enabled or disabled if there is no running acquisition only.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The flash feature is not accessible for write.
 *                                      Check the access status of the trigger feature via #peak_Flash_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup flash
 * \brief Get the enabled status of the flash
 *
 * Queries whether the flash is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The flash is currently enabled.
 * \return #PEAK_FALSE  The flash is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_Flash_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup flash
 * \brief Query the flash mode access status
 *
 * Provides the access status for the given flash mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] flashMode The flash mode.
 *
 * \return #PEAK_ACCESS_READWRITE       The flash mode is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The flash mode is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The flash mode is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The flash mode is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The flash mode is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The flash feature is not accessible.
 *                                      Check the access status of the flash feature via #peak_Flash_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p flashMode is an invalid flash mode.
 *                                      Check #peak_flash_reference and #peak_io_channel.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Flash_Mode_GetAccessStatus(peak_camera_handle hCam, peak_flash_mode flashMode);

/*!
 * \ingroup flash
 * \brief Set the flash mode
 *
 * Changes the flash mode.
 *
 * The properties of the flash will be reset to the following default values:
 * \li The flash start delay will be set to 0.
 * \li The flash end delay will be set to 0.
 * \li The flash duration will be set to default.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] flashMode The flash mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        The flash mode is not available or not known at all.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash mode is not available for write access
 *                                          or the io channel is not available for write access.
 *                                          Check the access status of the flash mode via
 *                                          #peak_Flash_Mode_GetAccessStatus.
 *                                          Check the access status of the io channel via
 *                                          #peak_IOChannel_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p flashMode is an invalid flash mode.
 *                                          Check #peak_flash_reference and #peak_io_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p flashMode contains an invalid parameter, which can never be set.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_Mode_Set(peak_camera_handle hCam, peak_flash_mode flashMode);

/*!
 * \ingroup flash
 * \brief Get the flash mode
 *
 * Reads the current flash mode.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] flashMode    The flash mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash mode is not available for read access.
 *                                          Check the access status of the flash mode via
 *                                          #peak_Flash_Mode_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p flashMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_Mode_Get(peak_camera_handle hCam, peak_flash_mode* flashMode);

/*!
 * \ingroup flash_start_delay
 * \brief Query the flash start delay property access status
 *
 * Provides the current access status for the flash start delay property for the configured flash mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The flash start delay property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The flash start delay property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The flash start delay property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The flash start delay property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The flash start delay property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The flash feature is not accessible.
 *                                  Check the access status of the flash feature via #peak_Flash_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Flash_StartDelay_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup flash_start_delay
 * \brief Get the current range of valid flash start delay values
 *
 * Queries the current range of valid values for the flash start delay for the configured flash mode.
 *
 * The range of valid flash start delay values may depend on the flash mode, the camera configuration, and
 * the camera status.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] minFlashStartDelay_us    The minimum flash start delay value in microseconds.
 * \param[out] maxFlashStartDelay_us    The maximum flash start delay value in microseconds.
 * \param[out] incFlashStartDelay_us    The flash start delay value increment in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash start delay property is not accessible.
 *                                          Check the access status of the flash start delay via
 *                                          #peak_Flash_StartDelay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minFlashStartDelay_us, \p maxFlashStartDelay_us, and
 *                                          \p incFlashStartDelay_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_StartDelay_GetRange(peak_camera_handle hCam, double* minFlashStartDelay_us,
    double* maxFlashStartDelay_us, double* incFlashStartDelay_us);

/*!
 * \ingroup flash_start_delay
 * \brief Set the flash start delay
 *
 * Writes the desired flash start delay.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] flashStartDelay_us    The flash start delay in microseconds to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p flashStartDelay_us is out of range.
 *                                      Check the range of valid values via #peak_Flash_StartDelay_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The flash start delay property is not available for write access.
 *                                      Check the access status of the flash start delay via
 *                                      #peak_Flash_StartDelay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_StartDelay_Set(peak_camera_handle hCam, double flashStartDelay_us);

/*!
 * \ingroup flash_start_delay
 * \brief Get the flash start delay
 *
 * Reads the current flash start delay.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] flashStartDelay_us   The flash start delay in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash start delay property is not available for read access.
 *                                          Check the access status of the flash start delay via
 *                                          #peak_Flash_StartDelay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p flashStartDelay_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_StartDelay_Get(peak_camera_handle hCam, double* flashStartDelay_us);

/*!
 * \ingroup flash_end_delay
 * \brief Query the flash end delay property access status
 *
 * Provides the current access status for the flash end delay property for the configured flash mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The flash end delay property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The flash end delay property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The flash end delay property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The flash end delay property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The flash end delay property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The flash feature is not accessible.
 *                                  Check the access status of the flash feature via #peak_Flash_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Flash_EndDelay_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup flash_end_delay
 * \brief Get the current range of valid flash end delay values
 *
 * Queries the current range of valid values for the flash end delay for the configured flash mode.
 *
 * The range of valid flash end delay values may depend on the flash mode, the camera configuration, and
 * the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] minFlashEndDelay_us  The minimum flash end delay value in microseconds.
 * \param[out] maxFlashEndDelay_us  The maximum flash end delay value in microseconds.
 * \param[out] incFlashEndDelay_us  The flash end delay value increment in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash end delay property is not accessible.
 *                                          Check the access status of the flash end delay via
 *                                          #peak_Flash_EndDelay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minFlashEndDelay_us, maxFlashEndDelay_us, and
 *                                          incFlashEndDelay_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_EndDelay_GetRange(peak_camera_handle hCam, double* minFlashEndDelay_us,
    double* maxFlashEndDelay_us, double* incFlashEndDelay_us);

/*!
 * \ingroup flash_end_delay
 * \brief Set the flash end delay
 *
 * Writes the desired flash end delay.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] flashEndDelay_us  The flash end delay in microseconds to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p flashEndDelay_us is out of range.
 *                                      Check the range of valid values via #peak_Flash_EndDelay_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The flash end delay property is not available for write access.
 *                                      or the flash feature is not supported.
 *                                      Check the access status of the flash end delay via
 *                                      #peak_Flash_EndDelay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_EndDelay_Set(peak_camera_handle hCam, double flashEndDelay_us);

/*!
 * \ingroup flash_end_delay
 * \brief Get the flash end delay
 *
 * Reads the current flash end delay.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] flashEndDelay_us The flash end delay in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash end delay property is not available for read access.
 *                                          Check the access status of the flash end delay via
 *                                          #peak_Flash_EndDelay_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p flashEndDelay_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_EndDelay_Get(peak_camera_handle hCam, double* flashEndDelay_us);

/*!
 * \ingroup flash_duration
 * \brief Query the flash duration property access status
 *
 * Provides the current access status for the flash duration property for the configured flash mode.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The flash duration property is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The flash duration property is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The flash duration property is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The flash duration property is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The flash duration property is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED   The flash feature is not accessible.
 *                                  Check the access status of the flash feature via #peak_Flash_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Flash_Duration_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup flash_duration
 * \brief Get the current range of valid flash duration values
 *
 * Queries the current range of valid values for the flash duration for the current flash mode.
 *
 * The range of valid flash duration values may depend on the flash mode, the camera configuration, and
 * the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] minFlashDuration_us  The minimum flash duration value in microseconds.
 * \param[out] maxFlashDuration_us  The maximum flash duration value in microseconds.
 * \param[out] incFlashDuration_us  The flash duration value increment in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash duration property is not accessible.
 *                                          Check the access status of the flash duration via
 *                                          #peak_Flash_Duration_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minFlashDuration_us, \p maxFlashDuration_us, and
 *                                          \p incFlashDuration_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_Duration_GetRange(peak_camera_handle hCam, double* minFlashDuration_us,
    double* maxFlashDuration_us, double* incFlashDuration_us);

/*!
 * \ingroup flash_duration
 * \brief Set the flash duration
 *
 * Writes the desired flash duration.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] flashDuration_us  The flash duration in microseconds to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p flashDuration_us is out of range.
 *                                      Check the range of valid values via #peak_Flash_Duration_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The flash duration property is not available for write access.
 *                                      Check the access status via #peak_Flash_Duration_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_Duration_Set(peak_camera_handle hCam, double flashDuration_us);

/*!
 * \ingroup flash_duration
 * \brief Get the flash duration
 *
 * Reads the current flash duration.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] flashDuration_us The flash duration in microseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The flash duration property is not available for read access.
 *                                          Check the access status of the flash duration via
 *                                          #peak_Flash_Duration_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p flashDuration_us is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Flash_Duration_Get(peak_camera_handle hCam, double* flashDuration_us);

/*!
 * \ingroup pixelformat
 * \brief Query the pixel format access status
 *
 * Provides the current access status for the pixel format feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The pixel format feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The pixel format feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The pixel format feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The pixel format feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The pixel format feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_PixelFormat_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup pixelformat
 * \brief Get the list of currently selectable pixel formats
 *
 * Queries the list of currently selectable pixel formats.
 *
 * The list of selectable pixel formats may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] pixelFormatList      Pointer to a user allocated array buffer to receive the pixel format list.
 *                                  If this parameter is NULL, \p pixelFormatCount will contain the current
 *                                  number of pixel formats. \n
 *                                  The required size of \p pixelFormatList in bytes is
 *                                  \p pixelFormatCount x sizeof(#peak_pixel_format).
 * \param[in,out] pixelFormatCount  \li \p pixelFormatList equal NULL: \n
 *                                      out: minimal number of pixel formats \p pixelFormatList must be
 *                                           large enough to hold \n
 *                                  \li \p pixelFormatList unequal NULL: \n
 *                                      in: number of pixel formats \p pixelFormatList can hold \n
 *                                      out: number of pixel formats filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p pixelFormatList is not NULL and the value of \p *pixelFormatCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel format feature is not accessible.
 *                                          Check the access status of the pixel format feature via
 *                                          #peak_PixelFormat_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelFormatCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the pixel format list might change between the size query call and the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_PixelFormat_GetList(peak_camera_handle hCam, peak_pixel_format* pixelFormatList,
    size_t* pixelFormatCount);

/*!
 * \ingroup pixelformat
 * \brief Set the pixel format
 *
 * Writes the desired pixel format.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] pixelFormat   The pixel format to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p pixelFormat is out of range.
 *                                      Check the range of valid values via #peak_PixelFormat_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED   The pixel format feature is not available for write access.
 *                                      Check the access status via #peak_PixelFormat_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_PixelFormat_Set(peak_camera_handle hCam, peak_pixel_format pixelFormat);

/*!
 * \ingroup pixelformat
 * \brief Get the pixel format
 *
 * Reads the current pixel format.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] pixelFormat  The pixel format.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel format feature is not available for read access.
 *                                          Check the access status via #peak_PixelFormat_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelFormat is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_PixelFormat_Get(peak_camera_handle hCam, peak_pixel_format* pixelFormat);

/*!
 * \ingroup gain
 * \brief peak Gain type
 *
 * The gain type is used in the gain related functions and specifies which type of gain is addressed or used.
 */
typedef enum
{
    /*! \brief Invalid gain type
     *
     * Use this value for the initialization of variables of type peak_gain_type.
     */
    PEAK_GAIN_TYPE_INVALID  = 0,

    /*! \brief Analog gain is used */
    PEAK_GAIN_TYPE_ANALOG   = 0x1001,

    /*! \brief Digital gain is used */
    PEAK_GAIN_TYPE_DIGITAL  = 0x2001,

    /*! \brief Combined gain is used */
    PEAK_GAIN_TYPE_COMBINED = 0x3001

} peak_gain_type;

/*!
 * \ingroup gain
 * \brief peak Gain channel
 *
 * The gain channel is used in the gain related functions and specifies which channel of gain is addressed or used.
 */
typedef enum
{
    /*! \brief Invalid gain channel
     *
     * Use this value for the initialization of variables of type peak_gain_channel.
     */
    PEAK_GAIN_CHANNEL_INVALID   = 0,

    /*! \brief Red channel */
    PEAK_GAIN_CHANNEL_RED       = 0x0001,

    /*! \brief Green channel */
    PEAK_GAIN_CHANNEL_GREEN     = 0x0002,

    /*! \brief Blue channel */
    PEAK_GAIN_CHANNEL_BLUE      = 0x0004,

    /*! \brief Master channel */
    PEAK_GAIN_CHANNEL_MASTER    = 0x0007

} peak_gain_channel;

/*!
 * \ingroup gain
 * \brief Query the gain access status for the specified gain type and gain channel
 *
 * Provides the current access status of the gain feature for the specified gain type and gain channel.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainType      The gain type.
 * \param[in] gainChannel   The gain channel.
 *
 * \return #PEAK_ACCESS_READWRITE       The gain feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The gain feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The gain feature is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The gain feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The gain feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p gainType is an invalid gain type
 *                                      or \p gainChannel is an invalid gain channel.
 *                                      Check #peak_gain_type and #peak_gain_channel.
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Gain_GetAccessStatus(peak_camera_handle hCam, peak_gain_type gainType,
    peak_gain_channel gainChannel);

/*!
 * \ingroup gain
 * \brief Get the list of available gain channels for the given gain type
 *
 * Queries the list of available gain channels for the specified gain type.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] gainType              The addressed gain type.
 * \param[out] gainChannelList      Pointer to a user allocated array buffer to receive the gain channel list.
 *                                  If this parameter is NULL, \p gainChannelCount will contain the
 *                                  number of gain channels. \n
 *                                  The required size of \p gainChannelList in bytes is
 *                                  \p gainChannelCount x sizeof(#peak_gain_channel).
 * \param[in,out] gainChannelCount  \li \p gainChannelList equal NULL: \n
 *                                      out: minimal number of gain channels \p gainChannelList must be
 *                                           large enough to hold \n
 *                                  \li \p gainChannelList unequal NULL: \n
 *                                      in: number of gain channels \p gainChannelList can hold \n
 *                                      out: number of gain channels filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p gainChannelList is not NULL and the value of \p *gainChannelCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The gain feature is not accessible.
 *                                          Check the access status via #peak_Gain_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gainType is an invalid gain channel
 *                                          or \p gainChannelCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gain_GetChannelList(peak_camera_handle hCam, peak_gain_type gainType,
    peak_gain_channel* gainChannelList, size_t* gainChannelCount);

/*!
 * \ingroup gain
 * \brief Get the current range of valid gain values for the specified gain type and gain channel
 *
 * Queries the current range of valid values for the gain for the specified gain type and gain channel.
 *
 * The range of valid gain values may depend on the camera configuration and the camera status.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainType      The addressed gain type.
 * \param[in] gainChannel   The addressed gain channel.
 * \param[out] minGain      The minimum gain value.
 * \param[out] maxGain      The maximum gain value.
 * \param[out] incGain      The gain value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The gain is not accessible.
 *                                          Check the access status via #peak_Gain_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gainType is an invalid gain type
 *                                          or \p gainChannel is an invalid gain channel
 *                                          or at least one of \p minGain, \p maxGain, and \p incGain is an invalid
 *                                          pointer.
 *                                          Check #peak_gain_type and #peak_gain_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gain_GetRange(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel,
    double* minGain, double* maxGain, double* incGain);

/*!
 * \ingroup gain
 * \brief Set the gain for the specified gain type and gain channel
 *
 * Writes the desired gain value for the specified gain type and gain channel.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainType      The addressed gain type.
 * \param[in] gainChannel   The addressed gain channel.
 * \param[in] gain          The gain value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p gain is out of range.
 *                                          Check the range of valid values via #peak_Gain_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED       The gain feature is not available for write access.
 *                                          Check the access status via #peak_Gain_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gainType is an invalid gain type
 *                                          or \p gainChannel is an invalid gain channel.
 *                                          Check #peak_gain_type and #peak_gain_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gain_Set(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel,
    double gain);

/*!
 * \ingroup gain
 * \brief Get the gain value for the specified gain type and gain channel
 *
 * Reads the current gain value for the specified gain type and gain channel.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainType      The addressed gain type.
 * \param[in] gainChannel   The addressed gain channel.
 * \param[out] gain         The gain value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The gain feature is not available for read access.
 *                                          Check the access status via #peak_Gain_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gainType is an invalid gain type
 *                                          or \p gainChannel is an invalid gain channel
 *                                          or \p gain is an invalid pointer.
 *                                          Check #peak_gain_type and #peak_gain_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gain_Get(peak_camera_handle hCam, peak_gain_type gainType, peak_gain_channel gainChannel,
    double* gain);

/*!
 * \ingroup gamma
 * \brief Query the gamma access status
 *
 * Provides the current access status for the gamma feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The gamma feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The gamma feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The gamma feature is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The gamma feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The gamma feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Gamma_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup gamma
 * \brief Get the current range of valid gamma values
 *
 * Queries the current range of valid values for the gamma feature.
 *
 * \param[in] hCam      The camera handle.
 * \param[out] minGamma The minimum gamma value.
 * \param[out] maxGamma The maximum gamma value.
 * \param[out] incGamma The gamma value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The gamma feature is not accessible.
 *                                          Check the access status via #peak_Gamma_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minGamma, \p maxGamma and \p incGamma is an invalid
 *                                          pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gamma_GetRange(peak_camera_handle hCam, double* minGamma, double* maxGamma, double* incGamma);

/*!
 * \ingroup gamma
 * \brief Set the gamma value
 *
 * Writes the desired gamma value.
 *
 * \param[in] hCam  The camera handle.
 * \param[in] gamma The gamma value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p gamma value is out of range.
 *                                      Check the range of valid values via #peak_Gamma_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The gamma feature is not available for write access.
 *                                      Check the access status via #peak_Gamma_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gamma_Set(peak_camera_handle hCam, double gamma);

/*!
 * \ingroup gamma
 * \brief Get the gamma value
 *
 * Reads the current gamma value.
 *
 * \param[in] hCam      The camera handle.
 * \param[out] gamma    The gamma value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The gamma feature is not available for read access.
 *                                          Check the access status via #peak_Gamma_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gamma is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Gamma_Get(peak_camera_handle hCam, double* gamma);

/*!
 * \ingroup color_correction
 * \brief peak Color correction mode
 *
 *
 * The color correction mode defines the matrix of factors that the color correction feature applies to the image data.
 */
typedef enum
{
    /*! \brief Invalid color correction
     *
     * Use this value for the initialization of variables of type peak_color_correction;.
     */
    PEAK_COLOR_CORRECTION_MODE_INVALID  = 0,

     /*! \brief HQ
      *
      * The color correction is done with the high quality matrix preset.
      */
    PEAK_COLOR_CORRECTION_MODE_HQ       = 0x1001,

    /*! \brief User 1
     *
     * The color correction is done with the user-defined matrix.
     *
     * By default the user-defined matrix is set to the identity matrix. \n
     * It can be changed via #peak_ColorCorrection_Matrix_Set.
     */
    PEAK_COLOR_CORRECTION_MODE_USER_1   = 0x2001,

} peak_color_correction_mode;

/*!
 * \ingroup color_correction
 * \brief Query the color correction access status
 *
 * Provides the current access status for the color correction feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The color correction feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The color correction feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The color correction feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The color correction feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The color correction feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_ColorCorrection_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup color_correction
 * \brief Get the list of currently selectable color correction modes
 *
 * Queries the list of currently selectable color correction modes.
 *
 * The list of selectable color correction modes may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] colorCorrectionModeList      Pointer to a user allocated array buffer to receive the color correction
 *                                          mode list. \n
 *                                          If this parameter is NULL, \p colorCorrectionModeCount will contain the
 *                                          current number of color correction modes. \n
 *                                          The required size of \p colorCorrectionModeList in bytes is
 *                                          \p colorCorrectionModeCount x sizeof(peak_color_correction_mode).
 * \param[in,out] colorCorrectionModeCount  \li \p colorCorrectionModeList equal NULL: \n
 *                                              out: minimal number of color correction modes \p colorCorrectionModeList
 *                                                   must be large enough to hold \n
 *                                          \li \p colorCorrectionModeList unequal NULL: \n
 *                                              in:  number of color corrections modes \p colorCorrectionModeList can
 *                                                   hold \n
 *                                              out: number of color correction modes filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p colorCorrectionModeList is not NULL and the value of
 *                                          \p *colorCorrectionModeCount is too small to receive the expected amount of
 *                                          data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The color correction feature is not accessible.
 *                                          Check the access status via #peak_ColorCorrection_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p colorCorrectionModeCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Please consider that the color correction mode list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_ColorCorrection_Mode_GetList(peak_camera_handle hCam,
    peak_color_correction_mode* colorCorrectionModeList, size_t* colorCorrectionModeCount);

/*!
 * \ingroup color_correction
 * \brief Set the color correction mode
 *
 * Sets the specified color correction mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] colorCorrectionMode   The color correction mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p colorCorrectionMode is out of range.
 *                                          Check the list of valid color correction modes via
 *                                          #peak_ColorCorrection_Mode_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The color correction feature is not available for write access.
 *                                          Check the access status via #peak_ColorCorrection_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p colorCorrectionMode is an invalid color correction mode.
 *                                          Check #peak_color_correction_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ColorCorrection_Mode_Set(peak_camera_handle hCam, peak_color_correction_mode colorCorrectionMode);

/*!
 * \ingroup color_correction
 * \brief Get the color correction mode
 *
 * Reads the current color correction mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] colorCorrectionMode  The color correction mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The color correction feature is not available for read access.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p colorCorrectionMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ColorCorrection_Mode_Get(peak_camera_handle hCam, peak_color_correction_mode* colorCorrectionMode);

/*!
 * \ingroup color_correction
 * \brief Query the color correction matrix access status
 *
 * Provides the current access status for the color correction feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The color correction feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The color correction feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The color correction feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The color correction feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The color correction feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_ColorCorrection_Matrix_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup color_correction
 * \brief Get the current range of valid color correction matrix element values
 *
 * Queries the current range of valid values for the color correction matrix elements.
 *
 * The range of valid matrix values may depend on the camera configuration and the camera status.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] minMatrixElementValue    The minimum element value.
 * \param[out] maxMatrixElementValue    The maximum element value.
 * \param[out] incMatrixElementValue    The element increment value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minMatrixElementValue, \p maxMatrixElementValue, and
 *                                          \p incMatrixElementValue is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ColorCorrection_Matrix_GetRange(peak_camera_handle hCam, double* minMatrixElementValue,
    double* maxMatrixElementValue, double* incMatrixElementValue);

/*!
 * \ingroup color_correction
 * \brief Sets the color correction matrix for the current selected color correction
 *
 * Writes the desired image color correction matrix for the current color correction.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] colorCorrectionMatrix The color correction matrix to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p one or more matrix values are out of range.
 *                                          Check the range of valid values via #peak_ColorCorrection_Matrix_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED       The color correction feature is not available for write access.
 *                                          Check the access status via #peak_ColorCorrection_Matrix_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ColorCorrection_Matrix_Set(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix);

/*!
 * \ingroup color_correction
 * \brief Get the color correction matrix
 *
 * Reads the current color correction matrix.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] colorCorrectionMatrix    The color correction matrix.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The color correction feature is not available for read access.
 *                                          Check the access status via #peak_ColorCorrection_Matrix_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p colorCorrectionMatrix is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ColorCorrection_Matrix_Get(peak_camera_handle hCam, peak_matrix* colorCorrectionMatrix);

/*!
 * \ingroup color_correction
 * \brief Enable/Disable the color correction
 *
 * Sets the color correction to enabled or disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The color correction feature is not accessible for write.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ColorCorrection_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup color_correction
 * \brief Get the enabled status of the color correction
 *
 * Queries whether the color correction is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The color correction feature is currently enabled.
 * \return #PEAK_FALSE  The color correction feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_ColorCorrection_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup generics
 * \brief peak Auto feature mode
 *
 * The auto feature mode defines the mode of operation for auto features.
 */
typedef enum
{
    /*! \brief Invalid auto feature mode
     *
     * Use this value for the initialization of variables of type peak_auto_feature_mode.
     */
    PEAK_AUTO_FEATURE_MODE_INVALID      = 0,

    /*! \brief Auto feature Off
     *
     * The auto feature is off.
     * 
     * This is the default mode for all auto features.
     */
    PEAK_AUTO_FEATURE_MODE_OFF          = 0x0001,

    /*! \brief Auto feature mode Once
     *
     * The auto feature is executed once.
     */
    PEAK_AUTO_FEATURE_MODE_ONCE         = 0x1001,

    /*! \brief Auto feature mode Continuous
     *
     * The auto feature is executed continuously.
     */
    PEAK_AUTO_FEATURE_MODE_CONTINUOUS   = 0x1002

} peak_auto_feature_mode;

/*!
 * \ingroup generics
 * \brief peak Auto feature ROI mode
 *
 * The auto feature ROI mode defines the mode of operation for auto feature ROIs.
 */
typedef enum
{
    /*! \brief Invalid auto feature ROI mode
     *
     * Use this value for the initialization of variables of type peak_auto_feature_roi_mode.
     */
    PEAK_AUTO_FEATURE_ROI_MODE_INVALID      = 0,

    /*! \brief Auto feature ROI mode Full Image
     *
     * The auto feature ROI automatically follows the image ROI. \n
     * I.e. the auto feature always covers the whole image.
     * 
     * This is the default mode for all auto features.
     */
    PEAK_AUTO_FEATURE_ROI_MODE_FULL_IMAGE   = 0x1001,

    /*! \brief Auto feature ROI mode Manual
     *
     * The auto feature ROI can be set manually inside of the bounds of the image ROI. \n
     * If the image ROI size is reduced the auto feature ROI may be automatically clipped.
     * If the auto feature ROI is out of the image ROI bounds after a change of the image ROI,
     * the position of the auto feature ROI is adjusted and its size is set to minimum.
     */
    PEAK_AUTO_FEATURE_ROI_MODE_MANUAL       = 0x2001

} peak_auto_feature_roi_mode;

/*!
 * \ingroup auto_brightness
 * \brief Query the auto brightness access status
 *
 * Provides the current access status for the auto brightness feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The auto brightness feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The auto brightness feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The auto brightness feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The auto brightness feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The auto brightness feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_AutoBrightness_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup auto_brightness
 * \brief Get the current range of valid auto brightness target values
 *
 * Queries the current range of valid values for the auto brightness target property.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] minAutoBrightnessTarget  The minimum auto brightness target value.
 * \param[out] maxAutoBrightnessTarget  The maximum auto brightness target value.
 * \param[out] incAutoBrightnessTarget  The auto brightness target value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not accessible.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessTarget, \p maxAutoBrightnessTarget, and
 *                                          \p incAutoBrightnessTarget is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Target_GetRange(peak_camera_handle hCam, uint32_t* minAutoBrightnessTarget,
    uint32_t* maxAutoBrightnessTarget, uint32_t* incAutoBrightnessTarget);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto brightness target value
 *
 * Writes the desired auto brightness target value.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoBrightnessTarget  The auto brightness target value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessTarget value is out of range.
 *                                      Check the range of valid values via #peak_AutoBrightness_Target_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto brightness feature is not available for write access.
 *                                      Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Target_Set(peak_camera_handle hCam, uint32_t autoBrightnessTarget);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto brightness target value
 *
 * Reads the current auto brightness target value.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoBrightnessTarget The auto brightness target value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessTarget is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Target_Get(peak_camera_handle hCam, uint32_t* autoBrightnessTarget);

/*!
 * \ingroup auto_brightness
 * \brief Get the current range of valid auto brightness target tolerance values
 *
 * Queries the current range of valid values for the auto brightness target tolerance property.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] minAutoBrightnessTargetTolerance The minimum auto brightness target tolerance value.
 * \param[out] maxAutoBrightnessTargetTolerance The maximum auto brightness target tolerance value.
 * \param[out] incAutoBrightnessTargetTolerance The auto brightness target tolerance value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not accessible.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessTargetTolerance,
 *                                          \p maxAutoBrightnessTargetTolerance, and \p incAutoBrightnessTargetTolerance
 *                                          is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_TargetTolerance_GetRange(peak_camera_handle hCam,
    uint32_t* minAutoBrightnessTargetTolerance, uint32_t* maxAutoBrightnessTargetTolerance,
    uint32_t* incAutoBrightnessTargetTolerance);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto brightness target tolerance value
 *
 * Writes the desired auto brightness target tolerance value.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] autoBrightnessTargetTolerance The auto brightness target tolerance value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessTargetTolerance value is out of range.
 *                                      Check the range of valid values via
 *                                      #peak_AutoBrightness_TargetTolerance_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto brightness feature is not available for write access.
 *                                      Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_TargetTolerance_Set(peak_camera_handle hCam,
    uint32_t autoBrightnessTargetTolerance);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto brightness target tolerance value
 *
 * Reads the current auto brightness target tolerance value.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] autoBrightnessTargetTolerance    The auto brightness target tolerance value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessTargetTolerance is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_TargetTolerance_Get(peak_camera_handle hCam,
    uint32_t* autoBrightnessTargetTolerance);

/*!
 * \ingroup auto_brightness
 * \brief Get the current range of valid auto brightness target percentile values
 *
 * Queries the current range of valid values for the auto brightness target percentile property.
 *
 * \param[in] hCam                                  The camera handle.
 * \param[out] minAutoBrightnessTargetPercentile    The minimum auto brightness target percentile value.
 * \param[out] maxAutoBrightnessTargetPercentile    The maximum auto brightness target percentile value.
 * \param[out] incAutoBrightnessTargetPercentile    The auto brightness target percentile value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not accessible.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessTargetPercentile,
 *                                          \p maxAutoBrightnessTargetPercentile, and
 *                                          \p incAutoBrightnessTargetPercentile is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_TargetPercentile_GetRange(peak_camera_handle hCam,
    double* minAutoBrightnessTargetPercentile, double* maxAutoBrightnessTargetPercentile,
    double* incAutoBrightnessTargetPercentile);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto brightness target percentile value
 *
 * Writes the desired auto brightness target percentile value.
 *
 * \param[in] hCam                              The camera handle.
 * \param[in] autoBrightnessTargetPercentile    The auto brightness target percentile value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessTargetPercentile value is out of range.
 *                                      Check the range of valid values via
 *                                      #peak_AutoBrightness_TargetPercentile_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto brightness feature is not available for write access.
 *                                      Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_TargetPercentile_Set(peak_camera_handle hCam,
    double autoBrightnessTargetPercentile);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto brightness target percentile value
 *
 * Reads the current auto brightness target percentile value.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] autoBrightnessTargetPercentile   The auto brightness target percentile value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessTargetPercentile is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_TargetPercentile_Get(peak_camera_handle hCam,
    double* autoBrightnessTargetPercentile);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto brightness ROI mode
 *
 * Writes the desired auto brightness ROI mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoBrightnessROIMode The auto brightness ROI mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not available for write access.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessROIMode is an invalid auto feature ROI mode.
 *                                          Check #peak_auto_feature_roi_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_ROI_Mode_Set(peak_camera_handle hCam,
    peak_auto_feature_roi_mode autoBrightnessROIMode);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto brightness ROI mode
 *
 * Reads the current auto brightness ROI mode.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] autoBrightnessROIMode    The current auto brightness ROI mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessROIMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_ROI_Mode_Get(peak_camera_handle hCam,
    peak_auto_feature_roi_mode* autoBrightnessROIMode);

/*!
 * \ingroup auto_brightness
 * \brief Get the current range of valid auto brightness ROI offsets
 *
 * Queries the current range of valid values for the auto brightness ROI offset.
 *
 * The range of valid auto brightness ROI offset values may depend on the camera configuration and the camera status. \n
 * In special the current setting of the image ROI and the current setting of the auto brightness ROI size has an impact
 * on the range of valid auto brightness ROI offset values.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] minAutoBrightnessROIOffset   The minimum auto brightness ROI offset values.
 * \param[out] maxAutoBrightnessROIOffset   The maximum auto brightness ROI offset values.
 * \param[out] incAutoBrightnessROIOffset   The auto brightness ROI offset values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not accessible.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minROIOffset, maxROIOffset, and incROIOffset is an
 *                                          invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_ROI_Offset_GetRange(peak_camera_handle hCam,
    peak_position* minAutoBrightnessROIOffset, peak_position* maxAutoBrightnessROIOffset,
    peak_position* incAutoBrightnessROIOffset);

/*!
 * \ingroup auto_brightness
 * \brief Get the current range of valid auto brightness ROI sizes
 *
 * Queries the current range of valid values for the auto brightness ROI dimensions.
 *
 * The range of valid auto brightness ROI size values may depend on the camera configuration and the camera status. \n
 * In special the current setting of the image ROI and the current setting of the auto brightness ROI offset has an
 * impact on the range of valid auto brightness ROI size values.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] minAutoBrightnessROISize The minimum auto brightness ROI size values.
 * \param[out] maxAutoBrightnessROISize The maximum auto brightness ROI size values.
 * \param[out] incAutoBrightnessROISize The auto brightness ROI size values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not accessible.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessROISize, \p maxAutoBrightnessROISize,
 *                                          and \p incAutoBrightnessROISize is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_ROI_Size_GetRange(peak_camera_handle hCam, peak_size* minAutoBrightnessROISize,
    peak_size* maxAutoBrightnessROISize, peak_size* incAutoBrightnessROISize);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto brightness ROI
 *
 * Writes the desired auto brightness ROI.
 * 
 * \note Setting the auto brightness ROI is only possible if #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL is set for the
 *       auto brightness ROI mode.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] autoBrightnessROI The auto brightness ROI to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessROI value is out of range.
 *                                      Check the range of valid values via #peak_AutoBrightness_ROI_Offset_GetRange and
 *                                      #peak_AutoBrightness_ROI_Size_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto brightness feature is not available for write access
 *                                      or the auto brightness ROI mode is not set to
 *                                      #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL.
 *                                      Check the access status via #peak_AutoBrightness_GetAccessStatus.
 *                                      Check the auto brightness ROI mode via #peak_AutoBrightness_ROI_Mode_Get.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_ROI_Set(peak_camera_handle hCam, peak_roi autoBrightnessROI);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto brightness ROI
 *
 * Reads the current auto brightness ROI.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoBrightnessROI    The auto brightness ROI.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto brightness feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessROI is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_ROI_Get(peak_camera_handle hCam, peak_roi* autoBrightnessROI);

/*!
 * \ingroup auto_brightness
 * \brief Query the auto exposure control access status
 *
 * Provides the current access status for the auto exposure control feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The auto exposure control feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The auto exposure control feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The auto exposure control feature is not accessible because the GFA write access
 *                                      is enabled.
 * \return #PEAK_ACCESS_NONE            The auto exposure control feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The auto exposure control feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_ACCESS_DENIED   The auto brightness feature is not accessible. 
 *                                  Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_AutoBrightness_Exposure_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto exposure control mode
 *
 * Writes the desired auto exposure control mode.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] autoExposureMode  The auto exposure control mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto exposure control feature is not available for write access.
 *                                          Check the access status via #peak_AutoBrightness_Exposure_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoExposureMode is an invalid auto feature mode.
 *                                          Check #peak_auto_feature_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Exposure_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoExposureMode);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto exposure control mode
 *
 * Reads the current auto exposure control mode.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] autoExposureMode The current auto exposure control mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto exposure control feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_Exposure_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoExposureMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Exposure_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode* autoExposureMode);

/*!
 * \ingroup auto_brightness
 * \brief Query the auto gain control access status
 *
 * Provides the current access status for the auto gain control feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The auto gain control feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The auto gain control feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The auto gain control feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The auto gain control feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The auto gain control feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_ACCESS_DENIED   The auto brightness feature is not accessible. 
 *                                  Check the access status via #peak_AutoBrightness_GetAccessStatus.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_AutoBrightness_Gain_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup auto_brightness
 * \brief Set the auto gain control mode
 *
 * Writes the desired auto gain control mode.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] autoGainMode  The auto gain control mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto gain control feature is not available for write access.
 *                                          Check the access status via #peak_AutoBrightness_Gain_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoGainMode is an invalid auto feature mode.
 *                                          Check #peak_auto_feature_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Gain_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode);

/*!
 * \ingroup auto_brightness
 * \brief Get the auto gain control mode
 *
 * Reads the current auto gain control mode.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] autoGainMode The current auto gain control mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto gain control feature is not available for read access.
 *                                          Check the access status via #peak_AutoBrightness_Gain_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoGainMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoBrightness_Gain_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode* autoGainMode);

/*!
 * \ingroup auto_white_balance
 * \brief Query the auto white balance access status
 *
 * Provides the current access status for the auto white balance feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The auto white balance feature is readable and writable.
 * \return #PEAK_ACCESS_READONLY        The auto white balance feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The auto white balance feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The auto white balance feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The auto white balance feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_AutoWhiteBalance_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup auto_white_balance
 * \brief Set the auto white balance ROI mode
 *
 * Writes the desired auto white balance ROI mode.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] autoWhiteBalanceROIMode   The auto white balance ROI mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance feature is not available for write access.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceROIMode is an invalid auto feature ROI mode.
 *                                          Check #peak_auto_feature_roi_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Mode_Set(peak_camera_handle hCam,
    peak_auto_feature_roi_mode autoWhiteBalanceROIMode);

/*!
 * \ingroup auto_white_balance
 * \brief Get the auto white balance ROI mode
 *
 * Reads the current auto white balance ROI mode.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] autoWhiteBalanceROIMode  The current auto white balance ROI mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance control feature is not available for read access.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceROIMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Mode_Get(peak_camera_handle hCam,
    peak_auto_feature_roi_mode* autoWhiteBalanceROIMode);

/*!
 * \ingroup auto_white_balance
 * \brief Get the current range of valid auto white balance ROI offsets
 *
 * Queries the current range of valid values for the auto white balance ROI offset.
 *
 * The range of valid auto white balance ROI offset values may depend on the camera configuration and the camera
 * status. \n
 * In special the current setting of the image ROI and the current setting of the auto white balance ROI size has an
 * impact on the range of valid auto white balance ROI offset values.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] minAutoWhiteBalanceROIOffset The minimum auto white balance ROI offset values.
 * \param[out] maxAutoWhiteBalanceROIOffset The maximum auto white balance ROI offset values.
 * \param[out] incAutoWhiteBalanceROIOffset The auto white balance ROI offset values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance feature is not accessible.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoWhiteBalanceROIOffset,
 *                                          \p maxAutoWhiteBalanceROIOffset, and \p incAutoWhiteBalanceROIOffset is an
 *                                          invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Offset_GetRange(peak_camera_handle hCam,
    peak_position* minAutoWhiteBalanceROIOffset, peak_position* maxAutoWhiteBalanceROIOffset,
    peak_position* incAutoWhiteBalanceROIOffset);

/*!
 * \ingroup auto_white_balance
 * \brief Get the current range of valid auto white balance ROI sizes
 *
 * Queries the current range of valid values for the auto white balance ROI dimensions.
 *
 * The range of valid auto white balance ROI size values may depend on the camera configuration and the camera
 * status. \n
 * In special the current setting of the image ROI and the current setting of the auto white balance ROI offset has an
 * impact on the range of valid auto white balance ROI size values.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] minAutoWhiteBalanceROISize   The minimum auto white balance ROI size values.
 * \param[out] maxAutoWhiteBalanceROISize   The maximum auto white balance ROI size values.
 * \param[out] incAutoWhiteBalanceROISize   The auto white balance ROI size values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance feature is not accessible.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoWhiteBalanceROISize,
 *                                          \p maxAutoWhiteBalanceROISize, and \p incAutoWhiteBalanceROISize is an
 *                                          invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Size_GetRange(peak_camera_handle hCam, peak_size* minAutoWhiteBalanceROISize,
    peak_size* maxAutoWhiteBalanceROISize, peak_size* incAutoWhiteBalanceROISize);

/*!
 * \ingroup auto_white_balance
 * \brief Set the auto white balance ROI
 *
 * Writes the desired auto white balance ROI.
 *
 * \note Setting the auto white balance ROI is only possible if #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL is set for the
 *       auto white balance ROI mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoWhiteBalanceROI   The auto white balance ROI to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoWhiteBalanceROI value is out of range.
 *                                      Check the range of valid values via #peak_AutoWhiteBalance_ROI_Offset_GetRange and
 *                                      #peak_AutoWhiteBalance_ROI_Size_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto white balance feature is not available for write access
 *                                      or the auto white balance ROI mode is not set to
 *                                      #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL.
 *                                      Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 *                                      Check the auto white balance ROI mode via #peak_AutoWhiteBalance_ROI_Mode_Get.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Set(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI);

/*!
 * \ingroup auto_white_balance
 * \brief Get the auto white balance ROI
 *
 * Reads the current auto white balance ROI.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoWhiteBalanceROI  The auto white balance ROI.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance feature is not available for read access.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceROI is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_ROI_Get(peak_camera_handle hCam, peak_roi* autoWhiteBalanceROI);

/*!
 * \ingroup auto_white_balance
 * \brief Set the auto white balance control mode
 *
 * Writes the desired auto white balance control mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoWhiteBalanceMode  The auto white balance control mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance control feature is not available for write access.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceMode is an invalid auto feature mode.
 *                                          Check #peak_auto_feature_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode);

/*!
 * \ingroup auto_white_balance
 * \brief Get the auto white balance control mode
 *
 * Reads the current auto white balance control mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoWhiteBalanceMode The current auto white balance control mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The auto white balance control feature is not available for read access.
 *                                          Check the access status via #peak_AutoWhiteBalance_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_AutoWhiteBalance_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode* autoWhiteBalanceMode);

/*!
 * \ingroup roi
 * \brief Query the ROI access status
 *
 * Provides the current access status for the ROI feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The ROI feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The ROI feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The ROI feature is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The ROI feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The ROI feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_ROI_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup roi
 * \brief Get the current range of valid ROI offsets
 *
 * Queries the current range of valid values for the ROI offset.
 *
 * The range of valid ROI offset values may depend on the camera configuration and the camera status. \n
 * In special the current setting of the ROI size has an impact on the range of valid ROI offset values.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] minROIOffset The minimum ROI offset values.
 * \param[out] maxROIOffset The maximum ROI offset values.
 * \param[out] incROIOffset The ROI offset values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The ROI feature is not accessible.
 *                                          Check the access status via #peak_ROI_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minROIOffset, \p maxROIOffset, and \p incROIOffset is an
 *                                          invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ROI_Offset_GetRange(peak_camera_handle hCam, peak_position* minROIOffset,
    peak_position* maxROIOffset, peak_position* incROIOffset);

/*!
 * \ingroup roi
 * \brief Get the current range of valid ROI sizes
 *
 * Queries the current range of valid values for the ROI dimensions.
 *
 * The range of valid ROI size values may depend on the camera configuration and the camera status. \n
 * In special the current setting of the ROI offset has an impact on the range of valid ROI size values.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] minROISize   The minimum ROI size values.
 * \param[out] maxROISize   The maximum ROI size values.
 * \param[out] incROISize   The ROI size values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The ROI feature is not accessible.
 *                                          Check the access status via #peak_ROI_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minROISize, \p maxROISize, and \p incROISize is an
 *                                          invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ROI_Size_GetRange(peak_camera_handle hCam, peak_size* minROISize, peak_size* maxROISize,
    peak_size* incROISize);

/*!
 * \ingroup roi
 * \brief Set the ROI
 *
 * Writes the desired image ROI.
 *
 * \param[in] hCam  The camera handle.
 * \param[in] roi   The ROI to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p roi is out of range.
 *                                      Check the range of valid values via #peak_ROI_Offset_GetRange and
 *                                      #peak_ROI_Size_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The ROI feature is not available for write access.
 *                                      Check the access status via #peak_ROI_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ROI_Set(peak_camera_handle hCam, peak_roi roi);

/*!
 * \ingroup roi
 * \brief Get the ROI
 *
 * Reads the current image ROI.
 *
 * \param[in] hCam  The camera handle.
 * \param[out] roi  The ROI.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The ROI feature is not available for read access.
 *                                          Check the access status via #peak_ROI_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p roi is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_ROI_Get(peak_camera_handle hCam, peak_roi* roi);

/*!
 * \ingroup binning
 * \brief Query the binning access status
 *
 * Provides the current access status for the binning feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The binning feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The binning feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The binning feature is not accessible because the GFA write access is enabled.
 * \return #PEAK_ACCESS_NONE            The binning feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The binning feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Binning_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup binning
 * \brief Get the list of currently selectable factors for the binning in x direction
 *
 * Queries the list of currently selectable binning factors for the x direction.
 *
 * The list of selectable binning factors may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] binningFactorXList       Pointer to a user allocated array buffer to receive the binning factor list.
 *                                      If this parameter is NULL, \p binningFactorXCount will contain the current
 *                                      number of binning factors. \n
 *                                      The required size of \p binningFactorXList in bytes is
 *                                      \p binningFactorXCount x sizeof(uint32_t).
 * \param[in,out] binningFactorXCount   \li \p binningFactorXList equal NULL: \n
 *                                          out: minimal number of binning factors \p binningFactorXList must be
 *                                               large enough to hold \n
 *                                      \li \p binningFactorXList unequal NULL: \n
 *                                          in: number of binning factors \p binningFactorXList can hold \n
 *                                          out: number of binning factors filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p binningFactorXList is not NULL and the value of \p *binningFactorXCount
 *                                          is too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The binning feature is not accessible.
 *                                          Check the access status via #peak_Binning_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p binningFactorXCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the binning factor list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_Binning_FactorX_GetList(peak_camera_handle hCam, uint32_t* binningFactorXList,
    size_t* binningFactorXCount);

/*!
 * \ingroup binning
 * \brief Get the list of currently selectable factors for the binning in y direction
 *
 * Queries the list of currently selectable binning factors for the y direction.
 *
 * The list of selectable binning factors may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] binningFactorYList       Pointer to a user allocated array buffer to receive the binning factor list.
 *                                      If this parameter is NULL, \p binningFactorYCount will contain the current
 *                                      number of binning factors. \n
 *                                      The required size of \p binningFactorYList in bytes is
 *                                      \p binningFactorYCount x sizeof(uint32_t).
 * \param[in,out] binningFactorYCount   \li \p binningFactorYList equal NULL: \n
 *                                          out: minimal number of binning factors \p binningFactorYList must be
 *                                               large enough to hold \n
 *                                      \li \p binningFactorYList unequal NULL: \n
 *                                          in: number of binning factors \p binningFactorYList can hold \n
 *                                          out: number of binning factors filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p binningFactorYList is not NULL and the value of \p *binningFactorYCount
 *                                          is too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The binning feature is not accessible.
 *                                          Check the access status via #peak_Binning_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p binningFactorYCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the binning factor list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_Binning_FactorY_GetList(peak_camera_handle hCam, uint32_t* binningFactorYList,
    size_t* binningFactorYCount);

/*!
 * \ingroup binning
 * \brief Set the binning factors
 *
 * Writes the desired pixel binning factors.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] binningFactorX    The binning factor in x direction to set.
 * \param[in] binningFactorY    The binning factor in y direction to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p binningFactorX and/or \p binningFactorY are out of range.
 *                                          Check the range of valid values via #peak_Binning_FactorX_GetList and
 *                                          #peak_Binning_FactorY_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The binning feature is not available for write access.
 *                                          Check the access status via #peak_Binning_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Binning_Set(peak_camera_handle hCam, uint32_t binningFactorX, uint32_t binningFactorY);

/*!
 * \ingroup binning
 * \brief Get the binning factors
 *
 * Reads the current pixel binning factors.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] binningFactorX   The binning factor in x direction.
 * \param[out] binningFactorY   The binning factor in y direction.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The binning feature is not available for read access.
 *                                          Check the access status via #peak_Binning_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p binningFactorX and/or \p binningFactorY are invalid pointers.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Binning_Get(peak_camera_handle hCam, uint32_t* binningFactorX, uint32_t* binningFactorY);

/*!
 * \ingroup subsampling
 * \brief Query the decimation access status
 *
 * Provides the current access status for the decimation feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The decimation feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The decimation feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The decimation feature is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The decimation feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The decimation feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Decimation_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup decimation
 * \brief Get the list of currently selectable factors for the decimation in x direction
 *
 * Queries the list of currently selectable decimation factors for the x direction.
 *
 * The list of selectable decimation factors may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] decimationFactorXList        Pointer to a user allocated array buffer to receive the
 *                                          decimation factor list.
 *                                          If this parameter is NULL, \p decimationFactorXCount will contain
 *                                          the current number of decimation factors. \n
 *                                          The required size of \p decimationFactorXList in bytes is
 *                                          \p decimationFactorXCount x sizeof(uint32_t).
 * \param[in,out] decimationFactorXCount    \li \p decimationFactorXList equal NULL: \n
 *                                              out: minimal number of decimation factors \p decimationFactorXList
 *                                                   must be large enough to hold \n
 *                                          \li \p decimationFactorXList unequal NULL: \n
 *                                              in: number of decimation factors \p decimationFactorXList can hold \n
 *                                              out: number of decimation factors filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p decimationFactorXList is not NULL and the value of
 *                                          \p *decimationFactorXCount is too small to receive
 *                                          the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The decimation feature is not accessible.
 *                                          Check the access status via #peak_Decimation_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p decimationFactorXCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the decimation factor list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_Decimation_FactorX_GetList(peak_camera_handle hCam, uint32_t* decimationFactorXList,
    size_t* decimationFactorXCount);

/*!
 * \ingroup decimation
 * \brief Get the list of currently selectable factors for the decimation in y direction
 *
 * Queries the list of currently selectable decimation factors for the y direction.
 *
 * The list of selectable decimation factors may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] decimationFactorYList        Pointer to a user allocated array buffer to receive
 *                                          the decimation factor list.
 *                                          If this parameter is NULL, \p decimationFactorYCount will contain
 *                                          the current number of decimation factors. \n
 *                                          The required size of \p decimationFactorYList in bytes is
 *                                          \p decimationFactorYCount x sizeof(uint32_t).
 * \param[in,out] decimationFactorYCount    \li \p decimationFactorYList equal NULL: \n
 *                                              out: minimal number of decimation factors \p decimationFactorYList
 *                                                   must be large enough to hold \n
 *                                          \li \p decimationFactorYList unequal NULL: \n
 *                                              in: number of decimation factors \p decimationFactorYList can hold \n
 *                                              out: number of decimation factors filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p decimationFactorYList is not NULL and the value of
 *                                          \p *decimationFactorYCount is too small to receive
 *                                          the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The decimation feature is not accessible.
 *                                          Check the access status via #peak_Decimation_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p decimationFactorYCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the decimation factor list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_Decimation_FactorY_GetList(peak_camera_handle hCam, uint32_t* decimationFactorYList,
    size_t* decimationFactorYCount);

/*!
 * \ingroup decimation
 * \brief Set the decimation factors
 *
 * Writes the desired pixel decimation factors.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] decimationFactorX The decimation factor in x direction to set.
 * \param[in] decimationFactorY The decimation factor in y direction to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p decimationFactorX and/or \p decimationFactorY are out of range.
 *                                      Check the range of valid values via #peak_Decimation_FactorX_GetList and
 *                                      #peak_Decimation_FactorY_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED   The decimation feature is not available for write access.
 *                                      Check the access status via #peak_Decimation_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Decimation_Set(peak_camera_handle hCam, uint32_t decimationFactorX, uint32_t decimationFactorY);

/*!
 * \ingroup decimation
 * \brief Get the decimation factors
 *
 * Reads the current pixel decimation factors.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] decimationFactorX    The decimation factor in x direction.
 * \param[out] decimationFactorY    The decimation factor in y direction.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The decimation feature is not available for read access.
 *                                          Check the access status via #peak_Decimation_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p decimationFactorX and/or \p decimationFactorY are invalid pointers.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Decimation_Get(peak_camera_handle hCam, uint32_t* decimationFactorX, uint32_t* decimationFactorY);

/*!
 * \ingroup mirror
 * \brief Query the left-right mirroring access status
 *
 * Provides the current access status for the left-right mirroring feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The left-right mirroring feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The left-right mirroring feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The left-right mirroring feature is not accessible because the GFA write access
 *                                      is enabled.
 * \return #PEAK_ACCESS_NONE            The left-right mirroring is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The left-right mirroring feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Mirror_LeftRight_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup mirror
 * \brief Enable/Disable the left-right mirroring
 *
 * Sets the left-right mirroring to enabled or disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The left-right mirroring feature is not accessible for write.
 *                                      Check the access status via #peak_Mirror_LeftRight_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Mirror_LeftRight_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup mirror
 * \brief Get the enabled status of the left-right mirroring
 *
 * Queries whether the left-right mirroring is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The left-right mirroring feature is currently enabled.
 * \return #PEAK_FALSE  The left-right mirroring feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_Mirror_LeftRight_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup mirror
 * \brief Query the up-down mirroring access status
 *
 * Provides the current access status for the up-down mirroring feature.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_ACCESS_READWRITE       The up-down mirroring feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The up-down mirroring feature is readable only.
 * \return #PEAK_ACCESS_GFA_LOCK        The up-down mirroring feature is not accessible because the GFA write access
 *                                      is enabled.
 * \return #PEAK_ACCESS_NONE            The up-down mirroring is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The up-down mirroring feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \li #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_Mirror_UpDown_GetAccessStatus(peak_camera_handle hCam);

/*!
 * \ingroup mirror
 * \brief Enable/Disable the up-down mirroring
 *
 * Sets the up-down mirroring to enabled or disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The up-down mirroring feature is not accessible for write.
 *                                      Check the access status via #peak_Mirror_UpDown_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_Mirror_UpDown_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup mirror
 * \brief Get the enabled status of the up-down mirroring
 *
 * Queries whether the up-down mirroring is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The up-down mirroring feature is currently enabled.
 * \return #PEAK_FALSE  The up-down mirroring feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_Mirror_UpDown_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup camera_memory
 * \brief peak Camera Memory Area
 *
 * A camera memory area can be used to store binary data in the cameras persistent memory.
 */
typedef enum
{
    /*! \brief Invalid memory area
     *
     * Use this value for the initialization of variables of type peak_camera_memory_area.
     */
    PEAK_CAMERA_MEMORY_AREA_INVALID     = 0,

    /*! \brief Cameras User Data 1 memory
     *
     * This memory area can be used to store binary data in the cameras persistent memory.
     */
    PEAK_CAMERA_MEMORY_AREA_USER_DATA_1 = 0x01,

    /*! \brief Cameras User Data 2 memory
     *
     * This memory area can be used to store binary data in the cameras persistent memory.
     */
    PEAK_CAMERA_MEMORY_AREA_USER_DATA_2 = 0x02

} peak_camera_memory_area;

/*!
 * \ingroup camera_memory
 * \brief Query the camera memory area access status
 *
 * Provides the current access status for the specified camera memory area.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] cameraMemoryArea  The camera memory area.
 *
 * \return #PEAK_ACCESS_READWRITE       The camera memory area can be read from and written to.
 * \return #PEAK_ACCESS_READONLY        The camera memory area can be read from only.
 * \return #PEAK_ACCESS_WRITEONLY       The camera memory area can be written to only.
 * \return #PEAK_ACCESS_GFA_LOCK        The camera memory area is not accessible because the GFA write access is
 *                                      enabled.
 * \return #PEAK_ACCESS_NONE            The camera memory area is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The camera memory area is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p cameraMemoryArea is an invalid parameter set. Check #peak_camera_memory_area.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_ACCESS_STATUS peak_CameraMemory_Area_GetAccessStatus(peak_camera_handle hCam,
    peak_camera_memory_area cameraMemoryArea);

/*!
 * \ingroup camera_memory
 * \brief Get the list of currently usable camera memory areas
 *
 * Queries the list of currently selectable camera memory areas.
 *
 * The list of usable camera memory areas may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] cameraMemoryAreaList     Pointer to a user allocated array buffer to receive the camera memory area list.
 *                                      If this parameter is NULL, \p cameraMemoryAreaCount will contain the current
 *                                      number of camera memory areas. \n
 *                                      The required size of \p cameraMemoryAreaList in bytes is
 *                                      \p cameraMemoryAreaCount x sizeof(peak_camera_memory_area).
 * \param[in,out] cameraMemoryAreaCount \li \p cameraMemoryAreaList equal NULL: \n
 *                                          out: minimal number of parameter sets \p cameraMemoryAreaList must be
 *                                               large enough to hold \n
 *                                      \li \p parameterSetList unequal NULL: \n
 *                                          in: number of camera memory areas \p cameraMemoryAreaList can hold \n
 *                                          out: number of camera memory areas filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p cameraMemoryAreaList is not NULL and the value of
 *                                          \p *cameraMemoryAreaCount is too small to receive the expected amount
 *                                          of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The camera memory feature is not supported
 *                                          or the GFA write mode is enabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraMemoryAreaCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Please consider that the camera memory area list might change between the size query call and the
 *       list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_CameraMemory_Area_GetList(peak_camera_handle hCam,
    peak_camera_memory_area* cameraMemoryAreaList, size_t* cameraMemoryAreaCount);

/*!
 * \ingroup camera_memory
 * \brief Get the size of a camera memory area
 *
 * Queries the size of the specified camera memory area.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] cameraMemoryArea      The camera memory area.
 * \param[out] cameraMemoryAreaSize The size of the camera memory area in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The camera memory area is not accessible.
 *                                          Check the access status via #peak_CameraMemory_Area_GetAccessStatus.
 *                                          Check the list of currently usable camera memory areas via
 *                                          #peak_CameraMemory_Area_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraMemoryArea is an invalid camera memory area
 *                                          or \p size is an invalid pointer.
 *                                          Check #peak_camera_memory_area.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraMemory_Area_Size_Get(peak_camera_handle hCam,
    peak_camera_memory_area cameraMemoryArea, size_t* cameraMemoryAreaSize);

/*!
 * \ingroup camera_memory
 * \brief Clear a camera memory area
 *
 * Deletes the data from the specified camera memory area.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] cameraMemoryArea  The camera memory area.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The camera memory area is not writeable.
 *                                          Check the access status via #peak_CameraMemory_Area_GetAccessStatus.
 *                                          Check the list of currently usable camera memory areas via
 *                                          #peak_CameraMemory_Area_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraMemoryArea is an invalid camera memory area.
 *                                          Check #peak_camera_memory_area.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraMemory_Area_Data_Clear(peak_camera_handle hCam,
    peak_camera_memory_area cameraMemoryArea);

/*!
 * \ingroup camera_memory
 * \brief Write to a camera memory area
 *
 * Writes the specified data to the specified camera memory area.
 * 
 * The data is written to the start of the camera memory area.
 * If \p dataSize is smaller than the capacity of the camera memory area, the remaining contents of the camera memory
 * area are cleared.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] cameraMemoryArea  The camera memory area.
 * \param[in] data              The data to write.
 * \param[in] dataSize          The size of \p *data in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The camera memory area is not writeable.
 *                                          Check the access status via #peak_CameraMemory_Area_GetAccessStatus.
 *                                          Check the list of currently usable camera memory areas via
 *                                          #peak_CameraMemory_Area_GetList.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p dataSize exceeds the size of the specified camera memory area.
 *                                          Check the size of the camera memory area via
 *                                          #peak_CameraMemory_Area_Size_Get.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraMemoryArea is an invalid camera memory area
 *                                          or \p dataSize is 0
 *                                          or \p data is an invalid pointer.
 *                                          Check #peak_camera_memory_area.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraMemory_Area_Data_Write(peak_camera_handle hCam,
    peak_camera_memory_area cameraMemoryArea, const uint8_t* data, size_t dataSize);

/*!
 * \ingroup camera_memory
 * \brief Read from the specified camera memory area
 *
 * Reads the specified data from the specified camera memory area.

 * The data is read from the start of the camera memory area.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] cameraMemoryArea  The camera memory area.
 * \param[in] data              The buffer to receive the data to.
 * \param[in] dataSize          The size of \p *data in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The camera memory area is not readable.
 *                                          Check the access status via #peak_CameraMemory_Area_GetAccessStatus.
 *                                          Check the list of currently usable camera memory areas via
 *                                          #peak_CameraMemory_Area_GetList.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p dataSize exceeds the size of the specified camera memory area.
 *                                          Check the size of the camera memory area via
 *                                          #peak_CameraMemory_Area_Size_Get.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p cameraMemoryArea is an invalid camera memory area
 *                                          or \p dataSize is 0
 *                                          or \p data is an invalid pointer.
 *                                          Check #peak_camera_memory_area.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_CameraMemory_Area_Data_Read(peak_camera_handle hCam,
    peak_camera_memory_area cameraMemoryArea, uint8_t* data, size_t dataSize);

/*!
 * \ingroup gfa
 * \brief Enable/Disable the GFA write access
 *
 * Sets the GFA write access to enabled or disabled.
 * 
 * The GFA write access is a specific mode of operation of the library. \n
 * While the library is in GFA write access mode all calls to the convenience interface, i.e. to the
 * non-GFA functions of the library, are rejected. \n
 * The GFA write access mode can be set to enabled only
 * \li if there is no running call to a convenience interface function, and
 * \li if there is no running acquisition, and
 * \li if it is not enabled already.
 * 
 * \note A write access via the GFA interface is only allowed when the GFA write access is enabled.
 * \note The use of the convenience interface is only allowed when the GFA write access is disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED   The desired GFA write access can not be set. \n
 *                                      For \p enabled == #PEAK_TRUE
 *                                      \li Make sure there is no running call to a convenience interface function.
 *                                      \li Check for the GFA write access to be enabled already via
 *                                          #peak_GFA_IsWriteAccessEnabled.
 * 
 *                                      For \p enabled == #PEAK_FALSE
 *                                      \li Check for the GFA write access to be disabled already via
 *                                          #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_EnableWriteAccess(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup gfa
 * \brief Get the enabled status of the GFA write access
 *
 * Queries whether the GFA write access is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The GFA write access is currently enabled.
 * \return #PEAK_FALSE  The GFA write access is currently disabled or the query failed.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_BOOL peak_GFA_IsWriteAccessEnabled(peak_camera_handle hCam);

/*!
 * \ingroup gfa
 * \brief peak GFA modules
 *
 * The generic feature access module specifies the GenICam module which is addressed in a generic feature access
 * function call.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
typedef enum
{
    /*! \brief Invalid GFA module
     *
     * Use this value for the initialization of variables of type peak_gfa_module.
     */
    PEAK_GFA_MODULE_INVALID         = 0,

    /*! \brief The GFA module for the access of the GenICam GenTL System module. */
    PEAK_GFA_MODULE_SYSTEM          = 0x0001,

    /*! \brief The GFA module for the access of the GenICam GenTL Interface module. */
    PEAK_GFA_MODULE_INTERFACE       = 0x0002,

    /*! \brief The GFA module for the access of the GenICam GenTL Local Device module. */
    PEAK_GFA_MODULE_LOCAL_DEVICE    = 0x0003,

    /*! \brief The GFA module for the access of the GenICam Remote Device module. */
    PEAK_GFA_MODULE_REMOTE_DEVICE   = 0x1003,

    /*! \brief The GFA module for the access of the GenICam GenTL Data Stream module. */
    PEAK_GFA_MODULE_DATA_STREAM     = 0x0004

} peak_gfa_module;

/*!
 * \ingroup gfa
 * \brief Query the access status of the feature with the given name
 *
 * Provides the current access status of the specified feature for the specified module.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] module        The addressed module.
 * \param[in] featureName   The name of the feature as a zero-terminated string.
 *
 * \return #PEAK_ACCESS_READWRITE       The feature is readable and writeable.
 * \return #PEAK_ACCESS_READONLY        The feature is readable only.
 * \return #PEAK_ACCESS_WRITEONLY       The feature is writeable only.
 * \return #PEAK_ACCESS_NONE            The feature is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The feature is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * \note Consider that a write access can only be available in the GFA write access mode.
 *       See #peak_GFA_EnableWriteAccess.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module. Check #peak_gfa_module.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_ACCESS_STATUS peak_GFA_Feature_GetAccessStatus(peak_camera_handle hCam, peak_gfa_module module,
    const char* featureName);

/*!
 * \ingroup gfa_float
 * \brief Check whether the valid values for the float feature with the given name are organized as a range
 *
 * Checks whether the valid values for the float feature with the given name are organized as a range or as a list.
 *
 * This function implements the \ref principle_valid_values_organization_query principle.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] module            The addressed module.
 * \param[in] floatFeatureName  The name of the float feature as a zero-terminated string.
 *
 * \return #PEAK_TRUE   The valid values are organized as a range. Use #peak_GFA_Float_GetRange.
 * \return #PEAK_FALSE  The valid values are organized as a list. Use #peak_GFA_Float_GetList.
 */
PEAK_API_BOOL peak_GFA_Float_HasRange(peak_camera_handle hCam, peak_gfa_module module, const char* floatFeatureName);

/*!
 * \ingroup gfa_float
 * \brief Get the current range of valid values for the float feature with the given name
 *
 * Queries the current range of valid values for the float feature with the given name.
 *
 * The range of valid values for the float feature with the given name may depend on
 * the camera configuration and the camera status.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] module            The addressed module.
 * \param[in] floatFeatureName  The name of the float feature as a zero-terminated string.
 * \param[out] minFloatValue    The minimum value for the float feature.
 * \param[out] maxFloatValue    The maximum value for the float feature.
 * \param[out] incFloatValue    The increment for the float feature.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NO_DATA             The valid values for the float feature are organized as list rather than
 *                                          as a range. \n
 *                                          Use #peak_GFA_Float_GetList to query the valid float values.
 * \return #PEAK_STATUS_ACCESS_DENIED       The float feature is not accessible.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or at least one of \p floatFeatureName, \p minFloatValue, \p maxFloatValue,
 *                                          and \p incFloatValue is an invalid pointer
 *                                          or \p floatFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Float_GetRange(peak_camera_handle hCam, peak_gfa_module module, const char* floatFeatureName,
    double* minFloatValue, double* maxFloatValue, double* incFloatValue);

/*!
 * \ingroup gfa_float
 * \brief Get the list of currently selectable values for the float feature with the given name
 *
 * Queries the list of currently selectable values for the float feature with the given name.
 *
 * The list of selectable float values may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] module            The addressed module.
 * \param[in] floatFeatureName  The name of the float feature as a zero-terminated string.
 * \param[out] floatList        Pointer to a user allocated array buffer to receive the float value list.
 *                              If this parameter is NULL, \p floatCount will contain the current number of
 *                              float values. \n
 *                              The required size of \p floatList in bytes is
 *                              \p floatCount x sizeof(double).
 * \param[in,out] floatCount    \li \p floatList equal NULL: \n
 *                                  out: minimal number of float values \p floatList must be large enough to hold \n
 *                              \li \p floatList unequal NULL: \n
 *                                  in: number of float values \p floatList can hold \n
 *                                  out: number of float values filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NO_DATA             The valid values for the float feature are organized as range rather than
 *                                          as a list. \n
 *                                          Use #peak_GFA_Float_GetRange to query the valid float values.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p floatList is not NULL and the value of \p *floatCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The float feature is not accessible.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p floatFeatureName and/or \p floatCount are invalid pointers
 *                                          or floatFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the float value list might change between the size query call and the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_GFA_Float_GetList(peak_camera_handle hCam, peak_gfa_module module, const char* floatFeatureName,
    double* floatList, size_t* floatCount);

/*!
 * \ingroup gfa_float
 * \brief Set the float feature with the given name
 *
 * Writes the desired value to the float feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] module            The addressed module.
 * \param[in] floatFeatureName  The name of the float feature as a zero-terminated string.
 * \param[in] floatValue        The float value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p floatValue is out of range.
 *                                          Check the range of valid values via
 *                                          #peak_GFA_Float_GetRange or #peak_GFA_Float_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The float feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p floatFeatureName is an invalid pointer or it is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Float_Set(peak_camera_handle hCam, peak_gfa_module module, const char* floatFeatureName,
    double floatValue);

/*!
 * \ingroup gfa_float
 * \brief Get the float feature with the given name
 *
 * Reads the current value of the float feature with the given name.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] module            The addressed module.
 * \param[in] floatFeatureName  The name of the float feature as a zero-terminated string.
 * \param[out] floatValue       The value of the float feature.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The float feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p floatFeatureName and/or \p floatValue are invalid pointers
 *                                          or \p floatFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Float_Get(peak_camera_handle hCam, peak_gfa_module module, const char* floatFeatureName,
    double* floatValue);

/*!
 * \ingroup gfa_integer
 * \brief Check whether the valid values for the integer feature with the given name are organized as a range
 *
 * Checks whether the valid values for the integer feature with the given name are organized as a range or as a list.
 *
 * This function implements the \ref principle_valid_values_organization_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] integerFeatureName    The name of the integer feature as a zero-terminated string.
 *
 * \return #PEAK_TRUE   The valid values are organized as a range. Use #peak_GFA_Integer_GetRange.
 * \return #PEAK_FALSE  The valid values are organized as a list. Use #peak_GFA_Integer_GetList.
 */
PEAK_API_BOOL peak_GFA_Integer_HasRange(peak_camera_handle hCam, peak_gfa_module module,
    const char* integerFeatureName);

/*!
 * \ingroup gfa_integer
 * \brief Get the current range of valid values for the integer feature with the given name
 *
 * Queries the current range of valid values for the integer feature with the given name.
 *
 * The range of valid values for the integer feature with the given name may depend on
 * the camera configuration and the camera status.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] integerFeatureName    The name of the integer feature as a zero-terminated string.
 * \param[out] minIntegerValue      The minimum value for the integer feature.
 * \param[out] maxIntegerValue      The maximum value for the integer feature.
 * \param[out] incIntegerValue      The increment for the integer feature.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NO_DATA             The valid values for the integer feature are organized as list rather than
 *                                          as a range. \n
 *                                          Use #peak_GFA_Integer_GetList to query the valid integer values.
 * \return #PEAK_STATUS_ACCESS_DENIED       The integer feature is not accessible.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or at least one of \p integerFeatureName, \p minIntegerValue,
 *                                          \p maxIntegerValue, and \p incIntegerValue is an invalid pointer
 *                                          or \p integerFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Integer_GetRange(peak_camera_handle hCam, peak_gfa_module module,
    const char* integerFeatureName, int64_t* minIntegerValue, int64_t* maxIntegerValue, int64_t* incIntegerValue);

/*!
 * \ingroup gfa_integer
 * \brief Get the list of currently selectable values for the integer feature with the given name
 *
 * Queries the list of currently selectable values for the integer feature with the given name.
 *
 * The list of selectable integer values may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] integerFeatureName    The name of the integer feature as a zero-terminated string.
 * \param[out] integerList          Pointer to a user allocated array buffer to receive the integer value list.
 *                                  If this parameter is NULL, \p integerCount will contain the current number of
 *                                  integer values. \n
 *                                  The required size of \p integerList in bytes is
 *                                  \p integerCount x sizeof(int64_t).
 * \param[in,out] integerCount      \li \p integerList equal NULL: \n
 *                                      out: minimal number of integer values \p integerList must be
 *                                           large enough to hold \n
 *                                  \li \p integerList unequal NULL: \n
 *                                      in: number of integer values \p integerList can hold \n
 *                                      out: number of integer values filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_NO_DATA             The valid values for the integer feature are organized as range rather than
 *                                          as a list. \n
 *                                          Use #peak_GFA_Integer_GetRange to query the valid integer values.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p integerList is not NULL and the value of \p *integerCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The integer feature is not accessible.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module.
 *                                          or \p integerFeatureName and/or \p integerCount are invalid pointers
 *                                          or integerFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the integer value list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_GFA_Integer_GetList(peak_camera_handle hCam, peak_gfa_module module,
    const char* integerFeatureName, int64_t* integerList, size_t* integerCount);

/*!
 * \ingroup gfa_integer
 * \brief Set the integer feature with the given name
 *
 * Writes the desired value to the integer feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] integerFeatureName    The name of the integer feature as a zero-terminated string.
 * \param[in] integerValue          The integer value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p integerValue is out of range.
 *                                          Check the range of valid values via
 *                                          #peak_GFA_Integer_GetRange or #peak_GFA_Integer_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The integer feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p integerFeatureName is an invalid pointer or it is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Integer_Set(peak_camera_handle hCam, peak_gfa_module module, const char* integerFeatureName,
    int64_t integerValue);

/*!
 * \ingroup gfa_integer
 * \brief Get the integer feature with the given name
 *
 * Reads the current value of the integer feature with the given name.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] integerFeatureName    The name of the integer feature as a zero-terminated string.
 * \param[out] integerValue         The value of the integer feature.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The integer feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p integerFeatureName and/or \p integerValue are invalid pointers
 *                                          or \p integerFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Integer_Get(peak_camera_handle hCam, peak_gfa_module module, const char* integerFeatureName,
    int64_t* integerValue);

/*!
 * \ingroup gfa_boolean
 * \brief Set the boolean feature with the given name
 *
 * Writes the desired value to the boolean feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] booleanFeatureName    The name of the boolean feature as a zero-terminated string.
 * \param[in] booleanValue          The boolean value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p booleanValue is out of range.
 *                                          Valid values are #PEAK_TRUE and #PEAK_FALSE.
 * \return #PEAK_STATUS_ACCESS_DENIED       The boolean feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p booleanFeatureName is an invalid pointer or it is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Boolean_Set(peak_camera_handle hCam, peak_gfa_module module, const char* booleanFeatureName,
    peak_bool booleanValue);

/*!
 * \ingroup gfa_boolean
 * \brief Get the boolean feature with the given name
 *
 * Reads the current value of the boolean feature with the given name.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] booleanFeatureName    The name of the boolean feature as a zero-terminated string.
 * \param[out] booleanValue         The value of the boolean feature.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The boolean feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p booleanFeatureName and/or \p booleanValue are invalid pointers
 *                                          or \p booleanFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Boolean_Get(peak_camera_handle hCam, peak_gfa_module module, const char* booleanFeatureName,
    peak_bool* booleanValue);

/*!
 * \ingroup gfa_string
 * \brief Set the string feature with the given name
 *
 * Writes the desired value to the string feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] module            The addressed module.
 * \param[in] stringFeatureName The name of the string feature as a zero-terminated string.
 * \param[in] stringValue       The zero-terminated string value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The string feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p stringFeatureName and/or \p stringValue are invalid pointers or
 *                                          not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_String_Set(peak_camera_handle hCam, peak_gfa_module module, const char* stringFeatureName,
    const char* stringValue);

/*!
 * \ingroup gfa_string
 * \brief Get the string feature with the given name
 *
 * Reads the current value of the string feature with the given name.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] stringFeatureName     The name of the string feature as a zero-terminated string.
 * \param[out] stringValue          Pointer to a user allocated character buffer to receive the value of
 *                                  the string feature.
 *                                  If this parameter is NULL, \p stringValueSize will contain the current
 *                                  size of the string, including the terminating 0. \n
 *                                  The required size of \p stringValue in bytes is
 *                                  \p stringValueSize x sizeof(char).
 * \param[in,out] stringValueSize   \li \p stringValue equal NULL: \n
 *                                      out: minimal number of characters \p stringValue must be large enough to hold,
 *                                           including the terminating 0 \n
 *                                  \li \p stringValue unequal NULL: \n
 *                                      in: number of characters \p stringValue can hold \n
 *                                      out: number of characters filled by the function, including the terminating 0
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p stringValue is not NULL and the value of \p *stringValueSize is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The string feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or at least one of \p stringFeatureName, \p stringValue, and
 *                                          \p stringValueSize is an invalid pointer
 *                                          or \p stringFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 *
 * \note Consider that the string value might change between the size query call and the value query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_GFA_String_Get(peak_camera_handle hCam, peak_gfa_module module, const char* stringFeatureName,
    char* stringValue, size_t* stringValueSize);

/*!
 * \ingroup gfa_command
 * \brief Execute the command feature with the given name
 *
 * Writes the execute request to the command feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] commandFeatureName    The name of the command feature as a zero-terminated string.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The command feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p commandFeatureName is an invalid pointer or it is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Command_Execute(peak_camera_handle hCam, peak_gfa_module module,
    const char* commandFeatureName);

/*!
 * \ingroup gfa_command
 * \brief Wait for the execution of the command feature with the given name to be done
 *
 * Blocks and reads the status of the execution request for the command feature with the given name
 * until it is done or a timeout occurs. \n
 * If the command has not been executed the function will immediately return with #PEAK_STATUS_SUCCESS.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] commandFeatureName    The name of the command feature as a zero-terminated string.
 * \param[in] timeout_ms            The wait timeout in milliseconds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The command feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p commandFeatureName is an invalid pointer or it is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_TIMEOUT             The wait timeout has elapsed and the command execution has
 *                                          not been indicated.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 * 
 * \note The purpose of the timeout parameter is to cancel the wait in case of a malfunction of the command mechanism.
 *       If the applications control flow depends on the command execution to be done before it proceeds it should
 *       call this function with a reasonable timeout and take action for the case that the wait times out.
 *       A pending call to this function can not be aborted.
 */
PEAK_API_STATUS peak_GFA_Command_WaitForDone(peak_camera_handle hCam, peak_gfa_module module,
    const char* commandFeatureName, uint32_t timeout_ms);

/*!
 * \ingroup gfa_enumeration
 * \brief peak GFA enumeration entry
 * 
 * The GFA enumeration entry describes an entry of an enumeration by its symbolic and its integer value. \n
 * The symbolic value is a text string which represents the enumeration entry. \n
 * The integer value is the integer number which represents the enumeration entry.
 * It is also referred to as value or index of the enumeration entry.
 */
 typedef struct
{
     /*! \brief The symbolic value of the enumeration entry as a zero-terminated string. */
     char symbolicValue[64];

     /*! \brief The integer value of the enumeration entry. */
     int64_t integerValue;

} peak_gfa_enumeration_entry;

/*!
 * \ingroup gfa_enumeration
 * \brief Get the list of currently selectable enumeration entries
 *
 * Queries the list of currently selectable enumeration entries.
 *
 * The list of selectable enumeration entries may depend on the camera configuration and the camera status.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] module                    The addressed module.
 * \param[in] enumerationFeatureName    The name of the enumeration feature as a zero-terminated string.
 * \param[out] enumerationEntryList     Pointer to a user allocated array buffer to receive the enumeration entry list.
 *                                      If this parameter is NULL, \p enumerationEntryCount will contain the current
 *                                      number of enumeration entries. \n
 *                                      The required size of \p enumerationEntryList in bytes is
 *                                      \p enumerationEntryCount x sizeof(#peak_gfa_enumeration_entry).
 * \param[in,out] enumerationEntryCount \li \p enumerationEntryList equal NULL: \n
 *                                          out: minimal number of enumeration entries \p enumerationEntryList must be
 *                                               large enough to hold \n
 *                                      \li \p enumerationEntryList unequal NULL: \n
 *                                          in: number of enumeration entries \p enumerationEntryList can hold \n
 *                                          out: number of enumeration entries filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p enumerationEntryList is not NULL and the value of
 *                                          \p *enumerationEntryCount is too small to receive the expected
 *                                          amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not accessible.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p enumerationFeatureName and/or \p enumerationEntryCount are
 *                                          invalid pointers
 *                                          or enumerationFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the enumeration entry list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_GFA_Enumeration_GetList(peak_camera_handle hCam, peak_gfa_module module,
    const char* enumerationFeatureName, peak_gfa_enumeration_entry* enumerationEntryList,
    size_t* enumerationEntryCount);

/*!
 * \ingroup gfa_enumeration
 * \brief Query the access status of the enumeration entry
 *
 * Provides the current access status of the specified enumeration entry.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] module                    The addressed module.
 * \param[in] enumerationFeatureName    The name of the enumeration feature as a zero-terminated string.
 * \param[in] enumerationEntry          The enumeration entry.
 *
 * \return #PEAK_ACCESS_READWRITE       The enumeration entry is accessible.
 * \return #PEAK_ACCESS_NONE            The enumeration entry is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The enumeration entry is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 * 
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not accessible.
 *                                      Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                      or \p enumerationFeatureName and/or \p enumerationEntry are invalid pointers
 *                                      or \p enumerationFeatureName is not zero-terminated
 *                                      or \p enumerationEntry is an invalid enumeration entry.
 *                                      Check #peak_gfa_module.
 *                                      Check for the symbolicValue of \p enumerationEntry to match the integerValue.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_ACCESS_STATUS peak_GFA_EnumerationEntry_GetAccessStatus(peak_camera_handle hCam, peak_gfa_module module,
    const char* enumerationFeatureName, const peak_gfa_enumeration_entry* enumerationEntry);

/*!
 * \ingroup gfa_enumeration
 * \brief Query the access status of the enumeration entry by its symbolic value
 *
 * Provides the current access status of the enumeration entry that is specified by its symbolic value.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] module                        The addressed module.
 * \param[in] enumerationFeatureName        The name of the enumeration feature as a zero-terminated string.
 * \param[in] enumerationEntrySymbolicValue The symbolic value of the enumeration entry as a zero-terminated string.
 *
 * \return #PEAK_ACCESS_READWRITE       The enumeration entry is accessible.
 * \return #PEAK_ACCESS_NONE            The enumeration entry is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The enumeration entry is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not accessible.
 *                                      Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                      or \p enumerationFeatureName and/or \p enumerationEntrySymbolicValue are
 *                                      invalid pointers or not zero-terminated.
 *                                      Check #peak_gfa_module.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_ACCESS_STATUS peak_GFA_EnumerationEntry_GetAccessStatusBySymbolicValue(peak_camera_handle hCam,
    peak_gfa_module module, const char* enumerationFeatureName, const char* enumerationEntrySymbolicValue);

/*!
 * \ingroup gfa_enumeration
 * \brief Query the access status of the enumeration entry by its integer value
 *
 * Provides the current access status of the enumeration entry that is specified by it's integer value.
 *
 * This function implements the \ref principle_access_status_query principle.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] module                        The addressed module.
 * \param[in] enumerationFeatureName        The name of the enumeration feature as a zero-terminated string.
 * \param[in] enumerationEntryIntegerValue  The integer value of the enumeration entry.
 *
 * \return #PEAK_ACCESS_READWRITE       The enumeration entry is accessible.
 * \return #PEAK_ACCESS_NONE            The enumeration entry is not accessible.
 * \return #PEAK_ACCESS_NOT_SUPPORTED   The enumeration entry is not supported.
 * \return #PEAK_ACCESS_INVALID         The function failed.
 *                                      Call #peak_Library_GetLastError to get the error code and description.
 *
 * If the function indicates an error by returning #PEAK_ACCESS_INVALID, these are the possible errors:
 * \li #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not accessible.
 *                                      Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \li #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                      or \p enumerationFeatureName is an invalid pointer or it is not zero-terminated.
 *                                      Check #peak_gfa_module.
 * \li #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \li #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \li #PEAK_STATUS_ERROR               An unexpected internal error occurred.
*
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_ACCESS_STATUS peak_GFA_EnumerationEntry_GetAccessStatusByIntegerValue(peak_camera_handle hCam,
    peak_gfa_module module, const char* enumerationFeatureName, int64_t enumerationEntryIntegerValue);

/*!
 * \ingroup gfa_enumeration
 * \brief Set the enumeration feature with the given name
 *
 * Writes the desired enumeration entry value to the enumeration feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] module                    The addressed module.
 * \param[in] enumerationFeatureName    The name of the enumeration feature as a zero-terminated string.
 * \param[in] enumerationEntry          The enumeration entry value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p enumerationEntry is out of range.
 *                                          Check the range of valid values via #peak_GFA_Enumeration_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p enumerationFeatureName and/or \p enumerationEntry are invalid pointers
 *                                          or enumerationFeatureName is not zero-terminated
 *                                          or \p enumerationEntry is an invalid enumeration entry.
 *                                          Check #peak_gfa_module.
 *                                          Check for the symbolicValue of \p enumerationEntry to match the
 *                                          integerValue.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Enumeration_Set(peak_camera_handle hCam, peak_gfa_module module,
    const char* enumerationFeatureName, const peak_gfa_enumeration_entry* enumerationEntry);

/*!
 * \ingroup gfa_enumeration
 * \brief Set the enumeration feature with the given name by the entries symbolic value
 *
 * Writes the desired enumeration entry value by its symbolic value to the enumeration feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] module                        The addressed module.
 * \param[in] enumerationFeatureName        The name of the enumeration feature as a zero-terminated string.
 * \param[in] enumerationEntrySymbolicValue The symbolic value of the enumeration entry to set
 *                                          as a zero-terminated string.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p enumerationEntrySymbolicValue is out of range.
 *                                          Check the range of valid values via #peak_GFA_Enumeration_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p enumerationFeatureName and/or \p enumerationEntrySymbolicValue are
 *                                          invalid pointers or not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Enumeration_SetBySymbolicValue(peak_camera_handle hCam, peak_gfa_module module,
    const char* enumerationFeatureName, const char* enumerationEntrySymbolicValue);

/*!
 * \ingroup gfa_enumeration
 * \brief Set the enumeration feature with the given name by the entries integer value
 *
 * Writes the desired enumeration entry value by its symbolic value to the enumeration feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] module                        The addressed module.
 * \param[in] enumerationFeatureName        The name of the enumeration feature as a zero-terminated string.
 * \param[in] enumerationEntryIntegerValue  The integer value of the enumeration entry to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p enumerationEntryIntegerValue is out of range.
 *                                          Check the range of valid values via #peak_GFA_Enumeration_GetList.
 * \return #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p enumerationFeatureName is an invalid pointer
 *                                          or it is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Enumeration_SetByIntegerValue(peak_camera_handle hCam, peak_gfa_module module,
    const char* enumerationFeatureName, int64_t enumerationEntryIntegerValue);

/*!
 * \ingroup gfa_enumeration
 * \brief Get the enumeration feature with the given name
 *
 * Reads the current enumeration entry value of the enumeration feature with the given name.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] module                    The addressed module.
 * \param[in] enumerationFeatureName    The name of the enumeration feature as a zero-terminated string.
 * \param[out] enumerationEntry         The current enumeration entry value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The enumeration feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p enumerationFeatureName and/or \p enumerationEntry are invalid pointers
 *                                          or enumerationFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Enumeration_Get(peak_camera_handle hCam, peak_gfa_module module,
    const char* enumerationFeatureName, peak_gfa_enumeration_entry* enumerationEntry);

/*!
 * \ingroup gfa_register
 * \brief Set the register feature with the given name
 *
 * Writes the desired value/data to the register feature with the given name.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] registerFeatureName   The name of the register feature as a zero-terminated string.
 * \param[in] registerValue         The register value/data to set.
 * \param[in] registerValueSize     The size of *registerValue in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The register feature is not available for write access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p registerFeatureName and/or \p registerValue are invalid pointers
 *                                          or \p registerFeatureName is not zero-terminated
 *                                          or \p registerValueSize is 0.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Register_Set(peak_camera_handle hCam, peak_gfa_module module, const char* registerFeatureName,
    const uint8_t* registerValue, size_t registerValueSize);

/*!
 * \ingroup gfa_register
 * \brief Get the register feature with the given name
 *
 * Reads the current value/data of the register feature with the given name.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] module                The addressed module.
 * \param[in] registerFeatureName   The name of the string feature as a zero-terminated string.
 * \param[out] registerValue        Pointer to a user allocated buffer to receive the value/data of
 *                                  the register feature.
 *                                  If this parameter is NULL, \p registerValueSize will contain the
 *                                  size of the register data. \n
 *                                  The required size of \p registerValueSize in bytes is
 *                                  \p registerValueSize x sizeof(char).
 * \param[in,out] registerValueSize \li \p registerValue equal NULL: \n
 *                                      out: minimal number of bytes \p registerValue must be large enough to hold \n
 *                                  \li \p registerValue unequal NULL: \n
 *                                      in: number of bytes \p registerValue can hold \n
 *                                      out: number of bytes filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p registerValue is not NULL and the value of \p *registerValueSize is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The string feature is not available for read access.
 *                                          Check the access status via #peak_GFA_Feature_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or at least one of \p registerFeatureName, \p registerValue, and
 *                                          \p registerValueSize is an invalid pointer
 *                                          or \p registerFeatureName is not zero-terminated.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Register_Get(peak_camera_handle hCam, peak_gfa_module module, const char* registerFeatureName,
    uint8_t* registerValue, size_t* registerValueSize);

/*!
 * \ingroup gfa_data
 * \brief Write data to the specified register address
 *
 * Writes the specified data to the specified register address.
 *
 * \note The write access is only available in the GFA write access mode. See #peak_GFA_EnableWriteAccess.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] module    The addressed module.
 * \param[in] address   The address to write the data to.
 * \param[in] data      The data to write.
 * \param[in] dataSize  The size of *data in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The write access to the specified address range was denied by the camera
 *                                          of the GFA write access mode is not enabled.
 *                                          Check for the GFA write access mode to be enabled
 *                                          via #peak_GFA_IsWriteAccessEnabled.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p data is an invalid pointer
 *                                          or \p dataSize is 0.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Data_Write(peak_camera_handle hCam, peak_gfa_module module, uint64_t address,
    const uint8_t* data, size_t dataSize);

/*!
 * \ingroup gfa_data
 * \brief Read data from the specified register address
 *
 * Reads the data from the specified register address.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] module    The addressed module.
 * \param[in] address   The address to read the data from.
 * \param[out] data     The read data.
 * \param[in] dataSize  The size of *data in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_ACCESS_DENIED       The read access to the specified address range was denied by the camera.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p module is an invalid GFA module
 *                                          or \p data is an invalid pointer
 *                                          or \p dataSize is 0.
 *                                          Check #peak_gfa_module.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * For a description of the generic feature access concept see \ref concept_generic_feature_access.
 */
PEAK_API_STATUS peak_GFA_Data_Read(peak_camera_handle hCam, peak_gfa_module module, uint64_t address, uint8_t* data,
    size_t dataSize);

/*!
 * \ingroup host_pixelformat
 * \brief Get a list of supported output pixel formats for a specific input pixelformat
 *
 * Pixelformats can only be converted to specific other pixelformats. Queries a list which pixelformats a specific
 * input pixelformat can be converted to.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam                        The camera handle.
 * \param[in] inputPixelFormat            The input pixelformat, which is to be converted
 * \param[out] outputPixelFormatList      Pointer to a user allocated array buffer to receive the list of pixelformats,
 *                                        to which to inputPixelFormat can be converted. \n
 *                                        If this parameter is NULL, \p outputPixelFormatCount will contain the
 *                                        number of possible output pixelformats. \n
 *                                        The required size of \p outputPixelFormatList in bytes is
 *                                        \p outputPixelFormatCount x sizeof(peak_pixel_format).
 * \param[in,out] outputPixelFormatCount  \li \p outputPixelFormatList equal NULL: \n
 *                                            out: minimal number of pixelformats \p outputPixelFormatList
 *                                                 must be large enough to hold \n
 *                                        \li \p outputPixelFormatList unequal NULL: \n
 *                                            in:  number of pixelformats \p hotpixelList can
 *                                                 hold \n
 *                                            out: number of pixelformats filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p outputPixelFormatList is not NULL and the value of
 *                                          \p *outputPixelFormatCount is too small to receive the expected amount of
 *                                          data.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p inputPixelFormat is an invalid pixel format
 *                                          or \p outputPixelFormatCount is an invalid pointer.
 *                                          Check #peak_pixel_format.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_PixelFormat_GetList(peak_camera_handle hCam, peak_pixel_format inputPixelFormat,
    peak_pixel_format* outputPixelFormatList, size_t* outputPixelFormatCount);

/*!
 * \ingroup host_pixelformat
 * \brief Set the output pixel format for host processing
 *
 * Writes the desired output pixel format that input frames are to be converted to with the host image processing
 * pipeline. Frames can only be converted to specific output pixel formats, depending on the frame's pixelformat. Use
 * #peak_IPL_PixelFormat_GetList check which pixelformat can be converted.
 *
 * \note Frames can only be converted to non-packed and non-grouped pixelformats, except PEAK_PIXEL_FORMAT_RGB10P32
 *       and PEAK_PIXEL_FORMAT_BGR10P32.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] pixelFormat   The pixel format to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p pixelFormat is out of range.
 *                                          Check the range of valid values via #peak_IPL_PixelFormat_GetList.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelFormat is an invalid pixel format.
 *                                          Check #peak_pixel_format.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_PixelFormat_Set(peak_camera_handle hCam, peak_pixel_format pixelFormat);

/*!
 * \ingroup host_pixelformat
 * \brief Get the output pixel format of the host processing
 *
 * Reads the current output pixel format of the host processing.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] pixelFormat  The pixel format.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p pixelFormat is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_PixelFormat_Get(peak_camera_handle hCam, peak_pixel_format* pixelFormat);

/*!
 * \ingroup host_gain
 * \brief Get the current range of valid host gain values for the specified gain channel
 *
 * Queries the current range of valid values for the host gain for the specified gain channel.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainChannel   The addressed gain channel.
 * \param[out] minGain      The minimum gain value.
 * \param[out] maxGain      The maximum gain value.
 * \param[out] incGain      The increment gain value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minGain, \p maxGain and \p incGain is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Gain_GetRange(peak_camera_handle hCam, peak_gain_channel gainChannel, double* minGain,
    double* maxGain, double* incGain);

/*!
 * \ingroup host_gain
 * \brief Set the host gain for the specified gain channel
 *
 * Writes the desired host gain value for the specified gain channel.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainChannel   The addressed gain channel.
 * \param[in] gain          The gain value to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE        \p gain is out of range.
 *                                          Check the range of valid values via #peak_Gain_GetRange.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gainChannel is an invalid gain channel.
 *                                          Check #peak_gain_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Gain_Set(peak_camera_handle hCam, peak_gain_channel gainChannel, double gain);

/*!
 * \ingroup host_gain
 * \brief Get the host gain value for the specified gain channel
 *
 * Reads the current host gain value for the specified gain channel.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] gainChannel   The addressed gain channel.
 * \param[out] gain         The gain value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gainChannel is an invalid gain channel
 *                                          or \p gain is an invalid pointer.
 *                                          Check #peak_gain_channel.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Gain_Get(peak_camera_handle hCam, peak_gain_channel gainChannel, double* gain);

/*!
 * \ingroup host_gamma
 * \brief Get the current range of valid host gamma values
 *
 * Queries the current range of valid values for the host gamma feature.
 *
 * \param[in] hCam      The camera handle.
 * \param[out] minGamma The minimum gamma value.
 * \param[out] maxGamma The maximum gamma value.
 * \param[out] incGamma The increment gamma value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minGamma, \p maxGamma and \p incGamma is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Gamma_GetRange(peak_camera_handle hCam, double* minGamma, double* maxGamma, double* incGamma);

/*!
 * \ingroup host_gamma
 * \brief Set the host gamma value
 *
 * Writes the desired host gamma value.
 *
 * \param[in] hCam  The camera handle.
 * \param[in] gamma The gamma value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p gamma value is out of range.
 *                                      Check the range of valid values via #peak_IPL_Gamma_GetRange.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Gamma_Set(peak_camera_handle hCam, double gamma);

/*!
 * \ingroup host_gamma
 * \brief Get the host gamma value
 *
 * Reads the current host gamma value.
 *
 * \param[in] hCam      The camera handle.
 * \param[out] gamma    The gamma value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p gamma is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Gamma_Get(peak_camera_handle hCam, double* gamma);

/*!
 * \ingroup host_color_correction
 * \brief Sets the cost color correction matrix.
 *
 * Writes the desired image color correction matrix.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] colorCorrectionMatrix The color correction matrix to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_ColorCorrection_Matrix_Set(peak_camera_handle hCam, peak_matrix colorCorrectionMatrix);

/*!
 * \ingroup host_color_correction
 * \brief Get the host color correction matrix
 *
 * Reads the current host color correction matrix.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] colorCorrectionMatrix    The color correction matrix.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p colorCorrectionMatrix is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_ColorCorrection_Matrix_Get(peak_camera_handle hCam, peak_matrix* colorCorrectionMatrix);

/*!
 * \ingroup host_color_correction
 * \brief Enable/Disable the host color correction
 *
 * Sets the host color correction to enabled or disabled.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_ColorCorrection_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup host_color_correction
 * \brief Get the enabled status of the host color correction
 *
 * Queries whether the host color correction is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The color correction feature is currently enabled.
 * \return #PEAK_FALSE  The color correction feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_IPL_ColorCorrection_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the current range of valid host auto brightness target values
 *
 * Queries the current range of valid values for the host auto brightness target property.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] minAutoBrightnessTarget  The minimum auto brightness target value.
 * \param[out] maxAutoBrightnessTarget  The maximum auto brightness target value.
 * \param[out] incAutoBrightnessTarget  The auto brightness target value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessTarget, \p maxAutoBrightnessTarget, and
 *                                          \p incAutoBrightnessTarget is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Target_GetRange(peak_camera_handle hCam, uint32_t* minAutoBrightnessTarget,
    uint32_t* maxAutoBrightnessTarget, uint32_t* incAutoBrightnessTarget);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto brightness target value
 *
 * Writes the desired host auto brightness target value.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoBrightnessTarget  The auto brightness target value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessTarget value is out of range.
 *                                      Check the range of valid values via #peak_IPL_AutoBrightness_Target_GetRange.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Target_Set(peak_camera_handle hCam, uint32_t autoBrightnessTarget);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto brightness target value
 *
 * Reads the current host auto brightness target value.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoBrightnessTarget The auto brightness target value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessTarget is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Target_Get(peak_camera_handle hCam, uint32_t* autoBrightnessTarget);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the current range of valid host auto brightness target tolerance values
 *
 * Queries the current range of valid values for the host auto brightness target tolerance property.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] minAutoBrightnessTargetTolerance The minimum auto brightness target tolerance value.
 * \param[out] maxAutoBrightnessTargetTolerance The maximum auto brightness target tolerance value.
 * \param[out] incAutoBrightnessTargetTolerance The auto brightness target tolerance value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessTargetTolerance,
 *                                          \p maxAutoBrightnessTargetTolerance, and \p incAutoBrightnessTargetTolerance
 *                                          is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_TargetTolerance_GetRange(peak_camera_handle hCam,
    uint32_t* minAutoBrightnessTargetTolerance, uint32_t* maxAutoBrightnessTargetTolerance,
    uint32_t* incAutoBrightnessTargetTolerance);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto brightness target tolerance value
 *
 * Writes the desired host auto brightness target tolerance value.
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] autoBrightnessTargetTolerance The auto brightness target tolerance value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessTargetTolerance value is out of range.
 *                                      Check the range of valid values via
 *                                      #peak_IPL_AutoBrightness_TargetTolerance_GetRange.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_TargetTolerance_Set(peak_camera_handle hCam,
    uint32_t autoBrightnessTargetTolerance);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto brightness target tolerance value
 *
 * Reads the current host auto brightness target tolerance value.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] autoBrightnessTargetTolerance    The auto brightness target tolerance value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessTargetTolerance is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_TargetTolerance_Get(peak_camera_handle hCam,
    uint32_t* autoBrightnessTargetTolerance);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the current range of valid host auto brightness target percentile values
 *
 * Queries the current range of valid values for the host auto brightness target percentile property.
 *
 * \param[in] hCam                                  The camera handle.
 * \param[out] minAutoBrightnessTargetPercentile    The minimum auto brightness target percentile value.
 * \param[out] maxAutoBrightnessTargetPercentile    The maximum auto brightness target percentile value.
 * \param[out] incAutoBrightnessTargetPercentile    The auto brightness target percentile value increment.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessTargetPercentile,
 *                                                  \p maxAutoBrightnessTargetPercentile, and
 *                                                  \p incAutoBrightnessTargetPercentile is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_TargetPercentile_GetRange(peak_camera_handle hCam,
    double* minAutoBrightnessTargetPercentile, double* maxAutoBrightnessTargetPercentile,
    double* incAutoBrightnessTargetPercentile);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto brightness target percentile value
 *
 * Writes the desired host auto brightness target percentile value.
 *
 * \param[in] hCam                              The camera handle.
 * \param[in] autoBrightnessTargetPercentile    The auto brightness target percentile value to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessTargetPercentile value is out of range.
 *                                              Check the range of valid values via
 *                                              #peak_IPL_AutoBrightness_TargetPercentile_GetRange.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_TargetPercentile_Set(peak_camera_handle hCam,
    double autoBrightnessTargetPercentile);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto brightness target percentile value
 *
 * Reads the current host auto brightness target percentile value.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] autoBrightnessTargetPercentile   The auto brightness target percentile value.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessTargetPercentile is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_TargetPercentile_Get(peak_camera_handle hCam,
    double* autoBrightnessTargetPercentile);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto brightness ROI mode
 *
 * Writes the desired host auto brightness ROI mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoBrightnessROIMode The auto brightness ROI mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessROIMode is an invalid auto feature ROI mode.
 *                                          Check #peak_auto_feature_roi_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Mode_Set(peak_camera_handle hCam,
    peak_auto_feature_roi_mode autoBrightnessROIMode);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto brightness ROI mode
 *
 * Reads the current host auto brightness ROI mode.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] autoBrightnessROIMode    The current auto brightness ROI mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessROIMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Mode_Get(peak_camera_handle hCam,
    peak_auto_feature_roi_mode* autoBrightnessROIMode);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the current range of valid host auto brightness ROI offsets
 *
 * Queries the current range of valid values for the host auto brightness ROI offset.
 *
 * In special the current setting of the image ROI and the current setting of the host auto brightness ROI size has an impact
 * on the range of valid host auto brightness ROI offset values.
 *
 * \param[in] hCam                          The camera handle.
 * \param[out] minAutoBrightnessROIOffset   The minimum auto brightness ROI offset values.
 * \param[out] maxAutoBrightnessROIOffset   The maximum auto brightness ROI offset values.
 * \param[out] incAutoBrightnessROIOffset   The auto brightness ROI offset values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessROIOffset, \p maxAutoBrightnessROIOffset
 *                                          and \p incAutoBrightnessROIOffset is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Offset_GetRange(peak_camera_handle hCam,
                                                                          peak_position* minAutoBrightnessROIOffset, peak_position* maxAutoBrightnessROIOffset,
                                                                          peak_position* incAutoBrightnessROIOffset);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the current range of valid host auto brightness ROI sizes
 *
 * Queries the current range of valid values for the host auto brightness ROI dimensions.
 *
 * In special the current setting of the image ROI and the current setting of the host auto brightness ROI offset has an
 * impact on the range of valid host auto brightness ROI size values.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] minAutoBrightnessROISize The minimum auto brightness ROI size values.
 * \param[out] maxAutoBrightnessROISize The maximum auto brightness ROI size values.
 * \param[out] incAutoBrightnessROISize The auto brightness ROI size values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoBrightnessROISize, \p maxAutoBrightnessROISize
 *                                          and \p incAutoBrightnessROISize is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Size_GetRange(peak_camera_handle hCam, peak_size* minAutoBrightnessROISize,
                                                                        peak_size* maxAutoBrightnessROISize, peak_size* incAutoBrightnessROISize);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto brightness ROI
 *
 * Writes the desired host auto brightness ROI.
 *
 * \note Setting the auto brightness ROI is only possible if #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL is set for the
 *       auto brightness ROI mode..
 * \note The range of valid ROIs for the auto brightness feature is the range of valid image ROIs.
 *       It can be queried via #peak_IPL_AutoBrightness_ROI_Offset_GetRange and #peak_IPL_AutoBrightness_ROI_Size_GetRange.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] autoBrightnessROI The auto brightness ROI to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoBrightnessROI value is out of range.
 *                                      Check the range of valid values via #peak_IPL_AutoBrightness_ROI_Offset_GetRange and
 *                                      #peak_IPL_AutoBrightness_ROI_Size_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto brightness ROI mode is not set to #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL.
 *                                              Check the auto brightness ROI mode via #peak_IPL_AutoBrightness_ROI_Mode_Get.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Set(peak_camera_handle hCam, peak_roi autoBrightnessROI);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto brightness ROI
 *
 * Reads the current host auto brightness ROI.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoBrightnessROI    The auto brightness ROI.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoBrightnessROI is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_ROI_Get(peak_camera_handle hCam, peak_roi* autoBrightnessROI);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto exposure control mode
 *
 * Writes the desired host auto exposure control mode.
 *
 * \param[in] hCam              The camera handle.
 * \param[in] autoExposureMode  The auto exposure control mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoExposureMode is an invalid auto feature mode.
 *                                                  Check #peak_auto_feature_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Exposure_Mode_Set(peak_camera_handle hCam,
    peak_auto_feature_mode autoExposureMode);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto exposure control mode
 *
 * Reads the current host auto exposure control mode.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] autoExposureMode The current auto exposure control mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoExposureMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Exposure_Mode_Get(peak_camera_handle hCam,
    peak_auto_feature_mode* autoExposureMode);

/*!
 * \ingroup host_auto_brightness
 * \brief Set the host auto gain control mode
 *
 * Writes the desired host auto gain control mode.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] autoGainMode  The auto gain control mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoGainMode is an invalid auto feature mode.
 *                                                  Check #peak_auto_feature_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Gain_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoGainMode);

/*!
 * \ingroup host_auto_brightness
 * \brief Get the host auto gain control mode
 *
 * Reads the current host auto gain control mode.
 *
 * \param[in] hCam          The camera handle.
 * \param[out] autoGainMode The current auto gain control mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoGainMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoBrightness_Gain_Mode_Get(peak_camera_handle hCam, peak_auto_feature_mode* autoGainMode);

/*!
 * \ingroup host_auto_white_balance
 * \brief Set the host auto white balance ROI mode
 *
 * Writes the desired host auto white balance ROI mode.
 *
 * \param[in] hCam                      The camera handle.
 * \param[in] autoWhiteBalanceROIMode   The auto white balance ROI mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceROIMode is an invalid auto feature ROI mode.
 *                                          Check #peak_auto_feature_roi_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Mode_Set(peak_camera_handle hCam,
    peak_auto_feature_roi_mode autoWhiteBalanceROIMode);

/*!
 * \ingroup host_auto_white_balance
 * \brief Get the host auto white balance ROI mode
 *
 * Reads the current host auto white balance ROI mode.
 *
 * \param[in] hCam                      The camera handle.
 * \param[out] autoWhiteBalanceROIMode  The current auto white balance ROI mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceROIMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Mode_Get(peak_camera_handle hCam,
    peak_auto_feature_roi_mode* autoWhiteBalanceROIMode);

/*!
 * \ingroup host_auto_white_balance
 * \brief Get the current range of valid host auto white balance ROI offsets
 *
 * Queries the current range of valid values for the host auto white balance ROI offset.
 *
 * In special the current setting of the image ROI and the current setting of the host auto white balance ROI size has an impact
 * on the range of valid host auto white balance ROI offset values.
 *
 * \param[in] hCam                            The camera handle.
 * \param[out] minAutoWhiteBalanceROIOffset   The minimum auto white balance ROI offset values.
 * \param[out] maxAutoWhiteBalanceROIOffset   The maximum auto white balance ROI offset values.
 * \param[out] incAutoWhiteBalanceROIOffset   The auto white balance ROI offset values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoWhiteBalanceROIOffset, \p maxAutoWhiteBalanceROIOffset
 *                                          and \p incAutoWhiteBalanceROIOffset is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange(peak_camera_handle hCam,
                                                                            peak_position* minAutoWhiteBalanceROIOffset, peak_position* maxAutoWhiteBalanceROIOffset,
                                                                            peak_position* incAutoWhiteBalanceROIOffset);

/*!
 * \ingroup host_auto_white_balance
 * \brief Get the current range of valid host auto white balance ROI sizes
 *
 * Queries the current range of valid values for the host auto white balance ROI dimensions.
 *
 * In special the current setting of the image ROI and the current setting of the host auto brightness ROI offset has an
 * impact on the range of valid host auto brightness ROI size values.
 *
 * \param[in] hCam                        The camera handle.
 * \param[out] minAutoWhiteBalanceROISize The minimum auto white balance ROI size values.
 * \param[out] maxAutoWhiteBalanceROISize The maximum auto white balance ROI size values.
 * \param[out] incAutoWhiteBalanceROISize The auto white balance ROI size values increments.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   At least one of \p minAutoWhiteBalanceROISize, \p maxAutoWhiteBalanceROISize,
 *                                          and \p incAutoWhiteBalanceROISize is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Size_GetRange(peak_camera_handle hCam, peak_size* minAutoWhiteBalanceROISize,
                                                                          peak_size* maxAutoWhiteBalanceROISize, peak_size* incAutoWhiteBalanceROISize);

/*!
 * \ingroup host_auto_white_balance
 * \brief Set the host auto white balance ROI
 *
 * Writes the desired host auto white balance ROI.
 *
 * \note Setting the auto white balance ROI is only possible if #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL is set for the
 *       auto white balance ROI mode.
 * \note The range of valid ROIs for the auto white balance feature is the range of valid image ROIs.
 *       It can be queried via #peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange and #peak_IPL_AutoWhiteBalance_ROI_Size_GetRange.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoWhiteBalanceROI   The auto white balance ROI to set.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_OUT_OF_RANGE    \p autoWhiteBalanceROI value is out of range.
 *                                      Check the range of valid values via #peak_IPL_AutoWhiteBalance_ROI_Offset_GetRange and
 *                                      #peak_IPL_AutoWhiteBalance_ROI_Size_GetRange.
 * \return #PEAK_STATUS_ACCESS_DENIED   The auto white balance ROI mode is not set to
 *                                      #PEAK_AUTO_FEATURE_ROI_MODE_MANUAL.
 *                                      Check the auto white balance ROI mode via
 *                                      #peak_IPL_AutoWhiteBalance_ROI_Mode_Get.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Set(peak_camera_handle hCam, peak_roi autoWhiteBalanceROI);

/*!
 * \ingroup host_auto_white_balance
 * \brief Get the host auto white balance ROI
 *
 * Reads the current host auto white balance ROI.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoWhiteBalanceROI  The auto white balance ROI.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceROI is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_ROI_Get(peak_camera_handle hCam, peak_roi* autoWhiteBalanceROI);

/*!
 * \ingroup host_auto_white_balance
 * \brief Set the host auto white balance control mode
 *
 * Writes the desired host auto white balance control mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[in] autoWhiteBalanceMode  The auto white balance control mode to set.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceMode is an invalid auto feature mode.
 *                                          Check #peak_auto_feature_mode.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_Mode_Set(peak_camera_handle hCam, peak_auto_feature_mode autoWhiteBalanceMode);

/*!
 * \ingroup host_auto_white_balance
 * \brief Get the host auto white balance control mode
 *
 * Reads the current host auto white balance control mode.
 *
 * \param[in] hCam                  The camera handle.
 * \param[out] autoWhiteBalanceMode The current auto white balance control mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p autoWhiteBalanceMode is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_AutoWhiteBalance_Mode_Get(peak_camera_handle hCam,
    peak_auto_feature_mode* autoWhiteBalanceMode);

/*!
 * \ingroup host_hotpixel
 * \brief peak hotpixel correction sensitivity level
 *
 * Higher sensitivity levels mean more hotpixels will be detected and corrected, but can also lead to more
 * false-positives.
 */
typedef enum
{
    /*! \brief Invalid hotpixel correction sensitivity level
     *
     * Use this value for the initialization of variables of type peak_hotpixel_correction_sensitivity.
     */
    PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_INVALID    = 0,

    /*! \brief hotpixel correction sensitivity level 1
     *
     * This is the lowest sensitivity level, detecting the fewest hotpixels, therefore may miss more hotpixels,
     * creating more false-negatives.
     */
    PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_1    = 0x0001,

    /*! \brief hotpixel correction sensitivity level 2 */
    PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_2    = 0x0002,

    /*! \brief hotpixel correction sensitivity level 3
     *
     * This is the default sensitivity level.
     */
    PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_3    = 0x0003,

    /*! \brief hotpixel correction sensitivity level 4 */
    PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_4    = 0x0004,

    /*! \brief hotpixel correction sensitivity level 5
     *
     * This is the highest sensitivity level, detecting the most hotpixels, but may create more false-positives.
     */
    PEAK_HOTPIXEL_CORRECTION_SENSITIVITY_LEVEL_5    = 0x0005

} peak_hotpixel_correction_sensitivity;

/*!
 * \ingroup host_hotpixel
 * \brief Set the host hotpixel correction sensitivity level
 *
 * Sets the specified host hotpixel correction sensitivity level. Setting the sensitivity also resets already detected
 * hotpixel positions, so they are automatically detected again, with the new sensitivity
 * (see #peak_IPL_HotpixelCorrection_ResetList).
 *
 * \param[in] hCam                          The camera handle.
 * \param[in] hotpixelCorrectionSensitivity The hotpixel correction sensitivity level.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p hotpixelCorrectionSensitivity is an invalid hotpixel correction
 *                                          sensitivity.
 *                                          Check #peak_hotpixel_correction_sensitivity.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_HotpixelCorrection_Sensitivity_Set(peak_camera_handle hCam,
    peak_hotpixel_correction_sensitivity hotpixelCorrectionSensitivity);

/*!
 * \ingroup host_hotpixel
 * \brief Get the host hotpixel correction sensitivity level
 *
 * Reads the current host hotpixel correction sensitivity level.
 *
 * \param[in] hCam                              The camera handle.
 * \param[out] hotpixelCorrectionSensitivity    The color correction mode.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p hotpixelCorrectionSensitivity is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_HotpixelCorrection_Sensitivity_Get(peak_camera_handle hCam,
    peak_hotpixel_correction_sensitivity* hotpixelCorrectionSensitivity);

/*!
 * \ingroup host_hotpixel
 * \brief Get the list of detected host hotpixel correction positions/pixels.
 *
 * Queries the list of detected host hotpixel correction positions/pixels.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] hCam              The camera handle.
 * \param[out] hotpixelList     Pointer to a user allocated array buffer to receive the hotpixel positions list. \n
 *                              If this parameter is NULL, \p hotpixelCount will contain the current number of
 *                              hotpixel positions. \n
 *                              The required size of \p hotpixelList in bytes is
 *                              \p hotpixelCount x sizeof(peak_position).
 * \param[in,out] hotpixelCount \li \p hotpixelList equal NULL: \n
 *                                  out: minimal number of hotpixel positions \p hotpixelList must be large enough to
 *                                       hold \n
 *                              \li \p hotpixelList unequal NULL: \n
 *                                  in:  number of hotpixel positions \p hotpixelList can hold \n
 *                                  out: number of hotpixel positions filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p hotpixelList is not NULL and the value of \p *hotpixelCount is too small
 *                                          to receive the expected amount of data.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p hotpixelCount is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Please consider that the hotpixel positions list might change between the size query call and
 *       the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_IPL_HotpixelCorrection_GetList(peak_camera_handle hCam, peak_position* hotpixelList,
    size_t* hotpixelCount);

/*!
 * \ingroup host_hotpixel
 * \brief Set the list of host hotpixel positions
 *
 * Sets the list of hotpixel positions that should be corrected.
 *
 * By default, the host hotpixel correction automatically detects and corrects hotpixels. This function
 * overwrites the automatically detected hotpixel positions, so custom values can be used for the hotpixel correction.
 *
 * \param[in] hCam          The camera handle.
 * \param[in] hotpixelList  The positions that should be used in the hotpixel correction.
 * \param[in] hotpixelCount The number of hotpixel positions \p hotpixelList holds.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p hotpixelList is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_HotpixelCorrection_SetList(peak_camera_handle hCam, peak_position* hotpixelList,
    size_t hotpixelCount);

/*!
 * \ingroup host_hotpixel
 * \brief Reset the list of host hotpixel positions.
 *
 * Resets the list of hotpixel positions that should be corrected, so they are automatically detected again.
 *
 * By default, the host hotpixel correction automatically detects the hotpixel positions once and uses these positions
 * for the hotpixel correction in the following images. This function resets/clears these positions, so they are
 * automatically detected again.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_HotpixelCorrection_ResetList(peak_camera_handle hCam);

/*!
 * \ingroup host_hotpixel
 * \brief Enable/Disable the host hotpixel correction
 *
 * Sets the host hotpixel correction to enabled or disabled.
 * Hotpixel correction is supported for bayer and mono input images.
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_HotpixelCorrection_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup host_hotpixel
 * \brief Get the enabled status of the host hotpixel correction
 *
 * Queries whether the host hotpixel correction is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The host hotpixel correction feature is currently enabled.
 * \return #PEAK_FALSE  The host hotpixel correction feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_IPL_HotpixelCorrection_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup host_mirror
 * \brief Enable/Disable the up-down host mirroring
 *
 * Sets the up-down host mirroring to enabled or disabled.
 * Mirroring a bayer pixel format changes the format, therefore we recommend processing to a RGB format
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Mirror_UpDown_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup host_mirror
 * \brief Get the enabled status of the up-down host mirroring
 *
 * Queries whether the up-down host mirroring is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The up-down mirroring feature is currently enabled.
 * \return #PEAK_FALSE  The up-down mirroring feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_IPL_Mirror_UpDown_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup host_mirror
 * \brief Enable/Disable the left-right host mirroring
 *
 * Sets the left-right host mirroring to enabled or disabled.
 * Mirroring a bayer pixel format changes the format, therefore we recommend processing to a RGB format
 *
 * \param[in] hCam      The camera handle.
 * \param[in] enabled   The desired enabled status. #PEAK_TRUE for enabled, #PEAK_FALSE for disabled.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hCam is an invalid camera handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_Mirror_LeftRight_Enable(peak_camera_handle hCam, peak_bool enabled);

/*!
 * \ingroup host_mirror
 * \brief Get the enabled status of the left-right host mirroring
 *
 * Queries whether the left-right host mirroring is currently enabled or disabled.
 *
 * This function implements the \ref principle_enabled_status_query principle.
 *
 * \param[in] hCam The camera handle.
 *
 * \return #PEAK_TRUE   The left-right mirroring feature is currently enabled.
 * \return #PEAK_FALSE  The left-right mirroring feature is currently disabled or the query failed.
 */
PEAK_API_BOOL peak_IPL_Mirror_LeftRight_IsEnabled(peak_camera_handle hCam);

/*!
 * \ingroup host_features
 * \brief Process a frame with the host image processing pipeline and store the result in a new frame.
 * 
 * Processes a frame with the host image processing pipeline and stores the result in a new frame. The host image 
 * processing pipeline can be configured with functions in the \ref host_features group.
 * 
 * The new frames create by this function are stored in the hResultFrame parameter. These frames must be released via 
 * #peak_Frame_Release.
 * 
 * \param[in] hCam           The camera handle.
 * \param[in] hFrame         Handle to the input frame.
 * \param[out] hResultFrame  Handle to the processed output frame.
 * 
 * \return #PEAK_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_CONFIGURATION   The image processing pipeline was misconfigured and can't apply the 
 *                                              required operations on the input image. Check the last error for more 
 *                                              information.
 * \return #PEAK_STATUS_INVALID_PARAMETER       \p hResultFrame is an invalid pointer.
 * \return #PEAK_STATUS_INVALID_HANDLE          \p hFrame and/or \p hCam are invalid handles.
 * \return #PEAK_STATUS_NOT_INITIALIZED         The library is not initialized.
 * \return #PEAK_STATUS_ERROR                   An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_ProcessFrame(peak_camera_handle hCam, peak_frame_handle hFrame,
    peak_frame_handle* hResultFrame);

/*!
 * \ingroup host_features
 * \brief Process a frame with the host image processing pipeline and replace the original frame.
 * 
 * Processes a frame with the host image processing pipeline and replaces the original frame. The host image 
 * processing pipeline can be configured with functions in the \ref host_features group.
 * 
 * \note Since debayered images require more memory than the corresponding Bayer image, it's not possible to convert 
 *       from Bayer formats to RGB(a)/BGR(a) with this in-place function.
 * 
 * The hFrame must still be released via #peak_Frame_Release.
 * 
 * \param[in] hCam      The camera handle.
 * \param[in] hFrame    Handle to the input frame.
 * 
 * \return #PEAK_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_CONFIGURATION   The image processing pipeline was misconfigured and can't apply the 
 *                                              required operations on the input image. Check the last error for more 
 *                                              information.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL        The image processing pipeline is configured for debayering, which 
 *                                              can't be done in-place.
 * \return #PEAK_STATUS_INVALID_HANDLE          \p hFrame and/or \p hCam are invalid handles.
 * \return #PEAK_STATUS_NOT_INITIALIZED         The library is not initialized.
 * \return #PEAK_STATUS_ERROR                   An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_IPL_ProcessFrameInplace(peak_camera_handle hCam, peak_frame_handle hFrame);

/*!
 * \ingroup video
 * \brief peak Video handle
 *
 * The video handle repesents an opened video handle. \n
 * The video handle is provided by the #peak_VideoWriter_Open function
 * and must be released by #peak_VideoWriter_Close. \n
 * The video handle is required in every function which controls a video stream.
 *
 * The value for an invalid camera handle is #PEAK_INVALID_HANDLE.
 */
typedef struct peak_video* peak_video_handle;

/*!
 * \ingroup video
 * \brief peak Encoder types
 *
 * The encoder specifies the used video compression.
 */
typedef enum
{
    /*! \brief Invalid encoder
     *
     * Use this value for the initialization of variables of type peak_video_encoder.
     */
    PEAK_VIDEO_ENCODER_INVALID = 0x0,

    /*! \brief Motion JPEG */
    PEAK_VIDEO_ENCODER_MJPEG   = 0x1

} peak_video_encoder;

/*!
 * \ingroup video
 * \brief peak Container types
 *
 * The container specifies the used file format for saving the video.
 */
typedef enum
{
    /*! \brief Invalid container
     *
     * Use this value for the initialization of variables of type peak_video_container.
     */
    PEAK_VIDEO_CONTAINER_INVALID = 0x0,

    /*! \brief Audio Video Interleave */
    PEAK_VIDEO_CONTAINER_AVI     = 0x1

} peak_video_container;

/*!
 * \ingroup video
 * \brief Opens a video file with the given file name.
 * 
 * \param[out] hVideo   The video handle.
 * \param[in] fileName  The given file name to use as an utf-8 encoded string
 * \param[in] container The container of the video.
 * \param[in] encoder   The encoder of the video.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p hVideo and/or \p fileName are invalid pointers.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ACCESS_DENIED       A file with the given file name already exists or can not be locked.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_VideoWriter_Open(peak_video_handle* hVideo, const char* fileName, 
    peak_video_container container, peak_video_encoder encoder);

/*!
 * \ingroup video
 * \brief Closes a video file.
 * 
 * \param[in] hVideo The video handle.
 *
 * \return #PEAK_STATUS_SUCCESS         Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE  \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_STATUS_ERROR           An unexpected internal error occurred.
 * 
 * \note The video handle is no longer valid after the function has returned.
 */
PEAK_API_STATUS peak_VideoWriter_Close(peak_video_handle hVideo);

/*!
 * \ingroup video
 * \brief Writes a image frame into the video file.
 * 
 * \param[in] hVideo   The video handle.
 * \param[in] hFrame   A frame handle.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle or \p hFrame is an invalid frame handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_INVALID_PARAMETER   The configured container or encoder are not valid for the given frame.
 * \return #PEAK_STATUS_BUSY                The internal image queue is full.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 */
PEAK_API_STATUS peak_VideoWriter_AddFrame(peak_video_handle hVideo, peak_frame_handle hFrame);

/*!
 * \ingroup video
 * \brief Get the list of currently usable encoders
 *
 * Queries the list of currently selectable encoders for the given container.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] container         Container 
 * \param[out] encoderList      Pointer to a user allocated array buffer to receive the encoder type list.
 *                              If this parameter is NULL, \p encoderCount will contain the current
 *                              number of encoder types. \n
 *                              The required size of \p encoderList in bytes is
 *                              \p encoderCount x sizeof(peak_video_encoder).
 * \param[in,out] encoderCount  \li \p encoderList equal NULL: \n
 *                                  out: minimal number of encoder types \p encoderList must be
 *                                      large enough to hold \n
 *                              \li \p encoderList unequal NULL: \n
 *                                  in: number of encoder types \p encoderList can hold \n
 *                                  out: number of encoder types filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p encoderList is not NULL and the value of \p *encoderCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p encoder is an invalid container or \p encoderCount is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_VideoWriter_Container_GetEncoderList(peak_video_container container, 
    peak_video_encoder* encoderList, size_t* encoderCount);

/*!
 * \ingroup pixelformat
 * \brief Get the list of currently selectable pixel formats
 *
 * Queries the list of currently selectable pixel formats.
 *
 * The list of selectable pixel formats may depend on the given encoder.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] encoder               Encoder
 * \param[out] pixelFormatList      Pointer to a user allocated array buffer to receive the pixel format list.
 *                                  If this parameter is NULL, \p pixelFormatCount will contain the current
 *                                  number of pixel formats. \n
 *                                  The required size of \p pixelFormatList in bytes is
 *                                  \p pixelFormatCount x sizeof(#peak_pixel_format).
 * \param[in,out] pixelFormatCount  \li \p pixelFormatList equal NULL: \n
 *                                      out: minimal number of pixel formats \p pixelFormatList must be
 *                                           large enough to hold \n
 *                                  \li \p pixelFormatList unequal NULL: \n
 *                                      in: number of pixel formats \p pixelFormatList can hold \n
 *                                      out: number of pixel formats filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p pixelFormatList is not NULL and the value of \p *pixelFormatCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_ACCESS_DENIED       The pixel format feature is not accessible.
 *                                          Check the access status of the pixel format feature via
 *                                          #peak_PixelFormat_GetAccessStatus.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p encoder is an invalid encoder or \p pixelFormatCount is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 * \note Consider that the pixel format list might change between the size query call and the list query call. \n
 *       This may be the case if the camera configuration or the camera status have changed in the time between
 *       the two function calls.
 */
PEAK_API_STATUS peak_VideoWriter_Encoder_GetPixelFormatList(peak_video_encoder encoder, 
    peak_pixel_format* pixelFormatList, size_t* pixelFormatCount);

/*!
 * \ingroup video
 * \brief Get the list of currently usable containers
 *
 * Queries the list of currently selectable containers.
 *
 * This function implements the \ref principle_two_stage_query principle.
 *
 * \param[in] encoder               Encoder
 * \param[out] containerList        Pointer to a user allocated array buffer to receive the container type list.
 *                                  If this parameter is NULL, \p containerCount will contain the current
 *                                  number of container types. \n
 *                                  The required size of \p containerList in bytes is
 *                                  \p containerCount x sizeof(peak_video_container).
 * \param[in,out] containerCount    \li \p containerList equal NULL: \n
 *                                      out: minimal number of container types \p containerList must be
 *                                          large enough to hold \n
 *                                  \li \p containerList unequal NULL: \n
 *                                      in: number of container types \p containerList can hold \n
 *                                      out: number of container types filled by the function
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_BUFFER_TOO_SMALL    \p containerList is not NULL and the value of \p *containerCount is
 *                                          too small to receive the expected amount of data.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p encoder is an invalid encoder or \p containerCount is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 */
PEAK_API_STATUS peak_VideoWriter_Encoder_GetContainerList(peak_video_encoder encoder, 
    peak_video_container* containerList, size_t* containerCount);

/*!
 * \ingroup video
 * \brief video info structure
 *
 * Holds information about the processed video.
 * 
 */
typedef struct
{
    /* \brief Overall encoded frames */
    uint64_t encodedFrames;

    /* \brief Overall dropped frames */
    uint64_t droppedFrames;

    /* \brief Current file size in bytes */
    uint64_t fileSize;
    
    uint8_t reserved[256];
} peak_video_info;

/*!
 * \ingroup video
 * \brief Get information from the video stream.
 * 
 * \param[in] hVideo        The video handle.
 * \param[out] videoInfo    Video information.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p videoInfo is an invalid pointer.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 */
PEAK_API_STATUS peak_VideoWriter_GetInfo(peak_video_handle hVideo, peak_video_info* videoInfo);

/*!
 * \ingroup video
 * \brief peak container options
 *
 * The container can be configured via the given options.
 */
typedef enum
{
    /*! \brief Invalid container option
     *
     * Use this value for the initialization of variables of type peak_video_container_option.
     */
    PEAK_VIDEO_CONTAINER_OPTION_INVALID = 0x0,

    /*! \brief Framerate container option
     *
     * Use this option to set or retrieve the frame rate of the avi container. Given value must be an double.
     */
    PEAK_VIDEO_CONTAINER_OPTION_FRAMERATE = 0x1

} peak_video_container_option;

/*!
 * \ingroup video
 * \brief peak container options
 *
 * The encoder can be configured via the given options.
 */
typedef enum
{
    /*! \brief Invalid encoder option
     *
     * Use this value for the initialization of variables of type peak_video_encoder_option.
     */
    PEAK_VIDEO_ENCODER_OPTION_INVALID = 0x0,

    /*! \brief Quality encoder option
     *
     * Use this option to set or retrieve the quality of the mjpeg encoder. Given value must be an int32_t.
     */
    PEAK_VIDEO_ENCODER_OPTION_QUALITY = 0x1

} peak_video_encoder_option;

/*!
 * \ingroup video
 * \brief Set additional container options
 * 
 * \param[in] hVideo            The video handle.
 * \param[in] containerOption   Container option to set see \ref peak_video_container_option
 * \param[in] value             see \ref peak_video_container_option
 * \param[in] count             size of \p value in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p containerOption is an invalid option or \p value is an invalid pointer
                                            or the size of \p count is incorrect.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 */
PEAK_API_STATUS peak_VideoWriter_Container_Option_Set(
    peak_video_handle hVideo, peak_video_container_option containerOption, const void* value, size_t count);

/*!
 * \ingroup video
 * \brief Get container options
 * 
 * \param[in]  hVideo            The video handle.
 * \param[in]  containerOption   Container option to retrieve see \ref peak_video_container_option
 * \param[out] value             see \ref peak_video_container_option for possible values
 * \param[in]  count             size of \p value in bytes.
 * \param[out] outCount          size of written data in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p containerOption is an invalid option or \p value is an invalid pointer
                                            or the size of \p count is incorrect.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 */
PEAK_API_STATUS peak_VideoWriter_Container_Option_Get(
    peak_video_handle hVideo, peak_video_container_option containerOption, void* value, size_t count, size_t* outCount);

/*!
 * \ingroup video
 * \brief Set additional encoder options
 * 
 * \param[in] hVideo            The video handle.
 * \param[in] encoderOption     Encoder option to set see \ref peak_video_encoder_option
 * \param[in] value             see \ref peak_video_encoder_option for possible values
 * \param[in] count             size of \p value in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p encoderOption is an invalid option or \p value is an invalid pointer
                                            or the size of \p count is incorrect.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 */
PEAK_API_STATUS peak_VideoWriter_Encoder_Option_Set(
    peak_video_handle hVideo, peak_video_encoder_option encoderOption, const void* value, size_t count);

/*!
 * \ingroup video
 * \brief Get encoder options
 * 
 * \param[in]  hVideo            The video handle.
 * \param[in]  encoderOption     Encoder option to retrieve see \ref peak_video_encoder_option.
 * \param[out] value             see \ref peak_video_encoder_option.
 * \param[in]  count             size of \p value in bytes.
 * \param[out] outCount          size of written data in bytes.
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_INVALID_PARAMETER   \p encoderOption is an invalid option or \p value is an invalid pointer
                                            or the size of \p count is incorrect.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 * 
 */
PEAK_API_STATUS peak_VideoWriter_Encoder_Option_Get(
    peak_video_handle hVideo, peak_video_encoder_option encoderOption, void* value, size_t count, size_t* outCount);

/*!
 * \ingroup video
 * \brief Wait until queue is empty.
 *
 * \param[in] hVideo            The video handle.
 * \param[in] timeout_ms        Timeout in milliseconds
 *
 * \return #PEAK_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_STATUS_INVALID_HANDLE      \p hVideo is an invalid video handle.
 * \return #PEAK_STATUS_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_STATUS_TIMEOUT             The wait timeout has elapsed.
 * \return #PEAK_STATUS_ERROR               An unexpected internal error occurred.
 *
 */
PEAK_API_STATUS peak_VideoWriter_WaitUntilQueueEmpty(peak_video_handle hVideo, int32_t timeout_ms);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // PEAK_COMFORT_C_H
