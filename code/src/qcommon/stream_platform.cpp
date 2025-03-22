#include "types.h"

/*
==============
Stream_CheckLockedFile
==============
*/
void Stream_CheckLockedFile(const char *name)
{
    char lock_name[256];

    _snprintf(lock_name, 0x100u, "%s~lk", name);

    _WIN32_FILE_ATTRIBUTE_DATA lock_attr;

    if (GetFileAttributesExA(lock_name, GetFileExInfoStandard, &lock_attr))
    {
        _WIN32_FILE_ATTRIBUTE_DATA orig_attr;

        if (GetFileAttributesExA(name, GetFileExInfoStandard, &orig_attr))
        {
            if (CompareFileTime(&orig_attr.ftLastWriteTime, &lock_attr.ftLastWriteTime) >= 0)
                DeleteFileA(lock_name);
            else
                MoveFileExA(lock_name, name, 1u);
        }
        else
        {
            MoveFileA(lock_name, name);
        }
    }
}

/*
==============
Stream_SeekInternal
==============
*/
void Stream_SeekInternal(void *fh, unsigned __int64 offset)
{
    void* v2; // [esp-10h] [ebp-10h]

    if (fh != (void*)-1)
    {
        v2 = fh;
        fh = 0;
        SetFilePointer(v2, offset, (PLONG)&fh, 0);
    }
}

/*
==============
Stream_ReadInternal
==============
*/
char Stream_ReadInternal(void *fh, unsigned __int64 readOffset, unsigned __int8 *dest, unsigned __int64 nBytes, unsigned __int64 *bytesRead)
{
    void* v5; // esi
    DWORD v7; // edi
    void* v8; // eax
    DWORD FileSize; // eax
    unsigned __int64* v10; // ecx
    DWORD LastError; // eax

    v5 = fh;

    if (fh == (void*)-1)
        return 0;

    v7 = SetFilePointer(fh, 0, 0, 1u);

    if (ReadFile(v5, dest, nBytes, (LPDWORD)&fh, 0))
    {
        v8 = fh;

        if (!fh)
        {
            FileSize = GetFileSize(v5, 0);
            if (FileSize < v7)
                v8 = fh;
            else
                v8 = (void*)(FileSize - v7);
        }

        v10 = bytesRead;

        if (bytesRead)
        {
            *(_DWORD*)bytesRead = v8;
            *((_DWORD*)v10 + 1) = 0;
        }

        return 1;
    }

    else
    {
        LastError = GetLastError();
        Com_Printf(10, "Stream_ReadInternal: Error reading a file (0x%08x,%d)\n", LastError, LastError);
        return 0;
    }
}

/*
==============
Stream_CloseInternal
==============
*/
void Stream_CloseInternal(void *fh)
{
    if (fh != (void*)-1)
        CloseHandle(fh);
}

/*
==============
CG_Destructible_GetModelIndexFromLabel
==============
*/
int CG_Destructible_GetModelIndexFromLabel()
{
    return 5;
}

/*
==============
Stream_OpenInternal
==============
*/
int Stream_OpenInternal(const char *name, int flags, void **fh, __int64 *fileSize)
{
    HANDLE FileA; // eax
    DWORD LastError; // eax
    DWORD v7; // eax
    DWORD v8; // esi
    __int64 *v9; // eax
    DWORD v10; // eax
    __int64 *v11; // eax
  
	Stream_CheckLockedFile(name);

	HANDLE file = CreateFileA(name, 0x80000000, 1u, 0, 3u, 0, 0);
    *fh = FileA;
	if (!file == nullptr)
	{
		DWORD size = GetFileSize(FileA, &fh);
		if (!size == nullptr)
		{
            v8 = v7;
            v9 = fileSize;
            *(fileSize + 1) = fh;
            *v9 = v8;
		}

		Com_Printf(10, "Stream_GetFileSizeInternal: Couldn't get size. (0x%08x,%d)\n", GetLastError(), GetLastError());

		*(fileSize + 1) = -1;
		*fileSize = -1;

		return false;
	}

	if ((flags & 2) == 0)
	{
		Com_Printf(10, "Stream_OpenInternal: Couldn't open \"%s\". (0x%08x,%d)\n", name, GetLastError(), GetLastError());
	}

	return nullptr;
}

