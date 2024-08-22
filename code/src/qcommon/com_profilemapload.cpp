#include "types.h"
#include "vars.h"
#include <qcommon/qcommon_public.h>
#include <ui/ui_public.h>

#define PROFLOAD_ENTRY_COUNT 384

static mapLoadProfile_t mapLoadProfile;

/*
==============
TRACK_com_profilemapload
==============
*/
void TRACK_com_profilemapload()
{
	track_static_alloc_internal(&mapLoadProfile, 43136, "mapLoadProfile", 0);
}

/*
==============
ProfLoad_IsActive
==============
*/
bool ProfLoad_IsActive()
{
	return mapLoadProfile.isLoading;
}

/*
==============
ProfLoad_BeginTrackedValueTicks
==============
*/
void ProfLoad_BeginTrackedValueTicks(MapProfileElement *value, unsigned __int64 ticks)
{
	assert(!value->ticksStart);
	value->ticksStart = ticks;
}

/*
==============
ProfLoad_BeginTrackedValue
==============
*/
void ProfLoad_BeginTrackedValue(MapProfileTrackedValue type)
{
	LARGE_INTEGER PerformanceCount;
	MapProfileEntry* entry;
	unsigned __int64 ticks;

	if (mapLoadProfile.isLoading && mapLoadProfile.currentEntry && Sys_IsMainThread())
	{
		QueryPerformanceCounter(&PerformanceCount);
		ticks = PerformanceCount.QuadPart;
		ProfLoad_BeginTrackedValueTicks(&mapLoadProfile.elements[type], PerformanceCount.QuadPart);
		++mapLoadProfile.elementAccessCount[type];

		for (entry = mapLoadProfile.currentEntry; entry; entry = entry->parent)
		{
			ProfLoad_BeginTrackedValueTicks(&entry->elements[type], ticks);
		}
	}
}

/*
==============
ProfLoad_EndTrackedValueTicks
==============
*/
void ProfLoad_EndTrackedValueTicks(MapProfileElement *value, unsigned __int64 ticks)
{
	assert(value->ticksStart != 0);
	value->ticksTotal += ticks - value->ticksStart;
	value->ticksStart = 0;
}

/*
==============
ProfLoad_EndTrackedValue
==============
*/
void ProfLoad_EndTrackedValue(MapProfileTrackedValue type)
{
	LARGE_INTEGER PerformanceCount;
	MapProfileEntry* entry;
	unsigned __int64 ticks;

	if (mapLoadProfile.isLoading && mapLoadProfile.currentEntry && Sys_IsMainThread())
	{
		QueryPerformanceCounter(&PerformanceCount);
		ticks = PerformanceCount.QuadPart;
		ProfLoad_EndTrackedValueTicks(&mapLoadProfile.elements[type], PerformanceCount.QuadPart);
		for (entry = mapLoadProfile.currentEntry; entry; entry = entry->parent)
		{
			ProfLoad_EndTrackedValueTicks(&entry->elements[type], ticks);
		}
	}
}

/*
==============
ProfLoad_Init
==============
*/
void ProfLoad_Init()
{
	com_profileLoading = _Dvar_RegisterBool("profile_show_loading", 0, 0, "Show map load profiler");
	mapLoadProfile.isLoading = 0;
}

/*
==============
ProfLoad_Activate
==============
*/
void ProfLoad_Activate()
{
	LARGE_INTEGER PerformanceCount;

	assert(mapLoadProfile.isLoading == false);
	memset(&mapLoadProfile, 0, 0xA880u);
	mapLoadProfile.isLoading = 1;
	QueryPerformanceCounter(&PerformanceCount);
	mapLoadProfile.ticksStart = PerformanceCount.QuadPart;
	mapLoadProfile.ticksFinish = PerformanceCount.QuadPart;
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6Activating map load profiler\n");
}

/*
==============
Com_GetEntryForNewLabel
==============
*/
MapProfileEntry *Com_GetEntryForNewLabel(const char *label)
{
	int entryIndex;
	int firstEntry;

	if (mapLoadProfile.currentEntry)
	{
		firstEntry = mapLoadProfile.currentEntry - mapLoadProfile.profileEntries + 1;
	}
	else
	{
		firstEntry = 0;
	}

	for (entryIndex = firstEntry; entryIndex < mapLoadProfile.profileEntryCount; ++entryIndex)
	{
		if (mapLoadProfile.profileEntries[entryIndex].parent == mapLoadProfile.currentEntry
			&& mapLoadProfile.profileEntries[entryIndex].label == label)
		{
			return &mapLoadProfile.profileEntries[entryIndex];
		}
	}

	assert(mapLoadProfile.profileEntryCount < PROFLOAD_ENTRY_COUNT);
	return &mapLoadProfile.profileEntries[mapLoadProfile.profileEntryCount++];
}

/*
==============
ProfLoad_CalculateSelfTicks
==============
*/
void ProfLoad_CalculateSelfTicks()
{
	// straight from IDA, I don't feel like dealing this this right now.

	int profileEntryCount; // edx
	int v1; // ecx
	unsigned __int64* p_ticksSelf; // eax
	int v3; // esi
	unsigned __int64* p_ticksTotal; // ecx
	DWORD* v5; // eax
	bool v6; // cf
	unsigned int v7; // edx
	unsigned int v8; // edx
	unsigned int v9; // edx

	profileEntryCount = mapLoadProfile.profileEntryCount;
	v1 = 0;
	if (mapLoadProfile.profileEntryCount > 0)
	{
		p_ticksSelf = &mapLoadProfile.profileEntries[0].ticksSelf;
		do
		{
			*(DWORD*)p_ticksSelf = *((DWORD*)p_ticksSelf - 2);
			*((DWORD*)p_ticksSelf + 1) = *((DWORD*)p_ticksSelf - 1);
			*((DWORD*)p_ticksSelf + 8) = *((DWORD*)p_ticksSelf + 6);
			*((DWORD*)p_ticksSelf + 9) = *((DWORD*)p_ticksSelf + 7);
			*((DWORD*)p_ticksSelf + 14) = *((DWORD*)p_ticksSelf + 12);
			*((DWORD*)p_ticksSelf + 15) = *((DWORD*)p_ticksSelf + 13);
			*((DWORD*)p_ticksSelf + 20) = *((DWORD*)p_ticksSelf + 18);
			*((DWORD*)p_ticksSelf + 21) = *((DWORD*)p_ticksSelf + 19);
			profileEntryCount = mapLoadProfile.profileEntryCount;
			++v1;
			p_ticksSelf += 14;
		} while (v1 < mapLoadProfile.profileEntryCount);
	}
	v3 = 0;
	if (profileEntryCount > 0)
	{
		p_ticksTotal = &mapLoadProfile.profileEntries[0].ticksTotal;
		do
		{
			v5 = (DWORD*)*((DWORD*)p_ticksTotal + 5);
			if (v5)
			{
				v6 = v5[6] < *(DWORD*)p_ticksTotal;
				v5[6] -= *(DWORD*)p_ticksTotal;
				v5[7] -= v6 + *((DWORD*)p_ticksTotal + 1);
				v7 = *((DWORD*)p_ticksTotal + 8);
				v6 = v5[14] < v7;
				v5[14] -= v7;
				v5[15] -= v6 + *((DWORD*)p_ticksTotal + 9);
				v8 = *((DWORD*)p_ticksTotal + 14);
				v6 = v5[20] < v8;
				v5[20] -= v8;
				v5[21] -= v6 + *((DWORD*)p_ticksTotal + 15);
				v9 = *((DWORD*)p_ticksTotal + 20);
				v6 = v5[26] < v9;
				v5[26] -= v9;
				v5[27] -= v6 + *((DWORD*)p_ticksTotal + 21);
				profileEntryCount = mapLoadProfile.profileEntryCount;
			}
			++v3;
			p_ticksTotal += 14;
		} while (v3 < profileEntryCount);
	}
}

/*
==============
ProfLoad_GetEntryRowText
==============
*/
void ProfLoad_GetEntryRowText(const MapProfileEntry *entry, char *rowText, int sizeofRowText)
{
	Com_sprintf(rowText, sizeofRowText, "%s - %5.3f total, %5.3f self, %5.3f file, %i hits", entry->label, (0.001000000047497451 * (msecPerRawTimerTick * entry->ticksTotal)), (entry->ticksSelf * msecPerRawTimerTick * 0.001000000047497451), ((entry->elements[0].ticksSelf + entry->elements[1].ticksSelf + entry->elements[2].ticksSelf) * msecPerRawTimerTick * 0.001000000047497451), entry->accessCount);
}

/*
==============
ProfLoad_PrintTree
==============
*/
void ProfLoad_PrintTree()
{
	int v0; // edi
	const char** v1; // esi
	char rowText[256]; // [esp+58h] [ebp-104h] BYREF

	v0 = 0;
	if (mapLoadProfile.profileEntryCount > 0)
	{
		v1 = (const char**)(&mapLoadProfile + 112);
		do
		{
			Com_sprintf(rowText, 256, "%s - %5.3f total, %5.3f self, %5.3f file, %i hits", *(v1 - 26), (double)(0.001000000047497451 * (msecPerRawTimerTick * (double)*((unsigned __int64*)v1 - 11))), (double)((double)*((unsigned __int64*)v1 - 10) * msecPerRawTimerTick * 0.001000000047497451), (double)((double)(unsigned __int64)(*(__int64*)v1 + *((__int64*)v1 - 3) + *((__int64*)v1 - 6)) * msecPerRawTimerTick * 0.001000000047497451), *(v1 - 25));
			Com_Printf(CON_CHANNEL_PERFORMANCE, "^6%*c %s\n", 2 * (DWORD) * (v1 - 18) + 1, 32, rowText);
			++v0;
			v1 += 28;
		} while (v0 < mapLoadProfile.profileEntryCount);
	}
}

/*
==============
ProfLoad_CompareHotSpotNames
==============
*/
BOOL ProfLoad_CompareHotSpotNames(const MapProfileHotSpot *hotSpot0, const MapProfileHotSpot *hotSpot1)
{
	return hotSpot1->label < hotSpot0->label;
}

/*
==============
ProfLoad_CompareHotSpotTicks
==============
*/
BOOL ProfLoad_CompareHotSpotTicks(const MapProfileHotSpot *hotSpot0, const MapProfileHotSpot *hotSpot1)
{
	return hotSpot0->ticksSelf > hotSpot1->ticksSelf;
}

/*
==============
ProfLoad_Begin
==============
*/
void ProfLoad_Begin(const char *label)
{
	LARGE_INTEGER PerformanceCount;
	MapProfileEntry* entry;

	if (mapLoadProfile.isLoading && Sys_IsMainThread())
	{
		entry = Com_GetEntryForNewLabel(label);
		++entry->accessCount;
		entry->parent = mapLoadProfile.currentEntry;
		if (entry->parent)
		{
			entry->indent = entry->parent->indent + 1;
		}
		else
		{
			entry->indent = 0;
		}

		mapLoadProfile.currentEntry = entry;
		QueryPerformanceCounter(&PerformanceCount);
		entry->ticksStart = PerformanceCount.QuadPart;
		entry->label = label;
	}
}

/*
==============
ProfLoad_End
==============
*/
void ProfLoad_End()
{
	LARGE_INTEGER PerformanceCount;
	MapProfileEntry* entry;
	unsigned __int64 timeStepInTicks;
	unsigned __int64 currentTimeInTicks;

	if (mapLoadProfile.isLoading && Sys_IsMainThread())
	{
		entry = mapLoadProfile.currentEntry;
		assert(entry);
		assert(entry->label);
		QueryPerformanceCounter(&PerformanceCount);
		currentTimeInTicks = PerformanceCount.QuadPart;
		mapLoadProfile.ticksFinish = currentTimeInTicks;
		timeStepInTicks = currentTimeInTicks - entry->ticksStart;
		entry->ticksTotal += timeStepInTicks;
		if (!entry->parent)
		{
			mapLoadProfile.ticksProfiled += timeStepInTicks;
		}
		mapLoadProfile.currentEntry = entry->parent;
	}
}

const vec4_t PROFLOAD_TEXT_COLOR = { { 0.0, 1.0, 0.0, 1.0 } };

/*
==============
ProfLoad_DrawTree
==============
*/
void ProfLoad_DrawTree()
{
	float textx;
	float texty;
	MapProfileEntry* currEntry;
	Font_s* profileFont;
	char rowText[256];
	int profileEntry;

	ProfLoad_CalculateSelfTicks();
	profileFont = UI_GetFontHandle(&scrPlaceFull, 0, 0.36000001);
	profileEntry = (mapLoadProfile.profileEntryCount - 16) & ((mapLoadProfile.profileEntryCount - 16 <= 0) - 1);
	if (profileEntry < mapLoadProfile.profileEntryCount)
	{
		texty = 70;
		currEntry = &mapLoadProfile.profileEntries[profileEntry];
		for (profileEntry; profileEntry < mapLoadProfile.profileEntryCount; texty += 16, ++profileEntry, ++currEntry)
		{
			textx = (5 * currEntry->indent + 60);
			ProfLoad_GetEntryRowText(currEntry, rowText, 256);
			UI_DrawText(&scrPlaceFull, rowText, 256, profileFont, textx, texty, 0, 0, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);

		}
	}
}

const vec4_t PROFLOAD_BACKGROUND_COLOR = { { 0.0, 0.0, 0.0, 0.80000001 } };

/*
==============
ProfLoad_DrawOverlay
==============
*/
void ProfLoad_DrawOverlay(rectDef_s *rect)
{
	Font_s* FontHandle;
	int fileOpenCount;
	int fileSeekCount;
	int fileReadCount;
	char line[256];

	if (Dvar_GetBool(com_profileLoading))
	{
		FontHandle = UI_GetFontHandle(&scrPlaceFull, 0, 0.36000001);
		UI_FillRect(&scrPlaceFull, rect->x, rect->y, rect->w, rect->h, rect->horzAlign, rect->vertAlign, &PROFLOAD_BACKGROUND_COLOR);
		ProfLoad_DrawTree();
		fileSeekCount = mapLoadProfile.elementAccessCount[1];
		fileOpenCount = mapLoadProfile.elementAccessCount[0];
		fileReadCount = mapLoadProfile.elementAccessCount[2];
		sprintf(line, "Total Load Time: %5.4f", ((mapLoadProfile.ticksFinish - mapLoadProfile.ticksStart) * msecPerRawTimerTick * 0.001000000047497451));
		UI_DrawText(&scrPlaceFull, line, 256, FontHandle, 60.0, 395.0, rect->horzAlign, rect->vertAlign, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);
		sprintf(line, "File Open Time: %5.4f, Accessed %d times", (mapLoadProfile.elements[0].ticksTotal * msecPerRawTimerTick * 0.001000000047497451), fileOpenCount);
		UI_DrawText(&scrPlaceFull, line, 256, FontHandle, 250.0, 395.0, rect->horzAlign, rect->vertAlign, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);
		sprintf(line, "Profiled Time: %5.4f", (mapLoadProfile.ticksProfiled * msecPerRawTimerTick * 0.001000000047497451));
		UI_DrawText(&scrPlaceFull, line, 256, FontHandle, 60.0, 410.0, rect->horzAlign, rect->vertAlign, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);
		sprintf(line, "File Seek Time: %5.4f, Accessed %d times", (mapLoadProfile.elements[1].ticksTotal * msecPerRawTimerTick * 0.001000000047497451), fileSeekCount);
		UI_DrawText(&scrPlaceFull, line, 256, FontHandle, 250.0, 410.0, rect->horzAlign, rect->vertAlign, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);
		sprintf(line, "Unprofiled Time: %5.4f", ((mapLoadProfile.ticksFinish - mapLoadProfile.ticksProfiled - mapLoadProfile.ticksStart) * msecPerRawTimerTick * 0.001000000047497451));
		UI_DrawText(&scrPlaceFull, line, 256, FontHandle, 60.0, 425.0, rect->horzAlign, rect->vertAlign, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);
		sprintf(line, "File Read Time: %5.4f, Accessed %d times", (mapLoadProfile.elements[2].ticksTotal * msecPerRawTimerTick * 0.001000000047497451), fileReadCount);
		UI_DrawText(&scrPlaceFull, line, 256, FontHandle, 250.0, 425.0, rect->horzAlign, rect->vertAlign, 0.36000001, &PROFLOAD_TEXT_COLOR, 0, LOCAL_CLIENT_FIRST);
	}
}

/*
==============
ProfLoad_PrintHotSpots
==============
*/
void ProfLoad_PrintHotSpots()
{
	// deal with this later
	int profileEntryCount; // edx
	int *p_accessCount; // ecx
	unsigned __int64 *p_ticksSelf; // eax
	int v3; // esi
	unsigned int v4; // ebx
	MapProfileHotSpot *v5; // esi
	unsigned int v6; // edx
	int v7; // esi
	int v8; // edi
	int v9; // edx
	int *v10; // eax
	MapProfileHotSpot *v11; // ecx
	int *v12; // ecx
	int v13; // ebx
	bool v14; // cf
	int v15; // ebx
	__int64 *p_ticksFile; // esi
	long double v17; // [esp+20h] [ebp-2444h]
	long double v18; // [esp+28h] [ebp-243Ch]
	double v19; // [esp+50h] [ebp-2414h]
	double v20; // [esp+58h] [ebp-240Ch]
	MapProfileHotSpot _First[384]; // [esp+60h] [ebp-2404h] BYREF

	profileEntryCount = mapLoadProfile.profileEntryCount;
	if ( mapLoadProfile.profileEntryCount > 0 )
	{
		p_accessCount = &_First[0].accessCount;
		p_ticksSelf = &mapLoadProfile.profileEntries[0].ticksSelf;
		v3 = mapLoadProfile.profileEntryCount;
		do
		{
			v4 = *(p_ticksSelf + 21);
			*(p_accessCount - 1) = *(p_ticksSelf - 6);
			*p_accessCount = *(p_ticksSelf - 5);
			p_accessCount[1] = *p_ticksSelf;
			p_accessCount[2] = *(p_ticksSelf + 1);
			*(p_accessCount + 3) = p_ticksSelf[4] + p_ticksSelf[7] + __PAIR64__(v4, *(p_ticksSelf + 20));
			p_ticksSelf += 14;
			p_accessCount += 6;
			--v3;
		}
		while ( v3 );
	}
	v5 = &_First[profileEntryCount];
	v6 = ((17179869192i64 * profileEntryCount) >> 32) >> 2;
	std::_Sort<MapProfileHotSpot *,int,bool (__cdecl *)(MapProfileHotSpot const &,MapProfileHotSpot const &)>(
		_First,
		v5,
		v6 + (v6 >> 31),
		ProfLoad_CompareHotSpotNames);
	v7 = mapLoadProfile.profileEntryCount;
	v8 = 0;
	v9 = 0;
	if ( mapLoadProfile.profileEntryCount )
	{
		v10 = &_First[0].accessCount;
		do
		{
			v11 = &_First[v9];
			*(v10 - 1) = *&v11->label;
			*(v10 + 1) = v11->ticksSelf;
			++v9;
			*(v10 + 3) = v11->ticksFile;
			if ( v9 != v7 )
			{
				v12 = &_First[v9].accessCount;
				do
				{
					if ( *(v12 - 1) != *(v10 - 1) )
						break;
					*v10 += *v12;
					v13 = v12[1];
					v14 = __CFADD__(v13, v10[1]);
					v10[1] += v13;
					v10[2] += v12[2] + v14;
					v15 = v12[3];
					v14 = __CFADD__(v15, v10[3]);
					v10[3] += v15;
					v10[4] += v12[4] + v14;
					++v9;
					v12 += 6;
				}
				while ( v9 != v7 );
			}
			++v8;
			v10 += 6;
		}
		while ( v9 != v7 );
	}
	std::_Sort<MapProfileHotSpot *,int,bool (__cdecl *)(MapProfileHotSpot const &,MapProfileHotSpot const &)>(
		_First,
		&_First[v8],
		24 * v8 / 24,
		ProfLoad_CompareHotSpotTicks);
	Com_Printf(23, "\n\n");
	Com_Printf(23, "^6---------- Load time hot spots ----------\n");
	if ( v8 > 16 )
		v8 = 16;
	v20 = 0.0;
	v19 = 0.0;
	if ( v8 > 0 )
	{
		p_ticksFile = &_First[0].ticksFile;
		do
		{
			v17 = *(p_ticksFile - 1) * msecPerRawTimerTick * 0.001000000047497451;
			v18 = 0.001000000047497451 * (msecPerRawTimerTick * *p_ticksFile);
			v20 = v17 + v20;
			v19 = v18 + v19;
			Com_Printf(23, "^6%s: %5.3f self, %5.3f file, %i hits\n", *(p_ticksFile - 4), v17, v18, *(p_ticksFile - 3));
			p_ticksFile += 3;
			--v8;
		}
		while ( v8 );
	}
	Com_Printf(23, "\n");
	Com_Printf(23, "^6Hot spot total time: %5.3f self, %5.3f file\n\n", v20, v19);
}

/*
==============
ProfLoad_Print
==============
*/
void ProfLoad_Print()
{
	int fileReadCount; // [esp+20h] [ebp-4h]

	ProfLoad_CalculateSelfTicks();
	ProfLoad_PrintTree();
	ProfLoad_PrintHotSpots();
	fileReadCount = mapLoadProfile.elementAccessCount[2];
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6Total Load Time: %5.4f\n", ((mapLoadProfile.ticksFinish - mapLoadProfile.ticksStart) * msecPerRawTimerTick * 0.001000000047497451));
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6Profiled Time: %5.4f\n", (mapLoadProfile.ticksProfiled * msecPerRawTimerTick * 0.001000000047497451));
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6Unprofiled Time: %5.4f\n", ((mapLoadProfile.ticksFinish - mapLoadProfile.ticksProfiled - mapLoadProfile.ticksStart) * msecPerRawTimerTick * 0.001000000047497451));
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6File Open Time: %5.4f, Accessed %d times\n", (mapLoadProfile.elements[0].ticksTotal * msecPerRawTimerTick * 0.001000000047497451), mapLoadProfile.elementAccessCount[0]);
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6File Seek Time: %5.4f, Accessed %d times\n", (mapLoadProfile.elements[1].ticksTotal * msecPerRawTimerTick * 0.001000000047497451), mapLoadProfile.elementAccessCount[1]);
	Com_Printf(CON_CHANNEL_PERFORMANCE, "^6File Read Time: %5.4f, Accessed %d times\n", (mapLoadProfile.elements[2].ticksTotal * msecPerRawTimerTick * 0.001000000047497451), fileReadCount);
}

/*
==============
ProfLoad_Deactivate
==============
*/
void ProfLoad_Deactivate()
{
	assert(mapLoadProfile.isLoading);
	LARGE_INTEGER PerformanceCount;
	QueryPerformanceCounter(&PerformanceCount);
	mapLoadProfile.ticksFinish = PerformanceCount.QuadPart;
	mapLoadProfile.isLoading = 0;
	ProfLoad_Print();
}

