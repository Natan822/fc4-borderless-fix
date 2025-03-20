#include <stdio.h>
#include <string>
#include <Windows.h>

#include "Utils.h"

namespace Utils
{
	namespace IO
	{
		const char* CONFIG_FILE_PATH = "./borderless-fix.ini";

		bool parseResolution(int* width, int* height)
		{
			int outWidth = ::GetPrivateProfileIntA("resolution", "width", 0, CONFIG_FILE_PATH);
			int outHeight = ::GetPrivateProfileIntA("resolution", "height", 0, CONFIG_FILE_PATH);

			const DWORD LAST_ERROR = ::GetLastError();
			if (LAST_ERROR)
			{
				if (LAST_ERROR == 2)
				{
					::MessageBoxA(
						0,
						"borderless-fix.ini not found.",
						"FC4 Borderless Fix",
						MB_OK);
				}
				else
				{
					char errorMessage[64];
					sprintf_s(errorMessage, "Unknown error: %d", LAST_ERROR);
					::MessageBoxA(
						0,
						errorMessage,
						"FC4 Borderless Fix",
						MB_OK);
				}
				::ExitProcess(LAST_ERROR);
			}

			if (outWidth > 0 && outHeight > 0)
			{
				*width = outWidth;
				*height = outHeight;
				return true;
			}
			return false;
		}
	}
}