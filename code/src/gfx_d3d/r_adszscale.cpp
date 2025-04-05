#include "types.h"

/*
==============
R_SetADSZScaleConstants
==============
*/
void R_SetADSZScaleConstants(GfxCmdBufInput *input, float adsZScale)
{
	*input->consts[157].v = adsZScale;
	*&input->consts[157].b = 0LL;
}

