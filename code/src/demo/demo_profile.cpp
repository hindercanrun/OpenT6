#include "types.h"

/*
==============
Demo_GetAnalyzePrintDataType
==============
*/
bool Demo_GetAnalyzePrintDataType(int fieldBit)
{
	static bool result;

	switch (fieldBit) // holy case
	{
	case -107:
	case -106:
	case -105:
	case -104:
	case -103:
	case -102:
	case -101:
	case -100:
	case -99:
	case -92:
	case -91:
	case -90:
	case -89:
	case -88:
	case -87:
	case -86:
	case -81:
	case -80:
	case -77:
	case -76:
	case -75:
	case -74:
	case -73:
	case -72:
	case -66:
	case -65:
	case -64:
	case -63:
	case -62:
	case -61:
	case 0:
		result = 0;
		break;
	default:
		result = 1;
		break;
	}

	return result;
}

/*
==============
Demo_RecordProfileData
==============
*/
void Demo_RecordProfileData(demoProfileData profileDataType, int size)
{
	s_demoProfile.memUsed[profileDataType] += size;
	++s_demoProfile.count[profileDataType];
}

/*
==============
Demo_PrintProfileData
==============
*/
void Demo_PrintProfileData()
{
	Demo_Printf(2, "Total Demo Filesize: %d bytes\n", demo.loadedTime);
	Demo_Printf(2, "--------------------Demo Profile--------------------\n");

	for (int i = 0; i < 8; ++i)
	{
		Demo_Printf(2, "%s : Count: %d Size: ", demo_profile_enum_string_6[i], s_demoProfile.count[i]);

		if (s_demoProfile.memUsed[i] < 1024)
		{
			Demo_Printf(2, "%d Bytes\n", s_demoProfile.memUsed[i]);
		}
		else
		{
			Demo_Printf(2, "%.2f KB\n", (s_demoProfile.memUsed[i] * 0.0009765625));
		}
	}

	Demo_Printf(2, "-----------------End of Demo Profile-----------------\n");
}

/*
==============
Demo_DrawDebugInformation
==============
*/
void Demo_DrawDebugInformation(LocalClientNum_t localClientNum)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
Demo_DrawProfile
==============
*/
void Demo_DrawProfile()
{
	UNIMPLEMENTED(__FUNCTION__);
}

