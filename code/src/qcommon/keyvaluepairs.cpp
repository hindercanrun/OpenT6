#include "types.h"

/*
==============
KeyValuePairs_GetNextValue
==============
*/
char KeyValuePairs_GetNextValue(const char *key, const char *namespaceKey, const char **outValue)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
KeyValuePairs_Add
==============
*/
void KeyValuePairs_Add(KeyValuePairs *kvp, int zoneIndex)
{
	assertMsg((unsigned)(zoneIndex) < (unsigned)((sizeof( s_keyValuePairs ) / (sizeof( s_keyValuePairs[0] ) * (sizeof( s_keyValuePairs ) != 4
		|| sizeof( s_keyValuePairs[0] ) <= 4)))),
		"zoneIndex doesn't index ARRAY_COUNT( s_keyValuePairs )\n\t%i not in [0, %i)",
		zoneIndex,
		65);

	if (s_keyValuePairs[zoneIndex])
	{
		assert(s_keyValuePairs[zoneIndex] == 0);

		s_keyValuePairs[zoneIndex] = kvp;
		s_lastLoadedZoneIndex = zoneIndex;
	}
	else
	{
		s_keyValuePairs[zoneIndex] = kvp;
		s_lastLoadedZoneIndex = zoneIndex;
	}
}

/*
==============
KeyValuePairs_Remove
==============
*/
void KeyValuePairs_Remove(KeyValuePairs *kvp)
{
	int v1 = 0;
	while (s_keyValuePairs[v1] != kvp)
	{
		if (++v1 >= 0x41)
		{
			assert("KeyValuePair already removed, or was never added");
			return;
		}
	}

	if (v1 == s_lastLoadedZoneIndex)
	{
		s_lastLoadedZoneIndex = -1;
	}
	s_keyValuePairs[v1] = 0;
}

