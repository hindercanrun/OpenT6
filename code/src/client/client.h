// client.h -- primary header for client

//#include "../game/q_shared.h"

#pragma once

//#include <win32/win32_public.h>
#include "types.h"
#include "vars.h"

#define	RETRANSMIT_TIMEOUT	3000	// time between connection packet retransmits


// snapshots are a view of the server at a given time
typedef struct {
	int				valid;			// cleared if delta parsing was invalid
	int				snapFlags;		// rate delayed and dropped commands

	int				serverTime;		// server time the message is valid for (in msec)
	int				physicsTime;

	int				messageNum;		// copied from netchan->incoming_sequence
	int				deltaNum;		// messageNum the delta is from
	int				ping;			// time from when cmdNum-1 was sent to time packet was reeceived

	int				cmdNum;			// the next cmdNum the server is expecting
	playerState_t	ps;						// complete information about the current player at this time

	int				numEntities;			// all of the entities that need to be presented
	int				numClients;
	int				numActors;
	int				parseMatchStateIndex;
	int				parseEntitiesIndex;
	int				parseEntitiesNum;		// at the time of this snapshot
	int				parseActorsIndex;

	int				serverCommandNum;		// execute all commands up to this before
											// making the snapshot current
} clSnapshot_t;



/*
=============================================================================

the clientActive_t structure is wiped completely at every
new gamestate_t, potentially several times during an established connection

=============================================================================
*/

typedef struct {
	int		p_cmdNumber;		// cl.cmdNumber when packet was sent
	int		p_serverTime;		// usercmd->serverTime when packet was sent
	int		p_realtime;			// cls.realtime when packet was sent
} outPacket_t;

// the parseEntities array must be large enough to hold PACKET_BACKUP frames of
// entities, so that when a delta compressed message arives from the server
// it can be un-deltad from the original 
#define	MAX_PARSE_ENTITIES	2048

extern int g_console_field_width;
extern int g_console_char_height;

typedef struct {
	int			timeoutcount;		// it requres several frames in a timeout condition
									// to disconnect, preventing debugging breaks from
									// causing immediate disconnects on continue
	clSnapshot_t	snap;			// latest received from server

	bool		alwaysFalse;

	int			serverTime;			// may be paused during play
	int			oldServerTime;		// to prevent time from flowing bakcwards
	int			oldFrameServerTime;	// to check tournament restarts
	int			serverTimeDelta;	// cl.serverTime = cls.realtime + cl.serverTimeDelta
									// this value changes as net lag varies
	qboolean	extrapolatedSnapshot;	// set if any cgame frame has been forced to extrapolate
									// cleared when CL_AdjustTimeDelta looks at it
	qboolean	newSnapshots;		// set on parse of any valid packet

	gameState_t	gameState;			// configstrings
	char		mapname[MAX_QPATH];	// extracted from CS_SERVERINFO

	int			parseEntitiesNum;	// index (not anded off) into cl_parse_entities[]

	int			mouseDx[2], mouseDy[2];	// added to by mouse events
	int			mouseIndex;
	int			joystickAxis[MAX_JOYSTICK_AXIS];	// set by joystick events

	// cgame communicates a few values to the client system
	int			cgameUserCmdValue;	// current weapon to add to usercmd_t
	float		cgameSensitivity;

	// cmds[cmdNumber] is the predicted command, [cmdNumber-1] is the last
	// properly generated command
	usercmd_t	cmds[CMD_BACKUP];	// each mesage will send several old cmds
	int			cmdNumber;			// incremented each frame, because multiple
									// frames may need to be packed into a single packet

	outPacket_t	outPackets[PACKET_BACKUP];	// information about each packet we have sent out

	// the client maintains its own idea of view angles, which are
	// sent to the server each frame.  It is cleared to 0 upon entering each level.
	// the server sends a delta each frame which is added to the locally
	// tracked view angles to account for standing on rotating objects,
	// and teleport direction changes
	vec3_t		viewangles;

	int			serverId;			// included in each client message so the server
												// can tell if it is for a prior map_restart
	// big stuff at end of structure so most offsets are 15 bits or less
	clSnapshot_t	snapshots[PACKET_BACKUP];

	entityState_t	entityBaselines[MAX_GENTITIES];	// for delta compression when not in previous frame

	entityState_t	parseEntities[MAX_PARSE_ENTITIES];
} clientActive_t;

extern	clientActive_t		clients;

static clientConnection_t* clientConnections;
static voiceCommunication_t cl_voiceCommunication[MAX_LOCAL_CLIENTS];

/*
==============
CL_GetLocalClientConnectionState
==============
*/
inline connstate_t CL_GetLocalClientConnectionState(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	connstate_t tmp;
	return tmp;
}

/*
==============
CL_LocalClient_IsCGameInitialized
==============
*/
inline unsigned int CL_LocalClient_IsCGameInitialized(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_GetLocalClientMigrationState
==============
*/
inline XModelRigidCullInfoContext *CL_GetLocalClientMigrationState(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CL_GetLocalClientGlobals
==============
*/
inline clientActive_t *CL_GetLocalClientGlobals(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CL_GetLocalClientUIGlobals
==============
*/
inline clientUIActive_t *CL_GetLocalClientUIGlobals(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CL_GetLocalClientConnection
==============
*/
inline clientConnection_t *CL_GetLocalClientConnection(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CL_SetLocalClientMigrationState
==============
*/
inline void CL_SetLocalClientMigrationState(LocalClientNum_t client, clientMigState_t state)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_SetLocalClientConnectionState
==============
*/
inline void CL_SetLocalClientConnectionState(LocalClientNum_t client, connstate_t state)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_LocalClient_SetCUIFlag
==============
*/
inline void CL_LocalClient_SetCUIFlag(LocalClientNum_t localClientNum, int flag)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_LocalClient_ClearCUIFlag
==============
*/
inline void CL_LocalClient_ClearCUIFlag(LocalClientNum_t localClientNum, int flag)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_LocalClient_IsInvited
==============
*/
inline unsigned int CL_LocalClient_IsInvited(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_LocalClient_IsDisplayingKeyCatcherHud
==============
*/
inline unsigned int CL_LocalClient_IsDisplayingKeyCatcherHud(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

//=================================================

//
// cl_main
//

