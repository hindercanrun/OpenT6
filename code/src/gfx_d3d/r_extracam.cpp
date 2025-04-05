#include "types.h"

/*
==============
CreateExtraCamRenderTargets
==============
*/
void CreateExtraCamRenderTargets(eExtraCamResolution resConfig, int location)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ExtraCam_Init
==============
*/
void R_ExtraCam_Init(int location)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ExtraCam_Shutdown
==============
*/
void R_ExtraCam_Shutdown()
{
	if (!g_extraCamConfig.initialized)
	{
		return;
	}

	R_ShutdownExtraCamRenderTargets();
	PMem_Free("ExtraCamHeap");

	g_extraCamConfig.initialized = FALSE;
}

/*
==============
R_ExtraCam_RenderTargetWidth
==============
*/
unsigned int R_ExtraCam_RenderTargetWidth(bool usingMultiExtraCam)
{
	if (!usingMultiExtraCam)
	{
		return g_extraCamConfig.renderTargetWidth;
	}
	else
	{
		return g_extraCamConfig.multi_renderTargetWidth;
	}
}

/*
==============
R_ExtraCam_RenderTargetHeight
==============
*/
unsigned int R_ExtraCam_RenderTargetHeight(bool usingMultiExtraCam)
{
	if (!usingMultiExtraCam)
	{
		return g_extraCamConfig.renderTargetHeight;
	}
	else
	{
		return g_extraCamConfig.multi_renderTargetHeight;
	}
}

/*
==============
R_ExtraCam_GfxResourcesReady
==============
*/
BOOL R_ExtraCam_GfxResourcesReady()
{
	return g_extraCamConfig.initialized && renderTarget.image;
}

/*
==============
RB_ExtraCam_SetSampler
==============
*/
void RB_ExtraCam_SetSampler(GfxCmdBufSourceState *source)
{
	if (!renderTarget.image)
	{
		return;
	}

	assert(source);
	source->input.codeImages[34] = renderTarget.image;
}

