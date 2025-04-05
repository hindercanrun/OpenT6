#include "types.h"

/*
==============
RB_ClearPixelShader
==============
*/
void RB_ClearPixelShader()
{
	if (gfxCmdBufState.pixelShader)
	{
		gfxCmdBufState.prim.device->PSSetShader(gfxCmdBufState.prim.device, 0, 0, 0);
	}

	gfxCmdBufState.pixelShader = NULL;
}

/*
==============
RB_ClearVertexShader
==============
*/
void RB_ClearVertexShader()
{
	if (gfxCmdBufState.vertexShader)
	{
		gfxCmdBufState.prim.device->VSSetShader(gfxCmdBufState.prim.device, 0, 0, 0);
	}

	gfxCmdBufState.vertexShader = NULL;
}

/*
==============
RB_ClearVertexDecl
==============
*/
void RB_ClearVertexDecl()
{
	if (gfxCmdBufState.prim.vertexDecl)
	{
		ID3D11DeviceContext *device = gfxCmdBufState.prim.device;
		assert(device);
		device->IASetInputLayout(device, 0);
		gfxCmdBufState.prim.vertexDecl = NULL;
	}
}

/*
==============
R_BeginPixMaterial
==============
*/
void R_BeginPixMaterial(GfxCmdBufState *state)
{
	if (!r_pix_material->current.enabled)
	{
		state->pixMaterial = NULL;
		state->pixTechnique = NULL;
	}

	const MaterialTechnique *technique = state->technique;
	const Material *material = state->material;

	if (state->pixMaterial != material)
	{
		if (state->pixTechnique)
		{
			state->pixTechnique = NULL;
		}

		if (state->pixMaterial || state->pixTechnique && Sys_IsRenderThread())
		{
			D3DPERF_EndEvent();
		}

		PIXBeginNamedEvent(-1, material->info.name);
	}

	const MaterialTechnique *pixTechnique = state->pixTechnique;
	if (pixTechnique != technique)
	{
		if (pixTechnique && Sys_IsRenderThread())
		{
			D3DPERF_EndEvent();
		}

		PIXBeginNamedEvent(-1, technique->name);
	}

	state->pixMaterial = material;
	state->pixTechnique = technique;
}

/*
==============
R_EndPixMaterial
==============
*/
void R_EndPixMaterial(GfxCmdBufState *state)
{
	if (!state->pixCombine)
	{
		if (state->pixTechnique || state->pixMaterial && Sys_IsRenderThread())
		{
			D3DPERF_EndEvent();
		}

		state->pixTechnique = NULL;
		state->pixMaterial = NULL;
	}
}

/*
==============
R_SetPixPrimarySortKey
==============
*/
void R_SetPixPrimarySortKey(GfxCmdBufState *state, unsigned int primarySortKey)
{
	const char *v2; // eax

	if (state->pixPrimarySortKey != primarySortKey)
	{
		if (state->pixTechnique && Sys_IsRenderThread())
		{
			D3DPERF_EndEvent();
		}

		if (state->pixMaterial && Sys_IsRenderThread())
		{
			D3DPERF_EndEvent();
		}

		state->pixTechnique = NULL;
		state->pixMaterial = NULL;
		state->pixPrimarySortKey = primarySortKey;

		PIXSetMarker(-1, va("key: %d", primarySortKey));
	}
}

/*
==============
R_BeginPixMaterials
==============
*/
void R_BeginPixMaterials(GfxCmdBufState *state)
{
	assert(!state->pixCombine);
	assert(!state->pixMaterial);
	assert(!state->pixTechnique);
	state->pixCombine = TRUE;
	state->pixPrimarySortKey = nullptr;
}

/*
==============
R_EndPixMaterials
==============
*/
void R_EndPixMaterials(GfxCmdBufState *state)
{
	assert(state->pixCombine);

	if ( state->pixTechnique || state->pixMaterial && Sys_IsRenderThread() )
	{
		D3DPERF_EndEvent();
	}

	state->pixTechnique = NULL;
	state->pixMaterial = NULL;
	state->pixCombine = NULL;
}

/*
==============
R_DrawTessTechnique
==============
*/
void R_DrawTessTechnique(GfxCmdBufContext context, const GfxDrawPrimArgs *args)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
RB_BeginSurface
==============
*/
void RB_BeginSurface(const Material *material, unsigned __int8 techType, TessPrimType primType)
{
	assertMsg(tess.indexCount == NULL, "tess.indexCount = %i", tess.indexCount);
	assertMsg(tess.vertexCount == NULL, "tess.vertexCount = %i", tess.vertexCount);
	assert(material);

	tess.primType = primType;
	tess.firstVertex = NULL;
	tess.lastVertex = NULL;

	gfxCmdBufState.material = material;
	gfxCmdBufState.techType = techType;
	gfxCmdBufState.prim.vertDeclType = VERTDECL_GENERIC;
	gfxCmdBufState.technique = Material_GetTechnique(material, techType);

	assert(gfxCmdBufState.technique);
}

/*
==============
RB_EndSurfaceEpilogue
==============
*/
void RB_EndSurfaceEpilogue()
{
	assert(tess.vertexCount == NULL);
	assert(tess.indexCount == NULL);
	tess.finishedFilling = NULL;
}

/*
==============
RB_DrawTessSurface
==============
*/
void RB_DrawTessSurface()
{
	assert(tess.indexCount);

	if (gfxCmdBufSourceState.viewportIsDirty)
	{
		GfxViewport viewport{};
		GfxViewport scissor{};
		R_GetViewport(&gfxCmdBufSourceState, &viewport);
		R_SetViewport(&gfxCmdBufState, &viewport);
		R_UpdateViewport(&gfxCmdBufSourceState, &viewport);

		if (R_GetScissor(&gfxCmdBufSourceState, &scissor))
		{
			R_SetScissor(&gfxCmdBufState, &scissor);
		}
		else
		{
			R_ClearScissor(&gfxCmdBufState);
		}
	}

	GfxDrawPrimArgs args{};
	args.vertexCount = tess.vertexCount;
	args.triCount = tess.indexCount / 3;

	assertMsg(
		gfxCmdBufState.prim.vertDeclType == VERTDECL_GENERIC,
		"gfxCmdBufState.prim.vertDeclType = %i",
		gfxCmdBufState.prim.vertDeclType);

	args.baseIndex = R_SetIndexDataIndexCount(&gfxCmdBufState, tess.indices, tess.indexCount);
	R_DrawTessTechnique(gfxCmdBufContext, &args);

	tess.indexCount = NULL;
	tess.vertexCount = NULL;
}

/*
==============
RB_EndTessSurface
==============
*/
void RB_EndTessSurface()
{
	assert(gfxCmdBufState.material);

	tess.finishedFilling = TRUE;
	RB_TrackDrawDynamic(&gfxCmdBufState.prim.frameStats, tess.indexCount, tess.vertexCount);
	RB_DrawTessSurface();
	RB_EndSurfaceEpilogue();
}

/*
==============
RB_TessOverflow
==============
*/
void RB_TessOverflow()
{
	RB_EndTessSurface();
	RB_BeginSurface(gfxCmdBufState.material, gfxCmdBufState.techType, tess.primType);
}

/*
==============
RB_SetTessTechnique
==============
*/
void RB_SetTessTechnique(const Material *material, unsigned __int8 techType)
{
	assert(material);

	if (gfxCmdBufState.material != material || gfxCmdBufState.techType != techType)
	{
		if (tess.indexCount)
		{
			RB_EndTessSurface();
		}

		RB_BeginSurface(material, techType, TESS_TRIANGLES);
	}
}

