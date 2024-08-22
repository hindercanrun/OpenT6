#include "types.h"

/*
==============
CL_AddMapDirSlider
==============
*/
void CL_AddMapDirSlider(const char *dir, int locationFlags, const char *locationName)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_CreateMapMenuEntriesForLocation
==============
*/
void CL_CreateMapMenuEntriesForLocation(int locationFlags, const char *locationName)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_RegisterDevGuiDvars
==============
*/
void CL_RegisterDevGuiDvars()
{
	clGuiGlob.mapEnumDvar[0] = Dvar_RegisterEnum("mapEnum0", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[1] = Dvar_RegisterEnum("mapEnum1", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[2] = Dvar_RegisterEnum("mapEnum2", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[3] = Dvar_RegisterEnum("mapEnum3", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[4] = Dvar_RegisterEnum("mapEnum4", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[5] = Dvar_RegisterEnum("mapEnum5", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[6] = Dvar_RegisterEnum("mapEnum6", emptyEnumList, 0, 0x840u, "");
	clGuiGlob.mapEnumDvar[7] = Dvar_RegisterEnum("mapEnum7", emptyEnumList, 0, 0x840u, "");
}

/*
==============
CL_CreateMapMenuEntries
==============
*/
void CL_CreateMapMenuEntries()
{
	clGuiGlob.mapDirCount = 0;

	CL_CreateMapMenuEntriesForLocation(1, "main*");
	CL_CreateMapMenuEntriesForLocation(2, "dev*");
	CL_CreateMapMenuEntriesForLocation(4, "temp*");
}

/*
==============
CL_CreateDevGui
==============
*/
void CL_CreateDevGui()
{
	clGuiGlob.inited = 1;

	CL_RegisterDevGuiDvars();
	CL_CreateMapMenuEntries();

	clGuiGlob.requiresCreation = 1;
}

/*
==============
CL_DestroyDevGui
==============
*/
void CL_DestroyDevGui()
{
	clGuiGlob.inited = 0;

	DevGui_RemoveMenu("Main:1/Maps:3");

	const dvar_t **mapEnumDvar = clGuiGlob.mapEnumDvar;

	for (mapEnumDvar < &marker_cl_devgui)
	{
		Dvar_UpdateEnumDomain(*mapEnumDvar++, emptyEnumList);
	}

	int v1 = 0;

	if (clGuiGlob.mapDirCount)
	{
		for (v1 != clGuiGlob.mapDirCount)
		{
			FS_FreeFileList(clGuiGlob.mapNames[v1++], 0);
		}
	}

	clGuiGlob.requiresCreation = 0;
}

