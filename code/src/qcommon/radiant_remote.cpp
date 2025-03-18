#include "types.h"

/*
==============
GetPairValue
==============
*/
char *GetPairValue(const SpawnVar *spawnVar, const char *key)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
AddSavedCommand
==============
*/
void AddSavedCommand(const RadiantCommand *command)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_RegisterGUID
==============
*/
void G_RegisterGUID(int guid, GUIDType type, void *data)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_FindGUID
==============
*/
void G_FindGUID(int guid, GUIDType *type, void **data)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
RadiantRemoteInit
==============
*/
void RadiantRemoteInit()
{
	savedCommandCount = 0;
}

/*
==============
G_FindEntity
==============
*/
gentity_t *G_FindEntity(int guid)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
IsEntityType
==============
*/
bool IsEntityType(const SpawnVar *spawnVar)
{
	const char *classname = GetPairValue(spawnVar, "classname");

	return I_stricmp(classname, "worldspawn")
		&& I_stricmp(classname, "misc_prefab")
		&& I_stricmp(classname, "script_brushmodel")
		&& I_stricmp(classname, "rope")
		&& I_stricmp(classname, "spawn_manager")
		&& I_strncmp(classname, "dyn_", 4);
}

/*
==============
G_ClearSelectedEntity
==============
*/
void G_ClearSelectedEntity()
{
	g_radiant_selected_ent = false;
}

/*
==============
G_IsSpawnPoint
==============
*/
bool G_IsSpawnPoint(const char *classname)
{
	return I_stricmp("mp_dm_spawn", classname)
		|| I_strnicmp("mp_wager_spawn", classname, 14)
		|| I_strnicmp("mp_tdm_spawn", classname, 12)
		|| I_strnicmp("mp_ctf_spawn", classname, 12)
		|| I_strnicmp("mp_dom_spawn", classname, 12)
		|| I_strnicmp("mp_sab_spawn", classname, 12)
		|| I_strnicmp("mp_sd_spawn", classname, 11)
		|| I_strnicmp("mp_twar_spawn", classname, 13)
		|| I_stricmp("mp_uspawn_point", classname);
}

/*
==============
G_ProcessEntityCommand
==============
*/
void G_ProcessEntityCommand(const RadiantCommand *command, SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_ProcessCameraCommand
==============
*/
void G_ProcessCameraCommand(SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_FindMiscModel
==============
*/
int G_FindMiscModel(const vec3_t *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
G_ProcessMiscModelCommand
==============
*/
void G_ProcessMiscModelCommand(const RadiantCommand *command, SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_ClearSelectedMiscModel
==============
*/
void G_ClearSelectedMiscModel()
{
	g_selected_misc_model = nullptr;
}

/*
==============
G_FindCorona
==============
*/
int G_FindCorona(const vec3_t *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
G_ProcessCoronaCommand
==============
*/
void G_ProcessCoronaCommand(const RadiantCommand *command, SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_ClearSelectedCorona
==============
*/
void G_ClearSelectedCorona()
{
	g_selected_corona = nullptr;
}

/*
==============
G_NotifyScriptsOfSelectedScriptStruct
==============
*/
void G_NotifyScriptsOfSelectedScriptStruct(unsigned int structId)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_FindStruct
==============
*/
unsigned int G_FindStruct(SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
G_ProcessScriptStructCommand
==============
*/
void G_ProcessScriptStructCommand(const RadiantCommand *command, SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_ClearSelectedScriptStruct
==============
*/
void G_ClearSelectedScriptStruct()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_NotifyScriptsOfSelectedScriptStruct
==============
*/
void CG_NotifyScriptsOfSelectedScriptStruct(unsigned int structId)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_FindStruct
==============
*/
unsigned int CG_FindStruct(SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_ProcessScriptStructCommand
==============
*/
void CG_ProcessScriptStructCommand(const RadiantCommand *command, SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ClearSelectedScriptStruct
==============
*/
void CG_ClearSelectedScriptStruct()
{
	gSelectedScriptStruct = false;
	Scr_NotifyLevel(scr_const.obstacle);
}

/*
==============
G_RadiantDebugDraw
==============
*/
void G_RadiantDebugDraw()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_ClearSelection
==============
*/
void G_ClearSelection(void (*ignoreFunc)())
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ClearSelection
==============
*/
void CG_ClearSelection(void (*ignoreFunc)())
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ProcessRadiantCmds
==============
*/
char CG_ProcessRadiantCmds()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
GetCommandProcessorType
==============
*/
int GetCommandProcessorType(const SpawnVar *spawnVar)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
G_ProcessRadiantCmd
==============
*/
void G_ProcessRadiantCmd(const RadiantCommand *command)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_ProcessRadiantCmds
==============
*/
char G_ProcessRadiantCmds()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
RunSavedRadiantCmds
==============
*/
void RunSavedRadiantCmds()
{
	UNIMPLEMENTED(__FUNCTION__);
}

