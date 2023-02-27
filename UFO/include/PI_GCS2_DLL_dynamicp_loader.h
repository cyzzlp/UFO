#pragma once

#include "PI_GCS2_DLL.h"
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

#undef PI_DLL_EXPORTS
#define PI_DLL_EXPORTS
#undef PI_FUNC_DECL
#define PI_FUNC_DECL

namespace PI_GCS2_DLL
{
	namespace dynamicp
	{
		typedef PI_FUNC_LONG(*lpPI_EnumerateUSB)(char* szBuffer, long iBufferSize, const char* szFilter);
		typedef PI_FUNC_LONG(*lpPI_ConnectRS232)(long nPortNr, long nBaudRate);
		typedef PI_FUNC_BOOL(*lpPI_TranslateError)(long errNr, char* szBuffer, long iBufferSize);
		typedef PI_FUNC_BOOL(*lpPI_qSAI)(long ID, char* szAxes, int iBufferSize);
		typedef PI_FUNC_VOID(*lpPI_CloseConnection)(long ID);
		typedef PI_FUNC_BOOL(*lpPI_SVO)(long ID, const char* szAxes, const BOOL* pbValueArray);
		typedef PI_FUNC_LONG(*lpPI_GetError)(long ID);
		typedef PI_FUNC_BOOL(*lpPI_MOV)(long ID, const char* szAxes, const double* pdValueArray);
		typedef PI_FUNC_BOOL(*lpPI_qPOS)(long ID, const char* szAxes, double* pdValueArray);
		typedef PI_FUNC_BOOL(*lpPI_IsMoving)(long ID, const char* szAxes, BOOL* pbValueArray);
		typedef PI_FUNC_LONG(*lpPI_ConnectUSB)(const char* szDescription);
		typedef PI_FUNC_BOOL(*lpPI_IsConnected)(long ID);

		class DynamicLoaderp
		{
		private:
			DynamicLoaderp();

			static DynamicLoaderp& instancep()
			{
				static DynamicLoaderp DynamicLoaderp{};
				return DynamicLoaderp;
			}
			bool loadLibp(const char* file);
			void unloadp();
			bool setPointersp(bool load);

		public:
			~DynamicLoaderp();

			static bool isLoadedp();

			static PI_FUNC_LONG PI_EnumerateUSB(char* szBuffer, long iBufferSize, const char* szFilter);
			static PI_FUNC_LONG PI_ConnectRS232(long nPortNr, long nBaudRate);
			static PI_FUNC_BOOL PI_TranslateError(long errNr, char* szBuffer, long iBufferSize);
			static PI_FUNC_BOOL PI_qSAI(long ID, char* szAxes, int iBufferSize);
			static PI_FUNC_VOID PI_CloseConnection(long ID);
			static PI_FUNC_BOOL PI_SVO(long ID, const char* szAxes, const BOOL* pbValueArray);
			static PI_FUNC_LONG PI_GetError(long ID);
			static PI_FUNC_BOOL PI_MOV(long ID, const char* szAxes, const double* pdValueArray);
			static PI_FUNC_BOOL PI_qPOS(long ID, const char* szAxes, double* pdValueArray);
			static PI_FUNC_BOOL PI_IsMoving(long ID, const char* szAxes, BOOL* pbValueArray);
			static PI_FUNC_LONG PI_ConnectUSB(const char* szDescription);
			static PI_FUNC_BOOL PI_IsConnected(long ID);

		private:
			void* m_handle = nullptr;
			lpPI_EnumerateUSB m_PI_EnumerateUSB{};
			lpPI_ConnectRS232 m_PI_ConnectRS232{};
			lpPI_TranslateError m_PI_TranslateError{};
			lpPI_qSAI m_PI_qSAI{};
			lpPI_CloseConnection m_PI_CloseConnection{};
			lpPI_SVO m_PI_SVO{};
			lpPI_GetError m_PI_GetError{};
			lpPI_MOV m_PI_MOV{};
			lpPI_qPOS m_PI_qPOS{};
			lpPI_IsMoving m_PI_IsMoving{};
			lpPI_ConnectUSB m_PI_ConnectUSB{};
			lpPI_IsConnected m_PI_IsConnected{};
		};

		inline void* import_functionp(void* module, const char* proc_name)
		{
			#ifdef __linux__
				return dlsym(module, proc_name);
			#else
				return GetProcAddress(static_cast<HMODULE>(module), proc_name);
			#endif
		}

		inline DynamicLoaderp::DynamicLoaderp()
		{
			#if defined _WIN32 || defined _WIN64
			size_t sz = 0;
			if (_wgetenv_s(&sz, NULL, 0, L"PI_SDK_PATH") == 0 && sz > 0)
			{
				std::vector<wchar_t> env_csc_mark(sz);
				if (_wgetenv_s(&sz, env_csc_mark.data(), sz, L"PI_SDK_PATH") == 0)
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

			loadLibp("PI_GCS2_DLL.dll");
			#endif
		}

		inline DynamicLoaderp::~DynamicLoaderp()
		{
			if (m_handle != nullptr)
			{
				unloadp();
			}
		}

		inline bool DynamicLoaderp::isLoadedp()
		{
			auto&& inst = instancep();
			return inst.m_handle != nullptr;
		}

		inline void DynamicLoaderp::unloadp()
		{
			setPointersp(false);

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

		inline bool DynamicLoaderp::loadLibp(const char* file)
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
						setPointersp(true);
						ret = true;
					}
					catch (const std::exception&)
					{
						unloadp();
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

		inline bool DynamicLoaderp::setPointersp(bool load)
		{
			m_PI_EnumerateUSB = (lpPI_EnumerateUSB)(load ? import_functionp(m_handle, "PI_EnumerateUSB") : nullptr);
			if (m_PI_EnumerateUSB == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_EnumerateUSB");
			}

			m_PI_ConnectRS232 = (lpPI_ConnectRS232)(load ? import_functionp(m_handle, "PI_ConnectRS232") : nullptr);
			if (m_PI_ConnectRS232 == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_ConnectRS232");
			}

			m_PI_TranslateError = (lpPI_TranslateError)(load ? import_functionp(m_handle, "PI_TranslateError") : nullptr);
			if (m_PI_TranslateError == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_TranslateError");
			}

			m_PI_qSAI = (lpPI_qSAI)(load ? import_functionp(m_handle, "PI_qSAI") : nullptr);
			if (m_PI_qSAI == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_qSAI");
			}

			m_PI_CloseConnection = (lpPI_CloseConnection)(load ? import_functionp(m_handle, "PI_CloseConnection") : nullptr);
			if (m_PI_CloseConnection == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_CloseConnection");
			}

			m_PI_SVO = (lpPI_SVO)(load ? import_functionp(m_handle, "PI_SVO") : nullptr);
			if (m_PI_SVO == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_SVO");
			}

			m_PI_GetError = (lpPI_GetError)(load ? import_functionp(m_handle, "PI_GetError") : nullptr);
			if (m_PI_GetError == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_GetError");
			}

			m_PI_MOV = (lpPI_MOV)(load ? import_functionp(m_handle, "PI_MOV") : nullptr);
			if (m_PI_MOV == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_MOV");
			}

			m_PI_qPOS = (lpPI_qPOS)(load ? import_functionp(m_handle, "PI_qPOS") : nullptr);
			if (m_PI_qPOS == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_qPOS");
			}

			m_PI_IsMoving = (lpPI_IsMoving)(load ? import_functionp(m_handle, "PI_IsMoving") : nullptr);
			if (m_PI_IsMoving == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_IsMoving");
			}

			m_PI_ConnectUSB = (lpPI_ConnectUSB)(load ? import_functionp(m_handle, "PI_ConnectUSB") : nullptr);
			if (m_PI_ConnectUSB == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_ConnectUSB");
			}

			m_PI_IsConnected = (lpPI_IsConnected)(load ? import_functionp(m_handle, "PI_IsConnected") : nullptr);
			if (m_PI_IsConnected == nullptr && load)
			{
				throw std::runtime_error("Failed to load PI_IsConnected");
			}

			return true;
		}

		inline PI_FUNC_LONG DynamicLoaderp::PI_EnumerateUSB(char* szBuffer, long iBufferSize, const char* szFilter)
		{
			auto& inst = instancep();
			if (inst.m_PI_EnumerateUSB)
			{
				return inst.m_PI_EnumerateUSB(szBuffer, iBufferSize, szFilter);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_LONG DynamicLoaderp::PI_ConnectRS232(long nPortNr, long nBaudRate)
		{
			auto& inst = instancep();
			if (inst.m_PI_ConnectRS232)
			{
				return inst.m_PI_ConnectRS232(nPortNr, nBaudRate);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_TranslateError(long errNr, char* szBuffer, long iBufferSize)
		{
			auto& inst = instancep();
			if (inst.m_PI_TranslateError)
			{
				return inst.m_PI_TranslateError(errNr, szBuffer, iBufferSize);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_qSAI(long ID, char* szAxes, int iBufferSize)
		{
			auto& inst = instancep();
			if (inst.m_PI_qSAI)
			{
				return inst.m_PI_qSAI(ID, szAxes, iBufferSize);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_VOID DynamicLoaderp::PI_CloseConnection(long ID)
		{
			auto& inst = instancep();
			if (inst.m_PI_CloseConnection)
			{
				return inst.m_PI_CloseConnection(ID);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_SVO(long ID, const char* szAxes, const BOOL* pbValueArray)
		{
			auto& inst = instancep();
			if (inst.m_PI_SVO)
			{
				return inst.m_PI_SVO(ID, szAxes, pbValueArray);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_LONG DynamicLoaderp::PI_GetError(long ID)
		{
			auto& inst = instancep();
			if (inst.m_PI_GetError)
			{
				return inst.m_PI_GetError(ID);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_MOV(long ID, const char* szAxes, const double* pdValueArray)
		{
			auto& inst = instancep();
			if (inst.m_PI_MOV)
			{
				return inst.m_PI_MOV(ID, szAxes, pdValueArray);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_qPOS(long ID, const char* szAxes, double* pdValueArray)
		{
			auto& inst = instancep();
			if (inst.m_PI_qPOS)
			{
				return inst.m_PI_qPOS(ID, szAxes, pdValueArray);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_IsMoving(long ID, const char* szAxes, BOOL* pbValueArray)
		{
			auto& inst = instancep();
			if (inst.m_PI_IsMoving)
			{
				return inst.m_PI_IsMoving(ID, szAxes, pbValueArray);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_LONG DynamicLoaderp::PI_ConnectUSB(const char* szDescription)
		{
			auto& inst = instancep();
			if (inst.m_PI_ConnectUSB)
			{
				return inst.m_PI_ConnectUSB(szDescription);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline PI_FUNC_BOOL DynamicLoaderp::PI_IsConnected(long ID)
		{
			auto& inst = instancep();
			if (inst.m_PI_IsConnected)
			{
				return inst.m_PI_IsConnected(ID);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}
	}
}
