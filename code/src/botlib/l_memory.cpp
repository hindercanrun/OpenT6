#include "types.h"

/*
==============
GetMemory
==============
*/
char *GetMemory(unsigned int size)
{
	char* result = Z_Malloc(size + 4, "GetMemory", 12);

	if ( result )
	{
		*result = 305419896;
		result += 4;
	}

	return result;
}

/*
==============
GetClearedMemory
==============
*/
char *GetClearedMemory(unsigned int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
FreeMemory
==============
*/
void FreeMemory(void *ptr)
{
	if ( *( ptr - 1 ) == 305419896 )
	{
		Z_Free(ptr - 4);
	}
}

