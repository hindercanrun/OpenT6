#include "types.h"

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
void DevGui_AddDvar(const char *path, const dvar_t *dvar)
{
	assert(path);
	assert(dvar);

	if (!DevGui_IsValidPath(path))
	{
		return;
	}

	unsigned __int16 handle = DevGui_ConstructPath_r(0, path);
	DevMenuItem *menu = DevGui_GetMenu(handle);
	assert(menu);

	if (menu->childType && !menu->child.menu || menu->childType == 1 && menu->child.dvar == dvar)
	{
		Com_Printf(
			CON_CHANNEL_DEVGUI,
			"Path '%s' can't be used for dvar '%s' because it is already used for something else.\n",
			path,
			dvar->name);
	}

	menu->childType = 1;
	menu->child.command = (const char *)dvar;
}

/*
==============
DevGui_AddDvarList
==============
*/
void DevGui_AddDvarList(char *path, const dvar_t *dvar)
{
	assert(path);
	assert(dvar);

	if (DevGui_IsValidPath(path))
	{
		return;
	}

	unsigned __int16 handle = DevGui_ConstructPath_r(0, path);
	DevMenuItem *menu = DevGui_GetMenu(handle);
	assert(menu);

	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_AddCommand
==============
*/
void DevGui_AddCommand(const char *path, const char *command)
{
	assert(path);
	assert(command);

	if (!DevGui_IsValidPath(path))
	{
		return;
	}

	unsigned __int16 handle = DevGui_ConstructPath_r(0, path);
	devguiGlob_t *menu = DevGui_GetMenu(handle);
	assert(menu);

	if (menu->menus[0].childType && !menu->menus[0].child.menu || menu->menus[0].childType == 2 && menu->menus[0].child.command == command)
	{
		Com_Printf(
			CON_CHANNEL_DEVGUI,
			"Path '%s' can't be used for command '%s' because it is already used for something else.\n",
			path,
			command);
	}

	menu->menus[0].childType = 2;
	menu->menus[0].child.command = CopyString(command, "DevGui_AddCommand", 0);
}

/*
==============
DevGui_AddGraph
==============
*/
void DevGui_AddGraph(const char *path, DevGraph *graph)
{
	assert(graph);
	assert(graph->knots);
	assert(graph->knotCount);
	assert(graph->knotCountMax > 0);
	assert(path);

	DevGui_IsInitialized();
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
DevGui_Draw
==============
*/
void DevGui_Draw(LocalClientNum_t localClientNum)
{
	if (!devguiGlob.isActive)
	{
		return;
	}

	DevMenuItem *menuItem = (DevMenuItem *)DevGui_GetMenu(devguiGlob.selectedMenu);
	if (devguiGlob.editingMenuItem)
	{
		assertMsg(
			(menuItem->childType == DEV_CHILD_GRAPH || menuItem->childType == DEV_CHILD_DVAR),
			"%s\n\t(menuItem->childType) = %i",
			menuItem->childType);

		if (menuItem->childType == DEV_CHILD_DVAR)
		{
			DevGui_DrawSliders(menuItem);
		}
		else
		{
			DevGui_DrawGraph(menuItem, localClientNum);
		}
	}
	else
	{
		int origin[2] = { devguiGlob.left, devguiGlob.top };
		unsigned __int16 parent = DevGui_GetMenuParent(devguiGlob.selectedMenu);

		DevGui_ChooseOrigin(origin);
		DevGui_DrawMenu(parent, devguiGlob.selectedMenu, origin);
	}

	if (devguiGlob.bindNextKey)
	{
		DevGui_DrawBindNextKey(devguiGlob.left, devguiGlob.top);
	}
}

/*
==============
DevGui_Init
==============
*/
void DevGui_Init()
{
	DevGui_RegisterDvars();
	DevGui_InputInit();

	int screen_xPad = 0;
	int screen_yPad = 0;

	for (unsigned int menuIndex = 0; menuIndex < 2047; ++menuIndex)
	{
		devguiGlob.menus[menuIndex].label = &devguiGlob.menus[menuIndex + 1];
	}

	devguiGlob.menus[2047].label = nullptr;

	devguiGlob.nextFreeMenu = (DevMenuItem *)&devguiGlob;
	devguiGlob.topmostMenu.childType = 0;
	devguiGlob.topmostMenu.childMenuMemory = nullptr;
	devguiGlob.topmostMenu.child.menu = nullptr;
	devguiGlob.topmostMenu.nextSibling = nullptr;
	devguiGlob.topmostMenu.prevSibling = nullptr;
	devguiGlob.topmostMenu.parent = nullptr;

	devguiGlob.sliderWidth = 3 * (devguiGlob.right - devguiGlob.left) / 4;
	devguiGlob.selRow = -1;

	devguiGlob.left = screen_xPad;
	devguiGlob.right = DevGui_GetScreenWidth() - screen_xPad;
	devguiGlob.top = screen_yPad;
	devguiGlob.bottom = DevGui_GetScreenHeight() - screen_yPad;

	devguiGlob.editingMenuItem = FALSE;
	devguiGlob.editingKnot = FALSE;
	devguiGlob.isActive = FALSE;
	devguiGlob.isInitialized = TRUE;
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
DevGui_KeyPressed
==============
*/
void DevGui_KeyPressed(int key)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_Update
==============
*/
void DevGui_Update()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_Toggle
==============
*/
void DevGui_Toggle()
{
	UNIMPLEMENTED(__FUNCTION__);
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

/*
==============
DevGui_GetMenu
==============
*/
devguiGlob_t *DevGui_GetMenu(unsigned __int16 handle)
{
	assertMsg(
		handle,
		"handle not in [1, ARRAY_COUNT( devguiGlob.menus )]\n\t%i not in [%i, %i]",
		handle,
		1,
		2048);

	return (devguiGlob_t *)((char *)&devguiGlob + 40 * handle - 40);
}

/*
==============
DevGui_ConstructPath_r
==============
*/
unsigned __int16 DevGui_ConstructPath_r(unsigned __int16 parent, const char *path)
{
}

/*
==============
DevGui_RegisterMenu
==============
*/
unsigned __int16 DevGui_RegisterMenu(unsigned __int16 parentHandle, const char *label, __int16 sortKey)
{
}

/*
==============
DevGui_CreateMenu
==============
*/
int DevGui_CreateMenu()
{
	return 0;
}

/*
==============
DevGui_GetMenuHandle
==============
*/
unsigned __int16 DevGui_GetMenuHandle(DevMenuItem *menu)
{
}

/*
==============
DevGui_CompareMenus
==============
*/
int DevGui_CompareMenus(const DevMenuItem *menu0, const DevMenuItem *menu1)
{
	assert(menu0);
	assert(menu1);

	if (!menu0->sortKey == menu1->sortKey)
	{
		return menu0->sortKey - menu1->sortKey;
	}

	return I_stricmp(menu0->label, menu1->label);
}

/*
==============
DevGui_FindMenu
==============
*/
unsigned __int16 DevGui_FindMenu(unsigned __int16 parentHandle, const char *label)
{
}

/*
==============
DevGui_PathToken
==============
*/
int DevGui_PathToken(const char **pathInOut, char *label, __int16 *sortKeyOut)
{
}

/*
==============
DevGui_IsValidPath
==============
*/
char DevGui_IsValidPath(const char *path)
{
}

/*
==============
DevGui_FreeMenu_r
==============
*/
void DevGui_FreeMenu_r(unsigned __int16 handle)
{
}

/*
==============
DevGui_EditableMenuItem
==============
*/
bool DevGui_EditableMenuItem(const DevMenuItem *menu)
{
}

/*
==============
DevGui_GetMenuParent
==============
*/
unsigned __int16 DevGui_GetMenuParent(unsigned __int16 handle)
{
	return DevGui_GetMenu(handle)->menus[0].parent;
}

/*
==============
DevGui_DrawMenu
==============
*/
void DevGui_DrawMenu(unsigned __int16 menuHandle, unsigned __int16 activeChild, int *origin)
{
}

/*
==============
DevGui_DrawMenuVertically
==============
*/
void DevGui_DrawMenuVertically(const DevMenuItem *menu, unsigned __int16 activeChild, int *origin)
{
}

/*
==============
DevGui_MenuItemDisabled
==============
*/
bool DevGui_MenuItemDisabled(const DevMenuItem *menu)
{
	return menu->childType == 1 && !DevGui_EditableMenuItem(menu);
}

/*
==============
DevGui_SubMenuTextWidth
==============
*/
int DevGui_SubMenuTextWidth()
{
	return R_TextWidth(" >", 0, cls.consoleFont);
}

/*
==============
DevGui_MaxChildMenuWidth
==============
*/
int DevGui_MaxChildMenuWidth(const DevMenuItem *menu)
{
}

/*
==============
DevGui_MenuItemWidth
==============
*/
int DevGui_MenuItemWidth(const DevMenuItem *menu)
{
}

/*
==============
DevGui_DrawMenuHorizontally
==============
*/
void DevGui_DrawMenuHorizontally(const DevMenuItem *menu, unsigned __int16 activeChild, int *origin)
{
}

/*
==============
DevGui_ChooseOrigin
==============
*/
void DevGui_ChooseOrigin(int *origin)
{
}

/*
==============
DevGui_DrawSliders
==============
*/
void DevGui_DrawSliders(const DevMenuItem *menu)
{
}

/*
==============
DevGui_DrawSliderPath
==============
*/
void DevGui_DrawSliderPath(int x, int y)
{
	char path[132] = { 0 };

	DevGui_GetSliderPath(devguiGlob.selectedMenu, path, 0);
	DevGui_DrawFont(x, y, (const unsigned __int8 *)&devgui_colorText->current, path, 1.0f, 1.0f);
}

/*
==============
DevGui_GetSliderPath
==============
*/
int DevGui_GetSliderPath(unsigned __int16 menuHandle, char *path, int pathLen)
{
}

/*
==============
DevGui_DrawDvarDescription
==============
*/
void DevGui_DrawDvarDescription(int x, int y, const dvar_t *dvar)
{
	if (dvar->description)
	{
		DevGui_DrawFont(x, y, (const unsigned __int8 *)&devgui_colorText->current, dvar->description, 1.0f, 1.0f);
	}
}

/*
==============
DevGui_DrawSingleSlider
==============
*/
void DevGui_DrawSingleSlider(
	int x,
	int y,
	int rowWidth,
	int rowHeight,
	float fraction,
	const unsigned __int8 *knobColor)
{
}

/*
==============
DevGui_DrawDvarValue
==============
*/
void DevGui_DrawDvarValue(int x, int y, const dvar_t *dvar)
{
}

/*
==============
DevGui_DvarRowCount
==============
*/
int DevGui_DvarRowCount(const dvar_t *dvar)
{
	switch (dvar->type)
	{
	case DVAR_TYPE_FLOAT_2:
		return 2;
	case DVAR_TYPE_FLOAT_3:
	case DVAR_TYPE_LINEAR_COLOR_RGB:
	case DVAR_TYPE_COLOR_XYZ:
		return 3;
	case DVAR_TYPE_FLOAT_4:
	case DVAR_TYPE_COLOR:
		return 4;
	default:
		return 1;
	}
}


/*
==============
DevGui_DrawBindNextKey
==============
*/
void DevGui_DrawBindNextKey()
{
}

/*
==============
DevGui_DrawGraph
==============
*/
void DevGui_DrawGraph(const DevMenuItem *menu, LocalClientNum_t localClientNum)
{
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
		0.0f,
		0.41999999f,
		0.0f,
		0.75f,
		DVAR_NOFLAG,
		"Color background for the devgui");
	devgui_colorText = _Dvar_RegisterColor(
		"devgui_colorText",
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		DVAR_NOFLAG,
		"Text color for the devgui");
	devgui_colorBgndSel = _Dvar_RegisterColor(
		"devgui_colorBgndSel",
		0.0f,
		0.69999999f,
		0.0f,
		0.75f,
		DVAR_NOFLAG,
		"Selection background color for the devgui");
	devgui_colorTextSel = _Dvar_RegisterColor(
		"devgui_colorTextSel",
		1.0f,
		1.0f,
		0.0f,
		1.0f,
		DVAR_NOFLAG,
		"Selection text color for the devgui");
	devgui_colorBgndGray = _Dvar_RegisterColor(
		"devgui_colorBgndGray",
		0.2f,
		0.2f,
		0.2f,
		0.89999998f,
		DVAR_NOFLAG,
		"Grayed out background color for the devgui");
	devgui_colorTextGray = _Dvar_RegisterColor(
		"devgui_colorTextGray",
		0.69999999f,
		0.69999999f,
		0.69999999f,
		1.0f,
		DVAR_NOFLAG,
		"Greyed out text color for the devgui");
	devgui_colorBgndGraySel = _Dvar_RegisterColor(
		"devgui_colorBgndGraySel",
		0.40000001f,
		0.40000001f,
		0.40000001f,
		0.89999998f,
		DVAR_NOFLAG,
		"Greyed out, selected background color for the devgui");
	devgui_colorTextGraySel = _Dvar_RegisterColor(
		"devgui_colorTextGraySel",
		1.0f,
		1.0f,
		0.0f,
		1.0f,
		DVAR_NOFLAG,
		"Greyed out, selected text color for the devgui");
	devgui_colorSliderBgnd = _Dvar_RegisterColor(
		"devgui_colorSliderBgnd",
		1.0f,
		1.0f,
		1.0f,
		0.75f,
		DVAR_NOFLAG,
		"Color slider background for the devgui");
	devgui_colorSliderKnob = _Dvar_RegisterColor(
		"devgui_colorSliderKnob",
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		DVAR_NOFLAG,
		"Knob color for the devgui");
	devgui_colorSliderKnobSel = _Dvar_RegisterColor(
		"devgui_colorSliderKnobSel",
		1.0f,
		1.0f,
		0.0f,
		1.0f,
		DVAR_NOFLAG,
		"Selected knob color for the devgui");
	devgui_bevelShade = _Dvar_RegisterFloat(
		"devgui_bevelShade",
		0.69999999f,
		0.0f,
		1.0f,
		DVAR_NOFLAG,
		"Bevel shade for the devgui");
	devgui_colorGraphKnotNormal = _Dvar_RegisterColor(
		"devgui_colorGraphKnotNormal",
		0.0f,
		1.0f,
		1.0f,
		0.69999999f,
		DVAR_NOFLAG,
		"Devgiu Color graph knot normal color");
	devgui_colorGraphKnotSelected = _Dvar_RegisterColor(
		"devgui_colorGraphKnotSelected",
		1.0f,
		0.0f,
		0.0f,
		0.69999999f,
		DVAR_NOFLAG,
		"Devgui color graph knot selected color");
	devgui_colorGraphKnotEditing = _Dvar_RegisterColor(
		"devgui_colorGraphKnotEditing",
		1.0f,
		0.0f,
		1.0f,
		1.0f,
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
DevGui_MoveSelectionHorizontally
==============
*/
int DevGui_MoveSelectionHorizontally()
{
}

/*
==============
DevGui_MoveLeft
==============
*/
int DevGui_MoveLeft()
{
}

/*
==============
DevGui_SelectPrevMenuItem
==============
*/
int DevGui_SelectPrevMenuItem()
{
}

/*
==============
DevGui_SelectTopLevelChild
==============
*/
void DevGui_SelectTopLevelChild()
{
}

/*
==============
DevGui_AdvanceChildNum
==============
*/
void DevGui_AdvanceChildNum(int numberToAdvance)
{
}

/*
==============
DevGui_MoveRight
==============
*/
int DevGui_MoveRight()
{
}

/*
==============
DevGui_SelectNextMenuItem
==============
*/
void DevGui_SelectNextMenuItem()
{
}

/*
==============
DevGui_MoveSelectionVertically
==============
*/
int DevGui_MoveSelectionVertically()
{
}

/*
==============
DevGui_MoveUp
==============
*/
int DevGui_MoveUp()
{
}

/*
==============
DevGui_MoveDown
==============
*/
int DevGui_MoveDown()
{
}

/*
==============
DevGui_Accept
==============
*/
void DevGui_Accept(LocalClientNum_t localClientNum)
{
}

/*
==============
DevGui_Reject
==============
*/
void DevGui_Reject()
{
}

/*
==============
DevGui_UpdateSelection
==============
*/
int DevGui_UpdateSelection()
{
}

/*
==============
DevGui_ScrollUp
==============
*/
int DevGui_ScrollUp()
{
}

/*
==============
DevGui_SelectedDvar
==============
*/
const dvar_t *DevGui_SelectedDvar()
{
}

/*
==============
DevGui_ScrollUpInternal
==============
*/
int DevGui_ScrollUpInternal()
{
}

/*
==============
DevGui_ScrollDown
==============
*/
int DevGui_ScrollDown()
{
}

/*
==============
DevGui_ScrollDownInternal
==============
*/
int DevGui_ScrollDownInternal()
{
}

/*
==============
DevGui_UpdateDvar
==============
*/
void DevGui_UpdateDvar(float deltaTime, bool channelLink, bool dvarReset)
{
}

/*
==============
DevGui_PickFloatScrollStep
==============
*/
double DevGui_PickFloatScrollStep(float min, float max)
{
}

/*
==============
DevGui_UpdateGraph
==============
*/
void DevGui_UpdateGraph(LocalClientNum_t localClientNum, float deltaTime)
{
}

/*
==============
DevGui_AddGraphKnot
==============
*/
void DevGui_AddGraphKnot(DevGraph *graph, LocalClientNum_t localClientNum)
{
}

/*
==============
DevGui_RemoveGraphKnot
==============
*/
void DevGui_RemoveGraphKnot(DevGraph *graph, LocalClientNum_t localClientNum)
{
}

