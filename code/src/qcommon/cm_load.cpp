#include "types.h"

/*
==============
TRACK_cm_load
==============
*/
void TRACK_cm_load()
{
	track_static_alloc_internal(&cm, 332, "cm", 29);
	track_static_alloc_internal(g_box_brush, 1248, "g_box_brush", 29);
	track_static_alloc_internal(g_box_model, 988, "g_box_model", 29);
	track_static_alloc_internal(g_geoms, 52, "g_geoms", 29);
}

/*
==============
Load_ClipInfoFixup
==============
*/
void Load_ClipInfoFixup(ClipInfo **pInfo, ClipInfo *info)
{
	*pInfo = info;
}

/*
==============
CM_InitThreadData
==============
*/
void CM_InitThreadData(int threadContext)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CM_InitAllThreadData
==============
*/
unsigned __int16 *CM_InitAllThreadData()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CM_LoadMapData_LoadObj
==============
*/
void CM_LoadMapData_LoadObj(const char *name)
{
	if (!cm.isInUse || I_stricmp(cm.name, name))
	{
		ProfLoad_Begin("Load bsp collision");

		CM_LoadMapFromBsp(name, 1);

		ProfLoad_End();
		ProfLoad_Begin("Load static model collision");

		CM_LoadStaticModels();

		ProfLoad_End();
		ProfLoad_Begin("Load dynamic entities");

		DynEnt_LoadEntities();

		ProfLoad_End();
	}
}

/*
==============
CM_LoadMapData_FastFile
==============
*/
void CM_LoadMapData_FastFile(const char *name)
{
	assert(clipMap == &cm);
	return DB_FindXAssetHeader(ASSET_TYPE_CLIPMAP_PVS, name, true, -1).clipMap != &cm;
}

/*
==============
CM_LoadMap
==============
*/
void CM_LoadMap(const char *name, int *checksum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CM_LoadAddonMapEnts_FastFile
==============
*/
void CM_LoadAddonMapEnts_FastFile(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CM_LoadAddonMapEnts
==============
*/
void CM_LoadAddonMapEnts(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CM_LoadAddOnMapEnts
==============
*/
void CM_LoadAddOnMapEnts(const char *name)
{
	if (!Com_IsAddonMap(name, 0))
	{
		g_addonMapEnts = FALSE;
	}

	CM_LoadAddonMapEnts(name);
}

/*
==============
Rope_InitRopes
==============
*/
void Rope_InitRopes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ShutdownRopes
==============
*/
void ShutdownRopes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CM_Shutdown
==============
*/
void CM_Shutdown()
{
	Com_Memset(&cm, 0, 332);
	cm.name = cm.name;//uh?
	assert(!cm.isInUse);
}

/*
==============
CM_Unload
==============
*/
void CM_Unload()
{
	assert(IsFastFileLoad());
	if (cm.isInUse)
	{
		Sys_Error("Cannot unload collision while it is in use");
	}
}

/*
==============
CM_ModelBounds
==============
*/
void CM_ModelBounds(unsigned int model, float *mins, float *maxs)
{
	cmodel_t *v3 = CM_ClipHandleToModel(model);
	*mins = v3->mins[0];
	mins[1] = v3->mins[1];
	mins[2] = v3->mins[2];

	*maxs = v3->maxs[0];
	maxs[1] = v3->maxs[1];
	maxs[2] = v3->maxs[2];
}

/*
==============
CM_ModelSurfaceFlags
==============
*/
int CM_ModelSurfaceFlags(unsigned int model)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CM_Hunk_Alloc
==============
*/
void *CM_Hunk_Alloc(int size, const char *name, int type)
{
	return Hunk_Alloc(size, name, type);
}

/*
==============
CM_Hunk_CheckTempMemoryHighClear
==============
*/
void CM_Hunk_CheckTempMemoryHighClear()
{
	Hunk_CheckTempMemoryHighClear();
}

/*
==============
CM_Hunk_AllocateTempMemoryHigh
==============
*/
void *CM_Hunk_AllocateTempMemoryHigh(int size, const char *name)
{
	return Hunk_AllocateTempMemoryHigh(size, name);
}

/*
==============
CM_Hunk_ClearTempMemoryHigh
==============
*/
void CM_Hunk_ClearTempMemoryHigh()
{
	Hunk_ClearTempMemoryHigh();
}

