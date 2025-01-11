#include "types.h"

typedef struct {
	DevMenuItem menus[2048];
	DevMenuItem *nextFreeMenu;
	DevMenuItem topmostMenu;

	bool bindNextKey;

	bool isActive;
	bool isInitialized;

	bool editingMenuItem;
	unsigned __int16 selectedMenu;
	int selRow;
	bool editingKnot;

	int top;
	int bottom;
	int left;
	int right;
	int sliderWidth;
	int textLabelWidth;
} devguiGlob_t;

extern	devguiGlob_t	devguiGlob;


/*
==============
TRACK_devgui
==============
*/
void TRACK_devgui()
{
	track_static_alloc_internal(&devguiGlob, 82000, "devguiGlob", 0);
}

/*
==============
DevGui_AddDvar
==============
*/
void DevGui_AddDvar(const char *path, const dvar_s *dvar)
{
	if (!path)
	{
		assert("path")
	}
	if (!dvar)
	{
		assert("dvar")
	}

	if (DevGui_IsValidPath(path))
	{
		unsigned __int16 handle = DevGui_ConstructPath_r(0, path);
		DevMenuItem *menu = DevGui_GetMenu(handle);

		if (!menu)
		{
			assert("menu")
		}

		if (!menu->childType && !menu->child.menu || menu->childType == 1 && menu->child.dvar == dvar)
		{
			menu->childType = 1;
			menu->child.command = (const char *)dvar;
		}
		else
		{
			Com_Printf(
				CON_CHANNEL_DEVGUI,
				"Path '%s' can't be used for dvar '%s' because it is already used for something else.\n",
				path,
				dvar->name);
		}
	}
}

/*
==============
DevGui_GetMenu
==============
*/
devguiGlob_t *DevGui_GetMenu(unsigned __int16 handle)
{
	if (!handle || handle > 0x800u)
	{
		assert("handle not in [1, ARRAY_COUNT( devguiGlob.menus )]\n\t%i not in [%i, %i]", handle, 1, 2048);
	}

	return (devguiGlob_t *)((char *)&devguiGlob + 40 * handle - 40);
}

/*
==============
DevGui_ConstructPath_r
==============
*/
unsigned __int16 DevGui_ConstructPath_r(unsigned __int16 parent, const char *path)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_RegisterMenu
==============
*/
unsigned __int16 DevGui_RegisterMenu(unsigned __int16 parentHandle, const char *label, __int16 sortKey)
{
	unsigned __int16 childHandle = DevGui_FindMenu(parentHandle, label);
	if (!childHandle)
	{
		return DevGui_CreateMenu(parentHandle, label, sortKey);
	}

	return childHandle;
}

/*
==============
DevGui_CreateMenu
==============
*/
int DevGui_CreateMenu()
{
	return FALSE;
}

/*
==============
DevGui_GetMenuParent
==============
*/
unsigned __int16 DevGui_GetMenuParent(unsigned __int16 handle)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_EditableMenuItem
==============
*/
bool DevGui_EditableMenuItem(const DevMenuItem *menu)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_FreeMenu_r
==============
*/
void DevGui_FreeMenu_r(unsigned __int16 handle)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_FindMenu
==============
*/
unsigned __int16 DevGui_FindMenu(unsigned __int16 parentHandle, const char *label)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_PathToken
==============
*/
int DevGui_PathToken(const char **pathInOut, char *label, __int16 *sortKeyOut)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_ConstructPath_r
==============
*/
unsigned __int16 DevGui_ConstructPath_r(unsigned __int16 parent, const char *path)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_IsValidPath
==============
*/
bool DevGui_IsValidPath(const char *path)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_AddDvar
==============
*/
void DevGui_AddDvar(const char *path, const dvar_t *dvar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_AddDvarList
==============
*/
void DevGui_AddDvarList(const char *path, const dvar_t *dvar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_AddCommand
==============
*/
void DevGui_AddCommand(const char *path, const char *command)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DoesMenuExist
==============
*/
bool DevGui_DoesMenuExist(const char *path)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_RemoveMenu
==============
*/
void DevGui_RemoveMenu(const char *path)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_OpenMenu
==============
*/
void DevGui_OpenMenu(const char *path)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_MaxChildMenuWidth
==============
*/
int DevGui_MaxChildMenuWidth(LocalClientNum_t localClientNum, const DevMenuItem *menu)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_DrawMenuVertically
==============
*/
void DevGui_DrawMenuVertically(LocalClientNum_t localClientNum, const DevMenuItem *menu, unsigned __int16 activeChild, int *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawMenuHorizontally
==============
*/
void DevGui_DrawMenuHorizontally(LocalClientNum_t localClientNum, const DevMenuItem *menu, unsigned __int16 activeChild, int *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawMenu
==============
*/
void DevGui_DrawMenu(const DevMenuItem *a1, LocalClientNum_t localClientNum, int *menuHandle, int *activeChild, int *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_ChooseOrigin
==============
*/
void DevGui_ChooseOrigin(LocalClientNum_t localClientNum, int *origin)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_GetSliderPath
==============
*/
unsigned int DevGui_GetSliderPath(unsigned __int16 menuHandle, char *path, int pathLen)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_DrawSliderTitle
==============
*/
void DevGui_DrawSliderTitle(int x, int y, const DevMenuItem *menu)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawSingleSlider
==============
*/
void DevGui_DrawSingleSlider(int x, int y, int rowWidth, int rowHeight, float fraction, const unsigned __int8 *knobColor)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawDvarValue
==============
*/
void DevGui_DrawDvarValue(int x, int y, const dvar_t *dvar)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_MenuRowCount
==============
*/
int DevGui_MenuRowCount(const DevMenuItem *menu)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_SelectedDvarFromMenu
==============
*/
const dvar_t *DevGui_SelectedDvarFromMenu(const DevMenuItem *menu)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
DevGui_DrawSliders
==============
*/
void DevGui_DrawSliders(const DevMenuItem *menu)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawBindNextKey
==============
*/
void DevGui_DrawBindNextKey()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_DrawGraph
==============
*/
void DevGui_DrawGraph(const DevMenuItem *menu, LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_Draw
==============
*/
void DevGui_Draw(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_AdvanceChildNum
==============
*/
void DevGui_AdvanceChildNum(int numberToAdvance)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_SelectTopLevelChild
==============
*/
void DevGui_SelectTopLevelChild()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_Init
==============
*/
void DevGui_Init()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_Shutdown
==============
*/
void DevGui_Shutdown()
{
	DevGui_InputShutdown();
	DevGui_MenuShutdown();
}

/*
==============
DevGui_RegisterDvars
==============
*/
void DevGui_RegisterDvars(int key)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_MenuShutdown
==============
*/
void DevGui_MenuShutdown()
{
	DevGui_FreeMenu_r(devguiGlob.topmostMenu.child.menu);
}

/*
==============
DevGui_KeyPressed
==============
*/
void DevGui_KeyPressed(int key)
{
	char path[128];

	if (devguiGlob.bindNextKey)
	{
		devguiGlob.bindNextKey = 0;

		if (key == K_ESCAPE)
		{
			return;
		}

		if (key == K_TAB || key == K_F1)
		{
			Com_Printf(CON_CHANNEL_DEVGUI, "Can't rebind 'tab' or 'F1'\n");
		}
		// maybe else if just in case?
		else
		{
			unsigned __int16 handle = devguiGlob.selectedMenu;
			if (!devguiGlob.selectedMenu)
			{
				assert("handle");
			}

			DevMenuItem* menu = (DevMenuItem*)DevGui_GetMenu(handle);
			if (!menu)
			{
				assert("menu");
			}

			if (menu->parent && (!menu->childType || menu->childType == 1 && !devguiGlob.editingMenuItem))
			{
				handle = menu->parent;
			}

			DevGui_GetSliderPath(handle, path, 0);

			// bind
			Key_SetBinding(LOCAL_CLIENT_0, key, va("devgui_open \"%s\"", path), 0);
		}
	}
}

/*
==============
DevGui_Toggle
==============
*/
void DevGui_Toggle()
{
	if (devguiGlob.isActive)
	{
		assert("!devguiGlob.isActive");
	}

	if (devguiGlob.topmostMenu.child.menu)
	{
		// is this even needed?
#if 0
		if (devguiGlob.selectedMenu)
		{
			devguiGlob.isActive = !devguiGlob.isActive;
			if (devguiGlob.isActive)
			{
				DevGui_SelectGamepad(CONTROLLER_INDEX_FIRST);
			}
		}
#endif

		devguiGlob.selectedMenu = devguiGlob.topmostMenu.child.menu;
		if (devguiGlob.topmostMenu.child.menu)
		{
			DevGui_SelectTopLevelChild();
		}
	}
}

/*
==============
DevGui_IsActive
==============
*/
bool DevGui_IsActive()
{
	return devguiGlob.isActive;
}

/*
==============
DevGui_IsInitialized
==============
*/
bool DevGui_IsInitialized()
{
	return devguiGlob.isInitialized;
}
