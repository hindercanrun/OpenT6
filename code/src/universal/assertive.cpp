#include "types.h"

char assertMessage[4096];
char lineBuffer[4096];

bool shouldQuitOnError;

AddressInfo_s g_assertAddress[32];
int g_assertAddressCount;

/*
==============
HideWindowCallback
==============
*/
int HideWindowCallback(HWND__ *hwnd, int lParam)
{
	// fix later
	LONG WindowLongA;
	LONG v3;
	int v4;
	char caption[1024];

	if (!GetWindowTextA(hwnd, caption, 1024) || !strcmp(caption, Com_GetBuildDisplayNameR()))
	{
		WindowLongA = GetWindowLongA(hwnd, -16);
		v3 = GetWindowLongA(hwnd, -20);

		if ((WindowLongA & 0x10000000) != 0)
		{
			v4 = g_hiddenCount;
			g_hwndGame[g_hiddenCount] = hwnd;
			g_hiddenCount = v4 + 1;

			SetWindowLongA(hwnd, -16, WindowLongA & 0xEFFFFFFF);
			SetWindowLongA(hwnd, -20, v3 & 0xFFFFFFF7);
 		}
	}

	return 1;
}

/*
==============
FixWindowsDesktop
==============
*/
void FixWindowsDesktop()
{
	// fix later
	DWORD CurrentThreadId;
	HWND DesktopWindow;
	HDC DC;
	int v3;
	unsigned __int16 *v4;
	int v5;
	unsigned __int16 ramp[3][256];

	ChangeDisplaySettingsA(0, 0);
	CurrentThreadId = GetCurrentThreadId();
	EnumThreadWindows(CurrentThreadId, HideWindowCallback, 0);
	DesktopWindow = GetDesktopWindow();
	DC = GetDC(DesktopWindow);
	v3 = 0;
	v4 = ramp[1];
	v5 = 256;

	do
	{
		*(v4 - 256) = v3;
		*v4 = v3;
		v4[256] = v3;
		v3 += 257;
		++v4;
		--v5;
	}
	while ( v5 );

	SetDeviceGammaRamp(DC, ramp);
	ReleaseDC(DesktopWindow, DC);
}

/*
==============
TRACK_assertive
==============
*/
void TRACK_assertive()
{
	track_static_alloc_internal(assertMessage, 4096, "assertMessage", 0);
	track_static_alloc_internal(lineBuffer, 4096, "lineBuffer", 0);
	track_static_alloc_internal(g_assertAddress, 8704, "g_assertAddress", 0);
}

/*
==============
SkipLines
==============
*/
char SkipLines(int lineCount, _iobuf *fp)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ParseMapFile
==============
*/
bool ParseMapFile(_iobuf *fp, unsigned int baseAddress, const char *mapName)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
GetModuleBase
==============
*/
unsigned int GetModuleBase(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LoadMapFilesForDir
==============
*/
void LoadMapFilesForDir(const char *dir)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
StackTrace_ResolveSymbols
==============
*/
int StackTrace_ResolveSymbols()
{
	if ( !g_inStackTrace )
	{
		g_inStackTrace = 1;
		LoadMapFilesForDir(&pBlock);
		g_inStackTrace = 0;
	}

	return 0;
}

/*
==============
StackTrace_Generate
==============
*/
int StackTrace_Generate(int len, char *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
StackTrace_Walk
==============
*/
int StackTrace_Walk(int ignoreCount, void *context)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
StackTrace_GetAddressInfo
==============
*/
AddressInfo_s *StackTrace_GetAddressInfo(int *addressCount)
{
	if ( addressCount )
	{
		*addressCount = g_assertAddressCount;
	}

	return g_assertAddress;
}

/*
==============
StackTrace_ResetAddressInfo
==============
*/
void StackTrace_ResetAddressInfo()
{
	g_assertAddressCount = 0;
}

/*
==============
CopyMessageToClipboard
==============
*/
void CopyMessageToClipboard(const char *msg)
{
	HWND DesktopWindow;
	HGLOBAL v2;
	void *v3;
	BYTE *v4;
	const char *v5;
	int v6;
	char v7;

	if ( OpenClipboard(GetDesktopWindow()) )
	{
		EmptyClipboard();
		v2 = GlobalAlloc(2u, strlen(msg) + 1);
		v3 = v2;

		if ( v2 )
		{
			v4 = GlobalLock(v2);

			if ( v4 )
			{
				v5 = msg;
				v6 = v4 - msg;

				do
				{
					v7 = *v5;
					v5[v6] = *v5;
					++v5;
				}
				while ( v7 );

				GlobalUnlock(v3);
				SetClipboardData(1u, v3);
			}
		}

		CloseClipboard();
	}
}

/*
==============
AssertNotify
==============
*/
char AssertNotify(int type, AssertOccurance occurance)
{
	const char *text;

	if (AssertCallback)
	{
		AssertCallback(assertMessage);
	}

	if (type)
	{
		if (type == 1)
		{
			text = "SANITY CHECK FAILURE... (this text is on the clipboard)";
		}
		else
		{
			text = "INTERNAL ERROR";
		}
	}
	else
	{
		text = "ASSERTION FAILURE... (this text is on the clipboard)";
	}

	ShowCursor(1);

	if (MessageBoxA(GetActiveWindow(), assertMessage, text, 0x12011u) == 1 && occurance != RECURSIVE)
	{
		if (Sys_IsMiniDumpStarted() && !IsDebuggerPresent())
		{
			RaiseException(1u, 0, 0, 0);
		}

		exit(-1);
	}

	return 1;
}

/*
==============
Assert_BuildAssertMessageWithStack
==============
*/
int Assert_BuildAssertMessageWithStack(const char *expr, const char *extra, const char *filename, int line, int type, int messageLen, char *message)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
IsDebuggerConnected
==============
*/
BOOL IsDebuggerConnected()
{
	return IsDebuggerPresent();
}

/*
==============
RefreshQuitOnErrorCondition
==============
*/
void RefreshQuitOnErrorCondition()
{
	if (Dvar_IsSystemActive())
	{
		if (Dvar_GetBool(quit_on_error) || (Dvar_GetInt(r_vc_compile), shouldQuitOnError = 0, Dvar_GetInt(r_vc_compile) == 2))
		{
			shouldQuitOnError = 1;
		}
	}
}

/*
==============
QuitOnError
==============
*/
bool QuitOnError()
{
	bool result;

	if (!Dvar_IsSystemActive())
	{
		return shouldQuitOnError;
	}

	if (Dvar_GetBool(quit_on_error) || Dvar_GetInt(r_vc_compile) == 2)
	{
		result = 1;
		shouldQuitOnError = 1;
	}
	else
	{
		result = 0;
		shouldQuitOnError = 0;
	}

	return result;
}

