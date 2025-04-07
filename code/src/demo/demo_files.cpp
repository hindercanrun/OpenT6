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
		s_fileHandler.ptr = NULL;
		s_fileHandler.size = NULL;
		s_fileHandler.offset = NULL;
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
		assert(s_fileHandler.ptr == NULL);

		s_fileHandler.ptr = Z_VirtualAlloc(size, "demoDownloadBuffer", 12);
		memset(s_fileHandler.ptr, 0, size);//why?
		s_fileHandler.offset = NULL;
		s_fileHandler.size = size;
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
		assert(s_fileHandler.ptr != NULL);
		Z_VirtualFree(s_fileHandler.ptr);
		s_fileHandler.ptr = NULL;
	}
}

/*
==============
Demo_IsStreamBufferAllocated
==============
*/
bool Demo_IsStreamBufferAllocated()
{
	return !demo_usefilesystem->current.enabled && s_fileHandler.ptr != NULL;
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
#if defined(XENON) || defined(RELEASE)
		if (DmMapDevkitDrive())
		{
			Com_PrintError(CON_CHANNEL_DONT_FILTER, "ERROR: Couldnt map devkit drive\n");
		}
		else
		{
			FS_BuildOSPath("DEVKIT:", "demos", nullptr, demoPath);
		}
#else
		FS_BuildOSPath(fs_homepath->current.string, "demos", nullptr, demoPath);
#endif
	}
}

/*
==============
Demo_OpenFileWrite
==============
*/
int Demo_OpenFileWrite(const char *filename, const char *dir, bool supressErrors)
{
	if (!demo_usefilesystem->current.enabled)
	{
		return TRUE;
	}

	char name[260];
	Com_sprintf(name, sizeof(name), "%s", filename);

	int handle = FS_SV_FOpenFileWrite(name, "demos");
	if (handle)
	{
		return handle;
	}
	if (!supressErrors)
	{
		Com_PrintError(CON_CHANNEL_DONT_FILTER, "ERROR: couldn't open file for write.\n");
	}

	return FALSE;
}

/*
==============
Demo_OpenFileRead
==============
*/
int Demo_OpenFileRead(const char *filename, const char *dir, bool supressErrors)
{
	if (!demo_usefilesystem->current.enabled)
	{
		assert(s_fileHandler.ptr != NULL);
		return TRUE;
	}

	char ospath[256];
	Com_sprintf(ospath, sizeof(ospath), "%s", filename);

	int handle;
	int size = FS_SV_FOpenFileRead(ospath, "demos", &handle);
	if (handle && size)
	{
		return handle;
	}
	else
	{
		if (!supressErrors)
		{
			Com_PrintError(CON_CHANNEL_DONT_FILTER, "ERROR: couldn't open file for read.\n");
		}

		if (handle)
		{
			FS_FCloseFile(handle);
		}
	}

	return FALSE;
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
	}
	else
	{
		if (!s_fileHandler.ptr)
		{
			return false;
		}

		memcpy(&s_fileHandler.ptr[s_fileHandler.offset], buffer, len);
		s_fileHandler.offset += len;
	}

	return len;
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
		s_fileHandler.offset = NULL;
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
	if (demo_usefilesystem->current.enabled)
	{
		return FS_Seek(handle, offset, origin);
	}

	switch (origin)
	{
	case 0:
		s_fileHandler.offset += offset;
		return offset;
	case 1:
		s_fileHandler.offset = offset + s_fileHandler.size;
		return offset;
	case 2:
		s_fileHandler.offset = offset;
		return offset;
	default:
		assertMsg(false, va("Bad origin %i in FS_Seek", origin));
		return false;
	}
}

