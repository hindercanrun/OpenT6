#include "types.h"

/*
==============
Scr_StubErrorReport
==============
*/
void Scr_StubErrorReport(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_ServerStubFunctionUseError
==============
*/
void Scr_ServerStubFunctionUseError()
{
	Scr_StubErrorReport(SCRIPTINSTANCE_SERVER);
}

/*
==============
Scr_ClientStubFunctionUseError
==============
*/
void Scr_ClientStubFunctionUseError()
{
	Scr_StubErrorReport(SCRIPTINSTANCE_CLIENT);
}

/*
==============
GetFunction
==============
*/
void (*GetFunction(
	scriptInstance_t inst,
	const char **pName,
	int *type,
	int *min_args,
	int *max_args))()
{
	if (inst)
		return CScr_GetFunction(pName, type, min_args, max_args);
	else
		return Scr_GetFunction(pName, type, min_args, max_args);
}

/*
==============
GetMethod
==============
*/
void (*GetMethod(
	scriptInstance_t inst,
	const char **pName,
	int *type,
	int *min_args,
	int *max_args))(scr_entref_t)
{
	if (inst)
		return CScr_GetMethod(pName, type, min_args, max_args);
	else
		return Scr_GetMethod(pName, type, min_args, max_args);
}

/*
==============
Scr_AutoExecFunctions
==============
*/
void Scr_AutoExecFunctions(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_IsBinaryObj
==============
*/
char Scr_IsBinaryObj(void *obj)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Scr_GetGSCObj
==============
*/
XModelPiece *Scr_GetGSCObj(scriptInstance_t inst, const char *name, bool appendExtension, bool errorIfMissing)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_ResolveScriptFunction
==============
*/
char Scr_ResolveScriptFunction(scriptInstance_t inst, GSC_OBJ *prime_obj, GSC_IMPORT_ITEM *import, unsigned __int8 op, bool is_pushfunc)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
LoadScriptGDB
==============
*/
void LoadScriptGDB(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
LoadScriptGDB
==============
*/
void LoadScriptGDB(scriptInstance_t inst, objFileInfo_t *fileInfo)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
GscBuiltinProfileData
==============
*/
_gscBuiltinProfileInfo_t *GscBuiltinProfileData(scriptInstance_t inst, const char *name, void (*func)())
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
GscBuiltinProfileData
==============
*/
_gscBuiltinProfileInfo_t *GscBuiltinProfileData(scriptInstance_t inst, const char *name, void (*method)(scr_entref_t))
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SL_GetCanonicalString
==============
*/
const char *SL_GetCanonicalString(unsigned int canonId)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SL_GetCanonicalString
==============
*/
unsigned int SL_GetCanonicalString(const char *string, bool is_static)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Scr_GetFunctionHandle
==============
*/
unsigned __int8 *Scr_GetFunctionHandle(scriptInstance_t inst, const char *filename, const char *name, unsigned int *checksum, bool errorIfMissing)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_GetFunctionHandle
==============
*/
unsigned __int8 *Scr_GetFunctionHandle(scriptInstance_t inst, unsigned __int8 *addr, int *func_index, unsigned int *checksum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_GetFunctionHandle
==============
*/
unsigned __int8 *Scr_GetFunctionHandle(scriptInstance_t inst, unsigned __int8 *addr, const char **filename, const char **funcname, unsigned int *checksum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_GetDefaultFunctionHandle
==============
*/
unsigned __int8 *Scr_GetDefaultFunctionHandle(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_GetProfileInfo
==============
*/
gscProfileInfo_t *Scr_GetProfileInfo(scriptInstance_t inst, unsigned __int8 *addr)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_FindObjFileInfo
==============
*/
objFileInfo_t *Scr_FindObjFileInfo(scriptInstance_t inst, void *addr)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
LoadScriptSource
==============
*/
void LoadScriptSource(debugFileInfo_t *fileInfo)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_FindLineAddress
==============
*/
unsigned __int8 *Scr_FindLineAddress(scriptInstance_t __formal, objFileInfo_t *info, int lineNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_FindLineNum
==============
*/
int Scr_FindLineNum(scriptInstance_t __formal, objFileInfo_t *info, unsigned __int8 *pos)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Scr_GetObjFileInfo
==============
*/
objFileInfo_t *Scr_GetObjFileInfo(scriptInstance_t inst, const char *filename)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_SendFileList
==============
*/
void Scr_SendFileList(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_GetPosForFileAndLineNum
==============
*/
unsigned __int8 *Scr_GetPosForFileAndLineNum(scriptInstance_t inst, const char *filename, int linenum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Scr_GetFileAndLineNum
==============
*/
void Scr_GetFileAndLineNum(scriptInstance_t inst, unsigned __int8 *pos, const char **filename, int *lineNum, const char **sourceLine)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
_ReportDeadCodeDebugger
==============
*/
void _ReportDeadCodeDebugger(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_ReportDeadCode
==============
*/
void Scr_ReportDeadCode()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_ReportDeadCodeDebugger
==============
*/
void Scr_ReportDeadCodeDebugger()
{
	_ReportDeadCodeDebugger(SCRIPTINSTANCE_SERVER);
	_ReportDeadCodeDebugger(SCRIPTINSTANCE_CLIENT);
}

/*
==============
_ReportScriptProfilerDebugger
==============
*/
void _ReportScriptProfilerDebugger(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_StopScriptProfiler
==============
*/
void Scr_StopScriptProfiler()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_StopScriptProfilerDebuggerReport
==============
*/
void Scr_StopScriptProfilerDebuggerReport(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
_ResetScriptProfiler
==============
*/
void _ResetScriptProfiler(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_ScriptProfilerActivate
==============
*/
void Scr_ScriptProfilerActivate(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_StartScriptProfiler
==============
*/
void Scr_StartScriptProfiler(scriptInstance_t inst, int type, int threshold)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_ScriptProfileUpdateTotalTime
==============
*/
void Scr_ScriptProfileUpdateTotalTime(scriptInstance_t inst, unsigned __int64 time)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
_AdjustThreadInstructionPointers
==============
*/
void _AdjustThreadInstructionPointers(scriptInstance_t inst, objFileInfo_t *objFileInfo, debugFileInfo_t *oldDebugInfo, unsigned __int8 **oldWaitOffsets, unsigned __int8 **waitOffsets, int waitCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
NextOpAddress
==============
*/
unsigned __int8 *NextOpAddress(unsigned __int8 *op)
{
	unsigned __int8 *next = op + 1;

	switch (*op)
	{
	case 4:
	case 5:
	case 25:
	case 36:
	case 39:
	case 47:
	case 49:
	case 51:
	case 53:
	case 84:
	case 94:
		next = op + 2;
		break;
	case 6:
	case 7:
	case 10:
	case 11:
	case 32:
	case 33:
	case 34:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
		next = (unsigned __int8 *)(((uintptr_t)(op + 2) & ~1) + 2);
		break;
	case 8:
	case 9:
	case 19:
	case 21:
	case 92:
		next = (unsigned __int8 *)(((uintptr_t)(op + 4) & ~3) + 4);
		break;
	case 23:
		int count = *(op + 1);
		next = op + 2;
		while (count--)
		{
			next = (unsigned __int8 *)(((uintptr_t)(next + 1) & ~1) + 2);
		}
		break;
	case 41:
	case 42:
	case 46:
	case 48:
	case 50:
	case 52:
		next = (unsigned __int8 *)(((uintptr_t)(op + 5) & ~3) + 4);
		break;
	case 89:
		uint32_t *aligned = (uint32_t *)((uintptr_t)(op + 4) & ~3);
		uint32_t count = *aligned;
		uint32_t *start = (uint32_t *)(((uintptr_t)aligned + 7) & ~3);
		next = (unsigned __int8 *)(start + 2 * count);
		break;
	default:
		break;
	}

	return next;
}

/*
==============
Scr_UpdateObj
==============
*/
void Scr_UpdateObj(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Scr_ResetObjCompile
==============
*/
void Scr_ResetObjCompile(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ReportObjLinkError
==============
*/
void ReportObjLinkError(scriptInstance_t inst, GSC_OBJ *prime_obj, objFileInfo_t *fileInfo, GSC_IMPORT_ITEM *import, char *errorString, int errorStringLength)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
GscObjResolve
==============
*/
int GscObjResolve(scriptInstance_t inst, GSC_OBJ *prime_obj, objFileInfo_t *objFileInfo)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
_GscObjLink
==============
*/
int _GscObjLink(scriptInstance_t inst, GSC_OBJ *prime_obj, objFileInfo_t *objFileInfo, bool is_bin_update)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
GscObjLink
==============
*/
int GscObjLink(scriptInstance_t inst, GSC_OBJ *prime_obj)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Scr_CheckPendingBinUpdate
==============
*/
void Scr_CheckPendingBinUpdate(scriptInstance_t inst)
{
	UNIMPLEMENTED(__FUNCTION__);
}

