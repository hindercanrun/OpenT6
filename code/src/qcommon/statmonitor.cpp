#include "types.h"

statmonitor_s stats[14];
int statCount = nullptr;

/*
==============
StatMon_GetStatsArray
==============
*/
void StatMon_GetStatsArray(const statmonitor_s **array, int *count)
{
	*array = stats;
	*count = statCount;
}

/*
==============
StatMon_Reset
==============
*/
void StatMon_Reset()
{
	memset((unsigned __int8 *)stats, 0, sizeof(stats));
	statCount = 0;
}

