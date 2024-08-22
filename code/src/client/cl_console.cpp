#include "types.h"
#include "client_public.h"

Console con;

/*
==============
SetupChatField
==============
*/
void SetupChatField(const LocalClientNum_t localClientNum, int teamChat, int widthInPixels)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ChatModePublic_f
==============
*/
void Con_ChatModePublic_f()
{
	SetupChatField(LOCAL_CLIENT_FIRST, 0, 588);
}

/*
==============
Con_GetTextCopy
==============
*/
void Con_GetTextCopy(char *text, int maxSize)
{
	if (con.consoleWindow.activeLineCount)
	{
		int begin = con.consoleWindow.lines[con.consoleWindow.firstLineIndex].textBufPos;
		unsigned int end = con.consoleWindow.textBufPos;
		int totalSize = con.consoleWindow.textBufPos - begin;

		if (con.consoleWindow.textBufPos - begin < 0)
		{
			totalSize += con.consoleWindow.textBufSize;
		}

		if (totalSize > maxSize - 1)
		{
			begin += totalSize - (maxSize - 1);

			if (begin > con.consoleWindow.textBufSize)
			{
				begin -= con.consoleWindow.textBufSize;
			}

			totalSize = maxSize - 1;
		}

		if (begin >= con.consoleWindow.textBufPos)
		{
			memcpy(text, &con.consoleWindow.circularTextBuffer[begin], con.consoleWindow.textBufSize - begin);
			memcpy(&text[con.consoleWindow.textBufSize - begin], con.consoleWindow.circularTextBuffer, end);
		}

		else
		{
			memcpy(text, &con.consoleWindow.circularTextBuffer[begin], con.consoleWindow.textBufPos - begin);
		}

		text[totalSize] = 0;
	}

	else
	{
		*text = 0;
	}
}

/*
==============
Con_ResetMessageWindowTimes
==============
*/
void Con_ResetMessageWindowTimes(MessageWindow *msgwnd, int serverTime)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_TimeJumped
==============
*/
void Con_TimeJumped(int a1, MessageWindow *a2, LocalClientNum_t localClientNum, int serverTime)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_NudgeMessageWindowTimes
==============
*/
void Con_NudgeMessageWindowTimes(MessageWindow *msgwnd, int serverTimeNudge, int serverTime)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_TimeNudged
==============
*/
void Con_TimeNudged(LocalClientNum_t localClientNum, int serverTimeNudge)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ClearMessageWindow
==============
*/
void Con_ClearMessageWindow(MessageWindow *msgwnd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_ClearNotify
==============
*/
void Con_ClearNotify(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CheckResize
==============
*/
void Con_CheckResize()
{
	float v0 = ScrPlace_ApplyX(&scrPlaceFullUnsafe, 4.0, 1);
	con.screenMin.v[0] = floor(v0);
	float v1 = ScrPlace_ApplyY(&scrPlaceFullUnsafe, 4.0, 1);
	con.screenMin.v[1] = floor(v1);
	float v2 = ScrPlace_ApplyX(&scrPlaceFullUnsafe, -4.0, 3);
	con.screenMax.v[0] = floor(v2);
	float v3 = ScrPlace_ApplyY(&scrPlaceFullUnsafe, -4.0, 3);
	con.screenMax.v[1] = floor(v3);

	if (cls.consoleFont)
	{
		int fontHeight = R_TextHeight(cls.consoleFont);
		con.fontHeight = fontHeight;

		if (fontHeight <= 0)
		{
			fontHeight = con.fontHeight;
		}

		con.visiblePixelWidth = (((con.screenMax.v[0] - con.screenMin.v[0]) - 10.0) - 18.0);
		con.visibleLineCount = (((con.screenMax.v[1] - con.screenMin.v[1]) - (2 * fontHeight)) - 24.0) / fontHeight;
	}

	else
	{
		con.fontHeight = 0;
		con.visibleLineCount = 0;
		con.visiblePixelWidth = 0;
	}
}

/*
==============
Con_InitMessageWindow
==============
*/
void Con_InitMessageWindow(MessageWindow *msgwnd, Message *messages, MessageLine *lines, char *text, int lineCount, int padding, int textPoolSize, int scrollTime, int fadeIn, int fadeOut)
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

	con.lineOffset = 0;
	con.displayLineOffset = 0;
}

/*
==============
Con_InitClientAssets
==============
*/
void Con_InitClientAssets()
{
	Con_CheckResize();
}

/*
==============
Con_GetDefaultMsgDuration
==============
*/
int Con_GetDefaultMsgDuration(print_msg_dest_t dest)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_UpdateMessage
==============
*/
void Con_UpdateMessage(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int duration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_FreeFirstMessageWindowLine
==============
*/
void Con_FreeFirstMessageWindowLine(MessageWindow *msgwnd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_NeedToFreeMessageWindowLine
==============
*/
bool Con_NeedToFreeMessageWindowLine(MessageWindow *msgwnd, int charCount)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_CopyCurrentConsoleLineText
==============
*/
void Con_CopyCurrentConsoleLineText(MessageWindow *msgwnd, MessageLine *msgLine)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
LatestActiveTypewrittenLineIdx
==============
*/
int LatestActiveTypewrittenLineIdx(MessageWindow *msgwnd)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PrintableCharsCount
==============
*/
int PrintableCharsCount(const MessageWindow *msgwnd, MessageLine *line)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PrintTimeTotal
==============
*/
int PrintTimeTotal(MessageWindow *msgwnd, MessageLine *line)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
GetNextValidPrintTimeForLine
==============
*/
int GetNextValidPrintTimeForLine(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int flags)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_UpdateMessageWindowLine
==============
*/
void Con_UpdateMessageWindowLine(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int linefeed, int flags)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_GetDestWindow
==============
*/
MessageWindow *Con_GetDestWindow(LocalClientNum_t localClientNum, print_msg_dest_t dest)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
Con_UpdateNotifyMessage
==============
*/
void Con_UpdateNotifyMessage(LocalClientNum_t localClientNum, int channel, int duration, int flags)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_UpdateNotifyLine
==============
*/
void Con_UpdateNotifyLine(LocalClientNum_t localClientNum, int channel, bool lineFeed, int flags)
{
	UNIMPLEMENTED(__FUNCTION__);
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
CL_ConsolePrint_AddLine
==============
*/
char CL_ConsolePrint_AddLine(LocalClientNum_t localClientNum, int channel, const char *txt, int duration, int pixelWidth, char color, int flags)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_AddMessageChar
==============
*/
int CL_AddMessageChar(char *msg, unsigned int msgLen, unsigned int msgMaxLen, char c)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_AddMessageString
==============
*/
int CL_AddMessageString(char *msg, unsigned int msgLen, unsigned int msgMaxLen, const char *string)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
CL_AddMessageIcon
==============
*/
int CL_AddMessageIcon(char *msg, unsigned int msgLen, unsigned int msgMaxLen, Material *iconShader, float iconWidth, float iconHeight, bool horzFlipIcon)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_AutoCompleteFromList
==============
*/
void Con_AutoCompleteFromList(const char **strings, unsigned int stringCount, const char *prefix, char *completed, unsigned int sizeofCompleted)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_TokenizeInput
==============
*/
const char* Con_TokenizeInput()
{
	Cmd_TokenizeStringNoEval(g_consoleField.buffer);

	const char* v0 = Cmd_Argv(0);

	if (*v0 == 92 || *v0 == 47)
	{
		++v0;
	}

	if (isspace(*v0))
	{
		int v1;

		do
		{
			v1 = *++v0;
		}
		while (isspace(v1));
	}

	return v0;
}

/*
==============
Con_AnySpaceAfterCommand
==============
*/
char Con_AnySpaceAfterCommand()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ConDrawInput_Text
==============
*/
void ConDrawInput_Text(const char *str, const vec4_t *color)
{
	R_AddCmdDrawTextInternal(
		str,
		0x7FFFFFFF,
		cls.consoleFont,
		conDrawInputGlob.x,
		conDrawInputGlob.fontHeight + conDrawInputGlob.y,
		1.0,
		1.0,
		0.0,
		color,
		0);
}

/*
==============
ConDrawInput_TextLimitChars
==============
*/
void ConDrawInput_TextLimitChars(const char *str, int maxChars, const vec4_t *color)
{
	R_AddCmdDrawTextInternal(
		str,
		maxChars,
		cls.consoleFont,
		conDrawInputGlob.x,
		conDrawInputGlob.fontHeight + conDrawInputGlob.y,
		1.0,
		1.0,
		0.0,
		color,
		0);
}

/*
==============
ConDrawInput_TextAndOver
==============
*/
void ConDrawInput_TextAndOver(LocalClientNum_t localClientNum, const char *str, const vec4_t *color)
{
	ConDrawInput_Text(str, color);

	conDrawInputGlob.x = R_TextWidth(localClientNum, str, 0, cls.consoleFont) + conDrawInputGlob.x;
}

/*
==============
ConDraw_Box
==============
*/
void ConDraw_Box(float x, float y, float w, float h, const vec4_t *color)
{
	vec4_t darkColor;

	darkColor[0] = color[0] * 0.5;
	darkColor[1] = color[1] * 0.5;
	darkColor[2] = color[2] * 0.5;
	darkColor[3] = color[3];

	R_AddCmdDrawStretchPicInternal(x, y, w, h, 0.0, 0.0, 0.0, 0.0, color, cls.whiteMaterial);
	R_AddCmdDrawStretchPicInternal(x, y, 2.0, h, 0.0, 0.0, 0.0, 0.0, &darkColor, cls.whiteMaterial);
	R_AddCmdDrawStretchPicInternal((x + w) - 2.0, y, 2.0, h, 0.0, 0.0, 0.0, 0.0, &darkColor, cls.whiteMaterial);
	R_AddCmdDrawStretchPicInternal(x, y, w, 2.0, 0.0, 0.0, 0.0, 0.0, &darkColor, cls.whiteMaterial);
	R_AddCmdDrawStretchPicInternal(x, (y + h) - 2.0, w, 2.0, 0.0, 0.0, 0.0, 0.0, &darkColor, cls.whiteMaterial);
}

/*
==============
ConDrawInput_Box
==============
*/
void ConDrawInput_Box(int lines, const vec4_t *color)
{
	ConDraw_Box(
		conDrawInputGlob.x - 6.0,
		conDrawInputGlob.y - 6.0,
		(con.screenMax.v[0] - con.screenMin.v[0]) - ((conDrawInputGlob.x - 6.0) - con.screenMin.v[0]),
		(lines * conDrawInputGlob.fontHeight) + 12.0,
		color);
}

/*
==============
Con_GetAutoCompleteColorCodedStringDiscontiguous
==============
*/
int Con_GetAutoCompleteColorCodedStringDiscontiguous(const char *query, const char *matchToText, int matchTextLen, char *colorCoded)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_GetAutoCompleteColorCodedStringContiguous
==============
*/
int Con_GetAutoCompleteColorCodedStringContiguous(const char *query, const char *matchToText, int matchTextLen, char *colorCoded)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_IsAutoCompleteMatch
==============
*/
bool Con_IsAutoCompleteMatch(const char *query, const char *matchToText, int matchTextLen)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ConDrawInput_IncrMatchCounter
==============
*/
void ConDrawInput_IncrMatchCounter(const char *str)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_DvarMatch
==============
*/
void ConDrawInput_DvarMatch(const char *str)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CG_SortPlayersAlphabeticallyComparator
==============
*/
int CG_SortPlayersAlphabeticallyComparator(const void *a, const void *b)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ConDrawInput_TextFieldFirstArgChar
==============
*/
int ConDrawInput_TextFieldFirstArgChar()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
ConDrawInput_AutoCompleteArg
==============
*/
void ConDrawInput_AutoCompleteArg(LocalClientNum_t localClientNum, const char **stringList, int stringCount)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_GetDvarDescriptionLines
==============
*/
int ConDrawInput_GetDvarDescriptionLines(const dvar_t *dvar)
{
	int result;

	const char* desc = Dvar_GetDescription(dvar);
	signed int v2 = strlen(desc);
	signed int v3 = 0;

	for (result = 1; v3 < v2; ++v3)
	{
		if (desc[v3] == 10)
		{
			++result;
		}
	}

	return result;
}

/*
==============
ConDrawInput_DetailedDvarMatch
==============
*/
void ConDrawInput_DetailedDvarMatch(LocalClientNum_t localClientNum, const char *str)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ConDrawInput_DetailedCmdMatch
==============
*/
void ConDrawInput_DetailedCmdMatch(LocalClientNum_t localClientNum, const char *str)
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
	if (Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen))
	{
		ConDrawInput_Text(str, &con_inputCommandMatchColor);

		conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
		conDrawInputGlob.x = conDrawInputGlob.leftX;
	}
}

/*
==============
Con_DrawAutoCompleteChoice
==============
*/
void Con_DrawAutoCompleteChoice(LocalClientNum_t localClientNum, bool isDvarCommand, const char *originalCommand)
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
	Field_Draw(localClientNum, &g_consoleField, conDrawInputGlob.x, conDrawInputGlob.y, 5, 5, 0);
}

/*
==============
Con_HasTooManyMatchesToShow
==============
*/
BOOL Con_HasTooManyMatchesToShow()
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
		|| I_stricmp(cmd, "togglep") == 0;
}

/*
==============
Con_CycleAutoComplete
==============
*/
char Con_CycleAutoComplete(int step)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
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
		return 0;
	}

	conDrawInputGlob.matchIndex = -1;
	conDrawInputGlob.autoCompleteChoice[0] = 0;

	return 1;
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
TypewriterSounds
==============
*/
void TypewriterSounds(LocalClientNum_t localClientNum, const MessageWindow *msgwnd, MessageLine *line)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageLineOnHUD
==============
*/
void Con_DrawMessageLineOnHUD(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, int x, int y, int charHeight, int horzAlign, int vertAlign, Font_s *font, const MessageWindow *msgwnd, int lineIdx, vec4_t *color, int textStyle, float msgwndScale, int textAlignMode)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CullFinishedLines
==============
*/
void Con_CullFinishedLines(int serverTime, MessageWindow *msgwnd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_GetMessageAlpha
==============
*/
double Con_GetMessageAlpha(Message *message, MessageWindow *msgwnd, int serverTime, bool scrollsIntoPlace)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_DrawMessageWindowNewToOld
==============
*/
void Con_DrawMessageWindowNewToOld(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int x, int y, int hudCharHeight, int horzAlign, int vertAlign, bool up, Font_s *font, vec4_t *color, int textStyle, float msgwndScale, int textAlignMode)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageWindowOldToNew
==============
*/
void Con_DrawMessageWindowOldToNew(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int x, int y, int charHeight, int horzAlign, int vertAlign, bool up, Font_s *font, vec4_t *color, int textStyle, float msgwndScale, int textAlignMode)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMessageWindow
==============
*/
void Con_DrawMessageWindow(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int x, int y, int charHeight, int horzAlign, int vertAlign, Font_s *font, vec4_t *color, int textStyle, float msgwndScale, msgwnd_mode_t mode, int textAlignMode)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawGameMessageWindow
==============
*/
void Con_DrawGameMessageWindow(LocalClientNum_t localClientNum, int windowIndex, int xPos, int yPos, int horzAlign, int vertAlign, Font_s *font, float fontScale, vec4_t *color, int textStyle, int textAlignMode, msgwnd_mode_t mode)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawMiniConsole
==============
*/
void Con_DrawMiniConsole(LocalClientNum_t localClientNum, int xPos, int yPos, float alpha)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawErrors
==============
*/
void Con_DrawErrors(LocalClientNum_t localClientNum, int xPos, int yPos, float alpha)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_IsValidGameMessageWindow
==============
*/
BOOL Con_IsValidGameMessageWindow(int windowIndex)
{
	return windowIndex <= 3;
}

/*
==============
Con_IsGameMessageWindowActive
==============
*/
bool Con_IsGameMessageWindowActive(LocalClientNum_t localClientNum, int windowIndex)
{
	return con.messageBuffer[localClientNum].gamemsgWindows[windowIndex].activeLineCount > 0;
}

/*
==============
Con_DrawSay
==============
*/
void Con_DrawSay(LocalClientNum_t localClientNum, int x, int y)
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
Con_DrawOutputScrollBar
==============
*/
void Con_DrawOutputScrollBar(float x, float y, float width, float height)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawOutputText
==============
*/
void Con_DrawOutputText(float x, float y)
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
Con_PageUp
==============
*/
void Con_PageUp()
{
	con.displayLineOffset -= 2;

	if (con.displayLineOffset < con.visibleLineCount)
	{
		con.displayLineOffset = con.visibleLineCount;

		if (con.consoleWindow.activeLineCount < con.visibleLineCount)
		{
			con.displayLineOffset = con.consoleWindow.activeLineCount;
		}
	}
}

/*
==============
Con_PageDown
==============
*/
void Con_PageDown()
{
	int v0 = con.displayLineOffset + 2;
	con.displayLineOffset = con.consoleWindow.activeLineCount;

	if (v0 < con.consoleWindow.activeLineCount)
	{
		con.displayLineOffset = v0;
	}
}

/*
==============
Con_Top
==============
*/
void Con_Top()
{
	con.displayLineOffset = con.visibleLineCount;

	if (con.consoleWindow.activeLineCount < con.visibleLineCount)
	{
		con.displayLineOffset = con.consoleWindow.activeLineCount;
	}
}

/*
==============
Con_Bottom
==============
*/
void Con_Bottom()
{
	con.displayLineOffset = con.consoleWindow.activeLineCount;
}

/*
==============
Con_Close
==============
*/
void Con_Close(LocalClientNum_t localClientNum)
{
	if ((clientUIActives[localClientNum].flags & 2) != 0)
	{
		Field_Clear(&g_consoleField);

		if (conDrawInputGlob.matchIndex >= 0)
		{
			if (conDrawInputGlob.autoCompleteChoice[0])
			{
				conDrawInputGlob.matchIndex = -1;
				conDrawInputGlob.autoCompleteChoice[0] = 0;
			}
		}

		Con_ClearNotify(localClientNum);

		Con_ClearMessageWindow(&con.messageBuffer[localClientNum].miniconWindow);
		Con_ClearMessageWindow(&con.messageBuffer[localClientNum].errorWindow);
		keyCatchers &= ~1u;
	}
}

/*
==============
Con_IsActive
==============
*/
bool Con_IsActive(LocalClientNum_t localClientNum)
{
	return Key_IsCatcherActive(localClientNum, 1);
}

/*
==============
CL_PlayTextFXPulseSounds
==============
*/
void CL_PlayTextFXPulseSounds(LocalClientNum_t localClientNum, int currentTime, int strLength, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int *soundTimeKeeper)
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
	Field_Clear(&g_consoleField);

	if (conDrawInputGlob.matchIndex >= 0 && conDrawInputGlob.autoCompleteChoice[0])
	{
		conDrawInputGlob.matchIndex = -1;
		conDrawInputGlob.autoCompleteChoice[0] = 0;
	}

	g_consoleField.widthInPixels = g_console_field_width;
	keyCatchers ^= 1u;
	g_consoleField.charHeight = g_console_char_height;
	g_consoleField.fixedSize = 1;
	con.outputVisible = 0;
}

/*
==============
Con_Echo_f
==============
*/
void Con_Echo_f()
{
	Con_ToggleConsole();

	I_strncpyz(g_consoleField.buffer, "\\echo ", 256);
	g_consoleField.cursor = strlen(g_consoleField.buffer);
	Field_AdjustScroll(LOCAL_CLIENT_FIRST, &scrPlaceFull, &g_consoleField);
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
	int *p_widthInPixels;

	cl_deathMessageWidth = Dvar_RegisterInt("cl_deathMessageWidth", 320, 1, 640, 0, "Pixel width of the obituary area");

	Field_Clear(&g_consoleField);

	g_consoleField.widthInPixels = g_console_field_width;
	g_consoleField.charHeight = g_console_char_height;
	g_consoleField.fixedSize = 1;
	p_widthInPixels = &historyEditLines[0].widthInPixels;

	// messy asf
	do
	{
		Field_Clear((field_t *)(p_widthInPixels - 3));
		float v1 = g_console_char_height;
		*p_widthInPixels = g_console_field_width;
		*(p_widthInPixels + 1) = v1;
		p_widthInPixels[2] = 1;
		p_widthInPixels += 70;
	}
	while (p_widthInPixels < &dword_125CC14);

	conDrawInputGlob.matchIndex = -1;

	Cmd_AddCommandInternal("chatmodepublic", Con_ChatModePublic_f, &Con_ChatModePublic_f_VAR);
	Cmd_AddCommandInternal("clear", Con_Clear_f, &Con_Clear_f_VAR);
	Cmd_AddCommandInternal("con_echo", Con_Echo_f, &Con_Echo_f_VAR);

	if (!con.initialized)
	{
		Con_OneTimeInit();
	}
}

/*
==============
CL_ConsolePrint
==============
*/
void CL_ConsolePrint(
		LocalClientNum_t localClientNum,
		int channel,
		const char *txt,
		int duration,
		int pixelWidth,
		int flags)
{
	if (!Dvar_GetBool(cl_noprint) && channel != 8)
	{
		if (!con.initialized)
		{
			Con_OneTimeInit();
		}

		Con_IsChannelVisible(CON_DEST_CONSOLE, channel, flags);
		Sys_EnterCriticalSection(CRITSECT_CONSOLE);
		CL_ConsolePrint_AddLine(localClientNum, channel, txt, duration, pixelWidth, 55, flags);
		Sys_LeaveCriticalSection(CRITSECT_CONSOLE);
	}
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
void CL_ReviveMessagePrint(unsigned int a1, LocalClientNum_t localClientNum, const char *reviveString, Material *iconShader, float iconWidth, float iconHeight, char *horzFlipIcon)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
CL_DeathMessagePrint
==============
*/
void CL_DeathMessagePrint(LocalClientNum_t localClientNum, const char *attackerName, char attackerColorIndex, const char *victimName, int victimColorIndex, Material *iconShader, float iconWidth, float iconHeight, unsigned int horzFlipIcon)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_DrawInput
==============
*/
void Con_DrawInput(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Con_CommitToAutoComplete
==============
*/
char Con_CommitToAutoComplete()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Con_DrawSolidConsole
==============
*/
void Con_DrawSolidConsole(LocalClientNum_t localClientNum)
{
	Sys_EnterCriticalSection(CRITSECT_CONSOLE);

	if (con.lineOffset)
	{
		Con_UpdateNotifyLine(localClientNum, con.prevChannel, 1, 0);

		con.lineOffset = 0;
		if (con.displayLineOffset == con.consoleWindow.activeLineCount - 1)
		{
			++con.displayLineOffset;
		}
	}

	Sys_LeaveCriticalSection(CRITSECT_CONSOLE);

	if (Key_IsCatcherActive(localClientNum, 1))
	{
		if (con.outputVisible)
		{
			Con_DrawOuputWindow();
		}

		Con_DrawInput(localClientNum);
	}

	else
	{
		con.outputVisible = 0;
		Con_DrawInput(localClientNum);
	}
}

/*
==============
Con_DrawConsole
==============
*/
void Con_DrawConsole(LocalClientNum_t localClientNum)
{
	Con_CheckResize();

	if (Key_IsCatcherActive(localClientNum, 1))
	{
		Con_DrawSolidConsole(localClientNum);
	}
}

