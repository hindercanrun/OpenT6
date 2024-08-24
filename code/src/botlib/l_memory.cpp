#include "types.h"

/*
==============
GetMemory
==============
*/
char *GetMemory(unsigned int size)
{
	char* result = Z_Malloc(size + 4, "GetMemory", 12);

	if (result)
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
	unsigned __int8 *v1 = Z_Malloc(size + 4, "GetMemory", 12);

	if (v1)
	{
		char *v3 = (v1 + 4);
		*v1 = 305419896;

		memset(v1 + 4, 0, size);

		return v3;
	}
	else
	{
		memset(0, 0, size);

		return 0;
	}
}

/*
==============
FreeMemory
==============
*/
void FreeMemory(void *ptr)
{
	if (*(ptr - 1) == 305419896)
	{
		Z_Free(ptr - 4);
	}
}

