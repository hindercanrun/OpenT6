#include "types.h"
#include "vars.h"

/*
==============
Com_GetBspLumpCountForVersion
==============
*/
unsigned int Com_GetBspLumpCountForVersion(const int version)
{
	assertMsg(
		6 <= version && version <= 18,
        "version not in [OLDEST_BSP_VERSION, 18]\n\t%i not in [%i, %i]",
        version,
        6,
        18);
	return unkown_string[version + 2];
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
	assert(comBspGlob.loadedLumpData != NULL);
	assert(
		comBspGlob.loadedLumpType == type,
		"comBspGlob.loadedLumpType == type\n\t%i, %i",
		comBspGlob.loadedLumpType,
		type);

	if (!comBspGlob.header)
	{
		Hunk_ClearTempMemoryHigh();
	}

	comBspGlob.loadedLumpData = NULL;
}

/*
==============
Com_BspHasLump
==============
*/
BOOL Com_BspHasLump(LumpType type)
{
	unsigned int count;
	Com_GetBspLump(type, 1, &count);
	return count != NULL;
}

/*
==============
Com_GetBspVersion
==============
*/
unsigned int Com_GetBspVersion()
{
	assert(Com_IsBspLoaded());
	return comBspGlob.header->version;
}

/*
==============
Com_GetBspChecksum
==============
*/
unsigned int Com_GetBspChecksum()
{
	assert(Com_IsBspLoaded());
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
	assert(Com_IsBspLoaded());
	assert(comBspGlob.loadedLumpData == NULL);

	ProfLoad_Begin("Unload bsp file");
	Z_Free(comBspGlob.header, 12);

	comBspGlob.header = NULL;
	comBspGlob.name[0] = NULL;

	ProfLoad_End();

	if (comBspGlob.header)
	{
		assert(!Com_IsBspLoaded());
	}
}

/*
==============
Com_CleanupBsp
==============
*/
void Com_CleanupBsp()
{
	comBspGlob.loadedLumpData = NULL;

	if (comBspGlob.header)
	{
		Com_UnloadBsp();

		// assert if it's still loaded
		if (comBspGlob.header)
		{
			assert(!Com_IsBspLoaded());
		}
	}
}

/*
==============
Com_EntityString
==============
*/
const char *Com_EntityString(int *numEntityChars)
{
	assert(Com_IsBspLoaded());

	unsigned int count;
	const char *entityString = (const char *)Com_GetBspLump(LUMP_ENTITIES, 1, &count);
	if (numEntityChars)
	{
		*numEntityChars = count;
	}

	return entityString;
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
	unsigned int length = strlen(string);
	unsigned __int8 *hunkCopy = (unsigned __int8 *)Hunk_AllocAlign(length + 1, 1, "Com_GetLightDefName", 14);
	memcpy(hunkCopy, string, length + 1);
	return (const char *)hunkCopy;
}

/*
==============
Com_GetLightDefName
==============
*/
const char *Com_GetLightDefName(
	const char *defName,
	const ComPrimaryLight *primaryLights,
	unsigned int primaryLightCount)
{
	for (unsigned int primaryLightIndex = 0; primaryLightIndex < primaryLightCount; ++primaryLightIndex)
	{
		if (primaryLights[primaryLightIndex].defName && !strcmp(defName, primaryLights[primaryLightIndex].defName))
		{
			return primaryLights[primaryLightIndex].defName;
		}
	}

	return Com_GetHunkStringCopy(defName);
}

/*
==============
Com_LoadWorld_FastFile
==============
*/
void Com_LoadWorld_FastFile(const char *name)
{
	DB_FindXAssetHeader(ASSET_TYPE_COMWORLD, name, true, -1).comWorld;
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
	comWorld.isInUse = FALSE;
}

/*
==============
Com_LoadPrimaryLight_DiskPrimaryLight_Version55_
==============
*/
void Com_LoadPrimaryLight_DiskPrimaryLight_Version55_(
	ComPrimaryLight *out,
	const DiskPrimaryLight_Version55 *in,
	unsigned int lightIndex)
{
	out->type = in->type;
	out->canUseShadowMap = in->canUseShadowMap;
	out->shadowmapVolume = in->shadowmapVolume;
	out->cullDist = in->cullDist;
	out->exponent = in->exponent;
	out->priority = in->priority;

	out->color[0] = in->color[0];
	out->color[1] = in->color[1];
	out->color[2] = in->color[2];

	out->dir[0] = in->dir[0];
	out->dir[1] = in->dir[1];
	out->dir[2] = in->dir[2];

	out->origin[0] = in->origin[0];
	out->origin[1] = in->origin[1];
	out->origin[2] = in->origin[2];

	out->radius = in->radius;
	out->cosHalfFovOuter = in->cosHalfFovOuter;
	out->cosHalfFovInner = in->cosHalfFovInner;
	out->rotationLimit = in->rotationLimit;
	out->translationLimit = in->translationLimit;

	if (in->type && in->type != 1)
	{
		out->defName = Com_GetLightDefName(in->defName, comWorld.primaryLights, lightIndex);

		if (out->cosHalfFovOuter >= out->cosHalfFovInner)
		{
			out->cosHalfFovInner = (float)(out->cosHalfFovOuter * 0.75f) + 0.25f;
		}
	
		if (out->rotationLimit == 1.0f)
		{
			out->cosHalfFovExpanded = out->cosHalfFovOuter;
		}
		else if (out->cosHalfFovOuter < out->rotationLimit)
		{
			out->cosHalfFovExpanded = CosOfSumOfArcCos(out->cosHalfFovOuter, out->rotationLimit);
		}
		else
		{
			out->cosHalfFovExpanded = -1.0f;
		}
	}
	else
	{
		out->defName = NULL;
		out->cosHalfFovExpanded = in->cosHalfFovOuter;
	}

	out->useCookie = in->useCookie;

	out->diffuseColor[0] = in->color[0];
	out->diffuseColor[1] = in->color[1];
	out->diffuseColor[2] = in->color[2];
	out->diffuseColor[3] = 0.0f;

	out->dAttenuation = in->dAttenuation;
	out->falloff.v[0] = in->cutOn;
	out->falloff.v[1] = in->radius;

	out->falloff[0] = in->cutOn;
	out->falloff[1] = in->radius;
	out->falloff[2] = (float)((float)(in->radius - in->cutOn) * in->nearEdge) + in->cutOn;
	out->falloff[3] = (float)((float)(in->radius - in->cutOn) * in->farEdge) + in->cutOn;

	out->angle[0] = in->angle[0];
	out->angle[1] = in->angle[1];
	out->angle[2] = in->angle[2];

	out->roundness = in->roundness;
	out->mipDistance = in->mipDistance;

	out->aAbB[0] = in->aAbB[0];
	out->aAbB[1] = in->aAbB[1];
	out->aAbB[2] = in->aAbB[2];
	out->aAbB[3] = in->aAbB[3];

	out->cookieControl0[0] = in->cookieControl0[0];
	out->cookieControl0[1] = in->cookieControl0[1];
	out->cookieControl0[2] = in->cookieControl0[2];
	out->cookieControl0[3] = in->cookieControl0[3];

	out->cookieControl1[0] = in->cookieControl1[0];
	out->cookieControl1[1] = in->cookieControl1[1];
	out->cookieControl1[2] = in->cookieControl1[2];
	out->cookieControl1[3] = in->cookieControl1[3];

	out->cookieControl2[0] = in->cookieControl2[0];
	out->cookieControl2[1] = in->cookieControl2[1];
	out->cookieControl2[2] = in->cookieControl2[2];
	out->cookieControl2[3] = in->cookieControl2[3];
}

/*
==============
Com_LoadPrimaryLight_DiskPrimaryLight_
==============
*/
void Com_LoadPrimaryLight_DiskPrimaryLight_(
	ComPrimaryLight *out,
	const DiskPrimaryLight *in,
	unsigned int lightIndex)
{
	out->type = in->type;
	out->canUseShadowMap = in->canUseShadowMap;
	out->shadowmapVolume = in->shadowmapVolume;
	out->cullDist = in->cullDist;
	out->exponent = in->exponent;
	out->priority = in->priority;

	out->color[0] = in->color[0];
	out->color[1] = in->color[1];
	out->color[2] = in->color[2];

	out->dir[0] = in->dir[0];
	out->dir[1] = in->dir[1];
	out->dir[2] = in->dir[2];

	out->origin[0] = in->origin[0];
	out->origin[1] = in->origin[1];
	out->origin[2] = in->origin[2];

	out->radius = in->radius;
	out->cosHalfFovOuter = in->cosHalfFovOuter;
	out->cosHalfFovInner = in->cosHalfFovInner;
	out->rotationLimit = in->rotationLimit;
	out->translationLimit = in->translationLimit;

	if (in->type && in->type != 1)
	{
		out->defName = Com_GetLightDefName(in->defName, comWorld.primaryLights, lightIndex);

		if (out->cosHalfFovOuter >= out->cosHalfFovInner)
		{
			out->cosHalfFovInner = (float)(out->cosHalfFovOuter * 0.75f) + 0.25f;
		}
	
		if (out->rotationLimit == 1.0f)
		{
			out->cosHalfFovExpanded = out->cosHalfFovOuter;
		}
		else if (out->cosHalfFovOuter < out->rotationLimit)
		{
			out->cosHalfFovExpanded = CosOfSumOfArcCos(out->cosHalfFovOuter, out->rotationLimit);
		}
		else
		{
			out->cosHalfFovExpanded = -1.0f;
		}
	}
	else
	{
		out->defName = NULL;
		out->cosHalfFovExpanded = in->cosHalfFovOuter;
	}

	out->useCookie = in->useCookie;

	out->diffuseColor[0] = in->color[0];
	out->diffuseColor[1] = in->color[1];
	out->diffuseColor[2] = in->color[2];
	out->diffuseColor[3] = 0.0f;

	out->dAttenuation = in->dAttenuation;

	out->falloff[0] = in->cutOn;
	out->falloff[1] = in->radius;
	out->falloff[2] = (float)((float)(in->radius - in->cutOn) * in->nearEdge) + in->cutOn;
	out->falloff[3] = (float)((float)(in->radius - in->cutOn) * in->farEdge) + in->cutOn;

	out->angle[0] = in->angle[0];
	out->angle[1] = in->angle[1];
	out->angle[2] = in->angle[2];

	out->roundness = in->roundness;
	out->mipDistance = in->mipDistance;

	out->aAbB[0] = in->aAbB[0];
	out->aAbB[1] = in->aAbB[1];
	out->aAbB[2] = in->aAbB[2];
	out->aAbB[3] = in->aAbB[3];

	out->cookieControl0[0] = in->cookieControl0[0];
	out->cookieControl0[1] = in->cookieControl0[1];
	out->cookieControl0[2] = in->cookieControl0[2];
	out->cookieControl0[3] = in->cookieControl0[3];

	out->cookieControl1[0] = in->cookieControl1[0];
	out->cookieControl1[1] = in->cookieControl1[1];
	out->cookieControl1[2] = in->cookieControl1[2];
	out->cookieControl1[3] = in->cookieControl1[3];

	out->cookieControl2[0] = in->cookieControl2[0];
	out->cookieControl2[1] = in->cookieControl2[1];
	out->cookieControl2[2] = in->cookieControl2[2];
	out->cookieControl2[3] = in->cookieControl2[3];
}

/*
==============
Com_LoadPrimaryLights
==============
*/
void Com_LoadPrimaryLights()
{
	const DiskPrimaryLight *BspLump = 0;

	unsigned int version = comBspGlob.header->version;
	if (version >= 55)
	{
		unsigned int diskLightCount;

		if (version >= 56)
		{
			BspLump = (const DiskPrimaryLight *)Com_GetBspLump(LUMP_PRIMARY_LIGHTS, 248, &diskLightCount);
		}
		else
		{
			BspLump = (const DiskPrimaryLight_Version55 *)Com_GetBspLump(LUMP_PRIMARY_LIGHTS, 260, &diskLightCount);
		}

		unsigned int diskLightCount{};
		if (diskLightCount <= 1)
		{
			Com_Error(ERR_DROP, "no primary lights in bsp\n");
		}

		ComPrimaryLight *primaryLights{};

		comWorld.primaryLightCount = diskLightCount;
		comWorld.primaryLights = primaryLights;

		if (comBspGlob.header->version >= 56)
		{
			for (unsigned int i = 0; i < diskLightCount; ++primaryLights)
			{
				Com_LoadPrimaryLight_DiskPrimaryLight_(primaryLights, BspLump++, i++);
			}
		}
		else
		{
			for (unsigned int j = 0; j < diskLightCount; ++primaryLights)
			{
				const DiskPrimaryLight_Version55 *in{};
				Com_LoadPrimaryLight_DiskPrimaryLight_Version55_(primaryLights, in++, j++);
			}
		}
	}
	else
	{
		Com_Error(ERR_DROP, "Old version of primary lights not supported, please recompile the BSP\n");
		comWorld.primaryLightCount = NULL;
	}
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
	if (IsFastFileLoad())
	{
		Com_LoadWorld_FastFile(name);
	}

	Com_LoadWorld_LoadObj(name);
}

