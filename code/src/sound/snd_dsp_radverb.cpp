#include "types.h"

/*
==============
SND_RvParamsDefault
==============
*/
void SND_RvParamsDefault(SndRvParams *params)
{
    params->smoothing = 0.5f;
    params->diffusion = 0.5f;

    params->earlySize = 1.0f;
    params->lateSize = 1.0f;

    params->dryGain = 0.0f;
    params->earlyTime = 0.8f;
    params->lateTime = 0.8f;

    params->earlyGain = 1.0f;
    params->earlyLpf = 0.0f;
    params->lateGain = 1.0f;
    params->lateLpf = 0.0f;
    params->returnGain = 1.0f;

    params->inputLpf = 0.0f;
    params->dampLpf = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        params->wallReflect[i] = 0.5f;
    }

    params->frameRate = 48000.0f;
    params->delayMatrix = 0;
    params->returnHighpass = 0.0f;
}


