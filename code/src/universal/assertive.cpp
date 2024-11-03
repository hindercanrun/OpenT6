#include "types.h"

void	(__cdecl *AssertCallback)(const char *);

char	assertMessage[4096];
char	lineBuffer[4096];
char	g_module[260];
char	*startOfStackTrace = NULL;

int		isHandlingAssert = 0;
int		g_assertAddressCount = NULL;
int		lastAssertType = NULL;

unsigned __int8		*lineBufferEndPos;
int					lineBufferStartPos;

bool	shouldQuitOnError = 0;
bool	g_inStackTrace = 0;


typedef struct {
	int		address;

	char	moduleName[64];

	char	bestFunction[64];
	char	bestFunctionFilename[64];
	int		bestFunctionAddress;

	char	bestLineFilename[64];
	int		bestLineAddress;
	int		bestLineNumber;
} AddressInfo_s;


AddressInfo_s	g_assertAddress[32];



/*
==============
FixWindowsDesktop

==============
*/
void FixWindowsDesktop( void ) {
	HDC__	*hdc;
	HWND__	*hwndDesktop;
	WORD	ramp[770];
	int		i;

	ChangeDisplaySettings( 0, 0 );

	EnumThreadWindows( GetCurrentThreadId (), HideWindowCallback, 0 );

	hwndDesktop = GetDesktopWindow( );
	hdc = GetDC( hwndDesktop );

	for ( i = 0 ; i <  0x100u ; ++i ) {
		ramp[i] = 257 * i;
		ramp[i + 256] = 257 * i;
		ramp[i + 512] = 257 * i;
	}

	SetDeviceGammaRamp( hdc, ramp );
	ReleaseDC( hwndDesktop, hdc );
}


/*
==============
HideWindowCallback

==============
*/
int HideWindowCallback( HWND__ *hwnd, int lParam ) {
	LONG	styleEx;
	char	caption[1024];
	int		style;

	if ( GetWindowText( hwnd, caption, 1024 ) && strcmp( caption, Com_GetBuildDisplayNameR () ) ) {
		return TRUE;
	}

	style = GetWindowLong( hwnd, -16 );
	styleEx = GetWindowLong( hwnd, -20 );

	if ( ( style & 0x10000000 ) != 0 ) {
		g_hwndGame[g_hiddenCount++] = hwnd;

		SetWindowLong( hwnd, -16, style & 0xEFFFFFFF );
		SetWindowLong( hwnd, -20, styleEx & 0xFFFFFFF7 );
	}

	return TRUE;
}


/*
==============
TRACK_assertive

==============
*/
void TRACK_assertive( void ) {
	track_static_alloc_internal( assertMessage,		4096,	"assertMessage",	0 );
	track_static_alloc_internal( lineBuffer,		4096,	"lineBuffer",		0 );
	track_static_alloc_internal( g_assertAddress,	8704,	"g_assertAddress",	0 );
}


/*
==============
Assert_DoStackTrace

==============
*/
int Assert_DoStackTrace( const char *msg, int nIgnore, int type, int *context ) {
	int	result;
	int *v5;
	int *reg_ebp;
	int i;
	int	savedregs;

	if ( g_inStackTrace ) {
		return 0;
	}

	g_inStackTrace = 1;

	memset( (unsigned __int8 *)g_assertAddress, 0, sizeof(g_assertAddress) );
	g_assertAddressCount = 0;
	if ( context ) {
		reg_ebp = context;
	} else {
		reg_ebp = &savedregs;
	}

	for ( i = 0; i < nIgnore + 32; ++i ) {
		v5 = reg_ebp;
		reg_ebp = (int *)*reg_ebp;

		if (i >= nIgnore) {
			g_assertAddress[g_assertAddressCount++].address = v5[1] - 5;

			if ( !reg_ebp ) {
				break;
			}
		}
	}

	result = LoadMapFiles( msg );
	g_inStackTrace = 0;

	return result;
}


/*
==============
LoadMapFiles

==============
*/
int LoadMapFiles( const char *msg ) {
	int				v2;
	int				j;
	AddressInfo_s	*addressInfo;
	char			*curPos;
	char			*curPosa;
	char			*curPosb;

#ifdef PLATFORM_XENON
	LoadMapFilesForDir ("D:");//LoadMapFilesForDir ("D:\\t6\\game\\xenon\\");
#endif
#ifdef PLATFORM_PS3
	LoadMapFilesForDir ("D:\\t6\\game\\ps3\\");
#endif
#ifdef PLATFORM_WIIU
	LoadMapFilesForDir ("D:\\t6\\game\\wiiu\\");
#endif
#ifdef PLATFORM_PC
	LoadMapFilesForDir ("D:\\t6\\game\\pc\\");
#endif

	if ( !msg ) {
		return 0;
	}

	curPos = msg;

	for ( j = 0 ; j < g_assertAddressCount  ; ++j ) {
		addressInfo = &g_assertAddress[j];

		if ( addressInfo->moduleName[0] ) {
			curPosa = &curPos[ sprintf (curPos, "%s:    ", addressInfo->moduleName)];

			if ( addressInfo->bestLineFilename[0] ) {
				curPosb = &curPosa[sprintf(curPosa, "%s        ...%s, line %i",
					addressInfo->bestFunction, addressInfo->bestLineFilename, addressInfo->bestLineNumber)];

				v2 = sprintf( curPosb, "\n" );
			} else {
				if ( addressInfo->bestFunction[0] ) {
					curPosb = &curPosa[sprintf(
										curPosa,
										"%s        ...%s, address %x",
										addressInfo->bestFunction,
										addressInfo->bestFunctionFilename,
										addressInfo->address)];
				} else {
					curPosb = &curPosa[ sprintf(curPosa, "%s, address %x", addressInfo->bestFunction, addressInfo->address) ];
				}

				v2 = sprintf ( curPosb, "\n" ) ;
			}

			curPos = &curPosb[v2];
		}
	}

	return curPos - msg;
}


/*
==============
LoadMapFilesForDir

==============
*/
void LoadMapFilesForDir( const char *dir ) {
	//terrible
	char				v4;
	char				*p_file;
	cha					*cFileName;
	_WIN32_FIND_DATAA	FindFileData;
	char				file;
	BYTE				v9[3];
	int					baseAddress;
	_iobuf				*fp;
	HANDLE				hFindFile;
	char				string[2052];

	if ( *dir ) {
		sprintf(string, "%s\\%s\\*.map", Sys_DefaultInstallPath(), dir);
	} else {
		sprintf(string, "%s\\*.map", Sys_DefaultInstallPath());
	}

	hFindFile = FindFirstFile( string, &FindFileData );
	if ( hFindFile != (HANDLE)-1 ) {
		do {
			baseAddress = GetModuleBase( FindFileData.cFileName );
			if ( baseAddress ) {
				sprintf( &file, "%s\\%s", Sys_DefaultInstallPath (), FindFileData.cFileName );

				fp = fopen( &file, "rb" );
				if ( fp ) {
					cFileName = FindFileData.cFileName;
					p_file = &file;

					do {
						v4 = *cFileName;
						*p_file++ = *cFileName++;
					} while ( v4 );

					FindFileData.cAlternateFileName[ &v9[ strlen( &file ) ] - v9 + 12] = 0;


					ParseMapFile( fp, baseAddress, &file );
					fclose( fp );
				}
			}
		} while ( FindNextFile( hFindFile, &FindFileData ) );

		FindClose( hFindFile );
	}
}


/*
==============
ParseMapFile

==============
*/
char ParseMapFile( _iobuf *fp, unsigned int baseAddress, const char *mapName ) {
	UNIMPLEMENTED (__FUNCTION__);
	return NULL;
}


/*
==============
ParseError

==============
*/
void ParseError( const char* msg ) {
	MessageBoxA( GetActiveWindow (), msg, ".map parse error", MB_ICONERROR );
}


/*
==============
ReadLine

==============
*/
char ReadLine( _iobuf *fp ) {
	signed int	readSize;
	int			bytesRead;
	int			i;

START:
	lineBufferEndPos -= lineBufferStartPos;

//no asserts in ship
//todo: move these comments into the defs
#if defined(RELEASE_ASSERT) || defined(DEBUG_ASSERT) || defined(MILESTONE)
	if ( lineBufferEndPos < 0 ) {
		assert_message( "lineBufferEndPos >= 0" );
	}
#endif // #if defined(RELEASE_ASSERT) || defined(DEBUG_ASSERT) || defined(MILESTONE)

	memmove( lineBuffer, &lineBuffer[lineBufferStartPos], (unsigned int)lineBufferEndPos );

	lineBufferStartPos = 0;

	for ( i = 0; ; ++i ) {
		if ( i >= (int)lineBufferEndPos ) {
		LABEL_13:
			readSize = 4096 - (DWORD)lineBufferEndPos - 1;
			bytesRead = fread( &lineBuffer[(DWORD)lineBufferEndPos], 1u, readSize, fp );

//above comment
#if defined(RELEASE_ASSERT) || defined(DEBUG_ASSERT) || defined(MILESTONE)
			if ( bytesRead > readSize ) {
				assert_message( "bytesRead <= readSize" );
			}
#endif // #if defined(RELEASE_ASSERT) || defined(DEBUG_ASSERT) || defined(MILESTONE)

			lineBufferEndPos += bytesRead;
			lineBuffer[(DWORD)lineBufferEndPos] = 0;

			if ( !bytesRead ) {
				if ( !lineBufferEndPos ) {
					return FALSE;
				}

				lineBufferStartPos = (int)lineBufferEndPos;
				return TRUE;
			}

			goto START;
		}

		if ( lineBuffer[i] == 10 ) {
			break;
		}
	}

	if ( (unsigned __int8*)( i + 1 ) == lineBufferEndPos ) {
		goto LABEL_13;
	}

	lineBuffer[i] = 0;

	if ( *(BYTE*)( i + 161261593 ) == 13 ) {
		lineBufferStartPos = i + 2;
	} else {
		lineBufferStartPos = i + 1;
	}

	return TRUE;
}


/*
==============
SkipLines

==============
*/
char SkipLines( int lineCount, _iobuf *fp ) {
	int		i;

	for ( i = 0 ; i < lineCount ; ++i ) {
		if ( !ReadLine( fp ) ) {
			return 0;
		}
	}

	return TRUE;
}


/*
==============
GetModuleBase

==============
*/
HINSTANCE__ *GetModuleBase( char *name ) {
	const char	*v2;
	HINSTANCE__	*moduleHandle;

	int			nameLength;
	int			nameIndex;

	char		moduleName[264];


	v2 = &name[strlen (name) + 1];
	nameLength = v2 - ( name + 1 );

	if ( nameIndex >= 0 && name[nameIndex] == 46 ) {
		nameLength = nameIndex;
	}

	memcpy((unsigned __int8 *)moduleName, (unsigned __int8 *)name, nameLength);
	strcpy(&moduleName[nameLength], ".exe");

	moduleHandle = GetModuleHandleA(moduleName);
	if ( moduleHandle ) {
		return moduleHandle;
	}

	strcpy( &moduleName[nameLength], ".dll" );

	return GetModuleHandle( moduleName );
}


/*
==============
Assert_ResetAddressInfo

==============
*/
void Assert_ResetAddressInfo( void ) {
	g_assertAddressCount = 0;
}



char message[1024];

/*
==============
Assert_MyHandler

==============
*/
BOOL Assert_MyHandler( const char* expression, const char *filename, int line, int type, const char *fmt, ... ) {
	const char	*msg;
	va_list		va;

	va_start (va, fmt);

	Sys_EnterCriticalSection( CRITSECT_ASSERT );

	_vsnprintf(message, 0x400u, fmt, va);
	message[1023] = 0;


	if ( isHandlingAssert ) {
		msg = ::va( "Assert Expression:\n    %s\nFile:    %s\nLine:    %d\n\n", expression, filename, line );
		Com_Printf( 16, msg );

		CopyMessageToClipboard ();

		AssertNotify( lastAssertType, RECURSIVE );
		Assert_BuildAssertMessage( message, filename, line, type, 1,  expression);

		if ( isHandlingAssert == 1 ) {
			isHandlingAssert = 2;

			Com_Printf( 16, "ASSERTBEGIN - ( Recursive assert )---------------------------------------------\n" );
			Com_Printf( 16, "%s", expression );
			Com_Printf( 16, "ASSERTEND - ( Recursive assert ) ----------------------------------------------\n\n" );
		}

		_exit( -1 );
	}

	lastAssertType = type;
	isHandlingAssert = 1;

	FixWindowsDesktop ();
	Assert_BuildAssertMessage ( message, filename, line, type, 1, expression );


	Com_Printf( 16, "ASSERTBEGIN -------------------------------------------------------------------\n" );
	Com_Printf( 16, "%s", expression );
	Com_Printf( 16, "ASSERTEND ---------------------------------------------------------------------\n" );

	if ( QuitOnError () ) {
		ExitProcess( 0xFFFFFFFF );
	}


	CopyMessageToClipboard ();

	isHandlingAssert = 0;
	Sys_LeaveCriticalSection( CRITSECT_ASSERT );

	return !AssertNotify( type, FIRST_TIME );
}


/*
==============
CopyMessageToClipboard

==============
*/
BOOL CopyMessageToClipboard () {
	char	v2;
	char	*v3;
	char	*v4;
	char	*mem;

	HGLOBAL	memoryHandle;
	BOOL	result;

	//very bad but it'll do
	result = OpenClipboard (GetDesktopWindow ());
	if ( result ) {
		EmptyClipboard();

		memoryHandle = GlobalAlloc( 2u, strlen( assertMessage ) + 1 );
		if ( memoryHandle ) {
			mem = (char *)GlobalLock( memoryHandle );
			if ( mem ) {
				v4 = assertMessage;
				v3 = mem;

				do {
					v2 = *v4;
					*v3++ = *v4++;
				} while ( v2 );

				GlobalUnlock( memoryHandle );
				SetClipboardData( 1u, memoryHandle );
			}
		}

		return CloseClipboard ();
	}

	return result;
}


/*
==============
AssertNotify

==============
*/
char AssertNotify( int type, AssertOccurance occurance ) {
	const char	*msg;

	if ( AssertCallback ) {
		AssertCallback( assertMessage );
	}

	if ( type ) {
		if ( type == 1 ) {
			msg = "SANITY CHECK FAILURE... (this text is on the clipboard)";
		} else {
			msg = "INTERNAL ERROR";
		}
	} else {
		msg = "ASSERTION FAILURE... (this text is on the clipboard)";
	}

	ShowCursor(TRUE);

	if ( MessageBoxA( GetActiveWindow(), assertMessage, msg, 0x12011u ) == TRUE ) {
		if ( occurance != RECURSIVE ) {
			if ( Sys_IsMiniDumpStarted () && !IsDebuggerPresent () ) {
				RaiseException( 1u, 0, 0, 0 );
			}

			exit(-1);
		}

		return TRUE;
	} else {
		return TRUE;
	}
}


/*
==============
Assert_BuildAssertMessage

==============
*/
void Assert_BuildAssertMessage( const char *expression, const char *filename, int line, int type, int skipLevels, const char *message ) {
	const char	*BuildVersion;
	const char	*BuildName;
	const char	*BuildDisplayName;

	char		*curPos;
	char		unknown[12];

	strcpy( unknown, "<unknown>" );

	//
	//	file name
	//
	if ( !filename ) {
		filename = unknown;
	}

	//
	//	expression
	//
	if ( !expression ) {
		expression = unknown;
	}

	//
	//	program name
	//
	if ( !GetModuleFileName( 0, g_module, 0x104u ) ) {
		strcpy( g_module, "<unknown application>" );
	}

	BuildVersion		= Com_GetBuildVersion ();
	BuildName			= Com_GetBuildName ();
	BuildDisplayName	= Com_GetBuildDisplayName();

	//
	//	version number
	//
	curPos = &message[sprintf(message, "Build: %s %s build %s %s\n", BuildDisplayName, BuildName, BuildVersion, "win-x86")];

	//
	//	format the start of the message
	//
	startOfStackTrace = &curPos[sprintf(
									curPos,
									"Expression:\n    %s\n\nModule:    %s\nFile:    %s\nLine:    %d\n\n",
									expression,
									g_module,
									filename,
									line)];
	Assert_DoStackTrace(startOfStackTrace, skipLevels + 1, type, 0);
}


/*
==============
RefreshQuitOnErrorCondition

==============
*/
void RefreshQuitOnErrorCondition (void) {
	if ( Dvar_IsSystemActive () ) {
		shouldQuitOnError = Dvar_GetBool ("QuitOnError") || Dvar_GetInt ("r_vc_compile") == 2;
	}
}


/*
==============
QuitOnError

==============
*/
bool QuitOnError( void ) {
	RefreshQuitOnErrorCondition ();

	return shouldQuitOnError;
}
