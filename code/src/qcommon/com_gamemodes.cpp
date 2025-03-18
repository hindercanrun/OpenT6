#include "types.h"

/*
==============
Com_GameMode_GetModeName
==============
*/
const char *Com_GameMode_GetModeName()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Com_GameMode_IsModeSet
==============
*/
BOOL Com_GameMode_IsModeSet()
{
	return sGameModeState != 0;
}

/*
==============
Com_GameMode_IsMode
==============
*/
bool Com_GameMode_IsMode(eGameModes mode)
{
	return ((1 << mode) & sGameModeState) != 0;
}

/*
==============
Com_GameMode_ResetModes
==============
*/
void Com_GameMode_ResetModes()
{
	if (bInBackupState)
	{
		Com_Error(ERR_FATAL, "Com_GameMode_ResetModes: Can not reset the modes when in backup lock!");
	}

	sGameModeState = 0;
}

/*
==============
Com_GameMode_IsUsingXP
==============
*/
int Com_GameMode_IsUsingXP()
{
	return sGameModeState & true;
}

/*
==============
Com_GameMode_IsUsingStats
==============
*/
BOOL Com_GameMode_IsUsingStats()
{
	return (sGameModeState & 0x41) != false;
}

/*
==============
Com_GameMode_WriteModes
==============
*/
void Com_GameMode_WriteModes(msg_t *msg)
{
	assert(sGameModeState >= 0 && sGameModeState < 0xFFFF);
	MSG_WriteShort(msg, sGameModeState);
}

/*
==============
Com_GameMode_ReadModes
==============
*/
bool Com_GameMode_ReadModes(msg_t *msg)
{
	assert(newState >= 0 && newState < 0xFFFF);
	return !MSG_ReadShort(msg);
}

/*
==============
ValidateGameModes
==============
*/
bool ValidateGameModes()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Com_GameMode_SetMode
==============
*/
void Com_GameMode_SetMode(eGameModes mode, bool value)
{
	if (bInBackupState)
	{
		Com_Error(ERR_FATAL, "Com_GameMode_SetMode: Can not set the mode when in backup block!");
	}

	ValidateGameModes();

	if (!value)
	{
		sGameModeState &= ~(1 << mode);
	}

	sGameModeState |= 1 << mode;
}

