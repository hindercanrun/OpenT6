#include "types.h"

/*
==============
DevGui_GetScreenWidth
==============
*/
unsigned int DevGui_GetScreenWidth()
{
	return cls.vidConfig.displayWidth;
}

/*
==============
DevGui_GetScreenHeight
==============
*/
unsigned int DevGui_GetScreenHeight()
{
	return cls.vidConfig.displayHeight;
}

/*
==============
DevGui_DrawBox
==============
*/
void DevGui_DrawBox(int x, int y, int w, int h, const unsigned __int8 *color)
{
	float unpackedColor[4];

	if (!w)
	{
		assert("h");
	}
	if (!h)
	{
		assert("h");
	}

	Byte4UnpackRgba(color, unpackedColor);
	R_AddCmdDrawStretchPic((float)x, (float)y, (float)w, (float)h, 0.0, 0.0, 0.0, 0.0, unpackedColor, cls.whiteMaterial);
}

/*
==============
DevGui_DrawBoxCentered
==============
*/
void DevGui_DrawBoxCentered(int centerX, int centerY, int w, int h, const unsigned __int8 *color)
{
  DevGui_DrawBox(centerX - w / 2, centerY - h / 2, w, h, color);
}

/*
==============
DevGui_DrawBevelBox
==============
*/
void DevGui_DrawBevelBox(int x, int y, int w, int h)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawQuad
==============
*/
void DevGui_DrawQuad(const int (*vtxs)[2], const float *color)
{
	float xy[4][2];

	xy[0][0] = (float)(*vtxs)[0];
	xy[0][1] = (float)(*vtxs)[1];
	xy[1][0] = (float)(*vtxs)[2];
	xy[1][1] = (float)(*vtxs)[3];
	xy[2][0] = (float)(*vtxs)[4];
	xy[2][1] = (float)(*vtxs)[5];
	xy[3][0] = (float)(*vtxs)[6];
	xy[3][1] = (float)(*vtxs)[7];

	R_AddCmdDrawQuadPic(xy, color, cls.whiteMaterial);
}

/*
==============
DevGui_DrawLine
==============
*/
void DevGui_DrawLine(vec2_t *start, vec2_t *end, int width, const unsigned __int8 *color)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawFont
==============
*/
void DevGui_DrawFont(int x, int y, const unsigned __int8 *color, const char *text, float xScale, float yScale)
{
	float unpackedColor[4];

	if (!text)
	{
		assert("text");
	}

	if (text)
	{
		Byte4UnpackRgba(color, unpackedColor);
		R_AddCmdDrawText(text, 0x7FFFFFFF, cls.consoleFont, x, (y + DevGui_GetFontHeight()), xScale, yScale, 0.0, unpackedColor, 0);
	}
}

/*
==============
DevGui_GetFontWidth
==============
*/
int DevGui_GetFontWidth(const char *text)
{
	return R_TextWidth(text, 0, cls.consoleFont);
}

/*
==============
DevGui_GetFontHeight
==============
*/
int DevGui_GetFontHeight()
{
	return R_TextHeight(cls.consoleFont);
}
