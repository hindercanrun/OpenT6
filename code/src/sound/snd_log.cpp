#include "types.h"

/*
==============
SND_LogMissingAliasId
==============
*/
void SND_LogMissingAliasId(unsigned int hash)
{
	assert(hash != NULL);

	Sys_EnterCriticalSection(CRITSECT_SOUND_LOOKUP_CACHE);

	static char reverse[48];
	SND_DevhostMissingAlias(hash);
	if (!SND_LogSkip(hash, 0x80u, g_snd.logSkipMissingHash, g_snd.logSkipMissingTimestamp))
	{
		SND_LogLookupAlias(hash, reverse);

		if (reverse[0])
		{
			BB_Print(INVALID_CONTROLLER_PORT, "sound_string", "string %s", reverse);
		}
	}

	Sys_LeaveCriticalSection(CRITSECT_SOUND_LOOKUP_CACHE);
}

