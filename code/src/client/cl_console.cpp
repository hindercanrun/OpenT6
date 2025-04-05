#include "types.h"
#include "client_public.h"

#define COMMAND_HISTORY 32

const dvar_t* con_restricted;
const dvar_t* con_matchPrefixOnly;

Console con;

int con_inputMaxMatchesShown = 24;

/*
==============
TRACK_cl_console
==============
*/
void TRACK_cl_console()
{
	track_static_alloc_internal(&con, 82200, "con", 11);
}


/*
==============
Con_GetTextCopy
==============
*/
void Con_GetTextCopy()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_TimeJumped
==============
*/
void Con_TimeJumped()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_TimeNudged
==============
*/
void Con_TimeNudged()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ClearNotify
==============
*/
void Con_ClearNotify()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CheckResize

If the line width has changed, reformat the buffer.
==============
*/
void Con_CheckResize()
{ 
	con.screenMin[0] = floor(ScrPlace_ApplyX(&scrPlaceFull, 4.0f, 1));
	con.screenMin[1] = floor(ScrPlace_ApplyY(&scrPlaceFull, 4.0f, 1));
	con.screenMax[0] = floor(ScrPlace_ApplyX(&scrPlaceFull, -4.0f, 3));
	con.screenMax[1] = floor(ScrPlace_ApplyY(&scrPlaceFull, -4.0f, 3));

	if (!cls.consoleFont)
	{
		con.fontHeight = 0;
		con.visibleLineCount = 0;
		con.visiblePixelWidth = 0;
	}

	con.fontHeight = R_TextHeight(cls.consoleFont);
	assert(con.fontHeight > 0);

    con.visiblePixelWidth = (((con.screenMax[0] - con.screenMin.0) - 10.0f) - 18.0f);
    con.visibleLineCount = (((con.screenMax[1] - con.screenMin[1]) - (2 * con.fontHeight)) - 24.0f) / con.fontHeight;
}

/*
==============
Con_InitClientAssets
==============
*/
void Con_InitClientAssets()
{
	// check for console width changes from a vid mode change
	Con_CheckResize();
}

/*
==============
Con_ShutdownClientAssets
==============
*/
void Con_ShutdownClientAssets()
{
	return nullptr;
}

/*
==============
Con_InitMessageBuffer
==============
*/
void Con_InitMessageBuffer()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_AutoCompleteFromList
==============
*/
void Con_AutoCompleteFromList()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_TokenizeInput
==============
*/
void Con_TokenizeInput()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_AnySpaceAfterCommand
==============
*/
void Con_AnySpaceAfterCommand()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_TextAndOver
==============
*/
void ConDrawInput_TextAndOver()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_IsAutoCompleteMatch
==============
*/
void Con_IsAutoCompleteMatch()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_HasTooManyMatchesToShow
==============
*/
void Con_HasTooManyMatchesToShow()
{
	return conDrawInputGlob.matchCount > con_inputMaxMatchesShown;
}

/*
==============
Con_IsDvarCommand
==============
*/
bool Con_IsDvarCommand(const char *cmd)
{
	return !I_stricmp(cmd, "set")
		|| !I_stricmp(cmd, "seta")
		|| !I_stricmp(cmd, "sets")
		|| !I_stricmp(cmd, "reset")
		|| !I_stricmp(cmd, "toggle")
		|| I_stricmp(cmd, "togglep") == false;
}

/*
==============
Con_CycleAutoComplete
==============
*/
void Con_CycleAutoComplete()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CancelAutoComplete
==============
*/
char Con_CancelAutoComplete()
{
	if (conDrawInputGlob.matchIndex < 0 || !conDrawInputGlob.autoCompleteChoice[0])
	{
		return false;
	}

	conDrawInputGlob.matchIndex = nullptr;
	conDrawInputGlob.autoCompleteChoice[0] = nullptr;
	return true;
}

/*
==============
Con_AllowAutoCompleteCycling
==============
*/
void Con_AllowAutoCompleteCycling(bool isAllowed)
{
	conDrawInputGlob.mayAutoComplete = isAllowed;
}

/*
==============
Con_ShouldProcessMessage
==============
*/
void Con_ShouldProcessMessage()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CullFinishedLines
==============
*/
void Con_CullFinishedLines()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_GetMessageAlpha
==============
*/
void Con_GetMessageAlpha()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ShouldntDrawMessageWindow
==============
*/
void CL_ShouldntDrawMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawGameMessageWindow
==============
*/
void Con_DrawGameMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMiniConsole
==============
*/
void Con_DrawMiniConsole()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawErrors
==============
*/
void Con_DrawErrors()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
PrintTimeTotal
==============
*/
void Con_IsValidGameMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_IsGameMessageWindowActive
==============
*/
void Con_IsGameMessageWindowActive()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ToggleConsoleOutput
==============
*/
void Con_ToggleConsoleOutput()
{
	con.outputVisible = !con.outputVisible;
}

/*
==============
Con_PageUp
==============
*/
void Con_PageUp()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_PageDown
==============
*/
void Con_PageDown()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Top
==============
*/
void Con_Top()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Bottom
==============
*/
void Con_Bottom()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Close
==============
*/
void Con_Close()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_IsActive
==============
*/
void Con_IsActive()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_PlayTextFXPulseSounds
==============
*/
void CL_PlayTextFXPulseSounds()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_GetMessageBufferForGameMessageWindow
==============
*/
void Con_GetMessageBufferForGameMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ToggleConsole
==============
*/
void Con_ToggleConsole()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_OneTimeInit
==============
*/
void Con_OneTimeInit()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Init
==============
*/
void Con_Init()
{
	con_restricted = Dvar_RegisterBool(
		"monkeytoy",
		false,
		DVAR_ARCHIVE,
		"Restrict console access");
	con_matchPrefixOnly = Dvar_RegisterBool(
		"con_matchPrefixOnly",
		true,
		DVAR_ARCHIVE,
		"Only match the prefix when listing matching Dvars");

	Field_Clear(&g_consoleField);
	g_consoleField.widthInPixels = g_console_field_width;
	g_consoleField.charHeight = g_console_char_height;
	g_consoleField.fixedSize = true;
	for (int i = 0; i < COMMAND_HISTORY; ++i )
	{
		Field_Clear(&historyEditLines[i]);
		historyEditLines[i].widthInPixels = g_console_field_width;
		historyEditLines[i].charHeight = g_console_char_height;
		historyEditLines[i].fixedSize = true;
	}
	conDrawInputGlob.matchIndex = nullptr;

	Cmd_AddCommandInternal("chatmodepublic", Con_ChatModePublic_f, &Con_ChatModePublic_f_VAR);
	Cmd_AddCommandInternal("chatmodeteam", Con_ChatModeTeam_f, &Con_ChatModeTeam_f_VAR);
	Cmd_AddCommandInternal("clear", Con_Clear_f, &Con_Clear_f_VAR);
	Cmd_AddCommandInternal("con_echo", Con_Echo_f, &Con_Echo_f_VAR);

	// init if not already init'd
	if (!con.initialized)
	{
		Con_OneTimeInit();
		// this is bad, throw an assert if console STILL isn't init'd
		assert(!con.initialized);
	}
}

/*
==============
CL_ConsolePrint
==============
*/
void CL_ConsolePrint()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ConsoleFixPosition
==============
*/
void CL_ConsoleFixPosition()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ReviveMessagePrint
==============
*/
void CL_ReviveMessagePrint()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DeathMessagePrint
==============
*/
void CL_DeathMessagePrint()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CommitToAutoComplete
==============
*/
void Con_CommitToAutoComplete()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawConsole
==============
*/
void Con_DrawConsole()
{
	// check for console width changes from a vid mode change
	Con_CheckResize();

	if (Key_IsCatcherActive(localClientNum, 1))
	{
		Con_DrawSolidConsole(localClientNum);
	}
}

/*
==============
Con_ChatModePublic_f
==============
*/
void Con_ChatModePublic_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_IsAutoCompleteMatch
==============
*/
void Con_ChatModeTeam_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ResetMessageWindowTimes
==============
*/
void Con_ResetMessageWindowTimes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_NudgeMessageWindowTimes
==============
*/
void Con_NudgeMessageWindowTimes()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ClearMessageWindow
==============
*/
void Con_ClearMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_InitMessageWindow
==============
*/
void Con_InitMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Clear_f
==============
*/
void Con_Clear_f()
{
	Con_ClearMessageWindow(&con.consoleWindow);
	con.lineOffset = nullptr;
	con.displayLineOffset = nullptr;
}

/*
==============
Con_GetDefaultMsgDuration
==============
*/
void Con_GetDefaultMsgDuration()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_UpdateMessage
==============
*/
void Con_UpdateMessage()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_FreeFirstMessageWindowLine
==============
*/
void Con_FreeFirstMessageWindowLine()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_NeedToFreeMessageWindowLine
==============
*/
void Con_NeedToFreeMessageWindowLine()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CopyCurrentConsoleLineText
==============
*/
void Con_CopyCurrentConsoleLineText()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
PrintableCharsCount
==============
*/
void PrintableCharsCount()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
GetNextValidPrintTimeForLine
==============
*/
void GetNextValidPrintTimeForLine()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_UpdateMessageWindowLine
==============
*/
void Con_UpdateMessageWindowLine()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_GetDestWindow
==============
*/
void Con_GetDestWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_UpdateNotifyMessage
==============
*/
void Con_UpdateNotifyMessage()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_UpdateNotifyLine
==============
*/
void Con_UpdateNotifyLine()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Linefeed
==============
*/
void Con_Linefeed()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_TextLineWrapPosition
==============
*/
void CL_TextLineWrapPosition()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_ConsolePrint_AddLine
==============
*/
void CL_ConsolePrint_AddLine()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_AddMessageChar
==============
*/
void CL_AddMessageChar(char *msg, unsigned int msgLen, unsigned int msgMaxLen, char c)
{
	assert(c != '\\0');
	assert(msgLen + 1 <= msgMaxLen);

	msg[msgLen] = c;
	return msgLen + 1;
}

/*
==============
CL_AddMessageString
==============
*/
void CL_AddMessageString()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_AddMessageIcon
==============
*/
void CL_AddMessageIcon()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============================================================================

DRAWING

==============================================================================
*/


/*
==============
ConDrawInput_TextWidth
==============
*/
int ConDrawInput_TextWidth(const char *text)
{
	assert(text);
	return R_TextWidth(text, 0, cls.consoleFont);
}

/*
==============
ConDrawInput_TextLimitChars
==============
*/
void ConDrawInput_TextLimitChars(const char *str, int maxChars, const float *color)
{
	assert(str);
	R_AddCmdDrawText(
		str,
		maxChars,
		cls.consoleFont,
		conDrawInputGlob.x,
		conDrawInputGlob.y + conDrawInputGlob.fontHeight,
		1.0f,
		1.0f,
		0.0f,
		color,
		LOCAL_CLIENT_FIRST);
}

/*
==============
ConDraw_Box
==============
*/
void ConDraw_Box(float x, float y, float w, float h, const float *color)
{
	float darkColor[4];


	darkColor[0] = 0.5f * *color;
	darkColor[1] = 0.5f * color[1];
	darkColor[2] = 0.5f * color[2];
	darkColor[3] = 0.5f * color[3];
	darkColor[3] = color[3];

	R_AddCmdDrawStretchPic(x, y, w, h, 0.0f, 0.0f, 0.0f, 0.0f, color, cls.whiteMaterial);
	R_AddCmdDrawStretchPic(x, y, 2.0f, h, 0.0f, 0.0f, 0.0f, 0.0f, darkColor, cls.whiteMaterial);
	R_AddCmdDrawStretchPic((x + w) - 2.0f, y, 2.0f, h, 0.0f, 0.0f, 0.0f, 0.0f, darkColor, cls.whiteMaterial);
	R_AddCmdDrawStretchPic(x, y, w, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, darkColor, cls.whiteMaterial);
	R_AddCmdDrawStretchPic(x, (y + h) - 2.0f, w, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, darkColor, cls.whiteMaterial);
}

/*
==============
ConDrawInput_Box
==============
*/
void ConDrawInput_Box(int lines, const float *color)
{
	ConDraw_Box(
		conDrawInputGlob.x - 6.0f,
		conDrawInputGlob.y - 6.0f,
		(con.screenMax[0] - con.screenMin[0]) - ((conDrawInputGlob.x - 6.0f) - con.screenMin[0]),
		(lines * conDrawInputGlob.fontHeight) + (2.0f * 6.0f),
		color);
}

/*
==============
Con_GetAutoCompleteColorCodedStringDiscontiguous
==============
*/
void Con_GetAutoCompleteColorCodedStringDiscontiguous()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_GetAutoCompleteColorCodedStringContiguous
==============
*/
void Con_GetAutoCompleteColorCodedStringContiguous()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_IncrMatchCounter
==============
*/
void ConDrawInput_IncrMatchCounter(const char *str)
{
	if (!Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen))
	{
		return;
	}

	if (conDrawInputGlob.matchCount == conDrawInputGlob.matchIndex)
	{
		I_strncpyz(conDrawInputGlob.autoCompleteChoice, str, sizeof(conDrawInputGlob));
	}

	++conDrawInputGlob.matchCount;
	if (!str[conDrawInputGlob.inputTextLen])
	{
		conDrawInputGlob.hasExactMatch = true;
	}
}

/*
==============
ConDrawInput_DvarMatch
==============
*/
void ConDrawInput_DvarMatch(const char *str)
{
	assert(str);
	if (!Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen))
	{
		return;
	}

	ConDrawInput_TextLimitChars(str, 24, con_inputDvarMatchColor);

	conDrawInputGlob.x = conDrawInputGlob.x + 200.0f;
	ConDrawInput_TextLimitChars(Dvar_GetVariantString(str), 40, con_inputDvarValueColor);

	conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
	conDrawInputGlob.x = conDrawInputGlob.leftX;
}

/*
==============
ConDrawInput_CompareStrings
==============
*/
void ConDrawInput_CompareStrings()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_AutoCompleteArg
==============
*/
void ConDrawInput_AutoCompleteArg()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_GetDvarDescriptionLines
==============
*/
void ConDrawInput_GetDvarDescriptionLines()
{
}

/*
==============
ConDrawInput_DetailedDvarMatch
==============
*/
void ConDrawInput_DetailedDvarMatch()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_DetailedCmdMatch
==============
*/
void ConDrawInput_DetailedCmdMatch()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_CmdMatch
==============
*/
void ConDrawInput_CmdMatch(const char *str)
{
	assert(str);
	if (!Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen))
	{
		return;
	}

	ConDrawInput_Text(str, con_inputCommandMatchColor);
	conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
	conDrawInputGlob.x = conDrawInputGlob.leftX;
}

/*
==============
Con_DrawAutoCompleteChoice
==============
*/
void Con_DrawAutoCompleteChoice()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawInputPrompt
==============
*/
void Con_DrawInputPrompt(LocalClientNum_t localClientNum)
{
	Field_Draw(localClientNum, &g_consoleField, conDrawInputGlob.x, conDrawInputGlob.y, 5, 5);
}

/*
==============
TypewriterSounds
==============
*/
void TypewriterSounds()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageLineOnHUD
==============
*/
void Con_DrawMessageLineOnHUD()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageWindowNewToOld
==============
*/
void Con_DrawMessageWindowNewToOld()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageWindowOldToNew
==============
*/
void Con_DrawMessageWindowOldToNew()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageWindow
==============
*/
void Con_DrawMessageWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawOutputScrollBar
==============
*/
void Con_DrawOutputScrollBar()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawOutputText
==============
*/
void Con_DrawOutputText()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawOuputWindow
==============
*/
void Con_DrawOuputWindow()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_Echo_f
==============
*/
void Con_Echo_f()
{
	Con_ToggleConsole();

	I_strncpyz(g_consoleField.buffer, "\\echo ", sizeof(g_consoleField));
	g_consoleField.cursor = strlen(g_consoleField.buffer);

	Field_AdjustScroll(LOCAL_CLIENT_FIRST, &scrPlaceFull, &g_consoleField);
}

/*
==============
Con_DrawInput

Draw the editline after a ] prompt
==============
*/
void Con_DrawInput(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawSolidConsole

Draws the console with the solid background
==============
*/
void Con_DrawSolidConsole(LocalClientNum_t localClientNum)
{
	Sys_EnterCriticalSection(CRITSECT_CONSOLE);

	if (con.lineOffset)
	{
		Con_Linefeed(localClientNum, con.prevChannel, 0);
	}

	Sys_LeaveCriticalSection(CRITSECT_CONSOLE);

	if (!Key_IsCatcherActive(localClientNum, 1))
	{
		con.outputVisible = false;
	}

	// draw the output window
	if (con.outputVisible)
	{
		Con_DrawOuputWindow();
	}

	// draw the input prompt
	Con_DrawInput(localClientNum);
}

//================================================================