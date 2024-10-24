#pragma once

#include "types.h"

//#include "client/client.h"

//t6/code/src/client/cl_compositing.cpp
GfxImage *CL_CompositeSetupImage();
void CL_PCCopyImageGenMIPCallback(void *job);
void CL_CompositeResetLayer(CompositeEmblemLayer *layer);
void CL_CompositeClearLayer(CompositeEmblemLayer *layer);
void CL_CompositeClearRecentColor(vec4_t *recentColor);
void CL_CompositeShiftLayersUp(CompositeEmblemLayer *layers, int selectedLayer, int layerCount);
void CL_CompositeRender();

//t6/code/src/client/cl_console.cpp
void SetupChatField(LocalClientNum_t localClientNum, int teamChat, int widthInPixels);
void Con_ChatModePublic_f();
void Con_GetTextCopy(char *text, int maxSize);
void Con_ResetMessageWindowTimes(MessageWindow *msgwnd, int serverTime);
void Con_TimeJumped(LocalClientNum_t localClientNum, int serverTime);
void Con_NudgeMessageWindowTimes(MessageWindow *msgwnd, int serverTimeNudge, int serverTime);
void Con_TimeNudged(LocalClientNum_t localClientNum, int serverTimeNudge);
void Con_ClearMessageWindow(MessageWindow *msgwnd);
void Con_ClearNotify(LocalClientNum_t localClientNum);
void Con_CheckResize();
void Con_InitMessageWindow(MessageWindow *msgwnd, Message *messages, MessageLine *lines, char *text, int lineCount, int padding, int textPoolSize, int scrollTime, int fadeIn, int fadeOut);
void Con_Clear_f(MessageWindow *notthis);
void Con_InitClientAssets();
int Con_GetDefaultMsgDuration(print_msg_dest_t dest);
void Con_UpdateMessage(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int duration);
void Con_FreeFirstMessageWindowLine(MessageWindow *msgwnd);
bool Con_NeedToFreeMessageWindowLine(MessageWindow *msgwnd, int charCount);
void Con_FreeFirstMessageWindowLine(MessageWindow *msgwnd);
void Con_CopyCurrentConsoleLineText(MessageWindow *msgwnd, MessageLine *msgLine);
int LatestActiveTypewrittenLineIdx(MessageWindow *msgwnd);
int PrintableCharsCount(const MessageWindow *msgwnd, MessageLine *line);
int GetNextValidPrintTimeForLine(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int flags);
void Con_UpdateMessageWindowLine(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int linefeed, int flags);
MessageWindow *Con_GetDestWindow(LocalClientNum_t localClientNum, print_msg_dest_t dest);
void Con_UpdateNotifyMessage(LocalClientNum_t localClientNum, int channel, int duration, int flags);
void Con_UpdateNotifyLine(LocalClientNum_t localClientNum, int channel, bool lineFeed, int flags);
void Con_InitMessageBuffer();
char CL_ConsolePrint_AddLine(LocalClientNum_t localClientNum, int channel, const char *txt, int duration, int pixelWidth, int color, int flags);
int CL_AddMessageChar(char *msg, unsigned int msgLen, unsigned int msgMaxLen, char c);
int CL_AddMessageString(char *msg, unsigned int msgLen, unsigned int msgMaxLen, const char *string);
int CL_AddMessageIcon(char *msg, unsigned int msgLen, unsigned int msgMaxLen, Material *iconShader, float iconWidth, float iconHeight, bool horzFlipIcon);
void Con_AutoCompleteFromList(const char **strings, unsigned int stringCount, const char *prefix, char *completed, unsigned int sizeofCompleted);
const char *Con_TokenizeInput();
char Con_AnySpaceAfterCommand();
void ConDrawInput_Text(const char *str, const vec4_t *color);
void ConDrawInput_TextLimitChars(const char *str, int maxChars, const vec4_t *color);
void ConDrawInput_TextAndOver(LocalClientNum_t localClientNum, const char *str);
void ConDraw_Box(float x, float y, float w, float h, const vec4_t *color);
void ConDrawInput_Box(int lines, const vec4_t *color);
int Con_GetAutoCompleteColorCodedStringDiscontiguous(const char *query, const char *matchToText, int matchTextLen, char *colorCoded);
int Con_GetAutoCompleteColorCodedStringContiguous(const char *query, const char *matchToText, int matchTextLen, char *colorCoded);
bool Con_IsAutoCompleteMatch(const char *query, const char *matchToText, int matchTextLen);
void ConDrawInput_IncrMatchCounter(const char *str);
void ConDrawInput_DvarMatch(const char *str);
int CG_SortPlayersAlphabeticallyComparator(const void *a, const void *b);
int ConDrawInput_TextFieldFirstArgChar();
void ConDrawInput_AutoCompleteArg(LocalClientNum_t localClientNum, const char **stringList, int stringCount);
int ConDrawInput_GetDvarDescriptionLines(const dvar_t *dvar);
void ConDrawInput_DetailedDvarMatch(LocalClientNum_t localClientNum, const char *str);
void ConDrawInput_DetailedCmdMatch(LocalClientNum_t localClientNum, const char *str);
void ConDrawInput_CmdMatch(const char *str);
void Con_DrawAutoCompleteChoice(LocalClientNum_t localClientNum, bool isDvarCommand, const char *originalCommand);
void Con_DrawInputPrompt(LocalClientNum_t localClientNum);
BOOL Con_HasTooManyMatchesToShow();
bool Con_IsDvarCommand(const char *cmd);
char Con_CycleAutoComplete(int step);
char Con_CancelAutoComplete();
void Con_AllowAutoCompleteCycling(bool isAllowed);
void TypewriterSounds(LocalClientNum_t localClientNum, const MessageWindow *msgwnd, MessageLine *line);
void Con_DrawMessageLineOnHUD(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, int x, int y, int charHeight, int horzAlign, int vertAlign, Font_s *font, const MessageWindow *msgwnd, int lineIdx, vec4_t *color, int textStyle, float msgwndScale, int textAlignMode);
void Con_CullFinishedLines(int serverTime, MessageWindow *msgwnd);
double Con_GetMessageAlpha(Message *message, MessageWindow *msgwnd, int serverTime, bool scrollsIntoPlace);
void Con_DrawMessageWindowNewToOld(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int x, int y, int hudCharHeight, int horzAlign, int vertAlign, bool up, Font_s *font, vec4_t *color, int textStyle, float msgwndScale, int textAlignMode);
void Con_DrawMessageWindowOldToNew(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int x, int y, int charHeight, int horzAlign, int vertAlign, bool up, Font_s *font, vec4_t *color, int textStyle, float msgwndScale, int textAlignMode);
void Con_DrawMessageWindow(LocalClientNum_t localClientNum, MessageWindow *msgwnd, int x, int y, int charHeight, int horzAlign, int vertAlign, Font_s *font, vec4_t *color, int textStyle, float msgwndScale, msgwnd_mode_t mode, int textAlignMode);
void Con_DrawGameMessageWindow(LocalClientNum_t localClientNum, int windowIndex, int xPos, int yPos, int horzAlign, int vertAlign, Font_s *font, float fontScale, vec4_t *color, int textStyle, int textAlignMode, msgwnd_mode_t mode);
void Con_DrawMiniConsole(LocalClientNum_t localClientNum, int xPos, int yPos, float alpha);
void Con_DrawErrors(LocalClientNum_t localClientNum, int xPos, int yPos, float alpha);
BOOL Con_IsValidGameMessageWindow(int windowIndex);
bool Con_IsGameMessageWindowActive(LocalClientNum_t localClientNum, int windowIndex);
void Con_DrawSay(LocalClientNum_t localClientNum, int x, int y);
void Con_ToggleConsoleOutput();
void Con_DrawOutputVersion(float x, float y, float width, float height);
void Con_DrawOutputScrollBar(float x, float y, float width, float height);
void Con_DrawOutputText(float x, float y);
void Con_DrawOuputWindow();
void Con_PageUp();
void Con_PageDown();
void Con_Top();
void Con_Bottom();
void Con_Close(LocalClientNum_t localClientNum);
bool Con_IsActive(LocalClientNum_t localClientNum);
void CL_PlayTextFXPulseSounds(LocalClientNum_t localClientNum, int currentTime, int strLength, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int *soundTimeKeeper);
void Con_ToggleConsole();
void Con_Echo_f();
void Con_OneTimeInit();
void Con_Init();
void CL_ConsolePrint(LocalClientNum_t localClientNum, int channel, const char *txt, int duration, int pixelWidth, int flags);
void Con_Linefeed(int localClientNum, int channel, int flags);
void CL_ConsoleFixPosition();
void CL_ReviveMessagePrint(LocalClientNum_t localClientNum, const char *reviveString, Material *iconShader, float iconWidth, float iconHeight, char *horzFlipIcon);
void CL_DeathMessagePrint(LocalClientNum_t localClientNum, const char *attackerName, char attackerColorIndex, const char *victimName, int victimColorIndex, Material *iconShader, float iconWidth, float iconHeight, unsigned int horzFlipIcon);
void Con_DrawInput(LocalClientNum_t localClientNum);
char Con_CommitToAutoComplete();
void Con_DrawSolidConsole(LocalClientNum_t localClientNum);
void Con_DrawConsole(LocalClientNum_t localClientNum);

//t6/code/src/client/cl_debugdata.cpp
void CL_DebugInitSVThreadVariables();
BOOL CreateDebugStringsIfNeeded();
void AddDebugStringInternal(const float* xyz, const float* color, float scale, const char* text, int duration, clientDebugStringInfo_t* info);
void CL_AddDebugString(const char *a1, int a2, const vec3_t *xyz, const vec4_t *color, float scale, const char *text, int duration);
BOOL CreateDebugSpheresIfNeeded();
void AddDebugSphereInternal(const float* center, const float radius, const float* color, int sideCount, int depthTest, int duration, clientDebugSphereInfo_t* info);
void CL_AddDebugSphere(int a1, const vec3_t *center, const float radius, const vec4_t *color, int sideCount, int depthTest, int duration);
BOOL CreateDebugLinesIfNeeded();
void AddDebugLineInternal(const vec3_t *start, const vec3_t *end, const vec4_t *color, int depthTest, int duration, clientDebugLineInfo_t *info);
void CL_AddDebugLine(clientDebugLineInfo_t *a1, const vec3_t *start, const vec3_t *end, const vec4_t *color, int depthTest, int duration);
void CL_AddDebugAxis(clientDebugLineInfo_t *a1, clientDebugLineInfo_t *a2, clientDebugLineInfo_t *origin, const vec3_t *axis, const vec3_t *length, float doDepthTest, int duration, int a8);
void CL_AddDebugStarWithText(clientDebugLineInfo_t *a1, const vec3_t *point, const vec4_t *starColor, const vec4_t *textColor, const char *string, float fontsize, int duration);
void CL_AddDebugStar(clientDebugLineInfo_t *a1, const vec3_t *point, const vec4_t *color, int duration);
void CL_AddDebugBox(const vec3_t *origin, const vec3_t *mins, const vec3_t *maxs, float yaw, const vec4_t *color, int depthTest, int duration);
void FlushDebugStrings(clientDebugStringInfo_t *info, int fromServer);
void FlushDebugLines(clientDebugLineInfo_t *info, int fromServer);
void FlushDebugSpheres(clientDebugSphereInfo_t *info, int fromServer);
void CL_FlushDebugClientData(clientDebugStringInfo_t *a1, int a2);
void CL_UpdateDebugClientData();
void CL_FlushDebugServerData(clientDebugStringInfo_t *a1, int a2);
void CL_UpdateDebugServerData();
void CL_ShutdownDebugData();

//t6/code/src/client/cl_devgui.cpp
void CL_AddMapDirSlider(const char *dir, int locationFlags, const char *locationName);
void CL_CreateMapMenuEntriesForLocation(int locationFlags, const char *locationName);
const dvar_t *CL_RegisterDevGuiDvars();
void CL_CreateMapMenuEntries();
void CL_CreateDevGui();
void CL_DestroyDevGui();

//t6/code/src/client/cl_gamepad.cpp
void CL_ResetLastGamePadEventTime();
void CL_InitGamepadAxisBindings();
GamepadPhysicalAxis Gamepad_StringToPhysicalAxis(const char *axisName);
GamepadVirtualAxis Axis_StringToVirtualAxis(const char *axisName);
GamepadMapping Gamepad_InputTypeStringToId(const char *name);
void Gamepad_BindAxis(GpadAxesGlob *gaGlob, GamepadPhysicalAxis realIndex, GamepadVirtualAxis axisIndex, GamepadMapping mapType);
void Axis_Bind_f();
void Axis_Unbindall_f();
double CL_GamepadAxisValue(LocalClientNum_t localClientNum, int virtualAxis);
bool CL_CheckForIgnoreDueToRepeat(LocalClientNum_t localClientNum, int key, int repeatCount, int time);
void CL_GamepadResetMenuScrollTime(LocalClientNum_t localClientNum, int key, int down, unsigned int time);
bool GamepadButtonEvent_LocationSelection(bool pressed, int keyCatchers, KeyState *keys, int key, LocalClientNum_t localClientNum);
bool GamepadButtonEvent_DevguiKeyEvent(LocalClientNum_t localClientNum, bool pressed, const char *kb, int keyCatchers, connstate_t clcState, int activeMenu);
void GamepadButtonEvent_UnlockableItems(LocalClientNum_t localClientNum, ControllerIndex_t controllerIndex, int key, KeyState *keys);
void GamepadButtonEvent_Cheats(LocalClientNum_t localClientNum, ControllerIndex_t controllerIndex, int key, bool pressed, KeyState *keys);
void CL_GamepadButtonEvent(char *a1, LocalClientNum_t localClientNum, ControllerIndex_t controllerIndex, int key, int buttonEvent, unsigned int time, int gamePadButton);
void CL_GamepadButtonEventForPort(ControllerIndex_t portIndex, int key, int buttonEvent, unsigned int time, int button);
void CL_InitGamepadCommands();
void CL_GamepadGenerateAPad(LocalClientNum_t localClientNum, ControllerIndex_t portIndex, int physicalAxis, int time);
void CL_GamepadEvent(ControllerIndex_t portIndex, int physicalAxis, int value, int time);
const char* Gamepad_VirtualAxisName(GamepadVirtualAxis axis);
const char* Axis_NumToAxisString(GamepadPhysicalAxis axis);
const char* Gamepad_InputTypeName(GamepadMapping mapType);
void Gamepad_WriteBindings(LocalClientNum_t localClientNum, int f);

//t6/code/src/client/cl_input.cpp
void CL_LeanCount_Reset();
void CL_LeanCount_Increment();
BOOL CL_LeanCount_ShouldIncrementStat();
bool CG_IsSprinting(LocalClientNum_t localClientNum);
void IN_KeyDown(int *a1, int a2, int time, unsigned int a4);
void IN_KeyUp(kbutton_t *b, int key, unsigned int time);
void IN_KeyDownCheat(kbutton_t *b);
void IN_KeyUpCheat(kbutton_t *b);
float CL_KeyState(kbutton_t *key);
void CL_SetStance(LocalClientNum_t localClientNum, StanceState stance);
void CL_ToggleStance(LocalClientNum_t localClientNum, StanceState preferredStance);
void IN_UpDown(kbutton_t *notthis);
void IN_UpUp(kbutton_t *notthis);
void IN_SpeedDown();
void IN_SpeedUp();
void IN_UpdateUseCount(LocalClientNum_t localClientNum);
void IN_UpdateUseHeld(LocalClientNum_t localClientNum);
void IN_Activate_Down(LocalClientNum_t localClientNum, int key, unsigned int time, float value);
void IN_Activate_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_Reload_Down(LocalClientNum_t localClientNum, int key, unsigned int time, float value);
void IN_Reload_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_UseReload_Down(LocalClientNum_t localClientNum, int key, unsigned int time, float value);
void IN_UseReload_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_Attack_Down(LocalClientNum_t localClientNum, int key, unsigned int time, float value);
void IN_Attack_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_Melee_Down(int a1, int a2, int time, unsigned int a4);
void IN_Melee_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_Frag_Down(int a1, int a2, int time, unsigned int a4);
void IN_Frag_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_Smoke_Down(int a1, int a2, int time, unsigned int a4);
void IN_Smoke_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_Stance_Down(unsigned int a1, LocalClientNum_t localClientNum, int key, unsigned int time, float value);
void __cdecl IN_Stance_Up(LocalClientNum_t localClientNum, int key, unsigned int time);
void IN_WeapNextInventoryDown(LocalClientNum_t localClientNum);
void IN_WeapNextInventoryUp(LocalClientNum_t localClientNum);
void IN_ToggleADS(LocalClientNum_t localClientNum);
void IN_CenterView(LocalClientNum_t localClientNum);
void IN_LowerStance();
void IN_RaiseStance();
bool IN_IsTalkKeyHeld();
void CL_AdjustAngles(LocalClientNum_t localClientNum);
void CL_StanceButtonUpdate(LocalClientNum_t localClientNum);
void CL_GetMouseMovement(clientActive_t *cl, float *mx, float *my);
void SetMeleeChargeCmd(const AimOutput *aimOutput, usercmd_s *cmd);
void CL_SetCursorPos(int x, int y);
void CL_ShowSystemCursor(int show);
void CL_CopyDamageKickAngles(LocalClientNum_t localClientNum, usercmd_s *cmd);
int CL_ReadyToSendPacket(LocalClientNum_t localClientNum);
void CL_SendCmd(LocalClientNum_t localClientNum);
void CL_InitInput();
void CL_ShutdownInput();
void CL_ClearKeys(LocalClientNum_t localClientNum);
void CL_ExecBinding(int a1, kbutton_t *a2, LocalClientNum_t localClientNum, Bind_t kb, int key, float value);
bool CL_SpectatorInput(LocalClientNum_t localClientNum, int button);
bool CL_TranslateSpecialStateButton(int a1, kbutton_t *a2, LocalClientNum_t localClientNum, int button);
void CL_UpdateAirburstMarkDistance(LocalClientNum_t localClientNum, playerState_s *ps, usercmd_s *cmd, float forwardMove, float rightMove, float pitchMove, float yawMove, float moveScale);
void CL_AddCurrentStanceToCmd(LocalClientNum_t localClientNum, usercmd_s *cmd);
void CL_WeapNextButtonUpdate(LocalClientNum_t localClientNum, usercmd_s *cmd);
void CL_KeyMove(LocalClientNum_t localClientNum, usercmd_s *cmd);
int CL_MouseEvent(LocalClientNum_t localClientNum, int x, int y, int dx, int dy);
// void CL_UpdateCmdButton(LocalClientNum_t localClientNum, bitarray<64> *cmdButton_bits, int kbButton, int buttonBit, int numBits);
void CL_CmdButtons(LocalClientNum_t localClientNum, usercmd_s *cmd);
bool CG_HandleLocationSelectionInput(LocalClientNum_t localClientNum, usercmd_s *cmd);
// void CL_HandleSpectatorInput(LocalClientNum_t localClientNum, bitarray<64> *button_bits);
// void CL_HandleSpecialStateInput(bitarray<64> *a1, LocalClientNum_t a2, LocalClientNum_t localClientNum);
void CL_GamepadMove(LocalClientNum_t localClientNum, usercmd_s *cmd, float frametime_base);
void CL_MouseMove(LocalClientNum_t localClientNum, usercmd_s *cmd, float frametime_base);
usercmd_s *CL_CreateCmd(LocalClientNum_t localClientNum);
void CL_CreateNewCommands(LocalClientNum_t localClientNum);
void CL_Input(LocalClientNum_t localClientNum);
void TRACK_cl_input();

//t6/code/src/client/cl_keys.cpp
void Field_AdjustScroll(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit);
char Field_Paste(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit);
void FindMatches(const char *s);
void PrintMatches(const char *s);
BOOL Console_IsRconCmd(const char *commandString);
bool Console_IsClientDisconnected();
int keyConcatArgs();
void ReplaceConsoleInputArgument(int replaceCount, const char *replacement);
void CompleteCmdArgument();
void CompleteDvarArgument();
void UpdateMatches(bool searchCmds, int *matchLenAfterCmds, int *matchLenAfterDvars);
void CompleteCommand(LocalClientNum_t localClientNum);
bool Console_IsScrollUpKey(int key, int isShiftDown, int isCtrlDown);
bool Console_IsScrollDownKey(int key, int isShiftDown, int isCtrlDown);
int Key_GetOverstrikeMode(LocalClientNum_t localClientNum);
void Key_SetOverstrikeMode(LocalClientNum_t localClientNum, int state);
int Key_IsDown(LocalClientNum_t localClientNum, int keynum);
int Key_StringToKeynum(LocalClientNum_t localClientNum, const char *str);
BOOL Key_IsValidGamePadChar(const char key);
const char *Key_KeynumToString(int keynum, int translate);
void Key_SetBinding(LocalClientNum_t localClientNum, int keynum, Bind_t binding, BindIndex_t index);
void Key_SetBindingCheat(LocalClientNum_t localClientNum, int keynum, const char *bindingCheat);
void Key_SetBindings(LocalClientNum_t localClientNum, int *twokeys, Bind_t binding, BindIndex_t bindNum);
Bind_t Key_GetBinding(LocalClientNum_t localClientNum, int keynum, BindIndex_t index);
int Key_GetCommandAssignmentInternal(LocalClientNum_t localClientNum, Bind_t binding, int *twokeys, BindIndex_t bindNum, int gamePadOnly);
int Key_GetSafeFreeKey(LocalClientNum_t localClientNum, BindIndex_t bindNum);
int Key_GetMouseKeyboardCommandAssignment(LocalClientNum_t localClientNum, Bind_t binding, int *twokeys, BindIndex_t bindNum);
void Key_BindMustHaveCommands(LocalClientNum_t localClientNum);
void Key_UpdateMustHaveBindings_f();
int Key_GetCommandAssignment(LocalClientNum_t localClientNum, Bind_t binding, int *twokeys, BindIndex_t bindNum);
void Key_Unbind_f();
void Key_Unbind2_f();
void Key_Unbindall_f();
void Key_Unbindall2_f();
void Key_ClearStates(LocalClientNum_t localClientNum);
int CL_IsKeyPressed(const LocalClientNum_t localClientNum, const char *keyName);
void Key_Shutdown();
bool Key_IsCatcherActive(LocalClientNum_t localClientNum, int mask);
void Key_AddCatcher(LocalClientNum_t localClientNum, int orMask);
void Key_RemoveCatcher(LocalClientNum_t localClientNum, int andMask);
void Key_SetCatcher(LocalClientNum_t localClientNum, int catcher);
Bind_t Key_GetBindingForCmd(const char *cmd);
const char *Key_GetCmdForBinding(Bind_t binding);
void Field_DrawTextOverride(LocalClientNum_t localClientNum, const field_t *edit, int x, int y, int horzAlign, int vertAlign, const char *str, int drawLen, int cursorPos, bool FullUnsafe);
void Field_Draw(LocalClientNum_t localClientNum, field_t *edit, int x, int y, int horzAlign, int vertAlign, bool fullUnSafe);
bool Field_KeyDownEvent(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit, int key);
char Field_CharEvent(LocalClientNum_t localClientNum, const ScreenPlacement *scrPlace, field_t *edit, int ch);
void __cdecl Console_Key(LocalClientNum_t localClientNum, int key);
void Message_Key(LocalClientNum_t localClientNum, int key);
const char *Key_GetBindingCheat(LocalClientNum_t localClientNum, int keynum);
int Key_GetCheatAssignmentInternal(LocalClientNum_t localClientNum, const char *command, int *twokeys, int gamePadOnly);
BOOL Key_IsCommandBound(LocalClientNum_t localClientNum, const char *command, BindIndex_t bindIndex);
void Key_Bind_f();
void Key_Bind2_f();
void Key_Bindlist_f();
void CL_InitKeyCommands();
void CL_KeyEvent(LocalClientNum_t localClientNum, int key, const int down, const unsigned int time);
void CL_ConsoleCharEvent(LocalClientNum_t localClientNum, int key);
void CL_CharEvent(LocalClientNum_t localClientNum, int key);
int __cdecl CL_GetKeyBindingInternal(LocalClientNum_t localClientNum, const char *command, char (*keyNames)[128], int gamePadOnly, BindIndex_t bindNum);
int CL_GetKeyBinding(LocalClientNum_t localClientNum, const char *command, char (*keyNames)[128], BindIndex_t bindNum);
int CL_GetGamePadBinding(LocalClientNum_t localClientNum, const char *command, char (*keyNames)[128], BindIndex_t bindNum);
void Key_WriteBindings(LocalClientNum_t localClientNum, int f);
int Key_WriteBindingsToBuffer(LocalClientNum_t localClientNum, char* buffer, int bufferSize);
void TRACK_cl_keys();

//t6/code/src/client/cl_main.cpp
char CL_AnyLocalClientsRunning();
void CL_Command_DisableAllButPrimaryClients();
void CL_Command_SetClientBeingUsedAndPrimary();
void CL_Command_SetClientBeingUsedAndPrimaryAndActive();
void CL_Command_SetClientPrimary();
void CL_Command_SetClientBeingUsed();
void CL_Command_SetClientBeingUsedAndActive();
void CL_Command_DisableAllClients();
void CL_Command_SignClientOutOfUI();
void CL_Command_SignClientIn();
void CL_SetupClientsForIngame();
void CL_DrawFramedPicPhysical(float x, float y, float w, float h, float thicknessW, float thicknessH, float thicknessTex, int sides, const vec4_t *color, Material *material);
void CL_ForwardToServer_f();
void CL_Setenv_f();
void CL_SkipLevel_f();
void CL_Vid_Restart_f();
void CL_Snd_Restart_f();
void CL_OpenedIWDList_f();
void CL_ReferencedIWDList_f();
void CL_Configstrings_f();
void CL_Clientinfo_f();
bool CL_WasMapAlreadyLoaded();
void CL_Live_StopAllParties();
void CL_Live_StopPrivateParty();
void CL_Live_LeaveParty(PartyData_s *party, ControllerIndex_t localControllerIndex);
void CL_Live_LeaveAllParties(ControllerIndex_t localControllerIndex);
char CL_Live_LocalClientJoinParty(PartyData_s *party, ControllerIndex_t localControllerIndex);
void CL_Live_StopParty(bool keepPartyTogether);
void CL_Live_PartySwitchLobbies();
void CL_ExecControllerBindings_f();
void CL_Live_ShowFriendsList();
void CL_Live_StartPartyHost(ControllerIndex_t localControllerIndex, bool silentFail);
void CL_Live_StartPartyHost();
void CL_Live_PartyMapVeto();
void CL_Live_UpdatePartyState();
void CL_Live_PartyMapReady();
void CL_UpdateSession(PartyData_s *party, SessionData *session, int maxplayers);
int CL_GetUserMaxPlayerSetting(ControllerIndex_t controllerIndex);
void CL_Live_SessionUpdate();
void CL_AnimateUI_f();
void __cdecl CL_ResetSelectedPlayerXuid_f();
void CL_DrawSpinnerPhysical(float x, float y, float w, float h, const vec4_t *color);
void CL_DrawSpinner(const ScreenPlacement *scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, const vec4_t *color);
void CL_DrawSpinnerLoadbarPhysical(float x, float y, float w, float h, const vec4_t *color, float percentDone);
void CL_DrawSpinnerLoadbar(const ScreenPlacement *scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, const vec4_t *color, float percentDone);
void CL_ShutdownHunkUsers();
void CL_SendBlackboxSession(ControllerIndex_t controllerIndex, bool isserver, const char *mapname, const char *gametype);
void CL_ResetSkeletonCache(LocalClientNum_t localClientNum);
int CL_HighestPriorityStatPacket(clientConnection_t *clc, int numCompressedStatsPackets);
void CL_CheckForResend(LocalClientNum_t localClientNum);
void CL_DisconnectError(const char *message);
void CL_DisconnectPacket(LocalClientNum_t localClientNum, netadr_t from, const char *reason);
void CL_HandleRelayPacket(LocalClientNum_t localClientNum);
char CL_HandleVoiceTypePacket(LocalClientNum_t localClientNum, msg_t *msg);
void CL_SetupForNewServerMap(LocalClientNum_t localClientNum, const char *pszMapName, const char *pszGametype);
void CL_AuthRequestPacket(LocalClientNum_t localClientNum, unsigned __int64 serverSteamID);
bool CL_DispatchConnectionlessPacket(LocalClientNum_t localClientNum, netadr_t from, msg_t *msg, int time);
bool CL_ConnectionlessPacket(int a1, LocalClientNum_t localClientNum, netadr_t from, msg_t *msg);
bool CL_PacketEvent(LocalClientNum_t localClientNum, netadr_t from, msg_t *msg, int time, bool connectionlesss_packets_only);
BOOL CL_LocalClientIsInGame(LocalClientNum_t localClientNum);
char CL_IsClientLocal(ClientNum_t clientNum);
void CL_ParseBadPacket_f();
void CL_SetupViewport();
void __cdecl CL_SetupViewport_f();
void CL_InitRenderer();
void CL_DevGuiDvar_f();
void CL_DevGuiDvarList_f();
void CL_DevGuiCmd_f();
void CL_DevGuiOpen_f();
void CL_InitDevGui();
void CL_StartHunkUsers();
int CL_ScaledMilliseconds();
void CL_InitDedicated();
void CL_startSingleplayer_f();
void CL_startZombies_f();
void CL_startMultiplayer_f();
void CL_PlayLogo_f();
void CL_OpenScriptMenu_f();
char Playlist_ReadFromDisk();
char __cdecl Playlist_CmdReadFromDisk();
void CL_VoiceFail_f();
void CL_ForceVoiceFail_f();
void CL_MigrateHost_f();
void CL_SetNatStrict_f();
void CL_SetNatOpen_f();
void CL_LoadFFOTD_f();
void CL_ChooseNextPlaylist();
void CL_ChoosePreviousPlaylist();
void CL_LocalServers_f();
void CL_FlushGump(int slot);
void __cdecl CL_FlushGumps();
void CL_LoadGump();
void CL_AddListenIn_f();
void CL_RemoveListenIn_f();
void CL_ResetListenIn_f();
void CL_SetListenIn_f();
void CL_RemoveCommands();
void CL_RegisterDvars();
bool CL_IsServerLoadingMap();
bool CL_IsWaitingOnServerToLoadMap(LocalClientNum_t localClientNum);
void CL_SetWaitingOnServerToLoadMap(LocalClientNum_t localClientNum, bool waiting);
void CL_DrawTextPhysical(const char *text, int maxChars, Font_s *font, float x, float y, float w, float xScale, float yScale, const vec4_t *color, int style, float padding);
void CL_DrawTextPhysicalWithEffects(const char *text, int maxChars, Font_s *font, float x, float y, float w, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
void CL_DrawText(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style);
void CL_DrawTextRotate(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style);
void CL_DrawTextPhysicalWithCursor(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, int cursorPos, char cursor);
void CL_DrawTextWithCursor(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, int cursorPos, char cursor);
void CL_DrawTextWithEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
void CL_DrawTextWithCOD7TypeWriterEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
void CL_DrawTextPhysicalWithCOD7TypeWriterEffects(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
void CL_DrawTextWithRedactEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration, int fxRedactDecayStartTime, int fxRedactDecayDuration);
void CL_DrawTextPhysicalWithCOD7DecodeEffects(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
void CL_DrawTextPhysicalWithRedactEffects(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration, int fxRedactDecayStartTime, int fxRedactDecayDuration);
void CL_DrawTextWithPopInEffects(const ScreenPlacement *scrPlace, const char *text, int maxChars, Font_s *font, float x, float y, float rotation, int horzAlign, int vertAlign, float xScale, float yScale, const vec4_t *color, int style, const vec4_t *glowColor, Material *fxMaterial, Material *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
char CL_ShouldDisplayHud(LocalClientNum_t localClientNum);
BOOL CL_IsUIActive(const LocalClientNum_t localClientNum);
Font_s *CL_RegisterFont(const char *fontName, int imageTrack);
vec3_t *CL_GetMapCenter();
void CL_ConnectFromParty(ControllerIndex_t controllerIndex, XSESSION_INFO *hostInfo, netadr_t addr, int numPublicSlots, int numPrivateSlots, const char *mapname);
void CL_SanitizeClanName(ControllerIndex_t controllerIndex);
void CL_UploadStatsForController(const ControllerIndex_t localControllerIndex);
void CL_ClearState(LocalClientNum_t localClientNum);
void CL_MapLoading_SetupDevmapParty();
void CL_Live_StopParty();
void CL_Live_StopPartyKeepPartyTogether();
void CL_ShutdownRenderer(int destroyWindow);
void CL_ShutdownAll();
void CL_MapLoading(const char *mapname);
void CL_DownloadsComplete(LocalClientNum_t localClientNum);
void CL_InitLoad(const char *mapname, const char *gametype);
void CL_ShutdownRef();
void CL_DrawLogo(LocalClientNum_t localClientNum);
void CL_ShowIP_f(bdCommonAddr *notthis);
void CL_RegisterCommands();
void CL_InitOnceForAllClients();
void CL_SetupClientsForFrontend();
void TRACK_cl_main();

//t6/code/src/client/cl_main_dw.cpp
void CL_Live_PartyPlay();

//t6/code/src/client/cl_main_pc.cpp
void CL_Live_ShowGamerCard();
void CL_Live_UpdatePartyMapPacks();
void CL_Platform_RemoveCommands();
BOOL CL_IsPlayerMuted(SessionData *session, LocalClientNum_t localClientNum, ClientNum_t muteClientIndex);
int CL_IsPlayerMuted(LocalClientNum_t localClientNum, unsigned __int64 playerXuid);

//t6/code/src/client/cl_migration.cpp
void CL_MigrationInit();
void PingAck(const LocalClientNum_t localClientNum, netadr_t to, const int time);
void SendToHost(const LocalClientNum_t localClientNum, const char *cmd, const unsigned __int8 *data, int len);
void Migration_SendMigrateToAck(const char *a1, LocalClientNum_t a2, char *localClientNum, const LocalClientNum_t a4);
int GetHostRating(const LocalClientNum_t localClientNum);
void CL_SaveMigrationPers(LocalClientNum_t localClientNum);
void CL_LoadMigrationPers(LocalClientNum_t localClientNum);
void HandleSaveDataMsg(const LocalClientNum_t localClientNum, netadr_t from, msg_t *msg);
void __cdecl HandlePingMsg(const LocalClientNum_t localClientNum, netadr_t from, msg_t *msg);
void HandlePingAckMsg(const LocalClientNum_t localClientNum, netadr_t from, msg_t *msg);
void __cdecl HandleHeaderMsg(const LocalClientNum_t localClientNum, netadr_t from, msg_t *msg);
char CL_MigrationPacket(const LocalClientNum_t localClientNum, const char *cmd, netadr_t from, msg_t *msg);
void CL_Migrate(LocalClientNum_t localClientNum, XSESSION_INFO *hostInfo, netadr_t addr);
void HandleStartMsg(char *a1, const LocalClientNum_t localClientNum);

//t6/code/src/client/cl_parse.cpp
void CL_SavePredictedPlayerInformationForServerTime(clientActive_t *cl, const int serverTime);
char CL_GetClientArchiveIndexForServerTime(clientActive_t *cl, const int serverTime, int *resultIndex);
char CL_GetPredictedPlayerInformationForServerTime(clientActive_t *cl, const int serverTime, playerState_s *to);
void CL_SavePredictedVehicleForServerTime(clientActive_t *cl, const int serverTime, const PlayerVehicleState *predictedPlayerVehState);
int CL_GetPredictedVehicleForServerTime(clientActive_t *cl, const int serverTime, PlayerVehicleState *predictedPlayerVehState);
void CL_CopyOldEntity(clientActive_t *cl, clSnapshot_t *frame, entityState_s *old);
void CL_ParsePacketMatchState(clientActive_t *cl, msg_t *msg, const int time, clSnapshot_t *oldframe, clSnapshot_t *newframe);
void CL_DeltaClient(clientActive_t *cl, msg_t *msg, const int time, clSnapshot_t *frame, int newnum, clientState_s *old, int unchanged);
void CL_ParsePacketClients(clientActive_t *cl, msg_t *msg, const int time, clSnapshot_t *oldframe, clSnapshot_t *newframe);
void CL_ParsePacketActors(clientActive_t *cl, msg_t *msg, const int time, clSnapshot_t *oldframe, clSnapshot_t *newframe);
void CL_ServerIdChanged(LocalClientNum_t localClientNum);
void CL_SystemInfoChanged(LocalClientNum_t localClientNum);
void CL_ParseMapCenter();
void StoreConfigString(int index, const char *s);
void CL_ParseConfigStrings_Internal(LocalClientNum_t localClientNum, msg_t *msg, void (*storeHandler)(int, const char *));
void CL_CheckBSPCheckSum(unsigned int serverChecksum);
void CL_ParseGamestate_Checksums(LocalClientNum_t localClientNum, msg_t *msg);
void CL_ParseGamestate(LocalClientNum_t localClientNum, msg_t *msg);
void CL_ParseServerMessage(LocalClientNum_t localClientNum, msg_t *msg);
void TRACK_cl_parse();

//t6/code/src/client/con_channels.cpp
bool Con_OpenChannel(const char *name, bool allowScript);
bool Con_ScriptHasPermission(int channel);
BOOL Con_GetChannel(const char *name, int *channel_result);
bool Con_IsChannelOpen(int channel);
void Con_FilterShowChannel(print_msg_dest_t dest, const char *channelName, bool show);
bool Con_IsChannelVisible(print_msg_dest_t dest, int channel, int errorflags);
void Con_ChannelList_f();
void Con_FilterAdd(bool show);
void Con_FilterAdd_f();
void Con_FilterRemove_f();
void Con_FilterList_f();
void Con_WriteFilterConfigString(int f);
void Con_InitChannelsForDestFromList(print_msg_dest_t dest, const char *channelNames);
void Con_InitGameMsgChannels();
void Con_InitChannels();
void Con_ShutdownChannels();

// t6/code/src/client/screen_placement.cpp
ScreenPlacement *ScrPlace_GetView(const LocalClientNum_t localClientNum);
ScreenPlacement *ScrPlace_GetViewWritable(const LocalClientNum_t localClientNum);
ScreenPlacement *ScrPlace_GetViewUIContext(const UIContextIndex_t contextIndex);
ScreenPlacement *ScrPlace_GetViewUIContextWritable(const UIContextIndex_t contextIndex);
double ScrPlace_HiResGetScaleY();
vec2_t *ScrPlace_CalcSafeAreaOffsets(float *a1, float *a2, float viewportY, float viewportWidth, float horzAspectScale, float vertAspectScale, float safeAreaRatioHorz, float safeAreaRatioVert, float virtualViewableMin, float virtualViewableMax, vec2_t *a11, vec2_t *a12);
void ScrPlace_SetupFloatViewport(ScreenPlacement *scrPlace, float viewportX, float viewportY, float viewportWidth, float viewportHeight, float aspect, bool splitScreen);
void ScrPlace_SetupViewport(ScreenPlacement *scrPlace, int viewportX, int viewportY, int viewportWidth, int viewportHeight, float aspect, bool splitScreen);
void ScrPlace_SetupUnsafeViewport(ScreenPlacement *scrPlace, int viewportX, int viewportY, int viewportWidth, int viewportHeight, float aspect, bool splitScreen);
double ScrPlace_ApplyX(const ScreenPlacement *scrPlace, float x, int horzAlign);
double ScrPlace_ApplyY(const ScreenPlacement *scrPlace, float y, int vertAlign);
double ScrPlace_ApplyW(const ScreenPlacement *scrPlace, float w, int horzAlign);
double ScrPlace_ApplyH(const ScreenPlacement *scrPlace, float h, int vertAlign);
void ApplySplitscreenScaling(float *x, float *y, float *w, float *h, float hudSplitscreenScale);
void ScrPlace_ApplyRect(const ScreenPlacement *scrPlace, float *x, float *y, float *w, float *h, int horzAlign, int vertAlign);
void ScrPlace_SetLegacySplitscreenScaling();
void ScrPlace_SetNormalSplitscreenScaling();
void ScrPlace_Init();

//#include "client/screen_placement.h"

//t6/code/src/client/splitscreen.cpp
int CL_LocalClient_IsActive(LocalClientNum_t localClientNum);
BOOL CL_LocalClient_IsFirstActive(LocalClientNum_t localClientNum);
BOOL CL_LocalClient_GetActiveCount();
char CL_AllLocalClientsDisconnected();
char CL_AllLocalClientStatesActive();
char CL_AnyLocalClientStateActive();
char CL_AnyLocalClientChallenging();
int CL_GetFirstActiveLocalClient();
char CL_IsFirstActiveLocalClient(LocalClientNum_t localClientNum);
char CL_IsLastActiveLocalClient(LocalClientNum_t localClientNum);
int CL_ControllerIndexFromActiveClient(const LocalClientNum_t localActiveClientNum);
int CL_LocalActiveIndexFromClientNum(const LocalClientNum_t localClientNum);
const GfxViewParms *CL_ControllerIndex_GetUsername(ControllerIndex_t controllerIndex);
char *CL_ControllerIndex_GetXuidString(ControllerIndex_t controllerIndex);
void CL_LocalClient_SetActive(LocalClientNum_t localClientNum, bool active);
bool CL_LocalClient_IsSplitscreen();
void CL_LocalClients_SetAllUsedActive();

