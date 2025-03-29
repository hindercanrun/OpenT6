#include "types.h"

/*
==============
PIXBeginNamedEvent
==============
*/
inline void PIXBeginNamedEvent(int Color, const char *Name, ...)
{
	if (Sys_IsRenderThread())
	{
		wchar_t w[256] = { 0 };
		MultiByteToWideChar(0, 0, Name, -1, w, 256);
		D3DPERF_BeginEvent(Color, w);
	}
}

/*
==============
PIXSetMarker
==============
*/
inline void PIXSetMarker(int Color, const char *Name, ...)
{
	if (Sys_IsRenderThread())
	{
		wchar_t w[256] = { 0 };
		MultiByteToWideChar(0, 0, Name, -1, w, 256);
		D3DPERF_SetMarker(Color, w);
	}
}

