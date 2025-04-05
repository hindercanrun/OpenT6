#include "types.h"

struct GfxDebugPoly
{
	float faceColor[4];
	bool faceDepthTest;
	float edgeColor[4];
	bool edgeDepthTest;
	int firstVert;
	int vertCount;
};

struct trDebugString_t
{
	float xyz[3];
	float color[4];
	float scale;
	char text[96];
};

struct trDebugLine_t
{
	float start[3];
	float end[3];
	float color[4];
	int depthTest;
};

struct GfxDebugPlume
{
	float origin[3];
	float color[4];
	int score;
	int startTime;
	int duration;
};

struct DebugGlobals
{
	PolySet polySet;
	trDebugString_t *strings;
	int stringCount;
	int stringLimit;
	trDebugString_t *externStrings;
	int externStringCount;
	int externMaxStringCount;
	trDebugLine_t *lines;
	int lineCount;
	int lineLimit;
	trDebugLine_t *externLines;
	int externLineCount;
	int externMaxLineCount;
	GfxDebugPlume *plumes;
	int plumeCount;
	int plumeLimit;
	trDebugSphere_t *spheres;
	int sphereCount;
	int sphereLimit;
	trDebugSphere_t *externSpheres;
	int externSphereCount;
	int externMaxSphereCount;
};

DebugGlobals debugGlobals{};

struct PolySet
{
	float *verts[3];
	int vertCount;
	int vertLimit;
	GfxDebugPoly *polys;
	int polyCount;
	int polyLimit;
};

PolySet persistentPolySet{};

const float colorRed[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
const float colorGreen[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
const float colorBlue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

/*
==============
TRACK_r_debug
==============
*/
void TRACK_r_debug()
{
	track_static_alloc_internal(&debugGlobals, 108, "debugGlobals", 0);
}

/*
==============
R_AddDebugPolygon
==============
*/
void R_AddDebugPolygon(
	DebugGlobals *debugGlobalsEntry,
	int pointCount,
	const float *points,
	const float *faceColor,
	int faceDepthTest,
	const float *edgeColor,
	bool edgeDepthTest)
{
	R_AddDebugPolygonInternal(
		&debugGlobalsEntry->polySet,
		pointCount,
		points,
		faceColor,
		faceDepthTest,
		edgeColor,
		edgeDepthTest);
}

/*
==============
R_AddPersistentDebugPolygon
==============
*/
void R_AddPersistentDebugPolygon(
	DebugGlobals *debugGlobalsEntry,
	int pointCount,
	const float *points,
	const float *faceColor,
	int faceDepthTest,
	const float *edgeColor,
	bool edgeDepthTest)
{
	R_AddDebugPolygonInternal(
		&persistentPolySet,
		pointCount,
		points,
		faceColor,
		faceDepthTest,
		edgeColor,
		edgeDepthTest);
}

/*
==============
R_ClearPersistentDebugPolygons
==============
*/
void R_ClearPersistentDebugPolygons()
{
	Sys_EnterCriticalSection(CRITSECT_DEBUG_LINE);

	persistentPolySet.vertCount = NULL;
	persistentPolySet.polyCount = NULL;

	Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
}

/*
==============
R_AddDebugLine
==============
*/
void R_AddDebugLine(
	DebugGlobals *debugGlobalsEntry,
	const float *start,
	const float *end,
	const float *color,
	int doDepthTest)
{
	Sys_EnterCriticalSection(CRITSECT_DEBUG_LINE);

	if (debugGlobalsEntry->lineCount + 1 <= debugGlobalsEntry->lineLimit)
	{
		if (debugGlobalsEntry->lines
			|| (R_DebugAlloc(&debugGlobalsEntry->lines, 44
				* debugGlobalsEntry->lineLimit, "R_AddDebugLine"), debugGlobalsEntry->lines))
		{
			trDebugLine_t *pDebugLine{};
			pDebugLine = &debugGlobalsEntry->lines[debugGlobalsEntry->lineCount];
			pDebugLine->start[0] = *start;
			pDebugLine->start[1] = start[1];
			pDebugLine->start[2] = start[2];
			pDebugLine->end[0] = *end;
			pDebugLine->end[1] = end[1];
			pDebugLine->end[2] = end[2];
			pDebugLine->color[0] = *color;
			pDebugLine->color[1] = color[1];
			pDebugLine->color[2] = color[2];
			pDebugLine->color[3] = color[3];
			pDebugLine->depthTest = doDepthTest;

			++debugGlobalsEntry->lineCount;

			Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
		}
		else
		{
			Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
		}
	}
	else
	{
		Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);

		Com_Printf(
			CON_CHANNEL_DONT_FILTER,
			"Debug line limit exceeded, current=%d, limit=%d\n",
			debugGlobalsEntry->lineCount,
			debugGlobalsEntry->lineLimit);
	}
}

/*
==============
R_AddDebugBox
==============
*/
void R_AddDebugBox(
	DebugGlobals *debugGlobalsEntry,
	const float *mins,
	const float *maxs,
	const float *color)
{
	float v[8][3];
  
	for (unsigned int i = 0; i < 8; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			float v4{};
			if ( (i & (1 << j)) != 0 )
			{
				v4 = maxs[j];
			}
			else
			{
				v4 = mins[j];
			}

			v[i][j] = v4;
		}
	}

	for (unsigned int ia = 0; ia < 12; ++ia)
	{
		R_AddDebugLine(debugGlobalsEntry, v[iEdgePairs[ia][0]], v[dword_D7F394[2 * ia]], color, 0);
	}
}

/*
==============
R_AddDebugFrustum
==============
*/
void R_AddDebugFrustum(const GfxViewParms *viewParms)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_AddDebugString
==============
*/
void R_AddDebugString(
	DebugGlobals *debugGlobalsEntry,
	const float *origin,
	const float *color,
	float scale,
	const char *string)
{
	Sys_EnterCriticalSection(CRITSECT_DEBUG_LINE);

	if (debugGlobalsEntry->stringCount + 1 <= debugGlobalsEntry->stringLimit
		&& (debugGlobalsEntry->strings
			|| (R_DebugAlloc(&debugGlobalsEntry->strings, debugGlobalsEntry->stringLimit << 7, "R_AddDebugString"),
			debugGlobalsEntry->strings)))
	{
		trDebugString_t *pDebugString{};
		pDebugString = &debugGlobalsEntry->strings[debugGlobalsEntry->stringCount];
		pDebugString->xyz[0] = *origin;
		pDebugString->xyz[1] = origin[1];
		pDebugString->xyz[2] = origin[2];
		pDebugString->color[0] = *color;
		pDebugString->color[1] = color[1];
		pDebugString->color[2] = color[2];
		pDebugString->color[3] = color[3];
		pDebugString->scale = scale;

		strncpy(pDebugString->text, string, 95);
		pDebugString->text[95] = 0;

		++debugGlobalsEntry->stringCount;

		Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
	}
	else
	{
		Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
	}
}

/*
==============
R_AddScaledDebugString
==============
*/
void R_AddScaledDebugString(
	DebugGlobals *debugGlobalsEntry,
	const GfxViewParms *viewParms,
	const float *origin,
	const float *color,
	const char *string)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_InitDebugEntry
==============
*/
void R_InitDebugEntry(DebugGlobals *debugGlobalsEntry)
{
	memset(debugGlobalsEntry, 0, sizeof(DebugGlobals));
	debugGlobalsEntry->polySet.vertLimit = 32768;
	debugGlobalsEntry->polySet.polyLimit = 8192;
	debugGlobalsEntry->stringLimit = 4096;
	debugGlobalsEntry->lineLimit = 16384;
	debugGlobalsEntry->sphereLimit = 1024;
	debugGlobalsEntry->plumeLimit = 4096;
}

/*
==============
R_ShutdownDebugEntry
==============
*/
void R_ShutdownDebugEntry(DebugGlobals *debugGlobalsEntry)
{
	R_DebugFree(&debugGlobalsEntry->polySet.polys);
	R_DebugFree(&debugGlobalsEntry->polySet.verts);
	R_DebugFree(&debugGlobalsEntry->strings);
	R_DebugFree(&debugGlobalsEntry->externStrings);
	R_DebugFree(&debugGlobalsEntry->spheres);
	R_DebugFree(&debugGlobalsEntry->externSpheres);
	R_DebugFree(&debugGlobalsEntry->lines);
	R_DebugFree(&debugGlobalsEntry->externLines);
	R_DebugFree(&debugGlobalsEntry->plumes);

	free_chull_lists();
}

/*
==============
R_TransferDebugGlobals
==============
*/
void R_TransferDebugGlobals(DebugGlobals *debugGlobalsEntry)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ShutdownDebug
==============
*/
void R_ShutdownDebug()
{
	R_ShutdownDebugEntry(&debugGlobals);

	R_DebugFree(&persistentPolySet.polys);
	R_DebugFree(&persistentPolySet.verts);
}

/*
==============
R_CopyDebugStrings
==============
*/
void R_CopyDebugStrings(
	trDebugString_t *clStrings,
	int clStringCnt,
	trDebugString_t *svStrings,
	int svStringCnt,
	int maxStringCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CopyDebugLines
==============
*/
void R_CopyDebugLines(
	trDebugLine_t *clLines,
	int clLineCnt,
	trDebugLine_t *svLines,
	int svLineCnt,
	int maxLineCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CopyDebugSpheres
==============
*/
void R_CopyDebugSpheres(
	trDebugSphere_t *clSpheres,
	int clSphereCnt,
	trDebugSphere_t *svSpheres,
	int svSphereCnt,
	int maxSphereCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_AddDebugAxis
==============
*/
void R_AddDebugAxis(
	DebugGlobals *debugGlobalsEntry,
	const float *origin,
	const float *axis,
	float length,
	int doDepthTest)
{
	const float *axisColors[3];

	axisColors[0] = colorRed;
	axisColors[1] = colorGreen;
	axisColors[2] = colorBlue;

	for (int i = 0; i < 3; ++i)
	{
		float end[3]{};
		end[0] = (length * (*axis)[3 * i]) + *origin;
		end[1] = (length * (*axis)[3 * i + 1]) + origin[1];
		end[2] = (length * (*axis)[3 * i + 2]) + origin[2];

		R_AddDebugLine(debugGlobalsEntry, origin, end, axisColors[i], doDepthTest);
	}
}

/*
==============
R_AddDebugPolygonOutline
==============
*/
void R_AddDebugPolygonOutline(
	DebugGlobals *debugGlobalsEntry,
	int pointCount,
	const float *points,
	const float *color,
	int doDepthTest)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_AddDebugPolygonInternal
==============
*/
void R_AddDebugPolygonInternal(
	PolySet *polySet,
	int pointCount,
	const float *points,
	const float *faceColor,
	bool faceDepthTest,
	const float *edgeColor,
	bool edgeDepthTest)
{
	Sys_EnterCriticalSection(CRITSECT_DEBUG_LINE);

	if (pointCount + polySet->vertCount <= polySet->vertLimit)
	{
		if (polySet->polyCount + 1 <= polySet->polyLimit)
		{
			if (!polySet->polys)
			{
				assert(polySet->verts == NULL);
				R_DebugAlloc(&polySet->polys, 48 * polySet->polyLimit, "(debugGlobalsEntry->polys)");
				R_DebugAlloc(&polySet->verts, 12 * polySet->vertLimit, "(debugGlobalsEntry->verts)");
			}

			if (polySet->polys && polySet->verts)
			{
				GfxDebugPoly *the_poly{};
				the_poly = &polySet->polys[polySet->polyCount];
				the_poly->firstVert = polySet->vertCount;
				the_poly->vertCount = pointCount;
				the_poly->faceColor[0] = *faceColor;
				the_poly->faceColor[1] = faceColor[1];
				the_poly->faceColor[2] = faceColor[2];
				the_poly->faceColor[3] = faceColor[3];
				the_poly->faceDepthTest = faceDepthTest;
				the_poly->edgeColor[0] = *edgeColor;
				the_poly->edgeColor[1] = edgeColor[1];
				the_poly->edgeColor[2] = edgeColor[2];
				the_poly->edgeColor[3] = edgeColor[3];
				the_poly->edgeDepthTest = edgeDepthTest;

				++polySet->polyCount;
				memcpy(polySet->verts[polySet->vertCount], points, 12 * pointCount);
				polySet->vertCount += pointCount;

				Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
			}
			else
			{
				Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);
			}
		}
		else
		{
			Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);

			Com_Printf(
				CON_CHANNEL_DONT_FILTER,
				"Debug polygon limit exceeded, current=%d, limit=%d\n",
				polySet->polyCount,
				polySet->polyLimit);
		}
	}
	else
	{
		Sys_LeaveCriticalSection(CRITSECT_DEBUG_LINE);

		Com_Printf(
			CON_CHANNEL_DONT_FILTER,
			"Debug vertex limit exceeded, current=%d, adding=%d, limit=%d\n",
			polySet->vertCount,
			pointCount,
			polySet->vertLimit);
	}
}

/*
==============
R_UpdatePersistentDebugPolys
==============
*/
void R_UpdatePersistentDebugPolys(DebugGlobals *debugGlobalsEntry)
{
	for (int ipoly = 0; ipoly < persistentPolySet.polyCount; ++ipoly)
	{
		R_AddDebugPolygon(
			debugGlobalsEntry,
			persistentPolySet.polys[ipoly].vertCount,
			persistentPolySet.verts[persistentPolySet.polys[ipoly].firstVert],
			persistentPolySet.polys[ipoly].faceColor,
			persistentPolySet.polys[ipoly].faceDepthTest,
			persistentPolySet.polys[ipoly].edgeColor,
			persistentPolySet.polys[ipoly].edgeDepthTest);
	}
}

