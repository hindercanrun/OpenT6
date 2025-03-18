#include "types.h"

struct tlFileBuf
{
  unsigned __int8 *Buf;
  unsigned int Size;
  unsigned int UserData;
};

struct tlSystemCallbacks
{
  bool (__cdecl *ReadFile)(const char *, tlFileBuf *, unsigned int, unsigned int);
  void (__cdecl *ReleaseFile)(tlFileBuf *);
  void (__cdecl *CriticalError)(const char *);
  void (__cdecl *Warning)(const char *);
  void (__cdecl *DebugPrint)(const char *);
  void *(__cdecl *MemAlloc)(unsigned int, unsigned int, unsigned int);
  void *(__cdecl *MemRealloc)(void *, unsigned int, unsigned int, unsigned int);
  void (__cdecl *MemFree)(void *);
};

HunkUser *s_tlHunkUser;

/*
==============
TL_Warning
==============
*/
void TL_Warning(const char *Text)
{
	Com_PrintWarning(CON_CHANNEL_TL, "TL Warning: %s\n", Text);
}

/*
==============
TL_ReadFile
==============
*/
bool TL_ReadFile()
{
	TL_Warning("TL_ReadFile: no implementation");
	return 0;
}

/*
==============
TL_ReleaseFile
==============
*/
void TL_ReleaseFile()
{
	TL_Warning("TL_ReleaseFile: no implementation");
}

/*
==============
TL_DebugPrint
==============
*/
void TL_DebugPrint(const char *Text)
{
	Com_Printf(CON_CHANNEL_TL, Text);
}

/*
==============
TL_MemAlloc
==============
*/
void *TL_MemAlloc(unsigned int Size, unsigned int Align)
{
	return Hunk_UserAlloc(s_tlHunkUser, Size, Align, 0);
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
	assert(msg);
}

/*
==============
Sys_SetupTLCallbacks
==============
*/
void Sys_SetupTLCallbacks(int hunkMemSize)
{
	s_tlHunkUser = Hunk_UserCreate(hunkMemSize, HU_SCHEME_DEFAULT, 4, 0, "TL_MemAlloc support", 40);

	tlSystemCallbacks callbacks;
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

