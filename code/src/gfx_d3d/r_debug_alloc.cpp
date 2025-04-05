#include "types.h"

/*
==============
R_DebugAlloc
==============
*/
void R_DebugAlloc(void **memPtr, int size, const char *name)
{
	assert(memPtr);
	assert(!*memPtr);
	assert(size > 0);
	assert((size & 0x3) == 0);

	*memPtr = Z_TryVirtualAlloc(size, name, 0);
	if (!memPtr)
	{
		R_WarnOncePerFrame(R_WARN_DEBUG_ALLOC, name);
	}
}

/*
==============
R_DebugFree
==============
*/
void R_DebugFree(void **dataPtr)
{
	if (*dataPtr)
	{
		Z_VirtualFree(*dataPtr);
		*dataPtr = NULL;
	}
}

