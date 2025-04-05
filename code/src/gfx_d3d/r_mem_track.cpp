#include "types.h"

/*
==============
R_Track_Init
==============
*/
void R_Track_Init()
{
	g_mem_track_filename = "r_bsp_load_obj";
	TRACK_r_bsp_load_obj();

	g_mem_track_filename = "rb_sky";
	TRACK_rb_sky();

	g_mem_track_filename = "r_buffers";
	TRACK_r_buffers();

	g_mem_track_filename = "r_debug";
	TRACK_r_debug();

	g_mem_track_filename = "r_dpvs";
	TRACK_r_dpvs();

	g_mem_track_filename = "r_fog";
	//BG_EvalVehicleName();

	g_mem_track_filename = "r_font";
	TRACK_r_font();

	g_mem_track_filename = "r_image";
	TRACK_r_image();

	g_mem_track_filename = "r_image_wavelet";
	TRACK_r_image_wavelet();

	g_mem_track_filename = "r_init";
	TRACK_r_init();

	g_mem_track_filename = "r_marks";
	//BG_EvalVehicleName();

	g_mem_track_filename = "r_material";
	TRACK_r_material();

	g_mem_track_filename = "r_model";
	TRACK_r_model();

	g_mem_track_filename = "r_rendercmds";
	TRACK_r_rendercmds();

	g_mem_track_filename = "r_screenshot";
	TRACK_r_screenshot();

	g_mem_track_filename = "r_staticmodel";
	//BG_EvalVehicleName();

	g_mem_track_filename = "r_utils";
	//BG_EvalVehicleName();

	g_mem_track_filename = "r_xsurface";
	//BG_EvalVehicleName();

	g_mem_track_filename = "r_light";
	//BG_EvalVehicleName();

	g_mem_track_filename = "rb_debug";
	TRACK_rb_debug();

	g_mem_track_filename = "rb_backend";
	TRACK_rb_backend();

	g_mem_track_filename = "rb_shade";
	//BG_EvalVehicleName();

	g_mem_track_filename = "rb_showcollision";
	TRACK_rb_showcollision();

	g_mem_track_filename = "rb_state";
	TRACK_rb_state();

	g_mem_track_filename = "rb_stats";
	//BG_EvalVehicleName();

	g_mem_track_filename = "rb_sunshadow";
	TRACK_rb_sunshadow();

	g_mem_track_filename = "rb_tess";
	//BG_EvalVehicleName();
}

