#include "ipak_public.h"

#define IPAK_MAX_LOADED_PACKFILES

bool s_adjacencyInfoStale = FALSE;

struct IPakSection
{
  unsigned int type;
  unsigned int offset;
  unsigned int size;
  unsigned int itemCount;
};

struct IPakLoadedPackfile
{
  char name[64];
  IPakSection data;
  IPakSection index;
  int fh;
  int refCount;
  int priority;
};

IPakLoadedPackfile s_loadedPackfiles[16];



/*
==============
IPak_ProcessString

name is guessed
==============
*/
char *IPak_ProcessString(char *dest, const char *src)
{
	char *d = dest;
	while ((*d++ = *src++) != '\0');

	char *exclamation = strchr(dest, '!');
	if (exclamation)
	{
		*exclamation = '\0';
	}

	return exclamation;
}

/*
==============
IPak_IndexToName
==============
*/
const char *IPak_IndexToName(unsigned int index)
{
	assert(
		(unsigned)(index) < (unsigned)(16),
		"index doesn't index IPAK_MAX_LOADED_PACKFILES\n\t%i not in [0, %i)",
		index,
		16);

	IPakLoadedPackfile *packfile = &s_loadedPackfiles[index];

	if (packfile->refCount <= 0)
	{
		return "IPAK NOT LOADED";
	}

	return packfile->name;
}


/*
==============
IPak_IndexToFileID
==============
*/
int IPak_IndexToFileID(unsigned int index)
{
	assertMsg(
		(unsigned)(index) < (unsigned)(16),
		"index doesn't index IPAK_MAX_LOADED_PACKFILES\n\t%i not in [0, %i)",
		index,
		16);

	IPakLoadedPackfile *packfile = &s_loadedPackfiles[index];

	if (packfile->refCount <= 0)
	{
		return -16777217;
	}

	return packfile->fh;
}


/*
==============
IPak_FindPackfile
==============
*/
IPakLoadedPackfile *IPak_FindPackfile(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
IPak_RemovePackfile
==============
*/
int IPak_RemovePackfile(const char *name)
{
	PIXBeginNamedEvent(-1, "IPak_RemovePackfile");

	assert(Sys_IsMainThread() || Sys_IsRenderThread());

	IPakLoadedPackfile *pak = IPak_FindPackfile(name);
	if (!pak)
	{
		return FALSE;
	}

	assert(pak->refCount > 0);

	if (pak->refCount-- == 1)
	{
		Stream_CloseFile(pak->fh);
		pak->fh = -16777217;
		Com_Printf(41, "Removed ipak file: %s\n", pak->name);

		s_adjacencyInfoStale = TRUE;
	}

	return TRUE;
}

/*
==============
IPak_MarkAdjacencyInfoAsStale
==============
*/
void IPak_MarkAdjacencyInfoAsStale()
{
	s_adjacencyInfoStale = TRUE;
}

/*
==============
IPak_IndexReadCallback
==============
*/
void IPak_IndexReadCallback(int id, stream_status result, unsigned int numBytesRead, void *user)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_ReadIndexData
==============
*/
void IPak_ReadIndexData(IPakWorkData *work, int buffer)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_WaitReadIndexData
==============
*/
void IPak_WaitReadIndexData(IPakWorkData *work, int buffer)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_BeginIndexRead
==============
*/
void IPak_BeginIndexRead(IPakWorkData *work, IPakLoadedPackfile *pak)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_CurrentIndexEntry
==============
*/
char IPak_CurrentIndexEntry(int a1, IPakWorkData *work, IPakIndexEntry *entry)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
IPak_NextIndexEntry
==============
*/
char IPak_NextIndexEntry(int a1, IPakWorkData *work, IPakIndexEntry *entry)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
IPak_EndIndexRead
==============
*/
void IPak_EndIndexRead(IPakWorkData *work)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_CompareImagePartHashes
==============
*/
int IPak_CompareImagePartHashes(const void *A, const void *B)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
IPak_CompareImageOffsets
==============
*/
int IPak_CompareImageOffsets(const void *A, const void *B)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
IPak_BuildAdjacencyInfo
==============
*/
void IPak_BuildAdjacencyInfo(const char *a1, unsigned __int8 *workBuffer, int workBufferSize)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_InvalidateImages
==============
*/
void IPak_InvalidateImages()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_RemovePackfilesForZone
==============
*/
void IPak_RemovePackfilesForZone(const char *zoneName)
{
	static char zoneNameRoot[64];
	PIXBeginNamedEvent(-1, "IPak_RemovePackfilesForZone");

	const char *name = 0;
	strcpy(zoneNameRoot, zoneName);
	strchr(zoneNameRoot, 0x21u);

	static BYTE *v1;
	if (v1)
	{
	  *v1 = 0;
	}

	while (KeyValuePairs_GetNextValue("ipak_read", zoneNameRoot, &name))
	{
		IPak_RemovePackfile(name);
	}

	IPak_InvalidateImages();
}

