#include "types.h"
#include "vars.h"

char version_buf[128];

bool s_buildInfoParsed = 0;
int s_buildInfoVersion = NULL;
const char s_buildInfoName[128];


#define BUILD_NUMBER "12"
#define CHANGE_LIST_NUMBER 1468705
#define BUILD_MACHINE = "CODPCAB2 CEG";
#define BUILD_TIME = "Tue Dec 11 18:15:37 2012";//it's a custom way, this is just what the define would be. it's a mix of __DATE__ and __TIME__ with year on the end


#if defined(MULTIPLAYER)
#if defined(DEBUG)
#define BUILD_DISPLAY_NAME "Call of Duty Multiplayer - Debug"
#elif defined(RELEASE)
#define BUILD_DISPLAY_NAME "Call of Duty Multiplayer - Release"
#elif defined(PIXPROFILE)
#define BUILD_DISPLAY_NAME "Call of Duty Multiplayer - PixProfile"
#else
#define BUILD_DISPLAY_NAME "Call of Duty Multiplayer - Ship"
#endif
#else
#if defined(DEBUG)
#define BUILD_DISPLAY_NAME "Call of Duty Singleplayer - Debug"
#elif defined(RELEASE)
#define BUILD_DISPLAY_NAME "Call of Duty Singleplayer - Release"
#elif defined(PIXPROFILE)
#define BUILD_DISPLAY_NAME "Call of Duty Singleplayer - PixProfile"
#else
#define BUILD_DISPLAY_NAME "Call of Duty Singleplayer - Ship"
#endif
#endif


#if defined(MULTIPLAYER)
#if defined(DEBUG)
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Multiplayer - Debug"
#elif defined(RELEASE)
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Multiplayer - Release"
#elif defined(PIXPROFILE)
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Multiplayer - PixProfile"
#else
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Multiplayer - Ship"
#endif
#else
#if defined(DEBUG)
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Singleplayer - Debug"
#elif defined(RELEASE)
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Singleplayer - Release"
#elif defined(PIXPROFILE)
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Singleplayer - PixProfile"
#else
#define BUILD_DISPLAY_NAME_R "Call of Duty(R) Singleplayer - Ship"
#endif
#endif


#if defined(MULTIPLAYER)
#if defined(DEBUG)
#define BUILD_NAME "COD_T6_D MP";
#elif defined(RELEASE)
#define BUILD_NAME "COD_T6_R MP";
#elif defined(PIXPROFILE)
#define BUILD_NAME "COD_T6_P MP";
#else
#define BUILD_NAME "COD_T6_S MP";
#endif
#else
#if defined(DEBUG)
#define BUILD_NAME "COD_T6_D SP";
#elif defined(RELEASE)
#define BUILD_NAME "COD_T6_R SP";
#elif defined(PIXPROFILE)
#define BUILD_NAME "COD_T6_P SP";
#else
#define BUILD_NAME "COD_T6_S SP";
#endif
#endif


#define BASE_NAME "COD_T6"

#if defined(DEBUG)
#define BUILD_CONFIG "Debug";
#elif defined(RELEASE)
#define BUILD_CONFIG "Release";
#elif defined(PIXPROFILE)
#define BUILD_CONFIG "PixProfile";
#else
#define BUILD_CONFIG "Ship";
#endif


#if defined(MULTIPLAYER)
#define BUILD_GAME_MODE "Multiplayer";
#else
#define BUILD_GAME_MODE "Singleplayer";
#endif




#if defined(DEBUG) //might be xenon only
/*
==============
Com_GetBuildID
==============
*/
const char *Com_GetBuildID()
{
	sprintf(version_buf, "%s.%s.%d CL(%d) %s %s", "1", "0", BUILD_NUMBER, CHANGE_LIST_NUMBER, BUILD_MACHINE, BUILD_TIME);
	return version_buf;
}
#endif

/*
==============
Com_GetBuildVersion
==============
*/
const char *Com_GetBuildVersion()
{
#if defined(PC)
	if (CHANGE_LIST_NUMBER)
	{
		sprintf(version_buf, "%s.%s.%d CL(%d) %s %s", "1", "0", BUILD_NUMBER, CHANGE_LIST_NUMBER, BUILD_MACHINE, BUILD_TIME);
	}
	else
	{
		sprintf(version_buf, "%s.%s.%d %s %s", "1", "0", BUILD_NUMBER, BUILD_MACHINE, BUILD_TIME);
	}
#else // always a change-list on console builds.
	sprintf(version_buf, "%s.%s.%d CL(%d) %s %s", "1", "0", BUILD_NUMBER, CHANGE_LIST_NUMBER, BUILD_MACHINE, BUILD_TIME);
#endif
	
	return version_buf;
}

/*
==============
Com_GetBuildNumber
==============
*/
int Com_GetBuildNumber()
{
	return BUILD_NUMBER;
}

/*
==============
Com_GetBuildMachine
==============
*/
const char *Com_GetBuildMachine()
{
	return BUILD_MACHINE;
}

/*
==============
Com_GetBuildTime
==============
*/
const char *Com_GetBuildTime()
{
  return BUILD_TIME;
}

/*
==============
Com_GetBuildDisplayName
==============
*/
const char *Com_GetBuildDisplayName()
{
	return BUILD_DISPLAY_NAME;
}

/*
==============
Com_GetBuildDisplayNameR
==============
*/
const char *Com_GetBuildDisplayNameR()
{
	return BUILD_DISPLAY_NAME_R;
}

/*
==============
Com_GetBuildName
==============
*/
const char *Com_GetBuildName()
{
	return BUILD_NAME;
}

/*
==============
Com_GetBuildBaseName
==============
*/
const char *Com_GetBuildBaseName()
{
	return BASE_NAME;
}

/*
==============
Com_GetBuildConfig
==============
*/
const char *Com_GetBuildConfig()
{
	return BUILD_CONFIG;
}

/*
==============
Com_GetBuildMode
==============
*/
const char *Com_GetBuildMode()
{
	return BUILD_GAME_MODE;
}

/*
==============
Com_GetChangelist
==============
*/
int Com_GetChangelist()
{
	return CHANGE_LIST_NUMBER;
}

/*
==============
Com_GetBuildInfoName
==============
*/
const char *Com_GetBuildInfoName()
{
	if (!s_buildInfoParsed)
	{
		s_buildInfoParsed = 1;
		s_buildInfoVersion = 0;

		strcpy(s_buildInfoName, "unknown");
	}

	return s_buildInfoName;
}

/*
==============
Com_GetBuildInfoVersion
==============
*/
int Com_GetBuildInfoVersion()
{
	if (!s_buildInfoParsed)
	{
		s_buildInfoParsed = 1;
		s_buildInfoVersion = 0;

		strcpy(s_buildInfoName, "unknown");
		return FALSE;
	}

	return s_buildInfoVersion;
}

