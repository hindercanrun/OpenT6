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
	DevGui_InputUpdateGamepad(localClientNum);
	DevGui_InputUpdateMouse();

	for (int butIndex = 0; butIndex < 13; ++butIndex )
	{
		s_input.prevButtonDown[butIndex] = s_input.buttonDown[butIndex];

		if (s_input.gamePadIndex >= 0)
		{
			s_input.buttonDown[butIndex] = GPad_GetButton(s_input.gamePadIndex, s_butMapsGamepad[butIndex]) > 0.0;
		}

		s_input.buttonDown[butIndex] = Key_IsDown(localClientNum, s_butMapsKey[butIndex]) != 0;
	}

	DevGui_UpdateScrollInputs(localClientNum);
	DevGui_UpdateScrollStates(deltaTime, s_input.digitalStates, s_input.digitalAxis, s_input.digitalTimes);

	if (s_input.gamePadIndex >= 0)
	{
		DevGui_UpdateScrollStates(deltaTime, s_input.analogStates, s_input.analogAxis, s_input.analogTimes);
	}

	DevGui_UpdateMenuScroll(deltaTime);
	CL_ClearKeys(localClientNum);

	return 1;
}

/*
==============
DevGui_UpdateScrollInputs
==============
*/
void DevGui_UpdateScrollInputs(localClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_UpdateScrollStates
==============
*/
void DevGui_UpdateScrollStates(float deltaTime, DevGuiInputState *states, float *axis, float *times)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_UpdateMenuScroll
==============
*/
void DevGui_UpdateMenuScroll(float deltaTime)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DevGui_InputUpdateGamepad
==============
*/
char DevGui_InputUpdateGamepad()
{
	s_input.gamePadIndex = s_input.selectedGamePadIndex;

	if (s_input.selectedGamePadIndex >= 0 && GPad_IsActive(s_input.gamePadIndex))
	{
		s_input.sliderScrollTime = 10.0f;
		s_input.sliderScrollMaxTimeStep = 0.1;
		return 1;
	}
	else
	{
		s_input.gamePadIndex = -1;
		return 0;
	}
}

/*
==============
DevGui_InputUpdateMouse
==============
*/
void DevGui_InputUpdateMouse()
{
	s_input.sliderScrollTime = 100.0f;
	s_input.sliderScrollMaxTimeStep = 0.30000001;//weird
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
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
DevGui_UpdateFloatScroll
==============
*/
double DevGui_UpdateFloatScroll(float deltaTime, float value, float min, float max, float step, DevGuiInputAxis axis)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
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
