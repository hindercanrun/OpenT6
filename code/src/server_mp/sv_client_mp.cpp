#include "types.h"

/*
==============
SV_CountClients
==============
*/
int SV_CountClients()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_GetChallenge
==============
*/
void SV_GetChallenge(netadr_t from)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_UpdateSplitscreenStateForAddr
==============
*/
void SV_UpdateSplitscreenStateForAddr(netadr_t addr)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_GetPlayerXuid
==============
*/
int SV_GetPlayerXuid(ClientNum_t clientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_FreeClientScriptPers
==============
*/
void SV_FreeClientScriptPers()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_SendDisconnect
==============
*/
void SV_SendDisconnect(client_t *client, int state, const char *reason)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_DelayDropClient
==============
*/
void SV_DelayDropClient(client_t *drop, const char *reason)
{
	assert(drop);
	assert(reason);
	assert(drop->header.state != CS_FREE);

	if (!drop->dropReason)
	{
		drop->dropReason = reason;
	}
	else
	{
		assertMsg(
			(drop->dropReason == 0),
			"\t(drop->dropReason) = %s",
			drop->dropReason);
	}
}

/*
==============
SV_ClientEnterWorld
==============
*/
void SV_ClientEnterWorld(client_t *client, usercmd_s *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_VerifyIwds_f
==============
*/
void SV_VerifyIwds_f(char *a1, client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_ResetPureClient_f
==============
*/
void SV_ResetPureClient_f(client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_SynchronizePlayerInfoForClients
==============
*/
void SV_SynchronizePlayerInfoForClients()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_ValidateName
==============
*/
char SV_ValidateName(client_t *newcl, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_SanitizeName
==============
*/
BOOL SV_SanitizeName(const char *name, char *sanitizedName, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SegmentIntersectsSphere
==============
*/
bool SegmentIntersectsSphere(const vec3_t *point1, const vec3_t *point2, const vec3_t *center, const float *radius)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_FX_GetVisibility
==============
*/
double SV_FX_GetVisibility(const vec3_t *start, const vec3_t *end)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_FX_SetVisBlocker
==============
*/
void SV_FX_SetVisBlocker(const gentity_t *ent, float radius)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_FX_FreeVisBlocker
==============
*/
void SV_FX_FreeVisBlocker(const gentity_t *ent)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_ExecuteClientCommand
==============
*/
void SV_ExecuteClientCommand(char *a1, client_t *cl, const char *s, int clientOK, int fromOldServer)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_ClientThink
==============
*/
void SV_ClientThink(client_t *cl, usercmd_s *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_IsTestClient
==============
*/
BOOL SV_IsTestClient(ClientNum_t clientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_FreeClient
==============
*/
void SV_FreeClient(client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_FreeClients
==============
*/
void SV_FreeClients()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_DropClient
==============
*/
void SV_DropClient(client_t *drop, const char *reason, bool tellThem)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_SendClientGameState
==============
*/
void SV_SendClientGameState(client_t *client)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_Disconnect_f
==============
*/
void SV_Disconnect_f(client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_UserinfoChanged
==============
*/
void SV_UserinfoChanged(client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_UpdateUserinfo_f
==============
*/
void SV_UpdateUserinfo_f(client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_ProcessClientCommands
==============
*/
int SV_ProcessClientCommands(client_t *cl, msg_t *msg, int fromOldServer, int *lastCommand)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SV_BanClient
==============
*/
void SV_BanClient(client_t *cl)
{
	assert(cl);

	if (cl->header.netchan.remoteAddress.type == NA_LOOPBACK)
	{
		SV_SendServerCommand(cl, 0, SV_CMD_CAN_IGNORE, "%c \"EXE_CANNOTKICKHOSTPLAYER\"", 79);
	}
	else if (cl->xuid)
	{
		if (Party_IsInTempBannedXuidList(cl->xuid))
		{
			Com_Printf(26, "This xuid (%llx) is already banned\n", cl->xuid);
		}
		else
		{
			Party_AddToTempBannedXuidList(cl->xuid);
			SV_DropClient(cl, "EXE_PLAYERKICKED_BAN", 1);

			cl->lastPacketTime = svs.time;
		}
	}
	else
	{
		Com_Printf(26, "Can't ban user, no xuid was found\n");
	}
}

/*
==============
ReconnectMigratedClient
==============
*/
void ReconnectMigratedClient(client_t *cl, netadr_t from, const int qport, const int challenge, int playerGuid, const char *userinfo)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_DirectConnect
==============
*/
void SV_DirectConnect(netadr_t from)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_MigrateTestClient
==============
*/
void SV_MigrateTestClient(client_t *cl)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_AddTestClient
==============
*/
gentity_t *SV_AddTestClient(unsigned int a1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SV_UserMove
==============
*/
void SV_UserMove(client_t *cl, msg_t *msg, int delta)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SV_ExecuteClientMessage
==============
*/
void SV_ExecuteClientMessage(client_t *cl, msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

