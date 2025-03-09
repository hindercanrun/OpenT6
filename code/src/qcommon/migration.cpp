#include "types.h"

/*
==============
Migration_Init
==============
*/
void Migration_Init(unsigned __int8 *buffer, int len)
{
	assert(buffer);
	assert(len);
	assert(migrationGlob.buffer);

	migrationGlob.buffer = buffer;
	migrationGlob.size = len;

	Com_Memset(buffer, 170, len);
}

/*
==============
Migration_Shutdown
==============
*/
void Migration_Shutdown()
{
	migrationGlob.buffer = 0;
	migrationGlob.size = 0;
}

/*
==============
Migration_GetBuffer
==============
*/
unsigned __int8 *Migration_GetBuffer()
{
	return migrationGlob.buffer;
}

/*
==============
Migration_GetBufferSize
==============
*/
int Migration_GetBufferSize()
{
	return migrationGlob.size;
}

