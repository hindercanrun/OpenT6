#include "types.h"

/*
==============
SND_ChecksumToString
==============
*/
void SND_ChecksumToString(const unsigned __int8 *checksum, char *string)
{
	*string = 0;
	for (int i = 0; i < 16; ++i)
	{
		strcat(string, va("%02x", checksum[i]));
	}
}

/*
==============
SND_AssetBankValidateHeader
==============
*/
char SND_AssetBankValidateHeader(
    const char *filename,
    const SndAssetBankHeader *header,
    int64_t size,
    const uint8_t *checksum)
{
	if (header->magic == -559038737)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' was written incompletely.\n", filename);
		return FALSE;
	}

	if (header->magic != 592991538)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' had bad magic (corrupt).\n", filename);
		return FALSE;
	}

	if (header->version != 14)
	{
		Com_PrintError(
			CON_CHANNEL_ERROR,
			"ERROR: Sound asset bank '%s' had bad version %d should be %d.\n",
			filename,
			header->version,
			14);
		return FALSE;
	}

	if (header->entrySize != 20)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' had bad entry size.\n", filename);
		return FALSE;
	}

	if (size && header->fileSize != size)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' was truncated.\n", filename);
		return FALSE;
	}

	if (header->entryCount && (header->entryOffset >= size || header->entryOffset == NULL))
	{
		Com_PrintError(
			CON_CHANNEL_ERROR,
			"ERROR: Sound asset bank '%s' had invalid layout offset. ofs %d siz %lld\n",
			filename,
			(int)header->entryOffset,
			size);
		return FALSE;
	}

	if (size && header->checksumOffset > size)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' had invalid checksum offset.\n", filename);
		return FALSE;
	}

	if (!checksum)
	{
		return TRUE;
	}

	for (int i = 0; i < 16; i++)
	{
		if (checksum[i] != header->checksumChecksum[i])
		{
			Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' did not match link time checksum.\n", filename);

			char checksumString[36];
			SND_ChecksumToString(checksum, checksumString);
			Com_PrintError(CON_CHANNEL_ERROR, "ERROR:   link checksum: %s\n", checksumString);

			SND_ChecksumToString(header->checksumChecksum, checksumString);
			Com_PrintError(CON_CHANNEL_ERROR, "ERROR:   game checksum: %s\n", checksumString);

			return FALSE;
		}
	}

	return TRUE;
}

/*
==============
SND_AssetBankValidateEntry
==============
*/
char SND_AssetBankValidateEntry(
	const char *name,
	const SndAssetBankHeader *header,
	const SndAssetBankEntry *entry)
{
	assert(entry->id);
	assert(entry->offset);
	assert(entry->size);

	uint64_t fileSize = header->fileSize;
	if (entry->size >= fileSize)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' had an invalid entry size.\n", name);
		return FALSE;
	}

	if (entry->offset >= fileSize)
	{
		Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound asset bank '%s' had an invalid entry offset.\n", name);
		return FALSE;
	}

	return TRUE;
}

/*
==============
SND_EntryCompare
==============
*/
int SND_EntryCompare(const void* va, const void* vb)
{
	if (va <= vb)
	{
		return -(va < vb);
	}

	return TRUE;
}

/*
==============
SND_AssetBankFindEntry
==============
*/
char SND_AssetBankFindEntry(unsigned int id, SndAssetBankEntry *entries, unsigned int entryCount, SndAssetBankEntry **entry)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
SND_AssetBankGetFrameRate
==============
*/
unsigned int SND_AssetBankGetFrameRate(const SndAssetBankEntry *entry)
{
	assert(entry);

	static unsigned int result;
	switch (entry->frameRateIndex)
	{
	case 0:
		result = 8000;
		break;
	case 1:
		result = 12000;
		break;
	case 2:
		result = 16000;
		break;
	case 3:
		result = 24000;
		break;
	case 4:
		result = 32000;
		break;
	case 5:
		result = 44100;
		break;
	case 6:
		result = 48000;
		break;
	case 7:
		result = 96000;
		break;
	case 8:
		result = 192000;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}

/*
==============
SND_AssetBankGetChannelCount
==============
*/
unsigned int SND_AssetBankGetChannelCount(const SndAssetBankEntry *entry)
{
	return entry->channelCount;
}

/*
==============
SND_AssetBankGetLooping
==============
*/
BOOL SND_AssetBankGetLooping(const SndAssetBankEntry *entry)
{
	return entry->looping != FALSE;
}

/*
==============
SND_AssetBankGetFrameCount
==============
*/
unsigned int SND_AssetBankGetFrameCount(const SndAssetBankEntry *entry)
{
	return entry->frameCount;
}

/*
==============
SND_AssetBankGetLengthMs
==============
*/
unsigned int SND_AssetBankGetLengthMs(const SndAssetBankEntry *entry)
{
	assert(entry);

	unsigned int frameCount = entry->frameCount;
	return 1000 * frameCount / SND_AssetBankGetFrameRate(entry);
}

