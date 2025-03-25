#include "types.h"

/*
==============
SD_SourceInitStream
==============
*/
void SD_SourceInitStream(
    sd_source *source,
    const char *name,
    const SndAssetBankEntry *entry,
    int fid,
    const char *primeData,
    unsigned int primeSize)
{
    assertMsg(
        "entry->channelCount == 1 || entry->channelCount == 2",
        "(entry->channelCount) = %i",
        entry->channelCount
    );

    source->stream = SD_StreamAllocate(name, entry, fid, primeData, primeSize);

    if (source->stream)
    {
        source->primed = 0;
        source->error = 0;
        source->eos = 0;
        source->looping = (entry->looping != 0);
    }
    else
    {
        source->error = 1;
        source->primed = 1;
        source->eos = 1;
    }
}

