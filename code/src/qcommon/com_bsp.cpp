#include "types.h"

/*
==============
Com_UnloadWorld
==============
*/
void Com_UnloadWorld()
{
	assert(!useFastFile->current.enabled);

	if (comWorld.isInUse)
	{
		Sys_Error("Cannot unload world while it is in use");
	}
}

