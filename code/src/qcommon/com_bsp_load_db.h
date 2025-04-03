#include "types.h"

ComPrimaryLight *varComPrimaryLight;
ComWorld *varComWorld;
ComWorld **varComWorldPtr;

/*
==============
Load_ComPrimaryLight
==============
*/
void oad_ComPrimaryLight(bool atStreamStart)
{
	Load_Stream(atStreamStart, varComPrimaryLight, 220);
	varXString = &varComPrimaryLight->defName;
	Load_XString(0);
}

/*
==============
Load_ComPrimaryLightArray
==============
*/
void Load_ComPrimaryLightArray(bool atStreamStart, int count)
{
	if (!Load_Stream(atStreamStart, varComPrimaryLight, 220 * count))
	{
		return;
	}

	for (int i = 0; i < count; ++i)
	{
		Load_ComPrimaryLight(0);
		++varComPrimaryLight;
	}
}

/*
==============
Load_ComWorld
==============
*/
void Load_ComWorld(bool atStreamStart)
{
	if (!Load_Stream(atStreamStart, varComWorld, 16))
	{
		return;
	}

	DB_PushStreamPos(5);

	if (varComWorld->primaryLights)
	{
		varComWorld->primaryLights = (ComPrimaryLight *)AllocLoad_FxElemVisStateSample();
		varComPrimaryLight = varComWorld->primaryLights;
		Load_ComPrimaryLightArray(1, varComWorld->primaryLightCount);
	}

	DB_PopStreamPos();
}

/*
==============
Load_ComWorldPtr
==============
*/
void Load_ComWorldPtr(bool atStreamStart)
{
	if (!Load_Stream(atStreamStart, varComWorldPtr, 4))
	{
		return;
	}

	DB_PushStreamPos(0);

	if (*varComWorldPtr)
	{
		int value = (unsigned int)*varComWorldPtr;
		if (*varComWorldPtr == (ComWorld *)-1 || value == -2)
		{
			*varComWorldPtr = (ComWorld *)AllocLoad_FxElemVisStateSample();
			varComWorld = *varComWorldPtr;

			const void **inserted{};

			if (value == -2)
			{
				inserted = DB_InsertPointer();
			}
			else
			{
				inserted = NULL;
			}

			if (inserted)
			{
				*inserted = *varComWorldPtr;
			}

			Load_ComWorld(true);
			Load_ComWorldAsset(varComWorldPtr);
		}
		else
		{
			DB_ConvertOffsetToAlias(varComWorldPtr);
		}
	}

	DB_PopStreamPos();
}

/*
==============
Mark_ComWorldPtr
==============
*/
void Mark_ComWorldPtr()
{
	if (*varComWorldPtr)
	{
		varComWorld = *varComWorldPtr;
		Mark_ComWorldAsset(varComWorld);
	}
}

