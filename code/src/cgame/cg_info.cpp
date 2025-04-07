#include "types.h"

static int com_expectedHunkUsage;

/*
==============
CG_LoadingString
==============
*/
void CG_LoadingString(LocalClientNum_t localClientNum, const char *s)
{
	Com_Printf(CON_CHANNEL_CLIENT, "LOADING... %s\n", s);
}

/*
==============
CG_IsShowingProgress_LoadObj
==============
*/
BOOL CG_IsShowingProgress_LoadObj()
{
	return com_expectedHunkUsage > 0;
}

/*
==============
CG_IsShowingProgress_FastFile
==============
*/
BOOL CG_IsShowingProgress_FastFile()
{
	return DB_GetLoadedFraction() > 0.0;
}

/*
==============
CG_DrawInformation
==============
*/
void CG_DrawInformation(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

