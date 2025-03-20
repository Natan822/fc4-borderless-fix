#include <windows.h>
#include <stdio.h>

#include "Proxy.h"

FARPROC p[17];
HMODULE originalDll = NULL;

bool initializeProxy()
{
	if (originalDll != NULL)
	{
		return true;
	}

	char sys32Path[MAX_PATH];
	GetSystemDirectoryA(sys32Path, MAX_PATH);

	char dllPath[MAX_PATH];
	sprintf_s(dllPath, "%s\\version.dll", sys32Path);

	originalDll = LoadLibraryA(dllPath);
	if (originalDll == NULL)
	{
		return false;
	}

	p[0] = GetProcAddress(originalDll, "GetFileVersionInfoA");
	p[1] = GetProcAddress(originalDll, "GetFileVersionInfoByHandle");
	p[2] = GetProcAddress(originalDll, "GetFileVersionInfoExA");
	p[3] = GetProcAddress(originalDll, "GetFileVersionInfoExW");
	p[4] = GetProcAddress(originalDll, "GetFileVersionInfoSizeA");
	p[5] = GetProcAddress(originalDll, "GetFileVersionInfoSizeExA");
	p[6] = GetProcAddress(originalDll, "GetFileVersionInfoSizeExW");
	p[7] = GetProcAddress(originalDll, "GetFileVersionInfoSizeW");
	p[8] = GetProcAddress(originalDll, "GetFileVersionInfoW");
	p[9] = GetProcAddress(originalDll, "VerFindFileA");
	p[10] = GetProcAddress(originalDll, "VerFindFileW");
	p[11] = GetProcAddress(originalDll, "VerInstallFileA");
	p[12] = GetProcAddress(originalDll, "VerInstallFileW");
	p[13] = GetProcAddress(originalDll, "VerLanguageNameA");
	p[14] = GetProcAddress(originalDll, "VerLanguageNameW");
	p[15] = GetProcAddress(originalDll, "VerQueryValueA");
	p[16] = GetProcAddress(originalDll, "VerQueryValueW");

	return true;
}

extern "C"
{
	FARPROC PA = NULL;
	int RunASM();

	void PROXY_GetFileVersionInfoA() {
		PA = p[0];
		RunASM();
	}
	void PROXY_GetFileVersionInfoByHandle() {
		PA = p[1];
		RunASM();
	}
	void PROXY_GetFileVersionInfoExA() {
		PA = p[2];
		RunASM();
	}
	void PROXY_GetFileVersionInfoExW() {
		PA = p[3];
		RunASM();
	}
	void PROXY_GetFileVersionInfoSizeA() {
		PA = p[4];
		RunASM();
	}
	void PROXY_GetFileVersionInfoSizeExA() {
		PA = p[5];
		RunASM();
	}
	void PROXY_GetFileVersionInfoSizeExW() {
		PA = p[6];
		RunASM();
	}
	void PROXY_GetFileVersionInfoSizeW() {
		PA = p[7];
		RunASM();
	}
	void PROXY_GetFileVersionInfoW() {
		PA = p[8];
		RunASM();
	}
	void PROXY_VerFindFileA() {
		PA = p[9];
		RunASM();
	}
	void PROXY_VerFindFileW() {
		PA = p[10];
		RunASM();
	}
	void PROXY_VerInstallFileA() {
		PA = p[11];
		RunASM();
	}
	void PROXY_VerInstallFileW() {
		PA = p[12];
		RunASM();
	}
	void PROXY_VerLanguageNameA() {
		PA = p[13];
		RunASM();
	}
	void PROXY_VerLanguageNameW() {
		PA = p[14];
		RunASM();
	}
	void PROXY_VerQueryValueA() {
		PA = p[15];
		RunASM();
	}
	void PROXY_VerQueryValueW() {
		PA = p[16];
		RunASM();
	}
}
