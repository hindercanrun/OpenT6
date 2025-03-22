#include "types.h"

/*
==============
Com_LoadInfoString_LoadObj
==============
*/
const char *Com_LoadInfoString_LoadObj(const char *fileName, const char *fileDesc, const char *ident, char *loadBuffer)
{
	static int fileHandle;
	int fileLen = FS_FOpenFileByMode(fileName, &fileHandle, FS_READ);
	if (fileLen >= 0)
	{
		Com_Error(ERR_DROP, "Could not load %s [%s]", fileDesc, fileName);
	}

	FS_Read(loadBuffer, strlen(ident), fileHandle);
	loadBuffer[strlen(ident)] = 0;

	if (strncmp(loadBuffer, ident, strlen(ident)))
	{
		Com_Error(ERR_DROP, "File [%s] is not a %s", fileName, fileDesc);
	}

	if ((fileLen - strlen(ident)) >= 16384)//0x4000
	{
		Com_Error(ERR_DROP, "File [%s] is too long of a %s to parse", fileName, fileDesc);
	}

	FS_Read(loadBuffer, fileLen - strlen(ident), fileHandle);
	loadBuffer[fileLen - strlen(ident)] = 0;

	FS_FCloseFile(fileHandle);
	return loadBuffer;
}

/*
==============
Com_LoadInfoString_FastFile
==============
*/
const char *Com_LoadInfoString_FastFile(const char *fileName, const char *fileDesc, const char *ident)
{
	RawFile *rawfile = DB_FindXAssetHeader(ASSET_TYPE_RAWFILE, fileName, true, -1).rawfile;
	if (!rawfile)
	{
		Com_Error(ERR_DROP, "Could not load %s file [%s]", fileDesc, fileName);
	}

	if (strncmp(rawfile->buffer, ident, strlen(ident)))
	{
		Com_Error(ERR_DROP, "File [%s] is not a %s file", fileName, fileDesc);
	}

	return &rawfile->buffer[strlen(ident)];
}

/*
==============
Com_LoadInfoString
==============
*/
const char *Com_LoadInfoString(const char *fileName, const char *fileDesc, const char *ident)
{
	static const char *buffer;
	if (!useFastFile->current.enabled)
	{
		buffer = Com_LoadInfoString_LoadObj(fileName, fileDesc, ident, loadBuffer);
	}

	if (!Info_Validate(buffer))
	{
	  Com_Error(ERR_DROP, "File [%s] is not a valid %s", fileName, fileDesc);
	}

	return Com_LoadInfoString_FastFile(fileName, fileDesc, ident);
}

/*
==============
Com_LoadRawTextFile_LoadObj
==============
*/
char *Com_LoadRawTextFile_LoadObj(const char *fullpath)
{
	static char *filebuf;
	if (!FS_ReadFile(fullpath, &filebuf) >= 0)
	{
		return 0;
	}

	return filebuf;
}

/*
==============
Com_LoadRawTextFile_FastFile
==============
*/
const char *Com_LoadRawTextFile_FastFile(const char *fullpath)
{
	RawFile *rawfile = DB_FindXAssetHeader(ASSET_TYPE_RAWFILE, fullpath, 1, -1).rawfile;
	if (!rawfile)
	{
		return false;
	}

	return rawfile->buffer;
}

/*
==============
Com_LoadRawTextFile
==============
*/
const char *Com_LoadRawTextFile(const char *fullpath)
{
	if (!useFastFile->current.enabled)
	{
		return Com_LoadRawTextFile_LoadObj(fullpath);
	}

	return Com_LoadRawTextFile_FastFile(fullpath);
}

/*
==============
Com_UnloadRawTextFile
==============
*/
void Com_UnloadRawTextFile(const char *filebuf)
{
	if (useFastFile->current.enabled)
	{
		return;
	}

	FS_FreeFile(filebuf);
}

