#include "types.h"

/*
==============
SND_DebugFini
==============
*/
void SND_DebugFini()
{
	Cmd_RemoveCommand("snd_playLocal");
}

/*
==============
DebugDrawWorldSound3D
==============
*/
void DebugDrawWorldSound3D(int idx, int debugDrawStyle, int *offsets, int *closestId, float *closestIdDotProd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_DebugDrawWorldSounds
==============
*/
void SND_DebugDrawWorldSounds(int debugDrawStyle)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_GetSoundOverlay
==============
*/
int SND_GetSoundOverlay(SndOverlayInfo *info, int start, int count)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SND_GetSoundOverlay
==============
*/
int SND_GetSoundOverlay(SndOverlayType type, SndOverlayInfo *info, int maxcount)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

