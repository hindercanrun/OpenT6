#include "types.h"

/*
==============
Demo_InitFileHandlerSystem
==============
*/
void Demo_InitFileHandlerSystem()
{
	if (!demo_usefilesystem->current.enabled)
	{
		*&s_fileHandler.ptr = nullptr;
		s_fileHandler.offset = 0;
	}
}

/*
==============
Demo_AllocateMemoryFromStreamBuffer
==============
*/
void Demo_AllocateMemoryFromStreamBuffer(int size)
{
	if (!demo_usefilesystem->current.enabled)
	{
		assertMsg(s_fileHandler.ptr, "(s_fileHandler.ptr == 0)");
		s_fileHandler.ptr = Z_VirtualAlloc(size, "demoDownloadBuffer", 12);

		memset(s_fileHandler.ptr, 0, size);
		s_fileHandler.size = size;
		s_fileHandler.offset = 0;
	}
}

/*
==============
Demo_ReturnStreamBufferMemory
==============
*/
void Demo_ReturnStreamBufferMemory()
{
	if (!demo_usefilesystem->current.enabled)
	{
		assertMsg(!s_fileHandler.ptr, "(s_fileHandler.ptr != 0)");
		Z_VirtualFree(s_fileHandler.ptr);
		s_fileHandler.ptr = 0;
	}
}

/*
==============
Demo_IsStreamBufferAllocated
==============
*/
bool Demo_IsStreamBufferAllocated()
{
	return !demo_usefilesystem->current.enabled && s_fileHandler.ptr != 0;
}

/*
==============
Demo_GetCurrentAllocatedFileSize
==============
*/
int Demo_GetCurrentAllocatedFileSize()
{
	return s_fileHandler.size;
}

/*
==============
Demo_GetStreamAllocatedBuffer
==============
*/
char *Demo_GetStreamAllocatedBuffer()
{
	return s_fileHandler.ptr;
}

/*
==============
Demo_GetFileReadOffset
==============
*/
int Demo_GetFileReadOffset()
{
	return s_fileHandler.offset;
}

/*
==============
Demo_GetDemoPath
==============
*/
void Demo_GetDemoPath(const char *demoPath)
{
	if (demo_usefilesystem->current.enabled)
	{
		FS_BuildOSPath(fs_homepath->current.string, "demos", nullptr, demoPath);
	}
}

/*
==============
Demo_OpenFileWrite
==============
*/
int Demo_OpenFileWrite(const char *filename, const char *dir, bool supressErrors)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_OpenFileRead
==============
*/
int Demo_OpenFileRead(const char *filename, const char *dir, bool supressErrors)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_Write
==============
*/
int Demo_Write(const void *buffer, int len, int handle)
{
	if (demo_usefilesystem->current.enabled)
	{
		return FS_WriteToDemo(buffer, len, handle);
	}

	if (Demo_IsRecording())
	{
		Demo_SaveToStreamBuffer(buffer, len);
		return len;
	}
	else if (s_fileHandler.ptr)
	{
		memcpy(&s_fileHandler.ptr[s_fileHandler.offset], buffer, len);

		s_fileHandler.offset += len;
		return len;
	}
	else
	{
		return 0;
	}
}

/*
==============
Demo_Read
==============
*/
int Demo_Read(void *buffer, int len, int handle)
{
	if (demo_usefilesystem->current.enabled)
	{
		return FS_Read(buffer, len, handle);
	}

	memcpy(buffer, &s_fileHandler.ptr[s_fileHandler.offset], len);
	s_fileHandler.offset += len;
	return len;
}

/*
==============
Demo_CloseFile
==============
*/
void Demo_CloseFile(int handle)
{
	if (!demo_usefilesystem->current.enabled)
	{
		s_fileHandler.offset = 0;
	}

	FS_FCloseFile(handle);
}

/*
==============
Demo_SeekFile
==============
*/
int Demo_SeekFile(int handle, int offset, int origin)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

