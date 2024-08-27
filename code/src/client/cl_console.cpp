#include "types.h"
#include "client_public.h"

Console con;
ConDrawInputGlob conDrawInputGlob;
field_t g_consoleField;
clientStatic_t cls;
ScreenPlacement scrPlaceFull;

int con_inputMaxMatchesShown;
int g_console_field_width;
float g_console_char_height;
int keyCatchers;

bool con_ignoreMatchPrefixOnly;

cmd_function_s Con_ChatModePublic_f_VAR;
cmd_function_s Con_Clear_f_VAR;
cmd_function_s Con_Echo_f_VAR;

float con_versionColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
float colorWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float con_inputDvarMatchColor[4] = { 1.0f, 1.0f, 0.80000001f, 1.0f };
float con_inputCommandMatchColor[4] = { 0.80000001f, 0.80000001f, 1.0f, 1.0f };

/*
==============
SetupChatField
==============
*/
void SetupChatField(LocalClientNum_t localClientNum, int teamChat, int widthInPixels)
{
	int width;
	int height;
	float aspect;

	CL_GetScreenDimensions(&width, &height, &aspect);

	playerKeys[localClientNum].chat_team = teamChat;
	PlayerKeyState *chatField = &playerKeys[localClientNum];

	Field_Clear(&chatField->chatField);

	chatField->chatField.widthInPixels = widthInPixels;
	chatField->chatField.fixedSize = 0;

	if (height <= 768)
	{
		chatField->chatField.charHeight = 16.0f;
	}
	else
	{
		chatField->chatField.charHeight = 10.f;
	}

	clientUIActive_t *LocalClientUIGlobals = CL_GetLocalClientUIGlobals(localClientNum);
	LocalClientUIGlobals->keyCatchers ^= 0x20u;
}

/*
==============
Con_ChatModePublic_f
==============
*/
void Con_ChatModePublic_f()
{
	if (Com_SessionMode_IsOnlineGame() || Com_SessionMode_IsMode(SESSIONMODE_SYSTEMLINK))
	{
		SetupChatField(0, 0, 588);
	}
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
	// todo make it nicer to look at

	int v7;
	Message *window;

	for (int i = 0; i < msgwnd->activeLineCount; window->endTime = serverTime + v7)
	{
		int lineCount = msgwnd->lineCount;
		unsigned int v4 = (i + msgwnd->firstLineIndex) % lineCount;
		MessageLine *v5 = &msgwnd->lines[v4];
		Message *messages = msgwnd->messages;

		intv7 = messages[v5->messageIndex].endTime - messages[v5->messageIndex].startTime;
		window = &messages[v5->messageIndex];
		++i;

		window->startTime = serverTime;
	}
}

/*
==============
Con_TimeJumped
==============
*/
void Con_TimeJumped(LocalClientNum_t localClientNum, int serverTime)
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
	int serverTime = CL_GetLocalClientGlobals(localClientNum)->serverTime;
	Con_NudgeMessageWindowTimes(&con.consoleWindow, serverTimeNudge, serverTime);

	LocalClientNum_t v4 = localClientNum;
	MessageWindow *gamemsgWindows = con.messageBuffer[localClientNum].gamemsgWindows;
	LocalClientNum_t localClientNuma = 4;

	do
	{
		Con_NudgeMessageWindowTimes(gamemsgWindows++, serverTimeNudge, serverTime);
		--localClientNuma;
	}
	while (localClientNuma);

	Con_NudgeMessageWindowTimes(&con.messageBuffer[v4].miniconWindow, serverTimeNudge, serverTime);
	Con_NudgeMessageWindowTimes(&con.messageBuffer[v4].errorWindow, serverTimeNudge, serverTime);
}

/*
==============
Con_ClearMessageWindow
==============
*/
void Con_ClearMessageWindow(MessageWindow *msgwnd)
{
	msgwnd->textBufPos = 0;
	msgwnd->messageIndex = 0;
	msgwnd->firstLineIndex = 0;
	msgwnd->activeLineCount = 0;
}

/*
==============
Con_ClearNotify
==============
*/
void Con_ClearNotify(LocalClientNum_t localClientNum)
{
	int *p_textBufPos = &con.messageBuffer[localClientNum].gamemsgWindows[0].textBufPos;
	int v2 = 4;

	do
	{
		*p_textBufPos = 0;
		p_textBufPos[3] = 0;
		p_textBufPos[1] = 0;
		p_textBufPos[2] = 0;
		p_textBufPos += 13;
		--v2;
	}

	while (v2);
}

/*
==============
Con_CheckResize
==============
*/
void Con_CheckResize()
{
	float x = ScrPlace_ApplyX(&scrPlaceFull, 4.0, 1);
	con.screenMin[0] = floor(x);

	float y = ScrPlace_ApplyY(&scrPlaceFull, 4.0, 1);
	con.screenMin[1] = floor(y);

	float width = ScrPlace_ApplyX(&scrPlaceFull, -4.0, 3);
	con.screenMax[0] = floor(width);

	float height = ScrPlace_ApplyY(&scrPlaceFull, -4.0, 3);
	con.screenMax[1] = floor(height);

	if (cls.consoleFont)
	{
		int fontHeight = R_TextHeight(cls.consoleFont);
		con.fontHeight = fontHeight;

		if (fontHeight <= 0)
		{
			fontHeight = con.fontHeight;
		}

		con.visiblePixelWidth = (((con.screenMax[0] - con.screenMin[0]) - 10.0) - 18.0);
		con.visibleLineCount = (((con.screenMax[1] - con.screenMin[1]) - (2 * fontHeight)) - 24.0) / fontHeight;
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
void Con_InitMessageWindow(
	MessageWindow *msgwnd,
	Message *messages,
	MessageLine *lines,
	char *text,
	int lineCount,
	int padding,
	int textPoolSize,
	int scrollTime,
	int fadeIn,
	int fadeOut)
{
	msgwnd->lines = lines;
	msgwnd->messages = messages;
	msgwnd->circularTextBuffer = text;
	msgwnd->textBufSize = textPoolSize;
	msgwnd->textBufPos = 0;
	msgwnd->firstLineIndex = 0;
	msgwnd->activeLineCount = 0;
	msgwnd->messageIndex = 0;
	msgwnd->lineCount = lineCount;
	msgwnd->padding = padding;
	msgwnd->scrollTime = scrollTime;

	if (fadeOut > 0)
	{
		msgwnd->fadeOut = fadeOut;
		msgwnd->fadeIn = fadeIn;
	}
	else
	{
		msgwnd->fadeOut = fadeOut;
		msgwnd->fadeIn = fadeIn;
	}
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
	if (dest == 1)
	{
		float v4 = Dvar_GetFloat(con_minicontime) * 1000.0;
		return (v4 + 9.313225746154785e-10);
	}
	else if (dest == 2)
	{
		float v3 = Dvar_GetFloat(con_errormessagetime) * 1000.0;
		return (v3 + 9.313225746154785e-10);
	}
	else
	{
		float v2 = Dvar_GetFloat(con_gameMsgWindowNLineCount[dest + 1]) * 1000.0;
		return (v2 + 9.313225746154785e-10);
	}
}

/*
==============
Con_UpdateMessage
==============
*/
void Con_UpdateMessage(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int duration)
{
	unsigned int messageIndex = msgwnd->messageIndex;
	int v5 = (msgwnd->messageIndex + 1) % msgwnd->lineCount;

	Message *messages = msgwnd->messages;
	msgwnd->messageIndex = v5;

	Message *time = &messages[v5];
	time->startTime = 0;

	if (CL_GetLocalClientGlobals(localClientNum))
	{
		time->startTime = CL_GetLocalClientGlobals(localClientNum)->serverTime;
	}

	time->endTime = duration + time->startTime;
}

/*
==============
Con_FreeFirstMessageWindowLine
==============
*/
void Con_FreeFirstMessageWindowLine(MessageWindow *msgwnd)
{
	int win = ++msgwnd->firstLineIndex;

	--msgwnd->activeLineCount;

	if (win == msgwnd->lineCount)
	{
		msgwnd->firstLineIndex = 0;
	}

	if (msgwnd == &con.consoleWindow && --con.displayLineOffset < con.visibleLineCount)
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
Con_NeedToFreeMessageWindowLine
==============
*/
bool Con_NeedToFreeMessageWindowLine(MessageWindow *msgwnd, int charCount)
{
	// messy

	if (!msgwnd->activeLineCount)
	{
		return 0;
	}

	MessageLine *v3 = &msgwnd->lines[msgwnd->firstLineIndex];

	int textBufPos = msgwnd->textBufPos;
	int v5 = (msgwnd->textBufSize - 1) & (textBufPos + charCount);
	bool v6 = v5 < textBufPos;
	int v7 = v3->textBufPos;

	if (v6)
	{
		if (v7 < msgwnd->textBufPos && v7 >= v5)
		{
			return 0;
		}
	}
	else if (v7 < msgwnd->textBufPos || v7 >= v5)
	{
		return 0;
	}

	return 1;
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
	if (!dest)
	{
		return &con.consoleWindow;
	}

	int v4 = dest - 1;

	if (!v4)
	{
		return &con.messageBuffer[localClientNum].miniconWindow;
	}

	if (v4 == 1)
	{
		return &con.messageBuffer[localClientNum].errorWindow;
	}

	return (18520 * localClientNum + 52 * dest + 18941568);
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
CL_TextLineWrapPosition
==============
*/
const char *CL_TextLineWrapPosition(
	const char *txt,
	int bufferSize,
	int pixelsAvailable,
	Font_s *font,
	float scale,
	int lineBroken)
{
	if (lineBroken)
	{
		while (*txt == 32)
		++txt;
	}

	const char *lineWrapPos = R_TextLineWrapPosition(txt, bufferSize, pixelsAvailable, font, scale);

	return *lineWrapPos != 0 ? lineWrapPos : 0;
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
	int result;

	if (msgLen + 1 <= msgMaxLen)
	{
		result = msgLen + 1;
		msg[msgLen] = c;
	}
	else
	{
		msg[msgLen] = c;
		return msgLen + 1;
	}

	return result;
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
void Con_AutoCompleteFromList(
	const char **strings,
	unsigned int stringCount,
	const char *prefix,
	char *completed,
	unsigned int sizeofCompleted)
{
	int v5 = strlen(prefix);
	*completed = 0;

	for (unsigned int stringIndex = 0; stringIndex < stringCount; ++stringIndex)
	{
		const char *string = strings[stringIndex];

		if (!I_strnicmp(prefix, string, v5))
		{
			if (*completed)
			{
				unsigned int charIndex;

				for (charIndex = v5; string[charIndex] == completed[charIndex] && completed[charIndex]; ++charIndex)
				{
					break;
				}

				completed[charIndex] = 0;
			}
			else
			{
				I_strncpyz(completed, string, sizeofCompleted);
			}
		}
	}
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
	if (Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen))
	{
		if (conDrawInputGlob.matchCount == conDrawInputGlob.matchIndex)
		{
			I_strncpyz(conDrawInputGlob.autoCompleteChoice, str, 64);
		}

		++conDrawInputGlob.matchCount;

		if (!str[conDrawInputGlob.inputTextLen])
		{
			conDrawInputGlob.hasExactMatch = 1;
		}
	}
}

/*
==============
ConDrawInput_DvarMatch
==============
*/
void ConDrawInput_DvarMatch(const char *str)
{
	if (Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen))
	{
		ConDrawInput_TextLimitChars(str, 24, &con_inputDvarMatchColor);

		conDrawInputGlob.x = conDrawInputGlob.x + 200.0;
		const dvar_t *dvar = Dvar_FindVar(str);
		const char *VariantString = Dvar_GetVariantString(dvar);

		ConDrawInput_TextLimitChars(VariantString, 40, &con_inputDvarValueColor);

		conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
		conDrawInputGlob.x = conDrawInputGlob.leftX;
	}
}

/*
==============
CG_SortPlayersAlphabeticallyComparator
==============
*/
int CG_SortPlayersAlphabeticallyComparator(const void *a, const void *b)
{
	return I_stricmp(*a, *b);
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
	if (Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen)
		&& (!conDrawInputGlob.hasExactMatch || !str[conDrawInputGlob.inputTextLen]))
	{
		ConDrawInput_Box(1, &con_inputHintBoxColor->current.value);
		ConDrawInput_Text(str, &con_inputCommandMatchColor);

		conDrawInputGlob.y = conDrawInputGlob.fontHeight + conDrawInputGlob.y;
		conDrawInputGlob.x = conDrawInputGlob.leftX;

		if (Cmd_Argc() == 2)
		{
			int fileCount;
			const char **AutoCompleteFileList = Cmd_GetAutoCompleteFileList(str, &fileCount, 12);

			if (fileCount)
			{
				ConDrawInput_AutoCompleteArg(localClientNum, AutoCompleteFileList, fileCount);
				FS_FreeFileList(AutoCompleteFileList, 12);
			}
		}
	}
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
	float color[4];

	CL_LookupColor(0x37u, color);

	int rowCount = con.visibleLineCount;
	int firstRow = con.displayLineOffset - con.visibleLineCount;

	if (con.displayLineOffset - con.visibleLineCount < 0)
	{
		y = y - (con.fontHeight * firstRow);
		rowCount = con.displayLineOffset;
		firstRow = 0;
	}

	for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		int lineIndex = (rowIndex + firstRow + con.consoleWindow.firstLineIndex) % con.consoleWindow.lineCount;
		y = con.fontHeight + y;

		R_AddCmdDrawConsoleTextInternal(
			con.consoleWindow.circularTextBuffer,
			con.consoleWindow.textBufSize,
			con.consoleWindow.lines[lineIndex].textBufPos,
			con.consoleWindow.lines[lineIndex].textBufSize,
			cls.consoleFont,
			x,
			y,
			1.0,
			1.0,
			color,
			0);
	}
}

/*
==============
Con_DrawOuputWindow
==============
*/
void Con_DrawOuputWindow()
{
	float width = con.screenMax[0] - con.screenMin[0];
	float y = con.screenMin[1] + 32.0;
	float x = con.screenMin[0];
	float height = (con.screenMax[1] - con.screenMin[1]) - 32.0;

	ConDraw_Box(
		x,
		y,
		width,
		height,
		&con_outputWindowColor->current.value);

	float xa = x + 6.0;
	float ya = y + 6.0;
	float heighta = height - 12.0;

	const char *versionString = va("Build %d %s", Com_GetBuildNumber(), "win-x86");
	SCR_DrawSmallStringExt(xa, ((heighta - 16.0) + ya), versionString, &con_versionColor);
	Con_DrawOutputScrollBar(xa, ya, width - 12.0, heighta);
	Con_DrawOutputText(xa, ya);
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
	con_inputBoxColor = _Dvar_RegisterVec4(
							"con_inputBoxColor",
							0.25,
							0.25,
							0.2,
							1.0,
							0.0,
							1.0,
							DVAR_ARCHIVE,
							"Color of the console input box");
	con_inputHintBoxColor = _Dvar_RegisterVec4(
								"con_inputHintBoxColor",
								0.40000001,
								0.40000001,
								0.34999999,
								1.0,
								0.0,
								1.0,
								DVAR_ARCHIVE,
								"Color of the console input hint box");
	con_outputBarColor = _Dvar_RegisterVec4(
							"con_outputBarColor",
							1.0,
							1.0,
							0.94999999,
							0.60000002,
							0.0,
							1.0,
							DVAR_ARCHIVE,
							"Color of the console output slider bar");
	con_outputSliderColor = _Dvar_RegisterVec4(
								"con_outputSliderColor",
								0.15000001,
								0.15000001,
								0.1,
								0.60000002,
								0.0,
								1.0,
								DVAR_ARCHIVE,
								"Color of the console slider");
	con_outputWindowColor = _Dvar_RegisterVec4(
								"con_outputWindowColor",
								0.34999999,
								0.34999999,
								0.30000001,
								0.75,
								0.0,
								1.0,
								DVAR_ARCHIVE,
								"Color of the console output");

	for (unsigned int i = 0; i < 4; ++i)
	{
		sprintf(con_gameMsgWindowNMsgTime_Names[i], "con_gameMsgWindow%dMsgTime", i);
		sprintf(
			con_gameMsgWindowNMsgTime_Descs[i],
			"On screen time for game messages in seconds in game message window %d",
			i);

		con_gameMsgWindowNMsgTime[i] = _Dvar_RegisterFloat(
										con_gameMsgWindowNMsgTime_Names[i],
										defaultGameMessageTimes[i],
										0.0,
										3.4028235e38,
										1u,
										con_gameMsgWindowNMsgTime_Descs[i]);

		sprintf((28 * i + 18866376), "con_gameMsgWindow%dLineCount", i);
		sprintf(
			con_gameMsgWindowNLineCount_Descs[i],
			"Maximum number of lines of text visible at once in game message window %d",
			i);

		con_gameMsgWindowNLineCount[i] = _Dvar_RegisterInt(
											(28 * i + 18866376),
											defaultGameMessageWindowLineCounts[i],
											1,
											9,
											1u,
											con_gameMsgWindowNLineCount_Descs[i]);

		char *dvarName = con_gameMsgWindowNScrollTime_Names[i];

		sprintf(dvarName, "con_gameMsgWindow%dScrollTime", i);
		sprintf(
			con_gameMsgWindowNScrollTime_Descs[i],
			"Time to scroll messages when the oldest message is removed in game message window %d",
			i);

		char *v1 = con_gameMsgWindowNFadeInTime_Names[i];
		con_gameMsgWindowNScrollTime[i] = _Dvar_RegisterFloat(
											dvarName,
											0.25,
											0.0,
											3.4028235e38,
 											1u,
											con_gameMsgWindowNScrollTime_Descs[i]);

		sprintf(v1, "con_gameMsgWindow%dFadeInTime", i);
		sprintf(con_gameMsgWindowNFadeInTime_Descs[i], "Time to fade in new messages in game message window %d", i);

		float value;
		if (i == 2)
		{
			value = 0.75f;
		}
		else
		{
			value = 0.25f;
		}

		con_gameMsgWindowNFadeInTime[i] = _Dvar_RegisterFloat(
											v1,
											value,
											0.0,
											3.4028235e38,
											1u,
											con_gameMsgWindowNFadeInTime_Descs[i]);

		sprintf((30 * i + 18867120), "con_gameMsgWindow%dFadeOutTime", i);
		sprintf(con_gameMsgWindowNFadeOutTime_Descs[i], "Time to fade out old messages in game message window %d", i);

		float v3;
		if (i == 1)
		{
			v3 = 0.0099999998f;
		}
		else
		{
			v3 = 0.5f;
		}

		con_gameMsgWindowNFadeOutTime[i] = _Dvar_RegisterFloat(
											(30 * i + 18867120),
											v3,
											0.0099999998,
											3.4028235e38,
											1u,
											con_gameMsgWindowNFadeOutTime_Descs[i]);

		sprintf(con_gameMsgWindowNSplitscreenScale_Names[i], "con_gameMsgWindow%dSplitscreenScale", i);
		sprintf(con_gameMsgWindowNSplitscreenScale_Descs[i], "Scaling of game message window %d in splitscreen", i);

		con_gameMsgWindowNSplitscreenScale[i] = _Dvar_RegisterFloat(
													con_gameMsgWindowNSplitscreenScale_Names[i],
													1.5,
													0.0,
													3.4028235e38,
													1u,
													con_gameMsgWindowNSplitscreenScale_Descs[i]);
	}

	con_typewriterColorBase = _Dvar_RegisterVec3(
								"con_typewriterColorBase",
								1.0,
								1.0,
								1.0,
								0.0,
								1.0,
								0x1000u,
								"Base color of typewritten objective text.");

	Con_InitMessageWindow(
		&con.consoleWindow,
		con.consoleMessages,
		con.consoleLines,
		con.consoleText,
		1024,
		0,
		0x8000,
		0,
		1,
		1);
	Con_InitMessageBuffer();

	con.color = colorWhite;

	Con_CheckResize();

	con.initialized = 1;
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
	LocalClientNum_t primary = Com_LocalClients_GetPrimary();
	CL_ConsolePrint(primary, 0, "\n", 0, 0, 0);

	con.displayLineOffset = con.consoleWindow.activeLineCount - 1;
}

/*
==============
CL_ReviveMessagePrint
==============
*/
void CL_ReviveMessagePrint(LocalClientNum_t localClientNum, const char *reviveString, Material *iconShader, float iconWidth, float iconHeight, char *horzFlipIcon)
{
	char reviveMsg[1024];

	int msgLen = CL_AddMessageIcon(reviveMsg, 0, 0x400u, iconShader, iconWidth, iconHeight, horzFlipIcon);

	while (*reviveString)
	{
		msgLen = CL_AddMessageChar(reviveMsg, msgLen, 0x400u, *reviveString++);
	}

	unsigned int reviveMsgLen = CL_AddMessageChar(reviveMsg, msgLen, 0x400u, 10);

	reviveMsg[reviveMsgLen] = 0;
	int pixelWidth = con.visiblePixelWidth;

	CL_ConsolePrint(localClientNum, 5, reviveMsg, 0, con.visiblePixelWidth, 0);
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
	bool isDvarCommand;

	if (!Key_IsCatcherActive(localClientNum, 1))
	{
		return;
	}

	conDrawInputGlob.fontHeight = R_TextHeight(cls.consoleFont);
	conDrawInputGlob.x = con.screenMin[0] + 6.0;
	conDrawInputGlob.y = con.screenMin[1] + 6.0;
	conDrawInputGlob.leftX = con.screenMin[0] + 6.0;

	ConDrawInput_Box(1, &con_inputBoxColor->current.value);
	const char *console_title = va("%s.%s.%d: %s> ", "1", "0", Com_GetBuildNumber(), Com_GetBuildName());
	ConDrawInput_TextAndOver(localClientNum, console_title, &con_versionColor);

	conDrawInputGlob.leftX = conDrawInputGlob.x;
	g_consoleField.widthInPixels = ((con.screenMax[0] - 6.0) - conDrawInputGlob.x);
	conDrawInputGlob.inputText = Con_TokenizeInput();
	conDrawInputGlob.inputTextLen = strlen(Con_TokenizeInput());
	conDrawInputGlob.autoCompleteChoice[0] = 0;

	if (!conDrawInputGlob.inputTextLen)
	{
		conDrawInputGlob.mayAutoComplete = 0;

		Field_Draw(localClientNum, &g_consoleField, conDrawInputGlob.x, conDrawInputGlob.y, 5, 5);
LABEL_39:
		Cmd_EndTokenizedString();
		return;
	}

	const char *originalCommand = Con_TokenizeInput();
	if (Cmd_Argc() > 1 && Con_IsDvarCommand(conDrawInputGlob.inputText))
	{
		isDvarCommand = 1;
		conDrawInputGlob.inputText = Cmd_Argv(1);
		conDrawInputGlob.inputTextLen = strlen(conDrawInputGlob.inputText);

		if (!conDrawInputGlob.inputTextLen)
		{
			conDrawInputGlob.mayAutoComplete = 0;

			Con_DrawInputPrompt(localClientNum);
			goto LABEL_39;
		}
	}
	else
	{
		isDvarCommand = 0;
	}

	bool con_matchPrefixOnlyDvar = Dvar_GetBool(con_matchPrefixOnly);
	conDrawInputGlob.hasExactMatch = 0;
	conDrawInputGlob.matchCount = 0;

	if (con_matchPrefixOnlyDvar)
	{
		con_ignoreMatchPrefixOnly = 1;

		Dvar_ForEachName(ConDrawInput_IncrMatchCounter);

		if (!isDvarCommand)
		{
			Cmd_ForEach(ConDrawInput_IncrMatchCounter);
		}

		if (conDrawInputGlob.matchCount <= con_inputMaxMatchesShown
			|| (conDrawInputGlob.hasExactMatch = 0,
				conDrawInputGlob.matchCount = 0,
				con_ignoreMatchPrefixOnly = 0,
				Dvar_ForEachName(ConDrawInput_IncrMatchCounter),
				Cmd_ForEach(ConDrawInput_IncrMatchCounter),
				conDrawInputGlob.matchCount))
		{
LABEL_22:
			int matchCount = conDrawInputGlob.matchCount;

			if (!conDrawInputGlob.matchCount)
			{
				Field_Draw(localClientNum, &g_consoleField, conDrawInputGlob.x, conDrawInputGlob.y, 5, 5);
				goto LABEL_39;
			}

			if (conDrawInputGlob.matchIndex < conDrawInputGlob.matchCount && conDrawInputGlob.autoCompleteChoice[0])
			{
				if (conDrawInputGlob.matchIndex >= 0)
				{
					Con_DrawAutoCompleteChoice(localClientNum, isDvarCommand, originalCommand);
LABEL_28:
					conDrawInputGlob.y = (conDrawInputGlob.y + conDrawInputGlob.fontHeight) + conDrawInputGlob.fontHeight;
					conDrawInputGlob.x = conDrawInputGlob.leftX;

					if (matchCount <= con_inputMaxMatchesShown)
					{
						if (matchCount == 1 || conDrawInputGlob.hasExactMatch && Con_AnySpaceAfterCommand())
						{
							Dvar_ForEachName(localClientNum, ConDrawInput_DetailedDvarMatch);

							if (!isDvarCommand)
							{
								Cmd_ForEach(localClientNum, ConDrawInput_DetailedCmdMatch);
							}
						}
						else
						{
							ConDrawInput_Box(matchCount, &con_inputHintBoxColor->current.value);
							Dvar_ForEachName(ConDrawInput_DvarMatch);

							if (!isDvarCommand)
							{
								Cmd_ForEach(ConDrawInput_CmdMatch);
							}
						}
					}
					else
					{
						const char *tooManyMatchesStr = va(
															"%i matches (too many to show here, press shift+tilde to open full console)",
															matchCount);
						ConDrawInput_Box(1, &con_inputHintBoxColor->current.value);
						ConDrawInput_Text(tooManyMatchesStr, &con_inputDvarMatchColor);
					}

					goto LABEL_39;
				}
			}
			else
			{
				conDrawInputGlob.matchIndex = -1;
			}

			Con_DrawInputPrompt(v6, localClientNum);

			goto LABEL_28;
		}

		conDrawInputGlob.hasExactMatch = 0;
		conDrawInputGlob.matchCount = 0;
		con_ignoreMatchPrefixOnly = 1;
	}
	else
	{
		con_ignoreMatchPrefixOnly = 0;
	}

	Dvar_ForEachName(ConDrawInput_IncrMatchCounter);

	if (!isDvarCommand)
	{
		Cmd_ForEach(ConDrawInput_IncrMatchCounter);
	}

	goto LABEL_22;
}

/*
==============
Con_CommitToAutoComplete
==============
*/
char Con_CommitToAutoComplete()
{
	if (conDrawInputGlob.matchIndex < 0 || !conDrawInputGlob.autoCompleteChoice[0])
	{
		return 0;
	}

	const char *cmd = Con_TokenizeInput();

	if (Con_IsDvarCommand(cmd))
	{
		Com_sprintf(g_consoleField.buffer, 256, "%s %s", cmd, conDrawInputGlob.autoCompleteChoice);
	}
	else
	{
		int v2 = 0;
		char v3;

		do
		{
			v3 = conDrawInputGlob.autoCompleteChoice[v2];
			g_consoleField.buffer[v2++] = v3;
		}
		while (v3);
	}

	Cmd_EndTokenizedString();

	g_consoleField.cursor = strlen(g_consoleField.buffer);
	g_consoleField.buffer[g_consoleField.cursor++] = 32;
	g_consoleField.buffer[g_consoleField.cursor] = 0;
	g_consoleField.drawWidth = SEH_PrintStrlen(g_consoleField.buffer);

	if (conDrawInputGlob.matchIndex >= 0)
	{
		if (conDrawInputGlob.autoCompleteChoice[0])
		{
			conDrawInputGlob.matchIndex = -1;
			conDrawInputGlob.autoCompleteChoice[0] = 0;
		}
	}
	return 1;
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

