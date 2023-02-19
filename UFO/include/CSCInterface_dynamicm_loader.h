#pragma once

#include "CSCInterface.h"
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

#undef CSC_DLL_EXPORTS
#define CSC_DLL_EXPORTS
#undef CSC_FUNC_DECL
#define CSC_FUNC_DECL

namespace CSC_MARK
{
	namespace dynamicm
	{
		typedef CSC_FUNC_INT(*lpOpenUSB_Board)(int deviceIndex, void* handle);
		typedef CSC_FUNC_INT(*lpLoadFPGA_FirmwareProgram)(char* rbfFilePath);
		typedef CSC_FUNC_INT(*lpSetLaserMode)(int laserType, int standby, float frequency, float pulseWidth);
		typedef CSC_FUNC_INT(*lpSetSystemParameters)(double rangeX, double rangeY, bool exchangeXY, bool invertX, bool invertY, int startMarkMode);
		typedef CSC_FUNC_INT(*lpSetCorrectParameters_0)(double xCorrection, double yCorrection, double xShear, double yShear, double xLadder, double yLadder, double ratioX, double ratioY, double ratioZ);
		typedef CSC_FUNC_INT(*lpSetCorrectParameters_1)(double ratioX, double ratioY, double ratioZ, char* filePath);
		typedef CSC_FUNC_VOID(*lpWriteDataEnd)();
		typedef CSC_FUNC_VOID(*lpSetOverallMarkCounts)(int count);
		typedef CSC_FUNC_BOOL(*lpIsMarkEnd)();
		typedef CSC_FUNC_BOOL(*lpStartMark)();
		typedef CSC_FUNC_UNDIGNED_INT(*lpGetProducedData)();
		typedef CSC_FUNC_INT(*lpSetMarkParameter)(int index, int markCounts, int isBitmap, float markSpeed, float jumpSpeed, float jumpDelay, float polygonDelay, float laserOnDelay, float laserOffDelay, float polygonKillerTime, float laserFrequency, float current, float firstPulseKillerLength, float pulseWidth, float firstPulseWidth, float incrementStep, float dotSpace);
		typedef CSC_FUNC_BOOL(*lpDownloadMarkParameters)();
		typedef CSC_FUNC_BOOL(*lpSetFirstMarkParameter)(int pen);
		typedef CSC_FUNC_BOOL(*lpReadyMark)();
		typedef CSC_FUNC_BOOL(*lpReadyPreview)();
		typedef CSC_FUNC_BOOL(*lpStartReadDataThread)();
		typedef CSC_FUNC_INT(*lpZeroCounter)();
		typedef CSC_FUNC_BOOL(*lpStopMark)();
		typedef CSC_FUNC_BOOL(*lpStopPreview)();
		typedef CSC_FUNC_BOOL(*lpStopCalcData)();
		typedef CSC_FUNC_BOOL(*lpGetMarkStatus)();
		typedef CSC_FUNC_UNDIGNED_LONG(*lpGetMarkTime)();
		typedef CSC_FUNC_BOOL(*lpGetMarkCounts)(unsigned char* internalMarkCounts, unsigned char* externalMarkCounts);
		typedef CSC_FUNC_BOOL(*lpGetLaserAndScannerStatus)(int* laserStatus, int* scannerStatus);
		typedef CSC_FUNC_BOOL(*lpGetScannerPosition)(float* xPos, float* yPos);
		typedef CSC_FUNC_BOOL(*lpLaserSignalOn)();
		typedef CSC_FUNC_BOOL(*lpLaserSignalOff)();
		typedef CSC_FUNC_INT(*lpMarkCommand_Point)(double x, double y, int type, int tp);
		typedef CSC_FUNC_INT(*lpMarkCommand_Vector)(int length, double* sitsetX, double* sitsetY);
		typedef CSC_FUNC_INT(*lpMarkCommand_Bitmap)(int length, double* sitsetX, double* sitsetY, int* sitsetGray);
		typedef CSC_FUNC_INT(*lpChangePensCommand)(unsigned char pen);
		typedef CSC_FUNC_INT(*lpEndCommand)();
		typedef CSC_FUNC_INT(*lpGoto_XY)(double x, double y);
		typedef CSC_FUNC_BOOL(*lpJumpCommand)(double x, double y);
		typedef CSC_FUNC_VOID(*lpCloseUSBBoard)();
		typedef CSC_FUNC_BOOL(*lpWrite_IO_Port)(unsigned char port);
		typedef CSC_FUNC_INT(*lpOutputCommand)(unsigned char port, int outMode, int level, int outputPulseWidth);
		typedef CSC_FUNC_UNDIGNED_CHAR(*lpGetOutputPortState)();
		

		class DynamicLoaderc
		{
		private:
			DynamicLoaderc();

			static DynamicLoaderc& instancec()
			{
				static DynamicLoaderc DynamicLoaderc{};
				return DynamicLoaderc;
			}
			bool loadLibc(const char* file);
			void unloadc();
			bool setPointersc(bool load);

		public:
			~DynamicLoaderc();

			static bool isLoadedc();

			static CSC_FUNC_INT OpenUSB_Board(int deviceIndex, void* handle);
			static CSC_FUNC_INT LoadFPGA_FirmwareProgram(char* rbfFilePath);
			static CSC_FUNC_BOOL SetLaserMode(int laserType, int standby, float frequency, float pulseWidth);
			static CSC_FUNC_INT SetSystemParameters(double rangeX, double rangeY, double markStep, double jumpStep, bool exchangeXY, bool invertX, bool invertY, int startMarkMode);
			static CSC_FUNC_INT SetCorrectParameters_0(double xCorrection, double yCorrection, double xShear, double yShear, double xLadder, double yLadder, double ratioX, double ratioY, double ratioZ);
			static CSC_FUNC_INT SetCorrectParameters_1(double ratioX, double ratioY, double ratioZ, char* filePath);
			static CSC_FUNC_VOID WriteDataEnd();
			static CSC_FUNC_VOID SetOverallMarkCounts(int count);
			static CSC_FUNC_BOOL IsMarkEnd();
			static CSC_FUNC_BOOL StartMark();
			static CSC_FUNC_UNDIGNED_INT GetProducedData();
			static CSC_FUNC_BOOL DownloadMarkParameters();
			static CSC_FUNC_INT SetMarkParameter(int index, int markCounts, int isBitmap, float markSpeed, float jumpSpeed, float jumpDelay, float polygonDelay, float laserOnDelay, float laserOffDelay, float polygonKillerTime, float laserFrequency, float current, float firstPulseKillerLength, float pulseWidth, float firstPulseWidth, float incrementStep, float dotSpace);;
			static CSC_FUNC_BOOL SetFirstMarkParameter(int pen);
			static CSC_FUNC_BOOL ReadyMark();
			static CSC_FUNC_BOOL ReadyPreview();
			static CSC_FUNC_BOOL StartReadDataThread();
			static CSC_FUNC_BOOL StopMark();
			static CSC_FUNC_BOOL StopPreview();
			static CSC_FUNC_BOOL StopCalcData();
			static CSC_FUNC_BOOL GetMarkStatus();
			static CSC_FUNC_UNDIGNED_LONG GetMarkTime();
			static CSC_FUNC_BOOL GetMarkCounts(unsigned char* internalMarkCounts, unsigned char* externalMarkCounts);
			static CSC_FUNC_BOOL GetLaserAndScannerStatus(int* laserStatus, int* scannerStatus);
			static CSC_FUNC_BOOL GetScannerPosition(float* xPos, float* yPos);
			static CSC_FUNC_BOOL LaserSignalOn();
			static CSC_FUNC_BOOL LaserSignalOff();
			static CSC_FUNC_INT MarkCommand_Point(double x, double y, int type, int tp);
			static CSC_FUNC_INT MarkCommand_Vector(int length, double* sitsetX, double* sitsetY);
			static CSC_FUNC_INT MarkCommand_Bitmap(int length, double* sitsetX, double* sitsetY, int* sitsetGray);
			static CSC_FUNC_INT ChangePensCommand(unsigned char pen);
			static CSC_FUNC_INT EndCommand();
			static CSC_FUNC_INT Goto_XY(double x, double y);
			static CSC_FUNC_BOOL JumpCommand(double x, double y);
			static CSC_FUNC_VOID CloseUSB_Board();
			static CSC_FUNC_BOOL Write_IO_Port(unsigned char port);
			static CSC_FUNC_INT OutputCommand(unsigned char port, int outMode, int level, int outputPulseWidth);
			static CSC_FUNC_UNDIGNED_CHAR GetOutputPortState();

		private:
			void* m_handle = nullptr;
			lpOpenUSB_Board m_OpenUSB_Board{};
			lpLoadFPGA_FirmwareProgram m_LoadFPGA_FirmwareProgram{};
			lpSetLaserMode m_SetLaserMode{};
			lpSetSystemParameters m_SetSystemParameters{};
			lpSetCorrectParameters_0 m_SetCorrectParameters_0{};
			lpSetCorrectParameters_1 m_SetCorrectParameters_1{};
			lpWriteDataEnd m_WriteDataEnd{};
			lpSetOverallMarkCounts m_SetOverallMarkCounts{};
			lpIsMarkEnd m_IsMarkEnd{};
			lpStartMark m_StartMark{};
			lpGetProducedData m_GetProducedData{};
			lpDownloadMarkParameters m_DownloadMarkParameters{};
			lpSetMarkParameter m_SetMarkParameter{};
			lpSetFirstMarkParameter m_SetFirstMarkParameter{};
			lpReadyMark m_ReadyMark{};
			lpReadyPreview m_ReadyPreview{};
			lpStartReadDataThread m_StartReadDataThread{};
			lpZeroCounter m_ZeroCounter{};
			lpStopMark m_StopMark{};
			lpStopPreview m_StopPreview{};
			lpStopCalcData m_StopCalcData{};
			lpGetMarkStatus m_GetMarkStatus{};
			lpGetMarkTime m_GetMarkTime{};
			lpGetMarkCounts m_GetMarkCounts{};
			lpGetLaserAndScannerStatus m_GetLaserAndScannerStatus{};
			lpGetScannerPosition m_GetScannerPosition{};
			lpLaserSignalOn m_LaserSignalOn{};
			lpLaserSignalOff m_LaserSignalOff{};
			lpMarkCommand_Point m_MarkCommand_Point{};
			lpMarkCommand_Vector m_MarkCommand_Vector{};
			lpMarkCommand_Bitmap m_MarkCommand_Bitmap{};
			lpChangePensCommand m_ChangePensCommand{};
			lpEndCommand m_EndCommand{};
			lpGoto_XY m_Goto_XY{};
			lpJumpCommand m_JumpCommand{};
			lpCloseUSBBoard m_CloseUSBBoard{};
			lpWrite_IO_Port m_Write_IO_Port{};
			lpOutputCommand m_OutputCommand{};
			lpGetOutputPortState m_GetOutputPortState{};
		};

		inline void* import_functionc(void* module, const char* proc_name)
		{
			#ifdef __linux__
				return dlsym(module, proc_name);
			#else
				return GetProcAddress(static_cast<HMODULE>(module), proc_name);
			#endif
		}

		inline DynamicLoaderc::DynamicLoaderc()
		{
			#if defined _WIN32 || defined _WIN64
			size_t sz = 0;
			if (_wgetenv_s(&sz, NULL, 0, L"CSCINTERFACE_COMFORT_SDK_PATH") == 0 && sz > 0)
			{
				std::vector<wchar_t> env_csc_mark(sz);
				if (_wgetenv_s(&sz, env_csc_mark.data(), sz, L"CSCINTERFACE_COMFORT_SDK_PATH") == 0)
				{
					if (_wgetenv_s(&sz, NULL, 0, L"PATH") == 0 && sz > 0)
					{
						std::vector<wchar_t> env_path(sz);
						if (_wgetenv_s(&sz, env_path.data(), sz, L"PATH") == 0)
						{
							std::wstring env_csc_mark_path(env_csc_mark.data());
							#ifdef _WIN64
								env_csc_mark_path.append(L"x86_64");
							#else
								env_csc_mark_path.append(L"x86_32");
							#endif
							std::wstring path_var(env_path.data());
							path_var.append(L";").append(env_csc_mark_path);
							_wputenv_s(L"PATH", path_var.c_str());
						}
					}
				}
			}

			loadLibc("CSCInterface.dll");
			#endif
		}

		inline DynamicLoaderc::~DynamicLoaderc()
		{
			if (m_handle != nullptr)
			{
				unloadc();
			}
		}

		inline bool DynamicLoaderc::isLoadedc()
		{
			auto&& inst = instancec();
			return inst.m_handle != nullptr;
		}

		inline void DynamicLoaderc::unloadc()
		{
			setPointersc(false);

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

		inline bool DynamicLoaderc::loadLibc(const char* file)
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
					try 
					{
						setPointersc(true);
						ret = true;
					}
					catch (const std::exception&) 
					{
						unloadc();
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

		inline bool DynamicLoaderc::setPointersc(bool load)
		{
			m_OpenUSB_Board = (lpOpenUSB_Board)(load ? import_functionc(m_handle, "OpenUSB_Board") : nullptr);
			if (m_OpenUSB_Board == nullptr && load)
			{
				throw std::runtime_error("Failed to load OpenUSB_Board");
			}

			m_LoadFPGA_FirmwareProgram= (lpLoadFPGA_FirmwareProgram)(load ? import_functionc(m_handle, "LoadFPGA_FirmwareProgram") : nullptr);
			if (m_LoadFPGA_FirmwareProgram == nullptr && load)
			{
				throw std::runtime_error("Failed to load LoadFPGA_FirmwareProgram");
			}

			m_SetLaserMode = (lpSetLaserMode)(load ? import_functionc(m_handle, "SetLaserMode") : nullptr);
			if (m_SetLaserMode == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetLaserMode");
			}

			m_SetSystemParameters = (lpSetSystemParameters)(load ? import_functionc(m_handle, "SetSystemParameters") : nullptr);
			if (m_SetSystemParameters == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetSystemParameters");
			}

			m_SetCorrectParameters_0 = (lpSetCorrectParameters_0)(load ? import_functionc(m_handle, "SetCorrectParameters_0") : nullptr);
			if (m_SetCorrectParameters_0 == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetCorrectParameters_0");
			}

			m_SetCorrectParameters_1 = (lpSetCorrectParameters_1)(load ? import_functionc(m_handle, "SetCorrectParameters_1") : nullptr);
			if (m_SetCorrectParameters_1 == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetCorrectParameters_1");
			}

			m_WriteDataEnd = (lpWriteDataEnd)(load ? import_functionc(m_handle, "WriteDataEnd") : nullptr);
			if (m_WriteDataEnd == nullptr && load)
			{
				throw std::runtime_error("Failed to load WriteDataEnd");
			}

			m_SetOverallMarkCounts = (lpSetOverallMarkCounts)(load ? import_functionc(m_handle, "SetOverallMarkCounts") : nullptr);
			if (m_SetOverallMarkCounts == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetOverallMarkCounts");
			}

			m_IsMarkEnd = (lpIsMarkEnd)(load ? import_functionc(m_handle, "IsMarkEnd") : nullptr);
			if (m_IsMarkEnd == nullptr && load)
			{
				throw std::runtime_error("Failed to load IsMarkEnd");
			}

			m_StartMark = (lpStartMark)(load ? import_functionc(m_handle, "StartMark") : nullptr);
			if (m_StartMark == nullptr && load)
			{
				throw std::runtime_error("Failed to load StartMark");
			}

			m_GetProducedData = (lpGetProducedData)(load ? import_functionc(m_handle, "GetProducedData") : nullptr);
			if (m_GetProducedData == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetProducedData");
			}

			m_DownloadMarkParameters = (lpDownloadMarkParameters)(load ? import_functionc(m_handle, "DownloadMarkParameters") : nullptr);
			if (m_DownloadMarkParameters == nullptr && load)
			{
				throw std::runtime_error("Failed to load DownloadMarkParameters");
			}

			m_SetMarkParameter = (lpSetMarkParameter)(load ? import_functionc(m_handle, "SetMarkParameter") : nullptr);
			if (m_SetMarkParameter == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetMarkParameter");
			}

			m_SetFirstMarkParameter = (lpSetFirstMarkParameter)(load ? import_functionc(m_handle, "SetFirstMarkParameter") : nullptr);
			if (m_SetFirstMarkParameter == nullptr && load)
			{
				throw std::runtime_error("Failed to load SetFirstMarkParameter");
			}

			m_ReadyMark = (lpReadyMark)(load ? import_functionc(m_handle, "ReadyMark") : nullptr);
			if (m_ReadyMark == nullptr && load)
			{
				throw std::runtime_error("Failed to load ReadyMark");
			}

			m_ReadyPreview = (lpReadyPreview)(load ? import_functionc(m_handle, "ReadyPreview") : nullptr);
			if (m_ReadyPreview == nullptr && load)
			{
				throw std::runtime_error("Failed to load ReadyPreview");
			}

			m_StartReadDataThread = (lpStartReadDataThread)(load ? import_functionc(m_handle, "StartReadDataThread") : nullptr);
			if (m_StartReadDataThread == nullptr && load)
			{
				throw std::runtime_error("Failed to load StartReadDataThread");
			}

			m_ZeroCounter = (lpZeroCounter)(load ? import_functionc(m_handle, "ZeroCounter") : nullptr);
			if (m_ZeroCounter == nullptr && load)
			{
				throw std::runtime_error("Failed to load ZeroCounter");
			}

			m_StopMark = (lpStopMark)(load ? import_functionc(m_handle, "StopMark") : nullptr);
			if (m_StopMark == nullptr && load)
			{
				throw std::runtime_error("Failed to load StopMark");
			}

			m_StopPreview = (lpStopPreview)(load ? import_functionc(m_handle, "StopPreview") : nullptr);
			if (m_StopPreview == nullptr && load)
			{
				throw std::runtime_error("Failed to load StopPreview");
			}

			m_StopCalcData = (lpStopCalcData)(load ? import_functionc(m_handle, "StopCalcData") : nullptr);
			if (m_StopCalcData == nullptr && load)
			{
				throw std::runtime_error("Failed to load StopCalcData");
			}

			m_GetMarkStatus = (lpGetMarkStatus)(load ? import_functionc(m_handle, "GetMarkStatus") : nullptr);
			if (m_GetMarkStatus == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetMarkStatus");
			}

			m_GetMarkTime = (lpGetMarkTime)(load ? import_functionc(m_handle, "GetMarkTime") : nullptr);
			if (m_GetMarkTime == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetMarkTime");
			}

			m_GetMarkCounts = (lpGetMarkCounts)(load ? import_functionc(m_handle, "GetMarkCounts") : nullptr);
			if (m_GetMarkCounts == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetMarkCounts");
			}

			m_GetLaserAndScannerStatus = (lpGetLaserAndScannerStatus)(load ? import_functionc(m_handle, "GetLaserAndScannerStatus") : nullptr);
			if (m_GetLaserAndScannerStatus == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetLaserAndScannerStatus");
			}

			m_GetScannerPosition = (lpGetScannerPosition)(load ? import_functionc(m_handle, "GetScannerPosition") : nullptr);
			if (m_GetScannerPosition == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetScannerPosition");
			}

			m_LaserSignalOn = (lpLaserSignalOn)(load ? import_functionc(m_handle, "LaserSignalOn") : nullptr);
			if (m_LaserSignalOn == nullptr && load)
			{
				throw std::runtime_error("Failed to load LaserSignalOn");
			}

			m_LaserSignalOff = (lpLaserSignalOff)(load ? import_functionc(m_handle, "LaserSignalOff") : nullptr);
			if (m_LaserSignalOff == nullptr && load)
			{
				throw std::runtime_error("Failed to load LaserSignalOff");
			}

			m_MarkCommand_Point = (lpMarkCommand_Point)(load ? import_functionc(m_handle, "MarkCommand_Point") : nullptr);
			if (m_MarkCommand_Point == nullptr && load)
			{
				throw std::runtime_error("Failed to load MarkCommand_Point");
			}

			m_MarkCommand_Vector = (lpMarkCommand_Vector)(load ? import_functionc(m_handle, "MarkCommand_Vector") : nullptr);
			if (m_MarkCommand_Vector == nullptr && load)
			{
				throw std::runtime_error("Failed to load MarkCommand_Vector");
			}

			m_MarkCommand_Bitmap = (lpMarkCommand_Bitmap)(load ? import_functionc(m_handle, "MarkCommand_Bitmap") : nullptr);
			if (m_MarkCommand_Bitmap == nullptr && load)
			{
				throw std::runtime_error("Failed to load MarkCommand_Bitmap");
			}

			m_ChangePensCommand = (lpChangePensCommand)(load ? import_functionc(m_handle, "MarkCommand_Point") : nullptr);
			if (m_ChangePensCommand == nullptr && load)
			{
				throw std::runtime_error("Failed to load MarkCommand_Point");
			}

			m_ChangePensCommand = (lpChangePensCommand)(load ? import_functionc(m_handle, "ChangePensCommand") : nullptr);
			if (m_ChangePensCommand == nullptr && load)
			{
				throw std::runtime_error("Failed to load ChangePensCommand");
			}

			m_EndCommand = (lpEndCommand)(load ? import_functionc(m_handle, "EndCommand") : nullptr);
			if (m_EndCommand == nullptr && load)
			{
				throw std::runtime_error("Failed to load EndCommand");
			}

			m_Goto_XY = (lpGoto_XY)(load ? import_functionc(m_handle, "Goto_XY") : nullptr);
			if (m_Goto_XY == nullptr && load)
			{
				throw std::runtime_error("Failed to load Goto_XY");
			}

			m_JumpCommand = (lpJumpCommand)(load ? import_functionc(m_handle, "JumpCommand") : nullptr);
			if (m_JumpCommand == nullptr && load)
			{
				throw std::runtime_error("Failed to load JumpCommand");
			}

			m_CloseUSBBoard = (lpCloseUSBBoard)(load ? import_functionc(m_handle, "CloseUSB_Board") : nullptr);
			if (m_CloseUSBBoard == nullptr && load)
			{
				throw std::runtime_error("Failed to load CloseUSB_Board");
			}

			m_Write_IO_Port = (lpWrite_IO_Port)(load ? import_functionc(m_handle, "Write_IO_Port") : nullptr);
			if (m_Write_IO_Port == nullptr && load)
			{
				throw std::runtime_error("Failed to load Write_IO_Port");
			}

			m_OutputCommand = (lpOutputCommand)(load ? import_functionc(m_handle, "OutputCommand") : nullptr);
			if (m_OutputCommand == nullptr && load)
			{
				throw std::runtime_error("Failed to load OutputCommand");
			}

			m_GetOutputPortState = (lpGetOutputPortState)(load ? import_functionc(m_handle, "GetOutputPortState") : nullptr);
			if (m_GetOutputPortState == nullptr && load)
			{
				throw std::runtime_error("Failed to load GetOutputPortState");
			}

			return true;
		}

		inline CSC_FUNC_INT DynamicLoaderc::OpenUSB_Board(int deviceIndex, void* handle)
		{
			auto& inst = instancec();
			if (inst.m_OpenUSB_Board)
			{
				return inst.m_OpenUSB_Board(deviceIndex, handle);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::LoadFPGA_FirmwareProgram(char* rbfFilePath)
		{
			auto& inst = instancec();
			if (inst.m_LoadFPGA_FirmwareProgram)
			{
				int i = 0;
				i = inst.m_LoadFPGA_FirmwareProgram(rbfFilePath);
				return i;
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::SetLaserMode(int laserType, int standby, float frequency, float pulseWidth)
		{
			auto& inst = instancec();
			if (inst.m_SetLaserMode)
			{
				return inst.m_SetLaserMode(laserType, standby, frequency, pulseWidth);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::SetSystemParameters(double rangeX, double rangeY, double markStep, double jumpStep, bool exchangeXY, bool invertX, bool invertY, int startMarkMode)
		{
			auto& inst = instancec();
			if (inst.m_SetSystemParameters)
			{
				return inst.m_SetSystemParameters(rangeX, rangeY, exchangeXY, invertX, invertY, startMarkMode);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::SetCorrectParameters_0(double xCorrection, double yCorrection, double xShear, double yShear, double xLadder, double yLadder, double ratioX, double ratioY, double ratioZ)
		{
			auto& inst = instancec();
			if (inst.m_SetCorrectParameters_0)
			{
				return inst.m_SetCorrectParameters_0(xCorrection, yCorrection, xShear, yShear, xLadder, yLadder, ratioX, ratioY, ratioZ);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::SetCorrectParameters_1(double ratioX, double ratioY, double ratioZ, char* filePath)
		{
			auto& inst = instancec();
			if (inst.m_SetCorrectParameters_1)
			{
				return inst.m_SetCorrectParameters_1(ratioX, ratioY, ratioZ, filePath);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_VOID DynamicLoaderc::WriteDataEnd()
		{
			auto& inst = instancec();
			if (inst.m_WriteDataEnd)
			{
				return inst.m_WriteDataEnd();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_VOID DynamicLoaderc::SetOverallMarkCounts(int count)
		{
			auto& inst = instancec();
			if (inst.m_SetOverallMarkCounts)
			{
				return inst.m_SetOverallMarkCounts(count);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::IsMarkEnd()
		{
			auto& inst = instancec();
			if (inst.m_IsMarkEnd)
			{
				return inst.m_IsMarkEnd();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::StartMark()
		{
			auto& inst = instancec();
			if (inst.m_StartMark)
			{
				return inst.m_StartMark();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_UNDIGNED_INT DynamicLoaderc::GetProducedData()
		{
			auto& inst = instancec();
			if (inst.m_GetProducedData)
			{
				return inst.m_GetProducedData();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::DownloadMarkParameters()
		{
			auto& inst = instancec();
			if (inst.m_DownloadMarkParameters)
			{
				return inst.m_DownloadMarkParameters();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::SetMarkParameter(int index, int markCounts, int isBitmap, float markSpeed, float jumpSpeed, float jumpDelay, float polygonDelay, float laserOnDelay, float laserOffDelay, float polygonKillerTime, float laserFrequency, float current, float firstPulseKillerLength, float pulseWidth, float firstPulseWidth, float incrementStep, float dotSpace)
		{
			auto& inst = instancec();
			if (inst.m_SetMarkParameter)
			{
				return inst.m_SetMarkParameter(index, markCounts, isBitmap, markSpeed, jumpSpeed, jumpDelay, polygonDelay, laserOnDelay, laserOffDelay, polygonKillerTime, laserFrequency, current, firstPulseKillerLength, pulseWidth, firstPulseWidth, incrementStep, dotSpace);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::SetFirstMarkParameter(int pen)
		{
			auto& inst = instancec();
			if (inst.m_SetFirstMarkParameter)
			{
				return inst.m_SetFirstMarkParameter(pen);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::ReadyMark()
		{
			auto& inst = instancec();
			if (inst.m_ReadyMark)
			{
				return inst.m_ReadyMark();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::ReadyPreview()
		{
			auto& inst = instancec();
			if (inst.m_ReadyPreview)
			{
				return inst.m_ReadyPreview();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::StartReadDataThread()
		{
			auto& inst = instancec();
			if (inst.m_StartReadDataThread)
			{
				return inst.m_StartReadDataThread();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::StopMark()
		{
			auto& inst = instancec();
			if (inst.m_StopMark)
			{
				return inst.m_StopMark();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::StopPreview()
		{
			auto& inst = instancec();
			if (inst.m_StopPreview)
			{
				return inst.m_StopPreview();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::StopCalcData()
		{
			auto& inst = instancec();
			if (inst.m_StopCalcData)
			{
				return inst.m_StopCalcData();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::GetMarkStatus()
		{
			auto& inst = instancec();
			if (inst.m_GetMarkStatus)
			{
				return inst.m_GetMarkStatus();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_UNDIGNED_LONG DynamicLoaderc::GetMarkTime()
		{
			auto& inst = instancec();
			if (inst.m_GetMarkTime)
			{
				return inst.m_GetMarkTime();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::GetMarkCounts(unsigned char* internalMarkCounts, unsigned char* externalMarkCounts)
		{
			auto& inst = instancec();
			if (inst.m_GetMarkCounts)
			{
				return inst.m_GetMarkCounts(internalMarkCounts, externalMarkCounts);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::GetLaserAndScannerStatus(int* laserStatus, int* scannerStatus)
		{
			auto& inst = instancec();
			if (inst.m_GetLaserAndScannerStatus)
			{
				return inst.m_GetLaserAndScannerStatus(laserStatus, scannerStatus);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::GetScannerPosition(float* xPos, float* yPos)
		{
			auto& inst = instancec();
			if (inst.m_GetScannerPosition)
			{
				return inst.m_GetScannerPosition(xPos, yPos);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::LaserSignalOn()
		{
			auto& inst = instancec();
			if (inst.m_LaserSignalOn)
			{
				return inst.m_LaserSignalOn();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::LaserSignalOff()
		{
			auto& inst = instancec();
			if (inst.m_LaserSignalOff)
			{
				return inst.m_LaserSignalOff();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::MarkCommand_Point(double x, double y, int type, int tp)
		{
			auto& inst = instancec();
			if (inst.m_MarkCommand_Point)
			{
				return inst.m_MarkCommand_Point(x, y, type, tp);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::MarkCommand_Vector(int length, double* sitsetX, double* sitsetY)
		{
			auto& inst = instancec();
			if (inst.m_MarkCommand_Vector)
			{
				return inst.m_MarkCommand_Vector(length, sitsetX, sitsetY);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::MarkCommand_Bitmap(int length, double* sitsetX, double* sitsetY, int* sitsetGray)
		{
			auto& inst = instancec();
			if (inst.m_MarkCommand_Bitmap)
			{
				return inst.MarkCommand_Bitmap(length, sitsetX, sitsetY, sitsetGray);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::ChangePensCommand(unsigned char pen)
		{
			auto& inst = instancec();
			if (inst.m_ChangePensCommand)
			{
				return inst.m_ChangePensCommand(pen);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::EndCommand()
		{
			auto& inst = instancec();
			if (inst.m_EndCommand)
			{
				return inst.m_EndCommand();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::Goto_XY(double x, double y)
		{
			auto& inst = instancec();
			if (inst.m_Goto_XY)
			{
				return inst.m_Goto_XY(x, y);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::JumpCommand(double x, double y)
		{
			auto& inst = instancec();
			if (inst.m_JumpCommand)
			{
				return inst.m_JumpCommand(x, y);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_VOID DynamicLoaderc::CloseUSB_Board()
		{
			auto& inst = instancec();
			if (inst.m_CloseUSBBoard)
			{
				return inst.m_CloseUSBBoard();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_BOOL DynamicLoaderc::Write_IO_Port(unsigned char port)
		{
			auto& inst = instancec();
			if (inst.m_Write_IO_Port)
			{
				return inst.m_Write_IO_Port(port);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_INT DynamicLoaderc::OutputCommand(unsigned char port, int outMode, int level, int outputPulseWidth)
		{
			auto& inst = instancec();
			if (inst.m_OutputCommand)
			{
				return inst.m_OutputCommand(port, outMode, level, outputPulseWidth);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline CSC_FUNC_UNDIGNED_CHAR DynamicLoaderc::GetOutputPortState()
		{
			auto& inst = instancec();
			if (inst.m_GetOutputPortState)
			{
				return inst.m_GetOutputPortState();
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

	} /* namespace dynamics */
} /* namespace CSC_Mark */
	
