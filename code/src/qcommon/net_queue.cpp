#include "types.h"

/*
==============
PacketQueueBlock_Enqueue
==============
*/
PacketQueueEntry *PacketQueueBlock_Enqueue(PacketQueueBlock *block, unsigned int flags, int dequeueTime, netsrc_t sock, const netadr_t *addr, int length, const void *data)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
PacketQueueBlock_Dequeue
==============
*/
bool PacketQueueBlock_Dequeue(PacketQueueBlock *block)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PacketQueueBlock_Peek
==============
*/
PacketQueueEntry *PacketQueueBlock_Peek(PacketQueueBlock *block)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
PacketQueue_AddTailBlock
==============
*/
bool PacketQueue_AddTailBlock(PacketQueue *queue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PacketQueue_RemoveHeadBlock
==============
*/
void PacketQueue_RemoveHeadBlock(PacketQueue *queue)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
PacketQueue_Peek
==============
*/
PacketQueueEntry *PacketQueue_Peek(PacketQueue *queue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
PacketQueue_EnqueueInternal
==============
*/
PacketQueueEntry *PacketQueue_EnqueueInternal(PacketQueue *queue, unsigned int flags, int dequeueTime, netsrc_t sock, const netadr_t *addr, int length, const void *data)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
PacketQueue_DequeueInternal
==============
*/
bool PacketQueue_DequeueInternal(PacketQueue *queue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PacketQueue_Enqueue
==============
*/
PacketQueueEntry *PacketQueue_Enqueue(PacketQueue *queue, unsigned int flags, netsrc_t sock, const netadr_t *addr, int length, const void *data)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
PacketQueue_Dequeue
==============
*/
bool PacketQueue_Dequeue(PacketQueue *queue, unsigned int *flags, netsrc_t *sock, netadr_t *addr, int maxlength, int *length, void *data)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
NET_InitQueues
==============
*/
void NET_InitQueues()
{
	assert(s_packetQueueBlockFreeHead == 0);

	for (unsigned int i = 0; i < 26; ++i)
	{
		s_packetQueueBlocks[i].next = (i * 16396 + 125080676);
	}

	s_packetQueueBlocks[25].next = 0;
	s_packetQueueBlockFreeHead = s_packetQueueBlocks;
	s_packetQueues = 0;

	net_emu_latency = Dvar_RegisterInt("net_emu_latency", 0, 0, 1000, 0, "Emulated network latency in ms");
	net_emu_jitter = Dvar_RegisterInt("net_emu_jitter", 0, 0, 1000, 0, "Emulated network latency jitter in ms");
	net_emu_packet_loss = Dvar_RegisterInt("net_emu_packet_loss", 0, 0, 100, 0, "Emulated network %% packet loss");
	net_emu_server = Dvar_RegisterString("net_emu_server", nullptr, 0, "Server network emulation info string");
	net_emu_client = Dvar_RegisterString("net_emu_client", nullptr, 0, "Client network emulation info string");
}

/*
==============
NET_InitQueue
==============
*/
void NET_InitQueue(PacketQueue *queue, const char *name, bool emulation)
{
	assert(queue);

	memset(queue, 0, sizeof(PacketQueue));
	queue->name = name;
	queue->tail = 0;
	queue->head = 0;
	queue->emulation = emulation;
	queue->nextQueue = queue;
	queue->queuedBytesLimit = 0x7FFFFFFF;
	queue->queuedPacketsLimit = 0x7FFFFFFF;
	queue->bucketBitsPerMS = 0;
	queue->bucketBitsLimit = 0x7FFFFFFF;
}

/*
==============
NET_DequeuePacket
==============
*/
bool NET_DequeuePacket(char *a1, PacketQueue *queue, unsigned int *flags, netsrc_t *sock, netadr_t *addr, int maxlength, int *length)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
NET_EnqueuePacket
==============
*/
bool __cdecl NET_EnqueuePacket(PacketQueue *queue, unsigned int flags, netsrc_t sock, const netadr_t *addr, int length)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
NET_QueueCmd
==============
*/
void NET_QueueCmd()
{
	UNIMPLEMENTED(__FUNCTION__);
}

