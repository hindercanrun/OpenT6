#pragma once

#include "types.h"

char *IPak_ProcessString(char *dest, const char *src);// should probably be const char*
const char *IPak_IndexToName(unsigned int index);
int IPak_IndexToFileID(unsigned int index);
IPakLoadedPackfile *IPak_FindPackfile(const char *name);
int IPak_RemovePackfile(const char *name);
void IPak_MarkAdjacencyInfoAsStale();
void IPak_IndexReadCallback(int id, stream_status result, unsigned int numBytesRead, void *user);
void IPak_ReadIndexData(IPakWorkData *work, int buffer);
void IPak_WaitReadIndexData(IPakWorkData *work, int buffer);
void IPak_BeginIndexRead(IPakWorkData *work, IPakLoadedPackfile *pak);
char IPak_CurrentIndexEntry(int a1, IPakWorkData *work, IPakIndexEntry *entry);
char IPak_NextIndexEntry(int a1, IPakWorkData *work, IPakIndexEntry *entry);
void IPak_EndIndexRead(IPakWorkData *work);
int IPak_CompareImagePartHashes(const void *A, const void *B);
int IPak_CompareImageOffsets(const void *A, const void *B);
void IPak_BuildAdjacencyInfo(const char *a1, unsigned __int8 *workBuffer, int workBufferSize);
void IPak_InvalidateImages();
void IPak_RemovePackfilesForZone(const char *zoneName);

