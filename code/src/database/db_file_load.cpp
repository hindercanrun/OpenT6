#include "types.h"

/*
==============
DB_Init_Reading
==============
*/
void DB_Init_Reading()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_GetLoadedFraction
==============
*/
double DB_GetLoadedFraction()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DB_Reliable_FsOpen_ReadOnly
==============
*/
int DB_Reliable_FsOpen_ReadOnly(const char *path, unsigned int *outClumpSize)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DB_FileReadCompletionCallback
==============
*/
void DB_FileReadCompletionCallback(int id, stream_status result, unsigned int numBytesRead, void *user)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_SetZoneSizeLevelCount
==============
*/
void DB_SetZoneSizeLevelCount(int levelZoneCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_ResetZoneSize
==============
*/
void DB_ResetZoneSize(int trackLoadProgress)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_IsMinimumFastFileLoaded
==============
*/
bool DB_IsMinimumFastFileLoaded()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DB_ResetMinimumFastFileLoaded
==============
*/
void DB_ResetMinimumFastFileLoaded()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_ReadData
==============
*/
int DB_ReadData()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
RecomputeLocks
==============
*/
void RecomputeLocks()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_WaitXFileStage
==============
*/
void DB_WaitXFileStage(int buffer_index)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_CancelLoadXFile
==============
*/
void DB_CancelLoadXFile()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_DecompressIOStream
==============
*/
void DB_DecompressIOStream(DBDecompressCmd_t *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_WaitWorkerCmd
==============
*/
void DB_WaitWorkerCmd(DB_LOAD_STREAM *stream)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
TestBoundryCondition
==============
*/
char TestBoundryCondition(unsigned __int8 *pos, int len)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
AdvanceRead
==============
*/
void AdvanceRead(bool advance)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CopyFromDecompressBufferNullTerminal
==============
*/
void CopyFromDecompressBufferNullTerminal(unsigned __int8 *pos, int *size_copied)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_LoadXFileData
==============
*/
void DB_LoadXFileData(unsigned __int8 *pos, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_LoadXFileDataNullTerminated
==============
*/
int DB_LoadXFileDataNullTerminated(unsigned __int8 *pos)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ValidateFileHeader
==============
*/
char *ValidateFileHeader(bool *fileIsSecure, int *fileVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
#if SHIT
	char magic[8];

	if (memcmp(magic, "TAff0100", 8u)
		&& memcmp(magic, "TAffu100", 8u)
		&& memcmp(magic, "TAffsvu100", 8u)
		&& memcmp(magic, "TAffx100", 8u))
	{
		Com_Error(ERR_DROP, "Fastfile for zone '%s' is corrupt or unreadable.", g_load.filename);
	}

	unsigned int version = *g_load.stream.next_in;
	if (version != 147)
	{
#if defined(MULTIPLAYER_DEDICATED_SERVER) || defined(MULTIPLAYER)
		//if (((((v6 << 16) | v6 & 0xFF00) << 8) | ((HIWORD(v6) | &g_sd.voiceDecodeBuffer[817536] & v6) >> 8)) == 0x93) // terrible
		if (version == 0x93) // 147
		{
			Com_Error(
				ERR_DROP,
				"Fastfile for zone '%s' is RIGHT VERSION( %d), but the WRONG PLATFORM!!",
				g_load.filename,
				version,
				147);
		}
#endif

		if (version >= 0x93) // 147
		{
			Com_Error(
				ERR_DROP,
				"Fastfile for zone '%s' is newer than client executable (version %d, expecting %d)",
				g_load.filename,
				version,
				147);
		}
		else
		{
			Com_Error(
				ERR_DROP,
				"Fastfile for zone '%s' is out of date (version %d, expecting %d)",
				g_load.filename,
				version,
				147);
		}
	}


#if 0
	int v2; // ecx
	unsigned __int8 *ioBuffer; // esi
	unsigned int v4; // eax
	char v5; // bl
	unsigned int v6; // eax
	unsigned __int8 *v7; // esi
	unsigned int v9; // eax
	int v10; // ecx
	unsigned int v11; // eax
	int v12; // ecx
	const char *v13; // edi
	LocalClientNum_t v14; // [esp+0h] [ebp-20h]
	LocalClientNum_t v15; // [esp+0h] [ebp-20h]
	char magic[8]; // [esp+14h] [ebp-Ch]

	v2 = 0;
	ioBuffer = g_load.ioBuffer;
	*fileVersion = 0;
	g_NumStreams = 4;
	*magic = *ioBuffer;
	*&magic[4] = *(ioBuffer + 1);
	v4 = 8;

	while ( *&magic[v2] == *&aTaff0100[v2] )
	{
		v4 -= 4;
		v2 += 4;

		if ( v4 < 4 )
		{
			*fileVersion = 0;
			*fileIsSecure = 1;
		LABEL_5:
			v5 = 0;
		LABEL_6:
			v6 = *(ioBuffer + 2);
			v7 = ioBuffer + 12;

			if ( v6 == 147 )
			{
				if ( *fileVersion == g_load.requiredVersion )
				{
					if ( !destructible_ent_aa::process_collision(v14) || (v13 = "loading a client fastfile on a server not supported", v5) )
					{
						v13 = 0;
					}

					if ( !destructible_ent_aa::process_collision(v15) && v5 )
					{
						v13 = "loading a server fastfile on a client not supported";
					}

					g_load.ioBufferOffset += v7 - g_load.ioBuffer;
					return v13;
				}
				else
				{
					return va("Fastfile is out of date");
				}
			}
			else if ( ((((v6 << 16) | v6 & 0xFF00) << 8) | ((HIWORD(v6) | &g_sd.voiceDecodeBuffer[817536] & v6) >> 8)) == 0x93 )
			{
				return va("Fastfile for zone '%s' is RIGHT VERSION( %d), but the WRONG PLATFORM!!", g_load.filename, 147);
			}
			else if ( v6 >= 0x93 )
			{
				return va("Fastfile for zone '%s' is newer than client executable (version %d, expecting %d)", g_load.filename, v6, 147);
			}
			else
			{
				return va("Fastfile for zone '%s' is out of date (version %d, expecting %d)", g_load.filename, v6, 147);
			}
		}
	}

	v9 = 8;
	v10 = 0;

	while ( *&magic[v10] == *&aTaffu100[v10] )
	{
		v9 -= 4;
		v10 += 4;
		if ( v9 < 4 )
		{
			*fileVersion = 0;
			*fileIsSecure = 0;
			goto LABEL_5;
		}
	}

	v11 = 8;
	v12 = 0;

	while ( *&magic[v12] == *&aTasvu100[v12] )
	{
		v11 -= 4;
		v12 += 4;
		if ( v11 < 4 )
		{
			*fileVersion = 0;
			*fileIsSecure = 0;
			v5 = 1;
			goto LABEL_6;
		}
	}

	return va("Fastfile for zone '%s' is corrupt or unreadable.", g_load.filename);
#endif
#endif
}

/*
==============
DB_LoadedExternalData
==============
*/
void DB_LoadedExternalData(int size)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_DecompressIOStreamWorkerCallback
==============
*/
int DB_DecompressIOStreamWorkerCallback(jqBatch *batch)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DB_LoadXFile
==============
*/
BOOL DB_LoadXFile(const char *path, int f, const char *filename, XBlock *blocks, void (*interrupt)(), unsigned __int8 *buf, int allocType, int flags, int requiredVersion, unsigned int desiredReadBytes)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

