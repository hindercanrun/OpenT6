#include "types.h"

/*
==============
R_GetMaterialUsageData
==============
*/
MaterialUsage *R_GetMaterialUsageData(const Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_CreateMaterialList
==============
*/
void R_CreateMaterialList()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ShutdownMaterialUsage
==============
*/
void R_ShutdownMaterialUsage()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CopyParseParamsFromDvars
==============
*/
void R_CopyParseParamsFromDvars(SunLightParseParams *sunParse)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_InterpretSunLightParseParams
==============
*/
void R_InterpretSunLightParseParams(SunLightParseParams *sunParse)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_UpdateLightsFromDvars
==============
*/
void R_UpdateLightsFromDvars()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CopyParseParamsToDvars
==============
*/
void R_CopyParseParamsToDvars(const SunLightParseParams *sunParse, int savegame)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SetWorldPtr_LoadObj
==============
*/
void R_SetWorldPtr_LoadObj(const char *name)
{
	assert(!rgp.world);
	rgp.world = R_LoadWorldInternal(name);
	assert(rgp.world);
}

/*
==============
R_SetWorldPtr_FastFile
==============
*/
void R_SetWorldPtr_FastFile(const char *name)
{
	rgp.world = DB_FindXAssetHeader(ASSET_TYPE_GFXWORLD, name, true, -1).gfxWorld;
	rgp.needSortMaterials = true;
}

/*
==============
R_LoadWorld
==============
*/
void R_LoadWorld(const char *name, int *checksum, int savegame)
{
	assert(!rgp.world);
	R_InitLightVisHistory(name);

	if (!useFastFile->current.enabled)
	{
		R_SetWorldPtr_LoadObj(name);
	}

	R_SetWorldPtr_FastFile(name);

	R_WorldLod_Init();
	R_FoliageInitModels(rgp.world);

	g_worldDpvsPlanes = &rgp.world->dpvsPlanes;
	g_worldDpvs = &rgp.world->dpvs;
	g_worldDraw = &rgp.world->draw;
	qmemcpy(&g_drawConsts, rgp.world->outdoorLookupMatrix, 64);

	if (checksum)
	{
	  *checksum = rgp.world->checksum;
	}

	R_CopyParseParamsToDvars(&rgp.world->sunParse, savegame);
	R_UpdateLightsFromDvars();
	R_FlushSun();
	R_ClearSkyboxModel();
	R_RegisterSkyboxModel();
	R_InitDynamicData();
	R_ResetModelLighting();

	RB_ResetCoronas();
	RB_SetBspImages();

	DynEntCl_InitFilter();
	R_GenerateShadowMapCasterCells();

	for (unsigned int reflectionProbeIndex = 0; reflectionProbeIndex < g_worldDraw->reflectionProbeCount; ++reflectionProbeIndex)
	{
		g_worldDraw->reflectionProbeTextures[reflectionProbeIndex].basemap = g_worldDraw->reflectionProbes[reflectionProbeIndex].reflectionImage->texture.basemap;
	}

	for (int lightmapIndex = 0; lightmapIndex < g_worldDraw->lightmapCount; ++lightmapIndex)
	{
		g_worldDraw->lightmapPrimaryTextures[lightmapIndex].basemap = g_worldDraw->lightmaps[lightmapIndex].primary->texture.basemap;
		g_worldDraw->lightmapSecondaryTextures[lightmapIndex].basemap = g_worldDraw->lightmaps[lightmapIndex].secondary->texture.basemap;
		g_worldDraw->lightmapSecondaryTexturesB[lightmapIndex].basemap = g_worldDraw->lightmaps[lightmapIndex].secondaryB->texture.basemap;
	}
}

/*
==============
R_GetDebugReflectionProbeLocs
==============
*/
signed int R_GetDebugReflectionProbeLocs(vec3_t *locArray, unsigned int maxCount)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

