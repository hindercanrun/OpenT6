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

	return demo.header.version;
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
		return TRUE;
	}
	if (Demo_IsIdle())
	{
		Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
	}

	return demo.header.version >= version;
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

	int netFieldsVersionIndex = 1 - Demo_GetVersion();
	if (netFieldsVersionIndex < 0)
	{
		Com_Error(ERR_DROP, "Invalid Version Handling. Grab Bat !!!");
	}

	return &s_demoOtherNetFieldLists[netFieldsVersionIndex][fieldType];
}

/*
==============
Demo_GetStateFieldListForEntityType
==============
*/
const NetFieldList *Demo_GetStateFieldListForEntityType(const int entityType)
{
	if (Demo_IsIdle())
	{
		Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
	}

	int netFieldsVersionIndex = 1 - Demo_GetVersion();
	if (netFieldsVersionIndex < 0)
	{
		Com_Error(ERR_DROP, "Invalid Version Handling. Grab Bat !!!");
	}

	static int fieldType;
	if (entityType > 21)
	{
		fieldType = 21;
	}
	else
	{
		fieldType = entityType;
	}

	return &s_demoEntityNetFieldLists[netFieldsVersionIndex][fieldType];
}

