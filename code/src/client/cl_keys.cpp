#include "types.h"
#include "vars.h"
#include "client.h"
#include "client_public.h"
#include <client_mp/client_mp_public.h>

/*

key up events are sent even if in console mode

*/

#define COMMAND_HISTORY 32

PlayerKeyState playerKeys[MAX_LOCAL_CLIENTS];
field_t g_consoleField;
field_t	historyEditLines[COMMAND_HISTORY];

int	nextHistoryLine; // the last line in the history buffer, not masked
int	historyLine;	 // the line being displayed from history buffer

bool con_ignoreMatchPrefixOnly;
const char *s_completionString
int s_matchCount;
int s_prefixMatchCount;
char s_shortestMatch[1024];
int g_console_field_width;
float g_console_char_height;
bool s_shouldCompleteCmd = 1;
bool s_hasExactMatch;

const char *keynames[256];
int keyCatchers;

const dvar_t *con_matchPrefixOnly;

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
===========================================
command line completion
===========================================
*/

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
	if (con_ignoreMatchPrefixOnly && con_matchPrefixOnly->current.enabled
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
Console_IsRconCmd
==============
*/
BOOL Console_IsRconCmd(const char *commandString)
{
	return I_strncmp(commandString, "rcon", strlen("rcon")) == 0;
}

/*
==============
Console_IsClientDisconnected
==============
*/
bool Console_IsClientDisconnected()
{
	return CL_AllLocalClientsDisconnected();
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
	s_matchCount = 0;
	s_prefixMatchCount = 0;
	s_shortestMatch[0] = 0;

	if (searchCmds)
	{
		Cmd_ForEach(FindMatches);
		*matchLenAfterCmds = strlen(s_shortestMatch);
	}
	else
	{
		*matchLenAfterCmds = 0;
	}

	Dvar_ForEachName(FindMatches);

	*matchLenAfterDvars = strlen(s_shortestMatch);
}

/*
==============
CompleteCommand

perform Tab expansion
==============
*/
void CompleteCommand(LocalClientNum_t localClientNum)
{
	// only look at the first token for completion purposes
	s_completionString = Con_TokenizeInput();
	s_matchCount = 0;
	s_prefixMatchCount = 0;
	s_shortestMatch[0] = 0;

	if (*s_completionString)
	{
		const char* originalCommand = s_completionString;
		bool isDvarCommand = Cmd_Argc() > 1 && Con_IsDvarCommand(s_completionString);

		if (Cmd_Argc() > 1 && Con_IsDvarCommand(s_completionString))
		{
			s_completionString = Cmd_Argv(1);
		}

		int matchLenAfterCmds = 0;
		int matchLenAfterDvars = 0;

		if (con_matchPrefixOnly->current.enabled)
		{
			con_ignoreMatchPrefixOnly = 1;
			UpdateMatches(!isDvarCommand, &matchLenAfterCmds, &matchLenAfterDvars);

			if (s_matchCount > con_inputMaxMatchesShown)
			{
				con_ignoreMatchPrefixOnly = 0;
				UpdateMatches(!isDvarCommand, &matchLenAfterCmds, &matchLenAfterDvars);

				if (!s_matchCount)
				{
					con_ignoreMatchPrefixOnly = 1;
					UpdateMatches(!isDvarCommand, &matchLenAfterCmds, &matchLenAfterDvars);
				}
			}
		}
		else
		{
			con_ignoreMatchPrefixOnly = 0;
			UpdateMatches(!isDvarCommand, &matchLenAfterCmds, &matchLenAfterDvars);
		}

		if (s_matchCount)
		{
			field_t savedField;
			memcpy(&savedField, &g_consoleField, sizeof(savedField));

			bool useExactMatch = isDvarCommand || s_matchCount == 1 || s_hasExactMatch && Con_AnySpaceAfterCommand();

			if (isDvarCommand)
			{
				Com_sprintf(g_consoleField->buffer, 256, "\\%s %s", originalCommand, s_shortestMatch);
			}
			else
			{
				Com_sprintf(g_consoleField->buffer, 256, "\\%s", s_shortestMatch);
			}

			g_consoleField.cursor = strlen(g_consoleField.buffer);

			ConcatRemaining(savedField.buffer, s_completionString);

			if (useExactMatch)
			{
				if (!isDvarCommand)
				{
					if (Cmd_Argc() == 1)
					{
						I_strncat(g_consoleField.buffer, 256, " ");
					}
					else if (Cmd_Argc() == 2)
					{
						if (matchLenAfterCmds == matchLenAfterDvars)
						{
							//T6todo CompleteCmdArgument();
						}
						else
						{
							//T6todo CompleteDvarArgument();
						}
					}
				}

				g_consoleField.cursor = strlen(g_consoleField.buffer);
			}
			else if (Con_HasTooManyMatchesToShow())
			{
				Com_Printf(CON_CHANNEL_DONT_FILTER, "]%s\n", g_consoleField.buffer);

				// run through again, printing matches
				Cmd_ForEach(PrintMatches);
				Dvar_ForEachName(PrintMatches);
			}

			Cmd_EndTokenizedString();
			Field_AdjustScroll(localClientNum, &scrPlaceFull, &g_consoleField);
		}
		else
		{
			Cmd_EndTokenizedString();
		}
	}
	else
	{
		Cmd_EndTokenizedString();
	}
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
	if (!keynum == -1)
	{
		return playerKeys[localClientNum].keys[keynum].down;
	}
	return 0;
}

/*
==============
Key_StringToKeynum

Returns a key number to be used to index keys[] by looking at
the given string.  Single ascii characters return themselves, while
the K_* names are matched up.

0x11 will be interpreted as raw hex, which will allow new controlers

to be configured even if they don't have defined names.
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

Returns a string (either a single ascii char, a K_* name, or a 0x11 hex string) for the
given keynum.
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
	if (localClientNum != INVALID_LOCAL_CLIENT)
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
=============================================================================

EDIT FIELDS

=============================================================================
*/


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

Handles horizontal scrolling and cursor blinking
x, y, amd width are in pixels
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

Performs the basic line editing functions for the console,
in-game talk, and menu fields

Key events are used for non-printable characters, others are gotten from char events.
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
=============================================================================

CONSOLE LINE EDITING

==============================================================================
*/

/*
==============
Console_Key
==============
*/
void Console_Key(LocalClientNum_t localClientNum, int key)
{
	char v5; // not good

	int isShiftKeyDown = playerKeys[localClientNum].keys[K_SHIFT].down;
	int isCtrlKeyDown = playerKeys[localClientNum].keys[K_CTRL].down;
	int isAltKeyDown = playerKeys[localClientNum].keys[K_ALT].down;

	// ctrl-L clears screen
	if (key == 'l' && isCtrlKeyDown)
	{
		Cbuf_AddText(localClientNum, "clear\n");
		return;
	}

	// enter finishes the line
	if (key == K_ENTER || key == K_KP_ENTER)
	{
		if (Con_CommitToAutoComplete())
		{
			return;
		}

		Com_Printf(CON_CHANNEL_DONT_FILTER, "]%s\n", g_consoleField.buffer);

		// leading slash is an explicit command
		if (g_consoleField.buffer[0] == '\\' || g_consoleField.buffer[0] == '/')
		{
			Cbuf_AddText(localClientNum, &g_consoleField.buffer[1]); // valid command
		}
		else
		{
			if (!Console_IsClientDisconnected()
				|| !I_strnicmp(g_consoleField.buffer, "quit", 4)
				|| !I_strnicmp(g_consoleField.buffer, "kill", 4))
			{
				if (!g_consoleField.buffer[0])
				{
					return; // empty lines just scroll the console without adding to history
				}

				// other text will be chat messages if RCon is enabled
				if (Console_IsRconCmd(g_consoleField.buffer))
				{
					Cbuf_AddText(localClientNum, "cmd say ");
					Cbuf_AddText(localClientNum, g_consoleField.buffer);
					Cbuf_AddText(localClientNum, "\n");
				}
			}
			Cbuf_AddText(localClientNum, g_consoleField.buffer);
		}
		Cbuf_AddText(localClientNum, "\n");

		if (g_consoleField.buffer[0])
		{
			// copy line to history buffer
			qmemcpy(&historyEditLines[nextHistoryLine % COMMAND_HISTORY], &g_consoleField, sizeof(field_t));
			historyLine = ++nextHistoryLine;
		}

		Field_Clear(&g_consoleField);
		g_consoleField.widthInPixels = g_console_field_width;
		g_consoleField.charHeight = g_console_char_height;
		g_consoleField.fixedSize = true;

		if (Console_IsClientDisconnected())
		{
			SCR_UpdateScreen(); // force an update, because the command may take some time
		}
	}
	// command completion
	else if (key == K_TAB)
	{
		if (s_shouldCompleteCmd)
		{
			CompleteCommand(localClientNum);
		}
		else
		{
			Con_CycleAutoComplete(2 * (isShiftKeyDown == 0) - 1);
		}

		s_shouldCompleteCmd = 0;
	}
	else
	{
		if (key == K_UPARROW && isCtrlKeyDown)
		{
			Con_CycleAutoComplete(-1);
			return;
		}

		if (key == K_DOWNARROW && isCtrlKeyDown)
		{
			Con_CycleAutoComplete(1);
			return;
		}

		if (key == K_MWHEELUP && isShiftKeyDown)
		{
			v5 = 1;
		}
		else if (key == K_KP_UPARROW)
		{
			v5 = 1;
		}
		else
		{
			v5 = key == K_UPARROW || tolower(key) == 'p' && isCtrlKeyDown;
		}
	}

	// command history (ctrl-p ctrl-n for unix style)
	if (v5)
	{
		if (nextHistoryLine - historyLine < COMMAND_HISTORY && historyLine > 0)
		{
			--historyLine;
		}

		memcpy(&g_consoleField, &historyEditLines[historyLine % COMMAND_HISTORY], sizeof(g_consoleField));
		Field_AdjustScroll(&scrPlaceFull, &g_consoleField);
		Con_AllowAutoCompleteCycling(0);
	}
	else
	{
		char v4; // not good x2
		if (key == K_MWHEELDOWN && isShiftKeyDown)
		{
			v4 = 1;
		}
		else if (key == K_KP_DOWNARROW)
		{
			v4 = 1;
		}
		else
		{
			v4 = key == K_DOWNARROW || tolower(key) == 'n' && isCtrlKeyDown;
		}

		if (v4)
		{
			if (!Con_CycleAutoComplete(1) && historyLine != nextHistoryLine)
			{
				memcpy(&g_consoleField, &historyEditLines[++historyLine % COMMAND_HISTORY], sizeof(g_consoleField));
				Field_AdjustScroll(&scrPlaceFull, &g_consoleField);
			}
		}
		else
		{
			// console scrolling
			switch (key)
			{
			case K_PGUP:
				Con_PageUp();
				return;
			case K_PGDN:
				Con_PageDown();
				return;
			case K_MWHEELUP:
				Con_PageUp();

				if (isCtrlKeyDown) // hold <ctrl> to accelerate scrolling
				{
					Con_PageUp();
					Con_PageUp();
				}
				break;
			case K_MWHEELDOWN:
				Con_PageDown();

				if (isCtrlKeyDown) // hold <ctrl> to accelerate scrolling
				{
					Con_PageDown();
					Con_PageDown();
				}
				break;
			default:
				// ctrl-home = top of console
				if (key == K_HOME && isCtrlKeyDown)
				{
					Con_Top();
					return;
				}

				// ctrl-end = bottom of console
				if (key == K_END && isCtrlKeyDown)
				{
					Con_Bottom();
					return;
				}

				if (key == K_DEL || key == K_ESCAPE)
				{
					if (Con_CancelAutoComplete())
					{
						return;
					}
				}
				else if (key == K_RIGHTARROW
					|| key == K_KP_RIGHTARROW
					|| key == K_LEFTARROW
					|| key == K_KP_LEFTARROW
					|| key != K_BACKSPACE && !isCtrlKeyDown && !isAltKeyDown && !isShiftKeyDown)
				{
					Con_CommitToAutoComplete();
				}

				// pass to the normal editline routine
				if (Field_KeyDownEvent(localClientNum, &scrPlaceFull, &g_consoleField, key))
				{
					Con_AllowAutoCompleteCycling(1);
				}
				break;
			}
		}
	}
}

//============================================================================


/*
==============
Message_Key

In game talk message
==============
*/
void Message_Key(LocalClientNum_t localClientNum, int key)
{
	UNIMPLEMENTED(__FUNCTION__);
}

//============================================================================


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
	// register our functions
	Cmd_AddCommandInternal("bind", Key_Bind_f, &Key_Bind_f_VAR);
	Cmd_AddCommandInternal("bind2", Key_Bind2_f, &Key_Bind2_f_VAR);
	Cmd_AddCommandInternal("unbind", Key_Unbind_f, &Key_Unbind_f_VAR);
	Cmd_AddCommandInternal("unbind2", Key_Unbind2_f, &Key_Unbind2_f_VAR);
	Cmd_AddCommandInternal("unbindall", Key_Unbindall_f, &Key_Unbindall_f_VAR);
	Cmd_AddCommandInternal("unbindall2", Key_Unbindall2_f, &Key_Unbindall2_f_VAR);
	Cmd_AddCommandInternal("bindlist", Key_Bindlist_f, &Key_Bindlist_f_VAR);
	Cmd_AddCommandInternal("updateMustHaveBindings", Key_UpdateMustHaveBindings_f, &Key_UpdateMustHaveBindings_f_VAR);

	memset(keynames, 0, sizeof(keynames));

	// todo
	
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_KeyEvent

Called by the system for both key up and key down events
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

Normal keyboard characters, already shifted / capslocked / etc
==============
*/
void CL_CharEvent(LocalClientNum_t localClientNum, int key)
{
	PIXBeginNamedEvent(-1, "CL_CharEvent");

	if (DevGui_IsActive())
	{
		if (!Sys_IsRenderThread())
		{
			return;
		}
	}

	// the console key should never be used as a char
	if (key == K_GRAVE || key == K_TILDE)
	{
		return;
	}

	int keyCatchers = CL_GetLocalClientUIGlobals(localClientNum)->keyCatchers;

	if ((keyCatchers & 1) != 0)
	{
		if (key == K_BS && Con_CancelAutoComplete())
		{
			return;
		}

		CL_ConsoleCharEvent(localClientNum, key);
		return;
	}

	// distribute the key down event to the apropriate handler
	if ((keyCatchers & 0x20) != 0)
	{
		Field_CharEvent(localClientNum, ScrPlace_GetView(localClientNum), &playerKeys[localClientNum].chatField, key);
		return;
	}

	if ((keyCatchers & 8) != 0)
	{
		UI_KeyEvent(localClientNum, key | 0x400, 1);
		return;
	}

	if (CL_GetLocalClientConnectionState(localClientNum) == CA_DISCONNECTED)
	{
		CL_ConsoleCharEvent(localClientNum, key);
		return;
	}
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

Writes lines containing "bind key value"
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

