#include "types.h"

float cg_hudSplitscreenScale;

/*
==============
ScrPlace_RealFromVirtual_Width
==============
*/
double ScrPlace_RealFromVirtual_Width(const ScreenPlacement *scrPlace, float width)
{
	return ScrPlace_HiResGetScaleY() * cg_hudSplitscreenScale * width * scrPlace->scaleVirtualToReal.v[0];
}

/*
==============
ScrPlace_RealFromVirtual_Height
==============
*/
double ScrPlace_RealFromVirtual_Height(const ScreenPlacement *scrPlace, float height)
{
	return ScrPlace_HiResGetScaleY() * cg_hudSplitscreenScale * height * scrPlace->scaleVirtualToReal.v[1];
}

/*
==============
ScrPlace_VirtualFromReal_Height
==============
*/
double ScrPlace_VirtualFromReal_Height(const ScreenPlacement *scrPlace, float height)
{
	return height / cg_hudSplitscreenScale / ScrPlace_HiResGetScaleY() * scrPlace->scaleRealToVirtual.v[1];
}

