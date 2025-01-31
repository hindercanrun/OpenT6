#include "types.h"

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
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
IPak_RemovePackfile
==============
*/
int IPak_RemovePackfile(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
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
	if (buffer >= 2)
	{
		assertMsg("(unsigned)(buffer) < (unsigned)(2)", "buffer doesn't index IPAK_INDEX_BUFFER_COUNT\n\t%i not in [0, %i)", buffer, 2);
	}

	if (!*&work[1].imageParts[2 * buffer + 260])
	{
		assert("(work->indexBufferState[ buffer ] != 0)");
	}

	while (*&work[1].imageParts[2 * buffer + 260] == 1)
	{
		Sys_CheckQuitRequest();
		NET_Sleep(1u);
	}

	if (*&work[1].imageParts[2 * buffer + 260] == 3)
	{
		Com_PrintError(41, "Error while reading ipak %s index data, offset %d\n", work->pak->name, *&work[1].imageParts[2 * buffer + 256]);
		memset(&work->indexBuffer[buffer][34], 255, 0x10000);
	}
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
	assert(!work->pak);

	int v1 = 0;
	unsigned __int8 *v2 = &work->indexBuffer[0][34];
	unsigned __int16 *v3 = &work[1].imageParts[260];

	do
	{
		if (*v3 == 1)
		{
			if (v1 >= 2)
			{
				assertMsg("(unsigned)(buffer) < (unsigned)(2)", "buffer doesn't index IPAK_INDEX_BUFFER_COUNT\n\t%i not in [0, %i)", v1, 2);
			}

			if (!*v3)
			{
				assert("(work->indexBufferState[ buffer ] != 0)");
			}

			while (*v3 == 1)
			{
				Sys_CheckQuitRequest();
				NET_Sleep(1u);
			}

			if (*v3 == 3)
			{
				Com_PrintError(41, "Error while reading ipak %s index data, offset %d\n", work->pak->name, *(v3 - 2));
				memset(v2, 255, 0x10000);
			}
		}

		++v1;
		v3 += 2;
		v2 += 0x10000;
	}
	while (v1 < 2);

	work->pak = 0;
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
	UNIMPLEMENTED(__FUNCTION__);
}

