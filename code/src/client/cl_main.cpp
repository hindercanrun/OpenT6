#include "types.h"
#include "vars.h"
#include "client_public.h"
#include <qcommon/qcommon_public.h>
#include <gfx_d3d/gfx_d3d_public.h>

cmd_function_s CL_ExecControllerBindings_f_VAR;
cmd_function_s CL_Live_ShowFriendsList_VAR;
cmd_function_s CL_Live_MutePlayer_VAR;
cmd_function_s CL_AnimateUI_f_VAR;
cmd_function_s CL_ResetSelectedPlayerXuid_f_VAR;
cmd_function_s CL_Setenv_f_VAR;
cmd_function_s CL_ForwardToServer_f_VAR;
cmd_function_s CL_Configstrings_f_VAR;
cmd_function_s CL_Clientinfo_f_VAR;
cmd_function_s CL_PlayLogo_f_VAR;
cmd_function_s CL_ShowIP_f_VAR;
cmd_function_s CL_startMultiplayer_f_VAR;
cmd_function_s CL_startSingleplayer_f_VAR;
cmd_function_s CL_startZombies_f_VAR;
cmd_function_s CL_SelectStringTableEntryInDvar_f_VAR;
cmd_function_s CL_ResetStats_f_VAR;
cmd_function_s CL_Command_DisableAllButPrimaryClients_VAR;
cmd_function_s CL_Command_DisableAllClients_VAR;
cmd_function_s CL_Command_SetClientBeingUsedAndPrimary_VAR;
cmd_function_s CL_Command_SetClientBeingUsedAndPrimaryAndActive_VAR;
cmd_function_s CL_Command_SetClientBeingUsed_VAR;
cmd_function_s CL_Command_SetClientBeingUsedAndActive_VAR;
cmd_function_s CL_Command_SetClientNotBeingUsed_VAR;
cmd_function_s CL_Command_SetClientPrimary_VAR;
cmd_function_s CL_Command_SignClientOutOfUI_VAR;
cmd_function_s CL_LoadGump_VAR;
cmd_function_s CL_FlushGump_VAR;
cmd_function_s CL_FlushGumps_VAR;
cmd_function_s CL_SetupViewport_f_VAR;
cmd_function_s CL_Live_StartPartyHost_VAR;
cmd_function_s CL_Live_StartParty_VAR;
cmd_function_s CL_Live_StartPrivateParty_VAR;
cmd_function_s CL_Live_StartLocalPrivateParty_VAR;
cmd_function_s CL_Live_StopParty_VAR;
cmd_function_s CL_Live_StopPartyKeepPartyTogether_VAR;
cmd_function_s CL_Live_StopPrivateParty_VAR;
cmd_function_s CL_Live_StopAllParties_VAR;
cmd_function_s CL_Live_PartySwitchLobbies_VAR;
cmd_function_s CL_Live_PartyPlay_VAR;
cmd_function_s CL_Live_PartyMapVeto_VAR;
cmd_function_s CL_Live_UpdatePartyMapPacks_VAR;
cmd_function_s CL_Live_UpdatePartyState_VAR;
cmd_function_s CL_Live_SessionUpdate_VAR;
cmd_function_s CL_Live_PartyMapReady_VAR;
cmd_function_s CL_Live_SessionUpdatePrivacy_VAR;
cmd_function_s CL_UpdateLevelHunkUsage_VAR;
cmd_function_s CL_CubemapShot_f_VAR;
cmd_function_s CL_Live_ShowGamerCard_VAR;
cmd_function_s CL_Live_DisbandPartyAfterRound_VAR;
cmd_function_s CL_VoiceFail_f_VAR;
cmd_function_s CL_ForceVoiceFail_f_VAR;
cmd_function_s CL_Command_SignClientIn_VAR;
cmd_function_s CL_ChooseNextPlaylist_VAR;
cmd_function_s CL_ChoosePreviousPlaylist_VAR;
cmd_function_s CL_Connect_f_VAR;
cmd_function_s CL_Connect_f_VAR_SERVER;
cmd_function_s CL_Disconnect_f_VAR;
cmd_function_s CL_Disconnect_f_VAR_SERVER;
cmd_function_s CL_Reconnect_f_VAR;
cmd_function_s CL_Reconnect_f_VAR_SERVER;
cmd_function_s CL_Vid_Restart_f_VAR;
cmd_function_s CL_Vid_Restart_f_VAR_SERVER;
cmd_function_s CL_CheckInvite_f_VAR;
cmd_function_s CL_CheckInvite_f_VAR_SERVER;
cmd_function_s CL_SkipLevel_f_VAR;
cmd_function_s CL_SkipLevel_f_VAR_SERVER;
cmd_function_s CL_Snd_Restart_f_VAR;
cmd_function_s CL_Snd_Restart_f_VAR_SERVER;
cmd_function_s dwInstantSendTestMessage_VAR;
cmd_function_s UI_KeyClearStates_f_VAR;

/*
==============
CL_AnyLocalClientsRunning
==============
*/
char CL_AnyLocalClientsRunning()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_Command_DisableAllButPrimaryClients
==============
*/
void CL_Command_DisableAllButPrimaryClients()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SetClientBeingUsedAndPrimary
==============
*/
void CL_Command_SetClientBeingUsedAndPrimary()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SetClientBeingUsedAndPrimaryAndActive
==============
*/
void CL_Command_SetClientBeingUsedAndPrimaryAndActive()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SetClientPrimary
==============
*/
void CL_Command_SetClientPrimary()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SetClientBeingUsed
==============
*/
void CL_Command_SetClientBeingUsed()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SetClientBeingUsedAndActive
==============
*/
void CL_Command_SetClientBeingUsedAndActive()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_DisableAllClients
==============
*/
void CL_Command_DisableAllClients()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SignClientOutOfUI
==============
*/
void CL_Command_SignClientOutOfUI()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Command_SignClientIn
==============
*/
void CL_Command_SignClientIn()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetupClientsForIngame
==============
*/
void CL_SetupClientsForIngame()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawFramedPicPhysical
==============
*/
void CL_DrawFramedPicPhysical(float x, float y, float w, float h, float thicknessW, float thicknessH, float thicknessTex, int sides, const vec4_t *color, Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ForwardToServer_f
==============
*/
void CL_ForwardToServer_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Setenv_f
==============
*/
void CL_Setenv_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SkipLevel_f
==============
*/
void CL_SkipLevel_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Vid_Restart_f
==============
*/
void CL_Vid_Restart_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Snd_Restart_f
==============
*/
void CL_Snd_Restart_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_OpenedIWDList_f
==============
*/
void CL_OpenedIWDList_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ReferencedIWDList_f
==============
*/
void CL_ReferencedIWDList_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Configstrings_f
==============
*/
void CL_Configstrings_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Clientinfo_f
==============
*/
void CL_Clientinfo_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_WasMapAlreadyLoaded
==============
*/
bool CL_WasMapAlreadyLoaded()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_Live_StopAllParties
==============
*/
void CL_Live_StopAllParties()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_StopPrivateParty
==============
*/
void CL_Live_StopPrivateParty()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_LeaveParty
==============
*/
void CL_Live_LeaveParty(PartyData_s *party, ControllerIndex_t localControllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_LeaveAllParties
==============
*/
void CL_Live_LeaveAllParties(ControllerIndex_t localControllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_LocalClientJoinParty
==============
*/
char CL_Live_LocalClientJoinParty(PartyData_s *party, ControllerIndex_t localControllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_Live_StopParty
==============
*/
void CL_Live_StopParty(bool keepPartyTogether)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_PartySwitchLobbies
==============
*/
void CL_Live_PartySwitchLobbies()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ExecControllerBindings_f
==============
*/
void CL_ExecControllerBindings_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_ShowFriendsList
==============
*/
void CL_Live_ShowFriendsList()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_StartPartyHost
==============
*/
void CL_Live_StartPartyHost(ControllerIndex_t localControllerIndex, bool silentFail)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_StartPartyHost
==============
*/
void CL_Live_StartPartyHost()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_PartyMapVeto
==============
*/
void CL_Live_PartyMapVeto()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_UpdatePartyState
==============
*/
void CL_Live_UpdatePartyState()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_PartyMapReady
==============
*/
void CL_Live_PartyMapReady()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_UpdateSession
==============
*/
void CL_UpdateSession(PartyData_s *party, SessionData *session, int maxplayers)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_GetUserMaxPlayerSetting
==============
*/
int CL_GetUserMaxPlayerSetting(ControllerIndex_t controllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_Live_SessionUpdate
==============
*/
void CL_Live_SessionUpdate()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_AnimateUI_f
==============
*/
void CL_AnimateUI_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ResetSelectedPlayerXuid_f
==============
*/
void __cdecl CL_ResetSelectedPlayerXuid_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawSpinnerPhysical
==============
*/
void CL_DrawSpinnerPhysical(float x, float y, float w, float h, const vec4_t *color)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawSpinner
==============
*/
void CL_DrawSpinner(const ScreenPlacement *scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, const vec4_t *color)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawSpinnerLoadbarPhysical
==============
*/
void CL_DrawSpinnerLoadbarPhysical(float x, float y, float w, float h, const vec4_t *color, float percentDone)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawSpinnerLoadbar
==============
*/
void CL_DrawSpinnerLoadbar(const ScreenPlacement *scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, const vec4_t *color, float percentDone)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ShutdownHunkUsers
==============
*/
void CL_ShutdownHunkUsers()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SendBlackboxSession
==============
*/
void CL_SendBlackboxSession(ControllerIndex_t controllerIndex, bool isserver, const char *mapname, const char *gametype)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ResetSkeletonCache
==============
*/
void CL_ResetSkeletonCache(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_HighestPriorityStatPacket
==============
*/
int CL_HighestPriorityStatPacket(clientConnection_t *clc, int numCompressedStatsPackets)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_CheckForResend
==============
*/
void CL_CheckForResend(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DisconnectError
==============
*/
void CL_DisconnectError(const char *message)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DisconnectPacket
==============
*/
void CL_DisconnectPacket(LocalClientNum_t localClientNum, netadr_t from, const char *reason)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_HandleRelayPacket
==============
*/
void CL_HandleRelayPacket(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_HandleVoiceTypePacket
==============
*/
char CL_HandleVoiceTypePacket(LocalClientNum_t localClientNum, msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_SetupForNewServerMap
==============
*/
void CL_SetupForNewServerMap(LocalClientNum_t localClientNum, const char *pszMapName, const char *pszGametype)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_AuthRequestPacket
==============
*/
void CL_AuthRequestPacket(LocalClientNum_t localClientNum, unsigned __int64 serverSteamID)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DispatchConnectionlessPacket
==============
*/
bool CL_DispatchConnectionlessPacket(LocalClientNum_t localClientNum, netadr_t from, msg_t *msg, int time)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_ConnectionlessPacket
==============
*/
bool CL_ConnectionlessPacket(int a1, LocalClientNum_t localClientNum, netadr_t from, msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_PacketEvent
==============
*/
bool CL_PacketEvent(LocalClientNum_t localClientNum, netadr_t from, msg_t *msg, int time, bool connectionlesss_packets_only)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_LocalClientIsInGame
==============
*/
BOOL CL_LocalClientIsInGame(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_IsClientLocal
==============
*/
char CL_IsClientLocal(ClientNum_t clientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_ParseBadPacket_f
==============
*/
void CL_ParseBadPacket_f()
{
	char *file;
	int file_size = FS_ReadFile("badpacket.dat", &file);
	if (file_size >= 0)
	{
		msg_t msg = { 0 };
		memset(&msg, NULL, sizeof(msg));

		msg.cursize = file_size;
		msg.data = file;

		MSG_ReadLong(&msg);
		MSG_ReadLong(&msg);

		assertMsg(true, "Time to debug this packet, baby!");

		CL_ParseServerMessage(LOCAL_CLIENT_0, &msg);
		FS_FreeFile(file);
	}
}

/*
==============
CL_SetupViewport
==============
*/
void CL_SetupViewport()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetupViewport_f
==============
*/
void __cdecl CL_SetupViewport_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_InitRenderer
==============
*/
void CL_InitRenderer()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DevGuiDvar_f
==============
*/
void CL_DevGuiDvar_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DevGuiDvarList_f
==============
*/
void CL_DevGuiDvarList_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DevGuiCmd_f
==============
*/
void CL_DevGuiCmd_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DevGuiOpen_f
==============
*/
void CL_DevGuiOpen_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_InitDevGui
==============
*/
void CL_InitDevGui()
{
	DevGui_Init();

	Cmd_AddCommandInternal("devgui_dvar", CL_DevGuiDvar_f, &CL_DevGuiDvar_f_VAR);
	Cmd_AddCommandInternal("devgui_list", CL_DevGuiDvarList_f, &CL_DevGuiDvarList_f_VAR);
	Cmd_AddCommandInternal("devgui_cmd", CL_DevGuiCmd_f, &CL_DevGuiCmd_f_VAR);
	Cmd_AddCommandInternal("devgui_open", CL_DevGuiOpen_f, &CL_DevGuiOpen_f_VAR);

	CL_CreateDevGui();
}

/*
==============
CL_StartHunkUsers
==============
*/
void CL_StartHunkUsers()
{
	assert(!cls.hunkUsersStarted);

	if (!CL_AnyLocalClientsRunning())
	{
		return;
	}

	assert(cls.soundStarted);
	assert(cls.rendererStarted);

	if (!cls.uiStarted)
	{
		CL_InitUI();
		assert(cls.uiStarted);

		if (!cls.devGuiStarted)
		{
			cls.devGuiStarted = true;
			CL_InitDevGui();
		}

		Com_DvarDump(8, false);

		cls.hunkUsersStarted = true;
	}
}

/*
==============
CL_ScaledMilliseconds
==============
*/
int CL_ScaledMilliseconds()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_InitDedicated
==============
*/
void CL_InitDedicated()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_startSingleplayer_f
==============
*/
void CL_startSingleplayer_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_startZombies_f
==============
*/
void CL_startZombies_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_startMultiplayer_f
==============
*/
void CL_startMultiplayer_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_PlayLogo_f
==============
*/
void CL_PlayLogo_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_OpenScriptMenu_f
==============
*/
void CL_OpenScriptMenu_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Playlist_ReadFromDisk
==============
*/
char Playlist_ReadFromDisk()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Playlist_CmdReadFromDisk
==============
*/
char __cdecl Playlist_CmdReadFromDisk()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_VoiceFail_f
==============
*/
void CL_VoiceFail_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ForceVoiceFail_f
==============
*/
void CL_ForceVoiceFail_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_MigrateHost_f
==============
*/
void CL_MigrateHost_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetNatStrict_f
==============
*/
void CL_SetNatStrict_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetNatOpen_f
==============
*/
void CL_SetNatOpen_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_LoadFFOTD_f
==============
*/
void CL_LoadFFOTD_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ChooseNextPlaylist
==============
*/
void CL_ChooseNextPlaylist()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ChoosePreviousPlaylist
==============
*/
void CL_ChoosePreviousPlaylist()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_LocalServers_f
==============
*/
void CL_LocalServers_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_FlushGump
==============
*/
void CL_FlushGump(int slot)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_FlushGumps
==============
*/
void __cdecl CL_FlushGumps()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_LoadGump
==============
*/
void CL_LoadGump()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_AddListenIn_f
==============
*/
void CL_AddListenIn_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_RemoveListenIn_f
==============
*/
void CL_RemoveListenIn_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ResetListenIn_f
==============
*/
void CL_ResetListenIn_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetListenIn_f
==============
*/
void CL_SetListenIn_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_RemoveCommands
==============
*/
void CL_RemoveCommands()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_RegisterDvars
==============
*/
void CL_RegisterDvars()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_IsServerLoadingMap
==============
*/
bool CL_IsServerLoadingMap()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_IsWaitingOnServerToLoadMap
==============
*/
bool CL_IsWaitingOnServerToLoadMap(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_SetWaitingOnServerToLoadMap
==============
*/
void CL_SetWaitingOnServerToLoadMap(LocalClientNum_t localClientNum, bool waiting)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextPhysical
==============
*/
void CL_DrawTextPhysical(const char *text, int maxChars, Font_s *font, float x, float y, float w, float xScale, float yScale, const vec4_t *color, int style, float padding)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextPhysicalWithEffects
==============
*/
void CL_DrawTextPhysicalWithEffects(const char *text, int maxChars, Font_s *font, float x, float y, float w, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawText
==============
*/
void CL_DrawText(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextRotate
==============
*/
void CL_DrawTextRotate(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextPhysicalWithCursor
==============
*/
void CL_DrawTextPhysicalWithCursor(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, int cursorPos, char cursor)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextWithCursor
==============
*/
void CL_DrawTextWithCursor(
	const ScreenPlacement *scrPlace,
	const char *text,
	int maxChars,
	Font_s *font,
	float x,
	float y,
	int horzAlign,
	int vertAlign,
	float xScale,
	float yScale,
	const float *color,
	int style,
	int cursorPos,
	char cursor)
{
	ScrPlace_ApplyRect(scrPlace, &x, &y, &xScale, &yScale, horzAlign, vertAlign);
	R_AddCmdDrawTextWithCursorInternal(
		text,
		maxChars,
		font,
		x,
		y,
		1.0f,
		xScale,
		yScale,
		0.0f,
		color,
		style,
		cursorPos,
		cursor,
		0.0f);
}

/*
==============
CL_DrawTextWithEffects
==============
*/
void CL_DrawTextWithEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextWithCOD7TypeWriterEffects
==============
*/
void CL_DrawTextWithCOD7TypeWriterEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextPhysicalWithCOD7TypeWriterEffects
==============
*/
void CL_DrawTextPhysicalWithCOD7TypeWriterEffects(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextWithRedactEffects
==============
*/
void CL_DrawTextWithRedactEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration, int fxRedactDecayStartTime, int fxRedactDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextPhysicalWithCOD7DecodeEffects
==============
*/
void CL_DrawTextPhysicalWithCOD7DecodeEffects(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextPhysicalWithRedactEffects
==============
*/
void CL_DrawTextPhysicalWithRedactEffects(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration, int fxRedactDecayStartTime, int fxRedactDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawTextWithPopInEffects
==============
*/
void CL_DrawTextWithPopInEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ShouldDisplayHud
==============
*/
char CL_ShouldDisplayHud(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_IsUIActive
==============
*/
BOOL CL_IsUIActive(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_RegisterFont
==============
*/
Font_s *CL_RegisterFont(const char *fontName, int imageTrack)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CL_GetMapCenter
==============
*/
vec3_t *CL_GetMapCenter()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CL_ConnectFromParty
==============
*/
void CL_ConnectFromParty(
	ControllerIndex_t controllerIndex,
	XSESSION_INFO *hostInfo,
	netadr_t addr,
	int numPublicSlots,
	int numPrivateSlots,
	const char *mapname)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SanitizeClanName
==============
*/
void CL_SanitizeClanName(ControllerIndex_t controllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_UploadStatsForController
==============
*/
void CL_UploadStatsForController(const ControllerIndex_t localControllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ClearState
==============
*/
void CL_ClearState(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_MapLoading_SetupDevmapParty
==============
*/
void CL_MapLoading_SetupDevmapParty()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_StopParty
==============
*/
void CL_Live_StopParty()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_Live_StopPartyKeepPartyTogether
==============
*/
void CL_Live_StopPartyKeepPartyTogether()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ShutdownAll
==============
*/
void CL_ShutdownRenderer(int destroyWindow)
{
	cls.rendererStarted = false;

	Com_ShutdownWorld();
	if (IsFastFileLoad() && destroyWindow)
	{
		CM_Shutdown();
	}

	R_Shutdown(destroyWindow);

	cls.whiteMaterial = nullptr;
	cls.consoleMaterial = nullptr;
	cls.consoleFont = nullptr;
	cls.spinnerMaterial = nullptr;
}

/*
==============
CL_ShutdownAll
==============
*/
void CL_ShutdownAll()
{
	if (cls.rendererStarted)
	{
		CL_ShutdownRenderer(false);
	}
}

/*
==============
CL_MapLoading
==============
*/
void CL_MapLoading(const char *mapname)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DownloadsComplete
==============
*/
void CL_DownloadsComplete(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_InitLoad
==============
*/
void CL_InitLoad(const char *mapname, const char *gametype)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ShutdownRef
==============
*/
void CL_ShutdownRef()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DrawLogo
==============
*/
void CL_DrawLogo(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ShowIP_f
==============
*/
void CL_ShowIP_f(bdCommonAddr *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_RegisterCommands
==============
*/
void CL_RegisterCommands()
{
	CL_Project_RegisterCommands();
	CL_Platform_RegisterCommands();
	CG_RegisterDvars();

	Cmd_AddCommandInternal("execcontrollerbindings", CL_ExecControllerBindings_f, &CL_ExecControllerBindings_f_VAR);
	Cmd_AddCommandInternal("xshowfriendslist", CL_Live_ShowFriendsList, &CL_Live_ShowFriendsList_VAR);
	Cmd_AddCommandInternal("xmuteplayer", nullptr, &CL_Live_MutePlayer_VAR);
	Cmd_AddCommandInternal("ui_animate", CL_AnimateUI_f, &CL_AnimateUI_f_VAR);
	Cmd_AddCommandInternal("ui_resetSelectedPlayerXuid", CL_ResetSelectedPlayerXuid_f, &CL_ResetSelectedPlayerXuid_f_VAR);
	Cmd_AddCommandInternal("setenv", CL_Setenv_f, &CL_Setenv_f_VAR);
	Cmd_AddCommandInternal("cmd", CL_ForwardToServer_f, &CL_ForwardToServer_f_VAR);
	Cmd_AddCommandInternal("configstrings", CL_Configstrings_f, &CL_Configstrings_f_VAR);
	Cmd_AddCommandInternal("clientinfo", CL_Clientinfo_f, &CL_Clientinfo_f_VAR);
	Cmd_AddCommandInternal("logo", CL_PlayLogo_f, &CL_PlayLogo_f_VAR);
	Cmd_AddCommandInternal("showip", nullptr, &CL_ShowIP_f_VAR);
	Cmd_AddCommandInternal("startMultiplayer", CL_startMultiplayer_f, &CL_startMultiplayer_f_VAR);
	Cmd_AddCommandInternal("startSingleplayer", CL_startSingleplayer_f, &CL_startSingleplayer_f_VAR);
	Cmd_AddCommandInternal("startZombies", CL_startZombies_f, &CL_startZombies_f_VAR);
	Cmd_AddCommandInternal(
		"selectStringTableEntryInDvar",
		CL_SelectStringTableEntryInDvar_f,
		&CL_SelectStringTableEntryInDvar_f_VAR);
	Cmd_AddCommandInternal("resetStats", CL_ResetStats_f, &CL_ResetStats_f_VAR);
	Cmd_AddCommandInternal(
		"disableallbutprimaryclients",
		CL_Command_DisableAllButPrimaryClients,
		&CL_Command_DisableAllButPrimaryClients_VAR);
	Cmd_AddCommandInternal("disableallclients", CL_Command_DisableAllClients, &CL_Command_DisableAllClients_VAR);
	Cmd_AddCommandInternal(
		"setclientbeingusedandprimary",
		CL_Command_SetClientBeingUsedAndPrimary,
		&CL_Command_SetClientBeingUsedAndPrimary_VAR);
	Cmd_AddCommandInternal(
		"setclientbeingusedandprimaryandactive",
		CL_Command_SetClientBeingUsedAndPrimaryAndActive,
		&CL_Command_SetClientBeingUsedAndPrimaryAndActive_VAR);
	Cmd_AddCommandInternal("setclientbeingused", CL_Command_SetClientBeingUsed, &CL_Command_SetClientBeingUsed_VAR);
	Cmd_AddCommandInternal(
		"setclientbeingusedandactive",
		CL_Command_SetClientBeingUsedAndActive,
		&CL_Command_SetClientBeingUsedAndActive_VAR);
	Cmd_AddCommandInternal("setclientnotbeingused", CL_Command_DisableAllClients, &CL_Command_SetClientNotBeingUsed_VAR);
	Cmd_AddCommandInternal("setclientprimary", CL_Command_SetClientPrimary, &CL_Command_SetClientPrimary_VAR);
	Cmd_AddCommandInternal("signclientout", CL_Command_SignClientOutOfUI, &CL_Command_SignClientOutOfUI_VAR);
	Cmd_AddCommandInternal("LoadGump", CL_LoadGump, &CL_LoadGump_VAR);
	Cmd_AddCommandInternal("FlushGump", CL_FlushGump, &CL_FlushGump_VAR);
	Cmd_AddCommandInternal("FlushGumps", CL_FlushGump, &CL_FlushGumps_VAR);
	Cmd_AddCommandInternal("setupviewport", CL_SetupViewport_f, &CL_SetupViewport_f_VAR);
	Cmd_AddCommandInternal("xstartpartyhost", CL_Live_StartPartyHost, &CL_Live_StartPartyHost_VAR);
	Cmd_AddCommandInternal("xstartparty", CL_Live_StartParty, &CL_Live_StartParty_VAR);
	Cmd_AddCommandInternal("xstartprivateparty", CL_Live_StartPrivateParty, &CL_Live_StartPrivateParty_VAR);
	Cmd_AddCommandInternal("xstartlocalprivateparty", CL_Live_StartLocalPrivateParty, &CL_Live_StartLocalPrivateParty_VAR);
	Cmd_AddCommandInternal("xstopparty", CL_Live_StopParty, &CL_Live_StopParty_VAR);
	Cmd_AddCommandInternal(
		"xstoppartykeeptogether",
		CL_Live_StopPartyKeepPartyTogether,
		&CL_Live_StopPartyKeepPartyTogether_VAR);
	Cmd_AddCommandInternal("xstopprivateparty", CL_Live_StopPrivateParty, &CL_Live_StopPrivateParty_VAR);
	Cmd_AddCommandInternal("xstopallparties", CL_Live_StopAllParties, &CL_Live_StopAllParties_VAR);
	Cmd_AddCommandInternal("xpartyswitchlobbies", CL_Live_PartySwitchLobbies, &CL_Live_PartySwitchLobbies_VAR);
	Cmd_AddCommandInternal("xpartygo", CL_Live_PartyPlay, &CL_Live_PartyPlay_VAR);
	Cmd_AddCommandInternal("xpartyveto", CL_Live_PartyMapVeto, &CL_Live_PartyMapVeto_VAR);
	Cmd_AddCommandInternal("xupdatepartymappacks", CL_Live_UpdatePartyMapPacks, &CL_Live_UpdatePartyMapPacks_VAR);
	Cmd_AddCommandInternal("xupdatepartystate", CL_Live_UpdatePartyState, &CL_Live_UpdatePartyState_VAR);
	Cmd_AddCommandInternal("xsessionupdate", CL_Live_SessionUpdate, &CL_Live_SessionUpdate_VAR);
	Cmd_AddCommandInternal("xpartyready", CL_Live_PartyMapReady, &CL_Live_PartyMapReady_VAR);
	Cmd_AddCommandInternal("xsessionupdateprivacy", CL_Live_SessionUpdatePrivacy, &CL_Live_SessionUpdatePrivacy_VAR);
	Cmd_AddCommandInternal("updatehunkusage", CL_UpdateLevelHunkUsage, &CL_UpdateLevelHunkUsage_VAR);
	Cmd_AddCommandInternal("cubemapShot", CL_CubemapShot_f, &CL_CubemapShot_f_VAR);
	Cmd_AddCommandInternal("xshowgamercard", CL_Live_ShowGamerCard, &CL_Live_ShowGamerCard_VAR);
	Cmd_AddCommandInternal("xpartydisbandafterround", CL_Live_DisbandPartyAfterRound, &CL_Live_DisbandPartyAfterRound_VAR);
	Cmd_AddCommandInternal("voicefail", CL_VoiceFail_f, &CL_VoiceFail_f_VAR);
	Cmd_AddCommandInternal("forcevoicefail", CL_ForceVoiceFail_f, &CL_ForceVoiceFail_f_VAR);
	Cmd_AddCommandInternal("signclientin", CL_Command_SignClientIn, &CL_Command_SignClientIn_VAR);
	Cmd_AddCommandInternal("xplaylistchoosegame", CL_ChooseNextPlaylist, &CL_ChooseNextPlaylist_VAR);
	Cmd_AddCommandInternal("xplaylistchoosepreviousgame", CL_ChoosePreviousPlaylist, &CL_ChoosePreviousPlaylist_VAR);
	Cmd_AddCommandInternal("connect", nullptr, &CL_Connect_f_VAR);
	Cmd_AddServerCommandInternal("connect", CL_Connect_f, &CL_Connect_f_VAR_SERVER);
	Cmd_AddCommandInternal("disconnect", nullptr, &CL_Disconnect_f_VAR);
	Cmd_AddServerCommandInternal("disconnect", &CL_Disconnect_f, &CL_Disconnect_f_VAR_SERVER);
	Cmd_AddCommandInternal("reconnect", nullptr, &CL_Reconnect_f_VAR);
	Cmd_AddServerCommandInternal("reconnect", CL_Reconnect_f, &CL_Reconnect_f_VAR_SERVER);
	Cmd_AddCommandInternal("vid_restart", nullptr, &CL_Vid_Restart_f_VAR);
	Cmd_AddServerCommandInternal("vid_restart", CL_Vid_Restart_f, &CL_Vid_Restart_f_VAR_SERVER);
	Cmd_AddCommandInternal("checkinvite", nullptr, &CL_CheckInvite_f_VAR);
	Cmd_AddServerCommandInternal("checkinvite", nullptr, &CL_CheckInvite_f_VAR_SERVER);
	Cmd_AddCommandInternal("skip_level", nullptr, &CL_SkipLevel_f_VAR);
	Cmd_AddServerCommandInternal("skip_level", CL_SkipLevel_f, &CL_SkipLevel_f_VAR_SERVER);
	Cmd_AddCommandInternal("snd_restart", nullptr, &CL_Snd_Restart_f_VAR);
	Cmd_AddServerCommandInternal("snd_restart", CL_Snd_Restart_f, &CL_Snd_Restart_f_VAR_SERVER);
	Cmd_AddCommandInternal("sendinstantmessage", dwInstantSendTestMessage, &dwInstantSendTestMessage_VAR);
	Cmd_AddCommandInternal("clearKeyStates", UI_KeyClearStates_f, &UI_KeyClearStates_f_VAR);
}

/*
==============
CL_InitOnceForAllClients
==============
*/
void CL_InitOnceForAllClients()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetupClientsForFrontend
==============
*/
void CL_SetupClientsForFrontend()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
TRACK_cl_main
==============
*/
void TRACK_cl_main()
{
	UNIMPLEMENTED(__FUNCTION__);
}

