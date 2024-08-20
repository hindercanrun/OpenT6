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
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
PS_ReadWhiteSpace
==============
*/
int PS_ReadWhiteSpace(script_s *script)
{
	char *script_p;

LABEL_1:
	if ( *script->script_p <= 32 )
	{
		do
		{
			script_p = script->script_p;

			if ( !*script_p )
			{
				return 0;
			}

			if ( *script_p == 10 )
			{
				++script->line;
			}

			script->script_p = script_p + 1;
		}

		while ( script_p[1] <= 32 );
	}

	char *v2 = script->script_p;

	if ( *v2 == 47 )
	{
		char v3 = v2[1];
		char *v4 = v2 + 1;

		if ( v3 == 47 )
		{
			script->script_p = v4;

			while ( 1 )
			{
				script->script_p = ++v4;

				if ( !*v4 )
				{
					return 0;
				}

				if ( *v4 == 10 )
				{
					++script->line;

					goto LABEL_20;
				}
			}
		}

		if ( v3 == 42 )
		{
			script->script_p = v4;

			while ( 1 )
			{
				script->script_p = ++v4;

				if ( !*v4 )
				{
					return 0;
				}

				if ( *v4 == 10 )
				{
					++script->line;
				}

				if ( *v4 == 42 && v4[1] == 47 )
				{
					v4 = ++script->script_p;

					if ( !*v4 )
					{
						return 0;
					}
LABEL_20:
					char *v5 = v4 + 1;
					script->script_p = v5;

					if ( *v5 )
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

	while ( 1 )
	{
		token->string[v2] = *script->script_p++;
		if ( ++v2 >= 1024 )
			break;
		char v4 = *script->script_p;
		if ( (v4 < 97 || v4 > 122) && (v4 < 65 || v4 > 90) && (v4 < 48 || v4 > 57) && v4 != 95 )
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

	for ( result = 1; *script->script_p > 32; ++v2 )
	{
		char v4 = *script->script_p;

		if ( v4 == 59 )
		{
			break;
		}

		if ( v2 >= 1024 )
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
	UNIMPLEMENTED(__FUNCTION__);
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
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
LoadScriptMemory
==============
*/
script_s *LoadScriptMemory(const char *ptr, int length, const char *name)
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
FreeScript
==============
*/
void FreeScript(script_s *script)
{
	UNIMPLEMENTED(__FUNCTION__);
}

