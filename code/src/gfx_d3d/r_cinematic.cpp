#include "types.h"
#include "gfx_d3d_public.h"

CinematicGlob cinematicGlob;

/*
==============
duck_Initialize
==============
*/
void duck_Initialize()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
duck_Update
==============
*/
void duck_Update()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_MemoryInit
==============
*/
void R_Cinematic_MemoryInit(CinematicInfo *cinematicInfo)
{
	cinematicGlob.bytesAllocated = cinematicInfo->moviePlayer->GetMainBytesNeeded(cinematicInfo->playbackFlags);
	cinematicGlob.masterBufferBase = cinematicGlob.memPool;
	cinematicInfo->moviePlayer->InitMemory(
		cinematicGlob.memPool,
		cinematicGlob.bytesAllocated,
		0,
		0,
		cinematicInfo->playbackFlags);
}

/*
==============
R_Cinematic_CancelQueuedMovie
==============
*/
void R_Cinematic_CancelQueuedMovie(CinematicInfo *info)
{
	info->commonflags.packed &= ~1u;
	info->id = 0;
	info->name[0] = 0;
}

/*
==============
R_Cinematic_GetPathFromFilename
==============
*/
bool R_Cinematic_GetPathFromFilename(CinematicInfo *info, const char *filename, const char *ext, unsigned int playbackFlags)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_StartSound
==============
*/
void R_Cinematic_StartSound(CinematicInfo *info, bool startPaused)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_OpenMovie_Now
==============
*/
void *R_Cinematic_OpenMovie_Now(CinematicInfo *cinematicInfo, const char *filename, unsigned int playbackFlags, bool isNextBink)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
StreamThread_OpenMovie
==============
*/
void StreamThread_OpenMovie(int msAllotted, void *user)
{
	CinematicGlob *queue = cinematicGlob.queue;

	if (!*(user + 516))
	{
		queue = &cinematicGlob;
	}

	cinematicGlob.asyncOpenData.outMovieHandle = R_Cinematic_OpenMovie_Now(
													&queue->current,
													user,
													*(user + 128),
													*(user + 516));
}

/*
==============
R_Cinematic_QueueStreamOpen
==============
*/
void R_Cinematic_QueueStreamOpen(bool isNextBink, bool isNeededImmediately)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_PopFromQueue
==============
*/
void R_Cinematic_PopFromQueue()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_RemoveInactiveFromQueue
==============
*/
void R_Cinematic_RemoveInactiveFromQueue(int a1)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
StreamThread_GetMoviePath
==============
*/
void StreamThread_GetMoviePath(int msAllotted, void *user, int id)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_StartPlayback_Internal
==============
*/
void R_Cinematic_StartPlayback_Internal(const char *name, unsigned int playbackFlags, float volume, CIN_CALLBACK_INFO *callbackInfo, int id)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_GetPlayingId
==============
*/
int R_Cinematic_GetPlayingId()
{
	return cinematicGlob.current.id;
}

/*
==============
R_Cinematic_StartPlayback
==============
*/
int R_Cinematic_StartPlayback(const char *name, unsigned int playbackFlags, float volume, CIN_CALLBACK_INFO *callbackInfo, int reservedId)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_StopPlayback
==============
*/
char R_Cinematic_StopPlayback(int id, bool cancelAll)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_HandleFinishedCallbacks
==============
*/
void R_Cinematic_HandleFinishedCallbacks(CIN_CALLBACK_TYPE type)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_UpdateSoundTime
==============
*/
char R_Cinematic_UpdateSoundTime()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_UpdateFrame
==============
*/
void R_Cinematic_UpdateFrame(bool force_wait)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_Cinematic_GetFilenameAndTimeInMsec
==============
*/
char R_Cinematic_GetFilenameAndTimeInMsec(int id, char *outName, int outNameSize, unsigned int *outTimeInMsec)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_IsAnyPlaying
==============
*/
char R_Cinematic_IsAnyPlaying()
{
	Sys_EnterCriticalSection(CRITSECT_CINEMATIC);

	if ( cinematicGlob.current.id || cinematicGlob.queue[0].id )
	{
		Sys_LeaveCriticalSection(CRITSECT_CINEMATIC);
		return 1;
	}
	else
	{
		Sys_LeaveCriticalSection(CRITSECT_CINEMATIC);
		return 0;
	}
}

/*
==============
R_Cinematic_IsInProgress
==============
*/
char R_Cinematic_IsInProgress(int id)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_IsPreloading
==============
*/
char R_Cinematic_IsPreloading(int id)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_Cinematic_GetDebugInfo
==============
*/
void R_Cinematic_GetDebugInfo(const char **name, int *bytesUsed)
{
	*name = cinematicGlob.current.name;
	*bytesUsed = cinematicGlob.bytesAllocated;
	*bytesUsed += nullptr;
}

/*
==============
R_Cinematic_ForceRelinquishIO
==============
*/
void R_Cinematic_ForceRelinquishIO()
{
	if (cinematicGlob.current.moviePlayer)
	{
		cinematicGlob.current.moviePlayer->ForceRelinquishIO();
	}
}

