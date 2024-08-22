#include "types.h"
#include "vars.h"

const char *BUILD_MACHINE = "CODPCAB2 CEG";
const char *BUILD_TIME = "Tue Dec 11 18:15:37 2012";

/*
==============
Com_GetBuildVersion
==============
*/
char *Com_GetBuildVersion()
{
	sprintf(buf, "%s.%s.%d CL(%d) %s %s", "1", "0", 12, 1468705, BUILD_MACHINE, BUILD_TIME);
	return buf;
}

/*
==============
Com_GetBuildNumber
==============
*/
int Com_GetBuildNumber()
{
	return "%s.%s.%d", "1", "0", 12;
}

/*
==============
Com_GetBuildDisplayName
==============
*/
const char *Com_GetBuildDisplayName()
{
	return "Call of Duty Singleplayer - Release";
}

/*
==============
Com_GetBuildDisplayNameR
==============
*/
const char *Com_GetBuildDisplayNameR()
{
	return "Call of Duty(R) Singleplayer - Release";
}

/*
==============
Com_GetBuildName
==============
*/
const char *Com_GetBuildName()
{
	return "COD_T6_R SP";
}

