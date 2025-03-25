#include "types.h"

/*
==============
SND_IsInitialized
==============
*/
BOOL SND_IsInitialized()
{
	return g_snd.init != FALSE;
}

/*
==============
SND_GetGroupByIndex
==============
*/
SndVolumeGroup *SND_GetGroupByIndex(unsigned int index)
{
	assertMsg(
		(unsigned)index < (unsigned)g_snd.global_constants->groupCount,
		"index doesn't index g_snd.global_constants->groupCount\n\t%i not in [0, %i)",
		index,
		g_snd.global_constants->groupCount
	);
	return &g_snd.global_constants->groups[index];
}

/*
==============
SND_GetMaster
==============
*/
SndMaster *SND_GetMaster(unsigned int id)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetMasterByConfig
==============
*/
SndMaster *SND_GetMasterByConfig()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetMasterCurrent
==============
*/
SndMaster *SND_GetMasterCurrent()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetVoiceDuck
==============
*/
SndSidechainDuck *SND_GetVoiceDuck(unsigned int id)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetCurrentVoiceDuck
==============
*/
SndSidechainDuck *SND_GetCurrentVoiceDuck()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetFutz
==============
*/
SndFutz *SND_GetFutz(unsigned int id)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetCurveByIndex
==============
*/
SndCurve *SND_GetCurveByIndex(unsigned int i)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_GetPanByIndex
==============
*/
SndPan *SND_GetPanByIndex(int i)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_FindContextIndex
==============
*/
int SND_FindContextIndex(unsigned int type)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SND_IsValidContext
==============
*/
char SND_IsValidContext(unsigned int type, unsigned int value)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SND_GetDuckGroupIndex
==============
*/
int SND_GetDuckGroupIndex(unsigned int id)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SND_GroupCategory
==============
*/
SndMenuCategory SND_GroupCategory(unsigned int group)
{
	UNIMPLEMENTED(__FUNCTION__);
	SndMenuCategory tmp;
	return tmp;
}

/*
==============
SND_GroupGetAttenuation
==============
*/
double SND_GroupGetAttenuation(unsigned int group)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

