#include "PI.h"

long(__stdcall* PIConnectUSB)(const char* szDescription);
long(__stdcall* PIConnectUSBWithBaudRate)(const char* szDescription, long iBaudRate);
long(__stdcall* PIEnumerateUSB)(char* szBuffer, long iBufferSize, const char* szFilter);
long(__stdcall* PIConnectRS232)(long nPortNr, long nBaudRate);
BOOL(__stdcall* PITranslateError)(long errNr, char* szBuffer, long iBufferSize);
BOOL(__stdcall* PIqSAI)(long ID, char* szAxes, int iBufferSize);
void(__stdcall* PICloseConnection)(long ID);
BOOL(__stdcall* PISVO)(long ID, const char* szAxes, const BOOL* pbValueArray);
long(__stdcall* PIGetError)(long ID);
BOOL(__stdcall* PIMOV)(long ID, const char* szAxes, const double* pdValueArray);
BOOL(__stdcall* PIqPOS)(long ID, const char* szAxes, double* pdValueArray);
BOOL(__stdcall* PIIsMoving)(long ID, const char* szAxes, BOOL* pbValueArray);
BOOL(__stdcall* PIIsConnected)(long ID);

HINSTANCE PIDll;

long __stdcall PI_ConnectUSB(const char* szDescription)
{
	int returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIConnectUSB = GetProcAddress(PIDll, "PI_ConnectUSB");
		if (PIConnectUSB)
		{
			returnValue = PIConnectUSB(szDescription);
		}
	}
	return returnValue;
}

long __stdcall PI_EnumerateUSB(char* szBuffer, long iBufferSize, const char* szFilter)
{
	long returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIEnumerateUSB = GetProcAddress(PIDll, "PI_EnumerateUSB");
		if (PIEnumerateUSB)
		{
			returnValue = PIEnumerateUSB(szBuffer, iBufferSize, szFilter);
		}
	}
	return returnValue;
}

long __stdcall PI_ConnectRS232(long nPortNr, long nBaudRate)
{
	int returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIConnectRS232 = GetProcAddress(PIDll, "PI_ConnectRS232");
		if (PIConnectRS232)
		{
			returnValue = PIConnectRS232(nPortNr, nBaudRate);
		}
	}
	return returnValue;
}

BOOL __stdcall PI_TranslateError(long errNr, char* szBuffer, long iBufferSize)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PITranslateError = GetProcAddress(PIDll, "PI_TranslateError");
		if (PITranslateError)
		{
			returnValue = PITranslateError(errNr, szBuffer, iBufferSize);
		}
	}
	return returnValue;
}

BOOL __stdcall PI_qSAI(long ID, char* szAxes, int iBufferSize)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIqSAI = GetProcAddress(PIDll, "PI_qSAI");
		if (PIqSAI)
		{
			returnValue = PIqSAI(ID, szAxes, iBufferSize);
		}
	}
	return returnValue;
}

void __stdcall PI_CloseConnection(long ID)
{
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PICloseConnection = GetProcAddress(PIDll, "PI_CloseConnection");
		if (PICloseConnection)
		{
			PICloseConnection(ID);
		}
	}
}

BOOL __stdcall PI_SVO(long ID, const char* szAxes, const BOOL* pbValueArray)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PISVO = GetProcAddress(PIDll, "PI_SVO");
		if (PISVO)
		{
			returnValue = PISVO(ID, szAxes, pbValueArray);
		}
	}
	return returnValue;
}

long __stdcall PI_GetError(long ID)
{
	int returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIGetError = GetProcAddress(PIDll, "PI_GetError");
		if (PIGetError)
		{
			returnValue = PIGetError(ID);
		}
	}
	return returnValue;
}

BOOL __stdcall PI_MOV(long ID, const char* szAxes, const double* pdValueArray)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIMOV = GetProcAddress(PIDll, "PI_MOV");
		if (PIqSAI)
		{
			returnValue = PIMOV(ID, szAxes, pdValueArray);
		}
	}
	return returnValue;
}

BOOL __stdcall PI_qPOS(long ID, const char* szAxes, double* pdValueArray)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIqPOS = GetProcAddress(PIDll, "PI_qPOS");
		if (PIqPOS)
		{
			returnValue = PIqPOS(ID, szAxes, pdValueArray);
		}
	}
	return returnValue;
}

BOOL __stdcall PI_IsMoving(long ID, const char* szAxes, BOOL* pbValueArray)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIIsMoving = GetProcAddress(PIDll, "PI_IsMoving");
		if (PIIsMoving)
		{
			returnValue = PIIsMoving(ID, szAxes, pbValueArray);
		}
	}
	return returnValue;
}

BOOL __stdcall PI_IsConnected(long ID)
{
	BOOL returnValue = 0;
	PIDll = LoadLibrary(TEXT("PI.dll"));
	if (PIDll)
	{
		(FARPROC)PIIsConnected = GetProcAddress(PIDll, "PI_IsConnected");
		if (PIIsConnected)
		{
			returnValue = PIIsConnected(ID);
		}
	}
	return returnValue;
}