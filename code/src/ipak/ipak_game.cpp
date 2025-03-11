#include "types.h"

bool s_adjacencyInfoStale = FALSE;

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
IPak_MarkAdjacencyInfoAsStale
==============
*/
void IPak_MarkAdjacencyInfoAsStale()
{
	s_adjacencyInfoStale = TRUE;
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

