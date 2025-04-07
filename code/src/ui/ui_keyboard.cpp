#include "types.h"

keyBoardUtitlity uiKeyboard;

/*
==============
UI_SetActiveKeyboardType
==============
*/
void UI_SetActiveKeyboardType(int keyboardType)
{
	assert(uiKeyboard.keyboardType == KEYBOARD_TYPE_NONE);

	if (!uiKeyboard.keyboardActive)
	{
		uiKeyboard.keyboardType = keyboardType;
		uiKeyboard.keyboardActive = 1;
	}

	assert(uiKeyboard.keyboardActive == NULL);
	uiKeyboard.keyboardType = keyboardType;
	uiKeyboard.keyboardActive = 1;
}

/*
==============
UI_Keyboard_ClanTagEntered
==============
*/
void UI_Keyboard_ClanTagEntered(LocalClientNum_t localClientNum, const char *clanTag)
{
	ControllerIndex_t ControllerIndex = Com_LocalClient_GetControllerIndex(localClientNum);
	EUserTier Tier = Live_GetTier(ControllerIndex);

	if (!UI_CheckCODClanTag(clanTag) || Tier == USER_TIER_DEVELOPER || Tier == USER_TIER_SUPER)
	{
		LiveStats_SetClanTagText(ControllerIndex, clanTag);
		CL_SanitizeClanName(ControllerIndex);
	}
	else
	{
		Com_SetErrorMessage("MP_CODNOTALLOWED");
		UI_OpenErrorPopup(localClientNum);

		uiKeyboard.keyboardActive = 0;
		uiKeyboard.keyboardType = 0;
	}
}

/*
==============
UI_Keyboard_ParseEmail
==============
*/
BOOL UI_Keyboard_ParseEmail(const char *address)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
UI_Keyboard_CheckValidEmail
==============
*/
void UI_Keyboard_CheckValidEmail()
{
	if (!UI_Keyboard_ParseEmail(ui_email_address->current.string))
	{
		UI_OpenMenu(LOCAL_CLIENT_FIRST, "email_rejected");
	}

	UI_OpenMenu(LOCAL_CLIENT_FIRST, "email_accepted");

	const char* dvar = Dvar_GetString(ui_email_address);
	if (I_strncmp(dvar, last_email_sent, 64))
	{
		I_strncpyz(last_email_sent, dvar, 64);
		dwRecordEventFormat(CONTROLLER_INDEX_FIRST, DW_EVENT_EMAIL, "EMAIL:%s", dvar);
	}
}

/*
==============
UI_Keyboard_EmailEntry_f
==============
*/
void UI_Keyboard_EmailEntry_f()
{
	Cbuf_AddText(LOCAL_CLIENT_FIRST, va("ui_keyboard_new %d ", 2));
}

/*
==============
UI_KeyboardComplete
==============
*/
void UI_KeyboardComplete(LocalClientNum_t localClientNum)
{
	NIMPLEMENTED(__FUNCTION__);
}

/*
==============
UI_Keyboard_Complete_f
==============
*/
void UI_Keyboard_Complete_f()
{
	UI_KeyboardComplete(LOCAL_CLIENT_FIRST);
}

/*
==============
UI_Keyboard_Cancel_f
==============
*/
void UI_Keyboard_Cancel_f()
{
	uiKeyboard.keyboardActive = 0;
	uiKeyboard.keyboardType = 0;
}

/*
==============
UI_Keyboard_New_f
==============
*/
void UI_Keyboard_New_f()
{
	const char *v1; // eax
	int v2; // eax
	const char *KeyboardTitle; // ebx
	const char *KeyboardDefaultText; // esi
	int KeyboardTextSize; // edi
	const char *v6; // eax
	const char *v7; // eax
	const char *v8; // eax
	const char *v9; // eax
	const char *v10; // eax
	const char *v11; // eax
	int keyboardType; // [esp+0h] [ebp-4h]
  
	if (Cmd_Argc() != 2 || Cmd_Argc() != 5 || Cmd_Argc() != 6)
	{
		Com_Printf(
			CON_CHANNEL_SYSTEM,
			"Usage: ui_keyboard_new <type>\n"
			" OR \n"
			" ui_keyboard_new <type> <title> <defaultString> <size>\n"
			" OR \n"
			" type specific\n");
	}

	keyboardType = atoi(Cmd_Argv(1));

	if ((atoi(Cmd_Argv(1)) - 1) > 16)
	{
		Com_Printf(CON_CHANNEL_SYSTEM, "Unsupported keyboard type %d.\n", atoi(Cmd_Argv(1)));
	}
	else
	{
		switch (atoi(Cmd_Argv(1)))
		{
		case 1:
			KeyboardTitle = Demo_GetKeyboardTitle();
			KeyboardDefaultText = Demo_GetKeyboardDefaultText();
			KeyboardTextSize = Demo_GetKeyboardTextSize();
			break;
		case 2:
			KeyboardTitle = UI_SafeTranslateString("MENU_EMAIL_KEYBOARD_TITLE_CAPS");
			KeyboardDefaultText = ui_email_address->current.string;
			KeyboardTextSize = 64;
			break;
		case 3:
			KeyboardTitle = UI_SafeTranslateString("MENU_CUSTOMCLASS_KEYBOARD");
			KeyboardDefaultText = "";
			KeyboardTextSize = 16;
			break;
		case 17:
			KeyboardTitle = UI_SafeTranslateString("MENU_CLASS_SET_KEYBOARD");
			KeyboardDefaultText = "";
			KeyboardTextSize = 16;
			break;
		case 4:
			KeyboardTitle = UI_SafeTranslateString("MENU_ENTER_TEAM_NAME");
			KeyboardDefaultText = "";
			KeyboardTextSize = 16;
			break;
		case 5:
			KeyboardTitle = UI_SafeTranslateString("MENU_TWITCH_USERNAME");
			KeyboardDefaultText = "";
			KeyboardTextSize = 25;
			break;
		case 6:
			KeyboardTitle = UI_SafeTranslateString("MENU_TWITCH_PASSWORD");
			KeyboardDefaultText = "";
			KeyboardTextSize = 40;
			break;
		case 15:
			KeyboardTitle = UI_SafeTranslateString("MENU_TWITTER_USERNAME");
			KeyboardDefaultText = "";
			KeyboardTextSize = 128;
			break;
		case 16:
			KeyboardTitle = UI_SafeTranslateString("MENU_TWITTER_PASSWORD");
			KeyboardDefaultText = "";
			KeyboardTextSize = 128;
			break;
		case 9:
		case 10:
		case 12:
			KeyboardTitle = Cmd_Argv(2);
			if (I_stricmp(Cmd_Argv(3), "n/a"))
			{
				KeyboardDefaultText = Cmd_Argv(3);
			}
			else
			{
				KeyboardDefaultText = "";
			}
			KeyboardTextSize = atoi(Cmd_Argv(4));
			break;
		case 11:
			KeyboardTitle = Cmd_Argv(2);
			if (I_stricmp(Cmd_Argv(3), "n/a"))
			{
				KeyboardDefaultText = Cmd_Argv(3);
			}
			else
			{
				KeyboardDefaultText = "";
			}
			KeyboardTextSize = atoi(Cmd_Argv(4));
			break;
		case 14:
			KeyboardTitle = UI_SafeTranslateString("MENU_CLAN_NAME");
			KeyboardDefaultText = Clan_GetName();
			KeyboardTextSize = 5;
			break;
		default:
			KeyboardTitle = Cmd_Argv(2);
			KeyboardDefaultText = Cmd_Argv(3);
			KeyboardTextSize = atoi(Cmd_Argv(4));
			break;
		}

		SEH_LocalizeTextMessage(KeyboardTitle, "menu prompt", LOCMSG_SAFE);
		UI_SetActiveKeyboardType(keyboardType);

		uiKeyboard.maxChar = KeyboardTextSize;
		uiKeyboard.cursorPos = strlen(KeyboardDefaultText);
		uiKeyboard.overstrikeMode = 0;

		Dvar_SetString(ui_keyboardtitle, KeyboardTitle);
		Dvar_SetString(ui_keyboard_dvar_edit, KeyboardDefaultText);

		UI_OpenMenu(LOCAL_CLIENT_FIRST, "popmenu_ui_keyboard_text");
	}
}

