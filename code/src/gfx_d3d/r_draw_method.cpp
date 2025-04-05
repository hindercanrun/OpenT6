#include "types.h"

/*
==============
R_SetDefaultLitTechTypes
==============
*/
void R_SetDefaultLitTechTypes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_InitDrawMethod
==============
*/
void R_InitDrawMethod()
{
	if (r_fullbright->current.enabled)
	{
		gfxDrawMethod.drawScene = GFX_DRAW_SCENE_FULLBRIGHT;
		gfxDrawMethod.baseTechType = 514;

		memset(gfxDrawMethod.litTechType[0], 2, sizeof(gfxDrawMethod));
	}
	else if (r_debugShader->current.integer >= 1)
	{
		gfxDrawMethod.drawScene = GFX_DRAW_SCENE_DEBUGSHADER;
		gfxDrawMethod.baseTechType = 8738;

		memset(gfxDrawMethod.litTechType[0], 34, sizeof(gfxDrawMethod));
	}
	else if (r_debugPerformance->current.integer >= 1)
	{
		gfxDrawMethod.drawScene = GFX_DRAW_SCENE_DEBUGSHADER;
		gfxDrawMethod.baseTechType = 772;

		R_SetDefaultLitTechTypes();
	}
	else
	{
		gfxDrawMethod.baseTechType = 772;
		gfxDrawMethod.drawScene = GFX_DRAW_SCENE_STANDARD;

		R_SetDefaultLitTechTypes();
	}
}

/*
==============
R_UpdateDrawMethod
==============
*/
void R_UpdateDrawMethod(GfxBackEndData *data)
{
	UNIMPLEMENTED(__FUNCTION__);
}

