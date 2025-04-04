#include "types.h"

/*
==============
CG_GetPicWidth
==============
*/
double CG_GetPicWidth(Material *mat)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_DrawRotatedPicPhysicalW
==============
*/
void CG_DrawRotatedPicPhysicalW(const ScreenPlacement *scrPlace, float x, float y, float w, float width, float height, float angle, const vec4_t *color, Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_DrawRotatedPicPhysical
==============
*/
void CG_DrawRotatedPicPhysical(const ScreenPlacement *scrPlace, float x, float y, float width, float height, float angle, const vec4_t *color, Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_DrawRotatedPicW
==============
*/
void CG_DrawRotatedPicW(const ScreenPlacement *scrPlace, float x, float y, float w, float width, float height, int horzAlign, int vertAlign, float angle, const vec4_t *color, Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_DrawRotatedPic
==============
*/
void CG_DrawRotatedPic(const ScreenPlacement *scrPlace, float x, float y, float width, float height, int horzAlign, int vertAlign, float angle, const vec4_t *color, Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_DrawRotatedQuadPic
==============
*/
void CG_DrawRotatedQuadPic(const ScreenPlacement *scrPlace, float x, float y, const vec2_t *verts, float angle, const vec4_t *color, Material *material)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_DrawStringExt
==============
*/
void CG_DrawStringExt(const ScreenPlacement *scrPlace, float x, float y, const char *string, const vec4_t *setColor, int forceColor, int shadow, float charHeight)
{
	UNIMPLEMENTED(__FUNCTION__);
}

#define CG_ALIGN_X 3
#define CG_ALIGN_Y 12

#define CG_ALIGN_LEFT 1
#define CG_ALIGN_RIGHT 2
#define CG_ALIGN_CENTER 3
#define CG_ALIGN_TOP 4
#define CG_ALIGN_BOTTOM 8
#define CG_ALIGN_MIDDLE 12

/*
==============
CG_DrawDevString
==============
*/
int CG_DrawDevString(
	LocalClientNum_t localClientNum,
	const ScreenPlacement *scrPlace,
	float x,
	float y,
	float xScale,
	float yScale,
	const char *string,
	const float *color,
	int align,
	Font_s *font)
{
	assert((align & CG_ALIGN_X) == CG_ALIGN_LEFT || (align & CG_ALIGN_X) == CG_ALIGN_RIGHT || (align & CG_ALIGN_X) == CG_ALIGN_CENTER);

	if ((align & 3) == 2)
	{
		x = x - (R_TextWidth(localClientNum, string, 0, font) * xScale);
	}
	else if ((align & 3) == 3)
	{
		x = x - ((R_TextWidth(localClientNum, string, 0, font) * xScale) * 0.5f);
	}

	assert((align & CG_ALIGN_Y) == CG_ALIGN_TOP || (align & CG_ALIGN_Y) == CG_ALIGN_BOTTOM || (align & CG_ALIGN_Y) == CG_ALIGN_MIDDLE);

	int step = R_TextHeight(font);
	if ((align & 12) == 4)
	{
		y = y + (step * yScale);
	}
	else if ((align & 12) == 12)
	{
		y = ((step * yScale) * 0.5f) + y;
	}

	CL_DrawText(scrPlace, string, 0x7FFFFFFF, font, x, y, 1, 1, xScale, yScale, color, 0);
	return step;
}

/*
==============
CG_DrawSmallDevStringColor
==============
*/
int CG_DrawSmallDevStringColor(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, float x, float y, const char *s, const vec4_t *color, int align)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_FadeAlpha
==============
*/
double CG_FadeAlpha(int timeNow, int startMsec, int totalMsec, int fadeMsec)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_FadeColor
==============
*/
vec4_t *CG_FadeColor(int timeNow, int startMsec, int totalMsec, int fadeMsec)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CG_MiniMapChanged
==============
*/
void CG_MiniMapChanged(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_NorthDirectionChanged
==============
*/
void CG_NorthDirectionChanged(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_RelativeTeamColor
==============
*/
void CG_RelativeTeamColor(ClientNum_t clientNum, vec4_t *color, LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_DrawBigDevString
==============
*/
int CG_DrawBigDevString(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, float x, float y, const char *s, float alpha, int align)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

