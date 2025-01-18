#include "types.h"

#define MAX_DEVGUI_SIZE	82004

const dvar_t *devgui_colorBgnd;
const dvar_t *devgui_colorText;
const dvar_t *devgui_colorBgndSel;
const dvar_t *devgui_colorTextSel;
const dvar_t *devgui_colorBgndGray;
const dvar_t *devgui_colorTextGray;
const dvar_t *devgui_colorBgndGraySel;
const dvar_t *devgui_colorTextGraySel;
const dvar_t *devgui_colorSliderBgnd;
const dvar_t *devgui_colorSliderKnob;
const dvar_t *devgui_colorSliderKnobSel;
const dvar_t *devgui_bevelShade;
const dvar_t *devgui_colorGraphKnotNormal;
const dvar_t *devgui_colorGraphKnotSelected;
const dvar_t *devgui_colorGraphKnotEditing;
const dvar_t *devgui_zoomEnabled;

/*
==============
TRACK_devgui
==============
*/
void TRACK_devgui()
{
	track_static_alloc_internal(&devguiGlob, MAX_DEVGUI_SIZE, "devguiGlob", 0);
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
		assertMsg("handle not in [1, ARRAY_COUNT( devguiGlob.menus )]\n\t%i not in [%i, %i]", handle, 1, 2048);
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
void DevGui_RegisterDvars()
{
	devgui_colorBgnd = _Dvar_RegisterColor(
							"devgui_colorBgnd",
							0.0,
							0.419608,
							0.0,
							0.74902,
							DVAR_NOFLAG,
							"Color background for the devgui");
	devgui_colorText = _Dvar_RegisterColor(
							"devgui_colorText",
							1.0,
							1.0,
							1.0,
							1.0,
							DVAR_NOFLAG,
							"Text color for the devgui");
	devgui_colorBgndSel = _Dvar_RegisterColor(
								"devgui_colorBgndSel",
								0.0,
								0.69999999,
								0.0,
								0.75,
								DVAR_NOFLAG,
								"Selection background color for the devgui");
	devgui_colorTextSel = _Dvar_RegisterColor(
								"devgui_colorTextSel",
								0.0,
								0.701961,
								0.0,
								0.74902,
								DVAR_NOFLAG,
								"Selection text color for the devgui");
	devgui_colorBgndGray = _Dvar_RegisterColor(
								"devgui_colorBgndGray",
								0.2,
								0.2,
								0.2,
								0.901961,
								DVAR_NOFLAG,
								"Grayed out background color for the devgui");
	devgui_colorTextGray = _Dvar_RegisterColor(
								"devgui_colorTextGray",
								0.901961,
								0.901961,
								0.901961,
								1.0,
								DVAR_NOFLAG,
								"Greyed out text color for the devgui");
	devgui_colorBgndGraySel = _Dvar_RegisterColor(
								"devgui_colorBgndGraySel",
								0.4,
								0.4,
								0.4,
								0.901961,
								DVAR_NOFLAG,
								"Greyed out, selected background color for the devgui");
	devgui_colorTextGraySel = _Dvar_RegisterColor(
								"devgui_colorTextGraySel",
								1.0,
								1.0,
								0.0,
								1.0,
								DVAR_NOFLAG,
								"Greyed out, selected text color for the devgui");
	devgui_colorSliderBgnd = _Dvar_RegisterColor(
								"devgui_colorSliderBgnd",
								1.0,
								1.0,
								1.0,
								0.74902,
								DVAR_NOFLAG,
								"Color slider background for the devgui");
	devgui_colorSliderKnob = _Dvar_RegisterColor(
								"devgui_colorSliderKnob",
								1.0,
								1.0,
								1.0,
								1.0,
								DVAR_NOFLAG,
								"Knob color for the devgui");
	devgui_colorSliderKnobSel = _Dvar_RegisterColor(
									"devgui_colorSliderKnobSel",
									1.0,
									0.74902,
									0.0,
									1.0,
									DVAR_NOFLAG,
									"Selected knob color for the devgui");
	devgui_bevelShade = _Dvar_RegisterFloat(
							"devgui_bevelShade",
							0.7,
							0.0,
							1.0,
							DVAR_NOFLAG,
							"Bevel shade for the devgui");
	devgui_colorGraphKnotNormal = _Dvar_RegisterColor(
										"devgui_colorGraphKnotNormal",
										0.0,
										1.0,
										1.0,
										0.701961,
										DVAR_NOFLAG,
										"Devgiu Color graph knot normal color");
	devgui_colorGraphKnotSelected = _Dvar_RegisterColor(
										"devgui_colorGraphKnotSelected",
										1.0,
										0.0,
										0.0,
										0.701961,
										DVAR_NOFLAG,
										"Devgui color graph knot selected color");
	devgui_colorGraphKnotEditing = _Dvar_RegisterColor(
										"devgui_colorGraphKnotEditing",
										1.0,
										0.0,
										1.0,
										1.0,
										DVAR_NOFLAG,
										"Devgui color graph knot editing color");
	devgui_zoomEnabled = _Dvar_RegisterBool(
							"devgui_zoomEnabled",
							false,
							DVAR_NOFLAG,
							"Enlarges the currently selected Devgui cell.");
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

	//todo: maybe make this just a return if false
	if (devguiGlob.bindNextKey)
	{
		devguiGlob.bindNextKey = 0;

		if (key == K_ESCAPE)
			return;

		if (key == K_TAB || key == K_F1)
		{
			Com_Printf(CON_CHANNEL_DEVGUI, "Can't rebind 'tab' or 'F1'\n");
		}
		// maybe else if just in case?
		else
		{
			unsigned __int16 handle = devguiGlob.selectedMenu;
			assert(!handle);

			DevMenuItem* menu = (DevMenuItem*)DevGui_GetMenu(handle);
			assert(!menu);

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
	assert(devguiGlob.isActive);

	if (!devguiGlob.topmostMenu.child.menu)
		return; // probably bad

	DevGui_SelectTopLevelChild();
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
