#include "types.h"

static cmd_function_s DevGui_Toggle_VAR;

/*
==============
DevGui_InputInit
==============
*/
void DevGui_InputInit()
{
	Cmd_AddCommandInternal("devgui", DevGui_Toggle, &DevGui_Toggle_VAR);
}

/*
==============
DevGui_InputShutdown
==============
*/
void DevGui_InputShutdown()
{
	Cmd_RemoveCommand("devgui");
}

/*
==============
DevGui_SelectGamepad
==============
*/
void DevGui_SelectGamepad(ControllerIndex_t gamePadIndex)
{
	s_input.selectedGamePadIndex = gamePadIndex;
}

/*
==============
DevGui_InputUpdate
==============
*/
char DevGui_InputUpdate(localClientNum_t localClientNum, float deltaTime)
{
}

/*
==============
DevGui_MouseEvent
==============
*/
void DevGui_MouseEvent(int dx, int dy)
{
	s_input.mousePos[0] = (float)dx;
	s_input.mousePos[1] = (float)dy;
}

/*
==============
DevGui_GetMenuScroll
==============
*/
__int16 DevGui_GetMenuScroll(DevGuiInputAxis axis)
{
	return s_input.menuScroll[axis];
}

/*
==============
DevGui_UpdateIntScroll
==============
*/
__int64 DevGui_UpdateIntScroll(float deltaTime, __int64 value, __int64 min, __int64 max, DevGuiInputAxis axis)
{
}

/*
==============
DevGui_UpdateFloatScroll
==============
*/
double DevGui_UpdateFloatScroll(
	float deltaTime,
	float value,
	float min,
	float max,
	float step,
	DevGuiInputAxis axis)
{
}

/*
==============
DevGui_IsButtonDown
==============
*/
bool DevGui_IsButtonDown(DevGuiInputButton button)
{
	return s_input.buttonDown[button];
}

/*
==============
DevGui_IsButtonPressed
==============
*/
bool DevGui_IsButtonPressed(DevGuiInputButton button)
{
	return s_input.buttonDown[button] && !s_input.prevButtonDown[button];
}

/*
==============
DevGui_IsButtonReleased
==============
*/
bool DevGui_IsButtonReleased(DevGuiInputButton button)
{
	return !s_input.buttonDown[button] && s_input.prevButtonDown[button];
}

/*
==============
DevGui_UpdateScrollInputs
==============
*/
void DevGui_UpdateScrollInputs(int localClientNum)
{
}

/*
==============
DevGui_UpdateScrollStates
==============
*/
void DevGui_UpdateScrollStates(float deltaTime, DevGuiInputState *states, float *axis, float *times)
{
}

/*
==============
DevGui_UpdateMenuScroll
==============
*/
void DevGui_UpdateMenuScroll(float deltaTime)
{
}

/*
==============
DevGui_InputUpdateGamepad
==============
*/
char DevGui_InputUpdateGamepad()
{
}

/*
==============
DevGui_InputUpdateMouse
==============
*/
void DevGui_InputUpdateMouse()
{
}