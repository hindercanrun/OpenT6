#include "types.h"

/*
==============
BG_GetPlayerAnimTypeName
==============
*/
char *BG_GetPlayerAnimTypeName(int index)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_GetPlayerAnimTypeIndex
==============
*/
int BG_GetPlayerAnimTypeIndex(int typeEnum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
TRACK_bg_weapons_load_obj
==============
*/
void TRACK_bg_weapons_load_obj()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_GetWeaponTypeName
==============
*/
const char *BG_GetWeaponTypeName(weapType_t type)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_GetWeaponClassName
==============
*/
const char *BG_GetWeaponClassName(weapClass_t type)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_GetWeaponInventoryTypeName
==============
*/
const char *BG_GetWeaponInventoryTypeName(weapInventoryType_t type)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_LoadWeaponStrings
==============
*/
void BG_LoadWeaponStrings()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_LoadPlayerAnimTypes
==============
*/
void BG_LoadPlayerAnimTypes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Weapon_GetStringArrayIndex
==============
*/
int Weapon_GetStringArrayIndex(const char *value, const char **stringArray, int arraySize)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_ClearWeaponDefInternal
==============
*/
void BG_ClearWeaponDefInternal()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_RegisterSurfaceTypeSounds
==============
*/
char **BG_RegisterSurfaceTypeSounds(const char *surfaceSoundBase)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_ParseWeaponDefSpecificFieldType
==============
*/
int BG_ParseWeaponDefSpecificFieldType(const char **a1, unsigned __int8 *pStruct, const char *pValue, const int iFieldType)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_SetupTransitionTimes
==============
*/
void BG_SetupTransitionTimes(WeaponVariantDef *weapVariantDef)
{
	if (weapVariantDef->iAdsTransInTime < 0)
	{
		weapVariantDef->fOOPosAnimLength[0] = 1.0f / 300.0f;
	}
	else
	{
		weapVariantDef->fOOPosAnimLength[0] = 1.0f / weapVariantDef->iAdsTransInTime;
	}

	if (weapVariantDef->iAdsTransOutTime < 0)
	{
		weapVariantDef->fOOPosAnimLength[1] = 1.0f / 500.0f;
	}
	else
	{
		weapVariantDef->fOOPosAnimLength[1] = 1.0f / weapVariantDef->iAdsTransOutTime;
	}
}

/*
==============
BG_CheckWeaponDamageRanges
==============
*/
void BG_CheckWeaponDamageRanges(WeaponVariantDef *weapVariantDef)
{
	if (weapDef->fMaxDamageRange < 0.0f)
	{
		weapDef->fMaxDamageRange = 999999.0f;
	}

	if (weapDef->fMinDamageRange < 0.0f)
	{
		weapDef->fMinDamageRange = 999999.0f;
	}
}

/*
==============
BG_SetupAttachmentField
==============
*/
void BG_SetupAttachmentField(WeaponVariantDef *weapVariantDef)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_SetupAttachmentField_OldStyle
==============
*/
void BG_SetupAttachmentField_OldStyle(WeaponVariantDef *weapVariantDef, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_CheckProjectileValues
==============
*/
void BG_CheckProjectileValues(WeaponFullDef *weaponFullDef)
{
	assert(weaponDef->weapType != WEAPTYPE_PROJECTILE);

	if (weaponFullDef->weapDef.iProjectileSpeed < 0.0f)
	{
		Com_Error(
			ERR_DROP,
			"Projectile speed for WeapType %s must be greater than 0.0",
			weaponFullDef->weapVariantDef.szDisplayName);
	}

	if (weaponFullDef->weapDef.destabilizationCurvatureMax > 1000000000.0f || weaponFullDef->weapDef.destabilizationCurvatureMax < 0.0f)
	{
		Com_Error(
			ERR_DROP,
			"Destabilization angle for for WeapType %s must be between 0 and 45 degrees",
			weaponFullDef->weapVariantDef.szDisplayName);
	}

	if (weaponFullDef->weapDef.destabilizationRateTime < 0.0)
	{
		Com_Error(
			ERR_DROP,
			"Destabilization rate time for for WeapType %s must be non-negative",
			weaponFullDef->weapVariantDef.szDisplayName);
	}
}

/*
==============
InitWeaponDef
==============
*/
void InitWeaponDef(WeaponFullDef *weapFullDef)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_LoadFlameTableInternal
==============
*/
const cspField_t *BG_LoadFlameTableInternal(const char *folder, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_GetFlameTable
==============
*/
flameTable *BG_GetFlameTable(const char *folder, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_LoadWeaponFile
==============
*/
char BG_LoadWeaponFile(const char *a1, const char *a2, const char *szFileName, char *szBuffer, int iBufferSize)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_LoadWeaponMergeSupport
==============
*/
void BG_LoadWeaponMergeSupport()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_SplitWeaponDefNames
==============
*/
char BG_SplitWeaponDefNames(const char *name, char **sources, WeaponComponentList *componentAll, char *outputName)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_MergeWeaponDefClipName
==============
*/
int BG_MergeWeaponDefClipName(char **value, char *mergedValue, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_MergeWeaponDefFloatValue
==============
*/
int BG_MergeWeaponDefFloatValue(char **value, char *mergedValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_MergeWeaponDefBitFieldValue
==============
*/
int BG_MergeWeaponDefBitFieldValue(char **value, char *mergedValue, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_MergeWeaponDefHidetags
==============
*/
int BG_MergeWeaponDefHidetags(char **value, char *mergedValue, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_IsAnimationField
==============
*/
bool BG_IsAnimationField(const char *fieldName)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_MergeWeaponDefAnimations
==============
*/
int BG_MergeWeaponDefAnimations(const char *fieldName, char **value, char *mergedValue, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_MergeWeaponDefSpecialCases
==============
*/
int BG_MergeWeaponDefSpecialCases(const char *fieldName, char **value, char *mergedValue, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_LoadWeaponVariantDefFile
==============
*/
bool BG_LoadWeaponVariantDefFile(WeaponFullDef *weapFullDef, const char *folder, const char *name, const char *postfix)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_LoadWeaponVariantDefInternal
==============
*/
WeaponVariantDef *BG_LoadWeaponVariantDefInternal(const char *folder, const char *name, const char *postfix)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_WeaponUpdateField
==============
*/
char BG_WeaponUpdateField(const char *weaponName, const char *keyValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_FlameTableUpdateField
==============
*/
bool BG_FlameTableUpdateField(int (*a1)(unsigned __int8 *, const char *, const int, const int), const char *flameTableName, const char *keyValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_CamoParseMaterialIndex
==============
*/
void BG_CamoParseMaterialIndex(const char *key, unsigned int *set, unsigned int *mat)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
BG_CamoSetReplaceFlags
==============
*/
char BG_CamoSetReplaceFlags(WeaponCamo *camo, const char *key, WeaponCamoMaterialFlags flag, int value)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_WeaponCamoUpdateField
==============
*/
char BG_WeaponCamoUpdateField(const char *camoName, const char *keyValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
BG_LoadDefaultWeaponVariantDef_LoadObj
==============
*/
WeaponFullDef *BG_LoadDefaultWeaponVariantDef_LoadObj(WeaponFullDef *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_LoadDefaultWeaponVariantDef_FastFile
==============
*/
WeaponVariantDef *BG_LoadDefaultWeaponVariantDef_FastFile()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
BG_LoadDefaultWeaponVariantDef
==============
*/
WeaponVariantDef *BG_LoadDefaultWeaponVariantDef()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

