#include "types.h"

#define WORLD_SIZE 128*1024
#define GFX_LIGHTGRID_BITS_XY -128*1024

/*
==============
ParseKVPFileFloatKVP
==============
*/
bool ParseKVPFileFloatKVP(char *kvpFile, char *kvp, vec3_t *vec)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ParseKVPFileVec3KVP
==============
*/
bool ParseKVPFileVec3KVP(char *kvpFile, char *kvp, vec3_t *vec)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
TRACK_r_bsp_load_obj
==============
*/
void TRACK_r_bsp_load_obj()
{
	track_static_alloc_internal(&s_world, 1028, "s_world", 21);
}

/*
==============
R_GetBspMaterial
==============
*/
Material *R_GetBspMaterial(unsigned int materialIndex, GfxSurface *surface)
{
	static char materialName[256];

	assertMsg(
		(unsigned)(materialIndex) < (unsigned)((2048)),
		"materialIndex doesn't index MAX_MAP_MATERIALS\n\t%i not in [0, %i)",
		materialIndex,
		2048
	);

	const dmaterial_t *diskMaterial = &rgl.load.diskMaterials[materialIndex];
	const dmaterial_t *name = diskMaterial;

	assert(name[0]);
	assert(strcmp( name, "noshader" ));

	if (!strcmp(diskMaterial->material, "$default"))
	{
		name = (const dmaterial_t *)"$default3d";
	}

	if (!name->material[0] == 42)
	{
		Com_sprintf(materialName, 256, "%s%s", "wc/", name->material);
	}

	Com_sprintf(materialName, 256, "%s%s", nullptr, name->material);
	return Material_Register(materialName, 9);
}

/*
==============
R_CreateWorldVertexBuffer
==============
*/
void R_CreateWorldVertexBuffer(ID3D11Buffer **vb, int *srcData, unsigned int sizeInBytes)
{
	if (!r_loadForRenderer->current.enabled)
	{
		*vb = 0;
	}

	assert((srcData == NULL) == (sizeInBytes == NULL));

	if (!sizeInBytes)
	{
		static int dummyData{};
		dummyData = 0;
		srcData = &dummyData;
		sizeInBytes = 4;
	}

	R_AllocStaticVertexBuffer(vb, sizeInBytes srcData, 1, "R_CreateWorldVertexBuffer");
}

/*
==============
R_CreateWorldVertexBuffer
==============
*/
void *R_CreateWorldVertexBuffer(unsigned int bytes)
{
	return Hunk_Alloc(bytes, "R_LoadSurfaces", 21);
}

/*
==============
R_UpdateDiskSurfaces_Version14
==============
*/
const DiskTriangleSoup *R_UpdateDiskSurfaces_Version14(const DiskTriangleSoup *oldSurfs, int surfCount)
{
	unsigned __int8 *newSurfs = (unsigned __int8 *)Hunk_AllocateTempMemory(28 * surfCount, "R_UpdateDiskSurfaces");
	memcpy(newSurfs, (unsigned __int8 *)oldSurfs, 28 * surfCount);

	for (int surfIndex = 0; surfIndex < surfCount; ++surfIndex)
	{
		if (newSurfs[28 * surfIndex + 4] != 255)
		{
			++newSurfs[28 * surfIndex + 4];
		}

		newSurfs[28 * surfIndex + 4] = 0;
	}
	return (const DiskTriangleSoup *)newSurfs;
}

/*
==============
R_UpdateDiskSurfaces_Version12
==============
*/
const DiskTriangleSoup *R_UpdateDiskSurfaces_Version12(
	const DiskTriangleSoup_Version12 *oldSurfs,
	int surfCount)
{
	DiskTriangleSoup *newSurfs = (DiskTriangleSoup *)Hunk_AllocateTempMemory(28 * surfCount, "R_UpdateDiskSurfaces");
	for (int surfIndex = 0; surfIndex < surfCount; ++surfIndex)
	{
		newSurfs[surfIndex].materialIndex = oldSurfs[surfIndex].materialIndex;
		newSurfs[surfIndex].lightmapIndex = oldSurfs[surfIndex].lightmapIndex;
		newSurfs[surfIndex].reflectionProbeIndex = oldSurfs[surfIndex].reflectionProbeIndex;
		newSurfs[surfIndex].primaryLightIndex = 1;

		newSurfs[surfIndex].firstIndex = oldSurfs[surfIndex].firstIndex;
		newSurfs[surfIndex].firstVertex = oldSurfs[surfIndex].firstVertex;

		newSurfs[surfIndex].vertexLayerData = oldSurfs[surfIndex].vertexLayerData;

		newSurfs[surfIndex].vertexCount = oldSurfs[surfIndex].vertexCount;
		newSurfs[surfIndex].indexCount = oldSurfs[surfIndex].indexCount;
	}
	return newSurfs;
}

/*
==============
R_UpdateDiskSurfaces_Version8
==============
*/
const DiskTriangleSoup *R_UpdateDiskSurfaces_Version8(const DiskTriangleSoup_Version8 *oldSurfs, int surfCount)
{
	DiskTriangleSoup *newSurfs = (DiskTriangleSoup *)Hunk_AllocateTempMemory(28 * surfCount, "R_UpdateDiskSurfaces");
	for (int surfIndex = 0; surfIndex < surfCount; ++surfIndex)
	{
		newSurfs[surfIndex].materialIndex = oldSurfs[surfIndex].materialIndex;
		newSurfs[surfIndex].lightmapIndex = oldSurfs[surfIndex].lightmapIndex;
		newSurfs[surfIndex].reflectionProbeIndex = oldSurfs[surfIndex].reflectionProbeIndex;
		newSurfs[surfIndex].primaryLightIndex = 1;

		newSurfs[surfIndex].firstIndex = oldSurfs[surfIndex].firstIndex;
		newSurfs[surfIndex].firstVertex = oldSurfs[surfIndex].firstVertex;

		newSurfs[surfIndex].vertexLayerData = 0;

		newSurfs[surfIndex].vertexCount = oldSurfs[surfIndex].vertexCount;
		newSurfs[surfIndex].indexCount = oldSurfs[surfIndex].indexCount;
	}
	return newSurfs;
}

/*
==============
R_LoadTriangleSurfaces
==============
*/
void R_LoadTriangleSurfaces(
	unsigned int bspVersion,
	const DiskTriangleSoup **diskSurfaces,
	unsigned int *surfCount)
{
	if (!bspVersion > 8)
	{
		*diskSurfaces = (const DiskTriangleSoup *)Com_GetBspLump(LUMP_TRIANGLES, 16, surfCount);
		*diskSurfaces = R_UpdateDiskSurfaces_Version8((const DiskTriangleSoup_Version8 *)*diskSurfaces, *surfCount);
	}

	if (!bspVersion > 12)
	{
		*diskSurfaces = (const DiskTriangleSoup *)Com_GetBspLump(LUMP_TRIANGLES, 20, surfCount);
		*diskSurfaces = R_UpdateDiskSurfaces_Version12((const DiskTriangleSoup_Version12 *)*diskSurfaces, *surfCount);
	}

	static const DiskTriangleSoup *BspLump{};
	if (!bspVersion > 14)
	{
		*diskSurfaces = (const DiskTriangleSoup *)Com_GetBspLump(LUMP_TRIANGLES, 28, surfCount);
		BspLump = R_UpdateDiskSurfaces_Version14(*diskSurfaces, *surfCount);
	}

	BspLump = (const DiskTriangleSoup *)Com_GetBspLump(LUMP_TRIANGLES, 28, surfCount);
	*diskSurfaces = BspLump;
}

/*
==============
R_DetermineLightmapCoupling
==============
*/
int R_DetermineLightmapCoupling(GfxBspLoad *load, long double (*coupling)[30], LumpType lumpType)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_BuildLightmapMergability
==============
*/
int R_BuildLightmapMergability(GfxBspLoad *load, r_lightmapGroup_t *groupInfo, int *reorder, LumpType lumpType)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_LoadLightmaps
==============
*/
#define	LIGHTMAP_SIZE 0x400000
void R_LoadLightmaps(GfxBspLoad *load)
{
	printf("Loading LightMaps\n");

	assert(load);

	load->lmapMergeInfo[31].index = 31;
	load->lmapMergeInfo[31].shift[0] = 0.0;
	load->lmapMergeInfo[31].shift[1] = 0.0;
	load->lmapMergeInfo[31].scale[0] = 1.0;
	load->lmapMergeInfo[31].scale[1] = 1.0;

	static r_lightmapGroup_t groupInfo[16]{};
	static int reorder[16]{};
	int oldLmapCount = R_BuildLightmapMergability(load, groupInfo, reorder, LUMP_LIGHTBYTES);

	if (!oldLmapCount)
	{
		s_world.draw.lightmapCount = 0;
	}

	int totalImageSize = groupInfo[0].highCount * 9437184 * groupInfo[0].wideCount;
	unsigned __int8 *primaryImage = Hunk_AllocateTempMemory(totalImageSize, "R_LoadLightmaps");
	unsigned __int8 *secondaryImage = &primaryImage[groupInfo[0].highCount * (groupInfo[0].wideCount << 20)];

	static unsigned int len{};
	const unsigned __int8 *buf = Com_GetBspLump(LUMP_LIGHTBYTES, 1, &len);

	if (!len)
	{
		printf("\nNo Lightmap found - setting to white\n");
		memset(primaryImage, 255, groupInfo[0].highCount * (groupInfo[0].wideCount << 20));

		float* src = secondaryImage;
		for (unsigned int i = 0; i < (groupInfo[0].highCount * (groupInfo[0].wideCount << 23)) >> 2; ++i )
		{
			src[i] = 1.0;
		}
	}

	if (load->bspVersion < 7)
	{
		len = 0;
	}

	int imageFlags = 56;

	s_world.draw.lightmaps = Hunk_Alloc(204, "R_LoadLightmaps", 21);

	unsigned __int8 newLmapIndex = 0;
    int oldLmapBaseIndex = 0;

	while (oldLmapBaseIndex < oldLmapCount)
	{
		assert((newLmapIndex == 0 || groupInfo[newLmapIndex].wideCount <= groupInfo[newLmapIndex - 1].wideCount));
		assert((newLmapIndex == 0 || groupInfo[newLmapIndex].highCount <= groupInfo[newLmapIndex - 1].highCount));

		int groupCount = groupInfo[newLmapIndex].highCount * groupInfo[newLmapIndex].wideCount;

		for (int tileIndex = 0; tileIndex < groupCount; ++tileIndex)
		{
			int oldLmapIndex = reorder[tileIndex + oldLmapBaseIndex];

			int x = tileIndex % groupInfo[newLmapIndex].wideCount;
			int y = tileIndex / groupInfo[newLmapIndex].wideCount;

			if (len)
			{
				const unsigned __int8 *buf_p = &buf[9437184 * oldLmapIndex];
				R_CopyLightmap(buf_p, 512, 512, 16, secondaryImage, x, y, groupInfo[newLmapIndex].wideCount);

				buf_p += LIGHTMAP_SIZE;
				R_CopyLightmap(
					buf_p,
					512,
					512,
					16,
					secondaryImage,
					x,
					groupInfo[newLmapIndex].highCount + y,
					groupInfo[newLmapIndex].wideCount);
				R_CopyLightmap(buf_p, 1024, 1024, 1, primaryImage, x, y, groupInfo[newLmapIndex].wideCount);				
			}

			load->lmapMergeInfo[oldLmapIndex].index = newLmapIndex;
			load->lmapMergeInfo[oldLmapIndex].scale[0] = 1.0 / groupInfo[newLmapIndex].wideCount;
			load->lmapMergeInfo[oldLmapIndex].scale[1] = 1.0 / groupInfo[newLmapIndex].highCount;
			load->lmapMergeInfo[oldLmapIndex].shift[0] = x * load->lmapMergeInfo[oldLmapIndex].scale[0];
			load->lmapMergeInfo[oldLmapIndex].shift[1] = y * load->lmapMergeInfo[oldLmapIndex].scale[1];
		}

		s_world.draw.lightmaps[newLmapIndex].primary = Image_Alloc(va("*lightmap%i_primary", newLmapIndex), 2, 1, 4, 1.0);
		assert((s_world.draw.lightmaps[newLmapIndex].primary));

		Image_Generate2D(
			s_world.draw.lightmaps[newLmapIndex].primary,
			primaryImage,
			groupInfo[newLmapIndex].wideCount << 10,
			groupInfo[newLmapIndex].highCount << 10,
			D3DFMT_L8);

		s_world.draw.lightmaps[newLmapIndex].secondary = Image_Alloc(va("*lightmap%i_secondary", newLmapIndex), 2, 1, 4, 1.0);
		assert((s_world.draw.lightmaps[newLmapIndex].secondary));

		int width = groupInfo[newLmapIndex].wideCount << 9;
		int height = groupInfo[newLmapIndex].highCount << 10;
		int w = width;
		int h = height / 2;
		unsigned __int8 *v34 = secondaryImage;
		unsigned __int8 *lightmapLum = Hunk_AllocateTempMemory(4 * height / 2 * width, "R_LightMapLum");
		unsigned int *dst32 = lightmapLum;

		for (int j = 0; j < h * w; ++j)
		{
			//todo
		}

		Image_Generate2D(s_world.draw.lightmaps[newLmapIndex].secondaryB, lightmapLum, w, h, D3DFMT_G16R16);
		Hunk_FreeTempMemory(lightmapLum);

		int wa = width;
		int ha = height;
		unsigned __int8 *lightmapColor = Hunk_AllocateTempMemory(2 * height * width, "R_LightMapColor");
		unsigned __int8 *dst8 = lightmapColor;

		for (int k = 0; k < ha * wa; ++k)
		{
			//todo
		}

		Image_Generate2D(s_world.draw.lightmaps[newLmapIndex].secondary, lightmapColor, wa, ha, D3DFMT_R5G6B5);
		Hunk_FreeTempMemory(lightmapColor);

		oldLmapBaseIndex += groupCount;
		++newLmapIndex;
	}

    s_world.draw.lightmapCount = newLmapIndex;

    Hunk_FreeTempMemory(primaryImage);

	assert(
		((s_world.draw.lightmapCount <= 30)),
		"(s_world.draw.lightmapCount) = %i",
		s_world.draw.lightmapCount);

	s_world.draw.lightmapPrimaryTextures = Hunk_Alloc(4 * s_world.draw.lightmapCount, "R_LoadLightmaps", 21);
	s_world.draw.lightmapSecondaryTextures = Hunk_Alloc(4 * s_world.draw.lightmapCount, "R_LoadLightmaps", 21);
	s_world.draw.lightmapSecondaryTexturesB = Hunk_Alloc(4 * s_world.draw.lightmapCount, "R_LoadLightmaps", 21);
}

/*
==============
R_InitEmptyLightGrid
==============
*/
int R_InitEmptyLightGrid()
{
	s_world.lightGrid.mins[0] = 0;
	s_world.lightGrid.mins[1] = 0;
	s_world.lightGrid.mins[2] = 0;

	s_world.lightGrid.maxs[0] = 0;
	s_world.lightGrid.maxs[1] = 0;
	s_world.lightGrid.maxs[2] = 0;

	s_world.lightGrid.rowAxis = 0;
	s_world.lightGrid.colAxis = 1;

	s_world.lightGrid.rowDataStart = (unsigned __int16 *)Hunk_Alloc(2, "R_InitEmptyLightGrid", 21);
	return 65535;
}

/*
==============
R_AssertLightGridValid
==============
*/
void R_AssertLightGridValid(const GfxLightGrid *lightGrid)
{
	assertMsg(
		(lightGrid->mins[0]) <= (lightGrid->maxs[0]),
		"lightGrid->mins[0] <= lightGrid->maxs[0]\n\t%i, %i",
		lightGrid->mins[0],
		lightGrid->maxs[0]);
	assertMsg(
		(lightGrid->mins[1]) <= (lightGrid->maxs[1]),
		"lightGrid->mins[1] <= lightGrid->maxs[1]\n\t%i, %i",
		lightGrid->mins[1],
		lightGrid->maxs[1]);
	assertMsg(
		(lightGrid->mins[2]) <= (lightGrid->maxs[2]),
		"lightGrid->mins[2] <= lightGrid->maxs[2]\n\t%i, %i",
		lightGrid->mins[2],
		lightGrid->maxs[2]);
	unsigned int rowCount = lightGrid->maxs[lightGrid->rowAxis] + 1 - lightGrid->mins[lightGrid->rowAxis];
	assertMsg(
		(rowCount) <= (( ( WORLD_SIZE ) - ( GFX_LIGHTGRID_BITS_XY ) ) >> 5),
		"rowCount <= WORLD_SIZE >> GFX_LIGHTGRID_BITS_XY\n\t%i, %i",
		rowCount,
		8192);

	for (unsigned int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		if (lightGrid->rowDataStart[rowIndex] != 65535)
		{
			assertMsg(
				(unsigned)(lightGrid->rowDataStart[rowIndex] * 4) < (unsigned)(lightGrid->rawRowDataSize),
				"lightGrid->rowDataStart[rowIndex] * 4 doesn't index lightGrid->rawRowDataSize\n\t%i not in [0, %i)",
				4 * lightGrid->rowDataStart[rowIndex],
				lightGrid->rawRowDataSize);
			const GfxLightGridRow *row = (const GfxLightGridRow *)&lightGrid->rawRowData[4 * lightGrid->rowDataStart[rowIndex]];
			assertMsg(
				(unsigned)(row->firstEntry) < (unsigned)(lightGrid->entryCount),
				"row->firstEntry doesn't index lightGrid->entryCount\n\t%i not in [0, %i)",
				row->firstEntry,
				lightGrid->entryCount);
		}
	}
}

/*
==============
R_LoadLightGridHeader
==============
*/
void R_LoadLightGridHeader()
{
	static unsigned int len;
	const GfxLightGridHeader *header = Com_GetBspLump(LUMP_LIGHTGRIDHEADER, 1, &len);

	if (len < 20)
	{
		Com_Error(ERR_DROP, "ERROR: light grid header is truncated");
	}

	unsigned int rowCount = header->maxs[header->rowAxis] - header->mins[header->rowAxis] + 1;
	if (len != 2 * rowCount + 20)
	{
		Com_Error(ERR_DROP, "ERROR: light grid header has unexpected size");
	}

	s_world.lightGrid.sunPrimaryLightIndex = s_world.sunPrimaryLightIndex;

	s_world.lightGrid.mins[0] = header->mins[0];
	s_world.lightGrid.mins[1] = header->mins[1];
	s_world.lightGrid.mins[2] = header->mins[2];

	s_world.lightGrid.maxs[0] = header->maxs[0];
	s_world.lightGrid.maxs[1] = header->maxs[1];
	s_world.lightGrid.maxs[2] = header->maxs[2];

	s_world.lightGrid.rowAxis = header->rowAxis;
	s_world.lightGrid.colAxis = header->colAxis;

	s_world.lightGrid.rowDataStart = (unsigned __int16 *)Hunk_Alloc(2 * rowCount, "R_LoadLightGridHeader", 21);
	Com_Memcpy(s_world.lightGrid.rowDataStart, header->rowDataStart, 2 * rowCount);

	if (!s_world.lightGrid.entryCount)
	{
		R_InitEmptyLightGrid();
	}

	R_AssertLightGridValid(&s_world.lightGrid);
}

/*
==============
R_LoadLightGridColors
==============
*/
void R_LoadLightGridColors(unsigned int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadLightGridEntries
==============
*/
GfxLightGridEntry *R_LoadLightGridEntries(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadReflectionProbes
==============
*/
void R_LoadReflectionProbes(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_HeroLightSorter
==============
*/
int R_HeroLightSorter(const void *a, const void *b)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_BuildHeroLightTree
==============
*/
void R_BuildHeroLightTree(unsigned int nodeIndex, unsigned int firstLight, unsigned int lightCount, vec3_t *mins, vec3_t *maxs)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadHeroOnlyLights
==============
*/
void R_LoadHeroOnlyLights(LumpType a1, char *a2, const char *a3, unsigned int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadCoronas
==============
*/
GfxLightCorona *R_LoadCoronas(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadOccluders
==============
*/
unsigned __int8 *R_LoadOccluders(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadShadowMapVolumes
==============
*/
unsigned __int8 *R_LoadShadowMapVolumes(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadExposureVolumes
==============
*/
unsigned __int8 *R_LoadExposureVolumes(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadWorldFogVolumes
==============
*/
void R_LoadWorldFogVolumes(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadWorldFogModifierVolumes
==============
*/
void R_LoadWorldFogModifierVolumes(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadLutVolumes
==============
*/
void R_LoadLutVolumes(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CalculateSurfaceBounds
==============
*/
void R_CalculateSurfaceBounds(GfxSurface *surface, const DiskGfxVertex *vertsDisk, int vertCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_MergeSurfaceLightMapCoords
==============
*/
void R_MergeSurfaceLightMapCoords(const Material *material, GfxSurface *surface, const DiskGfxVertex *vertsDisk, const r_lightmapMerge_t *merge, GfxWorldVertex *vertsMem, int vertCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CalculateOutdoorBounds
==============
*/
void R_CalculateOutdoorBounds(GfxBspLoad *load, const DiskTriangleSoup *diskSurfaces)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CompareSurfaces
==============
*/
bool R_CompareSurfaces(const GfxSurface *surf0, const GfxSurface *surf1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortSurfacesOnAxis_PosX
==============
*/
BOOL R_SortSurfacesOnAxis_PosX(const GfxSurface *surf0, const GfxSurface *surf1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortSurfacesOnAxis_NegX
==============
*/
BOOL R_SortSurfacesOnAxis_NegX(const GfxSurface *surf0, const GfxSurface *surf1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortSurfacesOnAxis_PosY
==============
*/
BOOL R_SortSurfacesOnAxis_PosY(const GfxSurface *surf0, const GfxSurface *surf1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortSurfacesOnAxis_NegY
==============
*/
BOOL R_SortSurfacesOnAxis_NegY(const GfxSurface *surf0, const GfxSurface *surf1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_PackPosition
==============
*/
void R_PackPosition(const vec3_t dataDisk, vec3_t *dataMem)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_PackWorldVertex0
==============
*/
void R_PackWorldVertex0(const GfxSurface *surface, unsigned __int8 *out, const GfxWorldVertex *worldVert)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_PackWorldVertex1
==============
*/
void R_PackWorldVertex1(const GfxSurface *surface, unsigned __int8 *out, const GfxWorldVertex *worldVert, const unsigned __int8 *vertLayerData)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ValidateSurfaceLightmapUsage
==============
*/
void R_ValidateSurfaceLightmapUsage(const GfxSurface *surface)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CalculateTriangleGroupTexCoordExtents
==============
*/
void R_CalculateTriangleGroupTexCoordExtents(GfxSurface *surface, GfxWorldVertex *vertsMem, unsigned __int8 *layerVertsMem, unsigned int vertLayerDataStride, unsigned int extraTexCoordCount, unsigned __int8 *triUsed, unsigned __int8 *vertUsed, int startTriIndex, vec3_t *mins, vec3_t *maxs)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadSubmodels
==============
*/
void R_LoadSubmodels(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_FloatForKey
==============
*/
float R_FloatForKey(const char *key, float defaultValue, char *(*spawnVars)[2], int spawnVarCount)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_IntForKey
==============
*/
int R_IntForKey(const char *key, int defaultValue, char *(*spawnVars)[2], int spawnVarCount)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_VectorForKey
==============
*/
bool R_VectorForKey(const char *key, const char *defaultString, char *(*spawnVars)[2], int spawnVarCount, vec3_t *v)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_LoadStaticModelData
==============
*/
void R_LoadStaticModelData(LumpType a1, char *a2, int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadSkyGridVolumes
==============
*/
void R_LoadSkyGridVolumes(LumpType a1, char *a2, int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_PrefixStaticModelName
==============
*/
void R_PrefixStaticModelName(char *prefixedName, unsigned int prefixedNameSize, const char *name, unsigned int smid)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CheckValidStaticModel
==============
*/
bool R_CheckValidStaticModel(char *(*spawnVars)[2], int spawnVarCount, XModel **model, vec3_t *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SetStaticModelsLightmapData
==============
*/
void R_SetStaticModelsLightmapData()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadMiscModel
==============
*/
void R_LoadMiscModel(int a1, char *(*spawnVars)[2], int spawnVarCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ParseSunLight
==============
*/
char *R_ParseSunLight(SunLightParseParams *params, const char *text)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadPrimaryLights
==============
*/
void R_LoadPrimaryLights(unsigned int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadLightRegions
==============
*/
void R_LoadLightRegions()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_GetStaticModelSortIndex
==============
*/
unsigned int R_GetStaticModelSortIndex(const XModel *model)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_StaticModelCompare
==============
*/
bool R_StaticModelCompare(const GfxStaticModelCombinedInst *smodelInst0, const GfxStaticModelCombinedInst *smodelInst1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_AabbTreeChildrenCount_r
==============
*/
int R_AabbTreeChildrenCount_r(GfxAabbTree *tree)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_AabbTreeFixAABBSizes_r
==============
*/
void R_AabbTreeFixAABBSizes_r(GfxAabbTree *tree)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_AabbTreeMove_r
==============
*/
GfxAabbTree *R_AabbTreeMove_r(GfxAabbTree *tree, GfxAabbTree *newTree, GfxAabbTree *newChildren)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_FixupGfxAabbTrees
==============
*/
void R_FixupGfxAabbTrees(GfxCell *cell)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SortStaticModelsOnAxis_NegX
==============
*/
BOOL R_SortStaticModelsOnAxis_NegX(const GfxStaticModelCombinedInst *smodelCombinedInst0, const GfxStaticModelCombinedInst *smodelCombinedInst1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortStaticModelsOnAxis_PosY
==============
*/
BOOL R_SortStaticModelsOnAxis_PosY(const GfxStaticModelCombinedInst *smodelCombinedInst0, const GfxStaticModelCombinedInst *smodelCombinedInst1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortStaticModelsOnAxis_NegY
==============
*/
BOOL R_SortStaticModelsOnAxis_NegY(const GfxStaticModelCombinedInst *smodelCombinedInst0, const GfxStaticModelCombinedInst *smodelCombinedInst1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_CompareStaticModelSortModels
==============
*/
bool R_CompareStaticModelSortModels(const GfxStaticModelSortModel *sortModel0, const GfxStaticModelSortModel *sortModel1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_LoadEntities
==============
*/
void R_LoadEntities(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_FinishLoadingAabbTrees_r
==============
*/
int R_FinishLoadingAabbTrees_r(GfxAabbTree *tree, int totalTreesUsed)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_LoadAabbTrees
==============
*/
unsigned int R_LoadAabbTrees(LumpType a1, char *a2, const char *a3)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_LoadCells
==============
*/
void R_LoadCells(LumpType a1, char *a2, unsigned int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadPortals
==============
*/
GfxPortal *R_LoadPortals(char *a1, LumpType a2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_SetParentAndCell_r
==============
*/
void R_SetParentAndCell_r(mnode_load_t *node)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_CountNodes_r
==============
*/
unsigned int R_CountNodes_r(mnode_load_t *node)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
R_SortNodes_r
==============
*/
mnode_t *R_SortNodes_r(mnode_load_t *node, mnode_t *out)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadNodesAndLeafs
==============
*/
void R_LoadNodesAndLeafs(LumpType a1, char *a2, unsigned int bspVersion)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_AllocPrimaryLightBuffers
==============
*/
unsigned __int8 *R_AllocPrimaryLightBuffers()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_LoadWorldRuntime
==============
*/
unsigned __int8 *R_LoadWorldRuntime()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_SetStaticModelReflectionProbes
==============
*/
void R_SetStaticModelReflectionProbes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_IncrementShadowGeometryCount
==============
*/
void R_IncrementShadowGeometryCount(GfxWorld *world, unsigned int primaryLightIndex)
{
	++world->shadowGeom[primaryLightIndex].surfaceCount;
}

/*
==============
R_SetUpSunLight
==============
*/
void R_SetUpSunLight(const float *sunColor, const float *sunDirection, GfxLight *light)
{
	assert(light);

	memset(&light->type, 0, sizeof(GfxLight));
	light->type = 1;
	light->dir[0] = *sunDirection;
	light->dir[1] = sunDirection[1];
	light->dir[2] = sunDirection[2];
	light->color[0] = *sunColor;
	light->color[1] = sunColor[1];
	light->color[2] = sunColor[2];
}

/*
==============
R_InterpretSunLightParseParamsIntoLights
==============
*/
void R_InterpretSunLightParseParamsIntoLights(SunLightParseParams *sunParse, GfxLight *sunLight)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_InitPrimaryLights
==============
*/
/*void R_InitPrimaryLights(const vec3_t *a1, const char *a2@<ebx>, GfxLight *primaryLights)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
R_ForEachPrimaryLightAffectingSurface
==============
*/
void R_ForEachPrimaryLightAffectingSurface(GfxWorld *world, const GfxSurface *surface, unsigned int sortedSurfIndex, void (*Callback)(GfxWorld *, unsigned int, unsigned int))
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_GetSurfaceVertexLayerDataStride
==============
*/
MaterialTechniqueSet *R_GetSurfaceVertexLayerDataStride(const GfxSurface *surface)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
R_GetSurfaceVertexPosition
==============
*/
void R_GetSurfaceVertexPosition(const GfxSurface *surface, int vertIndex, vec3_t *result)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_GetSurfaceVertexLmapCoord
==============
*/
void R_GetSurfaceVertexLmapCoord(const GfxSurface *surface, int vertIndex, vec2_t *result)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_GetSurfaceVertexNormal
==============
*/
void R_GetSurfaceVertexNormal(const GfxSurface *surface, int vertIndex, vec3_t *result)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_RecenterSurfaceTexCoords
==============
*/
void R_RecenterSurfaceTexCoords(GfxSurface *surface, GfxWorldVertex *vertsMem, unsigned __int8 *vertLayerDataMem)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadSurfaces
==============
*/
void R_LoadSurfaces(const DiskTriangleSoup **a1, unsigned int a2, char *load, GfxBspLoad *a4)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadSunSettings
==============
*/
void R_LoadSunSettings(char *a1)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_ForEachShadowCastingSurfaceOnEachLight
==============
*/
void R_ForEachShadowCastingSurfaceOnEachLight(void (*Callback)(GfxWorld *, unsigned int, unsigned int))
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_AddShadowSurfaceToPrimaryLight
==============
*/
void R_AddShadowSurfaceToPrimaryLight(GfxWorld *world, unsigned int primaryLightIndex, unsigned int sortedSurfIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_InitShadowGeometryArrays
==============
*/
void R_InitShadowGeometryArrays()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SpatialSortSurfaceSubArray_r
==============
*/
void R_SpatialSortSurfaceSubArray_r(GfxSurface *beginSurf, GfxSurface *endSurf, unsigned int predIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SpatialSortAllSurfaces
==============
*/
void R_SpatialSortAllSurfaces(int surfaceCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SortSurfaces
==============
*/
void R_SortSurfaces(char *a1)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SpatialSortStaticModelSubArray_r
==============
*/
void R_SpatialSortStaticModelSubArray_r(GfxStaticModelCombinedInst *smodelCombinedInsts, unsigned int begin, unsigned int end, unsigned int predIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_SpatialSortAllStaticModels
==============
*/
void R_SpatialSortAllStaticModels(GfxStaticModelCombinedInst *smodelCombinedInsts)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_InitSortStaticModelsByModel
==============
*/
void R_InitSortStaticModelsByModel()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_PostLoadEntities
==============
*/
void R_PostLoadEntities()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
R_LoadWorldInternal
==============
*/
GfxWorld *R_LoadWorldInternal(const char *a1, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

