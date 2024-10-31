#include "types.h"

cmd_function_s DevGui_Toggle_VAR;

/*
==============
DevGui_InputInit
==============
*/
void DevGui_InputInit (void) {
	Cmd_AddCommandInternal ("devgui",DevGui_Toggle,&DevGui_Toggle_VAR);
}

/*
==============
DevGui_InputShutdown
==============
*/
void DevGui_InputShutdown (void) {
	Cmd_RemoveCommand ("devgui");
}


/*
==============
DevGui_SelectGamepad
==============
*/
void DevGui_SelectGamepad( ControllerIndex_t gamePadIndex ) {
	s_input.selectedGamePadIndex = gamePadIndex;
}

/*
==============
DevGui_MouseEvent
==============
*/
void DevGui_MouseEvent( int dx, int dy ) {
	s_input.mousePos[0] = (float)dx;
	s_input.mousePos[1] = (float)dy;
}

/*
==============
DevGui_IsButtonDown
==============
*/
bool DevGui_IsButtonDown(DevGuiInputButton button)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

