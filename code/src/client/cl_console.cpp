#include "types.h"
#include "client_public.h"

Console con;
ConDrawInputGlob conDrawInputGlob;
field_t g_consoleField;
field_t historyEditLines[32];
clientStatic_t cls;
ScreenPlacement scrPlaceFull;

int con_inputMaxMatchesShown;
int g_console_field_width;
float g_console_char_height;
int keyCatchers;
int callDepth;

bool con_ignoreMatchPrefixOnly;

cmd_function_s Con_ChatModePublic_f_VAR;
cmd_function_s Con_Clear_f_VAR;
cmd_function_s Con_Echo_f_VAR;

dvar_t *con_restricted;
dvar_t *con_matchPrefixOnly;
dvar_t *cl_deathMessageWidth;

vec4_t con_versionColor = { 1.0, 1.0, 0.0, 1.0 };
vec4_t colorWhite = { 1.0, 1.0, 1.0, 1.0 };
vec4_t con_inputDvarMatchColor = { 1.0, 1.0, 0.8, 1.0 };
vec4_t con_inputCommandMatchColor = { 0.8, 0.8, 1.0, 1.0 };

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
	for (int lineOffset = 0; lineOffset < msgwnd->activeLineCount; ++lineOffset )
	{
		unsigned int lineIndex = (lineOffset + msgwnd->firstLineIndex) % msgwnd->lineCount;
		MessageLine *line = &msgwnd->lines[lineIndex];

		Message *message = &msgwnd->messages[line->messageIndex];
		int duration = message->endTime - message->startTime;

		message->startTime = serverTime;
		message->endTime = duration + serverTime;
	}
}

/*
==============
Con_TimeJumped
==============
*/
void Con_TimeJumped(LocalClientNum_t localClientNum, int serverTime)
{
	Con_ResetMessageWindowTimes(&con.consoleWindow, serverTime);

	for (unsigned int gameWindowIndex = 0; gameWindowIndex < 3; ++gameWindowIndex)
	{
		Con_ResetMessageWindowTimes(&con.color[4009 * localClientNum - 2473 + 13 * gameWindowIndex], serverTime);
	}

	Con_ResetMessageWindowTimes(&con.color[4009 * localClientNum - 1122], serverTime);
	Con_ResetMessageWindowTimes(&con.color[4009 * localClientNum - 53], serverTime);
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

	for (unsigned int gameWindowIndex = 0; gameWindowIndex < 3; ++gameWindowIndex)
	{
		Con_NudgeMessageWindowTimes(
			&con.color[4009 * localClientNum - 2473 + 13 * gameWindowIndex],
			serverTimeNudge,
			serverTime);
	}

	Con_NudgeMessageWindowTimes(&con.color[4009 * localClientNum - 1122], serverTimeNudge, serverTime);
	Con_NudgeMessageWindowTimes(&con.color[4009 * localClientNum - 53], serverTimeNudge, serverTime);
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
	if (dest == CON_DEST_MINICON)
	{
		return ((con_minicontime->current.value * 1000.0) + 9.313225746154785e-10);
	}
	else if (dest == CON_DEST_ERROR)
	{
		return ((con_errormessagetime->current.value * 1000.0) + 9.313225746154785e-10);
	}

	return ((con_gameMsgWindowNLineCount[dest]->current.value * 1000.0) + 9.313225746154785e-10);
}

/*
==============
Con_UpdateMessage
==============
*/
void Con_UpdateMessage(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int duration)
{
	msgwnd->messageIndex = (msgwnd->messageIndex + 1) % msgwnd->lineCount;
	Message *message = &msgwnd->messages[msgwnd->messageIndex];
	message->startTime = 0;

	if (CL_GetLocalClientGlobals(localClientNum))
	{
		message->startTime = CL_GetLocalClientGlobals(localClientNum)->serverTime;
	}

	message->endTime = duration + message->startTime;
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
	switch (dest)
	{
		case CON_DEST_CONSOLE:
			return &con.consoleWindow;
		case CON_DEST_MINICON:
			return &con.color[4009 * localClientNum - 1122];
		case CON_DEST_ERROR:
			return &con.color[4009 * localClientNum - 53];
	}

	return &con.color[4009 * localClientNum - 2512 + 13 * dest];
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
	if (Con_IsChannelVisible(CON_DEST_CONSOLE, channel, flags))
	{
		Con_UpdateMessageWindowLine(&con.consoleWindow, localClientNum, lineFeed, flags);
	}

	if (Con_IsChannelVisible(CON_DEST_MINICON, channel, flags))
	{
		Con_UpdateMessageWindowLine(&con.messageBuffer[localClientNum].miniconWindow, localClientNum, lineFeed, flags);
	}

	for (int i = 3; i <= 6; ++i)
	{
		if ( Con_IsChannelVisible(i, channel, flags) )
		{
			Con_UpdateMessageWindowLine(Con_GetDestWindow(localClientNum, i), localClientNum, lineFeed, flags);
		}
	}

	if (com_developer->current.integer)
	{
		if (Con_IsChannelVisible(CON_DEST_ERROR, channel, flags))
		{
			Con_UpdateMessageWindowLine(&con.messageBuffer[localClientNum].errorWindow, localClientNum, lineFeed, flags);
		}
	}
}

/*
==============
Con_InitMessageBuffer
==============
*/
void Con_InitMessageBuffer()
{
	for (int localClientNum = 0; localClientNum < 1; ++localClientNum)
	{
		MessageBuffer *msgBuf = &con.messageBuffer[localClientNum];

		for (unsigned int gameWindowIndex = 0; gameWindowIndex < 3; ++gameWindowIndex)
		{
			Con_InitMessageWindow(
				&msgBuf->gamemsgWindows[gameWindowIndex],
				msgBuf->gamemsgMessages[gameWindowIndex],
				msgBuf->gamemsgLines[gameWindowIndex],
				msgBuf->gamemsgText[gameWindowIndex],
				con_gameMsgWindowNLineCount[gameWindowIndex]->current.integer + 3,
				3,
				2048,
				((con_gameMsgWindowNScrollTime[gameWindowIndex]->current.value * 1000.0) + 9.313225746154785e-10),
				((con_gameMsgWindowNFadeInTime[gameWindowIndex]->current.value * 1000.0) + 9.313225746154785e-10),
				((con_gameMsgWindowNFadeOutTime[gameWindowIndex]->current.value * 1000.0) + 9.313225746154785e-10));
		}

		Con_InitMessageWindow(
			&msgBuf->miniconWindow,
			msgBuf->miniconMessages,
			msgBuf->miniconLines,
			msgBuf->miniconText,
			con_miniconlines->current.integer,
			0,
			4096,
			0,
			0,
			1);
		Con_InitMessageWindow(
			&msgBuf->errorWindow,
			msgBuf->errorMessages,
			msgBuf->errorLines,
			msgBuf->errorText,
			5,
			0,
			1024,
			0,
			1,
			1);
	}
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
	char result;
	Font_s *FontHandle;
	const char *v10;
	const char *v11;
	const char *v12;
	char *v13;
	char v14;
	char v15;
	char v16;
	unsigned int v17;
	int v18;
	unsigned int v19;
	unsigned int v20;
	const char *v21;
	char v22;
	unsigned int v23;
	const char *v24;
	const char *v25;
	Font_s *font;
	float xScale;
	const char *wrapPosition;
	int atStartOfBrokenLine;
	char c;

	if (callDepth)
	{
		return color;
	}

	callDepth = 1;

	Con_UpdateNotifyMessage(localClientNum, channel, duration, flags);

	if (channel != con.prevChannel)
	{
		if (con.lineOffset)
		{
			Con_UpdateNotifyLine(localClientNum, con.prevChannel, 1, flags);

			con.lineOffset = 0;

			if (con.displayLineOffset == con.consoleWindow.activeLineCount - 1)
			{
				++con.displayLineOffset;
			}
		}
	}

	if (channel == 2 || channel == 3 || channel == 5 || channel == 4)
	{
		FontHandle = UI_GetFontHandle(ScrPlace_GetView(localClientNum), channel != 3 ? 0 : 4, 0.25);
		font = FontHandle;
		xScale = R_NormalizedTextScale(FontHandle, 0.25);
	}
	else
	{
		FontHandle = cls.consoleFont;
		font = cls.consoleFont;
		xScale = 1.0f;
	}

	if (!pixelWidth)
	{
		pixelWidth = con.visiblePixelWidth;
	}

	v10 = R_TextLineWrapPosition(txt, 512 - con.lineOffset, pixelWidth, FontHandle, xScale);
	wrapPosition = *v10 != 0 ? v10 : 0;

	if (txt == wrapPosition && con.lineOffset)
	{
		Con_UpdateNotifyLine(localClientNum, channel, 1, flags);

		con.lineOffset = 0;

		if (con.displayLineOffset == con.consoleWindow.activeLineCount - 1)
		{
			++con.displayLineOffset;
		}

		v11 = R_TextLineWrapPosition(txt, 512, pixelWidth, FontHandle, xScale);
		wrapPosition = *v11 != 0 ? v11 : 0;
	}

	v12 = txt;
	v13 = txt;
	atStartOfBrokenLine = 0;

	while ( *v13 )
	{
		v14 = *v13++;
		c = v14;

		if (v14 == 10)
		{
			if (!wrapPosition)
			{
				goto LABEL_71;
			}

			if (font)
			{
				if (wrapPosition == v13)
				{
					goto LABEL_71;
				}
			}
		}
		else
		{
			if (v14 == 94)
			{
				if (v13)
				{
					v15 = *v13;

					if (*v13 != 94 && (v15 >= 48 && v15 <= 57 || v15 == 70))
					{
						v16 = *v13;
						con.textTempLine[con.lineOffset++] = 94;
						con.textTempLine[con.lineOffset] = v16;
						v17 = con.lineOffset + 1;
						color = v16;
						con.lineOffset = v17;
						++v13;
						atStartOfBrokenLine = 0;
						goto LABEL_70;
					}
				}

				if (*v13 == 72 || *v13 == 73)
				{
					con.textTempLine[con.lineOffset++] = 94;
					v18 = v13[3];
					memcpy(&con.textTempLine[con.lineOffset], v13, v18 + 4);
					v19 = con.lineOffset + v18 + 4;
					con.lineOffset = v19;
					v13 += v18 + 4;
					atStartOfBrokenLine = 0;
					goto LABEL_70;
				}
			}

			else if (v14 == 32 && atStartOfBrokenLine)
			{
				goto LABEL_70;
			}

			if (con.lineOffset >= 0x200)
			{
				v14 = c;
			}

			con.textTempLine[con.lineOffset] = v14;
			v20 = con.lineOffset + 1;
			con.lineOffset = v20;
			atStartOfBrokenLine = 0;
		}

LABEL_70:
		if (v13 == wrapPosition)
		{
LABEL_71:
			Con_UpdateNotifyLine(localClientNum, channel, 1, flags);

			con.lineOffset = 0;

			if (con.displayLineOffset == con.consoleWindow.activeLineCount - 1)
			{
				++con.displayLineOffset;
			}

			if (c != 10)
			{
				v22 = color;
				atStartOfBrokenLine = 1;

				if (color != 55)
				{
					if (color < 48 || color > 57)
					{
						v22 = color;
					}

					con.textTempLine[con.lineOffset] = 94;
					*(con.lineOffset + 18932977) = v22;
					v23 = con.lineOffset + 2;
					con.lineOffset = v23;
				}
			}

			v24 = v13;

			if (atStartOfBrokenLine && *v13 == 32)
			{
				do
				{
					++v24;
				}
				while (*v24 == 32);
			}

			v25 = R_TextLineWrapPosition(v24, 512 - con.lineOffset, pixelWidth, font, xScale);
			v12 = txt;
			wrapPosition = *v25 != 0 ? v25 : 0;
		}
	}

	if (con.lineOffset)
	{
		if (channel == 2 || channel == 3 || channel == 5 || channel == 4)
		{
			Con_UpdateNotifyLine(localClientNum, channel, 1, flags);

			con.lineOffset = 0;

			if (con.displayLineOffset == con.consoleWindow.activeLineCount - 1)
			{
				++con.displayLineOffset;
			}
		}
		else
		{
			Con_UpdateNotifyLine(localClientNum, channel, 0, flags);
		}
	}

	--callDepth;
	result = color;
	con.prevChannel = channel;

	return result;
}

/*
==============
CL_AddMessageChar
==============
*/
int CL_AddMessageChar(char *msg, unsigned int msgLen, unsigned int msgMaxLen, char c)
{
	msg[msgLen] = c;

	return msgLen + 1;
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

	const char *cmd = Cmd_Argv(0);

	if (*cmd == 92 || *cmd == 47)
	{
		++cmd;
	}

	while (isspace(*cmd))
	{
		++cmd;
	}

	return cmd;
}

/*
==============
Con_AnySpaceAfterCommand
==============
*/
char Con_AnySpaceAfterCommand()
{
	int charIndex;

	for ( charIndex = 0; isspace(g_consoleField.buffer[charIndex]); ++charIndex )
	{
		// nothing
	}

	while (g_consoleField.buffer[charIndex])
	{
		if (isspace(g_consoleField.buffer[charIndex]))
		{
			return 1;
		}
		++charIndex;
	}

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
		(con.screenMax[0] - con.screenMin[0]) - ((conDrawInputGlob.x - 6.0) - con.screenMin[0]),
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
	if ( !conDrawInputGlob.mayAutoComplete
		|| conDrawInputGlob.matchCount <= 1
		|| conDrawInputGlob.matchCount >= con_inputMaxMatchesShown
		|| conDrawInputGlob.hasExactMatch && Con_AnySpaceAfterCommand() )
	{
		return 0;
	}

	conDrawInputGlob.matchIndex += step;

	if (conDrawInputGlob.matchIndex >= 0)
	{
		if (conDrawInputGlob.matchIndex >= conDrawInputGlob.matchCount)
		{
			conDrawInputGlob.matchIndex = 0;
		}
	}
	else
	{
		conDrawInputGlob.matchIndex = conDrawInputGlob.matchCount - 1;
	}

	return 1;
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
	// messy

	if (con_typewriterEnabledSounds->current.enabled)
	{
		clientActive_t *LocalClientGlobals = CL_GetLocalClientGlobals(localClientNum);
		int typingStartTime = line->typingStartTime;
		clientActive_t *v9 = LocalClientGlobals;
		int v5 = LocalClientGlobals->serverTime - typingStartTime;
		int lastSoundTime = line->lastTypingSoundTime - typingStartTime;
		int printCnt = PrintableCharsCount(msgwnd, line);
		int Int = Dvar_GetInt(con_typewriterPrintSpeed);
		int v7 = printCnt * Int;
		int typewriterPrintSpeed = Int;
		int v8 = Dvar_GetInt(con_typewriterDecayStartTime);

		if (v8 < v7)
		{
			v8 = v7;
		}

		if (v5 <= v8 && v5 <= v7 && lastSoundTime < typewriterPrintSpeed * (v5 / typewriterPrintSpeed))
		{
			SND_Play("uin_typewriter", 0, 1.0, (((localClientNum & 3) << 17) | 0x80FFF), 0, 0, 0);

			line->lastTypingSoundTime = v9->serverTime;
		}
	}
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
void Con_DrawMessageWindow(
	LocalClientNum_t localClientNum,
	MessageWindow *msgwnd,
	int x,
	int y,
	int charHeight,
	int horzAlign,
	int vertAlign,
	Font_s *font,
	vec4_t *color,
	int textStyle,
	float msgwndScale,
	msgwnd_mode_t mode,
	int textAlignMode)
{
	if (CL_GetLocalClientGlobals(localClientNum)->snap.ps.pm_type == 6 || CL_ShouldDisplayHud(localClientNum))
	{
		switch (mode)
		{
		case MWM_BOTTOMUP_ALIGN_TOP:
		case MWM_TOPDOWN_ALIGN_BOTTOM:
			Con_DrawMessageWindowOldToNew(
				localClientNum,
				msgwnd,
				x,
				y,
				charHeight,
				horzAlign,
				vertAlign,
				mode == MWM_TOPDOWN_ALIGN_BOTTOM,
				font,
				color,
				textStyle,
				msgwndScale,
				textAlignMode);
			break;
		case MWM_BOTTOMUP_ALIGN_BOTTOM:
		case MWM_TOPDOWN_ALIGN_TOP:
			Con_DrawMessageWindowNewToOld(
				localClientNum,
				msgwnd,
				x,
				y,
				charHeight,
				horzAlign,
				vertAlign,
				mode == MWM_BOTTOMUP_ALIGN_BOTTOM,
				font,
				color,
				textStyle,
				msgwndScale,
				textAlignMode);
			break;
		default:
			break;
		}
	}
}

/*
==============
Con_DrawGameMessageWindow
==============
*/
void Con_DrawGameMessageWindow(
	LocalClientNum_t localClientNum,
	int windowIndex,
	int xPos,
	int yPos,
	int horzAlign,
	int vertAlign,
	Font_s *font,
	float fontScale,
	vec4_t *color,
	int textStyle,
	int textAlignMode,
	msgwnd_mode_t mode)
{
	float msgwndScale;

	if (!cg_paused->current.integer)
	{
		if (R_Is3DOn())
		{
			msgwndScale = Dvar_GetFloat(con_gameMsgWindowNSplitscreenScale[windowIndex]);
		}
		else
		{
			msgwndScale = 1.0f;
		}

		Con_DrawMessageWindow(
			localClientNum,
			&con.messageBuffer[localClientNum].gamemsgWindows[windowIndex],
			xPos,
			yPos,
			((fontScale * 48.0) + 9.313225746154785e-10), // ?? dont even know at this point
			horzAlign,
			vertAlign,
			font,
			color,
			textStyle,
			msgwndScale,
			mode,
			textAlignMode);
	}
}

/*
==============
Con_DrawMiniConsole
==============
*/
void Con_DrawMiniConsole(LocalClientNum_t localClientNum, int xPos, int yPos, float alpha)
{
	float msgwndScale;
	vec4_t color;

	if (R_Is3DOn())
	{
		msgwndScale = Dvar_GetFloat(con_MiniConSplitscreenScale);
	}
	else
	{
		msgwndScale = 1.0f;
	}

	Font_s *font = UI_GetFontHandle(ScrPlace_GetView(localClientNum), 0, 1.0);

	if (con.messageBuffer[0].miniconWindow.lineCount != Dvar_GetInt(con_miniconlines))
	{
		con.messageBuffer[0].miniconWindow.lineCount = Dvar_GetInt(con_miniconlines);
		Con_ClearMessageWindow(&con.messageBuffer[localClientNum].miniconWindow);
	}

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = alpha;

	if (CL_GetLocalClientGlobals(localClientNum)->snap.ps.pm_type == 6 || CL_ShouldDisplayHud(localClientNum))
	{
		Con_DrawMessageWindowOldToNew(
			localClientNum,
			&con.messageBuffer[localClientNum].miniconWindow,
			xPos,
			yPos,
			12,
			1,
			1,
			0,
			font,
			&color,
			3,
			msgwndScale,
			4);
	}
}

/*
==============
Con_DrawErrors
==============
*/
void Con_DrawErrors(LocalClientNum_t localClientNum, int xPos, int yPos, float alpha)
{
	vec4_t color;

	Font_s *font = UI_GetFontHandle(ScrPlace_GetView(localClientNum), 1, 1.0);

	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = alpha;

	if (CL_GetLocalClientGlobals(localClientNum)->snap.ps.pm_type == 6 || CL_ShouldDisplayHud(localClientNum))
	{
		Con_DrawMessageWindowOldToNew(
			localClientNum,
			&con.messageBuffer[localClientNum].errorWindow,
			xPos,
			yPos,
			12,
			1,
			1,
			0,
			font,
			&color,
			3,
			1.0,
			4);
	}
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
	con_restricted = _Dvar_RegisterBool("monkeytoy", 0, DVAR_ARCHIVE, "Restrict console access");
	con_matchPrefixOnly = _Dvar_RegisterBool(
							"con_matchPrefixOnly",
							1,
							DVAR_ARCHIVE,
							"Only match the prefix when listing matching Dvars");
	cl_deathMessageWidth = _Dvar_RegisterInt("cl_deathMessageWidth", 320, 1, 640, DVAR_NOFLAG, "Pixel width of the obituary area");

	Field_Clear(&g_consoleField);

	g_consoleField.widthInPixels = g_console_field_width;
	g_consoleField.charHeight = g_console_char_height;
	g_consoleField.fixedSize = 1;

	for (int i = 0; i < 32; ++i)
	{
		Field_Clear(&historyEditLines[i]);

		historyEditLines[i].widthInPixels = g_console_field_width;
		historyEditLines[i].charHeight = g_console_char_height;
		historyEditLines[i].fixedSize = 1;
	}

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
	if (cl_noprint && !cl_noprint->current.enabled && channel != 8)
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
	CL_ConsolePrint(0, 0, "\n", 0, 0, 0);

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

	conDrawInputGlob.hasExactMatch = 0;
	conDrawInputGlob.matchCount = 0;

	if (con_matchPrefixOnly->current.enabled)
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

