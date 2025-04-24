// screen_placement.cpp


#include "types.h"
#include "screen_placement.h"
#include "client_public.h"

float	cg_hudSplitscreenScale;
float	cg_hudStereo3DScale;

typedef struct {
	vec2_t scaleVirtualToReal;
	vec2_t scaleVirtualToFull;

	vec2_t scaleRealToVirtual;

	vec2_t virtualViewableMin;
	vec2_t virtualViewableMax;
	vec2_t virtualTweakableMin;
	vec2_t virtualTweakableMax;

	vec2_t realViewportBase;
	vec2_t realViewportSize;
	vec2_t realViewportMid;

	vec2_t realViewableMin;
	vec2_t realViewableMax;

	vec2_t realTweakableMin;
	vec2_t realTweakableMax;

	vec2_t subScreen;

	float hudSplitscreenScale;
}  ScreenPlacement_t;

extern	 ScreenPlacement_t			scrPlaceView[1];


const	dvar_t		*cg_hudSplitscreenOffsetsUseScale;
const	dvar_t		*cg_hudLegacySplitscreenScale;
const	dvar_t		*safeArea_horizontal;
const	dvar_t		*safeArea_vertical;
const	dvar_t		*ui_safearea;
const	dvar_t		*cg_hudLegacyStereo3DScale;

/*
==============
ScrPlace_GetView
==============
*/
ScreenPlacement *ScrPlace_GetView( const LocalClientNum_t localClientNum ) {
	return &scrPlaceView[Com_LocalClient_GetUIContextIndex(localClientNum)];
}

/*
==============
ScrPlace_GetViewWritable
==============
*/
ScreenPlacement *ScrPlace_GetViewWritable(const LocalClientNum_t localClientNum)
{
	return &scrPlaceView[Com_LocalClient_GetUIContextIndex(localClientNum)];
}

/*
==============
ScrPlace_GetViewUIContext
==============
*/
ScreenPlacement *ScrPlace_GetViewUIContext(const UIContextIndex_t contextIndex)
{
	return &scrPlaceView[contextIndex];
}

/*
==============
ScrPlace_GetViewUIContextWritable
==============
*/
ScreenPlacement *ScrPlace_GetViewUIContextWritable(const UIContextIndex_t contextIndex)
{
	return &scrPlaceView[contextIndex];
}

/*
==============
ScrPlace_HiResGetScaleY
==============
*/
double ScrPlace_HiResGetScaleY()
{
	return 1.0;
}

/*
==============
ScrPlace_CalcSafeAreaOffsets
==============
*/
vec2_t *ScrPlace_CalcSafeAreaOffsets(
	float viewportY,
	float viewportWidth,
	float horzAspectScale,
	float vertAspectScale,
	float safeAreaRatioHorz,
	float safeAreaRatioVert,
	float virtualViewableMin,
	float virtualViewableMax/*,
	vec2_t *a11,
	vec2_t *a12*/)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
ScrPlace_SetupFloatViewport
==============
*/
void ScrPlace_SetupFloatViewport(
	ScreenPlacement *scrPlace,
	float viewportX,
	float viewportY,
	float viewportWidth,
	float viewportHeight,
	[[maybe_unused]] float aspect,
	bool splitScreen)
{
	memset(scrPlace, sizeof(scrPlace), sizeof(ScreenPlacement));
	scrPlace->realViewportBase[0] = 0.0f;
	scrPlace->realViewportBase[1] = 0.0f;
	scrPlace->realViewportSize[0] = viewportWidth;
	scrPlace->realViewportSize[1] = viewportHeight;

	float adjustedRealWidth = (1.3333334f * viewportHeight) / cls.vidConfig.aspectRatioScenePixel;
	if (adjustedRealWidth > viewportWidth)
	{
		adjustedRealWidth = viewportWidth;
	}

	ScrPlace_CalcSafeAreaOffsets(
		viewportX,
		viewportY,
		viewportWidth,
		viewportHeight,
		viewportWidth / adjustedRealWidth,
		viewportHeight / viewportHeight,
		1.0f,
		1.0f,
		scrPlace->realViewableMin,
		scrPlace->realViewableMax,
		scrPlace->virtualViewableMin,
		scrPlace->virtualViewableMax);
	ScrPlace_CalcSafeAreaOffsets(
		viewportX,
		viewportY,
		viewportWidth,
		viewportHeight,
		viewportWidth / adjustedRealWidth,
		viewportHeight / viewportHeight,
		1.0f,
		1.0f,
		scrPlace->realTweakableMin,
		scrPlace->realTweakableMax,
		scrPlace->virtualTweakableMin,
		scrPlace->virtualTweakableMax);

	scrPlace->scaleVirtualToReal[0] = adjustedRealWidth / 640.0f;
	scrPlace->scaleVirtualToReal[1] = viewportHeight / 480.0f;
	scrPlace->scaleVirtualToFull[0] = viewportWidth / 640.0f;
	scrPlace->scaleVirtualToFull[1] = viewportHeight / 480.0f;
	scrPlace->scaleRealToVirtual[0] = 640.0f / adjustedRealWidth;
	scrPlace->scaleRealToVirtual[1] = 480.0f / viewportHeight;
	scrPlace->subScreen[0] = (viewportWidth - adjustedRealWidth) * 0.5f;
	scrPlace->subScreen[1] = (viewportHeight - viewportHeight) * 0.5f;

	if (splitScreen)
	{
		scrPlace->hudSplitscreenScale = cg_hudSplitscreenScale;
	}
	else
	{
		scrPlace->hudSplitscreenScale = 1.0f;
	}
}

/*
==============
ScrPlace_SetupViewport
==============
*/
void ScrPlace_SetupViewport (
	ScreenPlacement *scrPlace,
	int viewportX,
	int viewportY,
	int viewportWidth,
	int viewportHeight,
	float aspect,
	bool splitScreen)
{
	ScrPlace_SetupFloatViewport( scrPlace, viewportX, viewportY, viewportWidth, viewportHeight, aspect, splitScreen );

}


/*
==============
ScrPlace_SetupUnsafeViewport
==============
*/
void ScrPlace_SetupUnsafeViewport (
	ScreenPlacement *scrPlace,
	int viewportX,
	int viewportY,
	int viewportWidth,
	int viewportHeight,
	float aspect,
	bool splitScreen)
{
	Dvar_SetFloat( safeArea_horizontal,	1.0 );
	Dvar_SetFloat( safeArea_vertical,	1.0 );

	ScrPlace_SetupFloatViewport ( scrPlace, viewportX, viewportY, viewportWidth, viewportHeight, aspect, splitScreen );


	Dvar_SetFloat( safeArea_horizontal, safeArea_horizontal->current.value );
	Dvar_SetFloat( safeArea_vertical,	safeArea_vertical->current.value );
}

/*
==============
ScrPlace_ApplyX
==============
*/
float ScrPlace_ApplyX(const ScreenPlacement *scrPlace, float x, int horzAlign)
{
	if (cg_hudSplitscreenOffsetsUseScale->current.enabled)
	{
		x = (cg_hudSplitscreenScale * x);
	}

	float scale = (cg_hudStereo3DScale * x);
	float result;

	switch (horzAlign)
	{
	case 1:
		result = (x * scrPlace->scaleVirtualToReal[0]) + scrPlace->realViewableMin[0];
		break;
	case 2:
		result = ((x * scrPlace->scaleVirtualToReal[0]) + (scrPlace->realViewportSize[0] * scale)) + scrPlace->realViewportBase[0];
		break;
	case 3:
		result = (x * scrPlace->scaleVirtualToReal[0]) + scrPlace->realViewableMax[0];
		break;
	case 4:
		result = (x * scrPlace->scaleVirtualToFull[0]) + scrPlace->realViewportBase[0];
		break;
	case 5:
		result = x;
		break;
	case 6:
		result = x * scrPlace->scaleRealToVirtual[0];
		break;
	case 7:
		result = (x * scrPlace->scaleVirtualToReal[0]) + ((scrPlace->realViewableMin[0] + scrPlace->realViewableMax[0]) * scale);
		break;
	case 8:
		result = (x * scrPlace->scaleVirtualToReal[0]) + scrPlace->realTweakableMin[0];
		break;
	case 9:
		result = (x * scrPlace->scaleVirtualToReal[0]) + ((scrPlace->realTweakableMin[0] + scrPlace->realTweakableMax[0]) * scale);
		break;
	case 10:
		result = (x * scrPlace->scaleVirtualToReal[0]) + scrPlace->realTweakableMax[0];
		break;
	default:
		assertMsg((horzAlign == NULL), "(horzAlign) = %i", horzAlign);
		result = (x * scrPlace->scaleVirtualToReal[0]) + scrPlace->subScreen[0];
		break;
	}

#ifn defined(DEDICATED)
	if (rg.renderHiResShot)
	{
		return ((rg.hiResShotTiles * result) - cls.vidConfig.displayWidth * rg.hiResShotRow);
	}
#endif

	return result;
}

/*
==============
ScrPlace_ApplyY
==============
*/
float ScrPlace_ApplyY(const ScreenPlacement *scrPlace, float y, int vertAlign)
{
	if (cg_hudSplitscreenOffsetsUseScale->current.enabled)
	{
		y = (cg_hudSplitscreenScale * y);
	}

	float scale = (cg_hudStereo3DScale * y);
	float result;

	switch (vertAlign)
	{
	case 1:
		result = (y * scrPlace->scaleVirtualToReal[1]) + scrPlace->realViewableMin[1];
		break;
	case 2:
		result = ((y * scrPlace->scaleVirtualToReal[1]) + (scrPlace->realViewportSize[1] * scale)) + scrPlace->realViewportBase[1];
		break;
	case 3:
		result = (y * scrPlace->scaleVirtualToReal[1]) + scrPlace->realViewableMax[1];
		break;
	case 4:
		result = (y * scrPlace->scaleVirtualToFull[1]) + scrPlace->realViewportBase[1];
		break;
	case 5:
		result = y;
		break;
	case 6:
		result = y * scrPlace->scaleRealToVirtual[1];
		break;
	case 7:
		result = (y * scrPlace->scaleVirtualToReal[1]) + ((scrPlace->realViewableMin[1] + scrPlace->realViewableMax[1]) * scale);
		break;
	case 8:
		result = (y * scrPlace->scaleVirtualToReal[1]) + scrPlace->realTweakableMin[1];
		break;
	case 9:
		result = (y * scrPlace->scaleVirtualToReal[1]) + ((scrPlace->realTweakableMin[1] + scrPlace->realTweakableMax[1]) * scale);
		break;
	case 10:
		result = (y * scrPlace->scaleVirtualToReal[1]) + scrPlace->realTweakableMax[1];
		break;
	default:
		assertMsg((vertAlign == NULL), "(vertAlign) = %i", vertAlign);
		result = (y * scrPlace->scaleVirtualToReal[1]) + scrPlace->subScreen[1];
		break;
	}

#ifn defined(DEDICATED)
	if (rg.renderHiResShot)
	{
		return ((rg.hiResShotTiles * result) - cls.vidConfig.displayHeight * rg.hiResShotCol);
	}
#endif

	return result;
}

/*
==============
ScrPlace_ApplyW
==============
*/
float ScrPlace_ApplyW(const ScreenPlacement *scrPlace, float w, int horzAlign)
{
	switch (horzAlign)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		w = w * scrPlace->scaleVirtualToReal[0];
		break;
	case 4:
		w = w * scrPlace->scaleVirtualToFull[0];
		break;
	case 5:
		break;
	default:
		assertMsg(false, "invalid horizontal alignment case");
		break;
	}

	if (rg.renderHiResShot)
	{
		return (rg.hiResShotTiles * w);
	}

	return w;
}

/*
==============
ScrPlace_ApplyH
==============
*/
float ScrPlace_ApplyH(const ScreenPlacement *scrPlace, float h, int vertAlign)
{
	switch (vertAlign)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		h = h * scrPlace->scaleVirtualToReal[1];
		break;
	case 4:
		h = h * scrPlace->scaleVirtualToFull[1];
		break;
	case 5:
		return h;
	default:
		assertMsg(false, "invalid vertical alignment case");
		break;
	}

	return h;
}

/*
==============
ApplySplitscreenScaling
==============
*/
void ApplySplitscreenScaling(float *x, float *y, float *w, float *h, float hudSplitscreenScale)
{
	if (cg_hudSplitscreenOffsetsUseScale->current.enabled)
	{
		*x = *x * hudSplitscreenScale;
		*y = *y * hudSplitscreenScale;
	}

	*w = *w * hudSplitscreenScale;
	*h = *h * hudSplitscreenScale;
}

/*
==============
ScrPlace_ApplyRect
==============
*/
void ScrPlace_ApplyRect(
	const ScreenPlacement *scrPlace,
	float *x,
	float *y,
	float *w,
	float *h,
	int horzAlign,
	int vertAlign)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ScrPlace_SetLegacySplitscreenScaling
==============
*/
void ScrPlace_SetLegacySplitscreenScaling()
{
	if (R_Is3DOn())
	{
		cg_hudSplitscreenScale = cg_hudLegacySplitscreenScale->current.value;
	}
	else
	{
		cg_hudSplitscreenScale = 1.0f;
	}
}

/*
==============
ScrPlace_SetNormalSplitscreenScaling
==============
*/
void ScrPlace_SetNormalSplitscreenScaling()
{
	cg_hudSplitscreenScale = 1.0f;
}

/*
==============
ScrPlace_Init
==============
*/
void ScrPlace_Init()
{
	safeArea_horizontal = Dvar_RegisterFloat(
		"safeArea_horizontal",
		0.85f,
		0.0f,
		1.0f,
		DVAR_NOFLAG,
		"Horizontal safe area as a fraction of the screen width");
	safeArea_vertical = Dvar_RegisterFloat(
		"safeArea_vertical",
		0.85f,
		0.0f,
		1.0f,
		DVAR_NOFLAG,
		"Vertical safe area as a fraction of the screen height");
	ui_safearea = Dvar_RegisterBool(
		"ui_safearea",
		false,
		DVAR_NOFLAG,
		nullptr);

	cg_hudSplitscreenScale = 1.0f;

	if (R_Is3DOn() && R_IsLowRes3D())
	{
		cg_hudLegacyStereo3DScale = Dvar_RegisterFloat(
			"cg_hudLegacyStereo3DScale",
			1.45f,
			1.0f,
			3.4028235e38f,
			DVAR_NOFLAG,
			"Screen scale for hud elements in stereo 3D");
		cg_hudStereo3DScale = 1.0f;
	}
	else
	{
		cg_hudLegacyStereo3DScale = Dvar_RegisterFloat(
			"cg_hudLegacyStereo3DScale",
			1.0f,
			1.0f,
			3.4028235e38f,
			DVAR_NOFLAG,
			"Screen scale for hud elements in stereo 3D");
		cg_hudStereo3DScale = 1.0f;
	}
}
