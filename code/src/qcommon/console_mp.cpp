#include "types.h"

const dvar_t* band_dedicated;

/*
==============
Live_GetNecessaryBandwidth
==============
*/
int Live_GetNecessaryBandwidth()
{
	return band_dedicated->current.integer;
}

/*
==============
Live_HowManyPlayersCanWeHost
==============
*/
int Live_HowManyPlayersCanWeHost()
{
	return 18;
}

