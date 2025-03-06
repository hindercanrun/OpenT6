#include "types.h"

cmd_function_s Demo_PartyUpdateDemo_f_VAR;
cmd_function_s Demo_PartyPlayDemo_f_VAR;
cmd_function_s Demo_PartyStopDemo_f_VAR;
cmd_function_s Demo_FreeDemoMemory_f_VAR;

/*
==============
Demo_PartyPlayDemo_f
==============
*/
void Demo_PartyPlayDemo_f()
{
	if (!Com_GameMode_IsMode(GAMEMODE_THEATER) || !PartyClient_CountMembers(&g_lobbyData) == 1)
	{
		Com_PrintError(10, "Error, you're trying to use xpartyplayclient when you shouldn't.  This is only for theater lobby.\n");
	}

	PartyHost_StartDemo(&g_lobbyData, CONTROLLER_INDEX_FIRST);
}

/*
==============
Demo_PartyStopDemo_f
==============
*/
void Demo_PartyStopDemo_f()
{
	if (!Com_GameMode_IsMode(GAMEMODE_THEATER) || !PartyClient_CountMembers(&g_lobbyData) == 1)
	{
		Com_PrintError(10, "Error, you're trying to use xpartyplayclient when you shouldn't.  This is only for theater lobby.\n");
	}

	PartyHost_StopDemo(&g_lobbyData, CONTROLLER_INDEX_FIRST);
}

/*
==============
Demo_SetDemoLoadedTime
==============
*/
void Demo_SetDemoLoadedTime()
{
	demo.header.version = Sys_Milliseconds();
}

/*
==============
Demo_WasDemoJustLoaded
==============
*/
bool Demo_WasDemoJustLoaded()
{
	return (Sys_Milliseconds() - demo.header.version) <= 5000;
}

/*
==============
Demo_PartyFinishedLoadingDemo
==============
*/
void Demo_PartyFinishedLoadingDemo()
{
	arty_SendFinishedLoadingDemoMsg(&g_lobbyData);
}

/*
==============
Demo_InitFileShareTaskHandler
==============
*/
void Demo_InitFileShareTaskHandler()
{
	//*&s_demoFileShareTaskHandle.isAbortingFileshareTask = nullptr;
	s_demoFileShareTaskHandle.abortResetTime = 0;
}

/*
==============
Demo_ResetFileShareAbort
==============
*/
void Demo_ResetFileShareAbort()
{
	s_demoFileShareTaskHandle.isAbortingFileshareTask = 0;
	s_demoFileShareTaskHandle.abortResetTime = Sys_Milliseconds();
}

/*
==============
Demo_IsFileShareAbortInProcess
==============
*/
bool Demo_IsFileShareAbortInProcess()
{
	return s_demoFileShareTaskHandle.isAbortingFileshareTask || (Sys_Milliseconds() - s_demoFileShareTaskHandle.abortResetTime) <= 250;
}

/*
==============
Demo_GetFileShareTaskControllerIndex
==============
*/
ControllerIndex_t Demo_GetFileShareTaskControllerIndex()
{
	return s_demoFileShareTaskHandle.fileshareTaskControllerIndex;
}

/*
==============
Demo_HaveAllPlayersFinishedDownloading
==============
*/
char Demo_HaveAllPlayersFinishedDownloading(PartyData_s *party)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_AreAllPlayersReadyToLoadDemo
==============
*/
char Demo_AreAllPlayersReadyToLoadDemo(PartyData_s *party)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_IsStereo3D
==============
*/
bool Demo_IsStereo3D()
{
	return r_dualPlayEnable->current.enabled;
}

/*
==============
Demo_HaveAllPlayersFinishedLoadingDemo
==============
*/
char Demo_HaveAllPlayersFinishedLoadingDemo()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_IsHostControlsEnabled
==============
*/
bool Demo_IsHostControlsEnabled()
{
	return !Com_GameMode_IsMode(GAMEMODE_THEATER) || Party_IsGameLobbyHost() != 0;
}

/*
==============
Demo_IsClipAndScreenshotsEnabled
==============
*/
bool Demo_IsClipAndScreenshotsEnabled()
{
	return !Com_GameMode_IsMode(GAMEMODE_THEATER) || !Demo_IsCameraEditMode() && !Demo_IsShoutcastMode()
		&& Party_IsGameLobbyHost() && PartyClient_CountMembers(&g_lobbyData) == 1;
}

/*
==============
Demo_IsWatchingWithParty
==============
*/
bool Demo_IsWatchingWithParty()
{
	if (Com_GameMode_IsMode(GAMEMODE_THEATER))
	{
		return PartyClient_CountMembers(&g_lobbyData) > 1;
	}

	return Com_GameMode_IsMode(GAMEMODE_THEATER);
}

/*
==============
Demo_WriteHeartbeat
==============
*/
void Demo_WriteHeartbeat(LocalClientNum_t localClientNum, PartyData_s *party, msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_ReadHeartbeat
==============
*/
void Demo_ReadHeartbeat(LocalClientNum_t localClientNum, PartyData_s *party, msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_ToggleScoreboard
==============
*/
void Demo_ToggleScoreboard()
{
	if (Demo_IsPlaybackInited())
	{
    	demo.playback->displayPartyScoreboard = !demo.playback->displayPartyScoreboard;
	}
}

/*
==============
Demo_DisplayingPartyScoreboard
==============
*/
bool Demo_DisplayingPartyScoreboard()
{
	return Demo_IsPlaying() && Demo_IsPlaybackInited() && demo.playback->displayPartyScoreboard;
}

/*
==============
Demo_AbortFileShareDownload
==============
*/
void Demo_AbortFileShareDownload(ControllerIndex_t controllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_CanRenderClip
==============
*/
bool Demo_CanRenderClip()
{
	return !r_dualPlayEnable->current.enabled && fshEnableRender->current.enabled && PartyClient_CountMembers(&g_lobbyData) == 1;
}

/*
==============
Demo_PartyUpdateDemo_f
==============
*/
void Demo_PartyUpdateDemo_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_FreeDemoMemory_f
==============
*/
void Demo_FreeDemoMemory_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_RegisterPartyCommands
==============
*/
void Demo_RegisterPartyCommands()
{
	Cmd_AddCommandInternal("xpartyupdatedemo", Demo_PartyUpdateDemo_f, &Demo_PartyUpdateDemo_f_VAR);
	Cmd_AddCommandInternal("xpartyplaydemo", Demo_PartyPlayDemo_f, &Demo_PartyPlayDemo_f_VAR);
	Cmd_AddCommandInternal("xpartystopdemo", Demo_PartyStopDemo_f, &Demo_PartyStopDemo_f_VAR);
	Cmd_AddCommandInternal("freeDemoMemory", Demo_FreeDemoMemory_f, &Demo_FreeDemoMemory_f_VAR);
}

