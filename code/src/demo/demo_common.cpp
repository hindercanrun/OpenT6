#include "types.h"

/*
==============
Demo_RegisterDvars
==============
*/
void Demo_RegisterDvars()
{
	demo_enabled = _Dvar_RegisterBool("demo_enabled",
						TRUE,
						DVAR_NOFLAG,
						"Used to turn the system on/off.");
	demo_recordBasicTraining = _Dvar_RegisterBool(
									"demo_recordBasicTraining",
									0,
									0,
									"Used to turn the basic training recording on/off.");
	demo_recordPrivateMatch = _Dvar_RegisterBool(
								"demo_recordPrivateMatch",
								0,
								0,
								"Used to turn the private match recording on/off.");
	demo_filesizeLimit = _Dvar_RegisterFloat(
							"demo_filesizeLimit",
							10.0,
							0.1,
							3.4028235e38,
							0,
							"The maximum filesize (in MB) of the demos which we support.");
	demo_debug = _Dvar_RegisterInt("demo_debug", 0, 0, 0x7FFF, 0, "Debug info for the Server Snapshot Demo system");
	demo_drawdebuginformation = _Dvar_RegisterInt(
									"demo_drawdebuginformation",
									0,
									0,
									3,
									0,
									"Used to draw debug information.");
	demo_errortitle = _Dvar_RegisterString("demo_errortitle", "", 0x40u, "Most recent demo error's title.");
	demo_errormessage = _Dvar_RegisterString(
							"demo_errormessage",
							"",
							0x40u,
							"Most recent demo error's message.");
	demo_client = _Dvar_RegisterInt("demo_client", 0, 0, 32, 0, "Current viewing player");
	demo_recordingrate = _Dvar_RegisterInt(
							"demo_recordingrate",
							100,
							50,
							0x7FFFFFFF,
							0,
							"Used to tweak the rate(in msec) at which we write a super snapshot");
	demo_keyframerate = _Dvar_RegisterInt(
							"demo_keyframerate",
							10,
							1,
							0x7FFFFFFF,
							0,
							"Used to specify the rate(in sec) at which we generate a keyframe during playback.");
	demo_pause = _Dvar_RegisterBool("demo_pause", 0, 0, "Used to pause a demo playback.");
	demo_usefilesystem = _Dvar_RegisterBool("demo_usefilesystem", 0, 0, "Used to turn HDD write ON or OFF.");
	demo_save_smp = _Dvar_RegisterBool("demo_save_smp", 0, 0, "Used to toggle threaded save for the demo system.");
	demo_timescale = _Dvar_RegisterFloat(
						"demo_timescale",
						1.0,
						0.001,
						4.0,
						0,
						"The rate at which we want to scale time. For slo-mo it will be time/rate, fast mo. it will be time * rate");
	demo_timeScaleRate = _Dvar_RegisterFloat(
							"demo_timeScaleRate",
							4.0,
							1.0,
							4.0,
							0,
							"The rate at which we want to scale time. For slo-mo it will be time/rate, fast mo. it will be time * rate");
	demo_cmdNum = _Dvar_RegisterInt(
					"demo_cmdnum",
					0,
					0,
					0x7FFFFFFF,
					0,
					"The number of the command sent from console/ingame menu. ");
	demo_bookmarkEventThresholdTime = _Dvar_RegisterFloat(
										"demo_bookmarkEventThresholdTime",
										2.0,
										1.0,
										4.0,
										0,
										"The time duration for which we want to show the bookmark event image in the demo timeline.");
	demo_controllerConfig = _Dvar_RegisterInt(
								"demo_controllerConfig",
								0,
								0,
								2,
								0,
								"The number of the command sent from console/ingame menu. ");
	demo_defaultSegmentTag = _Dvar_RegisterString(
								"demo_defaultSegmentTag",
								&toastPopupTitle,
								0,
								"The text to be displayed as the default tag for the segment in the UI (save prompt).");
	demo_selectedSegmentIndex = _Dvar_RegisterInt(
									"demo_selectedSegmentIndex",
									0,
									0,
									0x7FFFFFFF,
									0,
									"Used in the Manage Segments UI. This will be used to know which segment index we have selected.");
	demo_desiredTime = _Dvar_RegisterInt(
							"demo_desiredtime",
							-1,
							-1,
							0x7FFFFFFF,
							0,
							"Used to force demo to a certain time");
	demo_desiredClient = _Dvar_RegisterInt(
							"demo_desiredclient",
							-1,
							-1,
							0x7FFFFFFF,
							0,
							"Used to force demo to a certain client");
	demo_packetsPerSecondMin = _Dvar_RegisterInt(
									"demo_packetsPerSecondMin",
									2,
									0,
									0x7FFFFFFF,
									0,
									"Min amount of packets to send per second before throttling.");
	demo_bytesPerSecondMin = _Dvar_RegisterInt(
								"demo_bytesPerSecondMin",
								2048,
								0,
								0x7FFFFFFF,
								0,
								"Min amount of bytes to send per second before throttling.");
	demo_packetsPerSecondMax = _Dvar_RegisterInt(
									"demo_packetsPerSecondMax",
									10,
									0,
									0x7FFFFFFF,
									0,
									"Max amount of packets to send per second before throttling.");
	demo_bytesPerSecondMax = _Dvar_RegisterInt(
								"demo_bytesPerSecondMax",
								0x2000,
								0,
								0x7FFFFFFF,
								0,
								"Max amount of bytes to send per second before throttling.");
}

/*
==============
Demo_SwitchPlayer_f
==============
*/
void Demo_SwitchPlayer_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SaveAndUploadClip_f
==============
*/
void Demo_SaveAndUploadClip_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SwitchTransition_f
==============
*/
void Demo_SwitchTransition_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_Keyboard_f
==============
*/
void Demo_Keyboard_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_DownloadAndPlay_f
==============
*/
void Demo_DownloadAndPlay_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_CompareDollyCamMarkersBasedOnTime
==============
*/
int Demo_CompareDollyCamMarkersBasedOnTime(const void *marker1, const void *marker2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_CompareDollyCamMarkersBasedOnKeyframeBufferStart
==============
*/
int Demo_CompareDollyCamMarkersBasedOnKeyframeBufferStart(const void *marker1, const void *marker2)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_ClearRenderFlag_f
==============
*/
void Demo_ClearRenderFlag_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_AbortFileshareDownload_f
==============
*/
void Demo_AbortFileshareDownload_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_IsEnabled
==============
*/
bool Demo_IsEnabled()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_SetDemoState
==============
*/
void Demo_SetDemoState(demoState state)
{
	demo.state = state;
}

/*
==============
Demo_GetDemoState
==============
*/
demoState Demo_GetDemoState()
{
	return demo.state;
}

/*
==============
Demo_IsIdle
==============
*/
BOOL Demo_IsIdle()
{
	return demo.state == DEMO_STATE_IDLE;
}

/*
==============
Demo_IsRecording
==============
*/
BOOL Demo_IsRecording()
{
	return demo.state == DEMO_STATE_RECORDING;
}

/*
==============
Demo_IsPlaying
==============
*/
BOOL Demo_IsPlaying()
{
	return demo.state == DEMO_STATE_PLAYING;
}

/*
==============
Demo_GetDemoName
==============
*/
demoMain *Demo_GetDemoName()
{
	return &demo;
}

/*
==============
Demo_GetTotalSize
==============
*/
int Demo_GetTotalSize()
{
	return demo.loadedTime;
}

/*
==============
Demo_Printf
==============
*/
void Demo_Printf(int channel, const char *fmt, ...)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_Init
==============
*/
void Demo_Init()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_InitWrite
==============
*/
bool Demo_InitWrite()
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_Frame
==============
*/
void Demo_Frame(int msec, int scaledMsec)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_End
==============
*/
void Demo_End()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_MatchEnded
==============
*/
void __cdecl Demo_MatchEnded()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_WriteToSpawnDebugBuffer
==============
*/
char Demo_WriteToSpawnDebugBuffer(unsigned __int8 *buf, int bufSize)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
Demo_Play_f
==============
*/
void Demo_Play_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_Stop_f
==============
*/
void Demo_Stop_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_Forward_f
==============
*/
void Demo_Forward_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_Back_f
==============
*/
void Demo_Back_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_JumpToStart_f
==============
*/
void Demo_JumpToStart_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_StartClipRecord_f
==============
*/
void Demo_StartClipRecord_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_PreviewClip_f
==============
*/
void Demo_PreviewClip_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_DeleteClip_f
==============
*/
void Demo_DeleteClip_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SaveSegment_f
==============
*/
void Demo_SaveSegment_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_MoveSegment_f
==============
*/
void Demo_MoveSegment_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_DeleteSegment_f
==============
*/
void Demo_DeleteSegment_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_PreviewSegment_f
==============
*/
void Demo_PreviewSegment_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_MergeSegments_f
==============
*/
void Demo_MergeSegments_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_Screenshot_f
==============
*/
void Demo_Screenshot_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SaveScreenshot_f
==============
*/
void Demo_SaveScreenshot_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_CaptureSegmentThumbnail_f
==============
*/
void Demo_CaptureSegmentThumbnail_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_RegenerateHighlightReel_f
==============
*/
void Demo_RegenerateHighlightReel_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_RebuildHighlightReelTimeline_f
==============
*/
void Demo_RebuildHighlightReelTimeline_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SwitchControls_f
==============
*/
void Demo_SwitchControls_f(const char *a1)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_AddDollyCamMarker_f
==============
*/
void Demo_AddDollyCamMarker_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_RemoveDollyCamMarker_f
==============
*/
void Demo_RemoveDollyCamMarker_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SwitchDollyCamMarker_f
==============
*/
void Demo_SwitchDollyCamMarker_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_RepositionDollyCamMarker_f
==============
*/
void Demo_RepositionDollyCamMarker_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_UpdateDollyCamMarkerParameters_f
==============
*/
void Demo_UpdateDollyCamMarkerParameters_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_SetLagFlag_f
==============
*/
void Demo_SetLagFlag_f()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_RegisterCommands
==============
*/
void Demo_RegisterCommands()
{
	UNIMPLEMENTED(__FUNCTION__);
}

