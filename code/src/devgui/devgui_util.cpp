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
	assert(w);
	assert(h);

	float unpackedColor[4];
	Byte4UnpackRgba(color, unpackedColor);

	R_AddCmdDrawStretchPic(
		(float)x,
		(float)y,
		(float)w,
		(float)h,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		unpackedColor,
		cls.whiteMaterial);
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

#define DEVGUI_BEVEL_SIZE 4

/*
==============
DevGui_DrawBevelBox
==============
*/
void DevGui_DrawBevelBox(int x, int y, int w, int h, float shade, const unsigned __int8 *color)
{
	assert(w >= (DEVGUI_BEVEL_SIZE * 2.0f));
	assert(h >= (DEVGUI_BEVEL_SIZE * 2.0f));

	float unpackedColor[4];
	Byte4UnpackRgba(color, unpackedColor);
	DevGui_DrawBox(x, y, w, h, color);

	auto ApplyShade = [&](float &component)
	{
		component = std::clamp(shade * component, 0.0f, 1.0f);
	};

	ApplyShade(unpackedColor[0]);
	ApplyShade(unpackedColor[1]);
	ApplyShade(unpackedColor[2]);

	int vtxs[4][2];

	//left bevel
	vtxs[0][0] = x;
	vtxs[0][1] = y;
	vtxs[1][0] = x + DEVGUI_BEVEL_SIZE;
	vtxs[1][1] = y + DEVGUI_BEVEL_SIZE;
	vtxs[2][0] = x + DEVGUI_BEVEL_SIZE;
	vtxs[2][1] = y + h - DEVGUI_BEVEL_SIZE;
	vtxs[3][0] = x;
	vtxs[3][1] = y + h;
	DevGui_DrawQuad(vtxs, unpackedColor);

	ApplyShade(unpackedColor[0]);
	ApplyShade(unpackedColor[1]);
	ApplyShade(unpackedColor[2]);

	//top bevel
	vtxs[0][0] = x;
	vtxs[0][1] = y;
	vtxs[1][0] = x + w;
	vtxs[1][1] = y;
	vtxs[2][0] = x + w - DEVGUI_BEVEL_SIZE;
	vtxs[2][1] = y + DEVGUI_BEVEL_SIZE;
	vtxs[3][0] = x + DEVGUI_BEVEL_SIZE;
	vtxs[3][1] = y + DEVGUI_BEVEL_SIZE;
	DevGui_DrawQuad(vtxs, unpackedColor);

	ApplyShade(unpackedColor[0]);
	ApplyShade(unpackedColor[1]);
	ApplyShade(unpackedColor[2]);

	//bottom bevel
	vtxs[0][0] = x;
	vtxs[0][1] = y + h;
	vtxs[1][0] = x + DEVGUI_BEVEL_SIZE;
	vtxs[1][1] = y + h - DEVGUI_BEVEL_SIZE;
	vtxs[2][0] = x + w - DEVGUI_BEVEL_SIZE;
	vtxs[2][1] = y + h - DEVGUI_BEVEL_SIZE;
	vtxs[3][0] = x + w;
	vtxs[3][1] = y + h;
	DevGui_DrawQuad(vtxs, unpackedColor);

	ApplyShade(unpackedColor[0]);
	ApplyShade(unpackedColor[1]);
	ApplyShade(unpackedColor[2]);

	//right bevel
	vtxs[0][0] = x + w;
	vtxs[0][1] = y;
	vtxs[1][0] = x + w;
	vtxs[1][1] = y + h;
	vtxs[2][0] = x + w - DEVGUI_BEVEL_SIZE;
	vtxs[2][1] = y + h - DEVGUI_BEVEL_SIZE;
	vtxs[3][0] = x + w - DEVGUI_BEVEL_SIZE;
	vtxs[3][1] = y + DEVGUI_BEVEL_SIZE;
	DevGui_DrawQuad(vtxs, unpackedColor);
}

/*
==============
DevGui_DrawLine
==============
*/
void DevGui_DrawLine(float *start, float *end, int width, const unsigned __int8 *color)
{
	float minX = fminf(*start, *end);
	float minY = fminf(start[1], end[1]);
	float maxX = fmaxf(*start, *end);
	float maxY = fmaxf(start[1], end[1]);

	float deltaX = *end - *start;
	float deltaY = end[1] - start[1];
	float length = Vec2Length(&deltaX);
	Vec3Normalize(&deltaX);

	float angle = atan2f(deltaY, deltaX) * (180.0f / M_PI);
	if (start[1] > end[1])
	{
		angle = -angle;
	}

	while (angle < 0.0f)
	{
		angle += 360.0f;
	}

	float centerX = (minX + maxX) / 2.0f;
	float centerY = (minY + maxY) / 2.0f;

	float unpackedColor[4];
	Byte4UnpackRgba(color, unpackedColor);

	R_AddCmdDrawStretchPicRotateXY(
		centerX - (length / 2.0f),
		centerY - (width / 2.0f),
		length,
		(float)width,
		0.0f, 0.0f, 1.0f, 1.0f,
		angle,
		unpackedColor,
		cls.whiteMaterial);
}

/*
==============
DevGui_DrawFont
==============
*/
void DevGui_DrawFont(int x, int y, const unsigned __int8 *color, const char *text, float xScale, float yScale)
{
	assert(text);

	float unpackedColor[4];
	Byte4UnpackRgba(color, unpackedColor);

	float textPosY = (float)y + DevGui_GetFontHeight();

	R_AddCmdDrawText(
		text,
		INT_MAX,
		cls.consoleFont,
		(float)x,
		textPosY,
		xScale,
		yScale,
		0.0f,
		unpackedColor,
		0);
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

/*
==============
DevGui_DrawQuad
==============
*/
void DevGui_DrawQuad(const int (*vtxs)[2], const float *color)
{
	float xy[4][2];

	for (int i = 0; i < 4; ++i)
	{
		xy[i][0] = (float)vtxs[i][0];
		xy[i][1] = (float)vtxs[i][1];
	}

	R_AddCmdDrawQuadPic(xy, color, cls.whiteMaterial);
}

