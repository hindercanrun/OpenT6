#pragma once

#include "types.h"

//#include "database/db_assetlist_load.h"

//t6/code/src_noserver/database/db_assetnames.cpp
const char *DB_ImageGetName(const XAssetHeader *header);
void DB_ImageSetName(XAssetHeader *header, const char *name);
const char *DB_LocalizeEntryGetName(const XAssetHeader *header);
void DB_LocalizeEntrySetName(XAssetHeader *header, const char *name);
const char *DB_ZBarrierDefGetName(const XAssetHeader *header);
void DB_ZBarrierDefSetName(XAssetHeader *header, const char *name);
const char *DB_GetEmblemSetName();
const char *DB_GetXAssetHeaderName(int type, const XAssetHeader *header);
const char *DB_GetXAssetName(const XAsset *asset);
void DB_SetXAssetName(XAsset *asset, const char *name);
int DB_GetXAssetTypeSize(int type);
const char *DB_GetXAssetTypeName(int type);
// unsigned int bdLeagueSubdivisionResult::sizeOf(bdLeagueSubdivisionResult *notthis);
// unsigned int bdLeagueSubdivisionInfo::sizeOf(bdStatsInfo *notthis);
// int CCallback<CSteamAchievements,UserAchievementStored_t,0>::GetCallbackSizeBytes();
// unsigned int bdMatchMakingInfo::sizeOf(bdMatchMakingInfo *notthis);
// unsigned int bdBoolResult::sizeOf(bdYouTubeRegistrationResult *notthis);

//t6/code/src_noserver/database/db_auth_sha1.cpp
void SHA1_Transform(unsigned int *state, const unsigned __int8 *buffer);

//t6/code/src_noserver/database/db_file_load.cpp
void DB_Init_Reading();
double DB_GetLoadedFraction();
int DB_Reliable_FsOpen_ReadOnly(const char *path, unsigned int *outClumpSize);
void DB_FileReadCompletionCallback(int id, stream_status result, unsigned int numBytesRead, void *user);
void DB_SetZoneSizeLevelCount(int levelZoneCount);
void DB_ResetZoneSize(int trackLoadProgress);
bool DB_IsMinimumFastFileLoaded();
void DB_ResetMinimumFastFileLoaded();
int DB_ReadData();
void RecomputeLocks();
void DB_WaitXFileStage(int buffer_index);
void DB_CancelLoadXFile();
void DB_DecompressIOStream(DBDecompressCmd_t *cmd);
void DB_WaitWorkerCmd(DB_LOAD_STREAM *stream);
char TestBoundryCondition(unsigned __int8 *pos, int len);
void AdvanceRead(bool advance);
void CopyFromDecompressBufferNullTerminal(unsigned __int8 *pos, int *size_copied);
void DB_LoadXFileData(unsigned __int8 *pos, int size);
int DB_LoadXFileDataNullTerminated(unsigned __int8 *pos);
char *ValidateFileHeader(bool *fileIsSecure, int *fileVersion);
void DB_LoadedExternalData(int size);
int DB_DecompressIOStreamWorkerCallback(jqBatch *batch);
BOOL DB_LoadXFile(const char *path, int f, const char *filename, XBlock *blocks, void (*interrupt)(), unsigned __int8 *buf, int allocType, int flags, int requiredVersion, unsigned int desiredReadBytes);

//t6/code/src_noserver/database/db_gump.cpp
void DB_GumpPrint(const char *fmt, ...);
unsigned int DB_GumpSizeForBlockIndex(int bi);
unsigned int DB_GetGumpUnused(unsigned int budget);
void DB_GumpBeginAlloc(const char *name, unsigned int allocType, EMemTrack memTrack);
void DB_GumpEndAlloc(const char *name, unsigned int allocType);
unsigned __int8 *DB_GumpMemAlloc(unsigned int size, unsigned int blockIndex, unsigned int location, unsigned int allocType, const char *filename);
void DB_GumpMemFreeAll();
bool DB_GumpShouldFree(XBlock *blocks);
void DB_GumpMemFree(unsigned __int8 *data, unsigned int blockIndex);
char *DB_GetGumpZoneName(int flags);
int DB_AllocZoneForSlot(int slot);
void DB_FlushGump(int slot);
void DB_FlushGumps();
void DB_LoadGump(const char *fastfileName, unsigned int slot, int sync);

//t6/code/src_noserver/database/db_memory.cpp
void DB_InitFFOTDMem();
unsigned __int8 *DB_FFOTDMemAlloc(unsigned int size, unsigned int location, unsigned int allocType, const char *filename, int flags);
unsigned __int8 *DB_MemAlloc(unsigned int size, unsigned int location, unsigned int allocType, const char *filename, int flags);
void DB_GetMemoryBudgets(unsigned int *common, unsigned int *level, unsigned int *weapon);
unsigned int DB_GetLevelFree();
int DB_GetFactionFree();
void DB_UpdateUsage(XBlock *blocks, int flags, bool add);
void DB_AllocXBlocks(unsigned int *blockSize, const char *filename, XBlock *blocks, unsigned int allocType, int flags);
void DB_FreeXBlocks(const char *filename, XBlock *blocks, int flags);

//#include "database/db_primtypes_load.h"

//t6/code/src_noserver/database/db_registry.cpp
void TRACK_db_registry();
void DB_InitSingleton(void *pool, int size);
void DB_RemoveXModel(XAssetHeader header);
void DB_RemoveFX(XAssetHeader header);
void DB_RemoveMaterial(XAssetHeader header);
void DB_RemoveTechniqueSet(XAssetHeader header);
void DB_RemoveImage(XAssetHeader header);
void DB_RemoveSound(XAssetHeader header);
void DB_RemoveSndDriverGlobals(XAssetHeader header);
void DB_RemoveSoundPatch(XAssetHeader header);
void __cdecl DB_RemoveClipMap();
void __cdecl DB_RemoveComWorld();
void __cdecl DB_RemoveGfxWorld();
void DB_DynamicCloneMenu(const XAssetHeader from, XAssetHeader to, DBCloneMethod cloneMethod);
void DB_RemoveKeyValuePairs(XAssetHeader header);
char DB_CompareReorderEntries(const DBReorderAssetEntry *e0, const DBReorderAssetEntry *e1);
void DB_SetReorderIncludeSequence();
void DB_AddReorderAsset(const char *typeString, const char *assetName);
char DB_NextZoneCsvToken(const char **parse, char *token, unsigned int tokenSize, bool allowNewLine);
void DB_BeginReorderZone(const char *zoneName);
void DB_PrintAssetName(XAssetHeader header, void *data);
void DB_MarkAssetTypeUsageDirty();
void DB_GetAssetTypeUsageInfo(XAssetType assetType, const char **outName, int *outUsed, int *outPool);
void DB_PrintXAssetsForType_FastFile(XAssetType type, void *inData, bool includeOverride);
XAssetHeader DB_AllocXAssetSingleton(void* pool);
template <typename T>
XAssetHeader DB_AllocXAsset(void* pool);
template <typename T>
void DB_InitPool(void* pool, int size);
XAssetHeader DB_AllocXAssetHeader(XAssetType type);
void DB_Init();
XAssetEntry *DB_AllocXAssetEntry(XAssetType type, unsigned int zoneIndex);
void DB_FreeXAssetEntry(XAssetEntry *assetEntry);
void DB_LogMissingAsset(int a1, XAssetType type, const char *name);
void DB_EnumXAssets_FastFile(XAssetType type, void (*func)(XAssetHeader, void *), void *inData, bool includeOverride);
char DB_EnumXAssetsTimeout_FastFile(XAssetType type, void (*func)(XAssetHeader, void *), void *inData, bool includeOverride, int msec);
void DB_LoadDelayedImages();
void DB_CloneXAsset(const XAsset *from, XAsset *to, DBCloneMethod cloneMethod);
void DB_SwapXAsset(const XAsset *from, XAsset *to);
void DB_DelayedCloneXAsset(XAssetEntry *newEntry);
XAssetEntry *DB_FindXAssetEntry(XAssetType type, const char *name);
XAssetHeader DB_FindXAssetDefaultHeaderInternal(XAssetType type);
XAssetEntry *DB_CreateDefaultEntry(XAssetType type, const char *name);
void DB_ListDefaultEntries_f();
void DB_ListAssetPool(XAssetType type);
void DB_ListAssetPool_f();
void DB_DumpMaterialList_f();
void DB_DumpModels_f();
bool IsConfigFile(const char *name);
void PrintWaitedError(XAssetType type, const char *name, int waitedMsec);
bool DB_DoesXAssetExist(XAssetType type, const char* name);
bool DB_DoesXAssetExist(const char *typeName, const char *name);
void DB_SetInitializing(bool inUse);
bool DB_IsXAssetDefault(XAssetType a1, XAssetType type, const char *name);
int DB_GetAllXAssetOfType_FastFile(XAssetType type, XAssetHeader *assets, int maxCount);
void DB_SyncLostDevice();
int DB_GetZonePriority(int zone);
int DB_OverrideAsset(unsigned int newZoneIndex, unsigned int existingZoneIndex, XAssetType type);
XAssetEntry *DB_LinkXAssetEntry(XAssetEntry *newEntry, int allowOverride);
void DB_EnableInUseCache(unsigned __int16 *data);
void DB_GetXAsset(XAssetType type, XAssetHeader header);
void DB_BuildOSPath(const char *zoneName, const char *ext, int size, char *filename);
void DB_BuildOSPath_FromSource(const char *zoneName, FF_DIR source, int size, char *filename);
void DB_LoadXZone(XZoneInfo *zoneInfo, unsigned int zoneCount);
int DB_PostLoadPerXZone();
void DB_UpdateDebugZone();
void DB_LoadZone_f();
char DB_IsZoneLoaded(const char *name);
bool DB_IsZoneTypeLoading(int zoneType);
char DB_IsZoneTypeLoaded(int zoneType);
char DB_IsZoneTypeComplete(int zoneType);
char DB_ZoneLoadsOverlays(const char *zoneName);
char DB_CompareLoadXZoneInfos(const XZoneInfo *zone0, const XZoneInfo *zone1);
int DB_TryLoadXFileInternal(const char *zoneName, int zoneFlags, int requiredVersion, const char *contentDir);
void DB_InitFastFileNames();
void DB_UnloadXZoneInternal(unsigned int zoneIndex, bool createDefault);
void DB_UnloadXZoneMemory(XZone *zone);
void DB_FreeDefaultEntries();
void DB_ReleaseXAssets();
void DB_UnloadXAssetsMemory(XZone *zone);
void DB_UnloadXAssetsMemoryForZone(int zoneFreeFlags, int zoneFreeBit);
char DB_ArchiveAssets();
void DB_FreeUnusedResources(int fast_free);
char DB_UnarchiveAssets();
void DB_Cleanup();
// XAssetPoolEntry<GfxImage> *DB_GetImageAtIndex(unsigned int index);
unsigned int DB_GetImagePartPoolSize();
GfxStreamedPartInfo *DB_GetImagePartAtIndex(unsigned int index);
char *DB_ReferencedFFChecksums();
char *DB_ReferencedFFNameList();
char DB_FileExists(FF_DIR a1, const char *zoneName, FF_DIR source);
unsigned int DB_GetGfxWorldChecksum();

//auto generated during compile
void Load_PhysPresetAsset(PhysPreset **physPreset);
void Mark_PhysPresetAsset(PhysPreset *physPreset);

void Load_PhysConstraintsAsset(PhysConstraints **physConstraints);
void Mark_PhysConstraintsAsset(PhysConstraints *physConstraints);

void Load_DestructibleDefAsset(DestructibleDef **destructibleDef);
void Mark_DestructibleDefAsset(DestructibleDef *destructibleDef);

void Load_XAnimPartsAsset(XAnimParts **parts);
void Mark_XAnimPartsAsset(XAnimParts *parts);

void Load_XModelAsset(XModel **model);
void Mark_XModelAsset(XModel *model);

void Load_MaterialAsset(Material **material);
void Mark_MaterialAsset(Material *material);

void Load_MaterialTechniqueSetAsset(MaterialTechniqueSet **techniqueSet);
void Mark_MaterialTechniqueSetAsset(MaterialTechniqueSet *techniqueSet);

void Load_GfxImageAsset(GfxImage **image);
void Mark_GfxImageAsset(GfxImage *image);

void Load_SndBankAsset(SndBank **sound);
void Mark_SndBankAsset(SndBank *sound);

void Load_SndDriverGlobalsAsset(SndDriverGlobals **sndDriverGlobals);
void Mark_SndDriverGlobalsAsset(SndDriverGlobals *sndDriverGlobals);

void Load_SndPatchAsset(SndPatch **soundPatch);
void Mark_SndPatchAsset(SndPatch *soundPatch);

void Load_ClipMapAsset(clipMap_t **clipMap);
void Mark_ClipMapAsset(clipMap_t *clipMap);

void Load_ComWorldAsset(ComWorld **comWorld);
void Mark_ComWorldAsset(ComWorld *comWorld);

void Load_GameWorldSpAsset(GameWorldSp **gameWorldSp);
void Mark_GameWorldSpAsset(GameWorldSp *gameWorldSp);

void Load_GameWorldMpAsset(GameWorldMp **gameWorldMp);
void Mark_GameWorldMpAsset(GameWorldMp *gameWorldMp);

void Load_MapEntsAsset(MapEnts **mapEnts);
void Mark_MapEntsAsset(MapEnts *mapEnts);

void Load_DDLAsset(ddlRoot_t **ddlRoot);
void Mark_DDLAsset(ddlRoot_t *ddlRoot);

void Load_GfxWorldAsset(GfxWorld **gfxWorld);
void Mark_GfxWorldAsset(GfxWorld *gfxWorld);

void Load_LightDefAsset(GfxLightDef **lightDef);
void Mark_LightDefAsset(GfxLightDef *lightDef);

void Load_FontAsset(Font_s **font);
void Mark_FontAsset(Font_s *font);

void Load_FontIconAsset(FontIcon **fontIcon);
void Mark_FontIconAsset(FontIcon *fontIcon);

void Load_MenuListAsset(MenuList **menuList);
void Mark_MenuListAsset(MenuList *menuList);

void Load_MenuAsset(menuDef_t **menu);
void Mark_MenuAsset(menuDef_t *menu);

void Load_LocalizeEntryAsset(LocalizeEntry **localize);
void Mark_LocalizeEntryAsset(LocalizeEntry *localize);

void Load_WeaponVariantDefAsset(WeaponVariantDef **weapon);
void Mark_WeaponVariantDefAsset(WeaponVariantDef *weapon);

void Load_WeaponAttachmentAsset(WeaponAttachment **attachment);
void Mark_WeaponAttachmentAsset(WeaponAttachment *attachment);

void Load_WeaponAttachmentUniqueAsset(WeaponAttachmentUnique **attachmentUnique);
void Mark_WeaponAttachmentUniqueAsset(WeaponAttachmentUnique *attachmentUnique);

void Load_WeaponCamoAsset(WeaponCamo **weaponCamo);
void Mark_WeaponCamoAsset(WeaponCamo *weaponCamo);

void Load_FxEffectDefAsset(const FxEffectDef **fx);
void Mark_FxEffectDefAsset(FxEffectDef *fx);

void Load_FxImpactTableAsset(FxImpactTable **impactFx);
void Mark_FxImpactTableAsset(FxImpactTable *impactFx);

void Load_RawFileAsset(RawFile **rawfile);
void Mark_RawFileAsset(RawFile *rawfile);

void Load_StringTableAsset(StringTable **stringTable);
void Mark_StringTableAsset(StringTable *stringTable);

void Load_LeaderboardDefAsset(LeaderboardDef **leaderboardDef);
void Mark_LeaderboardDefAsset(LeaderboardDef *leaderboardDef);

void Load_XGlobalsAsset(XGlobals **xGlobals);
void Mark_XGlobalsAsset(XGlobals *xGlobals);

void Load_GlassesAsset(Glasses **glasses);
void Mark_GlassesAsset(Glasses *glasses);

void Load_EmblemSetAsset(EmblemSet **emblemSet);
void Mark_EmblemSetAsset(EmblemSet *emblemSet);

void Load_ScriptParseTreeAsset(ScriptParseTree **scriptParseTree);
void Mark_ScriptParseTreeAsset(ScriptParseTree *scriptParseTree);

void Load_QdbAsset(Qdb **qdb);
void Mark_QdbAsset(Qdb *qdb);

void Load_SlugAsset(Slug **slug);
void Mark_SlugAsset(Slug *slug);

void Load_KeyValuePairsAsset(KeyValuePairs **keyValuePairs);
void Mark_KeyValuePairsAsset(KeyValuePairs *keyValuePairs);

void Load_VehicleDefAsset(VehicleDef **vehicleDef);
void Mark_VehicleDefAsset(VehicleDef *vehicleDef);

void Load_MemoryBlockAsset(MemoryBlock **memoryBlock);
void Mark_MemoryBlockAsset(MemoryBlock *memoryBlock);

void Load_AddonMapEntsAsset(AddonMapEnts **addonMapEnts);
void Mark_AddonMapEntsAsset(AddonMapEnts *addonMapEnts);

void Load_TracerDefAsset(TracerDef **tracerDef);
void Mark_TracerDefAsset(TracerDef *tracerDef);

void Load_SkinnedVertsDefAsset(SkinnedVertsDef **skinnedVertsDef);
void Mark_SkinnedVertsDefAsset(SkinnedVertsDef *skinnedVertsDef);

void Load_FootstepTableDefAsset(FootstepTableDef **footstepTableDef);
void Mark_FootstepTableDefAsset(FootstepTableDef *footstepTableDef);

void Load_FootstepFXTableDefAsset(FootstepFXTableDef **footstepFXTableDef);
void Mark_FootstepFXTableDefAsset(FootstepFXTableDef *footstepFXTableDef);

void Load_ZBarrierDefAsset(ZBarrierDef **zbarrierDef);
void Mark_ZBarrierDefAsset(ZBarrierDef *zbarrierDef);


XAssetHeader DB_AllocMaterial(void *pool);
XAssetHeader DB_AllocGfxImage(void *pool);
void DB_FreeMaterial(void *pool, XAssetHeader header);
void DB_FreeMenu(void *pool, XAssetHeader header);
void DB_FreeXGlobals(void *pool, XAssetHeader header);
char DB_PostLoadXZone();
void DB_SyncXAssets();
void DB_ShutdownXAssets();
void DB_Update();
void DB_EndReorderZone();
bool DB_RegisterAllReorderAssetsOfType(int type, XAssetEntry *assetEntry);
void DB_RegisteredReorderAsset(int type, const char *assetName, XAssetEntry *assetEntry);
XAssetHeader DB_FindXAssetHeader(XAssetType type, const char *name, bool errorIfMissing, int waitTime);
void DB_LoadXAssets(XZoneInfo *zoneInfo, unsigned int zoneCount, int sync);
void DB_Thread(unsigned int threadContext);
void DB_InitThread();
void DB_ReplaceModel(const char *original, const char *replacement);
void DB_LoadGraphicsAssetsForPC();
void DB_InitFrontendXAssets(bool uiOnly);
void Load_FxEffectDefFromName(const char **name);
void DB_LoadLoadFastfilesForNewContent();

//#include "database/db_registry.h"

//t6/code/src_noserver/database/db_stream.cpp
void DB_InitStreams(XBlock *blocks);
void DB_PushStreamPos(unsigned int index);
void DB_PopStreamPos();
unsigned __int8 *DB_GetStreamPos();
unsigned __int8 *DB_AllocStreamPos(int alignment);
void DB_IncStreamPos(int size);
const void **DB_InsertPointer();

//t6/code/src_noserver/database/db_stream_load.cpp
bool Load_Stream(bool atStreamStart, const void *ptr, int size);
void Load_DelayStream();
void DB_ConvertOffsetToAlias(void *data);
void DB_ConvertOffsetToPointer(void *data);
void Load_XStringCustom(const char **str);
void Load_TempStringCustom(const char **str);

//t6/code/src_noserver/database/db_stringtable_load.cpp
void Load_ScriptStringCustom(unsigned __int16 *var);
void Mark_ScriptStringCustom(unsigned __int16 *var);

