#include "types.h"

/*
==============
MSG_ReadBits
==============
*/
int MSG_ReadBits(msg_t *msg, int bits)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_WriteBits
==============
*/
void MSG_WriteBits(msg_t *msg, int value, int bits)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteBit0
==============
*/
void MSG_WriteBit0(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteBit1
==============
*/
void MSG_WriteBit1(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteBitsCompress
==============
*/
int MSG_WriteBitsCompress(bool trainHuffman, const unsigned __int8 *from, int fromSizeBytes, unsigned __int8 *to, int toSizeBytes)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_WriteShort
==============
*/
void MSG_WriteShort(msg_t *msg, int c)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteLong
==============
*/
void MSG_WriteLong(msg_t *msg, int c)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_ClearLastReferencedEntity
==============
*/
void MSG_ClearLastReferencedEntity(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
HasMeleeChargeChanged
==============
*/
BOOL HasMeleeChargeChanged(const usercmd_s *from, const usercmd_s *to)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaGroundEntity
==============
*/
int MSG_ReadDeltaGroundEntity(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDemoRoundedFloat
==============
*/
double MSG_ReadDemoRoundedFloat(msg_t *msg, int bits, float oldValue, int diffBits, int fullBits)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaField
==============
*/
void MSG_ReadDeltaField(msg_t *msg, const int time, const void *from, void *to, const NetField *field, int print, __int16 noXor)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_ReadDeltaEntityStruct
==============
*/
int MSG_ReadDeltaEntityStruct(msg_t *msg, const int time, const void *from, void *to, unsigned int number, const int totalFields)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaArchivedEntity
==============
*/
int MSG_ReadDeltaArchivedEntity(msg_t *msg, const int time, const archivedEntity_s *from, archivedEntity_s *to, int number)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaHudElems
==============
*/
void MSG_ReadDeltaHudElems(msg_t *msg, const int time, const hudelem_s *from, hudelem_s *to, int count)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_ReadDeltaPlayerstate
==============
*/
void MSG_ReadDeltaPlayerstate(const LocalClientNum_t localClientNum, msg_t *msg, const int time, const playerState_s *remoteFrom, playerState_s *remoteTo, bool predictedFieldsIgnoreXor)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_DumpNetFieldChanges_f
==============
*/
void MSG_DumpNetFieldChanges_f()
{
	static const int *changeArray[6]{};
	changeArray[0] = (const int *)&orderInfo;
	changeArray[1] = orderInfo.arcEntState;
	changeArray[2] = orderInfo.clientState;
	changeArray[3] = orderInfo.playerState;
	changeArray[4] = orderInfo.objective;
	changeArray[5] = orderInfo.hudElem;

	static int arraySize[6]{};
	arraySize[0] = 79;
	arraySize[1] = 10;
	arraySize[2] = 52;
	arraySize[3] = 179;
	arraySize[4] = 9;
	arraySize[5] = 43;

	static const char *arrayNames[6]{};
	arrayNames[0] = "Entity State";
	arrayNames[1] = "Archived Entity State";
	arrayNames[2] = "Client State";
	arrayNames[3] = "Player State";
	arrayNames[4] = "Objective";
	arrayNames[5] = "HUD Elem";

	Com_Printf(CON_CHANNEL_DONT_FILTER, "========================================\n");
	Com_Printf(CON_CHANNEL_DONT_FILTER, "NetField changes. format: field# : #changes\n");

	for (unsigned int iArrayNum = 0; iArrayNum < 6; ++iArrayNum)
	{
		Com_Printf(CON_CHANNEL_DONT_FILTER, "========================================\n");
		Com_Printf(CON_CHANNEL_DONT_FILTER, "    %s\n", arrayNames[iArrayNum]);
		Com_Printf(CON_CHANNEL_DONT_FILTER, "--------------------\n");

		for (int i = 0; i < arraySize[iArrayNum]; ++i)
		{
			static const int *array;
			if (array[i])
			{
				Com_Printf(CON_CHANNEL_DONT_FILTER, "%3i :%8i\n", i, changeArray[iArrayNum][i]);
			}
		}
	}

	Com_Printf(CON_CHANNEL_DONT_FILTER, "========================================\n");
	Com_Printf(CON_CHANNEL_DONT_FILTER, "========================================\n");
}

/*
==============
MSG_ReadDeltaUsercmdKey
==============
*/
void MSG_ReadDeltaUsercmdKey(msg_t *msg, int key, const usercmd_s *from, usercmd_s *to)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteDeltaUsercmdKey
==============
*/
void MSG_WriteDeltaUsercmdKey(msg_t *msg, int key, const usercmd_s *from, const usercmd_s *to, int forceSendAngles)
{
	UNIMPLEMENTED(__FUNCTION__);
}

