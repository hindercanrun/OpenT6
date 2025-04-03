#include "types.h"

/*
==============
Com_UnloadWorld
==============
*/
void Com_UnloadWorld()
{
	assert(IsFastFileLoad());
	if (comWorld.isInUse)
	{
		Sys_Error("Cannot unload world while it is in use");
	}
}

