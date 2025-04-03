#include "types.h"

/*
==============
Com_GetPrimaryLight
==============
*/
ComPrimaryLight *Com_GetPrimaryLight(unsigned int primaryLightIndex)
{
	assert(comWorld.isInUse);
	assert(
		(unsigned)(primaryLightIndex) < (unsigned)(comWorld.primaryLightCount),
		"primaryLightIndex doesn't index comWorld.primaryLightCount\n\t%i not in [0, %i)",
		primaryLightIndex,
		comWorld.primaryLightCount);
	return &comWorld.primaryLights[primaryLightIndex];
}

