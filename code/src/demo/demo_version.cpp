#include "types.h"

/*
==============
Demo_GetVersion
==============
*/
int Demo_GetVersion()
{
	if (Demo_IsIdle())
	{
		Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
	}

	return demo.header.maxClients;
}

/*
==============
Demo_IsVersionAtLeast
==============
*/
bool Demo_IsVersionAtLeast(int version)
{
	if (!Demo_IsPlaying())
	{
		return 1;
	}

	if (Demo_IsIdle())
	{
		Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
	}

	return demo.header.maxClients >= version;
}

/*
==============
Demo_GetNetFieldListForType
==============
*/
const NetFieldList *Demo_GetNetFieldListForType(netFieldTypes_t fieldType)
{
	if (Demo_IsIdle())
	{
		Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
	}

	if (8 - demo.header.maxClients < 0)
	{
		Com_Error(ERR_DROP, "Invalid Version Handling. Grab Bat !!!");
	}

	return &s_demoOtherNetFieldLists[8 - demo.header.maxClients][fieldType];
}

/*
==============
Demo_GetStateFieldListForEntityType
==============
*/
const NetFieldList *Demo_GetStateFieldListForEntityType(const int eType)
{
	if (Demo_IsIdle())
	{
		Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
	}

	if (8 - demo.header.maxClients < 0)
	{
		Com_Error(ERR_DROP, "Invalid Version Handling. Grab Bat !!!");
	}

	if (eType > 21)
	{
		eType = 21;
	}

	return &s_demoEntityNetFieldLists[8 - demo.header.maxClients][eType];
}

