#include "types.h"

const char *g_mem_track_filename;

/*
==============
UI_track_init
==============
*/
void UI_track_init()
{
	g_mem_track_filename = "ui_main";
	TRACK_ui_main();

	g_mem_track_filename = "ui_shared";
	TRACK_ui_shared();

	g_mem_track_filename = "ui_utils";
	TRACK_ui_utils();

	//g_mem_track_filename = "ui_atoms";
	//BG_EvalVehicleName();

	g_mem_track_filename = "ui_shared_obj";
	TRACK_ui_shared_obj();
}

