#include "types.h"

/*
==============
CG_RegisterVisionSetsDvars
==============
*/
void CG_RegisterVisionSetsDvars()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
RawBufferOpen
==============
*/
const char *RawBufferOpen(const char *path, const char *backupPath)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
ApplyTokenToField
==============
*/
bool ApplyTokenToField(int fieldNum, const char *token, visionSetVars_t *settings)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LoadVisionSettingsFromBuffer
==============
*/
bool LoadVisionSettingsFromBuffer(const char *buffer, const char *filename, visionSetVars_t *settings)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LoadVisionFile
==============
*/
bool LoadVisionFile(const char *name, visionSetVars_t *resultSettings)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
GetVisionSet
==============
*/
bool GetVisionSet(LocalClientNum_t localClientNum, const char *name, visionSetVars_t *resultSettings)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LerpBool
==============
*/
bool LerpBool(bool from, bool to, float fraction, visionSetLerpStyle_t style)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LerpInteger
==============
*/
int LerpInteger(int from, int to, const float fraction, visionSetLerpStyle_t style)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LerpStepFloat
==============
*/
float LerpStepFloat(float from, float to, const float fraction, visionSetLerpStyle_t style)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LerpFloat
==============
*/
float LerpFloat(float from, float to, float fraction, visionSetLerpStyle_t style)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LerpVec4
==============
*/
void LerpVec4(const vec4_t *from, const vec4_t *to, float fraction, visionSetLerpStyle_t style, vec4_t *result)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
VisionSetCurrent
==============
*/
bool __cdecl VisionSetCurrent(LocalClientNum_t localClientNum, visionSetMode_t mode, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_VisionSetStartLerp_To
==============
*/
bool CG_VisionSetStartLerp_To(LocalClientNum_t localClientNum, visionSetMode_t mode, visionSetLerpStyle_t style, const char *nameTo, int duration)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_VisionSetLerp_To
==============
*/
char CG_VisionSetLerp_To(const char *a1, char *a2, LocalClientNum_t localClientNum, visionSetMode_t mode, visionSetLerpStyle_t style, const char *nameTo, const char *nameFrom, float lerpFraction)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SetDefaultVision
==============
*/
void SetDefaultVision(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VisionSetConfigString_Naked
==============
*/
void CG_VisionSetConfigString_Naked(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VisionSetConfigString_Night
==============
*/
void CG_VisionSetConfigString_Night(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VisionSetConfigString_LastStand
==============
*/
void CG_VisionSetConfigString_LastStand(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VisionSetMyChanges
==============
*/
void __cdecl CG_VisionSetMyChanges()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_InLastStandVision
==============
*/
bool CG_InLastStandVision(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_InFlareVision
==============
*/
bool CG_InFlareVision(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_LookingThroughNightVision
==============
*/
char CG_LookingThroughNightVision(const LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DrawVisionSetDebug
==============
*/
void DrawVisionSetDebug(LocalClientNum_t localClientNum, visionSetMode_t curChannel)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VisionSetApplyToRefdef
==============
*/
void CG_VisionSetApplyToRefdef(LocalClientNum_t localClientNum, bool isExtracam)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
UpdateVarsLerpCustom
==============
*/
void UpdateVarsLerpCustom(float lerpFraction, const visionSetVars_t *from, const visionSetVars_t *to, visionSetLerpData_t *lerpData, visionSetVars_t *result)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
UpdateVarsLerp
==============
*/
void UpdateVarsLerp(visionSetLerpStyle_t a1, int time, const visionSetVars_t *from, const visionSetVars_t *to, visionSetLerpData_t *lerpData, visionSetVars_t *result)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_InitVisionSets
==============
*/
void CG_InitVisionSets(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_VisionSetsUpdate
==============
*/
void CG_VisionSetsUpdate(char *a1, LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
LoadVisionFileForTweaks
==============
*/
bool __cdecl LoadVisionFileForTweaks(visionSetVars_t *setVars)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CG_VisionSetUpdateTweaksFromFile_Film
==============
*/
void CG_VisionSetUpdateTweaksFromFile_Film()
{
	visionSetVars_t setVars{};
	if (!LoadVisionFileForTweaks(&setVars))
	{
		Com_PrintWarning(
			CON_CHANNEL_SYSTEM,
			"WARNING: Couldn't update film tweak vars from file.  Vision file is likely not in use.\n");
	}

	Dvar_SetFloat(
		r_filmLut,
		setVars.filmLut);
	Dvar_SetBool(
		r_filmTweakEnable,
		setVars.filmEnable);
	Dvar_SetVec4(
		vc_RS,
		setVars.visColorRangeS[0],
		setVars.visColorRangeS[1],
		setVars.visColorRangeS[2],
		setVars.visColorRangeS[3]);
	Dvar_SetVec4(
		vc_RE,
		setVars.visColorRangeE[0],
		setVars.visColorRangeE[1],
		setVars.visColorRangeE[2],
		setVars.visColorRangeE[3]);
	Dvar_SetVec4(
		vc_SMR,
		setVars.visColorShadowMatrixR[0],
		setVars.visColorShadowMatrixR[1],
		setVars.visColorShadowMatrixR[2],
		setVars.visColorShadowMatrixR[3]);
	Dvar_SetVec4(
		vc_SMG,
		setVars.visColorShadowMatrixG[0],
		setVars.visColorShadowMatrixG[1],
		setVars.visColorShadowMatrixG[2],
		setVars.visColorShadowMatrixG[3]);
	Dvar_SetVec4(
		vc_SMB,
		setVars.visColorShadowMatrixB[0],
		setVars.visColorShadowMatrixB[1],
		setVars.visColorShadowMatrixB[2],
		setVars.visColorShadowMatrixB[3]);
	Dvar_SetVec4(
		vc_MMR,
		setVars.visColorMidtoneMatrixR[0],
		setVars.visColorMidtoneMatrixR[1],
		setVars.visColorMidtoneMatrixR[2],
		setVars.visColorMidtoneMatrixR[3]);
	Dvar_SetVec4(
		vc_MMG,
		setVars.visColorMidtoneMatrixG[0],
		setVars.visColorMidtoneMatrixG[1],
		setVars.visColorMidtoneMatrixG[2],
		setVars.visColorMidtoneMatrixG[3]);
	Dvar_SetVec4(
		vc_MMB,
		setVars.visColorMidtoneMatrixB[0],
		setVars.visColorMidtoneMatrixB[1],
		setVars.visColorMidtoneMatrixB[2],
		setVars.visColorMidtoneMatrixB[3]);
	Dvar_SetVec4(
		vc_HMR,
		setVars.visColorHilightMatrixR[0],
		setVars.visColorHilightMatrixR[1],
		setVars.visColorHilightMatrixR[2],
		setVars.visColorHilightMatrixR[3]);
	Dvar_SetVec4(
		vc_HMG,
		setVars.visColorHilightMatrixG[0],
		setVars.visColorHilightMatrixG[1],
		setVars.visColorHilightMatrixG[2],
		setVars.visColorHilightMatrixG[3]);
	Dvar_SetVec4(
		vc_HMB,
		setVars.visColorHilightMatrixB[0],
		setVars.visColorHilightMatrixB[1],
		setVars.visColorHilightMatrixB[2],
		setVars.visColorHilightMatrixB[3]);
	Dvar_SetVec4(
		vc_FGM,
		setVars.visColorFinalGamma[0],
		setVars.visColorFinalGamma[1],
		setVars.visColorFinalGamma[2],
		setVars.visColorFinalGamma[3]);
	Dvar_SetVec4(
		vc_FSM,
		setVars.visColorFinalSaturation[0],
		setVars.visColorFinalSaturation[1],
		setVars.visColorFinalSaturation[2],
		setVars.visColorFinalSaturation[3]);
	Dvar_SetVec4(
		vc_FBM,
		setVars.visColorFinalBlend[0],
		setVars.visColorFinalBlend[1],
		setVars.visColorFinalBlend[2],
		setVars.visColorFinalBlend[3]);
	Dvar_SetVec4(
		r_sunFlareTint,
		setVars.sunFlareTint[0],
		setVars.sunFlareTint[1],
		setVars.sunFlareTint[2],
		setVars.sunFlareTint[3]);
}

/*
==============
CG_VisionSetUpdateTweaksFromFile_CharPrimary
==============
*/
void CG_VisionSetUpdateTweaksFromFile_CharPrimary()
{
	visionSetVars_t setVars{};
	if (!LoadVisionFileForTweaks(&setVars))
	{
		Com_PrintWarning(
			CON_CHANNEL_SYSTEM,
			"WARNING: Couldn't update character primary light tweak vars from file.  Vision file is likely not in use.\n");
	}

	Dvar_SetBool(
		r_primaryLightUseTweaks,
		setVars.charPrimaryUseTweaks);
	Dvar_SetFloat(
		r_primaryLightTweakDiffuseStrength,
		setVars.charPrimaryDiffuseScale);
	Dvar_SetFloat(
		r_primaryLightTweakSpecularStrength,
		setVars.charPrimarySpecularScale);
}

/*
==============
CG_VisionSetUpdateTweaksFromFile_Bloom
==============
*/
void CG_VisionSetUpdateTweaksFromFile_Bloom()
{
	visionSetVars_t setVars{};
	if (!LoadVisionFileForTweaks(&setVars))
	{
		Com_PrintWarning(
			CON_CHANNEL_SYSTEM,
			"WARNING: Couldn't update bloom tweak vars from file.  Vision file is likely not in use.\n");
	}

	Dvar_SetVec4(
		vc_LIB,
		setVars.visBloomLevelsRGBYInB[0],
		setVars.visBloomLevelsRGBYInB[1],
		setVars.visBloomLevelsRGBYInB[2],
		setVars.visBloomLevelsRGBYInB[3]);
	Dvar_SetVec4(
		vc_LIG,
		setVars.visBloomLevelsRGBYInG[0],
		setVars.visBloomLevelsRGBYInG[1],
		setVars.visBloomLevelsRGBYInG[2],
		setVars.visBloomLevelsRGBYInG[3]);
	Dvar_SetVec4(
		vc_LIW,
		setVars.visBloomLevelsRGBYInW[0],
		setVars.visBloomLevelsRGBYInW[1],
		setVars.visBloomLevelsRGBYInW[2],
		setVars.visBloomLevelsRGBYInW[3]);
	Dvar_SetVec4(
		vc_LOB,
		setVars.visBloomLevelsRGBYOutB[0],
		setVars.visBloomLevelsRGBYOutB[1],
		setVars.visBloomLevelsRGBYOutB[2],
		setVars.visBloomLevelsRGBYOutB[3]);
	Dvar_SetVec4(
		vc_LOW,
		setVars.visBloomLevelsRGBYOutW[0],
		setVars.visBloomLevelsRGBYOutW[1],
		setVars.visBloomLevelsRGBYOutW[2],
		setVars.visBloomLevelsRGBYOutW[3]);
	Dvar_SetVec4(
		vc_RGBH,
		setVars.visBloomRGBHi[0],
		setVars.visBloomRGBHi[1],
		setVars.visBloomRGBHi[2],
		setVars.visBloomRGBHi[3]);
	Dvar_SetVec4(
		vc_RGBL,
		setVars.visBloomRGBLo[0],
		setVars.visBloomRGBLo[1],
		setVars.visBloomRGBLo[2],
		setVars.visBloomRGBLo[3]);
	Dvar_SetVec4(
		vc_YH,
		setVars.visBloomYHi[0],
		setVars.visBloomYHi[1],
		setVars.visBloomYHi[2],
		setVars.visBloomYHi[3]);
	Dvar_SetVec4(
		vc_YL,
		setVars.visBloomYLo[0],
		setVars.visBloomYLo[1],
		setVars.visBloomYLo[2],
		setVars.visBloomYLo[3]);
}

