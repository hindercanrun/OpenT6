#include "types.h"
#include "vars.h"

/*
==============
Com_GetBspLumpCountForVersion
==============
*/
unsigned int Com_GetBspLumpCountForVersion(const int version)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Com_ValidateBspLumpData
==============
*/
const void *Com_ValidateBspLumpData(LumpType type, unsigned int offset, unsigned int length, unsigned int elemSize, unsigned int *count)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_GetBspLump
==============
*/
const void *Com_GetBspLump(char *a1, LumpType type, unsigned int elemSize, unsigned int *count)
{
	assert(Com_IsBspLoaded());

	if (comBspGlob.header->version > 18)
	{
		unsigned int offset = 8 * comBspGlob.header->chunkCount + 12;
		for (unsigned int chunkIter = 0; chunkIter < comBspGlob.header->chunkCount; ++chunkIter)
		{
			if (comBspGlob.header->chunks[chunkIter].type == type)
			{
				return Com_ValidateBspLumpData(type, offset, comBspGlob.header->chunks[chunkIter].length, elemSize, count);
			}

			offset += (comBspGlob.header->chunks[chunkIter].length + 3) & 0xFFFFFFFC;
		}
		*count = 0;
		return 0;
	}
	else if (type < Com_GetBspLumpCountForVersion(comBspGlob.header->version))
	{
		return Com_ValidateBspLumpData(
				type,
				comBspGlob.header->chunks[type].type,
				*(&comBspGlob.header->chunkCount + 2 * type),
				elemSize,
				count);
	}
	else
	{
		*count = 0;
		return 0;
	}
}

/*
==============
Com_ReadLumpOutOfBspAtOffset
==============
*/
const void *Com_ReadLumpOutOfBspAtOffset(int h, LumpType type, unsigned int offset, unsigned int length, unsigned int elemSize, unsigned int *count)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_ReadLumpOutOfBsp
==============
*/
const void *Com_ReadLumpOutOfBsp(int h, LumpType type, unsigned int elemSize, unsigned int *count)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_LoadBspLump
==============
*/
const void *Com_LoadBspLump(const char *mapname, LumpType type, unsigned int elemSize, unsigned int *count)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_UnloadBspLump
==============
*/
void Com_UnloadBspLump(LumpType type)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Com_BspHasLump
==============
*/
BOOL Com_BspHasLump(LumpType a1, LumpType type)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Com_GetBspVersion
==============
*/
unsigned int Com_GetBspVersion()
{
	assert(!Com_IsBspLoaded());
	return comBspGlob.header->version;
}

/*
==============
Com_GetBspChecksum
==============
*/
unsigned int Com_GetBspChecksum()
{
	assert(!Com_IsBspLoaded());
	return comBspGlob.checksum;
}

/*
==============
Com_CheckVersionLumpCountError
==============
*/
bool Com_CheckVersionLumpCountError(int version)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Com_LoadBsp
==============
*/
void Com_LoadBsp(const char *filename)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Com_UnloadBsp
==============
*/
void Com_UnloadBsp()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Com_CleanupBsp
==============
*/
void Com_CleanupBsp()
{
	if (!Com_IsBspLoaded())
	{
		assert(!Com_IsBspLoaded());
	}

	comBspGlob.loadedLumpData = 0;
	if (Com_IsBspLoaded())
	{
		Com_UnloadBsp();
	}
}

/*
==============
Com_EntityString
==============
*/
const char *Com_EntityString(LumpType a1, char *a2, char *a3, int *numEntityChars)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_SaveLump
==============
*/
void Com_SaveLump(LumpType type, const void *newLump, unsigned int size, ComSaveLumpBehavior behavior)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Com_GetHunkStringCopy
==============
*/
const char *Com_GetHunkStringCopy(const char *string)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_GetLightDefName
==============
*/
const char *Com_GetLightDefName(const char *defName, const ComPrimaryLight *primaryLights, unsigned int primaryLightCount)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_LoadWorld_FastFile
==============
*/
void Com_LoadWorld_FastFile(const char *name)
{
	ComWorld *asset = DB_FindXAssetHeader(ASSET_TYPE_COMWORLD, name, 1, -1).comWorld;
	assert(asset == &comWorld);
	assert(comWorld.isInUse);
}

/*
==============
Com_ShutdownWorld
==============
*/
void Com_ShutdownWorld()
{
	LONG Target;

	comWorld.isInUse = 0;
	Target = 0;
	InterlockedExchange(&Target, 0);
}

/*
==============
Com_LoadPrimaryLights
==============
*/
void Com_LoadPrimaryLights(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Com_LoadWorld_LoadObj
==============
*/
void Com_LoadWorld_LoadObj(const char *name)
{
	assert(Com_IsBspLoaded());

	Com_LoadPrimaryLights();
	Com_LoadWaterData();
	Com_LoadBurnableData();

	comWorld.name = Com_GetHunkStringCopy(name);
	comWorld.isInUse = true;
}

/*
==============
Com_LoadWorld
==============
*/
void Com_LoadWorld(const char *name)
{
	if (!useFastFile->current.enabled)
	{
		Com_LoadWorld_LoadObj(name);
	}

	Com_LoadWorld_FastFile(name);
}

