#include "types.h"

/*
==============
Steam_CreateSteamAppIdFile
==============
*/
void Steam_CreateSteamAppIdFile()
{
	char buffer[32] = {0};

	FILE *file = fopen("steam_appid.txt", "r");
	if (!file || !fgets(buffer, sizeof(buffer), file) || strncmp(buffer, "202990", 6) != NULL)
	{
		if (file)
		{
			fclose(file);
		}

		file = fopen("steam_appid.txt", "w");
		if (file)
		{
			fprintf(file, "202990");
			fclose(file);
		}
	}
	else
	{
		fclose(file);
	}
}

