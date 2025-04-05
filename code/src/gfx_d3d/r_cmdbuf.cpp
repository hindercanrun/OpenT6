#include "types.h"

/*
==============
R_ShutdownCmdBuf
==============
*/
void R_ShutdownCmdBuf(GfxCmdBuf *context)
{
	assert(context);
	assert(dx.cmdBuf[cmdBuf->viewIndex].list[cmdBuf->deviceIndex] == NULL);

	ID3D11DeviceContext *buf = dx.cmdBuf[cmdBuf->viewIndex].context[cmdBuf->deviceIndex];
	buf->FinishCommandList(buf, 0, (4 * (cmdBuf->deviceIndex + 99 * cmdBuf->viewIndex) + 138259804));
}

/*
==============
R_InitContext
==============
*/
void R_InitContext(const GfxBackEndData *data, GfxCmdBuf *cmdBuf)
{
	cmdBuf->device = dx.context;
}

