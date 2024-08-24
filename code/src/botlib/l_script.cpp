#include "types.h"

/*
==============
PS_CreatePunctuationTable
==============
*/
void PS_CreatePunctuationTable(script_s *script, punctuation_s *punctuations)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ScriptError
==============
*/
void ScriptError(script_s *script, const char *str, ...)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
ScriptWarning
==============
*/
void ScriptWarning(script_s *script, const char *str, ...)
{
	char text[1024];
	va_list ap;

	va_start(ap, str);

	if ((script->flags & 2) == 0)
	{
		_vsnprintf(text, 0x400u, str, ap);
		Com_PrintWarning(21, "Warning: file %s, line %d: %s\n", script->filename, script->line, text);
	}
}

/*
==============
PS_ReadWhiteSpace
==============
*/
int PS_ReadWhiteSpace(script_s *script)
{
	// straight from ida
	// clean up soon

	char *script_p;

LABEL_1:
	if (*script->script_p <= 32)
	{
		do
		{
			script_p = script->script_p;

			if (!*script_p)
			{
				return 0;
			}

			if (*script_p == 10)
			{
				++script->line;
			}

			script->script_p = script_p + 1;
		}

		while (script_p[1] <= 32);
	}

	char *v2 = script->script_p;

	if (*v2 == 47)
	{
		char v3 = v2[1];
		char *v4 = v2 + 1;

		if (v3 == 47)
		{
			script->script_p = v4;

			while (1)
			{
				script->script_p = ++v4;

				if (!*v4)
				{
					return 0;
				}

				if (*v4 == 10)
				{
					++script->line;

					goto LABEL_20;
				}
			}
		}

		if (v3 == 42)
		{
			script->script_p = v4;

			while (1)
			{
				script->script_p = ++v4;

				if (!*v4)
				{
					return 0;
				}

				if (*v4 == 10)
				{
					++script->line;
				}

				if (*v4 == 42 && v4[1] == 47)
				{
					v4 = ++script->script_p;

					if (!*v4)
					{
						return 0;
					}
LABEL_20:
					char *v5 = v4 + 1;
					script->script_p = v5;

					if (*v5)
					{
						goto LABEL_1;
					}

					return 0;
				}
			}
		}
	}

	return 1;
}

/*
==============
PS_ReadEscapeCharacter
==============
*/
int PS_ReadEscapeCharacter(script_s *script, char *ch)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PS_ReadString
==============
*/
int PS_ReadString(script_s *script, token_s *token, int quote)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PS_ReadName
==============
*/
int PS_ReadName(script_s *script, token_s *token)
{
	int v2 = 0;
	token->type = 4;
	int result = 1;

	while (1)
	{
		token->string[v2] = *script->script_p++;

		if (++v2 >= 1024)
		{
			break;
		}

		char v4 = *script->script_p;

		if ((v4 < 97 || v4 > 122) && (v4 < 65 || v4 > 90) && (v4 < 48 || v4 > 57) && v4 != 95)
		{
			token->string[v2] = 0;
			token->subtype = v2;

			return result;
		}
	}

	ScriptError(script, "name longer than MAX_TOKEN = %d", 1024);

	return 0;
}

/*
==============
NumberValue
==============
*/
void NumberValue(char *string, int subtype, unsigned int *intvalue, long double *floatvalue)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
PS_ReadNumber
==============
*/
int PS_ReadNumber(script_s *script, token_s *token)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PS_ReadPunctuation
==============
*/
int PS_ReadPunctuation(script_s *script, token_s *token)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
PS_ReadPrimitive
==============
*/
int PS_ReadPrimitive(script_s *script, token_s *token)
{
	int result;
	int v2 = 0;

	for (result = 1; *script->script_p > 32; ++v2)
	{
		char v4 = *script->script_p;

		if (v4 == 59)
		{
			break;
		}

		if (v2 >= 1024)
		{
			ScriptError(script, "primitive token longer than MAX_TOKEN = %d", 1024);
			return 0;
		}

		token->string[v2] = v4;
		++script->script_p;
	}

	token->string[v2] = 0;

	qmemcpy(&script->token, token, sizeof(script->token));

	return result;
}

/*
==============
PS_ReadToken
==============
*/
int PS_ReadToken(script_s *script, token_s *token)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

/*
==============
StripDoubleQuotes
==============
*/
void StripDoubleQuotes(char *string)
{
	if (*string == 34)
	{
		// needs a clean up

		char *v1 = string + 1;
		do
		{
			char v2 = *v1;
			*(v1 - 1) = *v1;
			++v1;
		}
		while (v2);
	}

	if (string[strlen(string) - 1] == 34)
	{
		string[strlen(string) - 1] = 0;
	}
}

/*
==============
EndOfScript
==============
*/
BOOL EndOfScript(script_s *script)
{
	return script->script_p >= script->end_p;
}

/*
==============
LoadScriptFile
==============
*/
script_s *LoadScriptFile(const char *filename)
{
	int fp;
	char pathname[64];

	Com_sprintf(pathname, 64, "%s", filename);

	int v1 = FS_FOpenFileRead(pathname, &fp);

	if (!fp)
	{
		return 0;
	}

	script_s *ClearedMemory = GetClearedMemory(v1 + 1201);

	strcpy(ClearedMemory->filename, filename);

	ClearedMemory->buffer = ClearedMemory[1].filename;
	ClearedMemory[1].filename[v1] = 0;
	char *buffer = ClearedMemory->buffer;
	ClearedMemory->script_p = buffer;
	ClearedMemory->lastscript_p = buffer;
	ClearedMemory->length = v1;
	ClearedMemory->end_p = &buffer[v1];
	ClearedMemory->tokenavailable = 0;
	ClearedMemory->line = 1;
	ClearedMemory->lastline = 1;

	PS_CreatePunctuationTable(ClearedMemory, default_punctuations);

	char *v5 = ClearedMemory->buffer;
	ClearedMemory->punctuations = default_punctuations;

	FS_Read(v5, v1, fp);
	FS_FCloseFile(fp);

	ClearedMemory->length = Com_Compress(ClearedMemory->buffer);

	return ClearedMemory;
}

/*
==============
LoadScriptMemory
==============
*/
script_s *LoadScriptMemory(const char *ptr, int length, const char *name)
{
	script_s *ClearedMemory = GetClearedMemory(length + 1201);

	strcpy(ClearedMemory->filename, name);

	ClearedMemory->buffer = ClearedMemory[1].filename;
	ClearedMemory[1].filename[length] = 0;
	char *buffer = ClearedMemory->buffer;
	ClearedMemory->script_p = buffer;
	ClearedMemory->lastscript_p = buffer;
	ClearedMemory->length = length;
	ClearedMemory->end_p = &buffer[length];
	ClearedMemory->tokenavailable = 0;
	ClearedMemory->line = 1;
	ClearedMemory->lastline = 1;

	PS_CreatePunctuationTable(ClearedMemory, default_punctuations);

	unsigned __int8 *v6 = ClearedMemory->buffer;
	ClearedMemory->punctuations = default_punctuations;

	memcpy(v6, ptr, length);

	return ClearedMemory;
}

/*
==============
FreeScript
==============
*/
void FreeScript(script_s *script)
{
	if (script->punctuationtable)
	{
		FreeMemory(script->punctuationtable);
	}

	FreeMemory(script);
}

