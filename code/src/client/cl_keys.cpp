#include "types.h"
#include "vars.h"
#include "client_public.h"
#include <client_mp/client_mp_public.h>

PlayerKeyState playerKeys[MAX_LOCAL_CLIENTS];
field_t g_consoleField;

bool con_ignoreMatchPrefixOnly;
char s_shortestMatch[1024];
const char *keynames[256];
int keyCatchers;

cmd_function_s Key_Bind_f_VAR;
cmd_function_s Key_Bind2_f_VAR;
cmd_function_s Key_Unbind_f_VAR;
cmd_function_s Key_Unbind2_f_VAR;
cmd_function_s Key_Unbindall_f_VAR;
cmd_function_s Key_Unbindall2_f_VAR;
cmd_function_s Key_Bindlist_f_VAR;
cmd_function_s Key_UpdateMustHaveBindings_f_VAR;

/*
==============
Field_AdjustScroll
==============
*/
void Field_AdjustScroll(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Field_Paste
==============
*/
char Field_Paste(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit)
{
	const char *ClipboardData = Sys_GetClipboardData();
	char *v4 = ClipboardData;

	if ( !ClipboardData )
	{
		return 0;
	}

	signed int v6 = strlen(ClipboardData);
	for (signed int i = 0; i < v6; ++i)
	{
		Field_CharEvent(localClientNum, scrPlace, edit, v4[i]);
	}

	Sys_FreeClipboardData(v4);

	return 1;
}

/*
==============
FindMatches
==============
*/
void FindMatches(const char *s)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
PrintMatches
==============
*/
void PrintMatches(const char *s)
{
	if (con_ignoreMatchPrefixOnly && Dvar_GetBool(con_matchPrefixOnly)
		|| !I_strnicmp(s, s_shortestMatch, strlen(s_shortestMatch)))
	{
		if (I_stristr(s, s_shortestMatch))
		{
			Com_Printf(0, "    %s\n", s);
		}
	}
}

/*
==============
keyConcatArgs
==============
*/
int keyConcatArgs()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ReplaceConsoleInputArgument
==============
*/
void ReplaceConsoleInputArgument(int replaceCount, const char *replacement)
{
	signed int i;

	if (*replacement)
	{
		for (i = strlen(g_consoleField.buffer); i; --i)
		{
			if (!isspace(*(i + 18954375)))
			{
				break;
			}
		}

		if (replaceCount >= i)
		{
			I_strncpyz(&g_consoleField.buffer[i - replaceCount], replacement, 256 - (i - replaceCount));
		}
	}
}

/*
==============
CompleteCmdArgument
==============
*/
void CompleteCmdArgument()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CompleteDvarArgument
==============
*/
void CompleteDvarArgument()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
UpdateMatches
==============
*/
void UpdateMatches(bool searchCmds, int *matchLenAfterCmds, int *matchLenAfterDvars)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CompleteCommand
==============
*/
void CompleteCommand(int *a1, LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Console_IsScrollUpKey
==============
*/
bool Console_IsScrollUpKey(int key, int isShiftDown, int isCtrlDown)
{
	switch (key)
	{
	case 206:
		if (isShiftDown)
		{
			return 1;
		}
		break;
	case 183:
		return 1;
	case 154:
		return 1;
	}

	return tolower(key) == 112 && isCtrlDown;
}

/*
==============
Console_IsScrollDownKey
==============
*/
bool Console_IsScrollDownKey(int key, int isShiftDown, int isCtrlDown)
{
	switch (key)
	{
	case 205:
		if (isShiftDown)
		{
			return 1;
		}
		break;
	case 189:
		return 1;
	case 155:
		return 1;
	}

	return tolower(key) == 110 && isCtrlDown;
}

/*
==============
Key_GetOverstrikeMode
==============
*/
int Key_GetOverstrikeMode(LocalClientNum_t localClientNum)
{
	return playerKeys[localClientNum].overstrikeMode;
}

/*
==============
Key_SetOverstrikeMode
==============
*/
void Key_SetOverstrikeMode(LocalClientNum_t localClientNum, int state)
{
	playerKeys[localClientNum].overstrikeMode = state;
}

/*
==============
Key_IsDown
==============
*/
int Key_IsDown(LocalClientNum_t localClientNum, int keynum)
{
	if (keynum == -1)
	{
		return 0;
	}
	else
	{
		return playerKeys[localClientNum].keys[keynum].down;
	}
}

/*
==============
Key_StringToKeynum
==============
*/
int Key_StringToKeynum(LocalClientNum_t localClientNum, const char *str)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_IsValidGamePadChar
==============
*/
BOOL Key_IsValidGamePadChar(const char key)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_KeynumToString
==============
*/
const char *Key_KeynumToString(int keynum, int translate)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Key_SetBinding
==============
*/
void Key_SetBinding(LocalClientNum_t localClientNum, int keynum, Bind_t binding, BindIndex_t index)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_SetBindingCheat
==============
*/
void Key_SetBindingCheat(LocalClientNum_t localClientNum, int keynum, const char *bindingCheat)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_SetBindings
==============
*/
void Key_SetBindings(LocalClientNum_t localClientNum, int *twokeys, Bind_t binding, BindIndex_t bindNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_GetBinding
==============
*/
Bind_t Key_GetBinding(LocalClientNum_t localClientNum, int keynum, BindIndex_t index)
{
	return playerKeys[localClientNum].keys[keynum].binding[index];
}

/*
==============
Key_GetCommandAssignmentInternal
==============
*/
int Key_GetCommandAssignmentInternal(LocalClientNum_t localClientNum, Bind_t binding, int *twokeys, BindIndex_t bindNum, int gamePadOnly)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_GetSafeFreeKey
==============
*/
int Key_GetSafeFreeKey(LocalClientNum_t localClientNum, BindIndex_t bindNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_GetMouseKeyboardCommandAssignment
==============
*/
int Key_GetMouseKeyboardCommandAssignment(LocalClientNum_t localClientNum, Bind_t binding, int *twokeys, BindIndex_t bindNum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_BindMustHaveCommands
==============
*/
void __cdecl Key_BindMustHaveCommands(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_UpdateMustHaveBindings_f
==============
*/
void Key_UpdateMustHaveBindings_f()
{
	Key_BindMustHaveCommands(LOCAL_CLIENT_FIRST);
}

/*
==============
Key_GetCommandAssignment
==============
*/
int Key_GetCommandAssignment(
	LocalClientNum_t localClientNum,
	Bind_t binding,
	int *twokeys,
	BindIndex_t bindNum)
{
	return Key_GetCommandAssignmentInternal(localClientNum, binding, twokeys, bindNum, 0);
}

/*
==============
Key_Unbind_f
==============
*/
void Key_Unbind_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_Unbind2_f
==============
*/
void Key_Unbind2_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_Unbindall_f
==============
*/
void Key_Unbindall_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_Unbindall2_f
==============
*/
void Key_Unbindall2_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_ClearStates
==============
*/
void Key_ClearStates(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_IsKeyPressed
==============
*/
int CL_IsKeyPressed(const LocalClientNum_t localClientNum, const char *keyName)
{
	int v2 = Key_StringToKeynum(localClientNum, keyName, 0);
	if (v2 < 0)
	{
		return 0;
	}

	return playerKeys[localClientNum].keys[v2].down;
}

/*
==============
Key_Shutdown
==============
*/
void Key_Shutdown()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_IsCatcherActive
==============
*/
bool Key_IsCatcherActive(LocalClientNum_t localClientNum, int mask)
{
	if (localClientNum == INVALID_LOCAL_CLIENT)
	{
		return 0;
	}
	return (mask & keyCatchers) != 0;
}

/*
==============
Key_AddCatcher
==============
*/
void Key_AddCatcher(LocalClientNum_t localClientNum, int orMask)
{
	if ( localClientNum != INVALID_LOCAL_CLIENT )
	{
		keyCatchers |= orMask;
	}
}

/*
==============
Key_RemoveCatcher
==============
*/
void Key_RemoveCatcher(LocalClientNum_t localClientNum, int andMask)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_SetCatcher
==============
*/
void Key_SetCatcher(LocalClientNum_t localClientNum, int catcher)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_GetBindingForCmd
==============
*/
Bind_t Key_GetBindingForCmd(const char *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
	Bind_t tmp;
	return tmp;
}

/*
==============
Key_GetCmdForBinding
==============
*/
const char *Key_GetCmdForBinding(Bind_t binding)
{
	return g_bindCommands[binding];
}

/*
==============
Field_DrawTextOverride
==============
*/
void Field_DrawTextOverride(LocalClientNum_t localClientNum, const field_t *edit, int x, int y, int horzAlign, int vertAlign, const char *str, int drawLen, int cursorPos, bool FullUnsafe)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Field_Draw
==============
*/
void Field_Draw(LocalClientNum_t localClientNum, field_t *edit, int x, int y, int horzAlign, int vertAlign, bool fullUnSafe)
{
	char str[1024];

	if ( !edit->drawWidth )
	{
		edit->drawWidth = 256;
	}

	I_strncpyz(str, &edit->buffer[edit->scroll], 256 - edit->scroll);

	Field_DrawTextOverride(
		localClientNum,
		edit,
		x,
		y,
		horzAlign,
		vertAlign,
		str,
		edit->drawWidth,
		edit->cursor - edit->scroll);
}

/*
==============
Field_KeyDownEvent
==============
*/
bool Field_KeyDownEvent(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit, int key)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Field_CharEvent
==============
*/
char Field_CharEvent(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit, int ch)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Console_Key
==============
*/
void Console_Key(LocalClientNum_t localClientNum, int key)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Message_Key
==============
*/
void Message_Key(LocalClientNum_t localClientNum, int key)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_GetBindingCheat
==============
*/
const char *Key_GetBindingCheat(LocalClientNum_t localClientNum, int keynum)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Key_GetCheatAssignmentInternal
==============
*/
int Key_GetCheatAssignmentInternal(LocalClientNum_t localClientNum, const char *command, int *twokeys, int gamePadOnly)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_IsCommandBound
==============
*/
BOOL Key_IsCommandBound(LocalClientNum_t localClientNum, const char *command, BindIndex_t bindIndex)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Key_Bind_f
==============
*/
void Key_Bind_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_Bind2_f
==============
*/
void Key_Bind2_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Key_Bindlist_f
==============
*/
void Key_Bindlist_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_InitKeyCommands
==============
*/
void CL_InitKeyCommands()
{
	Cmd_AddCommandInternal("bind", Key_Bind_f, &Key_Bind_f_VAR);
	Cmd_AddCommandInternal("bind2", Key_Bind2_f, &Key_Bind2_f_VAR);
	Cmd_AddCommandInternal("unbind", Key_Unbind_f, &Key_Unbind_f_VAR);
	Cmd_AddCommandInternal("unbind2", Key_Unbind2_f, &Key_Unbind2_f_VAR);
	Cmd_AddCommandInternal("unbindall", Key_Unbindall_f, &Key_Unbindall_f_VAR);
	Cmd_AddCommandInternal("unbindall2", Key_Unbindall2_f, &Key_Unbindall2_f_VAR);
	Cmd_AddCommandInternal("bindlist", Key_Bindlist_f, &Key_Bindlist_f_VAR);
	Cmd_AddCommandInternal("updateMustHaveBindings", Key_UpdateMustHaveBindings_f, &Key_UpdateMustHaveBindings_f_VAR);

	memset(keynames, 0, sizeof(keynames));
}

/*
==============
CL_KeyEvent
==============
*/
void CL_KeyEvent(LocalClientNum_t localClientNum, int key, const int down, const unsigned int time)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ConsoleCharEvent
==============
*/
void CL_ConsoleCharEvent(LocalClientNum_t localClientNum, int key)
{
	if (Field_CharEvent(localClientNum, &scrPlaceFull, &g_consoleField, key))
	{
		Con_AllowAutoCompleteCycling(1);
	}
}

/*
==============
CL_CharEvent
==============
*/
void CL_CharEvent(LocalClientNum_t localClientNum, int key)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_GetKeyBindingInternal
==============
*/
int CL_GetKeyBindingInternal(LocalClientNum_t localClientNum, const char *command, char (*keyNames)[128], int gamePadOnly, BindIndex_t bindNum)
{
	int keys[2];
	int bindCount;
	Bind_t bind;

	Sys_EnterCriticalSection(CRITSECT_KEY_BINDINGS);
	(*keyNames)[128] = 0;
	bind = Key_GetBindingForCmd(command);
	bindCount = Key_GetCommandAssignmentInternal(localClientNum, bind, keys, bindNum, gamePadOnly);
	assert((0) <= (bindCount) && (bindCount) <= (2));
	if (bindCount)
	{
		Key_KeynumToStringBuf(localClientNum, keys[0], (char*)keyNames, 128);
		if (bindCount == 2)
		{
			Key_KeynumToStringBuf(localClientNum, keys[1], &(*keyNames)[128], 128);
		}
		Sys_LeaveCriticalSection(CRITSECT_KEY_BINDINGS);
		return bindCount;
	}
	else
	{
		strcpy((char*)keyNames, "KEY_UNBOUND");
		Sys_LeaveCriticalSection(CRITSECT_KEY_BINDINGS);
		return 0;
	}
}

/*
==============
CL_GetKeyBinding
==============
*/
int CL_GetKeyBinding(LocalClientNum_t localClientNum, const char *command, char (*keyNames)[128], BindIndex_t bindNum)
{
	return CL_GetKeyBindingInternal(localClientNum, command, keyNames, 0, bindNum);
}

/*
==============
CL_GetGamePadBinding
==============
*/
int CL_GetGamePadBinding(LocalClientNum_t localClientNum, const char *command, char (*keyNames)[128], BindIndex_t bindNum)
{
	return CL_GetKeyBindingInternal(localClientNum, command, keyNames, 1, bindNum);
}

/*
==============
Key_WriteBindings
==============
*/
void Key_WriteBindings(LocalClientNum_t localClientNum, int f)
{
	char buffer[8192];

	Key_WriteBindingsToBuffer(localClientNum, buffer, sizeof(buffer));
	FS_Printf(f, "%s", buffer);
}

/*
==============
Key_WriteBindingsToBuffer
==============
*/
int Key_WriteBindingsToBuffer(LocalClientNum_t localClientNum, char* buffer, int bufferSize)
{
	//TODO
	return 0;

	int bytesUsed;
	const char* bind;
	KeyState* keys;
	int len;
	int keyIndex;

	keys = playerKeys[localClientNum].keys;
	bufferSize = bufferSize - 4;
	bytesUsed = 0;
	for (keyIndex = 0; keyIndex < 256; ++keyIndex)
	{
		if (keys[keyIndex].binding[0] && *&keys[keyIndex].binding[0] || keys[keyIndex].binding[1] && *&keys[keyIndex].binding[1])
		{
			if (keys[keyIndex].binding[0] && *&keys[keyIndex].binding[0])
			{
				len = Com_sprintf(&buffer[bytesUsed], bufferSize - bytesUsed, "bind %s \"", Key_KeynumToString(keyIndex, 0));
				if (len < 0)
				{
					return bytesUsed;
				}

				bytesUsed = len + bytesUsed;
				/*for (bind = keys[keyIndex].binding; *bind && bytesUsed < bufferSize; ++bind)
				{
					if (*bind == 34)
					{
						buffer[bytesUsed++] = 92;
					}
					buffer[bytesUsed++] = *bind;
				}*/
			}
		}
	}
}

