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
	float aspect,
	bool splitScreen)
{
#ifdef 0
	float	adjustedRealWidth;

	memset((unsigned __int8 *)scrPlace, 0xB0u, sizeof(ScreenPlacement));

	scrPlace->realViewportBase[0] = *(float *)&0.0;
	scrPlace->realViewportBase[1] = *(float *)&0.0;
	scrPlace->realViewportSize[0] = viewportWidth;
	scrPlace->realViewportSize[1] = viewportHeight;
	adjustedRealWidth = (float)(1.3333334 * viewportHeight) / cls.vidConfig.aspectRatioScenePixel;

  if ( adjustedRealWidth > viewportWidth )
    adjustedRealWidth = viewportWidth;
  ScrPlace_CalcSafeAreaOffsets(
    viewportX,
    viewportY,
    viewportWidth,
    viewportHeight,
    viewportWidth / adjustedRealWidth,
    viewportHeight / viewportHeight,
    1.0,
    1.0,
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
    1.0,
    1.0,
    scrPlace->realTweakableMin,
    scrPlace->realTweakableMax,
    scrPlace->virtualTweakableMin,
    scrPlace->virtualTweakableMax);
  scrPlace->scaleVirtualToReal[0] = adjustedRealWidth / 640.0;
  scrPlace->scaleVirtualToReal[1] = viewportHeight / 480.0;
  scrPlace->scaleVirtualToFull[0] = viewportWidth / 640.0;
  scrPlace->scaleVirtualToFull[1] = viewportHeight / 480.0;
  scrPlace->scaleRealToVirtual[0] = 640.0 / adjustedRealWidth;
  scrPlace->scaleRealToVirtual[1] = 480.0 / viewportHeight;
  scrPlace->subScreen[0] = (viewportWidth - adjustedRealWidth) * 0.5;
  scrPlace->subScreen[1] = (viewportHeight - viewportHeight) * 0.5;
#endif
	UNIMPLEMENTED (__FUNCTION__);
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
double ScrPlace_ApplyX(const ScreenPlacement *scrPlace, float x, int horzAlign)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ScrPlace_ApplyY
==============
*/
double ScrPlace_ApplyY(const ScreenPlacement *scrPlace, float y, int vertAlign)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ScrPlace_ApplyW
==============
*/
double ScrPlace_ApplyW(const ScreenPlacement *scrPlace, float w, int horzAlign)
{
	switch ( horzAlign )
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
		return (scrPlace->scaleVirtualToReal[0] * scrPlace->hudSplitscreenScale * w);
	case 4:
		return (scrPlace->scaleVirtualToFull[0] * scrPlace->hudSplitscreenScale * w);
	case 5:
		return scrPlace->hudSplitscreenScale * w;
	default:
		return (scrPlace->scaleVirtualToReal[0] * scrPlace->hudSplitscreenScale * w);
	}
}

/*
==============
ScrPlace_ApplyH
==============
*/
double ScrPlace_ApplyH(const ScreenPlacement *scrPlace, float h, int vertAlign)
{
	switch ( vertAlign )
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
		return (scrPlace->scaleVirtualToReal[1] * scrPlace->hudSplitscreenScale * h);
	case 4:
		return (scrPlace->scaleVirtualToFull[1] * v3scrPlace->hudSplitscreenScale * h);
	case 5:
		return scrPlace->hudSplitscreenScale * h;
	default:
		return (scrPlace->scaleVirtualToReal[1] * scrPlace->hudSplitscreenScale * h);
	}
}

/*
==============
ApplySplitscreenScaling
==============
*/
void ApplySplitscreenScaling( float *x, float *y, float *w, float *h, float hudSplitscreenScale )
{
	if ( cg_hudSplitscreenOffsetsUseScale->current.enabled ) {
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
void	ScrPlace_ApplyRect (
	const ScreenPlacement *scrPlace,
	float *x,
	float *y,
	float *w,
	float *h,
	int horzAlign,
	int vertAlign)
{
	UNIMPLEMENTED (__FUNCTION__);
}


/*
==============
ScrPlace_SetLegacySplitscreenScaling
==============
*/
void ScrPlace_SetLegacySplitscreenScaling( void) {
	if ( R_Is3DOn( ) ) {
		cg_hudSplitscreenScale = cg_hudLegacySplitscreenScale->current.value;
	} else {
		cg_hudSplitscreenScale = 1.0f;
	}
}



/*
==============
ScrPlace_SetNormalSplitscreenScaling
==============
*/
void ScrPlace_SetNormalSplitscreenScaling (void) {
	cg_hudSplitscreenScale = 1.0f;
}


/*
==============
ScrPlace_Init
==============
*/
void ScrPlace_Init (void) {
	safeArea_horizontal = _Dvar_RegisterFloat ("safeArea_horizontal",
							0.85,
							0.0,
							1.0,
							DVAR_NOFLAG,
							"Horizontal safe area as a fraction of the screen width");
	safeArea_vertical = _Dvar_RegisterFloat (
							"safeArea_vertical",
							0.85,
							0.0,
							1.0,
							DVAR_NOFLAG,
							"Vertical safe area as a fraction of the screen height");
	ui_safearea = _Dvar_RegisterBool ("ui_safearea", 0, DVAR_NOFLAG, "");

	cg_hudSplitscreenScale = 1.0;

	if ( R_Is3DOn () && R_IsLowRes3D() ) {
		cg_hudLegacyStereo3DScale = _Dvar_RegisterFloat (
			"cg_hudLegacyStereo3DScale",
			1.45,
			1.0,
			3.4028235e38,
			DVAR_NOFLAG,
			"Screen scale for hud elements in stereo 3D");
		cg_hudStereo3DScale = 1.0;
	}
	else
	{
		cg_hudLegacyStereo3DScale = _Dvar_RegisterFloat (
			"cg_hudLegacyStereo3DScale",
			1.0,
			1.0,
			3.4028235e38,
			DVAR_NOFLAG,
			"Screen scale for hud elements in stereo 3D");
		cg_hudStereo3DScale = 1.0;
	}
}

///////