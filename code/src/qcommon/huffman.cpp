#include "types.h"

/*
==============
Huff_offsetReceive
==============
*/
void Huff_offsetReceive(nodetype *node, unsigned __int8 *ch, const unsigned __int8 *fin, int *_offset)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
huffman_send
==============
*/
void huffman_send(nodetype *node, nodetype *child, unsigned __int8 *fout)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Huff_offsetTransmit
==============
*/
void Huff_offsetTransmit(huff_t *huff, int ch, unsigned __int8 *fout, int *offset)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Huff_Init
==============
*/
void Huff_Init(huffman_t *huff)
{
	Com_Memset(huff, 0, 19476);

	huff->compressDecompress.loc[256] = &huff->compressDecompress.nodeList[huff->compressDecompress.blocNode++];
	huff->compressDecompress.tree = huff->compressDecompress.loc[256];
	huff->compressDecompress.tree->symbol = 256;
	huff->compressDecompress.tree->weight = 0;
	huff->compressDecompress.tree->parent = 0;
	huff->compressDecompress.tree->left = 0;
	huff->compressDecompress.tree->right = 0;
}

/*
==============
nodeCmp
==============
*/
int nodeCmp(const void *left, const void *right)
{
	return *(DWORD *)(*(DWORD *)left + 12) - *(DWORD *)(*(DWORD *)right + 12);
}

/*
==============
Huff_BuildFromData
==============
*/
void Huff_BuildFromData(huff_t *huff, const int *msg_hData)
{
	UNIMPLEMENTED(__FUNCTION__);
}

