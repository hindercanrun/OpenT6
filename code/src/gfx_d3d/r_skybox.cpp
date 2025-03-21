#include "types.h"

XModel *g_skyboxModel = nullptr;
unsigned __int16 myhandle;

/*
==============
R_RegisterSkyboxModel
==============
*/
void R_RegisterSkyboxModel(const char *xModelName)
{
	g_skyboxModel = R_RegisterModel(xModelName);
}

/*
==============
R_ClearSkyboxModel
==============
*/
void R_ClearSkyboxModel()
{
	g_skyboxModel = nullptr;
}

/*
==============
R_AddSkyboxModel
==============
*/
void R_AddSkyboxModel(const float *eyePos)
{
	if (!g_skyboxModel)
	{
		return;
	}

	static GfxScaledPlacement placement{};
	placement.scale = 1.0;
	placement.base.origin[0] = *eyePos;
	placement.base.origin[1] = eyePos[1];
	placement.base.origin[2] = eyePos[2];
	placement.base.quat[3] = 1.0;
	memset(&placement, 0, 12);

	R_FilterXModelIntoScene(g_skyboxModel, &placement, 0, &myhandle, 0.0);
}

/*
==============
R_MapGetSkyboxModel
==============
*/
XModel *R_MapGetSkyboxModel()
{
	return g_skyboxModel;
}

