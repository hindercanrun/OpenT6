#include "types.h"

const dvar_t* r_warningRepeatDelay;

/*
==============
R_WarnOncePerFrame
==============
*/
void R_WarnOncePerFrame(GfxWarningType warnType, ...)
{
	char message[1028];
	char *vargs;
	va_list va;
	va_start(va, warnType);

	assert(r_warningRepeatDelay);

	if (s_warnCount[warnType] < rg.frontEndFrameCount)
	{
		s_warnCount[warnType] = rg.frontEndFrameCount + (R_UpdateFrameRate() * r_warningRepeatDelay->current.value);
		va_copy(vargs, va);
		_vsnprintf(message, sizeof(message), s_warnFormat[warnType], va);
		vargs = 0;
		Com_PrintWarning(8, "%s", message);
	}
}

/*
==============
R_WarnInitDvars
==============
*/
void R_WarnInitDvars()
{
	r_warningRepeatDelay = Dvar_RegisterFloat(
		"r_warningRepeatDelay",
		5.0,
		0.0,
		30.0,
		DVAR_NOFLAG,
		"Number of seconds after displaying a \"per-frame\" warning before it will display again");
}

/*
==============
R_UpdateFrameRate
==============
*/
void R_UpdateFrameRate()
{
	UNIMPLEMENTED(__FUNCTION__);
}

