#pragma once

#include "CH375DLL.h"
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

#undef SHUT_DLL_EXPORTS
#define SHUT_DLL_EXPORTS
#undef SHUT_FUNC_DECL
#define SHUT_FUNC_DECL

namespace SHUT_CONTROL
{
	namespace dynamics
	{
		typedef SHUT_FUNC_HANDLE(*lpCH375OpenDevice)(ULONG iIndex);
		typedef SHUT_FUNC_BOOL(*lpCH375SetTimeout)(ULONG iIndex, ULONG iWriteTimeout, ULONG iReadTimeout);
		typedef SHUT_FUNC_BOOL(*lpCH375WriteData)(ULONG iIndex, PVOID iBuffer, PULONG ioLength);
		typedef SHUT_FUNC_VOID(*lpCH375CloseDevice)(ULONG iIndex);


		class DynamicLoader_S
		{
		private:
			DynamicLoader_S();

			static DynamicLoader_S& instancec()
			{
				static DynamicLoader_S DynamicLoader_S{};
				return DynamicLoader_S;
			}
			bool loadLibc(const char* file);
			void unloadc();
			bool setPointersc(bool load);

		public:
			~DynamicLoader_S();

			static bool isLoadedc();
			static SHUT_FUNC_HANDLE CH375OpenDevice(ULONG iIndex);
			static SHUT_FUNC_BOOL CH375SetTimeout(ULONG iIndex, ULONG iWriteTimeout, ULONG iReadTimeout);
			static SHUT_FUNC_BOOL CH375WriteData(ULONG iIndex, PVOID iBuffer, PULONG ioLength);
			static SHUT_FUNC_VOID CH375CloseDevice(ULONG iIndex);

		private:
			void* m_handle = nullptr;
			lpCH375OpenDevice m_CH375OpenDevice{};
			lpCH375SetTimeout m_CH375SetTimeout{};
			lpCH375WriteData m_CH375WriteData{};
			lpCH375CloseDevice m_CH375CloseDevice{};
		};

		inline void* import_functionc(void* module, const char* proc_name)
		{
			#ifdef __linux__
				return dlsym(module, proc_name);
			#else
				return GetProcAddress(static_cast<HMODULE>(module), proc_name);
			#endif
		}

		inline DynamicLoader_S::DynamicLoader_S()
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

			loadLibc("CH375DLL.DLL");
			#endif
		}

		inline DynamicLoader_S::~DynamicLoader_S()
		{
			if (m_handle != nullptr)
			{
				unloadc();
			}
		}

		inline bool DynamicLoader_S::isLoadedc()
		{
			auto&& inst = instancec();
			return inst.m_handle != nullptr;
		}

		inline void DynamicLoader_S::unloadc()
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

		inline bool DynamicLoader_S::loadLibc(const char* file)
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

		inline bool DynamicLoader_S::setPointersc(bool load)
		{
			m_CH375OpenDevice = (lpCH375OpenDevice)(load ? import_functionc(m_handle, "CH375OpenDevice") : nullptr);
			if (m_CH375OpenDevice == nullptr && load)
			{
				throw std::runtime_error("Failed to load OpenUSB_Board");
			}

			m_CH375SetTimeout = (lpCH375SetTimeout)(load ? import_functionc(m_handle, "CH375SetTimeout") : nullptr);
			if (m_CH375SetTimeout == nullptr && load)
			{
				throw std::runtime_error("Failed to load OpenUSB_Board");
			}

			m_CH375WriteData = (lpCH375WriteData)(load ? import_functionc(m_handle, "CH375WriteData") : nullptr);
			if (m_CH375WriteData == nullptr && load)
			{
				throw std::runtime_error("Failed to load OpenUSB_Board");
			}

			m_CH375CloseDevice = (lpCH375CloseDevice)(load ? import_functionc(m_handle, "CH375CloseDevice") : nullptr);
			if (m_CH375CloseDevice == nullptr && load)
			{
				throw std::runtime_error("Failed to load OpenUSB_Board");
			}
		}

		inline SHUT_FUNC_HANDLE DynamicLoader_S::CH375OpenDevice(ULONG iIndex)
		{
			auto& inst = instancec();
			if (inst.m_CH375OpenDevice)
			{
				return inst.m_CH375OpenDevice(iIndex);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline SHUT_FUNC_BOOL DynamicLoader_S::CH375SetTimeout(ULONG iIndex, ULONG iWriteTimeout, ULONG iReadTimeout)
		{
			auto& inst = instancec();
			if (inst.m_CH375SetTimeout)
			{
				return inst.m_CH375SetTimeout(iIndex, iWriteTimeout, iReadTimeout);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline SHUT_FUNC_BOOL DynamicLoader_S::CH375WriteData(ULONG iIndex, PVOID iBuffer, PULONG ioLength)
		{
			auto& inst = instancec();
			if (inst.m_CH375WriteData)
			{
				return inst.m_CH375WriteData(iIndex, iBuffer, ioLength);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}

		inline SHUT_FUNC_VOID DynamicLoader_S::CH375CloseDevice(ULONG iIndex)
		{
			auto& inst = instancec();
			if (inst.m_CH375CloseDevice)
			{
				return inst.m_CH375CloseDevice(iIndex);
			}
			else
			{
				throw std::runtime_error("Library not loaded!");
			}
		}
	}
}