#include "types.h"

unsigned int msg_NetFieldChecksum;
unsigned int msg_ProtocolNetfieldChecksum;

/*
==============
MSG_CRCNetFields
==============
*/
int MSG_CRCNetFields()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
MsgCRC_Init
==============
*/
void MsgCRC_Init()
{
	msg_NetFieldChecksum = MSG_CRCNetFields();
	msg_ProtocolNetfieldChecksum = crc;

	int protocol = BigLong(2078);
	unsigned int crc = Com_BlockChecksumKey32(&protocol, 4u, msg_NetFieldChecksum);
	Dvar_SetString(version, va("%s %x", version->current.string, crc));
}

/*
==============
MsgCRC_NetFieldChecksum
==============
*/
unsigned int MsgCRC_NetFieldChecksum()
{
	return msg_NetFieldChecksum;
}

