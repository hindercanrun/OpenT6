#include "types.h"

/*
==============
DB_InitStreams
==============
*/
void DB_InitStreams(XBlock *blocks)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_PushStreamPos
==============
*/
void DB_PushStreamPos(unsigned int index)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_PopStreamPos
==============
*/
void DB_PopStreamPos()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DB_GetStreamPos
==============
*/
unsigned __int8 *DB_GetStreamPos()
{
	return g_streamPos;
}

/*
==============
DB_AllocStreamPos
==============
*/
unsigned __int8 *DB_AllocStreamPos(int alignment)
{
	assert(g_streamPos);
	g_streamPos = (~alignment & &g_streamPos[alignment]);
	return g_streamPos;
}

/*
==============
DB_IncStreamPos
==============
*/
void DB_IncStreamPos(int size)
{
	assert(g_streamPos);
	assert(g_streamPos + size <= g_streamBlocks[g_streamPosIndex].data + g_streamBlocks[g_streamPosIndex].size);
	g_streamPos += size;
}

/*
==============
DB_InsertPointer
==============
*/
const void **DB_InsertPointer()
{
	DB_PushStreamPos(5);

	assert(g_streamPos);
	g_streamPos = ((g_streamPos + 3) & 0xFFFFFFFC);

	DB_IncStreamPos(4);
	DB_PopStreamPos();

	return g_streamPos;
}

