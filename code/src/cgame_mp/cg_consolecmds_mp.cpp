#include "types.h"

static cmd_function_s CG_Viewpos_f_VAR;
static cmd_function_s CG_NextWeapon_f_VAR;
static cmd_function_s CG_PrevWeapon_f_VAR;
static cmd_function_s CG_ShellShock_f_VAR;
static cmd_function_s CG_ShellShock_Load_f_VAR;
static cmd_function_s CG_ShellShock_Save_f_VAR;
static cmd_function_s CG_QuickMessage_f_VAR;
static cmd_function_s CG_VoiceChat_f_VAR;
static cmd_function_s CG_TeamVoiceChat_f_VAR;
static cmd_function_s CG_ToggleScores_f_VAR;
static cmd_function_s CG_PlayRumble_f_VAR;
static cmd_function_s CG_FxSetTestPosition_VAR;
static cmd_function_s CG_FxTest_VAR;
static cmd_function_s CG_RestartSmokeGrenades_f_VAR;
static cmd_function_s UpdateFilmTweaks_f_VAR;
static cmd_function_s UpdateCharPrimaryTweaks_f_VAR;
static cmd_function_s UpdateBloomTweaks_f_VAR;
static cmd_function_s CG_PrintFXNameUsage_VAR;
static cmd_function_s CG_ToggleBandwidthProfiling_f_VAR;
static cmd_function_s Recorder_TogglePlayback_f_VAR;
static cmd_function_s Recorder_MemResize_f_VAR;
static cmd_function_s Recorder_GotoTime_f_VAR;

/*
==============
CG_Viewpos_f
==============
*/
void CG_Viewpos_f()
{
	if (cgArray->nextSnap)
	{
		Com_Printf(
			CON_CHANNEL_DONT_FILTER,
			"(%.0f %.0f %.0f) : %.0f %.0f\n",
			cgArray->refdef.vieworg.x,
			cgArray->refdef.vieworg.y,
			cgArray->refdef.vieworg.z,
			cgArray->refdefViewAngles.y,
			cgArray->refdefViewAngles.x);
	}
}

/*
==============
CG_CloseScoreboard
==============
*/
void CG_CloseScoreboard(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ScoresUp
==============
*/
void CG_ScoresUp(LocalClientNum_t localClientNum)
{
	if (CG_IsScoreboardDisplayed(localClientNum))
	{
		cg_s *LocalClientGlobals = CG_GetLocalClientGlobals(localClientNum);
		LocalClientGlobals->showScores = false;
		LocalClientGlobals->scoresTop = -1;
		LocalClientGlobals->scoreFadeTime = LocalClientGlobals->time;
	}
}

/*
==============
CG_ScoresDown
==============
*/
void CG_ScoresDown(LocalClientNum_t localClientNum)
{
	CG_GetLocalClientGlobals(localClientNum)->showScores = 1;
}

/*
==============
CG_ToggleScores
==============
*/
void CG_ToggleScores(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ShellShock_f
==============
*/
void CG_ShellShock_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ShellShock_Load_f
==============
*/
void CG_ShellShock_Load_f()
{
	if (cgArray->nextSnap)
	{
		if (Cmd_Argc() != 2)
		{
			Com_Printf(CON_CHANNEL_DONT_FILTER, "USAGE: cg_shellshock_load <name>\n");
		}

		BG_LoadShellShockDvars(Cmd_Argv(1));
	}
}

/*
==============
CG_ShellShock_Save_f
==============
*/
void CG_ShellShock_Save_f()
{
	if (cgArray->nextSnap)
	{
		if (Cmd_Argc() != 2)
		{
			Com_Printf(CON_CHANNEL_DONT_FILTER, "USAGE: cg_shellshock_save <name>\n");
		}

		BG_SaveShellShockDvars(Cmd_Argv(1));
	}
}

/*
==============
CG_QuickMessage_f
==============
*/
void CG_QuickMessage_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VoiceChat_f
==============
*/
void CG_VoiceChat_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_TeamVoiceChat_f
==============
*/
void CG_TeamVoiceChat_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_PlayRumble_f
==============
*/
void CG_PlayRumble_f()
{
	if (cgArray->nextSnap)
	{
		if (Cmd_Argc() != 2)
		{
			Com_Printf(CON_CHANNEL_DONT_FILTER, "USAGE: playrumble <rumblename>\n");
		}

		CG_PlayRumbleOnClient(LOCAL_CLIENT_FIRST, Cmd_Argv(1));
	}
}

/*
==============
CG_RestartSmokeGrenades_f
==============
*/
void CG_RestartSmokeGrenades_f()
{
	CG_RestartSmokeGrenades(LOCAL_CLIENT_FIRST);
}

/*
==============
UpdateFilmTweaks_f
==============
*/
void UpdateFilmTweaks_f()
{
	CG_VisionSetUpdateTweaksFromFile_Film();
}

/*
==============
UpdateCharPrimaryTweaks_f
==============
*/
void UpdateCharPrimaryTweaks_f()
{
	CG_VisionSetUpdateTweaksFromFile_CharPrimary();
}

/*
==============
UpdateBloomTweaks_f
==============
*/
void UpdateBloomTweaks_f()
{
	CG_VisionSetUpdateTweaksFromFile_Bloom();
}

/*
==============
CG_PrintEntities_f
==============
*/
void CG_PrintEntities_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_ToggleScores_f
==============
*/
void CG_ToggleScores_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_InitConsoleCommandsProject
==============
*/
void CG_InitConsoleCommandsProject()
{
	Cmd_AddCommandInternal("viewpos", CG_Viewpos_f, &CG_Viewpos_f_VAR);
	Cmd_AddCommandInternal("weapnext", CG_NextWeapon_f, &CG_NextWeapon_f_VAR);
	Cmd_AddCommandInternal("weapprev", CG_PrevWeapon_f, &CG_PrevWeapon_f_VAR);
	Cmd_AddCommandInternal("cg_shellshock", CG_ShellShock_f, &CG_ShellShock_f_VAR);
	Cmd_AddCommandInternal("cg_shellshock_load", CG_ShellShock_Load_f, &CG_ShellShock_Load_f_VAR);
	Cmd_AddCommandInternal("cg_shellshock_save", CG_ShellShock_Save_f, &CG_ShellShock_Save_f_VAR);
	Cmd_AddCommandInternal("mp_QuickMessage", CG_QuickMessage_f, &CG_QuickMessage_f_VAR);
	Cmd_AddCommandInternal("VoiceChat", CG_VoiceChat_f, &CG_VoiceChat_f_VAR);
	Cmd_AddCommandInternal("VoiceTeamChat", CG_TeamVoiceChat_f, &CG_TeamVoiceChat_f_VAR);
	Cmd_AddCommandInternal("cg_toggleScores", CG_ToggleScores_f, &CG_ToggleScores_f_VAR);
	Cmd_AddCommandInternal("playrumble", CG_PlayRumble_f, &CG_PlayRumble_f_VAR);
	Cmd_AddCommandInternal("fxSetTestPosition", CG_FxSetTestPosition, &CG_FxSetTestPosition_VAR);
	Cmd_AddCommandInternal("fxTest", CG_FxTest, &CG_FxTest_VAR);
	Cmd_AddCommandInternal("restartsmokegrenades", CG_RestartSmokeGrenades_f, &CG_RestartSmokeGrenades_f_VAR);
	Cmd_AddCommandInternal("updateFilmTweaks", UpdateFilmTweaks_f, &UpdateFilmTweaks_f_VAR);
	Cmd_AddCommandInternal("updateCharPrimaryTweaks", UpdateCharPrimaryTweaks_f, &UpdateCharPrimaryTweaks_f_VAR);
	Cmd_AddCommandInternal("updateBloomTweaks", UpdateBloomTweaks_f, &UpdateBloomTweaks_f_VAR);
	Cmd_AddCommandInternal("printfxnameusage", CG_PrintFXNameUsage, &CG_PrintFXNameUsage_VAR);
	Cmd_AddCommandInternal("togglebandwidthprofile", nullptr, &CG_ToggleBandwidthProfiling_f_VAR);
	Cmd_AddCommandInternal("recorder_togglePlayback", nullptr, &Recorder_TogglePlayback_f_VAR);
	Cmd_AddCommandInternal("recorder_memResize", nullptr, &Recorder_MemResize_f_VAR);
	Cmd_AddCommandInternal("recorder_gotoTime", nullptr, &Recorder_GotoTime_f_VAR);
}

/*
==============
CG_ShutdownConsoleCommandsProject
==============
*/
void CG_ShutdownConsoleCommandsProject()
{
	Cmd_RemoveCommand("viewpos");
	Cmd_RemoveCommand("weapnext");
	Cmd_RemoveCommand("weapprev");
	Cmd_RemoveCommand("cg_shellshock");
	Cmd_RemoveCommand("cg_shellshock_load");
	Cmd_RemoveCommand("cg_shellshock_save");
	Cmd_RemoveCommand("mp_QuickMessage");
	Cmd_RemoveCommand("VoiceChat");
	Cmd_RemoveCommand("VoiceTeamChat");
	Cmd_RemoveCommand("playrumble");
	Cmd_RemoveCommand("fxSetTestPosition");
	Cmd_RemoveCommand("fxTest");
	Cmd_RemoveCommand("restartsmokegrenades");
	Cmd_RemoveCommand("updateGlowTweaks");
	Cmd_RemoveCommand("updateFilmTweaks");
	Cmd_RemoveCommand("updateBloomTweaks");
}

