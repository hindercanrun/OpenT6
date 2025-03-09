#include "types.h"

unsigned int s_connectionsHash;
unsigned int s_sessionsHash;

bool s_blackboxInitialized = nullptr;

struct bb_highwater_t
{
	const char *name;
	unsigned int current_value;
	unsigned int sent_value;
};

bb_highwater_t highwater[128];
int highwater_count = 0;

int s_throttledTypeCount = 0;
bool s_throttleByDefault = false;

/*
==============
BB_FindThrottledType
==============
*/
int BB_FindThrottledType(unsigned int hash, int *pos)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_CheckThrottle
==============
*/
char BB_CheckThrottle(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_SetThrottle
==============
*/
void BB_SetThrottle(const char *name, int throttle)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_Print
==============
*/
void BB_Print(ControllerIndex_t controllerIndex, const char *name, const char *fmt, ...)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
GScr_BBPrint
==============
*/
void GScr_BBPrint()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_WriteInstanceData
==============
*/
void BB_WriteInstanceData(ControllerIndex_t controllerIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_RegisterHighWaterMark
==============
*/
int BB_RegisterHighWaterMark(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_SetHighWaterMark
==============
*/
void BB_SetHighWaterMark(int idx, unsigned int value)
{
	if (idx >= 0 && idx < highwater_count && highwater[idx].current_value < value)
	{
		highwater[idx].current_value = value;
	}
}

/*
==============
BB_SetupMsg
==============
*/
void BB_SetupMsg()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_Enable_f
==============
*/
void BB_Enable_f()
{
	if (Cmd_Argc() >= 2)
	{
		if (I_stricmp(Cmd_Argv(1), "all"))
		{
			BB_SetThrottle(Cmd_Argv(1), 0);
		}
		else
		{
			s_throttledTypeCount = 0;
			s_throttleByDefault = 0;
		}
	}
}

/*
==============
BB_Disable_f
==============
*/
void BB_Disable_f()
{
	if (Cmd_Argc() >= 2)
	{
		if (I_stricmp(Cmd_Argv(1), "all"))
		{
			BB_SetThrottle(Cmd_Argv(1), -1);
		}
		else
		{
			s_throttledTypeCount = 0;
			s_throttleByDefault = true;
		}
	}
}

/*
==============
BB_Throttle_f
==============
*/
void BB_Throttle_f()
{
	if (Cmd_Argc() >= 3)
	{
		BB_SetThrottle(Cmd_Argv(1), atoi(Cmd_Argv(2)));
	}
}

/*
==============
BB_Start
==============
*/
void BB_Start()
{
	assert(s_blackboxInitialized == NULL);

	Sys_EnterCriticalSection(CRITSECT_BLACKBOX);

	BB_InitDefinitions();
	BB_InitStringCache();

	s_bbmac = NULL;

	Com_PrintWarning(CON_CHANNEL_SYSTEM, "Could not determine MAC address, using random default\n");

	//s_bbid = rand();
	//s_bbid = (4 * _time64(0)) ^ rand();

	s_blackboxInitialized = 1;
	BB_SetupMsg();

	Sys_LeaveCriticalSection(CRITSECT_BLACKBOX);
}

/*
==============
BB_Start_f
==============
*/
void BB_Start_f()
{
	if (!s_blackboxInitialized)
	{
		if (blackboxHighVolumeProbability->current.integer <= random())
		{
			Cmd_ExecuteSingleCommand(LOCAL_CLIENT_FIRST, CONTROLLER_INDEX_FIRST, "exec blackbox_low.cfg", false);
		}
		else
		{
			Cmd_ExecuteSingleCommand(LOCAL_CLIENT_FIRST, CONTROLLER_INDEX_FIRST, "exec blackbox.cfg", false);
		}

		BB_Start();
	}
}

/*
==============
BB_Send
==============
*/
void BB_Send(ControllerIndex_t controllerIndex, bool force, bool bandwidthLimited)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_Alert
==============
*/
void BB_Alert(const char *filename, int line, const char *type, const char *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_Notify
==============
*/
void BB_Notify(bool daily, const char *recipient, const char *msg, bool immediate)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_ResetHighWaterMarks
==============
*/
void BB_ResetHighWaterMarks()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_ResetHighWaterMark
==============
*/
void BB_ResetHighWaterMark(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_Send_f
==============
*/
void BB_Send_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_Init
==============
*/
void BB_Init()
{
	assert(s_blackboxInitialized == 0);

	Cmd_AddCommandInternal("bbstart", BB_Start_f, &BB_Start_f_VAR);
	Cmd_AddCommandInternal("bbsend", BB_Send_f, &BB_Send_f_VAR);
	Cmd_AddCommandInternal("bbenable", BB_Enable_f, &BB_Enable_f_VAR);
	Cmd_AddCommandInternal("bbdisable", BB_Disable_f, &BB_Disable_f_VAR);
	Cmd_AddCommandInternal("bbthrottle", BB_Throttle_f, &BB_Throttle_f_VAR);

	blackboxBandwidthLimited = _Dvar_RegisterBool(
									"blackboxBandwidthLimited",
									0,
									0x20000u,
									"When true, limits blackbox sending so that it only occurs when not in game");
	blackboxHighVolumeProbability = _Dvar_RegisterFloat(
										"blackboxHighVolumeProbability",
										0.0,
										0.0,
										1.0,
										0x20000u,
										"Probability of sending high volume blackbox data");

	s_connectionsHash = BB_HashString("connections", 11);
	s_sessionsHash = BB_HashString("sessions", 8);
}

