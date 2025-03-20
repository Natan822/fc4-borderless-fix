#include <Windows.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>

#include "Proxy.h"
#include "Utils.h"

const char* FC4_WINDOW_NAME = "FarCry®4";

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGHT = 1080;

DWORD WINAPI fixWindow(LPVOID lpParam)
{
	int targetWidth = 0;
	int targetHeight = 0;

	if (!Utils::IO::parseResolution(&targetWidth, &targetHeight))
	{
		::MessageBoxA(
			0,
			"Please configure your resolution in the borderless-fix.ini file.",
			"FC4 Borderless Fix",
			MB_OK);
		::ExitProcess(1);
	}

	HWND handle = FindWindowA(NULL, FC4_WINDOW_NAME);
	while (handle == NULL)
	{
		handle = FindWindowA(NULL, FC4_WINDOW_NAME);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	RECT rect = {};
	while (true)
	{
		if (::GetWindowRect(handle, &rect) == 0)
		{
			break;
		}

		int currentWidth = rect.right - rect.left;
		int currentHeight = rect.bottom - rect.top;

		if (currentWidth > targetWidth || currentHeight > targetHeight)
		{
			::SetWindowPos(handle, HWND_NOTOPMOST, 0, 0, targetWidth, targetHeight, 0);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (!initializeProxy())
			{
				return FALSE;
			}

			HANDLE hThread = ::CreateThread(NULL, 0, fixWindow, NULL, 0, NULL);
			if (hThread)
			{
				::CloseHandle(hThread);
			}
			break;
		}
		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			if (originalDll != NULL)
			{
				::FreeLibrary(originalDll);
			}
			break;
	}
	return TRUE;
}