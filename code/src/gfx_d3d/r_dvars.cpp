#include "types.h"

/*
==============
R_RegisterDvars
==============
*/
void R_RegisterDvars()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CheckDvarModified
==============
*/
bool R_CheckDvarModified(const dvar_t *dvar)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_GetDefaultNearClip
==============
*/
double R_GetDefaultNearClip()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_GetDefaultNearClip_DepthHack
==============
*/
double R_GetDefaultNearClip_DepthHack()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DvarBlock_SetFog
==============
*/
void DvarBlock_SetFog()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DvarBlock_SetWSI
==============
*/
void DvarBlock_SetWSI()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DvarBlock_SetVcBloom
==============
*/
void DvarBlock_SetVcBloom()
{
	if (gDvarDataReady == DBLOCK_READY_BLOOM)
	{
		Dvar_SetVec4FromVec4(vc_LIB, &dvar_buffer);
		Dvar_SetVec4FromVec4(vc_LIG, &vecin);
		Dvar_SetVec4FromVec4(vc_LIW, &stru_83D0E78);
		Dvar_SetVec4FromVec4(vc_LOB, &stru_83D0E88);
		Dvar_SetVec4FromVec4(vc_LOW, &stru_83D0E98);
		Dvar_SetVec4FromVec4(vc_RGBH, &stru_83D0EA8);
		Dvar_SetVec4FromVec4(vc_RGBL, &stru_83D0EB8);
		Dvar_SetVec4FromVec4(vc_YH, &stru_83D0EC8);
		Dvar_SetVec4FromVec4(vc_YL, &stru_83D0ED8);

		gDvarDataReady = DBLOCK_EMPTY;
	}
}

/*
==============
DvarBlock_SetVcColor
==============
*/
void DvarBlock_SetVcColor()
{
	if (gDvarDataReady == DBLOCK_READY_COLOR)
	{
		Dvar_SetVec4FromVec4(vc_RS, &dvar_buffer);
		Dvar_SetVec4FromVec4(vc_RE, &vecin);
		Dvar_SetVec4FromVec4(vc_SMR, &stru_83D0E78);
		Dvar_SetVec4FromVec4(vc_SMG, &stru_83D0E88);
		Dvar_SetVec4FromVec4(vc_SMB, &stru_83D0E98);
		Dvar_SetVec4FromVec4(vc_MMR, &stru_83D0EA8);
		Dvar_SetVec4FromVec4(vc_MMG, &stru_83D0EB8);
		Dvar_SetVec4FromVec4(vc_MMB, &stru_83D0EC8);
		Dvar_SetVec4FromVec4(vc_HMR, &stru_83D0ED8);
		Dvar_SetVec4FromVec4(vc_HMG, &stru_83D0EE8);
		Dvar_SetVec4FromVec4(vc_HMB, &stru_83D0EF8);
		Dvar_SetVec4FromVec4(vc_FGM, &stru_83D0F08);
		Dvar_SetVec4FromVec4(vc_FSM, &stru_83D0F18);
		Dvar_SetVec4FromVec4(vc_FBM, &stru_83D0F28);

		gDvarDataReady = DBLOCK_EMPTY;
	}
}

