#include "types.h"

/*
==============
DB_ImageGetName
==============
*/
const char *DB_ImageGetName(const XAssetHeader *header)
{
	return header->xmodelPieces[6].name;
}

/*
==============
DB_ImageSetName
==============
*/
void DB_ImageSetName(XAssetHeader *header, const char *name)
{
	header->xmodelPieces[6].name = name;
}

/*
==============
DB_LocalizeEntryGetName
==============
*/
const char *DB_LocalizeEntryGetName(const XAssetHeader *header)
{
	return header->xmodelPieces->numpieces;
}

/*
==============
DB_LocalizeEntrySetName
==============
*/
void DB_LocalizeEntrySetName(XAssetHeader *header, const char *name)
{
	header->xmodelPieces->numpieces = name;
}

/*
==============
DB_ZBarrierDefGetName
==============
*/
const char *DB_ZBarrierDefGetName(const XAssetHeader *header)
{
	return header->xmodelPieces->name;
}

/*
==============
DB_ZBarrierDefSetName
==============
*/
void DB_ZBarrierDefSetName(XAssetHeader *header, const char *name)
{
	header->xmodelPieces->name = name;
}

/*
==============
DB_GetEmblemSetName
==============
*/
const char *DB_GetEmblemSetName()
{
	return "emblemset";
}

/*
==============
DB_GetXAssetHeaderName
==============
*/
const char *DB_GetXAssetHeaderName(int type, const XAssetHeader *header)
{
	assert(header);
	assert(DB_XAssetGetNameHandler[type]);
	assert(header->data);

	const char *name = DB_XAssetGetNameHandler[type](header);
	if (!name)
	{
		assertMsg(name, va("Name \"%s\" not found for asset type %s\n", 0, g_assetNames[type]));
		return nullptr;
	}

	return name;
}

/*
==============
DB_GetXAssetName
==============
*/
const char *DB_GetXAssetName(const XAsset *asset)
{
	assert(asset);
	return DB_GetXAssetHeaderName(asset->type, &asset->header);
}

/*
==============
DB_SetXAssetName
==============
*/
void DB_SetXAssetName(XAsset *asset, const char *name)
{
	assert(DB_XAssetSetNameHandler[asset->type]);
	DB_XAssetSetNameHandler[asset->type](&asset->header, name);
}

/*
==============
DB_GetXAssetTypeSize
==============
*/
int DB_GetXAssetTypeSize(int type)
{
	assert(DB_GetXAssetSizeHandler[type]);
	return DB_GetXAssetSizeHandler[type]();
}

/*
==============
DB_GetXAssetTypeName
==============
*/
const char *DB_GetXAssetTypeName(int type)
{
	assert(type >= 0 && type < ASSET_TYPE_COUNT);
	return g_assetNames[type];
}

