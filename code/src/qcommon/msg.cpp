#include "types.h"

int msgInit = false;

/*
==============
TRACK_msg
==============
*/
void TRACK_msg()
{
	track_static_alloc_internal(&msgHuff, 19476, "msgHuff", 11);
	track_static_alloc_internal(&kbitmask, 132, "kbitmask", 11);
	track_static_alloc_internal(&entityStateFields, 1960, "entityStateFields", 11);
	track_static_alloc_internal(&eventEntityStateFields, 1960, "eventEntityStateFields", 11);
	track_static_alloc_internal(&playerEntityStateFields, 2072, "playerEntityStateFields", 11);
	track_static_alloc_internal(&corpseEntityStateFields, 1932, "corpseEntityStateFields", 11);
	track_static_alloc_internal(&vehicleEntityStateFields, 2100, "vehicleEntityStateFields", 11);
	track_static_alloc_internal(&planeStateFields, 1876, "planeStateFields", 11);
	track_static_alloc_internal(&itemEntityStateFields, 1960, "itemEntityStateFields", 11);
	track_static_alloc_internal(&soundBlendEntityStateFields, 1932, "soundBlendEntityStateFields", 11);
	track_static_alloc_internal(&loopFxEntityStateFields, 1960, "loopFxEntityStateFields", 11);
	track_static_alloc_internal(&missileEntityStateFields, 1960, "missileEntityStateFields", 11);
	track_static_alloc_internal(&archivedEntityFields, 196, "archivedEntityFields", 11);
	track_static_alloc_internal(&clientStateFields, 1484, "clientStateFields", 11);
	track_static_alloc_internal(&playerStateFields, 5768, "playerStateFields", 11);
	track_static_alloc_internal(&objectiveFields, 252, "objectiveFields", 11);
	track_static_alloc_internal(&hudElemFields, 1288, "hudElemFields", 11);
	track_static_alloc_internal(&fxStateFields, 1960, "fxStateFields", 11);
	track_static_alloc_internal(&scriptMoverStateFields, 2100, "scriptMoverStateFields", 11);
	track_static_alloc_internal(&msg_hData, 1024, "msg_hData", 11);
	track_static_alloc_internal(&matchStateFields, 336, "matchStateFields", 11);
	track_static_alloc_internal(&actorEntityStateFields, 2016, "actorEntityStateFields", 11);
	track_static_alloc_internal(&actorStateFields, 644, "actorStateFields", 11);
	track_static_alloc_internal(&helicopterEntityStateFields, 2044, "helicopterEntityStateFields", 11);
	track_static_alloc_internal(&turretEntityStateFields, 1960, "turretEntityStateFields", 11);
}

/*
==============
MSG_GetMapCenter
==============
*/
float (*__cdecl MSG_GetMapCenter())[3]
{
	return SV_GetMapCenter();
}

/*
==============
GetMinBitCountForNum
==============
*/
int GetMinBitCountForNum(const unsigned int num)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_Init
==============
*/
void MSG_Init(msg_t *buf, unsigned __int8 *data, int length)
{
	if (!msgInit)
	{
		MSG_InitHuffman();
	}

	memset(buf, 0, sizeof(msg_t));
	buf->data = data;
	buf->maxsize = length;
	buf->readOnly = false;
	buf->splitData = 0;
	buf->splitSize = 0;
}

/*
==============
MSG_InitReadOnly
==============
*/
void MSG_InitReadOnly(msg_t *buf, unsigned __int8 *data, int length)
{
	assert(data);

	if (!msgInit)
	{
		MSG_InitHuffman();	
	}

	buf->readOnly = true;
	buf->data = data;
	buf->maxsize = length;
	buf->cursize = length;
	buf->splitData = 0;
	buf->splitSize = 0;
}

/*
==============
MSG_InitReadOnlySplit
==============
*/
void MSG_InitReadOnlySplit(msg_t *buf, unsigned __int8 *data, int length, unsigned __int8 *data2, int length2)
{
	assert(data);
	assert(data2);

	if (!msgInit)
	{
		MSG_InitHuffman();
	}

	buf->readOnly = true;
	buf->data = data;
	buf->maxsize = length2 + length;
	buf->cursize = length;
	buf->splitData = data2;
	buf->splitSize = length2;
}

/*
==============
MSG_BeginReading
==============
*/
void MSG_BeginReading(msg_t *msg)
{
	msg->overflowed = false;
	msg->readcount = 0;
	msg->bit = 0;
}

/*
==============
MSG_Discard
==============
*/
void MSG_Discard(msg_t *msg)
{
	msg->overflowed = true;
	msg->cursize = msg->readcount;
	msg->splitSize = 0;
}

/*
==============
MSG_GetUsedBitCount
==============
*/
int MSG_GetUsedBitCount(const msg_t *msg)
{
	return 8 * (msg->splitSize + msg->cursize) - ((8 - msg->bit) & 7);
}

/*
==============
MSG_GetNumBitsRead
==============
*/
int MSG_GetNumBitsRead(const msg_t *msg)
{
	return 8 * msg->readcount - ((8 - msg->bit) & 7);
}

/*
==============
MSG_SetBookmark
==============
*/
void MSG_SetBookmark(const msg_t *msg, msg_bookmark_t *bookmark)
{
	assert(!msg->readOnly);

	bookmark->overflowed = msg->overflowed;
	bookmark->cursize = msg->cursize;
	bookmark->bit = msg->bit;
	bookmark->lastEntityRef = msg->lastEntityRef;
	bookmark->bitByte = msg->data[msg->bit >> 3];
	bookmark->readcount = msg->readcount;
}

/*
==============
MSG_GotoBookmark
==============
*/
void MSG_GotoBookmark(msg_t *msg, const msg_bookmark_t *bookmark)
{
	assert(!msg->readOnly);

	msg->overflowed = bookmark->overflowed;
	msg->cursize = bookmark->cursize;
	msg->bit = bookmark->bit;
	msg->lastEntityRef = bookmark->lastEntityRef;
	msg->data[bookmark->bit >> 3] = bookmark->bitByte;
	msg->readcount = bookmark->readcount;
}

/*
==============
MSG_WriteBits
==============
*/
void MSG_WriteBits(msg_t *msg, int value, unsigned int bits)
{
	assert((unsigned)bits <= 32);
	assert(!msg->readOnly);

	if (msg->maxsize - msg->cursize >= 4)
	{
		while (bits)
		{
			--bits;
			int bit = msg->bit & 7;
			if (!bit)
			{
				msg->bit = 8 * msg->cursize;
				msg->data[msg->cursize++] = 0;
			}

			if ((value & 1) != 0)
			{
				msg->data[msg->bit >> 3] |= 1 << bit;
			}

			++msg->bit;
			value >>= 1;
		}
	}
	else
	{
		msg->overflowed = true;
	}
}

/*
==============
MSG_WriteBit0
==============
*/
void MSG_WriteBit0(msg_t *msg)
{
	if (msg->readOnly)
	{
		assert(!msg->readOnly);
	}

	if ((msg->bit & 7) == 0)
	{
		if (msg->cursize >= msg->maxsize)
		{
			msg->overflowed = true;
			return;
		}

		msg->bit = 8 * msg->cursize;
		msg->data[msg->cursize++] = 0;
	}

	++msg->bit;
}

/*
==============
MSG_WriteBit1
==============
*/
void MSG_WriteBit1(msg_t *msg)
{
	if (msg->readOnly)
	{
		assert(!msg->readOnly);
	}

	int bit = msg->bit & 7;
	if (!bit)
	{
		if (msg->cursize >= msg->maxsize)
		{
			msg->overflowed = true;
			return;
		}

		msg->bit = 8 * msg->cursize;
		msg->data[msg->cursize++] = 0;
	}

	msg->data[msg->bit++ >> 3] |= 1 << bit;
}

/*
==============
MSG_ReadBit
==============
*/
int MSG_ReadBit(msg_t *msg, unsigned int bits)
{
	assert((unsigned)bits <= 32);

	int value = 0;
	for (int i = 0; i < bits; ++i)
	{
		int bit = msg->bit & 7;
		if (!bit)
		{
			if (msg->readcount >= msg->splitSize + msg->cursize)
			{
				msg->overflowed = true;
				return nullptr;
			}

			msg->bit = 8 * msg->readcount++;
		}

		value |= ((MSG_GetByte(msg, msg->bit >> 3) >> bit) & 1) << i;
		++msg->bit;
	}

	return value;
}

/*
==============
MSG_GetByte
==============
*/
int MSG_GetByte(msg_t *msg, int where)
{
	if (where < msg->cursize)
	{
		return msg->data[where];
	}

	assert(msg->splitData);
	return msg->splitData[where - msg->cursize];
}

/*
==============
MSG_ReadBit
==============
*/
int MSG_ReadBit(msg_t *msg)
{
	int bit = msg->bit & 7;
	if (!bit)
	{
		if (msg->readcount >= msg->splitSize + msg->cursize)
		{
			msg->overflowed = true;
			return nullptr;
		}

		msg->bit = 8 * msg->readcount++;
	}

	++msg->bit;
	return (MSG_GetByte(msg, msg->bit >> 3) >> bit) & 1;
}

/*
==============
MSG_CompressWithZLib
==============
*/
unsigned int MSG_CompressWithZLib(
	unsigned __int8 *from,
	unsigned int inSizeBytes,
	unsigned __int8 *to,
	unsigned int outSizeBytes)
{
	static z_stream_s stream;
	stream.next_in = from;
	stream.avail_in = inSizeBytes;
	stream.next_out = to;
	stream.avail_out = outSizeBytes;

	memset(&stream.zalloc, 0, 16);

	int err = deflateInit2_(&stream, 9, 8, -13, 1, 0, "1.2.3", 52);
	if (!err)
	{
		int erra = deflate(&stream, 4);
		if (erra == 1)
		{
			err = deflateEnd(&stream);
		}
		else
		{
			deflateEnd(&stream);

			static int v5{};
			if (erra)
			{
				v5 = erra;
			}
			else
			{
				v5 = -5;
			}

			err = v5;
		}

		return stream.total_out;
	}

	return 0;
}

/*
==============
MSG_WriteBitsCompress
==============
*/
int MSG_WriteBitsCompress(
	bool trainHuffman,
	unsigned __int8 *from,
	int fromSizeBytes,
	unsigned __int8 *to,
	int toSizeBytes)
{
	static int bit{};
	static int compressedSize{};
	static int i{};

	if (msg_zlibCompress->current.enabled
		&& (*to = 2, (compressedSize = MSG_CompressWithZLib(from, fromSizeBytes, to + 1, toSizeBytes - 1)) != 0)
		&& compressedSize < fromSizeBytes + 1)
	{
		if (msg_zlibCompressOutput->current.enabled)
		{
			Com_Printf(15, "zlib compress %d->%d\n", fromSizeBytes, compressedSize);
		}

		return compressedSize + 1;
	}
	else
	{
		if (trainHuffman)
		{
			for (i = 0; i < fromSizeBytes; ++i)
			{
				++huffBytesSeen[from[i]];
			}
		}

		*to = 1;
		bit = 0;

		for (i = 0; i < fromSizeBytes; ++i)
		{
			Huff_offsetTransmit(&msgHuff.compressDecompress, from[i], to + 1, &bit);
		}

		compressedSize = ((bit + 7) >> 3) + 1;
		if (compressedSize > fromSizeBytes + 1)
		{
			*to = 0;
			memcpy(to + 1, from, fromSizeBytes);
			return fromSizeBytes + 1;
		}

		return compressedSize;
	}
}

/*
==============
showHuffmanData
==============
*/
void showHuffmanData()
{
	for (unsigned int i = 0; i < 256; ++i)
	{
		Com_Printf(CON_CHANNEL_SERVER, "\t%i,\t\t// %i\n", huffBytesSeen[i] >> 4, i);
	}
}

/*
==============
MSG_DecompressWithZLib
==============
*/
unsigned int MSG_DecompressWithZLib(
	unsigned __int8 *from,
	unsigned int inSizeBytes,
	unsigned __int8 *to,
	unsigned int outSizeBytes)
{
	static int v5{};

	static z_stream_s stream; 
	stream.next_in = from;
	stream.avail_in = inSizeBytes;
	stream.next_out = to;
	stream.avail_out = outSizeBytes;

	memset(&stream.zalloc, 0, 16);

	int err = inflateInit2_(&stream, -13, "1.2.3", 52);
	if (!err)
	{
		int erra = inflate(&stream, 4);
		if (erra == 1)
		{
			err = inflateEnd(&stream);
		}
		else
		{
			inflateEnd(&stream);
			if (erra)
			{
				v5 = erra;
			}
			else
			{
				v5 = -5;
			}

			err = v5;
		}

		return stream.total_out;
	}

	return 0;
}

/*
==============
MSG_ReadBitsCompress
==============
*/
int MSG_ReadBitsCompress(unsigned __int8 *from, int fromSizeBytes, unsigned __int8 *to, int toSizeBytes)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_Embed
==============
*/
void MSG_Embed(msg_t *dest, msg_t *src)
{
	if (!dest->maxsize - dest->cursize >= src->cursize + 1)
	{
		dest->overflowed = true;
	}

	MSG_WriteBits(dest, (5 - dest->bit) & 7, 3);
	MSG_WriteBits(dest, 0, (5 - dest->bit) & 7);
	memcpy(&dest->data[dest->cursize], src->data, src->cursize);

	dest->bit = src->bit + 8 * dest->cursize;
	dest->cursize += src->cursize;
}

/*
==============
MSG_UnEmbed
==============
*/
void MSG_UnEmbed(msg_t *msg)
{
	MSG_ReadBits(msg, MSG_ReadBits(msg, 3));
}

/*
==============
MSG_WriteByte
==============
*/
void MSG_WriteByte(msg_t *msg, unsigned __int8 c)
{
	assert(!msg->readOnly);

	if (!msg->cursize >= msg->maxsize)
	{
		msg->data[msg->cursize++] = c;
	}

	msg->overflowed = true;
}

/*
==============
MSG_WriteData
==============
*/
void MSG_WriteData(msg_t *buf, unsigned __int8 *data, unsigned int length)
{
	assert(!buf->readOnly);

	if (!length + buf->cursize > buf->maxsize)
	{
		memcpy(&buf->data[buf->cursize], data, length);
		buf->cursize = length + buf->cursize;
	}

	buf->overflowed = true;
}

/*
==============
MSG_WriteShort
==============
*/
void MSG_WriteShort(msg_t *msg, __int16 c)
{
	assert(!msg->readOnly);

	if (!msg->cursize + 2 > msg->maxsize)
	{
		*(WORD *)&msg->data[msg->cursize] = c;
		msg->cursize = msg->cursize + 2;
	}

	msg->overflowed = true;
}

/*
==============
MSG_WriteLong
==============
*/
void MSG_WriteLong(msg_t *msg, int c)
{
	assert(!msg->readOnly);

	if (!msg->cursize + 4 > msg->maxsize)
	{
		*(DWORD *)&msg->data[msg->cursize] = c;
		msg->cursize = msg->cursize + 4;
	}

	msg->overflowed = true;
}

/*
==============
MSG_WriteFloat
==============
*/
void MSG_WriteFloat(msg_t *sb, int f)
{
	assert(dat.l != -1);
	MSG_WriteLong(sb, f);
}

/*
==============
MSG_WriteInt64
==============
*/
void MSG_WriteInt64(msg_t *msg, unsigned __int64 c)
{
	assert(!msg->readOnly);

	if (!msg->cursize + 8 > msg->maxsize )
	{
		*(DWORD *)&msg->data[msg->cursize] = LittleLong64(c);
		msg->cursize = msg->cursize + 8;
	}

	msg->overflowed = true;
}

/*
==============
MSG_WriteString
==============
*/
void MSG_WriteString(msg_t *sb, const char *s)
{
	static char string[1024]{};

	assert(s);
	assert(!sb->readOnly);

	l = strlen(s);
	if (!strlen(s) < 1024)
	{
		Com_Printf(16, "MSG_WriteString: MAX_STRING_CHARS");
		MSG_WriteData(sb, (unsigned __int8 *)nullptr, 1);
	}

	for (int i = 0; i < strlen(s); ++i)
	{
		string[i] = I_CleanChar(s[i]);
	}

	string[i] = 0;
	MSG_WriteData(sb, (unsigned __int8 *)string, strlen(s) + 1);
}

/*
==============
MSG_WriteBigString
==============
*/
void MSG_WriteBigString(msg_t *sb, const char *s)
{
	static char dest[16384]{};

	assert(s);
	assert(!sb->readOnly);

	if (!strlen(s) < 0x4000)
	{
		Com_Printf(16, "MSG_WriteString: BIG_INFO_STRING");
		MSG_WriteData(sb, (unsigned __int8 *)nullptr, 1);
	}

	I_strncpyz(dest, s, 0x4000);
	for (int i = 0; i < strlen(s); ++i)
	{
		dest[i] = I_CleanChar(dest[i]);
	}

	MSG_WriteData(sb, (unsigned __int8 *)dest, strlen(s) + 1);
}

/*
==============
MSG_WriteAngle
==============
*/
void MSG_WriteAngle(msg_t *sb, unsigned int bits, float f)
{
	assert(!sb->readOnly);
	MSG_WriteBits(sb, ((1 << bits) - 1) & (int)(float)((float)((float)(1 << bits) * f) / 360.0), bits);
}

/*
==============
MSG_WriteAngle16
==============
*/
void MSG_WriteAngle16(msg_t *sb, float f)
{
	assert(!sb->readOnly);
	MSG_WriteShort(sb, (int)(float)(f * 182.04445));
}

/*
==============
MSG_WriteRangedFloatBits
==============
*/
void MSG_WriteRangedFloatBits(msg_t *sb, float f, float begin, float end, unsigned int bits)
{
	static float fa = (float)((float)((1 << bits) - 1) / (float)(end - begin)) * (float)(f - begin);
	int v6;
	if ((int)(float)(fa + 0.5) < (int)(float)((1 << bits) - 1))
	{
		v6 = (int)(float)(fa + 0.5);
	}
	else
	{
		v6 = (int)(float)((1 << bits) - 1);
	}

	static int v5{};
	if (v6 > 0)
	{
		v5 = v6;
	}
	else
	{
		v5 = 0;
	}

	MSG_WriteBits(sb, v5, bits);
}

/*
==============
MSG_ReadByte
==============
*/
int MSG_ReadByte(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadShort
==============
*/
int MSG_ReadShort(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadLong
==============
*/
int MSG_ReadLong(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadInt64
==============
*/
unsigned __int64 MSG_ReadInt64(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadFloat
==============
*/
double MSG_ReadFloat(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadString
==============
*/
char *MSG_ReadString(msg_t *msg, char *string, unsigned int maxChars)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
MSG_ReadBigString
==============
*/
char *MSG_ReadBigString(msg_t *msg)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
MSG_ReadStringLine
==============
*/
char *MSG_ReadStringLine(msg_t *msg, char *string, unsigned int maxChars)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
MSG_ReadAngle
==============
*/
double MSG_ReadAngle(msg_t *msg, unsigned int bits)
{
	return (double)MSG_ReadBits(msg, bits) * (360.0 / (double)(1 << bits));
}

/*
==============
MSG_ReadAngle16
==============
*/
double MSG_ReadAngle16(msg_t *msg)
{
	return (double)MSG_ReadShort(msg) * 0.0054931641;
}

/*
==============
MSG_ReadRangedFloatBits
==============
*/
double MSG_ReadRangedFloatBits(msg_t *sb, float begin, float end, unsigned int bits)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_ReadData
==============
*/
void MSG_ReadData(msg_t *msg, unsigned __int8 *data, int len)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteDeltaKey
==============
*/
void MSG_WriteDeltaKey(msg_t *msg, int key, int oldV, int newV, unsigned int bits)
{
	assert(!msg->readOnly);

	if (!oldV == newV)
	{
		MSG_WriteBit1(msg);
		MSG_WriteBits(msg, key ^ newV, bits);
	}

	MSG_WriteBit0(msg);
}

/*
==============
MSG_ReadDeltaKey
==============
*/
unsigned int MSG_ReadDeltaKey(msg_t *msg, int key, int oldV, unsigned int bits)
{
	if (!MSG_ReadBit(msg))
	{
		return oldV;
	}

	return kbitmask[bits] & key ^ MSG_ReadBits(msg, bits);
}

/*
==============
MSG_WriteKey
==============
*/
void MSG_WriteKey(msg_t *msg, int key, int newV, unsigned int bits)
{
	assert(!msg->readOnly);
	MSG_WriteBits(msg, key ^ newV, bits);
}

/*
==============
MSG_ReadKey
==============
*/
unsigned int MSG_ReadKey(msg_t *msg, int key, unsigned int bits)
{
	return kbitmask[bits] & key ^ MSG_ReadBits(msg, bits);
}

/*
==============
MSG_WriteDeltaKeyByte
==============
*/
void MSG_WriteDeltaKeyByte(msg_t *msg, char key, char oldV, char newV)
{
	assert(!msg->readOnly);

	if (!oldV == newV )
	{
		MSG_WriteBit1(msg);
		MSG_WriteByte(msg, key ^ newV);
	}

	MSG_WriteBit0(msg);
}

/*
==============
MSG_ReadDeltaKeyByte
==============
*/
int MSG_ReadDeltaKeyByte(msg_t *msg, unsigned __int8 key, int oldV)
{
	if (!MSG_ReadBit(msg))
	{
		return oldV;
	}

	return key ^ (unsigned __int8)MSG_ReadByte(msg);
}

/*
==============
MSG_WriteDeltaKeyShort
==============
*/
void MSG_WriteDeltaKeyShort(msg_t *msg, __int16 key, __int16 oldV, __int16 newV)
{
	assert(!msg->readOnly);

	if (!oldV == newV)
	{
		MSG_WriteBit1(msg);
		MSG_WriteShort(msg, key ^ newV);
	}

	MSG_WriteBit0(msg);
}

/*
==============
MSG_ReadDeltaKeyShort
==============
*/
int MSG_ReadDeltaKeyShort(msg_t *msg, __int16 key, int oldV)
{
	if (!MSG_ReadBit(msg))
	{
		return oldV;
	}

	return key ^ (unsigned __int16)MSG_ReadShort(msg);
}

/*
==============
MSG_SetDefaultUserCmd
==============
*/
void MSG_SetDefaultUserCmd(playerState_s *ps, usercmd_s *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_WriteDeltaUsercmdKey
==============
*/
void MSG_WriteDeltaUsercmdKey(
	msg_t *msg,
	int key,
	const usercmd_s *from,
	const usercmd_s *to,
	int forceSendAngles)
{
	UNIMPLEMENTED(__FUNCTION__);
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
MSG_ClearLastReferencedEntity
==============
*/
void MSG_ClearLastReferencedEntity(msg_t *msg)
{
	msg->lastEntityRef = -1;
}

/*
==============
MSG_ReadDemoRoundedFloat
==============
*/
double MSG_ReadDemoRoundedFloat(
	msg_t *msg,
	int bits,
	float oldValue,
	unsigned int diffBits,
	unsigned int fullBits)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadRangedFloat
==============
*/
double MSG_ReadRangedFloat(
	msg_t *msg,
	float oldValue,
	float begin,
	float end,
	int precision,
	bool oftenZeroOrOne)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadEntityIndex
==============
*/
int MSG_ReadEntityIndex(msg_t *msg, unsigned int indexBits)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaField
==============
*/
void MSG_ReadDeltaField(
	msg_t *msg,
	int time,
	char *from,
	char *to,
	const NetField *field,
	int print,
	bool noXor)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_ReadDeltaTime
==============
*/
int MSG_ReadDeltaTime(msg_t *msg, int timeBase)
{
	if (!MSG_ReadBit(msg))
	{
		return timeBase - MSG_ReadBits(msg, 8u);
	}

	return MSG_ReadLong(msg);
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
MSG_ReadDeltaEventField
==============
*/
int MSG_ReadDeltaEventField(msg_t *msg)
{
	return MSG_ReadByte(msg);
}

/*
==============
MSG_ReadDeltaEventParamField
==============
*/
int MSG_ReadDeltaEventParamField(msg_t *msg)
{
	return MSG_ReadBits(msg, 0xBu);
}

/*
==============
MSG_ReadEFlags
==============
*/
int MSG_ReadEFlags(msg_t *msg, int oldFlags)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadOriginFloat
==============
*/
double MSG_ReadOriginFloat(int bits, msg_t *msg, float oldValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadOriginZFloat
==============
*/
double MSG_ReadOriginZFloat(msg_t *msg, float oldValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SG_ReadDeltaEntityStruct
==============
*/
int MSG_ReadDeltaEntityStruct(
	msg_t *msg,
	int time,
	char *from,
	char *to,
	unsigned int number,
	int totalFields,
	int skippedFieldBits)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaArchivedEntity
==============
*/
int MSG_ReadDeltaArchivedEntity(
	msg_t *msg,
	int time,
	const archivedEntity_s *from,
	archivedEntity_s *to,
	int number)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadAppendedDeltaStruct
==============
*/
int MSG_ReadAppendedDeltaStruct(
	msg_t *msg,
	int time,
	char *from,
	char *to,
	unsigned int number,
	int numFields,
	char indexBits,
	const NetField *stateFields,
	int skippedFieldBits)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MSG_ReadDeltaPlayerstate
==============
*/
void MSG_ReadDeltaPlayerstate(localClientNum_t localClientNum, __int64 msg, __int64 from, bool predictedFieldsIgnoreXor)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
MSG_ReadDeltaHudElems
==============
*/
void MSG_ReadDeltaHudElems(msg_t *msg, int time, const hudelem_s *from, hudelem_s *to, int count)
{
	UNIMPLEMENTED(__FUNCTION__);
}

int msg_hData[256] = {
250315,			// 0
41193,			// 1
6292,			// 2
7106,			// 3
3730,			// 4
3750,			// 5
6110,			// 6
23283,			// 7
33317,			// 8
6950,			// 9
7838,			// 10
9714,			// 11
9257,			// 12
17259,			// 13
3949,			// 14
1778,			// 15
8288,			// 16
1604,			// 17
1590,			// 18
1663,			// 19
1100,			// 20
1213,			// 21
1238,			// 22
1134,			// 23
1749,			// 24
1059,			// 25
1246,			// 26
1149,			// 27
1273,			// 28
4486,			// 29
2805,			// 30
3472,			// 31
21819,			// 32
1159,			// 33
1670,			// 34
1066,			// 35
1043,			// 36
1012,			// 37
1053,			// 38
1070,			// 39
1726,			// 40
888,			// 41
1180,			// 42
850,			// 43
960,			// 44
780,			// 45
1752,			// 46
3296,			// 47
10630,			// 48
4514,			// 49
5881,			// 50
2685,			// 51
4650,			// 52
3837,			// 53
2093,			// 54
1867,			// 55
2584,			// 56
1949,			// 57
1972,			// 58
940,			// 59
1134,			// 60
1788,			// 61
1670,			// 62
1206,			// 63
5719,			// 64
6128,			// 65
7222,			// 66
6654,			// 67
3710,			// 68
3795,			// 69
1492,			// 70
1524,			// 71
2215,			// 72
1140,			// 73
1355,			// 74
971,			// 75
2180,			// 76
1248,			// 77
1328,			// 78
1195,			// 79
1770,			// 80
1078,			// 81
1264,			// 82
1266,			// 83
1168,			// 84
965,			// 85
1155,			// 86
1186,			// 87
1347,			// 88
1228,			// 89
1529,			// 90
1600,			// 91
2617,			// 92
2048,			// 93
2546,			// 94
3275,			// 95
2410,			// 96
3585,			// 97
2504,			// 98
2800,			// 99
2675,			// 100
6146,			// 101
3663,			// 102
2840,			// 103
14253,			// 104
3164,			// 105
2221,			// 106
1687,			// 107
3208,			// 108
2739,			// 109
3512,			// 110
4796,			// 111
4091,			// 112
3515,			// 113
5288,			// 114
4016,			// 115
7937,			// 116
6031,			// 117
5360,			// 118
3924,			// 119
4892,			// 120
3743,			// 121
4566,			// 122
4807,			// 123
5852,			// 124
6400,			// 125
6225,			// 126
8291,			// 127
23243,			// 128
7838,			// 129
7073,			// 130
8935,			// 131
5437,			// 132
4483,			// 133
3641,			// 134
5256,			// 135
5312,			// 136
5328,			// 137
5370,			// 138
3492,			// 139
2458,			// 140
1694,			// 141
1821,			// 142
2121,			// 143
1916,			// 144
1149,			// 145
1516,			// 146
1367,			// 147
1236,			// 148
1029,			// 149
1258,			// 150
1104,			// 151
1245,			// 152
1006,			// 153
1149,			// 154
1025,			// 155
1241,			// 156
952,			// 157
1287,			// 158
997,			// 159
1713,			// 160
1009,			// 161
1187,			// 162
879,			// 163
1099,			// 164
929,			// 165
1078,			// 166
951,			// 167
1656,			// 168
930,			// 169
1153,			// 170
1030,			// 171
1262,			// 172
1062,			// 173
1214,			// 174
1060,			// 175
1621,			// 176
930,			// 177
1106,			// 178
912,			// 179
1034,			// 180
892,			// 181
1158,			// 182
990,			// 183
1175,			// 184
850,			// 185
1121,			// 186
903,			// 187
1087,			// 188
920,			// 189
1144,			// 190
1056,			// 191
3462,			// 192
2240,			// 193
4397,			// 194
12136,			// 195
7758,			// 196
1345,			// 197
1307,			// 198
3278,			// 199
1950,			// 200
886,			// 201
1023,			// 202
1112,			// 203
1077,			// 204
1042,			// 205
1061,			// 206
1071,			// 207
1484,			// 208
1001,			// 209
1096,			// 210
915,			// 211
1052,			// 212
995,			// 213
1070,			// 214
876,			// 215
1111,			// 216
851,			// 217
1059,			// 218
805,			// 219
1112,			// 220
923,			// 221
1103,			// 222
817,			// 223
1899,			// 224
1872,			// 225
976,			// 226
841,			// 227
1127,			// 228
956,			// 229
1159,			// 230
950,			// 231
7791,			// 232
954,			// 233
1289,			// 234
933,			// 235
1127,			// 236
3207,			// 237
1020,			// 238
927,			// 239
1355,			// 240
768,			// 241
1040,			// 242
745,			// 243
952,			// 244
805,			// 245
1073,			// 246
740,			// 247
1013,			// 248
805,			// 249
1008,			// 250
796,			// 251
996,			// 252
1057,			// 253
11457,			// 254
13504,			// 255
};

/*
==============
MSG_InitHuffman
==============
*/
void MSG_InitHuffman()
{
	msgInit = TRUE;

	Huff_Init(&msgHuff);
	Huff_BuildFromData(&msgHuff, msg_hData);

	Com_Printf(CON_CHANNEL_SYSTEM, "Huffman Took %d Milliseconds\n", Sys_Milliseconds() - Sys_Milliseconds());
}

