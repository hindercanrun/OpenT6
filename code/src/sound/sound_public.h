#pragma once

#include "types.h"

//t6/code/src/sound/sd_api.cpp
sd_mix_master_param *SD_GetMixParam(sd_mix_master_param *param);
sd_voice_param *SD_GetVoiceParam(int voiceIndex);
void SD_PrefetchAliasId(unsigned int aliasId, int timeTillPlayMs);
void SD_PreUpdate();
unsigned int SD_StartAlias(SndStartAliasInfo *info, int voiceIndex);
void SD_StopVoice(int voiceIndex);
void SD_UpdateVoice(int voiceIndex);
void SD_Sync();
void SD_Shutdown();
void SD_SetAuxCallback(bool (*callback)(float *, unsigned int, unsigned int));
void SD_SetVcsCallback(bool (*callback)(float *, unsigned int, unsigned int, bool *));

//t6/code/src/sound/sd_decode.cpp
void SD_DecoderShutdown();
sd_decoder *SD_DecoderAllocate(sd_source *source, const SndAssetBankEntry *entry, sd_decoder *pool, unsigned int count);
sd_decoder *SD_DecoderAllocate(const SndAssetBankEntry *a1, sd_source *source, const SndAssetBankEntry *entry);

//t6/code/src/sound/sd_mixer.cpp
sd_mix_master_param *SD_MixParamAllocate();
void SD_MixParamFree(sd_mix_master_param *param);
void SD_MixSetParam(sd_mix_master_param *param);

//t6/code/src/sound/sd_output_xa2.cpp
// void sd_xa2_callback::OnBufferEnd(sd_xa2_callback *notthis, void *pBufferContext);
void SD_OutputShutdown(bool reset);
void SD_OutputForceWakeup();
bool SD_XAudio2GetDeviceGUID(wchar_t *inGUID, _GUID *guid, char *outGUID, int size);
bool SD_XAudio2CheckDevice(IXAudio2 *pXAudio2, const XAUDIO2_DEVICE_DETAILS *deviceDetails, unsigned int deviceIndex);
void SD_SwitchDevice();
// void __stdcall SD_XAudio2Callbacks::OnCriticalError(SD_XAudio2Callbacks *notthis, HRESULT Error);
char SD_XAudio2EnumerateDevices(int a1);
bool SD_XAudio2InitPC(int a1);
void SD_OutputInit(int a1, bool reset);
void SD_Reset();

//t6/code/src/sound/sd_source.cpp
void SD_SourceInitStream(sd_source *source, const char *name, const SndAssetBankEntry *entry, int fid, const char *primeData, unsigned int primeSize);

//t6/code/src/sound/sd_stream.cpp
void SD_StreamShutdown();
void SD_StreamBufferPreload(const char *filename, unsigned int latencyMs, unsigned int offset, unsigned int size, int fileHandle);
sd_stream_globals *SD_StreamAllocate(const char *filename, const SndAssetBankEntry *entry, int fid, const char *primeData, unsigned int primeSize);
void SD_StreamDevhost();

//t6/code/src/sound/sd_voice.cpp
void SD_VoiceShutdown();
sd_voice_param *SD_VoiceParamAllocate();
void SD_VoiceParamFree(sd_voice_param *p);
sd_voice *SD_VoiceAllocate();
sd_voice *SD_VoiceAllocateRam(unsigned int assetId, bool looping, unsigned int channelCount, unsigned int frameRate, unsigned int frameCount, unsigned int dataSize, const char *data, const SndAssetBankEntry *entry);
sd_voice *SD_VoiceAllocateStream(const char *name, const SndAssetBankEntry *entry, int fid, const char *primeData, unsigned int primeSize);
void SD_VoiceSetParam(sd_voice *voice, sd_voice_param *param);
BOOL SD_VoiceHasData(sd_voice *voice);
void SD_VoiceStart(sd_voice *voice, sd_voice_param *param);
BOOL SD_VoiceStarted(sd_voice *voice);
BOOL SD_VoiceDone(sd_voice *voice);
__int64 SD_VoicePosition(sd_voice *voice);

//t6/code/src/sound/snd.cpp
void SND_SetPosition(int index, const vec3_t *org);
unsigned int SND_ActiveListenerCount();
int SND_GetListenerIndexNearestToOrigin(const vec3_t *origin, float *minDistanceSq);
int SND_AcquirePlaybackId();
void DoLengthNotify(int msec, void *lengthNotifyData, SndLengthType id);
void SND_StartLengthNotify(int index, int totalMsec);
double SND_GetSeed(unsigned int key, unsigned int global_age);
void SND_SetVoiceStartFlux(SndVoice *voice, vec3_t *player);
void SND_SetVoiceStartSeeds(const SndAlias *alias, SndVoice *voice);
void SND_SetVoiceStartFades(float fadetime, bool setScriptValues, float scriptPitch, float scriptPitchRate, float scriptAttenuation, float scriptAttenuationRate, SndVoice *voice);
void SND_UpdateVoicePosition(SndVoice *voice, const vec3_t *startPosition);
char SND_LosOcclusionCache(unsigned int channel, const vec3_t *position, float *value);
void SND_SetSoundFileVoiceInfo(int voiceIndex, int srcChannelCount, int baserate, int total_msec, int start_msec, SndFileLoadingState loadingState);
float Snd_GetGlobalPriorityVolume(const SndAlias *alias, const vec3_t *org, int localClientGroupMask);
void Snd_GetLowestPriority(float *priority, int *channel, unsigned int start, unsigned int count);
void SND_ContinueLoopingSound_Internal(int voiceIndex, float volumeScale, int fadeTime, const vec3_t *org, SndPlayback *playback, bool setScriptValues, float scriptPitch, float scriptPitchRate, float scriptAttenuation, float scriptAttenuationRate);
unsigned int SND_ContinueLoopingSound(unsigned int aliasId, float volumeScale, SndEntHandle sndEnt, const vec3_t *org, int fadeTime, SndPlayback *playback, bool setScriptValues, float scriptPitch, float scriptPitchRate, float scriptAttenuation, float scriptAttenuationRate);
SndAlias *SND_PickSoundAliasFromList(const SndAliasList *aliasList, int objectId, SndEntHandle sndEnt);
SndAlias *SND_PickSoundAlias(const char *name, int objectid, SndEntHandle sndEnt);
bool SND_CheckValidSecondary(const SndAlias *alias, const SndAlias *secondaryAlias);
void SND_GetPlayingInfo(unsigned int aliasHash, int *pcount, int *poldest, int *least, bool *isMultiple, SndEntHandle ent, bool useEnt);
bool SND_IsSoloAlias(const SndAlias *alias);
bool SND_IsMuteAlias(const SndAlias *alias);
void SND_PauseSounds();
int *SND_UnpauseSounds();
unsigned int SND_GetCurrentReverb();
void SND_UpdateRoomEffects(int frametime);
void SND_UpdatePreloads();
void SND_StopVoicePFutz(int voiceIndex);
void SND_SetStartPaused(SndVoice *voice, bool pause);
int SND_Active();
void SNDL_AddGlobals(SndDriverGlobals *globals);
void SNDL_RemoveGlobals(SndDriverGlobals *globals);
void SND_ErrorIfSoundGlobalsTrashed();
void SND_Init();
void __cdecl SND_ResetDriver();
double SND_GetPitch(SndVoice *voice);
double SND_GetBaseLevel(const SndVoice *voice);
float SND_GetDryLevel(const SndVoice *voice, float baseLevel);
float SND_GetWetLevel(const SndVoice *voice, float baseLevel);
void SND_GetLevels(const SndVoice *voice, float *wet, float *dry);
double SND_GetDistance(const SndVoice *voice);
double SND_GetLpfLevel(const SndVoice *voice);
unsigned int SND_GetVoiceLength(int voiceIndex);
double SND_GetOmni(const SndVoice *voice);
SndVoice *SND_GetPlaybackVoice(int playbackId);
SndDuckActive *SND_DuckFindFree();
void SND_DuckRateLimit(unsigned int count, const float *rate, const float *negrate, const float *target, float *delta, float *value);
void SND_SetDuckByCategory(SndDuckCategoryType category, unsigned int duckId, const SndDuck *duck, float amount);
SndDuckActive *SND_DuckStartAlias(const SndDuck *duck);
void SND_StopDuck(SndDuckActive *duck);
void SND_DuckUpdate(int a1, char *a2, float dt);
unsigned int SND_GetCurrentGfutzId();
char SND_AddLengthNotify(SndLengthType a1, char *a2, int playbackId, void *lengthNotifyData, SndLengthType id);
void SND_ResetVoiceInfo(int index);
void SND_ContinueLoopingPlayback(int id);
void SND_StopVoice(int voiceIndex);
void SND_ShutdownVoices();
void SND_UpdateVoiceDuck(SndVoice *voice);
void SND_UpdateVoice(SndVoice *voice, float dt);
void SND_DuckReset();
void __cdecl SND_SetVoiceStartInfo(int index, SndStartAliasInfo *SndStartAliasInfo);
int SND_FindFreeVoice(const vec3_t *a1, float volume, SndStartAliasInfo *startAliasInfo);
bool SND_Limit(const char *name, int aliasHash, SndLimitType limitType, int limitCount, SndEntHandle ent, bool useEnt, float priority);
char SND_LimitVoice(const SndAlias *alias, SndEntHandle ent);
unsigned int SND_PlaySoundAlias(int a1, const SndAliasList *aliasList, float volumeScale, SndEntHandle sndEnt, const vec3_t *org, int timeshift, int fadeTime, const vec3_t *direction, SndPlayback *playback, SndOcclusionStartCache *ocache, bool notify, const vec3_t *startPaused, bool setScriptValues, float scriptPitch, float scriptPitchRate, float scriptAttenuation, float scriptAttenuationRate);
void SND_UpdateDebug(unsigned int a1, float a2);
void SNDL_Update(float a1);
void SNDL_Shutdown();
void SND_SetGlobalFutz(unsigned int id, SndCallLocation callLocation);
void SND_SetStartPaused(int playbackId, bool pause);
void SND_SetGlobalFutz(const char *futzName, SndCallLocation callLocation);

//#include "sound/snd_alias_db.h"

//#include "sound/snd_alias_load_db.h"

//t6/code/src/sound/snd_asset_bank.cpp
void SND_ChecksumToString(const unsigned __int8 *checksum, char *string);
char SND_AssetBankValidateHeader(const char *filename, const SndAssetBankHeader *header, int64_t size, const uint8_t *checksum);
char SND_AssetBankValidateEntry(const char *name, const SndAssetBankHeader *header, const SndAssetBankEntry *entry);
int SND_EntryCompare(const void *va, const void *vb);
char SND_AssetBankFindEntry(unsigned int id, SndAssetBankEntry *entries, unsigned int entryCount, SndAssetBankEntry **entry);
unsigned int SND_AssetBankGetFrameRate(const SndAssetBankEntry *entry);
unsigned int SND_AssetBankGetChannelCount(const SndAssetBankEntry *entry);
BOOL SND_AssetBankGetLooping(const SndAssetBankEntry *entry);
unsigned int SND_AssetBankGetFrameCount(const SndAssetBankEntry *entry);
unsigned int SND_AssetBankGetLengthMs(const SndAssetBankEntry *entry);

//#include "sound/snd_asset_bank_load_db.h"

//t6/code/src/sound/snd_bank.cpp
int SND_CompareAssetLoads(const void *a, const void *b);
void SND_AddAssetToLoad(int bankFileId, unsigned int assetId, unsigned int fileOffset, unsigned int size, void *destination, unsigned int memoryOffset, SndBank *bank);
SndAssetToLoad *SND_FindNextAssetToLoad();
void SND_LoadAssetCallback(int id, stream_status result, unsigned int numBytesRead, void *b);
void SND_LoadAssetUpdate();
int SND_AllocateEntries(const char *bankName, int entryCount);
void SND_GetRuntimeAssetBankFileName(const char *a1, bool stream, const char *zone, const char *language, int length, char *path);
char SND_AssetBankFindStreamed(unsigned int id, SndAssetBankEntry **entry, int *fid);
char SND_AssetBankFindLoaded(unsigned int id, SndAssetBankEntry **entry, void **data);
bool SND_FindInIndex(unsigned int key, const SndBank *bank, SndAliasList **result);
void SND_AssertBankIndexValid(const SndBank *bank);
void SNDL_RemovePatch(SndPatch *patch);
int SND_AliasCount();
SndAliasList *SND_AliasByIndex(unsigned int index);
SndAliasList *SND_BankAliasLookup(unsigned int key);
SndAliasList *SND_BankAliasLookupCache(unsigned int id);
unsigned int SND_FindAliasId(const char *name);
int SND_GetPlaybackTime(const char *name);
const SndRadverb *SND_GetRadverb(unsigned int id);
SndAliasList *SND_FindAliasFromId(unsigned int id);
SndVolumeGroup *SND_FindRowGroup(unsigned int id);
SndCurve *SND_FindRowCurve(unsigned int id);
SndPan *SND_FindRowPan(unsigned int id);
// int gjk_base_t::get_brush();
const SndDuck *SND_GetDuckById(unsigned int id);
const SndDuck *SND_FindRowDuckPatchLpf(unsigned int id);
SndContext *SND_FindRowContext(unsigned int id);
const SndRadverb *SND_FindRowRadverb(unsigned int id);
SndMaster *SND_FindRowMaster(unsigned int id);
void SND_PatchValue(unsigned int table, char *asset, unsigned int fieldIndex, unsigned int value);
void SND_PatchDuckValue(unsigned int table, SndDuck *duck, unsigned int fieldIndex, unsigned int groupId, unsigned int value);
void SND_PatchApply(const SndPatch *patch);
void SNDL_ResetAliases();
void SND_BankReadCallback(int id, stream_status result, unsigned int numBytesRead, void *b);
void SND_StreamRead(SndBank *bank, int fileHandle, int offset, int size, void *data);
char SND_StartHeaderRead(bool streamed, SndRuntimeAssetBank *assetBank, SndBank *bank);
char SND_HeaderCheck(SndBank *bank, SndRuntimeAssetBank *assetBank);
char SND_StartTocRead(SndBank *bank, SndRuntimeAssetBank *assetBank);
char SND_TocCheck(SndBank *bank, SndRuntimeAssetBank *assetBank);
void SND_BankLoadError(SndBank *bank);
unsigned int SND_GetAliasIdFromScriptId(const unsigned int scriptId);
void SND_EnqueueLoadedAssets(SndBank *bank);
void SNDL_AddBank(SndBank *bank);
void SNDL_RemoveBank(SndBank *bank);
void SNDL_AddPatch(SndPatch *patch);
void SNDL_ApplyPatches();
SndAliasList *SND_FindAlias(const char *name);
void SND_EnqueueAssetLoads(SndBank *bank);
void SND_BankLoadUpdateState(SndBank *bank);
void SND_LoadSoundsWait();
char SND_BankUpdate();
bool SND_IsAliasNameLooping(const char *name);
int SND_GetPlaybackTime();

//#include "sound/snd_bank_load_db.h"

//t6/code/src/sound/snd_debug.cpp
void SND_DebugFini();
void DebugDrawWorldSound3D(int idx, int debugDrawStyle, int *offsets, int *closestId, float *closestIdDotProd);
void SND_DebugDrawWorldSounds(int debugDrawStyle);
int SND_GetSoundOverlay(SndOverlayInfo *info, int start, int count);
int SND_GetSoundOverlay(SndOverlayType type, SndOverlayInfo *info, int maxcount);

//t6/code/src/sound/snd_dsp.cpp
void SND_DspSqr(unsigned int count, const float *a, float *c);
void SND_DspMul(unsigned int count, const float *a, float *b);
void SND_DspCube(unsigned int count, const float *a, float *c);
void SND_DspMin(unsigned int count, const float *a, const float *b, float *c);
void SND_DspMax(unsigned int count, const float *a, const float *b, float *c);
void SND_DspScale(unsigned int count, float a, float *c);
void SND_DspConstant(unsigned int count, float a, float *c);
void SND_DspAdd(unsigned int count, const float *a, const float *b, float *c);
void SND_DspSub(unsigned int count, const float *a, const float *b, float *c);
void SND_DspSub(unsigned int count, const float *a, float *c);
void SND_DspBiquadInPlace(const SndDspBiQuadCoef *coef, SndDspBiquadState *state0, unsigned int count, float *i0);
void SND_DspBiquadNormalize(float *a, float *b, SndDspBiQuadCoef *coef);
void __cdecl SND_DspBiquadHShelve(float Fs, float db, float Fhz, float q, SndDspBiQuadCoef *coef);

//t6/code/src/sound/snd_dsp_radverb.cpp
void SND_RvParamsDefault(SndRvParams *params);

// t6/code/src/sound/snd_dvar.cpp
void SND_InitDvar();

//t6/code/src/sound/snd_globals.cpp
BOOL SND_IsInitialized();
SndVolumeGroup *SND_GetGroupByIndex(unsigned int index);
SndMaster *SND_GetMaster(unsigned int id);
SndMaster *SND_GetMasterByConfig();
SndMaster *SND_GetMasterCurrent();
SndSidechainDuck *SND_GetVoiceDuck(unsigned int id);
SndSidechainDuck *SND_GetCurrentVoiceDuck();
SndFutz *SND_GetFutz(unsigned int id);
SndCurve *SND_GetCurveByIndex(unsigned int i);
SndPan *SND_GetPanByIndex(int i);
int SND_FindContextIndex(unsigned int type);
char SND_IsValidContext(unsigned int type, unsigned int value);
int SND_GetDuckGroupIndex(unsigned int id);
SndMenuCategory SND_GroupCategory(unsigned int group);
double SND_GroupGetAttenuation(unsigned int group);

//#include "sound/snd_load_db.h"

//t6/code/src/sound/snd_local.cpp
int SNDL_Play(const char *a1, unsigned int aliasHash, int fadeTimeMs, float attenuation, SndEntHandle entHandle, const vec3_t *position, const vec3_t *direction, const vec3_t *notify, SndPlayback *playback, bool startPaused, float setScriptValues, float scriptPitch, float scriptPitchRate, float scriptAttenuation);
void StopSoundAliasesOnEnt(SndEntHandle sndEnt, unsigned int name);
void SNDL_StopSoundAliasOnEnt(SndEntHandle sndEnt, unsigned int name);
void SNDL_StopSoundsOnEnt(SndEntHandle sndEnt);
void SNDL_DisconnectListener(LocalClientNum_t localClientNum);
void SNDL_SetListener(LocalClientNum_t localClientNum, ClientNum_t clientNum, team_t team, const vec3_t *origin, const vec3_t *inAxis);
void SNDL_StopSounds(SndStopSoundFlags which);
void SNDL_FadeOut();
void SNDL_FadeIn();
void SNDL_SetEnvironmentEffects(int priority, unsigned int roomstring, float drylevel, float wetlevel, int fademsec);
void SNDL_DeactivateEnvironmentEffects(int priority, int fademsec);
void SNDL_SetPlaybackAttenuation(int playbackId, float attenuation);
void SNDL_SetPlaybackAttenuationRate(int playbackId, float rate);
void SNDL_SetPlaybackPitch(int playbackId, float pitch);
void SNDL_SetPlaybackPitchRate(int playbackId, float rate);
void SNDL_SetStartPaused(int playbackId, bool pause);
void SNDL_StopPlayback(int playbackId);
void SNDL_SetDuck(SndDuckCategoryType cat, unsigned int id, float amount);
void SNDL_SetSideChainDuck(unsigned int id);
void SNDL_SetScriptTimescale(float value);
void SNDL_PlayLoopAt(unsigned int id, const vec3_t *origin);
void SNDL_StopLoopAt(unsigned int id, const vec3_t *origin);
void SNDL_PlayLineAt(unsigned int id, const vec3_t *origin0, const vec3_t *origin1);
void SNDL_StopLineAt(unsigned int id, const vec3_t *origin0, const vec3_t *origin1);
void SNDL_UpdateStaticSounds(unsigned int a1, SndListener *listeners);
int SNDL_GetPlaybackTime(int playbackId);
void SNDL_GameReset(float a1);
void SNDL_SetContext(unsigned int type, unsigned int value);
void __cdecl SNDL_RestartDriver();
void SNDL_SetEntContext(SndEntHandle handle, unsigned int type, unsigned int value);
void SNDL_UpdateLoopingSounds(SndListener *a1);
void SNDL_SetMusicState(unsigned int id);
void SNDL_PrefetchLoadedAlias(unsigned int aliasId);
void SNDL_SetGlobalFutz(unsigned int id, SndCallLocation callLocation);
void SNDL_SetFrontendMusic(unsigned int musicAlias);
void SNDL_SetLoopState(SndEntHandle sndEnt, unsigned int alias, float attenuation, float attenuationRate, float pitch, float pitchRate);
void SNDL_PlayLoops(const char *a1, int count, const SndEntLoop *loops);
void SNDL_SetGameState(bool isMature, bool isPaused, float timescale, unsigned int cg_time, unsigned int seed, float voiceScale, float musicScale, float sfxScale, float masterScale, float cinematicScale, int masterPatch, bool hearingImpaired);

//t6/code/src/sound/snd_log.cpp
void SND_LogMissingAliasId(unsigned int hash);

//t6/code/src/sound/snd_occlusion.cpp
void SND_LosOcclusionUpdate();
void SND_LosOcclusionSync();
void SND_LosOcclusionFini();
double SND_TrimEnd(unsigned int a1, const char *debug, int *cache, const vec3_t *start, vec3_t *toEnd);
double SND_Trace(unsigned int a1, char *debug, int *trimCache, int *cache, float delta, const vec3_t *listener, const vec3_t *playback, vec3_t *toRight, int *totalTraces);
double SND_LosOcclusionTrace(unsigned int a1, int *ccache, int *lcache, int *rcache, int *ltcache, int *rtcache, const vec3_t *listener, const vec3_t *playback, int *totalTraces);
double SND_LosOcclusionTrace(bool fancy, int *cache, const vec3_t *listener, const vec3_t *playback);
void SND_LosOcclusionDoTraces(int a1, unsigned int traceCount, SndOcclusionTrace *traces, unsigned int traceSequence, int *totalTraces, int *voiceTraces);
void SND_LosOcclusionMultipleCmd(snd_occlusion_multiple *cmd);
int snd_occlusionCallback_Implementation(jqBatch *batch, void *data);
int snd_occlusionCallback(jqBatch *batch);

//t6/code/src/sound/snd_public_async.cpp
void SND_PlayInternal(unsigned int id, int fadeTimeMs, float attenuation, SndEntHandle entHandle, const vec3_t *position, const vec3_t *direction, bool notify, SndPlayback *playback, bool startPaused, bool setScriptValues, float scriptPitch, float scriptPitchRate, float scriptAttenuation, float scriptAttenuationRate);
void __cdecl SND_Play(unsigned int id, int fadeTimeMs, float attenuation, SndEntHandle entHandle, const vec3_t *position, const vec3_t *direction, SndPlayback *notify);
void __cdecl SND_Play(const char *alias, int fadeTimeMs, float attenuation, SndEntHandle entHandle, const vec3_t *position, const vec3_t *direction, SndPlayback *notify);
void SND_StopSoundAliasOnEnt(SndEntHandle ent, unsigned int alias_name);
void SND_StopSoundsOnEnt(SndEntHandle ent);
void SND_NotifyCinematicStart(float volume);
void SND_NotifyCinematicEnd();
void SND_DisconnectListener(LocalClientNum_t listener);
void SND_SetListener(LocalClientNum_t listener, ClientNum_t clientNum, team_t team, const vec3_t *origin, const vec3_t *axis);
void SND_FadeIn();
void SND_FadeOut();
void SND_SetEnvironmentEffects(int priority, const char *preset, float drylevel, float wetlevel, int fademsec);
void SND_DeactivateEnvironmentEffects(int priority, int fademsec);
void SND_SetPlaybackAttenuation(int id, float attenuation);
void SND_SetPlaybackAttenuationRate(int id, float rate);
void SND_SetPlaybackPitch(int playbackId, float pitch);
void SND_SetPlaybackPitchRate(int playbackId, float rate);
void SND_StopPlayback(int playbackId);
void SND_SetDuck(SndDuckCategoryType type, const char *name, float length, float amount);
void SND_SetSideChainDuck(const char *name);
void SND_SetEntState(SndEntHandle handle);
void SND_PlayLoopAt(unsigned int id, const vec3_t *origin);
void SND_StopLoopAt(unsigned int id, const vec3_t *origin);
void SND_PlayLineAt(unsigned int id, const vec3_t *origin0, const vec3_t *origin1);
void SND_StopLineAt(unsigned int id, const vec3_t *origin0, const vec3_t *origin1);
void SND_SetContext(const char *type, const char *value);
void SND_RestartDriver();
void SND_SetEntContext(SndEntHandle handle, const char *type, const char *value);
void SND_SetEntContext(SndEntHandle handle, const unsigned int type, const unsigned int value);
void SND_SetScriptTimescale(float value);
void SND_SetMusicState(const char *state);
void SND_AddBank(SndBank *bank);
void SND_AddPatch(SndPatch *patch);
void SND_AddGlobals(SndDriverGlobals *globals);
bool SND_WhizbyPath(const vec3_t *p1, const vec3_t *p2, const vec3_t *p3, float r, vec3_t *start, vec3_t *end);
void SND_Whizby(SndEntHandle sndEnt, const vec3_t *shotPosition, const vec3_t *shotDirection, const vec3_t *position, const vec3_t *center, const char *whizbySound, const bool isUnderwater, const char *crackSound);
SndEntState **SND_FindEntState(SndEntHandle handle, bool createNew);
void SNDL_SetEntState(SndEntHandle handle, const vec3_t *origin, const vec3_t *velocity, const vec3_t *orientation);
void SND_ResetEntState();
void __cdecl SND_ResetAliases();
void SND_SubtitleNotify(const char *subtitle, unsigned int lengthMs);
void SND_LengthNotify(unsigned int ent, unsigned int lengthMs);
void SND_FreePlaybackNotify(SndPlayback *playback);
void SND_BankLoadedNotify();
SndPlayback *SND_AllocatePlayback(unsigned int aliasId, SndEntHandle entHandle);
void SND_FreePlayback(SndPlayback *p);
SndPlayback *SND_FindPlayback(int playbackId);
bool SND_IsPlaying();
bool SND_GetKnownLength(int playbackId, int *msec);
int SND_Frame(float a1);
void updatesound_workerCallback_Implementation(jqBatch *,void *);
void SND_PossiblyUpdate(int minUpdateMs);
void SND_Update();
void SND_UpdateWait(void *notthis);
void SND_GameReset();
void SND_BeginFrame(bool isMature, bool isPaused, float timescale, unsigned int cgTime, unsigned int seed, float voiceScale, float musicScale, float sfxScale, float masterScale, float cinematicScale, int masterPatch, bool hearingImpaired);
void SND_SetFrontendMusic(const char *musicAlias);
void SND_SetLoopState(SndEntHandle ent, unsigned int alias, float attenuation, float attenuationRate, float pitch, float pitchRate);
void SND_PlayLoops(int count, const SndEntLoop *loops);
void SND_EndFrame();
void SND_Shutdown();
int __cdecl SND_PlaybackBundle(unsigned int alias, int fadeTimeMs, float attenuation, SndEntHandle entHandle, const vec3_t *position, const vec3_t *direction, SndPlayback *lengthNotify, bool startPaused, float scriptPitch, float scriptPitchRate, float scriptAttenuation);
int __cdecl SND_Playback(unsigned int alias, int fadeTimeMs, float attenuation, SndEntHandle entHandle, const vec3_t *position, const vec3_t *direction, SndPlayback *notify, bool startPaused);
int SND_Playback(const char *alias, int fadeTimeMs, float attenuation, int entHandle, const vec3_t *position, const vec3_t *direction, SndPlayback *notify, bool startPaused);
void SND_StopSounds(SndStopSoundFlags flags);
void SND_RemoveBank(SndBank *bank);
void SND_RemovePatch(SndPatch *patch);
void SND_RemoveGlobals(SndDriverGlobals *globals);
char SND_GetEntPosition(SndEntHandle handle, vec3_t *origin, vec3_t *velocity, vec3_t *orientation);
void SND_EntStateFrame();
int updatesound_workerCallback(jqBatch *batch);

//t6/code/src/sound/snd_public_async_q.cpp
SndCommand *SND_GetNewCommand();
void SND_CommandFreeBatch(SndCommand *start, SndCommand *end, int count);
void SND_CommandPush(SndCommand *cmd);
SndCommand *SND_CommandPeek();
void SND_CommandPop();
void SND_CommandProcess(const SndCommand *cmd);
SndNotify *SND_GetNewNotify();
void SND_NotifyFree(SndNotify *p);
void SND_NotifyProcess(const SndNotify *cmd);
void SND_NotifyPush(SndNotify *cmd);
SndNotify *SND_NotifyPeek();
void SND_NotifyPop();
void SND_NotifyPump();
bool SND_ShouldMuteAllSounds();
int SND_CommandPump(SndCommand *a1);

//t6/code/src/sound/snd_utils.cpp
unsigned int SND_GetSpeakerConfigCount(gjk_double_sphere_t *notthis);
SndSpeakerConfig *Snd_GetSpeakerConfig(unsigned int index);
int Snd_GetMixChannelCount(unsigned int speakerConfig);
double Snd_PanMono(float angle);
void SND_EqualPowerFadeCoefs(float t, float a, float *a3, float *b);
void SND_GetNearestPointOnSegment(const vec3_t *P, const vec3_t *segmentA, const vec3_t *segmentB, vec3_t *nearPoint);
void SND_GetNearestPointOnStrip(const vec3_t *point, const vec3_t *verts, unsigned int count, vec3_t *position);
const char *SND_GetAliasName(const SndAliasList *alias);
double SND_LinearToDbSpl(float linear);
int SND_HashName(const char *name);
void Snd_SpeakerMapZero(SndSpeakerMap *map);
int Snd_SpeakerMapGetIndex(const SndSpeakerMap *map, int in, int out);
double Snd_SpeakerMapGetVolume(const SndSpeakerMap *map, int in, int out);
double Snd_GetGlobalPriority(const SndAlias *alias, float volume);
double Snd_CurveEval(const SndCurve *curve, float x);
unsigned int SND_HashAlias(const SndAliasList *alias);
void Snd_PanStereo(float angle, float boost, float *left, float *right);
void Snd_Pan(const char *a1, unsigned int speakerCount, const float *angles, float toSound, float *levels);
void Snd_SpeakerMapSetVolume(SndSpeakerMap *map, int in, int out, float volume);
void SND_PanToSpeakermap11(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap12(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap16(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap18(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap21(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap22(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap26(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap28(const SndPan *pan, SndSpeakerMap *map);
void SND_PanToSpeakermap(SndSpeakerMap *a1, const SndPan *a2, unsigned int inputChannelCount, unsigned int outputChannelCount, const SndPan *pan, float centerSend, SndSpeakerMap *map);
void Snd_Pan3dFast(const vec3_t *position, const vec3_t *f, const vec3_t *listener, float centerSend, float lfeSend, float aliasOmni, SndSpeakerMap *pan);
double Snd_DistanceCurveEval(const SndCurve *minCurve, const SndCurve *curve, float minDist, float maxDist, float dist);
void SND_FixupStereoPan(SndSpeakerMap *pan);
void Snd_Pan3d(const SndSpeakerConfig *config, const vec3_t *position, const vec3_t *forward, const vec3_t *listener, float centerSend, float lfeSend, float aliasOmni, SndSpeakerMap *pan);

//#include "sound/snd_utils.h"

