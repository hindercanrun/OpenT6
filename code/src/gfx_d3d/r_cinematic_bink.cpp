#include "types.h"

CinematicGlob_Bink cinematicBinkGlob;
MoviePlayerFunctions binkMoviePlayerFunctions;

int dword_83DA494;
int dword_83DA48C;
int dword_83DA490;
int dword_83DA488;

/*
==============
R_Cinematic_CheckBinkError
==============
*/
const char *R_Cinematic_CheckBinkError()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
CinematicHunk_Open
==============
*/
void CinematicHunk_Open(CinematicHunk *hunk, void *memory, int size)
{
	hunk->base = memory;
	hunk->atFront = memory;
	hunk->end = &memory[size];
	hunk->atBack = &memory[size];
	hunk->lastAllocPtr = 0;
	hunk->fragmented = 0;
}

/*
==============
CinematicHunk_Close
==============
*/
void CinematicHunk_Close(CinematicHunk *hunk)
{
	hunk->base = 0;
	hunk->atFront = 0;
	hunk->atBack = 0;
	hunk->end = 0;
	hunk->lastAllocPtr = 0;
	hunk->fragmented = 0;
}

/*
==============
CinematicHunk_Reset
==============
*/
void CinematicHunk_Reset(CinematicHunk *hunk)
{
	void *end = hunk->end;
	hunk->atFront = hunk->base;
	hunk->atBack = end;
	hunk->lastAllocPtr = 0;
	hunk->fragmented = 0;
}

/*
==============
CinematicHunk_GetFreeSpace
==============
*/
int CinematicHunk_GetFreeSpace(CinematicHunk *hunk)
{
	return hunk->atBack - hunk->atFront;
}

/*
==============
CinematicHunk_Alloc
==============
*/
void *CinematicHunk_Alloc(CinematicHunk *hunk, int size)
{
	char *atFront = hunk->atFront;
	char *atBack = hunk->atBack;
	hunk->atFront = &atFront[size];

	if (&atFront[size] <= atBack)
	{
		if (hunk->fragmented)
		{
			Com_PrintWarning(13, "Bink allocating from fragmented memory at 0x%x.\n", &atFront[size]);
			hunk->fragmented = 0;
		}

		hunk->lastAllocPtr = atFront;
		return atFront;
	}
	else
	{
		return -1;
	}
}

/*
==============
BinkMoviePlayer::GetTimeRemaining
==============
*/
/*double BinkMoviePlayer::GetTimeRemaining(void *handle)
{
	if ((cinematicBinkGlob.current.playbackFlags & 2) != 0)
	{
		return -1.0;
	}
	else
	{
		return (handle->Frames - handle->FrameNum) / (cinematicBinkGlob.framesPerMs * 1000.0);
	}
}*/

/*
==============
BinkMoviePlayer::SetPaused
==============
*/
/*void BinkMoviePlayer::SetPaused(void *handle, bool paused, bool forUnderrun)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::GetMaxTextureBytesNeeded
==============
*/
/*void **BinkMoviePlayer::GetMaxTextureBytesNeeded()
{
	return &loc_5003FC + 4;
}*/

/*
==============
BinkMoviePlayer::GetMainBytesNeeded
==============
*/
/*unsigned int BinkMoviePlayer::GetMainBytesNeeded(unsigned int playbackFlags)
{
	unsigned int result = 1572864;

	if ((playbackFlags & 4) == 0)
	{
		result = (~(playbackFlags << 18) & 0x400000 | 0x200000) + 1572864;
	}

	if ((playbackFlags & 8) != 0)
	{
		result *= 2;
	}

	return result;
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_BlackRendererImages
==============
*/
/*GfxImage *BinkMoviePlayer::R_Cinematic_BlackRendererImages()
{
	int result = dword_83DA494;
	gfxCmdBufInput.codeImages[22] = dword_83DA48C;
	gfxCmdBufInput.codeImages[23] = dword_83DA494;
	gfxCmdBufInput.codeImages[24] = dword_83DA494;
	gfxCmdBufInput.codeImages[25] = dword_83DA48C;

	return result;
}*/

/*
==============
BinkMoviePlayer::InitMemory
==============
*/
/*void __cdecl BinkMoviePlayer::InitMemory(
	char *mainMemory,
	unsigned int mainBytes,
	void *textureMemory,
	unsigned int textureBytes,
	unsigned int playbackFlags)
{
	BinkMoviePlayer::R_Cinematic_BlackRendererImages();
	CinematicHunk_Open(&cinematicBinkGlob.masterHunk, mainMemory, mainBytes);
	char *v5 = CinematicHunk_Alloc(&cinematicBinkGlob.masterHunk, mainBytes);

	if ((playbackFlags & 8) != 0)
	{
		CinematicHunk_Open(&cinematicBinkGlob.binkHunk, v5, mainBytes >> 1);
		CinematicHunk_Open(&cinematicBinkGlob.altBinkHunk, &v5[mainBytes >> 1], mainBytes >> 1);
		cinematicBinkGlob.altBinkHunkAlloced = 1;
	}
	else
	{
		CinematicHunk_Open(&cinematicBinkGlob.binkHunk, v5, mainBytes);
	}

	cinematicBinkGlob.current.playbackFlags = playbackFlags;
	cinematicBinkGlob.activeImageFrame = -1;
	cinematicBinkGlob.readRequestId = -1;
	cinematicBinkGlob.lastSeamlessBinkTimeMs = 0.0;
}*/

/*
==============
BinkMoviePlayer::Destroy
==============
*/
/*void BinkMoviePlayer::Destroy()
{
	CinematicHunk_Close(&cinematicBinkGlob.masterHunk);
	CinematicHunk_Close(&cinematicBinkGlob.binkHunk);

	if (cinematicBinkGlob.altBinkHunkAlloced)
	{
		CinematicHunk_Close(&cinematicBinkGlob.altBinkHunk);
		*&cinematicBinkGlob.altBinkHunkAlloced = 0;
	}
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_ReleaseImages
==============
*/
/*void BinkMoviePlayer::R_Cinematic_ReleaseImages(CinematicTextureSet *textureSet)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::MakeBinkTexturePC
==============
*/
/*int BinkMoviePlayer::MakeBinkTexturePC(unsigned int width, unsigned int height, int sysMem, DXGI_FORMAT format, unsigned int pixel_size, ID3D11Texture2D **out_texture, void **out_ptr, unsigned int *out_pitch, unsigned int *out_size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_MakeBinkDrawTextures
==============
*/
/*HRESULT BinkMoviePlayer::R_Cinematic_MakeBinkDrawTextures(unsigned int a1, unsigned int *a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	HRESULT tmp;
	return tmp;
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_InitBinkTextures
==============
*/
/*HRESULT BinkMoviePlayer::R_Cinematic_InitBinkTextures(unsigned int *a1)
{
	UNIMPLEMENTED(__FUNCTION__);
	HRESULT tmp;
	return tmp;
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_Unlock_textures
==============
*/
/*void BinkMoviePlayer::R_Cinematic_Unlock_textures()
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_SetRendererImagesToFrame
==============
*/
/*void BinkMoviePlayer::R_Cinematic_SetRendererImagesToFrame(int frameToSetTo)
{
	if (cinematicBinkGlob.textureSet.drawImageY.texture.basemap)
	{
		gfxCmdBufInput.codeImages[22] = &cinematicBinkGlob.textureSet.drawImageY;
	}
	else
	{
		gfxCmdBufInput.codeImages[22] = dword_83DA490;
	}

	gfxCmdBufInput.codeImages[23] = &cinematicBinkGlob.textureSet.drawImageCr;

	if (!cinematicBinkGlob.textureSet.drawImageCr.texture.basemap)
	{
		gfxCmdBufInput.codeImages[23] = dword_83DA494;
	}

	gfxCmdBufInput.codeImages[24] = &cinematicBinkGlob.textureSet.drawImageCb;

	if (!cinematicBinkGlob.textureSet.drawImageCb.texture.basemap)
	{
		gfxCmdBufInput.codeImages[24] = dword_83DA494;
	}

	if (cinematicBinkGlob.textureSet.drawImageA.texture.basemap)
	{
		gfxCmdBufInput.codeImages[25] = &cinematicBinkGlob.textureSet.drawImageA;
	}
	else
	{
		gfxCmdBufInput.codeImages[25] = dword_83DA488;
	}
}*/

/*
==============
BinkMoviePlayer::GetTimeElapsed
==============
*/
/*double BinkMoviePlayer::GetTimeElapsed()
{
	return cinematicBinkGlob.timeInMsec * 0.001;
}*/

/*
==============
BinkMoviePlayer::SetMovieClock
==============
*/
/*void BinkMoviePlayer::SetMovieClock(void *handle, float time)
{
	cinematicBinkGlob.timeInMsec = time * 1000.0;
}*/

/*
==============
BinkMoviePlayer::SetVolume
==============
*/
/*void BinkMoviePlayer::SetVolume(void *handle, float volume)
{
	MovieSpecificInfo *p_current = &cinematicBinkGlob.current;

	if (handle != cinematicBinkGlob.current.bink)
	{
		p_current = &cinematicBinkGlob.next;
	}

	p_current->playbackVolume = volume;
}*/

/*
==============
BinkMoviePlayer::GetBufferFillPercentage
==============
*/
/*int BinkMoviePlayer::GetBufferFillPercentage(void *handle)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}*/

/*
==============
BinkMoviePlayer::IsUnderrun
==============
*/
/*bool BinkMoviePlayer::IsUnderrun(void *notthis)
{
	return BinkMoviePlayer::GetBufferFillPercentage(handle) <= 20;
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_BinkWaitAsyncDecode
==============
*/
/*int BinkMoviePlayer::R_Cinematic_BinkWaitAsyncDecode(BINK *bink, int waitMs)
{
	if (!BinkDoFrameAsyncWait(bink, waitMs))
	{
		return 0;
	}

	BinkMoviePlayer::R_Cinematic_Unlock_textures();
	return 1;
}*/

/*
==============
BinkMoviePlayer::IsReadyToStart
==============
*/
/*bool BinkMoviePlayer::IsReadyToStart(BINK *handle)
{
	return BinkMoviePlayer::GetBufferFillPercentage(handle) >= 10;
}*/

/*
==============
BinkMoviePlayer::StreamThread_DoBackgroundIO_Bink
==============
*/
/*void BinkMoviePlayer::StreamThread_DoBackgroundIO_Bink(int msAllotted, void *user, int id)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::StartPlayback
==============
*/
/*void BinkMoviePlayer::StartPlayback(void *handle, unsigned int playbackFlags)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::AdvanceFrame
==============
*/
/*const char *BinkMoviePlayer::AdvanceFrame()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_Lock_textures
==============
*/
/*void BinkMoviePlayer::R_Cinematic_Lock_textures(D3D11_MAPPED_SUBRESOURCE *p_m, int a2, int a3)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::R_Cinematic_BinkLaunchAsyncDecode
==============
*/
/*const char *BinkMoviePlayer::R_Cinematic_BinkLaunchAsyncDecode()
{
	BinkMoviePlayer::R_Cinematic_Lock_textures();
	BinkDoFrameAsync(
		cinematicBinkGlob.current.bink,
		cinematicBinkGlob.asyncThreadIndex,
		cinematicBinkGlob.asyncThreadIndex);
	const char *result = BinkGetError();

	return result;
}*/

/*
==============
BinkMoviePlayer::DoFrameSync
==============
*/
/*void BinkMoviePlayer::DoFrameSync()
{
	BinkMoviePlayer::R_Cinematic_Lock_textures();
	BinkDoFrame(cinematicBinkGlob.current.bink);

	return BinkMoviePlayer::R_Cinematic_Unlock_textures();
}*/

/*
==============
BinkMoviePlayer::UpdateMoviesAndImages
==============
*/
/*void BinkMoviePlayer::UpdateMoviesAndImages(D3D11_MAPPED_SUBRESOURCE *a1, int a2, bool forceWait)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::ForceRelinquishIO
==============
*/
/*char BinkMoviePlayer::ForceRelinquishIO()
{
	char result = cinematicBinkGlob.readRequestId;

	if ( cinematicBinkGlob.readRequestId != -1 )
	{
		result = Stream_FreeRequest(cinematicBinkGlob.readRequestId, 1);
		cinematicBinkGlob.readRequestId = -1;
	}
	return result;
}*/

/*
==============
BinkMoviePlayer::Bink_Alloc_Alt
==============
*/
/*void *BinkMoviePlayer::Bink_Alloc_Alt(unsigned int bytes)
{
	return malloc(bytes);
}*/

/*
==============
BinkMoviePlayer::Bink_Free
==============
*/
/*void BinkMoviePlayer::Bink_Free(void *ptr)
{
	if (cinematicBinkGlob.binkHunk.lastAllocPtr == ptr)
	{
		cinematicBinkGlob.binkHunk.atFront = cinematicBinkGlob.binkHunk.lastAllocPtr;
		cinematicBinkGlob.binkHunk.lastAllocPtr = 0;
	}
	else
	{
		cinematicBinkGlob.binkHunk.fragmented = 1;
	}
}*/

/*
==============
BinkMoviePlayer::Bink_Free_Alt
==============
*/
/*void BinkMoviePlayer::Bink_Free_Alt(void *ptr)
{
	if (cinematicBinkGlob.altBinkHunk.lastAllocPtr == ptr)
	{
		cinematicBinkGlob.altBinkHunk.atFront = cinematicBinkGlob.altBinkHunk.lastAllocPtr;
		cinematicBinkGlob.altBinkHunk.lastAllocPtr = 0;
	}
	else
	{
		cinematicBinkGlob.altBinkHunk.fragmented = 1;
	}
}*/

/*
==============
BinkMoviePlayer::PreOpen_Common
==============
*/
/*void BinkMoviePlayer::PreOpen_Common(bool isNextBink)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::PostOpen_Common
==============
*/
/*void BinkMoviePlayer::PostOpen_Common(BINK *pbink, unsigned int playbackFlags, bool isNextBink)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
BinkMoviePlayer::GetLastError
==============
*/
/*const char *__cdecl BinkMoviePlayer::GetLastError()
{
	return BinkGetError();
}*/

/*
==============
BinkMoviePlayer::OpenFromFastfile
==============
*/
/*BINK *BinkMoviePlayer::OpenFromFastfile(char *a1, const char *assetname, unsigned int playbackFlags)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}*/

/*
==============
BinkMoviePlayer::OpenPath
==============
*/
/*BINK *BinkMoviePlayer::OpenPath(char *a1, const char *filepath, unsigned int playbackFlags)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}*/

/*
==============
BinkMoviePlayer::StopPlayback
==============
*/
/*void BinkMoviePlayer::StopPlayback(void *handle)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
R_Cinematic_GetBinkFunctions
==============
*/
MoviePlayerFunctions *R_Cinematic_GetBinkFunctions()
{
	return &binkMoviePlayerFunctions;
}

/*
==============
launch_async_bink_drawCallback
==============
*/
int launch_async_bink_drawCallback(jqBatch *batch)
{
	void *v1 = jqCallbackPre(batch, "launch_async_bink_draw");

	if (cinematicBinkGlob.current.started)
	{
		// BinkMoviePlayer::R_Cinematic_BinkLaunchAsyncDecode();
	}

	jqCallbackPost(batch, v1, 1);
	return 0;
}

