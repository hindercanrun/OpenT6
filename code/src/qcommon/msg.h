#include "types.h"

#if T6
/*
==============
SetField
==============
*/
void SetField(int *i, int size, int value)
{
	UNIMPLEMENTED(__FUNCTION__);
}
#endif

/*
==============
MSG_GetField
==============
*/
int MSG_GetField(const int *i, int size)
{
	switch (size)
	{
	case 1:
		return *(char *)i;
	case 2:
		return *(__int16 *)i;
	case 4:
		return *i;
	}

	assertMsg("unknown field size");
	return 0;
}

#if T6
/*
==============
MSG_GetField64
==============
*/
__int64 MSG_GetField64(const __int64 *i, int size)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}
#endif

