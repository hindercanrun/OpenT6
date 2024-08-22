#include "types.h"

HunkUser *s_tlHunkUser;

/*
==============
TL_Warning
==============
*/
void TL_Warning(const char *Text)
{
	Com_PrintWarning(22, "TL Warning: %s\n", Text);
}

/*
==============
TL_ReadFile
==============
*/
bool TL_ReadFile()
{
	Com_PrintWarning(22, "TL Warning: %s\n", "TL_ReadFile: no implementation");
	return 0;
}

/*
==============
TL_ReleaseFile
==============
*/
void TL_ReleaseFile()
{
	Com_PrintWarning(22, "TL Warning: %s\n", "TL_ReleaseFile: no implementation");
}

/*
==============
TL_DebugPrint
==============
*/
void TL_DebugPrint(const char *Text)
{
	Com_Printf(22, "%s", Text);
}

/*
==============
TL_MemAlloc
==============
*/
void *TL_MemAlloc(unsigned int Size, unsigned int Align)
{
	Sys_EnterCriticalSection(CRITSECT_TL_MEMALLOC);
	void* v2 = Hunk_UserAlloc(s_tlHunkUser, Size, Align, 0);
	Sys_LeaveCriticalSection(CRITSECT_TL_MEMALLOC);

	return v2;
}

/*
==============
TL_MemFree
==============
*/
void TL_MemFree(void *Ptr)
{
	Hunk_UserFree(s_tlHunkUser, Ptr);
}

/*
==============
TL_CriticalError
==============
*/
void TL_CriticalError(const char *msg)
{
	// nothing
}

/*
==============
Sys_SetupTLCallbacks
==============
*/
void Sys_SetupTLCallbacks(int hunkMemSize)
{
	tlSystemCallbacks callbacks;

	s_tlHunkUser = Hunk_UserCreate(hunkMemSize, HU_SCHEME_DEFAULT, 4u, 0, "TL_MemAlloc support", 40);

	callbacks.ReadFile = TL_ReadFile;
	callbacks.ReleaseFile = TL_ReleaseFile;
	callbacks.CriticalError = TL_CriticalError;
	callbacks.Warning = TL_Warning;
	callbacks.DebugPrint = TL_DebugPrint;
	callbacks.MemAlloc = TL_MemAlloc;
	callbacks.MemRealloc = nullptr;
	callbacks.MemFree = TL_MemFree;

	tlSetSystemCallbacks(&callbacks);
}

