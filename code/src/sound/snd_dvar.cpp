#include "types.h"

const char *snd_draw3DNames[5] = { "Off", "Targets", "Names", "Verbose", "" };
const char *snd_speakerConfigurationStrings[32];

const dvar_t *snd_draw3D;
const dvar_t *snd_autosim_window;
const dvar_t *snd_max_ram_voice;
const dvar_t *snd_max_stream_voice;
const dvar_t *snd_trace_master;
const dvar_t *snd_trace_reverb;
const dvar_t *snd_trace_voice;
const dvar_t *snd_futz_blend;
const dvar_t *snd_ps3_vol_occlusion_attenuation_dry;
const dvar_t *snd_ps3_vol_occlusion_attenuation_wet;
const dvar_t *snd_speakerConfiguration;

/*
==============
SND_InitDvar
==============
*/
void SND_InitDvar()
{
	snd_draw3D = _Dvar_RegisterEnum("snd_draw3D", snd_draw3DNames, 0, 0x80u, "Draw the position and info of world sounds");
	snd_autosim_window = _Dvar_RegisterBool("snd_autosim_window", 1, 0x80u, "autosim window masking");
	snd_max_ram_voice = _Dvar_RegisterInt("snd_max_ram_voice", 58, 0, 58, 0x80u, "max ram voice count");
	snd_max_stream_voice = _Dvar_RegisterInt("snd_max_stream_voice", 10, 0, 10, 0x80u, "max stream voice count");
	snd_trace_master = _Dvar_RegisterBool("snd_trace_master", 0, 0x80u, "trace master dsp");
	snd_trace_reverb = _Dvar_RegisterBool("snd_trace_reverb", 0, 0x80u, "trace reverb dsp");
	snd_trace_voice = _Dvar_RegisterBool("snd_trace_voice", 0, 0x80u, "trace voice dsp");
	snd_futz_blend = _Dvar_RegisterFloat("snd_futz", 0.0, 0.0, 1.0, 0x80u, "futz");
	snd_ps3_vol_occlusion_attenuation_dry = _Dvar_RegisterFloat(
												"snd_ps3_vol_occlusion_attenuation_dry",
												-20.0,
												-80.0,
												0.0,
												0x80u,
												"maximum dry volume occlusion attenuation for PS3");
	snd_ps3_vol_occlusion_attenuation_wet = _Dvar_RegisterFloat(
												"snd_ps3_vol_occlusion_attenuation_wet",
												-10.0,
												-80.0,
												0.0,
												0x80u,
												"maximum wet volume occlusion attenuation for PS3");

	for (unsigned int i = 0; i < 4; ++i)
	{
		snd_speakerConfigurationStrings[i] = Snd_GetSpeakerConfig(i)->name;
	}

	snd_speakerConfigurationStrings[4] = 0;
	snd_speakerConfiguration = _Dvar_RegisterEnum(
								"snd_speakerConfiguration",
								snd_speakerConfigurationStrings,
								0,
								DVAR_ARCHIVE,
								"Speaker configuration");
}

