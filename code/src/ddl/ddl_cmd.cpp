#include "types.h"

static cmd_function_s DDL_Cmd_GetAsset_f_VAR;
static cmd_function_s DDL_Cmd_Show_f_VAR;
static cmd_function_s DDL_Cmd_ShowMember_f_VAR;
static cmd_function_s DDL_Cmd_ShowPaths_f_VAR;

/*
==============
DDL_Cmd_GetAsset_f
==============
*/
void DDL_Cmd_GetAsset_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DDL_Cmd_Show_f
==============
*/
void DDL_Cmd_Show_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DDL_Cmd_ShowMember_f
==============
*/
void DDL_Cmd_ShowMember_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DDL_Cmd_ShowPaths_f
==============
*/
void DDL_Cmd_ShowPaths_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DDL_Cmd_Init
==============
*/
void DDL_Cmd_Init()
{
	Cmd_AddCommandInternal("ddlLoadAsset", DDL_Cmd_GetAsset_f, &DDL_Cmd_GetAsset_f_VAR);
	Cmd_AddCommandInternal("ddlShow", DDL_Cmd_Show_f, &DDL_Cmd_Show_f_VAR);
	Cmd_AddCommandInternal("ddlShowMember", DDL_Cmd_ShowMember_f, &DDL_Cmd_ShowMember_f_VAR);
	Cmd_AddCommandInternal("ddlShowPaths", DDL_Cmd_ShowPaths_f, &DDL_Cmd_ShowPaths_f_VAR);
}

