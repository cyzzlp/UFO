/////////////////////////////////////////////////////////////////////////////
// This is a part of the PI-Software Sources
// Copyright (C) 1995-2002 PHYSIK INSTRUMENTE GmbH
// All rights reserved.
//

///////////////////////////////////////////////////////////////////////////// 
// Program: PI_G-Control DLL
//
// Developer: JKa
//  
// File: PI_GCS_DLL.h : 
/////////////////////////////////////////////////////////////////////////////

#ifndef PI_GCS2_DLL_H
#define PI_GCS2_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#undef PI_FUNC_DECL
#ifdef PI_DLL_EXPORTS
#ifndef UNKNOWN_GCS_DLL
#define PI_FUNC_DECL __declspec(dllexport) __stdcall
#else
#define PI_FUNC_DECL WINAPI
#endif
#else
#define PI_FUNC_DECL __declspec(dllimport) __stdcall
#endif
#else
#define PI_FUNC_DECL
#endif


#ifndef WIN32
#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#endif //WIN32


/* function type */
#define PI_FUNC_LONG long PI_FUNC_DECL
#define PI_FUNC_INT int PI_FUNC_DECL
#define PI_FUNC_BOOL BOOL PI_FUNC_DECL
#define PI_FUNC_VOID void PI_FUNC_DECL

////////////////////////////////
// E-7XX Bits (PI_BIT_XXX). //
////////////////////////////////

/* Curve Controll PI_BIT_WGO_XXX */
#define PI_BIT_WGO_START_DEFAULT			0x00000001U
#define PI_BIT_WGO_START_EXTERN_TRIGGER		0x00000002U
#define PI_BIT_WGO_WITH_DDL_INITIALISATION	0x00000040U
#define PI_BIT_WGO_WITH_DDL					0x00000080U
#define PI_BIT_WGO_START_AT_ENDPOSITION		0x00000100U
#define PI_BIT_WGO_SINGLE_RUN_DDL_TEST		0x00000200U
#define PI_BIT_WGO_EXTERN_WAVE_GENERATOR	0x00000400U
#define PI_BIT_WGO_SAVE_BIT_1				0x00100000U
#define PI_BIT_WGO_SAVE_BIT_2				0x00200000U
#define PI_BIT_WGO_SAVE_BIT_3				0x00400000U

/* Wave-Trigger PI_BIT_TRG_XXX */
#define	PI_BIT_TRG_LINE_1					0x0001U
#define	PI_BIT_TRG_LINE_2					0x0002U
#define	PI_BIT_TRG_LINE_3					0x0003U
#define	PI_BIT_TRG_LINE_4					0x0008U
#define	PI_BIT_TRG_ALL_CURVE_POINTS			0x0100U

/* Data Record Configuration PI_DRC_XXX */
#define	PI_DRC_DEFAULT					0U
#define	PI_DRC_AXIS_TARGET_POS			1U
#define	PI_DRC_AXIS_ACTUAL_POS			2U
#define	PI_DRC_AXIS_POS_ERROR			3U
#define	PI_DRC_AXIS_DDL_DATA			4U
#define	PI_DRC_AXIS_DRIVING_VOL			5U
#define	PI_DRC_PIEZO_MODEL_VOL			6U
#define	PI_DRC_PIEZO_VOL				7U
#define	PI_DRC_SENSOR_POS				8U


/* P(arameter)I(nfo)F(lag)_M(emory)T(ype)_XX */
#define PI_PIF_MT_RAM					0x00000001U
#define PI_PIF_MT_EPROM					0x00000002U
#define PI_PIF_MT_ALL					(PI_PIF_MT_RAM | PI_PIF_MT_EPROM)

/* P(arameter)I(nfo)F(lag)_D(ata)T(ype)_XX */
#define PI_PIF_DT_INT					1U
#define PI_PIF_DT_FLOAT					2U
#define PI_PIF_DT_CHAR					3U


/////////////////////////////////////////////////////////////////////////////
// DLL initialization and comm functions
	PI_FUNC_LONG PI_InterfaceSetupDlg(const char* szRegKeyName);
	PI_FUNC_LONG PI_ConnectRS232(long nPortNr, long nBaudRate);
#ifndef WIN32
	PI_FUNC_LONG PI_ConnectRS232ByDevName(const char* szDevName, long BaudRate);
#endif
	PI_FUNC_LONG PI_OpenRS232DaisyChain(long iPortNumber, long iBaudRate, long* pNumberOfConnectedDaisyChainDevices, char* szDeviceIDNs, long iBufferSize);
	PI_FUNC_LONG PI_ConnectDaisyChainDevice(long iPortId, long iDeviceNumber);
	PI_FUNC_LONG PI_CloseDaisyChain(long iPortId);

	PI_FUNC_LONG PI_ConnectNIgpib(const long nBoard, const long nDevAddr);

	PI_FUNC_LONG PI_ConnectTCPIP(const char* szHostname, long port);
	PI_FUNC_LONG PI_EnableTCPIPScan(long iMask);
	PI_FUNC_LONG PI_EnumerateTCPIPDevices(char* szBuffer, long iBufferSize, const char* szFilter);
	PI_FUNC_LONG PI_ConnectTCPIPByDescription(const char* szDescription);

	PI_FUNC_LONG PI_EnumerateUSB(char* szBuffer, long iBufferSize, const char* szFilter);
	PI_FUNC_LONG PI_ConnectUSB(const char* szDescription);
	PI_FUNC_LONG PI_ConnectUSBWithBaudRate(const char* szDescription, long iBaudRate);
	PI_FUNC_LONG PI_OpenUSBDaisyChain(const char* szDescription, long* pNumberOfConnectedDaisyChainDevices, char* szDeviceIDNs, long iBufferSize);

	PI_FUNC_BOOL PI_IsConnected(long ID);
	PI_FUNC_VOID PI_CloseConnection(long ID);
	PI_FUNC_LONG PI_GetError(long ID);
	PI_FUNC_BOOL PI_SetErrorCheck(long ID, BOOL bErrorCheck);
	PI_FUNC_BOOL PI_TranslateError(long errNr, char* szBuffer, long iBufferSize);




/////////////////////////////////////////////////////////////////////////////
// general
	PI_FUNC_BOOL PI_qERR(long ID, long* pnError);
	PI_FUNC_BOOL PI_qIDN(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_INI(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_qHLP(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qHPA(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qCSV(long ID, double* pdCommandSyntaxVersion);
	PI_FUNC_BOOL PI_qOVF(long ID, const char* szAxes, BOOL* piValueArray);
	PI_FUNC_BOOL PI_RBT(long ID);
	PI_FUNC_BOOL PI_REP(long ID);
	PI_FUNC_BOOL PI_BDR(long ID, int iBaudRate);
	PI_FUNC_BOOL PI_qBDR(long ID, int* iBaudRate);
	PI_FUNC_BOOL PI_DBR(long ID, int iBaudRate);
	PI_FUNC_BOOL PI_qDBR(long ID, int* iBaudRate);
	PI_FUNC_BOOL PI_qVER(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qSSN(long ID, char* szSerialNumber, int iBufferSize);
	PI_FUNC_BOOL PI_CCT(long ID, int iCommandType);
	PI_FUNC_BOOL PI_qCCT(long ID, int* iCommandType);
	PI_FUNC_BOOL PI_qTVI(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_IFC(long ID, const char* szParameters, const char* szValues);
	PI_FUNC_BOOL PI_qIFC(long ID, const char* szParameters, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_IFS(long ID, const char* szPassword, const char* szParameters, const char* szValues);
	PI_FUNC_BOOL PI_qIFS(long ID, const char* szParameters, char* szBuffer, int iBufferSize);

	PI_FUNC_BOOL PI_MOV(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qMOV(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_MVR(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_MVE(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_POS(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qPOS(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_IsMoving(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_HLT(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_STP(long ID);
	PI_FUNC_BOOL PI_qONT(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_RTO(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_qRTO(long ID, const char* szAxes, int* piValueArray);
	PI_FUNC_BOOL PI_ATZ(long ID, const char* szAxes, const double* pdLowvoltageArray, const BOOL* pfUseDefaultArray);
	PI_FUNC_BOOL PI_qATZ(long ID, const char* szAxes, int* piAtzResultArray);
	PI_FUNC_BOOL PI_AOS(int ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qAOS(int ID, const char* szAxes, double* pdValueArray);

	PI_FUNC_BOOL PI_SVA(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qSVA(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_SVR(long ID, const char* szAxes, const double* pdValueArray);

	PI_FUNC_BOOL PI_DFH(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_qDFH(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_GOH(long ID, const char* szAxes);

	PI_FUNC_BOOL PI_qCST(long ID, const char* szAxes, char* szNames, int iBufferSize);
	PI_FUNC_BOOL PI_CST(long ID, const char* szAxes, const char* szNames);
	PI_FUNC_BOOL PI_qVST(long ID, char* szBuffer, int iBufferSize);

	PI_FUNC_BOOL PI_SVO(long ID, const char* szAxes, const BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qSVO(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_SMO(long ID, const char* szAxes, const int* piValueArray);
	PI_FUNC_BOOL PI_qSMO(long ID, const char* szAxes, int* piValueArray);
	PI_FUNC_BOOL PI_DCO(long ID, const char* szAxes, const BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qDCO(long ID, const char* szAxes, BOOL* pbValueArray);

	PI_FUNC_BOOL PI_RON(long ID, const char* szAxes, const BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qRON(long ID, const char* szAxes, BOOL* pbValueArray);
	
	PI_FUNC_BOOL PI_VEL(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qVEL(long ID, const char* szAxes, double* pdValueArray);
	
	PI_FUNC_BOOL PI_ACC(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qACC(long ID, const char* szAxes, double* pdValueArray);
	
	PI_FUNC_BOOL PI_DEC(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qDEC(long ID, const char* szAxes, double* pdValueArray);
	
	PI_FUNC_BOOL PI_VCO(long ID, const char* szAxes, const BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qVCO(long ID, const char* szAxes, BOOL* pbValueArray);
	
	PI_FUNC_BOOL PI_SPA(long ID, const char* szAxes, const unsigned int* iParameterArray, const double* pdValueArray, const char* szStrings);
	PI_FUNC_BOOL PI_qSPA(long ID, const char* szAxes, unsigned int* iParameterArray, double* pdValueArray, char* szStrings, int iMaxNameSize);
	PI_FUNC_BOOL PI_SEP(long ID, const char* szPassword, const char* szAxes, const unsigned int* iParameterArray, const double* pdValueArray, const char* szStrings);
	PI_FUNC_BOOL PI_qSEP(long ID, const char* szAxes, unsigned int* iParameterArray, double* pdValueArray, char* szStrings, int iMaxNameSize);
	PI_FUNC_BOOL PI_WPA(long ID, const char* szPassword, const char* szAxes, const unsigned int* iParameterArray);
	PI_FUNC_BOOL PI_RPA(long ID, const char* szAxes, const unsigned int* iParameterArray);
	PI_FUNC_BOOL PI_SPA_String(long ID, const char* szAxes, const unsigned int* iParameterArray, const char* szStrings);
	PI_FUNC_BOOL PI_qSPA_String(long ID, const char* szAxes, const unsigned int* iParameterArray, char* szStrings, int iMaxNameSize);
	PI_FUNC_BOOL PI_SEP_String(long ID, const char* szPassword, const char* szAxes, const unsigned int* iParameterArray, const char* szStrings);
	PI_FUNC_BOOL PI_qSEP_String(long ID, const char* szAxes, unsigned int* iParameterArray, char* szStrings, int iMaxNameSize);
	
	PI_FUNC_BOOL PI_STE(long ID, const char* szAxes, const double* dOffsetArray);
	PI_FUNC_BOOL PI_qSTE(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_IMP(long ID, const char* szAxes, const double* pdImpulseSize);
	PI_FUNC_BOOL PI_IMP_PulseWidth(long ID, char cAxis, double dOffset, int iPulseWidth);
	PI_FUNC_BOOL PI_qIMP(long ID, const char* szAxes, double* pdValueArray);
	
	PI_FUNC_BOOL PI_SAI(long ID, const char* szOldAxes, const char* szNewAxes);
	PI_FUNC_BOOL PI_qSAI(long ID, char* szAxes, int iBufferSize);
	PI_FUNC_BOOL PI_qSAI_ALL(long ID, char* szAxes, int iBufferSize);
	
	PI_FUNC_BOOL PI_CCL(long ID, int iComandLevel, const char* szPassWord);
	PI_FUNC_BOOL PI_qCCL(long ID, int* piComandLevel);
	
	PI_FUNC_BOOL PI_AVG(long ID, int iAverrageTime);
	PI_FUNC_BOOL PI_qAVG(long ID, int* iAverrageTime);
	
	PI_FUNC_BOOL PI_qHAR(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qLIM(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qTRS(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_FNL(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_FPL(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_FRF(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_FED(long ID, const char* szAxes, const int* piEdgeArray, const int* piParamArray);
	PI_FUNC_BOOL PI_qFRF(long ID, const char* szAxes, BOOL* pbValueArray);
	PI_FUNC_BOOL PI_DIO(long ID, const int* piChannelsArray, const BOOL* pbValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qDIO(long ID, const long* piChannelsArray, BOOL* pbValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qTIO(long ID, int* piInputNr, int* piOutputNr);
	PI_FUNC_BOOL PI_IsControllerReady(long ID, int* piControllerReady);
	PI_FUNC_BOOL PI_qSRG(long ID, const char* szAxes, const int* iRegisterArray, int* iValArray);

	PI_FUNC_BOOL PI_ATC(long ID, const int* piChannels, const int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qATC(long ID, const int* piChannels, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qATS(long ID, const int* piChannels, const int* piOptions, int* piValueArray, int iArraySize);

/////////////////////////////////////////////////////////////////////////////
// Macro commande
	PI_FUNC_BOOL PI_IsRunningMacro(long ID, BOOL* pbRunningMacro);
	PI_FUNC_BOOL PI_MAC_BEG(long ID, const char* szMacroName);
	PI_FUNC_BOOL PI_MAC_START(long ID, const char* szMacroName);
	PI_FUNC_BOOL PI_MAC_NSTART(long ID, const char* szMacroName, int nrRuns);
	PI_FUNC_BOOL PI_MAC_END(long ID);
	PI_FUNC_BOOL PI_MAC_DEL(long ID, const char* szMacroName);
	PI_FUNC_BOOL PI_MAC_DEF(long ID, const char* szMacroName);
	PI_FUNC_BOOL PI_MAC_qDEF(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qMAC(long ID, const char* szMacroName, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qRMC(long ID, char* szBuffer, int iBufferSize);

	PI_FUNC_BOOL PI_DEL(long ID, int nMilliSeconds);
	PI_FUNC_BOOL PI_WAC(long ID, const char* szCondition);
	PI_FUNC_BOOL PI_MEX(long ID, const char* szCondition);

/////////////////////////////////////////////////////////////////////////////
// String commands.
	PI_FUNC_BOOL PI_GcsCommandset(long ID, const char* szCommand);
	PI_FUNC_BOOL PI_GcsGetAnswer(long ID, char* szAnswer, int iBufferSize);
	PI_FUNC_BOOL PI_GcsGetAnswerSize(long ID, int* iAnswerSize);


/////////////////////////////////////////////////////////////////////////////
// limits
	PI_FUNC_BOOL PI_qTMN(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_qTMX(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_NLM(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qNLM(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_PLM(long ID, const char* szAxes, const double* pdValueArray);
	PI_FUNC_BOOL PI_qPLM(long ID, const char* szAxes, double* pdValueArray);
	PI_FUNC_BOOL PI_SSL(long ID, const char* szAxes, const BOOL* pbValueArray);
	PI_FUNC_BOOL PI_qSSL(long ID, const char* szAxes, BOOL* pbValueArray);


/////////////////////////////////////////////////////////////////////////////
// Wave commands.
	PI_FUNC_BOOL PI_IsGeneratorRunning(long ID, const int* piWaveGeneratorIds, BOOL* pbValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qTWG(long ID, int* piWaveGenerators);
	PI_FUNC_BOOL PI_WAV_SIN_P(long ID, int iWaveTableId, int iOffsetOfFirstPointInWaveTable, int iNumberOfPoints, int iAddAppendWave, int iCenterPointOfWave, double dAmplitudeOfWave, double dOffsetOfWave, int iSegmentLength);
	PI_FUNC_BOOL PI_WAV_LIN(long ID, int iWaveTableId, int iOffsetOfFirstPointInWaveTable, int iNumberOfPoints, int iAddAppendWave, int iNumberOfSpeedUpDownPointsInWave, double dAmplitudeOfWave, double dOffsetOfWave, int iSegmentLength);
	PI_FUNC_BOOL PI_WAV_RAMP(long ID, int iWaveTableId, int iOffsetOfFirstPointInWaveTable, int iNumberOfPoints, int iAddAppendWave, int iCenterPointOfWave, int iNumberOfSpeedUpDownPointsInWave, double dAmplitudeOfWave, double dOffsetOfWave, int iSegmentLength);
	PI_FUNC_BOOL PI_WAV_PNT(long ID, int iWaveTableId, int iOffsetOfFirstPointInWaveTable, int iNumberOfPoints, int iAddAppendWave, const double* pdWavePoints);
	PI_FUNC_BOOL PI_qWAV(long ID, const int* piWaveTableIdsArray, const int* piParamereIdsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_WGO(long ID, const int* piWaveGeneratorIdsArray, const int* iStartModArray, int iArraySize);
	PI_FUNC_BOOL PI_qWGO(long ID, const int* piWaveGeneratorIdsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_WGC(long ID, const int* piWaveGeneratorIdsArray, const int* piNumberOfCyclesArray, int iArraySize);
	PI_FUNC_BOOL PI_qWGC(long ID, const int* piWaveGeneratorIdsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_WSL(long ID, const int* piWaveGeneratorIdsArray, const int* piWaveTableIdsArray, int iArraySize);
	PI_FUNC_BOOL PI_qWSL(long ID, const int* piWaveGeneratorIdsArray, int* piWaveTableIdsArray, int iArraySize);
	PI_FUNC_BOOL PI_DTC(long ID, const int* piDdlTableIdsArray, int iArraySize);
	PI_FUNC_BOOL PI_WCL(long ID, const int* piWaveTableIdsArray, int iArraySize);
	PI_FUNC_BOOL PI_qTLT(long ID, int* piNumberOfDdlTables);
	PI_FUNC_BOOL PI_qGWD_SYNC(long ID, int iWaveTableId, int iOffsetOfFirstPointInWaveTable, int iNumberOfValues, double* pdValueArray);
	PI_FUNC_BOOL PI_qGWD(long ID, const int* iWaveTableIdsArray, int iNumberOfWaveTables, int iOffset, int nrValues, double** pdValarray, char* szGcsArrayHeader, int iGcsArrayHeaderMaxSize);
	PI_FUNC_BOOL PI_WOS(long ID, const int* iWaveTableIdsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qWOS(long ID, const int* iWaveTableIdsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_WTR(long ID, const int* piWaveGeneratorIdsArray, const int* piTableRateArray, const int* piInterpolationTypeArray, int iArraySize);
	PI_FUNC_BOOL PI_qWTR(long ID, const int* piWaveGeneratorIdsArray, int* piTableRateArray, int* piInterpolationTypeArray, int iArraySize);
	PI_FUNC_BOOL PI_DPO(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_qWMS(long ID, const int* piWaveTableIds, int* iWaveTableMaimumSize, int iArraySize);



///////////////////////////////////////////////////////////////////////////////
//// Trigger commands.
	PI_FUNC_BOOL PI_TWC(long ID);
	PI_FUNC_BOOL PI_CTO(long ID, const int* piTriggerOutputIdsArray, const int* piTriggerParameterArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qCTO(long ID, const int* piTriggerOutputIdsArray, const int* piTriggerParameterArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_TRO(long ID, const long* piTriggerChannelIds, const BOOL* pbTriggerChannelEnabel, long iArraySize);
	PI_FUNC_BOOL PI_qTRO(long ID, const long* piTriggerChannelIds, BOOL* pbTriggerChannelEnabel, long iArraySize);


/////////////////////////////////////////////////////////////////////////////
// Record tabel commands.
	PI_FUNC_BOOL PI_qHDR(long ID, char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qTNR(long ID, int* piNumberOfRecordCannels);
	PI_FUNC_BOOL PI_DRC(long ID, const int* piRecordTableIdsArray, const char* szRecordSourceIds, const int* piRecordOptionArray);
	PI_FUNC_BOOL PI_qDRC(long ID, const int* piRecordTableIdsArray, char* szRecordSourceIds, int* piRecordOptionArray, int iRecordSourceIdsBufferSize, int iRecordOptionArraySize);
	PI_FUNC_BOOL PI_qDRR_SYNC(long ID, int iRecordTablelId, int iOffsetOfFirstPointInRecordTable, int iNumberOfValues, double* pdValueArray);
	PI_FUNC_BOOL PI_qDRR(long ID, const int* piRecTableIdsArray, int iNumberOfRecChannels, int iOffsetOfFirstPointInRecordTable, int iNumberOfValues, double** pdValueArray, char* szGcsArrayHeader, int iGcsArrayHeaderMaxSize);
	PI_FUNC_BOOL PI_DRT(long ID, const int* piRecordChannelIdsArray, const int* piTriggerSourceArray, const char* szValues, int iArraySize);
	PI_FUNC_BOOL PI_qDRT(long ID, const int* piRecordChannelIdsArray, int* piTriggerSourceArray, char* szValues, int iArraySize, int iValueBufferLength);
	PI_FUNC_BOOL PI_RTR(long ID, int piReportTableRate);
	PI_FUNC_BOOL PI_qRTR(long ID, int* piReportTableRate);
	PI_FUNC_BOOL PI_WGR(long ID);


/////////////////////////////////////////////////////////////////////////////
// Piezo-Channel commands.
	PI_FUNC_BOOL PI_VMA(long ID, const int* piPiezoChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qVMA(long ID, const int* piPiezoChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_VMI(long ID, const int* piPiezoChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qVMI(long ID, const int* piPiezoChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_VOL(long ID, const int* piPiezoChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qVOL(long ID, const int* piPiezoChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qTPC(long ID, int* piNumberOfPiezoChannels);
	PI_FUNC_BOOL PI_ONL(long ID, const int* iPiezoCannels, const int* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qONL(long ID, const int* iPiezoCannels, int* pdValueArray, int iArraySize);


/////////////////////////////////////////////////////////////////////////////
// Sensor-Channel commands.
	PI_FUNC_BOOL PI_qTAD(long ID, const int* piSensorsChannelsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qTNS(long ID, const int* piSensorsChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qTSP(long ID, const int* piSensorsChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_SCN(long ID, const int* piSensorsChannelsArray, const int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qSCN(long ID, const int* piSensorsChannelsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qTSC(long ID, int* piNumberOfSensorChannels);


/////////////////////////////////////////////////////////////////////////////
// PIEZOWALK(R)-Channel commands.
	PI_FUNC_BOOL PI_APG(long ID, const int* piPIEZOWALKChannelsArray, int iArraySize);
	PI_FUNC_BOOL PI_qAPG(long ID, const int* piPIEZOWALKChannelsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_OAD(long ID, const int* piPIEZOWALKChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qOAD(long ID, const int* piPIEZOWALKChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_OCD(long ID, const int* piPIEZOWALKChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qOCD(long ID, const int* piPIEZOWALKChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_OSM(long ID, const int* piPIEZOWALKChannelsArray, const int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qOSM(long ID, const int* piPIEZOWALKChannelsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_OVL(long ID, const int* piPIEZOWALKChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qOVL(long ID, const int* piPIEZOWALKChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qOSN(long ID, const int* piPIEZOWALKChannelsArray, int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_SSA(long ID, const int* piPIEZOWALKChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qSSA(long ID, const int* piPIEZOWALKChannelsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_RNP(long ID, const int* piPIEZOWALKChannelsArray, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_PGS(long ID, const int* piPIEZOWALKChannelsArray, int iArraySize);
	PI_FUNC_BOOL PI_qTAC(long ID, int* pnNrChannels);
	PI_FUNC_BOOL PI_qTAV(long ID, const int* piChannelsArray, double* pdValueArray, int iArraySize);

/////////////////////////////////////////////////////////////////////////////
// Joystick
	PI_FUNC_BOOL PI_qJAS(long ID, const int* iJoystickIDsArray, const int* iAxesIDsArray, double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_JAX(long ID, int iJoystickID, int iAxesID, const char* szAxesBuffer);
	PI_FUNC_BOOL PI_qJAX(long ID, const int* iJoystickIDsArray, const int* iAxesIDsArray, int iArraySize, char* szAxesBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_qJBS(long ID, const int* iJoystickIDsArray, const int* iButtonIDsArray, BOOL* pbValueArray, int iArraySize);
	PI_FUNC_BOOL PI_JDT(long ID, const int* iJoystickIDsArray, const int* iAxisIDsArray, const int* piValueArray, int iArraySize);
	PI_FUNC_BOOL PI_JLT(long ID, int iJoystickID, int iAxisID, int iStartAdress, const double* pdValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qJLT(long ID, const int* iJoystickIDsArray, const int* iAxisIDsArray, int iNumberOfTables, int iOffsetOfFirstPointInTable, int iNumberOfValues, double** pdValueArray, char* szGcsArrayHeader, int iGcsArrayHeaderMaxSize);
	PI_FUNC_BOOL PI_JON(long ID, const int* iJoystickIDsArray, const BOOL* pbValueArray, int iArraySize);
	PI_FUNC_BOOL PI_qJON(long ID, const int* iJoystickIDsArray, BOOL* pbValueArray, int iArraySize);




/////////////////////////////////////////////////////////////////////////////
// Spezial
	PI_FUNC_BOOL PI_GetSupportedFunctions(long ID, long* piCommandLevelArray, const int iiBufferSize, char* szFunctionNames, const int iMaxFunctioNamesLength);
	PI_FUNC_BOOL PI_GetSupportedParameters(long ID, int* piParameterIdArray, int* piCommandLevelArray, int* piMemoryLocationArray, int* piDataTypeArray, int* piNumberOfItems, const int iiBufferSize, char* szParameterName, const int iMaxParameterNameSize);
	PI_FUNC_BOOL PI_GetSupportedControllers(char* szBuffer, int iBufferSize);
	PI_FUNC_BOOL PI_GetAsyncBufferIndex(long ID);
	PI_FUNC_BOOL PI_GetAsyncBuffer(long ID, double** pdValueArray);
	
	
	PI_FUNC_BOOL PI_AddStage(long ID, const char* szAxes);
	PI_FUNC_BOOL PI_RemoveStage(long ID, const char* szStageName);
	PI_FUNC_BOOL PI_OpenUserStagesEditDialog(long ID);
	PI_FUNC_BOOL PI_OpenPiStagesEditDialog(long ID);


#ifdef __cplusplus
} // extern "C"
#endif// __cplusplus
#endif// !PI_GCS2_DLL_H