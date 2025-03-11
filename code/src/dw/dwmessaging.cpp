#include "types.h"

/*
==============
dwInstantHandleTestMessage
==============
*/
char dwInstantHandleTestMessage(unsigned __int64 senderID, const ControllerIndex_t controllerIndex, msg_t *msg)
{
	Com_Printf(CON_CHANNEL_LIVE, "got test message %i for controllerIndex %d from %llu\n", MSG_ReadLong(msg), controllerIndex, senderID);
	return TRUE;
}

/*
==============
dwInstantHandlePartyMessage
==============
*/
bool dwInstantHandlePartyMessage(unsigned __int64 senderID, const ControllerIndex_t controllerIndex, msg_t *msg)
{
	return Party_DispatchInstantMessage(senderID, controllerIndex, msg);
}

/*
==============
dwInstantHandleFriendMessage
==============
*/
bool dwInstantHandleFriendMessage(unsigned __int64 senderID, const ControllerIndex_t controllerIndex, msg_t *msg)
{
	return Live_ProcessFriendInstantMessage(senderID, controllerIndex, msg);
}

/*
==============
dwInstantDispatchMessage_Internal
==============
*/
bool dwInstantDispatchMessage_Internal(unsigned __int64 senderID, const ControllerIndex_t controllerIndex, void *message, unsigned int messageSize)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
dwLobbyEventHandler::onNewNotification
==============
*/
/*void dwLobbyEventHandler::onNewNotification(dwLobbyEventHandler *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwLobbyEventHandler::onTeamProposal
==============
*/
/*void dwLobbyEventHandler::onTeamProposal(dwLobbyEventHandler *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwLobbyEventHandler::onPlayerBanned
==============
*/
/*void dwLobbyEventHandler::onPlayerBanned(dwLobbyEventHandler *notthis, unsigned __int64 userID, unsigned int reputationLevel)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwLobbyEventHandler::onMultipleLogon
==============
*/
/*void dwLobbyEventHandler::onMultipleLogon(dwLobbyEventHandler *notthis, unsigned __int64 userID)
{
	Com_Error(ERR_FATAL, "PLATFORM_DW_MULTIPLE_LOGON");
}*/

/*
==============
dwLobbyEventHandler::onYouTubeRegistration
==============
*/
/*void dwLobbyEventHandler::onYouTubeRegistration(dwLobbyEventHandler *notthis, const bdYouTubeRegistrationResult *registrationResult)
{
	LiveYouTube_AuthReceived(notthis->m_controllerIndex, registrationResult->m_result);
}*/

/*
==============
dwLobbyEventHandler::onGlobalInstantMessage
==============
*/
/*void dwLobbyEventHandler::onGlobalInstantMessage(dwLobbyEventHandler *notthis, unsigned __int64 senderID, char *senderName, void *message, unsigned int messageSize)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwInitMessaging
==============
*/
void dwInitMessaging(ControllerIndex_t controllerIndex)
{
	assert(Sys_IsMainThread());
	assert(controllerIndex < CONTROLLER_INDEX_COUNT);

	bdLobbyService *lobby = dwGetLobby(controllerIndex);
	assert(lobby != 0);

	bdLobbyService::registerEventHandler(lobby, &s_eventHandler);
	Com_PrintWarning(CON_CHANNEL_SYSTEM, "Initialized Messaging for controller %d.\n", controllerIndex);
}

/*
==============
dwInstantSendMessage
==============
*/
TaskRecord *dwInstantSendMessage(ControllerIndex_t controllerIndex, const unsigned __int64 *recipientUIDs, unsigned int numRecipients, char msgType, const void *message, unsigned int msgSize)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
dwInstantSendTestMessage
==============
*/
void dwInstantSendTestMessage()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
dwProcessNotifications
==============
*/
char dwProcessNotifications(TaskRecord *task)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
dwLobbyEventHandler::onChallengesReceived
==============
*/
/*void dwLobbyEventHandler::onChallengesReceived(dwLobbyEventHandler *notthis, unsigned __int64 userID, bdReference<bdAntiCheatChallenges> challenges)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

