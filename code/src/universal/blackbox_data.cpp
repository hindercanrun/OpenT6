#include "types.h"

unsigned int s_stringHashTable[1024];
unsigned int s_stringHits;
unsigned int s_stringMisses;
unsigned int s_stringCollisions;
unsigned int s_stringHitBytes;

struct bb_msg_t
{
	unsigned __int8 *data;
	int maxsize;
	int cursize;
	bool overflow;
	unsigned __int8 *pppHashTable;
	unsigned __int8 pppBits;
	unsigned int pppHash;
	int pppBitOffset;
	int pppBitCount;
};

int s_definitionId;
int s_definitionSentOffset;
__int16 s_definitionMapHashTable[512];
unsigned __int8 s_definitionData[4096];
bb_msg_t s_definitionMsg;

/*
==============
BB_InitStringCache
==============
*/
void BB_InitStringCache()
{
	memset(s_stringHashTable, 0, sizeof(s_stringHashTable));

	s_stringHits = 0;
	s_stringMisses = 0;
	s_stringCollisions = 0;
	s_stringHitBytes = 0;
}

/*
==============
BB_ClearStringCache
==============
*/
void BB_ClearStringCache()
{
	memset(s_stringHashTable, 0, sizeof(s_stringHashTable));
}

/*
==============
BB_HashString
==============
*/
unsigned int BB_HashString(const char *str, int len)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_CacheString
==============
*/
int BB_CacheString(const char *str, int len)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_WriteString
==============
*/
void __cdecl BB_WriteString(bb_msg_t *msg, const char *str, int len)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BB_MsgInit
==============
*/
void BB_MsgInit(bb_msg_t *msg, void *data, int maxsize)
{
	msg->data = data;
	msg->maxsize = maxsize;
	msg->cursize = 0;
	msg->overflow = 0;
	msg->pppHashTable = 0;

	memset(data, 0, maxsize);
}

/*
==============
BB_MsgInitPPP
==============
*/
void BB_MsgInitPPP(bb_msg_t *msg, void *pppHashTable, int size)
{
	assert(size == 4096);
	assert(msg->pppHashTable == 0);

	int cursize = msg->cursize;
	msg->pppBitOffset = cursize;
	msg->cursize = cursize + 1;
	msg->pppBitCount = 0;
	msg->pppBits = 0;
	msg->pppHash = 0;
	msg->pppHashTable = pppHashTable;

	memset(pppHashTable, 0, size);
}

/*
==============
BB_InitDefinitions
==============
*/
void BB_InitDefinitions()
{
	s_definitionId = 0;
	s_definitionSentOffset = 0;

	memset(s_definitionMapHashTable, 0xFFu, sizeof(s_definitionMapHashTable));

	s_definitionMsg.data = s_definitionData;
	s_definitionMsg.maxsize = 4096;
	s_definitionMsg.cursize = 0;
	s_definitionMsg.overflow = 0;
	s_definitionMsg.pppHashTable = 0;

	memset(s_definitionData, 0, sizeof(s_definitionData));
}

/*
==============
BB_RewriteDefinitions
==============
*/
void BB_RewriteDefinitions(bb_msg_t *msg)
{
	s_definitionSentOffset = 0;

	if (s_definitionMsg.cursize > 0)
	{
		BB_Copy(msg, s_definitionMsg.data, s_definitionMsg.cursize);
		s_definitionSentOffset = s_definitionMsg.cursize;
	}
}

/*
==============
BB_BeginDefinition
==============
*/
int __cdecl BB_BeginDefinition(const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_ParseParameter
==============
*/
unsigned __int8 BB_ParseParameter(const char *string, int len)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_GetDefinitionMap
==============
*/
DefinitionMap *BB_GetDefinitionMap(unsigned int nameHash, unsigned int formatHash)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BB_ParseAndCacheFormatString
==============
*/
int BB_ParseAndCacheFormatString(bb_msg_t *msg, const char *name, const char *fmt, int *parameterCount, const unsigned __int8 **parameters)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BB_WriteFormatParameters
==============
*/
void BB_WriteFormatParameters(const void *a1, bb_msg_t *msg, int parameterCount, const unsigned __int8 *parameters, char *args)
{
	UNIMPLEMENTED(__FUNCTION__);
}

