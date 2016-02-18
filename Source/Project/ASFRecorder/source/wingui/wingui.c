
/*     GUI code for the ASFRecorder application     */
/* Uses ActiveMovie (DirectShow) for stream preview */

#include "global.h"
#include "CmdLine.h"

#ifdef  __MINGW32__
/* we need to rename the main() function for MINGW32 */
/* because otherwise WinMain() will never be called */
#define main(argc,argv) renamed_main(argc,argv)
#endif /* __MINGW32__ */

#define UNTITLED_STRING " - Untitled"
#define nMaxResourceStrSize 128

/*--------------------------------- GLOBALS ---------------------------------*/

/* some application variables */
AppVars appVars;

/* used for inter-process communication */
UINT WM_APPMSG;
#define MAGIC_COOKIE 0x1234
BOOL Idle = TRUE;

/* window and control handles */
HWND hwndAboutBox = NULL;
HWND hwndStatusbar = NULL;
HWND hwndOpenURLDialog = NULL;
// The window for each toolbar button
struct{
    HWND hwndPlayButton;
    HWND hwndPauseButton;
    HWND hwndStopButton;
    HWND hwndPreviewButton;
    HWND hwndCancelButton;
} toolbar = {NULL, NULL, NULL, NULL, NULL};
HWND hwndTrackbar = NULL;

/* timer for flashing status bar */
#define ID_STATUSTIMER   1
UINT StatusTimer = 0;
UINT StatusTimerCount;
UINT StatusTimerCref;

/* timer for moving trackbar */
#define ID_TRACKBARTIMER 2
UINT TrackbarTimer = 0;

/* some more trackbar stuff */
int positionTrackbar;
BOOL TrackbarDragging = FALSE;

/* flags/names of current stream and media file */
BOOL Batchmode = FALSE;
char StreamURL[512]  = "";
char StreamFilename[512] = "";
unsigned int StreamTotalTime;
unsigned int StreamMaxTime;
BOOL Transmitting = FALSE;
BOOL Previewing = FALSE;

/* data obtained from the IMediaPosition interface */
REFTIME IMPTotalTime;
REFTIME IMPCurrentPosition;
REFTIME IMPDownloadTime; /* obtained from gui_progressinfo */

/* data obtained from the IMediaSeeking interface */
LONGLONG IMSTotalTime;
LONGLONG IMSCurrentPosition;
DWORD    IMSCapabilities;
LONGLONG IMSDownloadTime; /* obtained from gui_progressinfo */

/* video window positions */
long IVWWindowLeft   = 0;
long IVWWindowTop    = 0;
long IVWWindowWidth  = 0;
long IVWWindowHeight = 0;

/* definition of min/max widths of status bar parts */
int StatusDefinitionArray[] =
{   6,
    50, 80,
    30, 40,
    80, 120,
    50, 80,
    160, -1,
    16, 16 };

/* enumeration of the status bar parts */
enum
{   STAT_KB = 0,
    STAT_PROGRESS,
    STAT_TIMECODE,
    STAT_SEQNO,
    STAT_STATUS, };

/* event for network socket notification */
WSAEVENT NetworkEvent = WSA_INVALID_EVENT;
SOCKET NetworkSocket = INVALID_SOCKET;

/* Winsock error strings/codes */
struct ErrorDef
{
    char* ErrorName;
    int   ErrorVal;
} WinSockErrors[] =

{
    "INTR"                ,(WSABASEERR+4),
    "BADF"                ,(WSABASEERR+9),
    "ACCES"               ,(WSABASEERR+13),
    "FAULT"               ,(WSABASEERR+14),
    "INVAL"               ,(WSABASEERR+22),
    "MFILE"               ,(WSABASEERR+24),
    "WOULDBLOCK"          ,(WSABASEERR+35),
    "INPROGRESS"          ,(WSABASEERR+36),
    "ALREADY"             ,(WSABASEERR+37),
    "NOTSOCK"             ,(WSABASEERR+38),
    "DESTADDRREQ"         ,(WSABASEERR+39),
    "MSGSIZE"             ,(WSABASEERR+40),
    "PROTOTYPE"           ,(WSABASEERR+41),
    "NOPROTOOPT"          ,(WSABASEERR+42),
    "PROTONOSUPPORT"      ,(WSABASEERR+43),
    "SOCKTNOSUPPORT"      ,(WSABASEERR+44),
    "OPNOTSUPP"           ,(WSABASEERR+45),
    "PFNOSUPPORT"         ,(WSABASEERR+46),
    "AFNOSUPPORT"         ,(WSABASEERR+47),
    "ADDRINUSE"           ,(WSABASEERR+48),
    "ADDRNOTAVAIL"        ,(WSABASEERR+49),
    "NETDOWN"             ,(WSABASEERR+50),
    "NETUNREACH"          ,(WSABASEERR+51),
    "NETRESET"            ,(WSABASEERR+52),
    "CONNABORTED"         ,(WSABASEERR+53),
    "CONNRESET"           ,(WSABASEERR+54),
    "NOBUFS"              ,(WSABASEERR+55),
    "ISCONN"              ,(WSABASEERR+56),
    "NOTCONN"             ,(WSABASEERR+57),
    "SHUTDOWN"            ,(WSABASEERR+58),
    "TOOMANYREFS"         ,(WSABASEERR+59),
    "TIMEDOUT"            ,(WSABASEERR+60),
    "CONNREFUSED"         ,(WSABASEERR+61),
    "LOOP"                ,(WSABASEERR+62),
    "NAMETOOLONG"         ,(WSABASEERR+63),
    "HOSTDOWN"            ,(WSABASEERR+64),
    "HOSTUNREACH"         ,(WSABASEERR+65),
    "NOTEMPTY"            ,(WSABASEERR+66),
    "PROCLIM"             ,(WSABASEERR+67),
    "USERS"               ,(WSABASEERR+68),
    "DQUOT"               ,(WSABASEERR+69),
    "STALE"               ,(WSABASEERR+70),
    "REMOTE"              ,(WSABASEERR+71),
    "SYSNOTREADY"         ,(WSABASEERR+91),
    "VERNOTSUPPORTED"     ,(WSABASEERR+92),
    "NOTINITIALISED"      ,(WSABASEERR+93),
    "DISCON"              ,(WSABASEERR+101),
    "HOST_NOT_FOUND"      ,(WSABASEERR+1001),
    "TRY_AGAIN"           ,(WSABASEERR+1002),
    "NO_RECOVERY"         ,(WSABASEERR+1003),
    "NO_DATA"             ,(WSABASEERR+1004),
    NULL,                 -1
};


/*--------------------------- FUNCTION PROTOTYPES ---------------------------*/

/* Function prototypes for externals in asfrecorder.c */
extern int main(int argc, char **argv);
extern int main_function(int argc, char **argv);
extern void gui_abort(void);
extern char *createtimestring(unsigned int timecode);
typedef enum  {
    ShowUsage,
    NoArguments,
    BadOption,
} UsageMode;
void Usage(char *progname, UsageMode mode);
UINT DoEnterPasswordDialog( HINSTANCE hInstance, HANDLE hwnd );
UINT DoProxyConfigurationDialog( HINSTANCE hInstance, HANDLE hwnd );


/*--------------------------- WINMAIN ENTRY POINT ---------------------------*/

//
// WinMain
//
// use call custom command line parser and
// give control to main() in asfrecorder.c
//
int PASCAL WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam,
                    int nCmdShow )
{
    UINT nReturn = 0;
    HWND win;
    DWORD result;
    
    LPTSTR cmdline;

    cmdline = GetCommandLine();

    /* register an application- and inter-process-global message */
    WM_APPMSG = RegisterWindowMessage( APP_NAME );

    if (WM_APPMSG != 0)
    {
        /* loop through all other open ASFRecorder windows */

        win = NULL;
        while ((win = FindWindowEx(NULL, win, APP_NAME, NULL)) != NULL)
        {
            /* send an application-specific message to the other windows */
            /* to probe if these windows are "idle" (not in a transfer) */
            if (SendMessageTimeout( win, WM_APPMSG, 0, 0, SMTO_BLOCK, 250, &result) != 0)
            {
                if (result == MAGIC_COOKIE)
                {
                    COPYDATASTRUCT cds;
                    DWORD result2;

                    /* other windows seems to be idle */
                    /* so send our command line to this window */

                    cds.dwData = MAGIC_COOKIE;
                    cds.cbData = strlen(cmdline)+1;
                    cds.lpData = cmdline;

                    result2 = SendMessage( win, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds );

                    if (result2 == MAGIC_COOKIE)
                    {
                        /* other window processed the message */
                        /* so we can exit this process now */
                        return nReturn;
                    }
                }
            }
        }
    }

    /* seems that no other ASFRecorder window was willing to accept */
    /* our command line. So we have to handle it in this process. */

    if (ParseCommandLine(cmdline))
    {
        appVars.szProgramExecutable = argv[0];

        main(argc, argv);
    }
    FreeCommandLine();

    return nReturn;
} // WinMain


/*-------------- INTERFACE CODE TO ASFRECORDER NETWORKING CORE --------------*/

int gui_initialize()
{
    UINT nReturn;

    HINSTANCE hInstance = GetModuleHandleA(NULL);
    HINSTANCE hPrevInstance = NULL;
    LPSTR lpszCmdParam = NULL;
    int nCmdShow = SW_SHOW;

    nReturn = PseudoWinMain(hInstance, hPrevInstance, lpszCmdParam, nCmdShow);

    return nReturn;
}


void gui_uninitialize(void)
{
    EndOfWinMain();
}


void gui_setbatchmode(int flag)
{
    Batchmode = flag;
}


int  gui_startedfromdesktop(void)
{
    int fromdesktop = 0;

    /* I don't know if this is correct, but */
    /* it works for determining wheter this */
    /* programm was started from DOS or from */
    /* Windows Explorer, both on Win98 and NT */

    LPTSTR lpszVariable; 
    LPVOID lpvEnv; 
    
    // Get a pointer to the environment block. 
    
    if ((lpvEnv = GetEnvironmentStrings()) != NULL)
    {
        // Variable strings are separated by NULL byte, and the block is 
        // terminated by a NULL byte. 
        
        for (lpszVariable = (LPTSTR) lpvEnv; *lpszVariable; lpszVariable++) 
        { 
            /* this one is for Windows NT (together with PROMPT=) */
            if (!stricmp(lpszVariable, "OS=Windows_NT"))
                fromdesktop = 1;
            while (*lpszVariable) lpszVariable++;
        } 

        for (lpszVariable = (LPTSTR) lpvEnv; *lpszVariable; lpszVariable++) 
        { 
            /* this one for Windows 98 */
            if (!stricmp(lpszVariable, "CMDLINE=win"))
                fromdesktop = 1;
            /* required for Windows NT only */
            if (!strnicmp(lpszVariable, "PROMPT=", 7))
                fromdesktop = 0;
            while (*lpszVariable) lpszVariable++;
        } 

        FreeEnvironmentStrings(lpvEnv);
    }
    return fromdesktop;
}


void gui_prepareasyncsocket(SOCKET s)
{
    int rc;

    if (NetworkEvent == WSA_INVALID_EVENT)
    {
        NetworkEvent = WSACreateEvent();
    }

    if (NetworkEvent != WSA_INVALID_EVENT)
    {
        NetworkSocket = s;
        rc = WSAEventSelect(s, NetworkEvent, FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE);
        if (rc == SOCKET_ERROR)
        {
            gui_criticalerror("WSAEventSelect() failed! Error code: %d\n", WSAGetLastError());
        }
    }
}


void gui_restoresyncsocket(SOCKET s)
{
    WSAEventSelect(s, NULL, 0);
    WSACloseEvent(NetworkEvent);

    NetworkSocket = INVALID_SOCKET;
    NetworkEvent = WSA_INVALID_EVENT;
}


void gui_return_on_network_activity(void)
{
    /* don't enter main loop if the user has already closed the main window */
    if (appVars.hwndMainFrame != NULL)
    {
        DoMainLoop(FD_READ | FD_WRITE | FD_CLOSE);
    }
}


void gui_return_on_network_connect(int *returnval)
{
    /* don't enter main loop if the user has already closed the main window */
    if (appVars.hwndMainFrame != NULL)
    {
        int ret = DoMainLoop(FD_CONNECT);

        if (ret == 0)
            *returnval = 0;
        else
        {
            *returnval = SOCKET_ERROR;
            WSASetLastError(ret);
        }
    }
    else
    {
        *returnval = 0;
    }
}


int gui_nonblocking_socket_check(int num)
{
    if (num == WSAEWOULDBLOCK)
        return 1;
    else
        return 0;
}


void gui_waitforuseraction()
{
    /* don't enter main loop if the user has already closed the main window */
    if (appVars.hwndMainFrame != NULL)
    {
        DoMainLoop(0);
    }
}


void gui_showtext(char *text, ...)
{
    char Buffer[4096];

    va_list arglist;
    va_start(arglist, text);

    vsprintf(Buffer, text, arglist);

    MessageBox( appVars.hwndMainFrame, Buffer, appVars.szAppName,
                MB_APPLMODAL | MB_OK | 0 );

    va_end(arglist);
}


void gui_setstatus(char *statustext, ...)
{
    va_list arglist;
    va_start(arglist, statustext);

    SetStatusTextArgs(STAT_STATUS, SBT_POPOUT, CLR_DEFAULT, statustext, arglist);

    va_end(arglist);
}


void gui_seterror(char *errortext, ...)
{
    va_list arglist;
    va_start(arglist, errortext);

    SetStatusTextArgs(STAT_STATUS, SBT_POPOUT, RGB(0xff,0xff,0), errortext, arglist);

    va_end(arglist);
}


void gui_criticalerror(char *errortext, ...)
{
    char Buffer[4096];

    va_list arglist;
    va_start(arglist, errortext);

    vsprintf(Buffer, errortext, arglist);

    if (!Batchmode)
    {
        MessageBox( appVars.hwndMainFrame, Buffer, appVars.szAppName,
                    MB_APPLMODAL | MB_OK | MB_ICONERROR );
    }
    else
    {
        /* in batch mode, don't bother the user with blocking requesters */
        gui_seterror("%s", Buffer);
    }

    va_end(arglist);
}


void gui_logtext(char *text, ...)
{
    char Buffer[4096];

    va_list arglist;
    va_start(arglist, text);

    vsprintf(Buffer, text, arglist);

//    MessageBox( appVars.hwndMainFrame, Buffer, appVars.szAppName,
//                MB_APPLMODAL | MB_OK | 0 );

    va_end(arglist);
}


int gui_start_transmission(char *url, char *filename, int filenamesize, unsigned int totaltime, unsigned int maxtime)
{
    int retval = 0;

    static char szFileName[ _MAX_PATH ];
    static char szTitleName[ _MAX_FNAME + _MAX_EXT ];
    LPSTR szTitle;

    strcpy(StreamURL, url);

    StreamTotalTime = totaltime;
    StreamMaxTime = maxtime;

    if ( appVars.hwndMainFrame != NULL )
    {
        SetStatusText(STAT_KB,       0, -1, "");
        SetStatusText(STAT_PROGRESS, 0, -1, "");
        SetStatusText(STAT_TIMECODE, 0, -1, "");
        SetStatusText(STAT_SEQNO,    0, -1, "");

        if (!strcmp(filename, ""))
        {
            strcpy(StreamFilename, filename);
            
            SetTitle( appVars.hwndMainFrame, StreamURL );
            
            Transmitting = TRUE;
        }
        else
        {
            // Work out the full path name and the file name from the
            // specified file
            GetFullPathName( filename, _MAX_PATH, szFileName, &szTitle );

            if (Batchmode)
            {
                /* don't bother the user with a file dialog in batch mode */
                Transmitting = TRUE;
            }
            else
            {
                strncpy( szTitleName, szTitle, _MAX_FNAME + _MAX_EXT );
                szTitleName[ _MAX_FNAME + _MAX_EXT -1 ] = '\0';
                
                if ( DoFileSaveDialog( appVars.hwndMainFrame, szFileName, szTitleName ) )
                {
                    Transmitting = TRUE;
                }
            }
            
            if (Transmitting)
            {
                /* keep a local copy of the stream file name (for preview) */
                strncpy(StreamFilename, szFileName, sizeof(StreamFilename));
                StreamFilename[sizeof(StreamFilename)-1] = '\0';

                /* return the new file name to the main function */
                strncpy(filename, szFileName, filenamesize);
                filename[filenamesize-1] = '\0';

                SetTitle( appVars.hwndMainFrame, StreamURL );
                retval = 1;
            }
            else
            {
                SetTitle( appVars.hwndMainFrame, "Untitled" );
                strcpy(filename, "");
                retval = 0;
            }
        }
        
        if (hwndTrackbar != NULL)
        {
            SendMessage(hwndTrackbar, TBM_CLEARSEL,    TRUE,  0     );
        }
        
        UpdateToolbar();
    }
    return retval;
}


void gui_progressinfo(int bytes, char *timecode, int progress, int seqno, int currenttime)
{
    /* currenttime is in milliseconds */
    IMPDownloadTime = (REFTIME) currenttime / 1000;   /* REFTIME is in seconds (64 bit floating pt) */
    IMSDownloadTime = (LONGLONG)currenttime * 10000;  /* LONGLONG: 10 million units equal 1 second */

    if ( appVars.hwndMainFrame != NULL )
    {
        /* progress is scaled from 0 (=0%) to 10000 (=100%) */
        SetStatusText(STAT_KB,       0, -1, "%d kB", bytes   /1024  );
        SetStatusText(STAT_PROGRESS, 0, -1, "%d%%",  progress/100   );
        SetStatusText(STAT_TIMECODE, 0, -1, "T: %s", timecode       );
        SetStatusText(STAT_SEQNO,    0, -1, "#%d", seqno            );

        if ((hwndTrackbar != NULL) && (timecode != 0))
        {
            if (StreamTotalTime != 0)
            {
                SendMessage(hwndTrackbar, TBM_SETSELSTART,  FALSE,  0                                              );
                SendMessage(hwndTrackbar, TBM_SETSELEND,    TRUE,   (int)((float)10000*currenttime/StreamTotalTime));
            }
            else
            {
                if (StreamMaxTime != 0)
                {
                    SendMessage(hwndTrackbar, TBM_SETSELSTART,  FALSE,  0                                            );
                    SendMessage(hwndTrackbar, TBM_SETSELEND,    TRUE,   (int)((float)10000*currenttime/StreamMaxTime));
                }
                else
                {
                    SendMessage(hwndTrackbar, TBM_SETSELSTART,  FALSE,  0                                            );
                    SendMessage(hwndTrackbar, TBM_SETSELEND,    TRUE,   10000                                        );
                }
            }
        }
    }
}


void gui_modify_duration(unsigned int totaltime)
{
    /* called only for live recordings */

    LONG value;

    StreamTotalTime = totaltime;

    IMPTotalTime = (REFTIME)totaltime / 1000;
    IMSTotalTime = (LONGLONG)totaltime * 10000;

    value = (LONG)(10000 * IMPCurrentPosition / IMPTotalTime);

    if (hwndTrackbar != NULL)
    {
        if (!TrackbarDragging)
        {
            SendMessage( hwndTrackbar, TBM_SETPOS, TRUE, value);
        }
    }
}


void gui_finished_transmission()
{
    Transmitting = FALSE;
    Previewing = FALSE;

    StreamTotalTime = 0;
    StreamMaxTime = 0;

    if ( appVars. hwndMainFrame != NULL )
    {
        SetStatusText(STAT_KB,       0, -1, "");
        SetStatusText(STAT_PROGRESS, 0, -1, "");
        SetStatusText(STAT_TIMECODE, 0, -1, "");
        SetStatusText(STAT_SEQNO,    0, -1, "");
        
        if (hwndTrackbar != NULL)
        {
            SendMessage(hwndTrackbar, TBM_CLEARSEL,    TRUE,  0     );
        }
        
        UpdateToolbar();
        
        ShowWindow( appVars.hwndMainFrame, SW_SHOWNORMAL );
        SetWindowPos(appVars.hwndMainFrame, HWND_TOP, 0, 0, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    }
}


void gui_not_idle(int flag)
{
    if (flag)
        Idle = FALSE;
    else
        Idle = TRUE;
}

char *gui_translate_errorcode(int error)
{
    static char def[32];
    char *result = def;
    struct ErrorDef *ed = WinSockErrors;

    sprintf(def, "<%d>", error);

    for (;;)
    {
        if (ed->ErrorVal == -1) break;

        if (ed->ErrorVal == error)
        {
            result = ed->ErrorName;
            break;
        }
        ed++;
    }

    return result;
}

static char username_buffer[256];
static char password_buffer[256];

int gui_getpassword(char **username, char **password)
{
    int ret = 0;

    if (!Batchmode)
    {
        if (*username != NULL) strncpy(username_buffer, *username, sizeof(username_buffer)-1);
        username[255]=0;
        if (*password != NULL) strncpy(password_buffer, *password, sizeof(password_buffer)-1);
        password[255]=0;
    
        if (DoEnterPasswordDialog( appVars.hInstance, appVars.hwndMainFrame ) == IDOK)
        {
            *username = username_buffer;
            *password = password_buffer;
            ret = 1;
        }
    }
    else
    {
        /* in batch mode, password must be given on command line */
        if (*username == NULL && *password == NULL)
        {
            /* cancel the authorization of no username/password given */
            ret = 0;
        }
        else
        {
            ret = 1;
        }
    }

    return ret;
}

static char proxy_buffer[512];

int gui_getproxy(char **proxy)
{
    int ret = 0;

    /* do not override command line proxy parameter */
    if (*proxy == NULL)
    {
        LONG retval;
        HKEY hkeyURLList;
        DWORD dwResult;
        
        retval = RegCreateKeyEx(APPREGKEY_ROOT,
            APPREGKEY_BASE,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hkeyURLList,
            &dwResult);
        
        
        if (retval != ERROR_SUCCESS)
        {
            gui_criticalerror("RegCreateKeyEx failed: %d\n", retval);
        }
        else
        {
            char buffer[512];
            DWORD dwType;
            DWORD dwSize;
                
            dwSize = sizeof(buffer);
            retval = RegQueryValueEx( hkeyURLList,
                "ProxyServer",
                0,
                &dwType,
                buffer,
                &dwSize );
            
            if (retval == ERROR_SUCCESS)
            {
                if (dwType == REG_SZ)
                {
                    strncpy(proxy_buffer, buffer, sizeof(proxy_buffer)-1);
                    proxy_buffer[sizeof(proxy_buffer)-1] = 0;

                    /* return proxy only if buffer not empty */
                    if (strcmp(proxy_buffer, ""))
                    {
                        *proxy = proxy_buffer;
                        ret = 1;
                    }
                }
                RegCloseKey(hkeyURLList);
            }
        }
    }
    return ret;
}

/*------------------------ COMMON CONTROLS STUFF ----------------------------*/

//
// InitMyControls
//
HRESULT InitMyControls(void)
{
    HRESULT hr;
    DWORD major;
    DWORD minor;
    BOOL too_old = FALSE;
#define MIN_MAJOR 4
#define MIN_MINOR 72

    GetComCtlVersion(&major, &minor);

    if (major < MIN_MAJOR) too_old = TRUE;
    else
        if (major == MIN_MAJOR && minor < MIN_MINOR) too_old = TRUE;

    if (too_old)
    {
        char Buffer[200];

        sprintf(Buffer, "Your commctl32.dll is too old!\n"
                        "You have version: %d.%d\n"
                        "Required is at least version %d.%d",
                        major, minor, MIN_MAJOR, MIN_MINOR);

        MessageBox( appVars.hwndMainFrame, Buffer, appVars.szAppName,
                    MB_APPLMODAL | MB_OK | MB_ICONERROR );

        hr = S_FALSE;
    }
    else
    {
        INITCOMMONCONTROLSEX icex;

        icex.dwSize  = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_WIN95_CLASSES;

        InitCommonControlsEx(&icex);

        hr = S_OK;
    }
    return hr;
} // InitMyControls


//
// GetComCtlVersion
//
HRESULT GetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
{
    HINSTANCE   hComCtl;

    if(   IsBadWritePtr(pdwMajor, sizeof(DWORD)) ||
        IsBadWritePtr(pdwMinor, sizeof(DWORD)))
        return E_INVALIDARG;

    //load the DLL
    hComCtl = LoadLibrary(TEXT("comctl32.dll"));

    if(hComCtl)
    {
        HRESULT           hr = S_OK;
        DLLGETVERSIONPROC pDllGetVersion;

        /*
        You must get this function explicitly because earlier versions of the DLL
        don't implement this function. That makes the lack of implementation of the
        function a version marker in itself.
        */
        pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hComCtl, TEXT("DllGetVersion"));

        if(pDllGetVersion)
        {
            DLLVERSIONINFO    dvi;

            ZeroMemory(&dvi, sizeof(dvi));
            dvi.cbSize = sizeof(dvi);

            hr = (*pDllGetVersion)(&dvi);

            if(SUCCEEDED(hr))
            {
                *pdwMajor = dvi.dwMajorVersion;
                *pdwMinor = dvi.dwMinorVersion;
            }
            else
            {
                hr = E_FAIL;
            }
        }
        else
        {
        /*
        If GetProcAddress failed, then the DLL is a version previous to the one
        shipped with IE 3.x.
            */
            *pdwMajor = 4;
            *pdwMinor = 0;
        }

        FreeLibrary(hComCtl);

        return hr;
    }

    return E_FAIL;

} // GetComCtlVersion


/*----------------------- STATUS BAR COMMON CONTROL -------------------------*/

//
// InitStatusbar
//
BOOL InitStatusbar( HINSTANCE hInstance, HWND hwndMainFrame )
{
    BOOL success = FALSE;

    if (hwndStatusbar = DoCreateStatusbar(hwndMainFrame, IDR_STATUSBAR, hInstance, StatusDefinitionArray))
    {
        ShowWindow( hwndStatusbar, SW_SHOW );
        UpdateWindow( hwndStatusbar );
        success = TRUE;
    }

    return success;
} // InitStatusbar


//
// SetStatusText
//
void SetStatusText(int partno, int drawmode, COLORREF cref, LPSTR text,...)
{
    va_list arglist;
    va_start(arglist, text);

    SetStatusTextArgs(partno, drawmode, cref, text, arglist);

    va_end(arglist);

} // SetStatusText


//
// StatusTimerFunc
//
void CALLBACK StatusTimerFunc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (uMsg == WM_TIMER && idEvent == StatusTimer)
    {
        StatusTimerCount--;
        if (StatusTimerCount%2 == 0)
            SendMessage(hwndStatusbar, SB_SETBKCOLOR, (WPARAM) 0,  (LPARAM) CLR_DEFAULT);
        else
            SendMessage(hwndStatusbar, SB_SETBKCOLOR, (WPARAM) 0,  (LPARAM) StatusTimerCref);
    }

    if (StatusTimerCount == 0)
        KillTimer( appVars.hwndMainFrame, StatusTimer );
} // StatusTimerFunc


//
// SetStatusTextArgs
//
void SetStatusTextArgs(int partno, int drawmode, COLORREF cref, LPSTR text, void *args)
{
    if (hwndStatusbar != NULL)
    {
        char Buffer[1024];
        vsprintf(Buffer, text, args);

        // Tell the status bar to create the window parts.
        if (cref != -1)
        {
            SendMessage(hwndStatusbar, SB_SETBKCOLOR, (WPARAM) 0,  (LPARAM) cref);

            if (StatusTimer != 0)
            {
                KillTimer( appVars.hwndMainFrame, StatusTimer);
                StatusTimerCount = 0;
            }

            if (cref != CLR_DEFAULT)
            {
                StatusTimerCref = cref;
                StatusTimerCount = 5;
                StatusTimer = SetTimer( appVars.hwndMainFrame, ID_STATUSTIMER, 200, StatusTimerFunc);
            }
        }
        SendMessage(hwndStatusbar, SB_SETTEXT, (WPARAM) partno | drawmode,  (LPARAM) Buffer);
        ShowWindow( hwndStatusbar, SW_SHOW );
        UpdateWindow( hwndStatusbar );
    }
} // SetStatusTextArgs


//
// CalcStatusSize
//
void CalcStatusSize ( SIZE *pSize, int *array )
{
    int i;
    int nParts;
    int *ptr;
    int mintotal = 0;

    nParts = *array;
    ptr = array+1;
    for (i = 0; i < nParts; i++)
    {
        int wmin = *ptr++;
        ptr++;
        mintotal += wmin;
    }

    pSize->cx = mintotal;
    pSize->cy = 20;

    if (hwndStatusbar != NULL)
    {
        RECT statRect;
        GetWindowRect(hwndStatusbar, &statRect);
        pSize->cy = statRect.bottom-statRect.top+1;
    }
}

//
// AdjustStatusbar
//
void AdjustStatusbar(HWND hwndStatus, HWND hwndParent, int *array)
{
    int nParts;

    RECT rcClient;
    HLOCAL hloc;
    LPINT lpParts;
    int i, x, nWidth;
    int *ptr;
    int mintotal = 0;
    int maxtotal = 0;
    int bendtotal = 0;
    int numunlim = 0;
    int weight = 0;
    int surplus, maxsurplus;

    // Get the coordinates of the parent window's client area.
    GetClientRect(hwndParent, &rcClient);

    nWidth = rcClient.right-rcClient.left+1;

    nParts = *array;
    ptr = array+1;
    for (i = 0; i < nParts; i++)
    {
        int wmin = *ptr++;
        int wmax = *ptr++;

        if (wmax!=-1)
        {
            mintotal += wmin;
            maxtotal += wmax;
            bendtotal += (wmax-wmin);
        }
        else
        {
            mintotal +=   wmin;
            maxtotal += 2*wmin;
            bendtotal +=  wmin;
            numunlim++;
        }
    }

    // Allocate an array for holding the right edge coordinates.
    hloc = LocalAlloc(LHND, sizeof(int) * nParts);
    lpParts = LocalLock(hloc);

    // Calculate the right edge coordinate for each part, and
    // copy the coordinates to the array.
    ptr = array+1;
    x = 0;

    surplus    = nWidth - mintotal;
    if (surplus<0) surplus=0;
    maxsurplus = nWidth - maxtotal;
    if (maxsurplus<0) maxsurplus=0;

    for (i = 0; i < nParts; i++)
    {
        int wmin = *ptr++;
        int wmax = *ptr++;
        int bend;
        int w = 0;

        if (wmax!=-1)
            bend = wmax-wmin;
        else
            bend = wmin;

        w = wmin + (surplus*bend/bendtotal);
        if (w > 2*wmin) w = 2*wmin;

        if (wmax==-1)
            w += maxsurplus / numunlim;

        if (w < wmin) w = wmin;
        if (wmax!=-1)
            if (w > wmax) w = wmax;

        x+= w;

        *(lpParts+i) = x;
    }

    // Tell the status bar to create the window parts.
    SendMessage(hwndStatus, SB_SETPARTS, (WPARAM) nParts, (LPARAM) lpParts);

    // Free the array, and return.
    LocalUnlock(hloc);
    LocalFree(hloc);

} // AdjustStatusbar


// DoCreateStatusbar - creates a status bar and divides it into
//                     the specified number of parts.
// Returns the handle to the status bar.
//        hwndParent - parent window for the status bar.
//         nStatusID - child window identifier.
//             hinst - handle to the application instance.
//            nParts - number of parts into which to divide the status bar.
HWND DoCreateStatusbar(HWND hwndParent, int nStatusID,
                       HINSTANCE hinst, int *array)
{
    HWND hwndStatus;

    // Create the status bar.
    hwndStatus = CreateWindowEx(
        0,                       // no extended styles
        STATUSCLASSNAME,         // name of status bar class
        (LPCTSTR) NULL,          // no text when first created
        SBARS_SIZEGRIP |         // includes a sizing grip
        WS_VISIBLE | WS_CHILD,   // creates a child window
        0, 0, 0, 0,              // ignores size and position
        hwndParent,              // handle to parent window
        (HMENU) nStatusID,       // child window identifier
        hinst,                   // handle to application instance
        NULL);                   // no window creation data

    AdjustStatusbar(hwndStatus, hwndParent, array);
    return hwndStatus;

} // DoCreateStatusbar



/*-------------------------- MESSAGE BOX ROUTINES ---------------------------*/

//
// DbgAssert
//
// Displays a message box if the condition evaluated to FALSE
//
void DbgAssert(const char *pCondition, const char *pFileName, int iLine)
{
    int MsgId;
    char szInfo[1024];

    wsprintf(szInfo, TEXT("%s \nAt line %d of %s"),pCondition, iLine, pFileName);
    MsgId = MessageBox(NULL, szInfo, TEXT("ASSERT Failed"),
                           MB_SYSTEMMODAL |
                           MB_ICONHAND |
                           MB_ABORTRETRYIGNORE);
    switch (MsgId)
    {
        case IDABORT:           // Kill the application

            FatalAppExit(FALSE, TEXT("Application terminated"));
            break;

        case IDRETRY:           // Break into the debugger
            DebugBreak();
            break;

        case IDIGNORE:          // Ignore assertion continue executing
            break;
    }
} // DbgAssert


//
// ReallyQuitMessageBox
//
// Ask the user wheter or not to quit
//
UINT ReallyQuitMessageBox( void )
{
    UINT retval;

    if (Transmitting == FALSE)
    {
        /* don't ask if there is no transmission in progress */
        retval = IDYES;
    }
    else
    {
        char szStr[ nMaxResourceStrSize ];

        LoadString( appVars.hInstance, IDS_REALLY_QUIT, szStr, nMaxResourceStrSize );
        retval = MessageBox( appVars.hwndMainFrame, szStr, appVars.szAppName,
                             MB_APPLMODAL | MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION );
    }
    return retval;

} // ReallyQuitMessageBox


//
// PlayerMessageBox
//
// Load and display an error message
//
void PlayerMessageBox( UINT nResource )
{
    char szStr[ nMaxResourceStrSize ];

    LoadString( appVars.hInstance, nResource, szStr, nMaxResourceStrSize );
    MessageBox( appVars.hwndMainFrame, szStr, appVars.szAppName,
                MB_APPLMODAL | MB_OK | MB_ICONEXCLAMATION );

} // PlayerMessageBox


//
// OnShowReadme
//
void OnShowReadme()
{
    char szFileName[ _MAX_PATH ];
    char *szTitle;
    SHELLEXECUTEINFO sei;
    BOOL ret;
    
    // Work out the full path name
    if (GetFullPathName( appVars.szProgramExecutable, _MAX_PATH, szFileName, &szTitle ) > 0)
    {
        strcpy( szTitle, "README.TXT");
        
        memset(&sei, 0, sizeof(sei));
        sei.cbSize = sizeof(sei);

        sei.fMask = SEE_MASK_FLAG_NO_UI;
        sei.hwnd = appVars.hwndMainFrame;
        sei.lpVerb = "open";
        sei.lpParameters = NULL;
        sei.lpDirectory = NULL;
        sei.lpFile = szFileName;
        sei.nShow = SW_SHOW;
        
        ret = ShellExecuteEx(&sei);
        
        if (ret == FALSE)
        {
            if ((long)GetLastError() == ERROR_FILE_NOT_FOUND)
                gui_criticalerror("Someone deleted the README.TXT\n"
                                  "file from the program directory!\n");
            else
                gui_criticalerror("Cannot show the README.TXT file for some strange reason!\n");
        }
    }
}

                
/*-------------------------- COMMAND HANDLING -------------------------------*/

//
// ProcessCommand
//
// Process a WM_COMMAND message to the main window
//
long ProcessCommand( HWND hwnd, UINT wParam, LONG lParam )
{
    switch( wParam ){
        case ID_URL_OPEN:
            DoOpenURLDialog( appVars.hInstance,hwnd );
            break;

        case ID_FILE_OPEN:
            if (OpenMediaFile( hwnd, NULL ))
                OnMediaPlay( );
            break;

        case ID_FILE_EXIT:
            PostMessage( appVars.hwndMainFrame, WM_CLOSE, 0, 0 );
            break;

        case ID_MEDIA_PLAY:
            OnMediaPlay( );
            break;

        case ID_MEDIA_PAUSE:
            OnMediaPause( );
            break;

        case ID_MEDIA_STOP:
            OnMediaStop(FALSE, TRUE);
            break;

        case ID_MEDIA_EJECT:
            DeleteContents();
            break;

        case ID_STREAM_PREVIEW:
            if (strcmp( StreamFilename, "" ))
            {
                if (OpenMediaFile( hwnd, StreamFilename ))
                {
                    Previewing = TRUE;
                    OnMediaPlay( );
                }
            }
            break;

        case ID_STREAM_CANCEL:
            gui_seterror("aborting transfer...");
            gui_abort();
            PostMessage(hwnd, WM_COMMAND, WM_QUIT, 0);
            break;

        case ID_SETTINGS_REGISTERFILETYPES:
            OnRegisterFileTypes();
            break;

        case ID_SETTINGS_UNREGISTERFILETYPES:
            OnUnregisterFileTypes();
            break;

        case ID_HELP_ABOUT:
            DoAboutDialog( appVars.hInstance,hwnd );
            break;

        case ID_PROGRAM_ARGUMENTS:
            Usage(appVars.szProgramExecutable, ShowUsage);
            break;

        case ID_SHOW_README:
            OnShowReadme();
            break;

        case ID_PROXY_SERVER:
            DoProxyConfigurationDialog( appVars.hInstance, hwnd );
            break;

        default:
            return DefWindowProc( hwnd, WM_COMMAND, wParam, lParam );
    }
    return (LRESULT) 0;

} // ProcessCommand

/*------------------------- WINDOW SIZE CALCULATIONS ------------------------*/

//
// OnGetMinMaxInfo
//
// Sets the minimum size of the main window and the maximum height
//
void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
    RECT rectRequired;
    SIZE sizeToolbar;
    SIZE sizeStatus;

    // Our client area is going to be the toolbar, so find our its size
    CalcToolbarSize( &sizeToolbar );

    rectRequired.left = rectRequired.top = 0;
    rectRequired.right = sizeToolbar.cx;
    rectRequired.bottom = sizeToolbar.cy;

    CalcStatusSize( &sizeStatus, StatusDefinitionArray );

    if (sizeStatus.cx > rectRequired.right)
        rectRequired.right = sizeStatus.cx;

    rectRequired.bottom += sizeStatus.cy;

    // Take into account the menu, caption and thick frame
    AdjustWindowRect( &rectRequired, WS_CAPTION|WS_THICKFRAME, TRUE );

    // Set the min/max sizes
    lpMMI->ptMinTrackSize.x = rectRequired.right - rectRequired.left;
    lpMMI->ptMinTrackSize.y = rectRequired.bottom - rectRequired.top;

} // OnGetMinMaxInfo


/*------------------------- MAIN WINDOW PROCEDURE ---------------------------*/

typedef BOOL (FAR WINAPI *GradientFillFunction)(HDC,PTRIVERTEX,ULONG,PVOID,ULONG,ULONG);
GradientFillFunction GradientFillPtr;

//
// MainFrameProc
//
// Handles the message sent to the main window
//

long FAR PASCAL MainFrameProc( HWND hwnd, UINT message, UINT wParam, LONG lParam)
{
    DRAWITEMSTRUCT *dis;

    /******************************************************/
    /*      Handle inter-process communications here      */
    /******************************************************/

    /* Answer the probe-message with our current status. */
    /* Return MAGIC_COOKIE if we are able to handle      */
    /* other tasks                                       */
    if (message == WM_APPMSG)
    {
        if (Idle == TRUE)
        {
            Idle = FALSE;
            return (LRESULT) MAGIC_COOKIE;
        }
        else
        {
            return (LRESULT) 0;
        }
    }

    /* This message is only received when we just answered */
    /* the probe message with a MAGIC_COOKIE               */
    /* Now we will get the command line from another ASF-  */
    /* Recorder process                                    */

    if (message == WM_COPYDATA)
    {
        COPYDATASTRUCT *cds = (COPYDATASTRUCT*)lParam;

        if (cds != NULL)
        {            
            if (cds->dwData == MAGIC_COOKIE)
            {
                LPTSTR cmdline;
                unsigned char buffer[1024];
                int argc_bak = argc;      /* ParseCommandLine() operates          */
                char **argv_bak = argv;   /* on global variables (backup needed!) */
                
                argc = 0;                 /* simulate "empty" command line */
                argv = NULL;   

                cmdline = cds->lpData;    /* copy the data from the WM_COPYDATA */
                strcpy(buffer, cmdline);  /* message */
                
                if (ParseCommandLine(buffer))
                {
                    /* tell the other process that we are now */
                    /* processing its command line */
                    ReplyMessage((LRESULT) MAGIC_COOKIE);

                    ShowWindow( appVars.hwndMainFrame, SW_SHOWNORMAL );
                    SetWindowPos(appVars.hwndMainFrame, HWND_TOP, 0, 0, 0, 0,
                                 SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

                    /* now process this command line */
                    main_function(argc, argv);
                }
                FreeCommandLine();
                
                /* restore the previous command line        */
                /* (needed for FreeCommandLine() in WinMain */
                argc = argc_bak;
                argv = argv_bak;
            }
        }

        /* return to idle state (can accept other command lines now) */
        Idle = TRUE;
        return (LRESULT) 0;
    }

    switch( message )
    {
    case WM_CLOSE:
        if (ReallyQuitMessageBox() == IDYES)
        {
            if (DestroyWindow ( appVars.hwndMainFrame ))
            {
                appVars.hwndMainFrame = NULL;
                hwndAboutBox = NULL;
                hwndOpenURLDialog = NULL;
                hwndStatusbar = NULL;
                toolbar.hwndPlayButton = NULL;
                toolbar.hwndPauseButton = NULL;
                toolbar.hwndStopButton = NULL;
                toolbar.hwndPreviewButton = NULL;
                toolbar.hwndCancelButton = NULL;
                hwndTrackbar = NULL;
            }
        }
        break;

    case WM_DESTROY:
        gui_abort();
        PostQuitMessage( 0 );
        break;

    case WM_GETMINMAXINFO:
        OnGetMinMaxInfo( (MINMAXINFO FAR *) lParam );
        break;

    case WM_ERASEBKGND:
        {
            RECT rc;
            HDC hdc;
            SIZE sizeStatus;

            HMODULE msimg32;

            hdc = (HDC) wParam;
            GetClientRect(hwnd, &rc);

            /* try to load msimg32.dll (Win98, Win2000) */
            if ((msimg32 = LoadLibrary("msimg32.dll")) != NULL)
	        {
                TRIVERTEX          vert[4] ;
                GRADIENT_TRIANGLE  gTri[2];

	            GradientFillPtr = (GradientFillFunction)GetProcAddress(msimg32, "GradientFill");

                CalcStatusSize( &sizeStatus, StatusDefinitionArray );
                rc.bottom -= (sizeStatus.cy-1);

                vert [0] .x      = rc.left;
                vert [0] .y      = rc.top;
                vert [0] .Red    = 0xff00;
                vert [0] .Green  = 0xff00;
                vert [0] .Blue   = 0x8000;
                vert [0] .Alpha  = 0x0000;

                vert [1] .x      = rc.right;
                vert [1] .y      = rc.top;
                vert [1] .Red    = 0x6000;
                vert [1] .Green  = 0x6000;
                vert [1] .Blue   = 0x6000;
                vert [1] .Alpha  = 0x0000;

                vert [2] .x      = rc.right;
                vert [2] .y      = rc.bottom;
                vert [2] .Red    = 0x8000;
                vert [2] .Green  = 0x4000;
                vert [2] .Blue   = 0x0000;
                vert [2] .Alpha  = 0x0000;

                vert [3] .x      = rc.left;
                vert [3] .y      = rc.bottom;
                vert [3] .Red    = 0x6000;
                vert [3] .Green  = 0x6000;
                vert [3] .Blue   = 0x6000;
                vert [3] .Alpha  = 0x0000;

                gTri[0].Vertex1 = 0;
                gTri[0].Vertex2 = 1;
                gTri[0].Vertex3 = 2;

                gTri[1].Vertex1 = 0;
                gTri[1].Vertex2 = 3;
                gTri[1].Vertex3 = 2;

                (*GradientFillPtr)(hdc, vert,4, gTri, 2, GRADIENT_FILL_TRIANGLE);

                FreeLibrary(msimg32);
            }
            else
            {
                /* basic backfill functions for users not having the msimg32.dll */
                HBRUSH brush = CreateSolidBrush(RGB(0xc0,0x80,0x00));
                FillRect(hdc, &rc, brush);
                DeleteObject(brush);
            }
        }
        return (LRESULT) 1;
        break;

    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT FAR *) lParam;
        if (( dis->CtlType == ODT_BUTTON ) &&
            ( dis->CtlID == ID_MEDIA_PLAY     ||
              dis->CtlID == ID_MEDIA_PAUSE    ||
              dis->CtlID == ID_MEDIA_STOP)    ||
              dis->CtlID == ID_STREAM_PREVIEW ||
              dis->CtlID == ID_STREAM_CANCEL    )
        {
            DrawButton( appVars.hInstance, (DRAWITEMSTRUCT FAR *) lParam );
            return (LRESULT) 1;
        }
        break;

    case WM_INITMENUPOPUP:
        if( lParam == 1 )
        {          // Media popup menu
            EnableMenuItem( (HMENU) wParam, ID_MEDIA_PLAY,     CanPlay()       ? MF_ENABLED : MF_GRAYED );
            EnableMenuItem( (HMENU) wParam, ID_MEDIA_PAUSE,    CanPause()      ? MF_ENABLED : MF_GRAYED );
            EnableMenuItem( (HMENU) wParam, ID_MEDIA_STOP,     CanStop()       ? MF_ENABLED : MF_GRAYED );
            EnableMenuItem( (HMENU) wParam, ID_MEDIA_EJECT,    IsInitialized() ? MF_ENABLED : MF_GRAYED );
        }
        else
        {
            if( lParam == 2 )
            {          // Stream popup menu
                EnableMenuItem( (HMENU) wParam, ID_STREAM_PREVIEW,  CanPreview() ? MF_ENABLED : MF_GRAYED );
                EnableMenuItem( (HMENU) wParam, ID_STREAM_CANCEL,   Transmitting ? MF_ENABLED : MF_GRAYED );
            }
            else
            {
                return DefWindowProc( hwnd, message, wParam, lParam );
            }
        }
        break;

    case WM_SIZE:
        SendMessage(hwndStatusbar, WM_SIZE, wParam, lParam);
        AdjustStatusbar(hwndStatusbar, appVars.hwndMainFrame, StatusDefinitionArray);
        AdjustTrackbar(hwndTrackbar, appVars.hwndMainFrame );
        return DefWindowProc( hwnd, message, wParam, lParam );
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint( hwnd, &ps );

            EndPaint( hwnd, &ps );
        }
        break;

    case WM_COMMAND:
        return ProcessCommand( hwnd, wParam, lParam );
        break;

    case WM_NOTIFY:
        {
            int id = wParam;
            LPNMHDR nmhdr = (LPNMHDR)lParam;

            if (nmhdr->hwndFrom == hwndTrackbar)
            {
                if (nmhdr->code == NM_RELEASEDCAPTURE)
                {
                    int pos;
                    pos = positionTrackbar;
                    SendMessage(hwndTrackbar, TBM_SETPOS, TRUE, pos);
                    SetCurrentPosition((REFTIME)((REFTIME)pos/10000 * IMPTotalTime));
                }
            }
        }
//        return DefWindowProc( hwnd, message, wParam, lParam );
        break;

    case WM_HSCROLL:
        {
            HWND hwndFrom = (HWND)lParam;
            if (hwndFrom == hwndTrackbar)
            {
                int pos  = HIWORD(wParam);
                int code = LOWORD(wParam);

                switch(code)
                {
                    case TB_THUMBTRACK:
                        {
                            unsigned int timecode;
                            char *timecodestring;

                            if (Previewing)
                            {
                                int prevpos = pos;
                                int min=SendMessage(hwndTrackbar, TBM_GETSELSTART, 0, 0);
                                int max=SendMessage(hwndTrackbar, TBM_GETSELEND,   0, 0);
                                if (pos < min) pos = min;
                                if (pos > max) pos = max;
                                if (pos != prevpos) SendMessage(hwndTrackbar, TBM_SETPOS, TRUE, pos);
                            }

                            /* save the current position of the trackbar slider */
                            positionTrackbar = pos;

                            if (!Transmitting)
                            {
                                timecode = (unsigned int)((float)pos/10000 * (1000*IMPTotalTime));
                                timecodestring = createtimestring(timecode);
                                SetStatusText(STAT_TIMECODE, 0, -1, "T: %s", timecodestring);
                            }

                            if (TrackbarDragging == FALSE)
                                OnMediaSeeking(TRUE);

                            TrackbarDragging = TRUE;
                        }
                        break;

                    case TB_THUMBPOSITION:
                        {
                            /* save the position of the trackbar slider /*
                            /* when we released the mouse button */
                            positionTrackbar = SendMessage(hwndTrackbar, TBM_GETPOS, 0, 0);

                            if (TrackbarDragging == TRUE)
                                OnMediaSeeking(FALSE);

                            TrackbarDragging = FALSE;
                        }
                        break;

                    default:
                        break;
                }
            }
        }
//        return DefWindowProc( hwnd, message, wParam, lParam );
        break;

    /* handle drag & drop */
    case WM_DROPFILES:
        {
            HANDLE hDrop = (HANDLE) wParam;
            UINT numfiles;
            char buffer[512];
            unsigned char *dotptr, *tmpptr;

            numfiles = DragQueryFile(hDrop, 0xffffffff, buffer, sizeof(buffer));

            if (numfiles > 1)
            {
                PlayerMessageBox( IDS_DROP_ONLY_ONE );
            }

            if (numfiles > 0)
            {
                DragQueryFile(hDrop, 0, buffer, sizeof(buffer));
            }

            DragFinish(hDrop);

            /* search for filename extension */
            for (dotptr = buffer+strlen(buffer), tmpptr = buffer; (tmpptr = strchr(tmpptr, '.')) != NULL ; dotptr = tmpptr++);

            /* search for redirection file name extension */
            if ( (!stricmp(dotptr, ".asx")) ||
                 (!stricmp(dotptr, ".wax")) ||
                 (!stricmp(dotptr, ".wvx")) ||
                 (!stricmp(dotptr, ".wmx"))   )
            {
                if (Transmitting)
                {
                    PlayerMessageBox( IDS_TRANSMISSION_RUNNING );
                }
                else
                {
                    /* call main_function() to process redirection file */
                    unsigned char *(my_argv[2]);

                    int my_argc = 2;
                    my_argv[0] = appVars.szProgramExecutable;
                    my_argv[1] = buffer;

                    main_function(my_argc, (char**)my_argv);
                }
            }
            else
            {
                /* try to play file as media file */
                if (OpenMediaFile( hwnd, buffer ))
                    OnMediaPlay( );
            }
        }
        break;

    default:
        return DefWindowProc( hwnd, message, wParam, lParam );
    }

    return (LRESULT) 0;

} // MainFrameProc


/*---------------------- INITIALIZATION/CLEANUP ROUTINES --------------------*/

//
// InitApplication
//
BOOL InitApplication()
{
    strcpy( appVars.szAppName, APP_NAME );

    // Filter interface initialize?
    if( SUCCEEDED( CoInitialize( NULL )))
        return TRUE;

    return FALSE;

} // InitApplication


//
// UnInitApplication
//
void UnInitApplication()
{
    CoUninitialize( );

} // UnInitApplication


//
// InitInstance
//
// Set the specific instance data and register our main
// window class if it has not been registered already
//
BOOL InitInstance( HANDLE hInstance, HANDLE hPrevInstance )
{
    appVars.hInstance = hInstance;

    if(!hPrevInstance)
    {
        WNDCLASS wndClass;

        wndClass.style          = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc    = MainFrameProc;
        wndClass.cbClsExtra     = 0;
        wndClass.cbWndExtra     = 0;
        wndClass.hInstance      = appVars.hInstance;
        wndClass.hIcon          = LoadIcon( appVars.hInstance, MAKEINTRESOURCE( IDI_APPLICATION_ICON ));
        wndClass.hCursor        = LoadCursor( NULL, IDC_ARROW );
        wndClass.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND + 1);
        wndClass.lpszMenuName   = MAKEINTRESOURCE( IDM_MAINFRAME );
        wndClass.lpszClassName  = appVars.szAppName;

        RegisterClass( &wndClass );

        if ( InitMyControls() == S_OK )
        {
            return TRUE;
        }

        return FALSE;

    }

    return TRUE;

} // InitInstance


//
// InitMainFrame
//
// Create our main window
//
BOOL InitMainFrame( int nCmdShow )
{
    const DWORD Styles = (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN) &~ WS_MAXIMIZEBOX;
    char szTitle[ 30 ];

    strcpy( szTitle, APP_NAME );
    strcat( szTitle, UNTITLED_STRING );

    appVars.hwndMainFrame =
        CreateWindowEx( WS_EX_ACCEPTFILES,
                      appVars.szAppName,    // Our class name
                      szTitle,              // Window title
                      Styles,               // It's styles
                      CW_USEDEFAULT,        // No x position
                      CW_USEDEFAULT,        // And no y either
                      0, 65,                // Initial sizes
                      NULL,                 // No parent window
                      NULL,                 // And no menu
                      appVars.hInstance,    // App instance
                      NULL);                // Creation data

    DragAcceptFiles( appVars.hwndMainFrame, TRUE);

    ShowWindow( appVars.hwndMainFrame, nCmdShow );
    UpdateWindow( appVars.hwndMainFrame );
    return TRUE;

} // InitMainFrame

/*-------------------------- BUSY POINTER ROUTINE ---------------------------*/

int BusyNest = 0;

//
// SetBusy
//
void SetBusy(BOOL flag)
{
    if (flag == TRUE)
    {
        BusyNest++;
        if (BusyNest > 0) SetCursor( LoadCursor( NULL, IDC_WAIT ) );
    }
    else
    {
        if (BusyNest > 0) BusyNest--;

        if (BusyNest == 0) SetCursor( LoadCursor( NULL, IDC_ARROW ) );
    }

} // SetBusy


/*-------------------- MAIN EVENT LOOP/MESSAGE HANDLING ---------------------*/

//
// DoMainLoop
//
// Main message loop
//
int DoMainLoop(int network_mask)
{
    MSG msg;

    BOOL network_event = FALSE;
    int network_retval = 0;

    // Message loop lasts until we get a WM_QUIT message
    // Upon which we shall return from the function

    // Message loop also exits when network activity is
    // dectected (only if network is set to TRUE)

    for (;;)
    {
        // Read all of the messages in this next loop
        // removing each message as we read it

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == 1)
        {
            if (msg.message == WM_QUIT)
                return msg.wParam;

            if (hwndAboutBox != NULL)
                if (IsDialogMessage(hwndAboutBox, &msg)) continue;

            if (hwndOpenURLDialog != NULL)
                if (IsDialogMessage(hwndOpenURLDialog, &msg)) continue;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }


        // The following code waits for the arrival of new messages, i.e.
        // it puts the task to sleep. This is a non-desired behaviour if
        // we must react to a network event.

        if (network_event == FALSE)
        {
            HANDLE  ahObjects[10];       // Handles that need to be waited on
            int cObjects = 0;                // Number of objects that we have
            int cGraphIndex = -1;
            int cNetworkIndex = -1;

            ahObjects [cObjects] = GetGraphEventHandle();
            if (ahObjects[cObjects] != NULL)
            {
                cGraphIndex = cObjects;
                cObjects++;
            }

            if (NetworkEvent != WSA_INVALID_EVENT)
            {
                ahObjects[cObjects] = NetworkEvent;
                cNetworkIndex = cObjects;
                cObjects++;
            }

            if( cObjects == 0 )
            {
                WaitMessage();
            }
            else
            {
                DWORD Result;

                // Wait for any message or a graph notification

                Result = MsgWaitForMultipleObjects( cObjects,
                                                    ahObjects,
                                                    FALSE,
                                                    INFINITE,
                                                    QS_ALLINPUT );

                // Have we received an event notification

                if( Result != (WAIT_OBJECT_0 + cObjects) )
                {
                    if (cGraphIndex != -1)
                    {
                        if( Result == WAIT_OBJECT_0 + cGraphIndex)
                        {
                            OnGraphNotify();
                        }
                    }

                    if (cNetworkIndex != -1)
                    {
                        if( Result == WAIT_OBJECT_0 + cNetworkIndex)
                        {
                            WSANETWORKEVENTS wsane;
                            if (WSAEnumNetworkEvents(NetworkSocket, NetworkEvent, &wsane) == SOCKET_ERROR)
                            {
                                gui_criticalerror("WSAEnumNetworkEvents() failed! Error code: %d\n", WSAGetLastError());
                            }
                            else
                            {
                                if (wsane.lNetworkEvents & FD_CONNECT)
                                {
                                    network_retval = wsane.iErrorCode[FD_CONNECT_BIT];
                                }
                                else
                                {
                                    network_retval = 0;
                                }
                                network_event = TRUE;
                            }
                        }
                    }
                }
            }
        }

        if (network_event == TRUE)
            break;

    }

    // if we end up here, we must have received a network event
    return network_retval;

} // DoMainLoop


/*--------------------------- PSEUDO WINMAIN CODE ---------------------------*/

//
// PseudoWinMain
//
// former WinMain code. Now called from real WinMain
//
int PASCAL PseudoWinMain( HINSTANCE hInstance,
                          HINSTANCE hPrevInstance,
                          LPSTR lpszCmdParam,
                          int nCmdShow )
{
    UINT nReturn = 0;

    // Initialise COM and the application
    if ( InitApplication() == FALSE ) return 0;

    if( InitInstance( hInstance, hPrevInstance ) &&
        InitMainFrame( nCmdShow ) &&
        InitToolbar( hInstance, appVars.hwndMainFrame ) &&
        InitStatusbar( hInstance, appVars.hwndMainFrame ) &&
        InitTrackbar( hInstance, appVars.hwndMainFrame ) &&
        InitMedia( ) &&
        InitFileOpenDialog( appVars.hwndMainFrame ) &&
        InitFileSaveDialog( appVars.hwndMainFrame ))
    {
        nReturn = 1;
    }

    return nReturn;

} // WinMain


//
// EndOfWinMain
//
// former end part of WinMain code. Now called from real WinMain
//
void EndOfWinMain(void)
{
    // Stop the graph if we can
    if( CanStop() )
            OnMediaStop(TRUE, FALSE);

    // Release the filter graph
    DeleteContents();

    UnInitApplication();

} // EndOfWinMain


/*--------------------------- ABOUT DIALOG BOX ------------------------------*/


// Simply handles the Help..About dialog box

//
// AboutDlgProc
//
BOOL FAR PASCAL AboutDlgProc( HWND hwnd, UINT message, UINT wParam, LONG lParam )
{
    DRAWITEMSTRUCT *dis;

    switch( message )
    {
        case WM_INITDIALOG:
           return (LRESULT) 1;

        case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT FAR *) lParam;
        if (( dis->CtlType == ODT_STATIC ) &&
            ( dis->CtlID == IDC_ASFRECORDER_BITMAP ))
        {
            HDC hSourceDC = CreateCompatibleDC( NULL );
            HGDIOBJ loadedbitmap;
            HGDIOBJ hgdiOldBitmap;
            
            loadedbitmap = (HGDIOBJ) LoadImage( appVars.hInstance, MAKEINTRESOURCE( IDB_ASFRECORDER ), IMAGE_BITMAP, 0,0, LR_DEFAULTCOLOR );
            hgdiOldBitmap = SelectObject( hSourceDC, loadedbitmap );
            
            // ..and blit it
            BitBlt( dis->hDC,
                dis->rcItem.left,
                dis->rcItem.top ,
                dis->rcItem.right-dis->rcItem.left+1,
                dis->rcItem.bottom-dis->rcItem.top+1,
                hSourceDC,
                0,
                0,
                SRCCOPY
                );
            
            // Restore the original bitmap
            SelectObject( hSourceDC, hgdiOldBitmap );
            
            // this was missing from the Microsoft example code
            DeleteObject(loadedbitmap);
            DeleteDC(hSourceDC);
            return (LRESULT) 1;
        }
        break;


        case WM_COMMAND:
            if( wParam==IDOK || wParam==IDCANCEL )
            {
                if (DestroyWindow( hwndAboutBox ))
                    hwndAboutBox = NULL;
                return (LRESULT) 1;
            }
    }
    return (LRESULT) 0;

} // AboutDlgProc


//
// DoAboutDialog
//
void DoAboutDialog( HINSTANCE hInstance, HANDLE hwnd )
{
    if (hwndAboutBox == NULL)
    {
        hwndAboutBox = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_ABOUTBOX ), hwnd, AboutDlgProc );
    }

    if (hwndAboutBox != NULL)
    {
        ShowWindow(hwndAboutBox, SW_SHOW);
        BringWindowToTop( hwndAboutBox );
    }

} // DoAboutDialog



/*--------------------------- OPEN URL DIALOG BOX ---------------------------*/


// Non-modal Open URL dialog

//
// OpenURLDlgProc
//
BOOL FAR PASCAL OpenURLDlgProc( HWND hwnd, UINT message, UINT wParam, LONG lParam )
{
    switch( message )
    {
        case WM_INITDIALOG:
        {
            HWND combo;
            if (combo = GetDlgItem( hwnd, IDC_URLCOMBO ))
            {
                LONG retval;
                HKEY hkeyURLList;
                DWORD dwResult;

                retval = RegCreateKeyEx(APPREGKEY_ROOT,
                                        APPREGKEY_URLLIST,
                                        0,
                                        NULL,
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_ALL_ACCESS,
                                        NULL,
                                        &hkeyURLList,
                                        &dwResult);


                if (retval != ERROR_SUCCESS)
                {
                    gui_criticalerror("RegCreateKeyEx failed: %d\n", retval);
                }
                else
                {
                    DWORD dwIndex;
                    char keyname[32];
                    char buffer[512];
                    DWORD dwType;
                    DWORD dwSize;

                    for (dwIndex = 0 ; dwIndex < URLS_TO_REMEMBER ; dwIndex++)
                    {
                        sprintf(keyname, "URL%d", dwIndex);

                        dwSize = sizeof(buffer);
                        retval = RegQueryValueEx( hkeyURLList,
                                                  keyname,
                                                  0,
                                                  &dwType,
                                                  buffer,
                                                  &dwSize );

                        if (retval != ERROR_SUCCESS)
                        {
                            break;
                        }
                        else
                        {
                            if (dwType == REG_SZ)
                            {
                                retval = SendMessage(combo, CB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);

                                if (dwIndex == 0)
                                {
                                    retval = SendMessage(combo, CB_SETCURSEL, (WPARAM)dwIndex, 0);
                                }
                            }
                        }
                    }
                    RegCloseKey(hkeyURLList);
                }
            }
            return (LRESULT) 1;
        }

        case WM_COMMAND:
        {
            int my_argc;
            char *(my_argv[2]);

            char buffer[512];
            strcpy(buffer, "");

            if (wParam==IDOK)
            {
                HWND combo;
                int textlength;
                if (combo = GetDlgItem( hwndOpenURLDialog, IDC_URLCOMBO ))
                {
                    textlength = SendMessage(combo , WM_GETTEXTLENGTH, 0, 0);
                    if (textlength > sizeof(buffer)-1) textlength = sizeof(buffer)-1;
                    SendMessage(combo, WM_GETTEXT, (WPARAM)textlength+1, (LPARAM)buffer);
                }

                if ( strcmp(buffer, "") )
                {
                    HWND combo;
                    if (combo = GetDlgItem( hwndOpenURLDialog, IDC_URLCOMBO ))
                    {
                        LONG retval;
                        HKEY hkeyURLList;
                        DWORD dwResult;

                        retval = RegCreateKeyEx(APPREGKEY_ROOT,
                                                APPREGKEY_URLLIST,
                                                0,
                                                NULL,
                                                REG_OPTION_NON_VOLATILE,
                                                KEY_ALL_ACCESS,
                                                NULL,
                                                &hkeyURLList,
                                                &dwResult);

                        if (retval != ERROR_SUCCESS)
                        {
                            gui_criticalerror("RegCreateKeyEx failed: %d\n", retval);
                        }
                        else
                        {
                            DWORD dwIndex;
                            char keyname[32];
                            char buffer[512];

                            retval = SendMessage(combo, WM_GETTEXT, (WPARAM)sizeof(buffer), (LPARAM)buffer);
                            dwIndex = SendMessage(combo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                            if (dwIndex != CB_ERR)
                            {
                                retval = SendMessage(combo, CB_DELETESTRING, (WPARAM)dwIndex, (LPARAM)0);
                            }
                            retval = SendMessage(combo, CB_INSERTSTRING, (WPARAM)0, (LPARAM)buffer);

                            for (dwIndex = 0 ; dwIndex < URLS_TO_REMEMBER ; dwIndex++)
                            {
                                retval = SendMessage(combo, CB_GETLBTEXT, (WPARAM)dwIndex, (LPARAM)buffer);
                                if (retval == CB_ERR)
                                {
                                    break;
                                }

                                sprintf(keyname, "URL%d", dwIndex);

                                retval = RegSetValueEx( hkeyURLList,
                                                        keyname,
                                                        0,
                                                        REG_SZ,
                                                        buffer,
                                                        strlen(buffer)+1 );

                                if (retval != ERROR_SUCCESS)
                                {
                                    gui_criticalerror("RegSetValueEx failed: %d\n", retval);
                                }
                            }
                            RegCloseKey(hkeyURLList);
                        }
                    }

                    if (DestroyWindow( hwndOpenURLDialog ))
                        hwndOpenURLDialog = NULL;

                    my_argc = 2;

                    my_argv[0] = appVars.szProgramExecutable;
                    my_argv[1] = buffer;

                    main_function(my_argc, my_argv);
                }
            }

            if ( wParam==IDOK || wParam==IDCANCEL )
            {
                if (hwndOpenURLDialog != NULL)
                {
                    if (DestroyWindow( hwndOpenURLDialog ))
                        hwndOpenURLDialog = NULL;
                }
            }

            return (LRESULT) 1;
        }
    }
    return (LRESULT) 0;

} // OpenURLDlgProc


//
// DoOpenURLDialog
//
void DoOpenURLDialog( HINSTANCE hInstance, HANDLE hwnd )
{
    if (Transmitting == FALSE)
    {
        if (hwndOpenURLDialog == NULL)
        {
            hwndOpenURLDialog = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_OPEN_URL ), hwnd, OpenURLDlgProc );
        }

        if (hwndOpenURLDialog != NULL)
        {
            ShowWindow(hwndOpenURLDialog, SW_SHOW);
            BringWindowToTop( hwndOpenURLDialog );
        }
    }
    else
    {
        PlayerMessageBox( IDS_TRANSMISSION_RUNNING );
    }

} // DoOpenURLDialog



/*------------------------ ENTER PASSWORD DIALOG BOX ------------------------*/


// Modal Enter Password dialog

//
// EnterPasswordDlgProc
//
BOOL FAR PASCAL EnterPasswordDlgProc( HWND hwnd, UINT message, UINT wParam, LONG lParam )
{
    switch( message )
    {
        case WM_INITDIALOG:
        {
            HWND edit;
            if (edit = GetDlgItem( hwnd, IDC_USERNAME_EDIT ))
            {
                SendMessage(edit, WM_SETTEXT, (WPARAM)0, (LPARAM)username_buffer);
            }
            if (edit = GetDlgItem( hwnd, IDC_PASSWORD_EDIT ))
            {
                SendMessage(edit, WM_SETTEXT, (WPARAM)0, (LPARAM)password_buffer);
            }
            return (LRESULT) 1;
        }

        case WM_COMMAND:
        {
            if (wParam==IDOK)
            {
                HWND edit;
                int textlength;
                if (edit = GetDlgItem( hwnd, IDC_USERNAME_EDIT ))
                {
                    textlength = SendMessage(edit , WM_GETTEXTLENGTH, 0, 0);
                    if (textlength > sizeof(username_buffer)-1) textlength = sizeof(username_buffer)-1;
                    SendMessage(edit, WM_GETTEXT, (WPARAM)textlength+1, (LPARAM)username_buffer);
                }
                if (edit = GetDlgItem( hwnd, IDC_PASSWORD_EDIT ))
                {
                    textlength = SendMessage(edit , WM_GETTEXTLENGTH, 0, 0);
                    if (textlength > sizeof(password_buffer)-1) textlength = sizeof(password_buffer)-1;
                    SendMessage(edit, WM_GETTEXT, (WPARAM)textlength+1, (LPARAM)password_buffer);

                }
            }

            if ( wParam==IDOK || wParam==IDCANCEL )
            {
                EndDialog(hwnd, wParam);
            }

            return (LRESULT) 1;
        }
    }
    return (LRESULT) 0;

} // EnterPasswordDlgProc


//
// DoEnterPasswordDialog
//
UINT DoEnterPasswordDialog( HINSTANCE hInstance, HANDLE hwnd )
{
    UINT ret;

    ret = DialogBox( hInstance, MAKEINTRESOURCE( IDD_ENTER_PASSWORD ), hwnd, EnterPasswordDlgProc );
    
    return ret;
} // DoEnterPasswordDialog



/*--------------------- PROXY CONFIGURATION DIALOG BOX ----------------------*/


// Modal Proxy Configuration dialog

//
// ProxyConfigurationDlgProc
//
BOOL FAR PASCAL ProxyConfigurationDlgProc( HWND hwnd, UINT message, UINT wParam, LONG lParam )
{
    char serverstring[512];
    unsigned int portnum;
    char *serverptr, *colonptr;
            
    switch( message )
    {
        case WM_INITDIALOG:
        {
            LONG retval;
            HKEY hkeyProxyServer;
            DWORD dwResult;
            HWND edit;

            retval = RegCreateKeyEx(APPREGKEY_ROOT,
                APPREGKEY_BASE,
                0,
                NULL,
                REG_OPTION_NON_VOLATILE,
                KEY_ALL_ACCESS,
                NULL,
                &hkeyProxyServer,
                &dwResult);
            
            if (retval != ERROR_SUCCESS)
            {
                gui_criticalerror("RegCreateKeyEx failed: %d\n", retval);
            }
            else
            {
                char buffer[512];
                DWORD dwType;
                DWORD dwSize;
                
                dwSize = sizeof(buffer);
                retval = RegQueryValueEx( hkeyProxyServer,
                    "ProxyServer",
                    0,
                    &dwType,
                    buffer,
                    &dwSize );
                
                if (retval == ERROR_SUCCESS)
                {
                    if (dwType == REG_SZ)
                    {
                        strncpy(proxy_buffer, buffer, sizeof(proxy_buffer)-1);
                        proxy_buffer[sizeof(proxy_buffer)-1] = 0;
                    }
                }
                RegCloseKey(hkeyProxyServer);
            }

            strncpy(serverstring, proxy_buffer, sizeof(serverstring)-1);
            serverstring[sizeof(serverstring)-1]=0;

            serverptr = serverstring;
            if (!strnicmp(serverptr, "http://", 7)) serverptr+=7;

            colonptr = strchr(serverptr, ':');
            if (colonptr == NULL)
            {
                colonptr = serverptr+strlen(serverptr);
            }
            else
            {
                *colonptr++ = '\0';
            }
            if (atol(colonptr) == 0) colonptr = "";

            if (edit = GetDlgItem( hwnd, IDC_PROXY_SERVER_EDIT ))
            {
                SendMessage(edit, WM_SETTEXT, (WPARAM)0, (LPARAM)serverstring);
            }
            if (edit = GetDlgItem( hwnd, IDC_PROXY_PORT_EDIT ))
            {
               SendMessage(edit, WM_SETTEXT, (WPARAM)0, (LPARAM)colonptr);
            }
            return (LRESULT) 1;
        }

        case WM_COMMAND:
        {
            if (wParam==IDOK)
            {
                LONG retval;
                HKEY hkeyProxyServer;
                DWORD dwResult;
                HWND edit;
                int textlength;

                if (edit = GetDlgItem( hwnd, IDC_PROXY_SERVER_EDIT ))
                {
                    textlength = SendMessage(edit , WM_GETTEXTLENGTH, 0, 0);
                    if (textlength > sizeof(serverstring)-1) textlength = sizeof(serverstring)-1;
                    SendMessage(edit, WM_GETTEXT, (WPARAM)textlength+1, (LPARAM)serverstring);
                }
                if (edit = GetDlgItem( hwnd, IDC_PROXY_PORT_EDIT ))
                {
                    unsigned char portstring[32];
                    textlength = SendMessage(edit , WM_GETTEXTLENGTH, 0, 0);
                    if (textlength > sizeof(portstring)-1) textlength = sizeof(portstring)-1;
                    SendMessage(edit, WM_GETTEXT, (WPARAM)textlength+1, (LPARAM)portstring);

                    portnum = atol(portstring);
                    if (portnum > 65535) portnum = 65535;
                    if (portnum == 0) portnum = 8080; /* default port number */
                }

                if (!strcmp(serverstring, ""))
                    strcpy(proxy_buffer, "");
                else
                    sprintf(proxy_buffer, "%s:%d", serverstring, portnum);

                retval = RegCreateKeyEx(APPREGKEY_ROOT,
                    APPREGKEY_BASE,
                    0,
                    NULL,
                    REG_OPTION_NON_VOLATILE,
                    KEY_ALL_ACCESS,
                    NULL,
                    &hkeyProxyServer,
                    &dwResult);
                
                if (retval != ERROR_SUCCESS)
                {
                    gui_criticalerror("RegCreateKeyEx failed: %d\n", retval);
                }
                else
                {
                    retval = RegSetValueEx( hkeyProxyServer,
                        "ProxyServer",
                        0,
                        REG_SZ,
                        proxy_buffer,
                        strlen(proxy_buffer)+1 );
                    
                    if (retval != ERROR_SUCCESS)
                    {
                        gui_criticalerror("RegSetValueEx failed: %d\n", retval);
                    }
                }
            }

            if ( wParam==IDOK || wParam==IDCANCEL )
            {
                EndDialog(hwnd, wParam);
            }

            return (LRESULT) 1;
        }
    }
    return (LRESULT) 0;

} // ProxyConfigurationDlgProc


//
// DoProxyConfigurationDialog
//
UINT DoProxyConfigurationDialog( HINSTANCE hInstance, HANDLE hwnd )
{
    UINT ret;

    ret = DialogBox( hInstance, MAKEINTRESOURCE( IDD_PROXY_SERVER ), hwnd, ProxyConfigurationDlgProc );
    
    return ret;
} // DoProxyConfigurationDialog



/*-------------------------- MEDIA STATE ROUTINES ---------------------------*/


// Current multimedia variables
static Media media;


//
// CanPreview
//
// Return true if we can preview the currently downloading stream
//
BOOL CanPreview()
{
    return ((!Previewing) && Transmitting && strcmp( StreamFilename, "" ));
} // CanPreview


//
// CanPlay
//
// Return true if we can go to a playing state from our current state
//
BOOL CanPlay()
{
    return (media.state == Stopped || media.state == Paused);

} // CanPlay


//
// CanStop
//
// Return true if we can go to a stopped state from our current state
//
BOOL CanStop()
{
    return (media.state == Playing || media.state == Paused);

} // CanStop


//
// CanPause
//
// Return true if we can go to a paused state from our current state
//
BOOL CanPause()
{
    return (media.state == Playing || media.state == Stopped);

} // CanPause


//
// IsInitialized
//
// Return true if we have loaded and initialized a multimedia file
//
BOOL IsInitialized()
{
    return (media.state != Uninitialized);

} // IsInitialized


//
// ChangeStateTo
//
void ChangeStateTo( State newState )
{
    if (!Transmitting)
    {
        switch (newState)
        {
        case Playing:
                gui_setstatus("Playing...");
                break;
        case Paused:
                gui_setstatus("Paused");
                break;
        case Stopped:
                gui_setstatus("Stopped");
                break;
        case Uninitialized:
                gui_setstatus("");
                break;
        }
    }

    media.state = newState;

    if (TrackbarTimer != 0)
    {
        KillTimer( appVars.hwndMainFrame, TrackbarTimer); TrackbarTimer = 0;
    }

    if (newState == Playing)
        TrackbarTimer = SetTimer( appVars.hwndMainFrame, ID_TRACKBARTIMER, 100, &TrackbarTimerFunc );

    // update the toolbar
    UpdateToolbar();

} // ChangeStateTo


//
// InitMedia
//
// Initialization
//
BOOL InitMedia()
{
    ChangeStateTo( Uninitialized );

    media.hGraphNotifyEvent = NULL;
    media.pGraph = NULL;

    return TRUE;

} // InitMedia


/*------------------------- GRAPH/MEDIA FUNCTIONS ---------------------------*/

//
// CreateFilterGraph
//
BOOL CreateFilterGraph()
{
    BOOL result = FALSE;

    IMediaEvent *pME;
    HRESULT hr;

    ASSERT(media.pGraph == NULL);

    SetBusy(TRUE);

    hr = CoCreateInstance(&CLSID_FilterGraph,           // CLSID of object
                          NULL,                         // Outer unknown
                          CLSCTX_INPROC_SERVER,         // Type of server
                          &IID_IGraphBuilder,           // Interface wanted
                          (void **) &media.pGraph);     // Returned object
    if (FAILED(hr))
    {
        media.pGraph = NULL;
    }
    else
    {
        // We use this to find out events sent by the filtergraph

        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                  &IID_IMediaEvent,
                                                  (void **) &pME);
        if (FAILED(hr))
        {
            DeleteContents();
        }
        else
        {
            hr = pME->lpVtbl->GetEventHandle(pME, (OAEVENT*) &media.hGraphNotifyEvent);
            pME->lpVtbl->Release( pME );

            if (FAILED(hr))
            {
                DeleteContents();
            }
            else
            {
                result = TRUE;
            }
        }
    }

    SetBusy(FALSE);

    return result;

} // CreateFilterGraph


// Destruction
//
// DeleteContents
//
void DeleteContents()
{
    if (media.pGraph != NULL)
    {
        HRESULT hr;
        IVideoWindow   *pVW;

        SetBusy(TRUE);

        /* check if this graph comes with a video window */
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IVideoWindow, (void**) &pVW);
        if (SUCCEEDED(hr))
        {
            long left, top, width, height;

            /* remember video window position */
            hr = pVW->lpVtbl->GetRestorePosition(pVW, &left, &top, &width, &height);
            if (SUCCEEDED(hr))
            {
                IVWWindowLeft   = left;
                IVWWindowTop    = top;
                IVWWindowWidth  = width;
                IVWWindowHeight = height;
            }
            pVW->lpVtbl->Release(pVW);
        }

        media.pGraph->lpVtbl->Release( media.pGraph );
        media.pGraph = NULL;

        SetBusy(FALSE);
    }

    // this event is owned by the filter graph and is thus invalid
    media.hGraphNotifyEvent = NULL;

    Previewing = FALSE;

    IMPTotalTime = 0.0;
    IMPCurrentPosition = 0.0;

    IMSTotalTime = 0;
    IMSCurrentPosition = 0;
    IMSCapabilities = 0;

    SetStatusText(STAT_TIMECODE, 0, -1, "");

    if (hwndTrackbar)
    {
        SendMessage( hwndTrackbar, TBM_SETPOS, TRUE, 0);
        EnableWindow(hwndTrackbar, FALSE);
    }

    ChangeStateTo( Uninitialized );

} // DeleteContents


//
// RenderFile
//
BOOL RenderFile( LPSTR szFileName )
{
    BOOL result = FALSE;

    HRESULT hr;
    WCHAR wPath[MAX_PATH];

    SetBusy(TRUE);

    DeleteContents();

    if (!Transmitting) gui_setstatus("Preparing to play...");

    if ( !CreateFilterGraph() )
    {
        PlayerMessageBox( IDS_CANT_INIT_QUARTZ );
    }
    else
    {
        MultiByteToWideChar( CP_ACP, 0, szFileName, -1, wPath, MAX_PATH );

        hr = media.pGraph->lpVtbl->RenderFile(media.pGraph, wPath, NULL);

        if (FAILED( hr ))
        {
            PlayerMessageBox( IDS_CANT_RENDER_FILE );
        }
        else
        {
            IMediaPosition *pMP;
            IMediaSeeking  *pMS;
            IVideoWindow   *pVW;

            IMPTotalTime = 0;
            IMPCurrentPosition = 0;

            hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                      &IID_IMediaPosition,
                                                      (void**) &pMP);
            if (SUCCEEDED(hr))
            {
                REFTIME tLength;
                hr = pMP->lpVtbl->get_Duration(pMP, &tLength);
                if (SUCCEEDED(hr))
                {
                    LONG lBackward;
                    LONG lForward;

                    IMPTotalTime = tLength;

                    hr = pMP->lpVtbl->CanSeekBackward(pMP, &lBackward);
                    if (SUCCEEDED(hr))
                    {
                        hr = pMP->lpVtbl->CanSeekBackward(pMP, &lForward);
                        if (SUCCEEDED(hr))
                        {
//                            if (lBackward == OATRUE && lForward == OATRUE)
                            {
                                if (hwndTrackbar)
                                    EnableWindow(hwndTrackbar, TRUE);
                            }
                        }
                    }
                }
                pMP->lpVtbl->Release(pMP);
            }

            IMSTotalTime = 0;
            IMSCurrentPosition = 0;
            IMSCapabilities = 0;

            hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                      &IID_IMediaSeeking,
                                                      (void**) &pMS);
            if (SUCCEEDED(hr))
            {
                LONGLONG llDuration;

                hr = pMS->lpVtbl->GetDuration(pMS, &llDuration);
                if (SUCCEEDED(hr))
                {
                    DWORD dwCapabilities = 0;

                    IMSTotalTime = llDuration;

                    hr = pMS->lpVtbl->GetCapabilities(pMS, &dwCapabilities);
                    if (SUCCEEDED(hr))
                    {
                      //if (dwCapabilities & AM_SEEKING_CanSeekAbsolute)  gui_criticalerror("AM_SEEKING_CanSeekAbsolute");
                      //if (dwCapabilities & AM_SEEKING_CanSeekForwards)  gui_criticalerror("AM_SEEKING_CanSeekForwards");
                      //if (dwCapabilities & AM_SEEKING_CanSeekBackwards) gui_criticalerror("AM_SEEKING_CanSeekBackwards");
                      //if (dwCapabilities & AM_SEEKING_CanGetCurrentPos) gui_criticalerror("AM_SEEKING_CanGetCurrentPos");
                      //if (dwCapabilities & AM_SEEKING_CanGetStopPos)    gui_criticalerror("AM_SEEKING_CanGetStopPos");
                      //if (dwCapabilities & AM_SEEKING_CanGetDuration)   gui_criticalerror("AM_SEEKING_CanGetDuration");
                      //if (dwCapabilities & AM_SEEKING_CanPlayBackwards) gui_criticalerror("AM_SEEKING_CanPlayBackwards");
                      //if (dwCapabilities & AM_SEEKING_CanDoSegments)    gui_criticalerror("AM_SEEKING_CanDoSegments");
                      //if (dwCapabilities & AM_SEEKING_Source)           gui_criticalerror("AM_SEEKING_Source");

                        IMSCapabilities = dwCapabilities;
                    }
                }

                pMS->lpVtbl->Release(pMS);
            }

            /* check if this graph comes with a video window */
            hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                      &IID_IVideoWindow,
                                                      (void**) &pVW);
            if (SUCCEEDED(hr))
            {
                BSTR title;
                
                if ((title = SysAllocString(wPath)) != NULL)
                {
                    hr = pVW->lpVtbl->put_Caption(pVW,title);

                    SysFreeString(title);
                }

                if (IVWWindowWidth > 0 && IVWWindowHeight > 0)
                {
                    long left, top, width, height;
                    left   = IVWWindowLeft;
                    top    = IVWWindowTop;
                    width  = IVWWindowWidth;
                    height = IVWWindowHeight;

                    hr = pVW->lpVtbl->SetWindowPosition(pVW, left, top, width, height);
                }

                pVW->lpVtbl->Release(pVW);
            }

            /* in any case, we got a filter graph, so return TRUE */
            result = TRUE;

        }
    }

    SetBusy(FALSE);

    return result;

} // RenderFile


//
// SetTitle
//
// Update the title of the video renderer to "Player - szFile"
//
void SetTitle( HWND hwnd, char *szFile )
{
    char szNewTitle[ _MAX_FNAME + _MAX_EXT  + 20 ];

    strcpy( szNewTitle, APP_NAME );
    strcat( szNewTitle, " - " );
    strcat( szNewTitle, szFile );

    // Update the window's title
    SetWindowText( hwnd, szNewTitle );

} // SetTitle


//
// OpenMediaFile
//
// File..Open has been selected
//
BOOL OpenMediaFile( HWND hwnd, LPSTR szFile )
{
    BOOL result = FALSE;

    static char szFileName[ _MAX_PATH ];
    static char szTitleName[ _MAX_FNAME + _MAX_EXT ];

    if( szFile != NULL )
    {
        if ( RenderFile( szFile ) )
        {
            LPSTR szTitle;

            // Work out the full path name and the file name from the
            // specified file
            GetFullPathName( szFile, _MAX_PATH, szFileName, &szTitle );
            strncpy( szTitleName, szTitle, _MAX_FNAME + _MAX_EXT );
            szTitleName[ _MAX_FNAME + _MAX_EXT -1 ] = '\0';

            // Set the main window title and update the state
            if (!Transmitting) SetTitle( hwnd, szTitleName );
            ChangeStateTo( Stopped );
            result = TRUE;
        }
        else
            if (!Transmitting) gui_seterror("Unable to play file!");
    }
    else
    {
        if( DoFileOpenDialog( hwnd, szFileName, szTitleName ) )
        {
            if (RenderFile( szFileName ) )
            {
                // Set the main window title and update the state
                if (!Transmitting) SetTitle( hwnd, szTitleName );
                ChangeStateTo( Stopped );
                result = TRUE;
            }
            else
                if (!Transmitting) gui_seterror("Unable to play file!");

        }
    }
    return result;

} // OpenMediaFile


//
// GetCurrentPosition
//

BOOL GetCurrentPosition(REFTIME *rtcur)
{
    BOOL result = FALSE;

    if (IsInitialized())
    {
        HRESULT hr;
        IMediaPosition *pMP;
        REFTIME tCurrent;

        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
            &IID_IMediaPosition,
            (void**) &pMP);
        if (SUCCEEDED(hr))
        {
            hr = pMP->lpVtbl->get_CurrentPosition(pMP, &tCurrent);
            if (SUCCEEDED(hr))
            {
                *rtcur = tCurrent;
                result = TRUE;
            }
            pMP->lpVtbl->Release(pMP);
        }
    }

    return result;
} // GetCurrentPosition


//
// GetStopPosition
//

BOOL GetStopPosition(REFTIME *rtstop, LONGLONG *llstop)
{
    BOOL result = FALSE;

    if (Previewing)
    {
        HRESULT hr;
        IMediaPosition *pMP;
        IMediaSeeking *pMS;

        // Obtain the IMediaPosition interface to our filter graph
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IMediaPosition, (void **) &pMP);
        if( SUCCEEDED(hr) )
        {
            pMP->lpVtbl->get_StopTime(pMP, rtstop);
            if ( SUCCEEDED(hr) )
            {
                result = TRUE;
            }
            pMP->lpVtbl->Release(pMP);
        }

        /* this one works as an alternative to the above */
        if (TRUE)
        {
            // Obtain the IMediaSeeking interface to our filter graph
            hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IMediaSeeking, (void **) &pMS);
            if( SUCCEEDED(hr) )
            {
                /* Replay should stop at the current download position */
                hr = pMS->lpVtbl->GetStopPosition(pMS, llstop);
                if ( SUCCEEDED(hr) )
                {
                    result = TRUE;
                }

                pMS->lpVtbl->Release(pMS);
            }

        }
    }

    return result;

} // GetStopPosition


//
// SetStopPosition
//

BOOL SetStopPosition(int milliseconds)
{
    BOOL result = FALSE;

    if (Previewing)
    {
        HRESULT hr;
        IMediaPosition *pMP;
        IMediaSeeking *pMS;

        // Obtain the IMediaPosition interface to our filter graph
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IMediaPosition, (void **) &pMP);
        if( SUCCEEDED(hr) )
        {
            pMP->lpVtbl->put_StopTime(pMP, (REFTIME)milliseconds/1000);
            if ( SUCCEEDED(hr) )
            {
                result = TRUE;
            }
            pMP->lpVtbl->Release(pMP);
        }

        /* this one works as an alternative to the above */
        if (result == FALSE)
        {
            // Obtain the IMediaSeeking interface to our filter graph
            hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IMediaSeeking, (void **) &pMS);
            if( SUCCEEDED(hr) )
            {
                LONGLONG llCurrent = 0;
                LONGLONG llStop = 0;
                DWORD dwCurrentFlags = AM_SEEKING_NoPositioning;
                DWORD dwStopFlags = AM_SEEKING_AbsolutePositioning;

                /* Replay should stop at the current download position */
                llStop = (LONGLONG)(milliseconds * 10000);
                hr = pMS->lpVtbl->SetPositions(pMS,
                    &llCurrent,
                    dwCurrentFlags,
                    &llStop,
                    dwStopFlags );
                if ( hr == NOERROR )
                {
                    result = TRUE;
                }

                pMS->lpVtbl->Release(pMS);
            }

        }
    }

    return result;

} // SetStopPosition


//
// SetCurrentPosition
//

BOOL SetCurrentPosition(REFTIME position)
{
    BOOL result = FALSE;

    if( IsInitialized() )
    {
        HRESULT hr;
        IMediaPosition *pMP;

        SetBusy ( TRUE );

        // Obtain the interface to our filter graph
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IMediaPosition, (void **) &pMP);
        if( SUCCEEDED(hr) )
        {
            pMP->lpVtbl->put_CurrentPosition(pMP, position);
            result = TRUE;
            pMP->lpVtbl->Release(pMP);
        }

        if (result == FALSE)
            // Inform the user that an error occurred
            PlayerMessageBox( IDS_CANT_SEEK );

        SetBusy ( FALSE );
    }

    return result;

} // SetCurrentPosition


//
// OnMediaSeeking
//
BOOL OnMediaSeeking(BOOL Enabled)
{
    BOOL result = FALSE;

    HRESULT hr;
    IMediaControl *pMC;

    // Obtain the interface to our filter graph
    hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
        &IID_IMediaControl,
        (void **) &pMC);

    if( SUCCEEDED(hr) )
    {
        result = TRUE;

        if (Enabled)
        {
            if (!Transmitting) gui_setstatus("Seeking...");

            if (media.state == Playing)
            {
                hr = pMC->lpVtbl->Pause( pMC );
            }
        }
        else
        {
            if (media.state == Playing)
            {
                hr = pMC->lpVtbl->Run( pMC );
            }

            ChangeStateTo(media.state);

        }

        pMC->lpVtbl->Release( pMC );

    }

    return result;

} // OnMediaSeeking


//
// OnMediaPlay
//

BOOL OnMediaPlay()
{
    BOOL result = FALSE;

    if( CanPlay() )
    {
        HRESULT hr;
        IVideoWindow  *pVW;
        IMediaControl *pMC;

        SetBusy ( TRUE );

        /* check if this graph comes with a video window */
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph, &IID_IVideoWindow, (void**) &pVW);
        if (SUCCEEDED(hr))
        {
            long windowstate;

            /* remember video window position */
            hr = pVW->lpVtbl->get_WindowState(pVW, &windowstate);
            if (SUCCEEDED(hr))
            {
                /* show the window if it was hidden/miminized */
                if (windowstate == SW_MINIMIZE || windowstate == SW_HIDE ||
                    windowstate == SW_SHOWMINNOACTIVE                     )
                {
                    windowstate = SW_SHOWNORMAL;
                    hr = pVW->lpVtbl->put_WindowState(pVW, windowstate);
                }
                
            }
            pVW->lpVtbl->Release(pVW);
        }

        if (Previewing)
        {
            REFTIME rtstoppos;
            LONGLONG llstoppos;
            REFTIME rtcurrent;

            if (GetStopPosition(&rtstoppos, &llstoppos))
            {
                if (GetCurrentPosition(&rtcurrent))
                {
                    /* the filter graph thinks it has reached the end of the stream */
                    /* because it is truncated and we are still downloading it!     */
                    if (rtcurrent == rtstoppos)
                    {
                        /* so in this case we have to reposition and try again */
                        /* otherwise the filter graph won't continue to play   */
                        SetCurrentPosition( IMPCurrentPosition );
                    }
                }
            }
        }

        // Obtain the interface to our filter graph
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                  &IID_IMediaControl,
                                                  (void **) &pMC);

        if( SUCCEEDED(hr) )
        {
            // Ask the filter graph to play and release the interface
            hr = pMC->lpVtbl->Run( pMC );
            if( SUCCEEDED(hr) )
            {
                ChangeStateTo( Playing );
                result = TRUE;
            }
            pMC->lpVtbl->Release( pMC );
        }

        if (result == FALSE)
            // Inform the user that an error occurred
            PlayerMessageBox( IDS_CANT_PLAY );

        SetBusy ( FALSE );
    }

    return result;

} // OnMediaPlay


//
// OnMediaPause
//
BOOL OnMediaPause()
{
    BOOL result = FALSE;

    if( CanPause() )
    {
        HRESULT hr;
        IMediaControl *pMC;

        SetBusy(TRUE);

        // Obtain the interface to our filter graph
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                  &IID_IMediaControl,
                                                  (void **) &pMC);

        if( SUCCEEDED(hr) )
        {
            // Ask the filter graph to pause and release the interface
            hr = pMC->lpVtbl->Pause( pMC );
            if( SUCCEEDED(hr) )
            {
                ChangeStateTo( Paused );
                result = TRUE;
            }

            pMC->lpVtbl->Release( pMC );

        }

        if (result == FALSE)
            // Inform the user that an error occurred
            PlayerMessageBox( IDS_CANT_PAUSE );

        SetBusy(FALSE);
    }

    return result;

} // OnMediaPause


//
// OnMediaStop
//
BOOL OnMediaStop(BOOL reallystop, BOOL rewind)
{
    BOOL result = FALSE;

    if( CanStop() )
    {
        HRESULT hr;
        IMediaControl *pMC;

        SetBusy(TRUE);

        if (!Transmitting) gui_setstatus("Stopping replay...");

        // Obtain the interface to our filter graph
        hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                  &IID_IMediaControl,
                                                  (void **) &pMC);
        if( SUCCEEDED(hr) )
        {
            IMediaPosition * pMP;

            if (reallystop)
                // now really do the stop
                pMC->lpVtbl->Stop( pMC );
            else
                // just simulate a stop using pause (faster)
                pMC->lpVtbl->Pause( pMC );

            if( SUCCEEDED(hr) )
            {
                ChangeStateTo( Stopped );
                result = TRUE;
            }

            if (rewind == TRUE)
            {
                hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                          &IID_IMediaPosition,
                                                          (void**) &pMP);
                if (SUCCEEDED(hr))
                {
                    hr = pMP->lpVtbl->put_CurrentPosition(pMP, 0);
                    if (SUCCEEDED(hr))
                    {
                        SetStatusText(STAT_TIMECODE, 0, -1, "");

                        if (hwndTrackbar != NULL)
                            SendMessage( hwndTrackbar, TBM_SETPOS, TRUE, 0);
                    }

                    pMP->lpVtbl->Release(pMP);
                }
            }
            pMC->lpVtbl->Release( pMC );
        }

        if (result == FALSE)
            // Inform the user that an error occurred
            PlayerMessageBox( IDS_CANT_STOP );

        SetBusy(FALSE);
    }

    return result;

} // OnMediaStop


//
// GetGraphEventHandle
//
// We use this to check for graph events
//
HANDLE GetGraphEventHandle()
{
    return media.hGraphNotifyEvent;

} // GetGraphEventHandle


//
// OnGraphNotify
//
// If the event handle is valid, then ask the graph if
// anything has happened (eg the graph has stopped...)
//
void OnGraphNotify()
{
    IMediaEvent *pME;
    long lEventCode, lParam1, lParam2;

    ASSERT( media.hGraphNotifyEvent != NULL );

    if( SUCCEEDED(media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                       &IID_IMediaEvent,
                                                       (void **) &pME)))
    {
        if( SUCCEEDED(pME->lpVtbl->GetEvent(pME, &lEventCode, &lParam1, &lParam2, 0)))
        {
            if (lEventCode == EC_COMPLETE)
            {
                OnMediaStop(FALSE, FALSE);
                if (!Transmitting) gui_setstatus("Replay complete");
            }
            if (lEventCode == EC_USERABORT)
            {
                OnMediaStop(TRUE, TRUE);
                if (!Transmitting) gui_setstatus("User aborted replay");
            }
            if (lEventCode == EC_ERRORABORT)
            {
                OnMediaStop(TRUE, TRUE);
                if (!Transmitting) gui_setstatus("Error during replay");
            }
        }
        pME->lpVtbl->Release( pME );
    }

} // OnGraphNotify


/*---------------------------- FILE OPEN DIALOG -----------------------------*/


// This handles the file..open dialog box

static OPENFILENAME ofn;

//
// InitFileOpenDialog
//
BOOL InitFileOpenDialog( HWND hwnd )
{
    ofn.lStructSize         = sizeof( OPENFILENAME );
    ofn.hwndOwner           = hwnd;
    ofn.hInstance           = NULL;
    ofn.lpstrFilter         = "Windows Media files (*.asf,*.wma,*.wmv)\0*.asf; *.wma; *.wmv\0"
                              "MPEG audio files (*.mp2,*.mp3)\0*.mp2; *.mp3;\0"
                              "MPEG video files (*.mpg,*.mpe,*.mpeg)\0*.mpg; *.mpe; *.mpeg\0"
                              "AVI files (*.avi)\0*.avi\0"
                              "Quick Time files (*.mov)\0*.mov\0"
                              "Wave audio files (*.wav)\0*.wav\0"
                              "Filter graph files (*.grf)\0*.grf\0"
                              "All Files (*.*)\0*.*\0\0";
    ofn.lpstrCustomFilter   = NULL;
    ofn.nMaxCustFilter      = 0;
    ofn.nFilterIndex        = 0;
    ofn.lpstrFile           = NULL;
    ofn.nMaxFile            = _MAX_PATH;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = _MAX_FNAME + _MAX_EXT;
    ofn.lpstrInitialDir     = NULL;
    ofn.lpstrTitle          = NULL;
    ofn.Flags               = OFN_EXPLORER | OFN_FILEMUSTEXIST;
    ofn.nFileOffset         = 0;
    ofn.nFileExtension      = 0;
    ofn.lpstrDefExt         = "asf";
    ofn.lCustData           = 0;
    ofn.lpfnHook            = NULL;
    ofn.lpTemplateName      = NULL;

    return TRUE;

} // InitFileOpenDialog


//
// DoFileOpenDialog
//
BOOL DoFileOpenDialog( HWND hwnd, LPSTR lpstrFileName, LPSTR lpstrTitleName )
{
    // Called to display the open file dialog
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = lpstrFileName;
    ofn.lpstrFileTitle = lpstrTitleName;

    ShowWindow( appVars.hwndMainFrame, SW_SHOWNORMAL );
    SetWindowPos(appVars.hwndMainFrame, HWND_TOP, 0, 0, 0, 0,
                 SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);

    return GetOpenFileName( &ofn );

} // DoFileOpenDialog



/*---------------------------- FILE SAVE DIALOG -----------------------------*/


// This handles the file..open dialog box

static OPENFILENAME sfn;

//
// InitFileSaveDialog
//
BOOL InitFileSaveDialog( HWND hwnd )
{
    sfn.lStructSize         = sizeof( OPENFILENAME );
    sfn.hwndOwner           = hwnd;
    sfn.hInstance           = NULL;
    sfn.lpstrFilter         = "Windows Media files (*.asf,*.wma,*.wmv)\0*.asf; *.wma; *.wmv\0"
                              "All Files (*.*)\0*.*\0\0";
    sfn.lpstrCustomFilter   = NULL;
    sfn.nMaxCustFilter      = 0;
    sfn.nFilterIndex        = 0;
    sfn.lpstrFile           = NULL;
    sfn.nMaxFile            = _MAX_PATH;
    sfn.lpstrFileTitle      = NULL;
    sfn.nMaxFileTitle       = _MAX_FNAME + _MAX_EXT;
    sfn.lpstrInitialDir     = NULL;
    sfn.lpstrTitle          = NULL;
    sfn.Flags               = OFN_EXPLORER ;
    sfn.nFileOffset         = 0;
    sfn.nFileExtension      = 0;
    sfn.lpstrDefExt         = "asf";
    sfn.lCustData           = 0;
    sfn.lpfnHook            = NULL;
    sfn.lpTemplateName      = NULL;

    return TRUE;

} // InitFileSaveDialog


//
// DoFileSaveDialog
//
BOOL DoFileSaveDialog( HWND hwnd, LPSTR lpstrFileName, LPSTR lpstrTitleName )
{
    // Called to display the open file dialog
    sfn.hwndOwner = hwnd;
    sfn.lpstrFile = lpstrFileName;
    sfn.lpstrFileTitle = lpstrTitleName;

    ShowWindow( appVars.hwndMainFrame, SW_SHOWNORMAL );
    SetWindowPos(appVars.hwndMainFrame, HWND_TOP, 0, 0, 0, 0,
                 SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);

    return GetSaveFileName( &sfn );

} // DoFileSaveDialog



/*----------------------------- TOOL BAR CODE -------------------------------*/


// Constants for the bitmap
const int nButtonImageWidth = 46;
const int nButtonImageHeight = 36;

// Constants for the toolbar implementation
const int nSeperatorGap = 6;
const int nToolbarBorderWidth = 5;
const int nToolbarBorderHeight = 3;

//
// CalcToolbarSize
//
void CalcToolbarSize( SIZE *pSize )
{
    // Calculate the area required for this toolbar

    // size for 3 buttons, 2 borders and a seperator
    // ...but we'll add on a some extra seperators for good measure
    pSize->cx = (nButtonImageWidth) * 5 + nSeperatorGap + 2 * nToolbarBorderWidth;

    // size for 1 button and 2 borders
    pSize->cy = nButtonImageHeight + 2 * nToolbarBorderHeight;

} // CalcToolbarSize


//
// UpdateToolbar
//
// Maintains the enabled/disabled state of the buttons - we should be
// called periodically and/or whenever there is a change of graph state
//
void UpdateToolbar()
{
    if (toolbar.hwndPlayButton != NULL)
        EnableWindow( toolbar.hwndPlayButton, CanPlay() );
    if (toolbar.hwndPauseButton != NULL)
        EnableWindow( toolbar.hwndPauseButton, CanPause() );
    if (toolbar.hwndStopButton != NULL)
        EnableWindow( toolbar.hwndStopButton, CanStop() );
    if (toolbar.hwndPreviewButton != NULL)
        EnableWindow( toolbar.hwndPreviewButton, CanPreview() );
    if (toolbar.hwndCancelButton != NULL)
        EnableWindow( toolbar.hwndCancelButton, Transmitting );

} // UpdateToolbar


//
// ToolbarButtonProc
//
// Subclassed window procedure for the toolbar buttons
//

long FAR PASCAL ToolbarButtonProc( HWND hwnd, UINT message, UINT wParam, LONG lParam)
{
    WNDPROC oldwndproc = (WNDPROC)GetWindowLong( hwnd, GWL_USERDATA );

    switch(message)
    {
        case WM_ERASEBKGND:
        {
            /* no nothing */
        }
        return (LRESULT) 1;
        break;

        default:
            return CallWindowProc(oldwndproc, hwnd, message, wParam, lParam);
    }
    return (LRESULT) 0;

} // MainFrameProc

//
// InitToolbar
//
// Create the controls for the buttons
//
BOOL InitToolbar( HINSTANCE hInstance, HWND hwnd )
{
    LONG oldwndproc;
    int x;      // Position of the next button

    x = nToolbarBorderWidth;

    // The 'Play' button
    toolbar.hwndPlayButton = CreateWindow( "BUTTON",
                                           NULL,
                                           BS_OWNERDRAW | WS_VISIBLE | WS_CHILD,
                                           x,
                                           nToolbarBorderHeight,
                                           nButtonImageWidth,
                                           nButtonImageHeight,
                                           hwnd,
                                           (HMENU) ID_MEDIA_PLAY,
                                           hInstance,
                                           NULL);

    oldwndproc = SetWindowLong( toolbar.hwndPlayButton, GWL_WNDPROC, (DWORD)&ToolbarButtonProc);
    SetWindowLong(toolbar.hwndPlayButton, GWL_USERDATA, oldwndproc);

    x += nButtonImageWidth;

    // The 'Pause' button
    toolbar.hwndPauseButton = CreateWindow( "BUTTON",
                                            NULL,
                                            BS_OWNERDRAW | WS_VISIBLE | WS_CHILD,
                                            x,
                                            nToolbarBorderHeight,
                                            nButtonImageWidth,
                                            nButtonImageHeight,
                                            hwnd,
                                            (HMENU) ID_MEDIA_PAUSE,
                                            hInstance,
                                            NULL);

    oldwndproc = SetWindowLong( toolbar.hwndPauseButton, GWL_WNDPROC, (DWORD)&ToolbarButtonProc);
    SetWindowLong(toolbar.hwndPauseButton, GWL_USERDATA, oldwndproc);

    x += nButtonImageWidth;

    // The 'Stop' button
    toolbar.hwndStopButton = CreateWindow( "BUTTON",
                                           NULL,
                                           BS_OWNERDRAW | WS_VISIBLE | WS_CHILD,
                                           x,
                                           nToolbarBorderHeight,
                                           nButtonImageWidth,
                                           nButtonImageHeight,
                                           hwnd,
                                           (HMENU) ID_MEDIA_STOP,
                                           hInstance,
                                           NULL);

    oldwndproc = SetWindowLong( toolbar.hwndStopButton, GWL_WNDPROC, (DWORD)&ToolbarButtonProc);
    SetWindowLong(toolbar.hwndStopButton, GWL_USERDATA, oldwndproc);

    x += nButtonImageWidth + nSeperatorGap;

    // The 'Preview' button
    toolbar.hwndPreviewButton = CreateWindow( "BUTTON",
                                           NULL,
                                           BS_OWNERDRAW | WS_VISIBLE | WS_CHILD,
                                           x,
                                           nToolbarBorderHeight,
                                           nButtonImageWidth,
                                           nButtonImageHeight,
                                           hwnd,
                                           (HMENU) ID_STREAM_PREVIEW,
                                           hInstance,
                                           NULL);

    oldwndproc = SetWindowLong( toolbar.hwndPreviewButton, GWL_WNDPROC, (DWORD)&ToolbarButtonProc);
    SetWindowLong(toolbar.hwndPreviewButton, GWL_USERDATA, oldwndproc);

    x += nButtonImageWidth;

    // The 'Cancel' button
    toolbar.hwndCancelButton = CreateWindow( "BUTTON",
                                           NULL,
                                           BS_OWNERDRAW | WS_VISIBLE | WS_CHILD,
                                           x,
                                           nToolbarBorderHeight,
                                           nButtonImageWidth,
                                           nButtonImageHeight,
                                           hwnd,
                                           (HMENU) ID_STREAM_CANCEL,
                                           hInstance,
                                           NULL);

    oldwndproc = SetWindowLong( toolbar.hwndCancelButton, GWL_WNDPROC, (DWORD)&ToolbarButtonProc);
    SetWindowLong(toolbar.hwndCancelButton, GWL_USERDATA, oldwndproc);

    // We don't call UpdateToolbar to set the button states as
    // the multimedia variables may not have been initialized yet
    return TRUE;

} // InitToolbar


//
// DrawButton
//
// Called by the main window whenever a button needs to be redrawn
//
void DrawButton( HINSTANCE hInstance, DRAWITEMSTRUCT FAR * lpDrawItem )
{
    HDC hSourceDC = CreateCompatibleDC( NULL );
    HGDIOBJ loadedbitmap;
    HGDIOBJ hgdiOldBitmap;
    int nIndex;

    // Load the IDR_TOOLBAR_INACTIVE bitmap into our source hDC if the
    // button is disabled otherwise load the IDR_TOOLBAR_PRESSED/NOTPRESSED bitmap
    if( lpDrawItem->itemState & ODS_DISABLED )
        loadedbitmap = (HGDIOBJ) LoadImage( hInstance, MAKEINTRESOURCE( IDB_TOOLBAR_INACTIVE ), IMAGE_BITMAP, 0,0, LR_DEFAULTCOLOR );
    else
    {
        if( lpDrawItem->itemState & ODS_SELECTED )
            loadedbitmap = (HGDIOBJ) LoadImage( hInstance, MAKEINTRESOURCE( IDB_TOOLBAR_PRESSED ), IMAGE_BITMAP, 0,0, LR_DEFAULTCOLOR );
        else
            loadedbitmap = (HGDIOBJ) LoadImage( hInstance, MAKEINTRESOURCE( IDB_TOOLBAR_NOTPRESSED ), IMAGE_BITMAP, 0,0, LR_DEFAULTCOLOR );
    }
    hgdiOldBitmap = SelectObject( hSourceDC, loadedbitmap );

    // Decide which button to blit to the display
    switch( lpDrawItem->CtlID ){
        case ID_MEDIA_PLAY:
            nIndex = 0;
            break;

        case ID_MEDIA_PAUSE:
            nIndex = 1;
            break;

        case ID_MEDIA_STOP:
            nIndex = 2;
            break;

        case ID_STREAM_PREVIEW:
            nIndex = 3;
            break;

        case ID_STREAM_CANCEL:
            nIndex = 4;
            break;
    }

    // ..and blit it
    BitBlt( lpDrawItem->hDC,
            lpDrawItem->rcItem.left,
            lpDrawItem->rcItem.top ,
            nButtonImageWidth,
            nButtonImageHeight,
            hSourceDC,
            nIndex * nButtonImageWidth + 2,
            0,
            SRCCOPY
          );

    // Restore the original bitmap
    SelectObject( hSourceDC, hgdiOldBitmap );

    // this was missing from the Microsoft example code
    DeleteObject(loadedbitmap);
    DeleteDC(hSourceDC);
} // DrawButton


/*---------------------------- TRACK BAR CODE -------------------------------*/

const int nTrackbarBorderWidth = 5;
const int nTrackbarBorderHeight = 11;

//
// CalcTrackbarSize
//
// Calculate the size of the trackbar (including borders)
//

void CalcTrackbarSize ( SIZE *pSize )
{
    RECT clientRect;

    SIZE sizeToolbar;

    GetClientRect( appVars.hwndMainFrame, &clientRect );
    CalcToolbarSize( &sizeToolbar );

    pSize->cx = (clientRect.right-clientRect.left+1) - sizeToolbar.cx;
    pSize->cy = sizeToolbar.cy;

} // CalcTrackbarSize


//
// TrackbarProc
//
// Subclassed window procedure for the trackbar
//

long FAR PASCAL TrackbarProc( HWND hwnd, UINT message, UINT wParam, LONG lParam)
{
    WNDPROC oldwndproc = (WNDPROC)GetWindowLong( hwnd, GWL_USERDATA );

    switch(message)
    {
        /* This modifies the default behaviour of the trackbar.     */
        /* When clicking inside the channel, the click position     */
        /* is converted to a slider position value and stored in    */
        /* positionTrackbar                                         */

        /* this enables us to move the slider to this position when */
        /* we receive a WM_NOTIFY / NM_RELEASEDCAPTURE message      */

    case WM_LBUTTONDOWN:
        {
            UINT fwKeys = wParam;        // key flags
            if (fwKeys == MK_LBUTTON)
            {
                int xPos = LOWORD(lParam);  // horizontal position of cursor
                int yPos = HIWORD(lParam);  // vertical position of cursor
                RECT chanrect;
                LONG chanwidth;

                SendMessage(hwndTrackbar, TBM_GETCHANNELRECT, 0, (LPARAM) &chanrect);
                chanwidth = chanrect.right - chanrect.left + 1;

                if (xPos >= chanrect.left && xPos <= chanrect.right)
                {
                    UINT min, max;
                    min = SendMessage(hwndTrackbar, TBM_GETRANGEMIN, 0, 0);
                    max = SendMessage(hwndTrackbar, TBM_GETRANGEMAX, 0, 0);

                    positionTrackbar = min + ((max-min)*(xPos-chanrect.left))/chanwidth;
                }
            }
            return CallWindowProc(oldwndproc, hwnd, message, wParam, lParam);
        }
        break;

    case WM_ERASEBKGND:
        {
            /* no nothing */
        }
        return (LRESULT) 1;
        break;

        default:
            return CallWindowProc(oldwndproc, hwnd, message, wParam, lParam);
    }
    return (LRESULT) 0;

} // TrackbarProc


//
// AdjustTrackbar
//
// Reposition the trackbar control in the main frame
//

void AdjustTrackbar ( HWND hwndTrack, HWND hwndParent )
{
    int x,y,w,h;

    SIZE sizeToolbar;
    SIZE sizeTrackbar;

    CalcToolbarSize( &sizeToolbar );
    CalcTrackbarSize ( &sizeTrackbar );

    x = sizeToolbar.cx + nTrackbarBorderWidth;
    y = (sizeToolbar.cy - sizeTrackbar.cy)/2 + nTrackbarBorderHeight;
    w = sizeTrackbar.cx - 2 * nTrackbarBorderWidth;
    h = sizeTrackbar.cy - 2 * nTrackbarBorderHeight;

    MoveWindow( hwndTrack, x,y,w,h, TRUE );

} // AdjustTrackbar


//
// InitTrackbar
//
// Create and initialize the trackbar control
//

BOOL InitTrackbar( HINSTANCE hInstance, HWND hwnd )
{
    LONG oldwndproc;
    int x,y,w,h;

    SIZE sizeToolbar;
    SIZE sizeTrackbar;

    CalcToolbarSize( &sizeToolbar );
    CalcTrackbarSize ( &sizeTrackbar );

    x = sizeToolbar.cx + nTrackbarBorderWidth;
    y = (sizeToolbar.cy - sizeTrackbar.cy)/2 + nTrackbarBorderHeight;
    w = sizeTrackbar.cx - 2 * nTrackbarBorderWidth;
    h = sizeTrackbar.cy - 2 * nTrackbarBorderHeight;

    // Create the trackbar
    hwndTrackbar = CreateWindow( TRACKBAR_CLASS,
                                 NULL,
                                 WS_DISABLED | WS_VISIBLE | WS_CHILD | TBS_NOTICKS | TBS_ENABLESELRANGE | TBS_FIXEDLENGTH,
                                 x,
                                 y,
                                 w,
                                 h,
                                 hwnd,
                                 (HMENU) IDR_TRACKBAR,
                                 hInstance,
                                 NULL );

    SendMessage(hwndTrackbar, TBM_SETTHUMBLENGTH, 16, 0);

    /* TrackBars range is from 0 to 10000, regardless of the stream length */
    SendMessage(hwndTrackbar, TBM_SETRANGEMIN, FALSE, 0     );
    SendMessage(hwndTrackbar, TBM_SETRANGEMAX, FALSE, 10000 );

    /* disable pageup/down lineup/down using keyboard or mouse */
    SendMessage(hwndTrackbar, TBM_SETPAGESIZE,    0 , 0);
    SendMessage(hwndTrackbar, TBM_SETLINESIZE,    0,  0);

    oldwndproc = SetWindowLong( hwndTrackbar, GWL_WNDPROC, (DWORD)&TrackbarProc);
    SetWindowLong(hwndTrackbar, GWL_USERDATA, oldwndproc);

    return TRUE;

} // InitTrackbar


//
// TrackbarTimerFunc
//
// Moves the trackbar during media replay. Also prints time stamp.
//

void CALLBACK TrackbarTimerFunc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    HRESULT hr;
    IMediaPosition * pMP;

    if (idEvent == TrackbarTimer)
    {
        if (IMPTotalTime != 0.0)
        {
            if (IsInitialized())
            {
                hr = media.pGraph->lpVtbl->QueryInterface(media.pGraph,
                                                          &IID_IMediaPosition,
                                                          (void**) &pMP);
                if (SUCCEEDED(hr))
                {
                    REFTIME tCurrent;
                    hr = pMP->lpVtbl->get_CurrentPosition(pMP, &tCurrent);
                    if (SUCCEEDED(hr))
                    {
                        LONG value;

                        if (Previewing)
                        {
                            if (tCurrent < IMPDownloadTime)
                            {
                                IMPCurrentPosition = tCurrent;
                            }
                        }
                        else
                        {
                            IMPCurrentPosition = tCurrent;
                        }

                        if (hwndTrackbar != NULL)
                        {
                            if (!TrackbarDragging)
                            {
                                value = (LONG)(10000 * IMPCurrentPosition / IMPTotalTime);
                                SendMessage( hwndTrackbar, TBM_SETPOS, TRUE, value);
                            }
                        }


                        if ((!Transmitting) && (!TrackbarDragging))
                        {
                            unsigned int timecode = (unsigned int)(1000 * IMPCurrentPosition);
                            char *timecodestring = createtimestring(timecode);
                            SetStatusText(STAT_TIMECODE, 0, -1, "T: %s", timecodestring);
                        }
                    }
                    pMP->lpVtbl->Release(pMP);
                }
            }
        }
    }

} // TrackbarTimerFunc


/*---------------------- FILE TYPE REGISTRATION CODE ------------------------*/

enum
{
    Query,
    Register,
    Unregister
};

//
// FileTypeRegistration
//
// query for, register or unregister a given file type
//

BOOL FileTypeRegistration(LPTSTR filetype, int mode)
{
    BOOL result = FALSE;

    LONG retval;
    HKEY hkeyFileExtension;
    HKEY hkeyFileType;
    DWORD dwResult;

    unsigned char keyname[32];
    unsigned char defaulttypename[32];
    unsigned char *src, *dst;

    int i;

    keyname[0] = '.';
    for (src = filetype, dst = &keyname[1]; *dst = tolower(*src) ; dst++, src++ );
    for (src = filetype, dst = defaulttypename; *dst = toupper(*src) ; dst++, src++ );
    strcat(defaulttypename, "File");

    retval = RegCreateKeyEx(HKEY_CLASSES_ROOT,
                            keyname,
                            0,
                            NULL,
                            REG_OPTION_NON_VOLATILE,
                            KEY_READ | KEY_WRITE,
                            NULL,
                            &hkeyFileExtension,
                            &dwResult);

    if (retval != ERROR_SUCCESS)
    {
        gui_criticalerror("RegCreateKeyEx (1) for '%s' failed: %d\n", keyname, retval);
    }
    else
    {
        unsigned char filetypename[200];
        unsigned char filetypenameshellcommand[256];
        DWORD dwType;
        DWORD dwSize;

        strcpy(filetypename, "");

        dwSize = sizeof(filetypename);
        retval = RegQueryValueEx( hkeyFileExtension,
                                  "",
                                  0,
                                  &dwType,
                                  filetypename,
                                  &dwSize );

        if (retval != ERROR_SUCCESS)
        {
            if (retval != ERROR_FILE_NOT_FOUND)
                gui_criticalerror("RegQueryValueEx (1) for '%s' failed: %d\n", "(Default)", retval);
            else
            {
                retval = RegSetValueEx( hkeyFileExtension,
                                        "",
                                        0,
                                        REG_SZ,
                                        defaulttypename,
                                        strlen(defaulttypename)+1 );
                if (retval != ERROR_SUCCESS)
                {
                    gui_criticalerror("RegSetValueEx (1) for '%s' failed: %d\n", "(Default)", retval);
                }
                else
                    strcpy(filetypename, defaulttypename);
            }
        }
        else
        {
            if (dwType == REG_SZ)
            {
                if (!strcmp("", filetypename))
                {
                    retval = RegSetValueEx( hkeyFileExtension,
                                            "",
                                            0,
                                            REG_SZ,
                                            defaulttypename,
                                            strlen(defaulttypename)+1 );
                    if (retval != ERROR_SUCCESS)
                    {
                        gui_criticalerror("RegSetValueEx (2) for '%s' failed: %d\n", "(Default)", retval);
                    }
                    else
                        strcpy(filetypename, defaulttypename);
                }
            }
        }
            

        if (strcmp(filetypename, ""))
        {
            if (mode == Query)
                result = TRUE;

            for (i = 0; i < 2 ; i++)
            {
                strcpy(filetypenameshellcommand, filetypename);
                if (i == 0)
                    strcat(filetypenameshellcommand, "\\shell\\open\\command");
                if (i == 1)
                    strcat(filetypenameshellcommand, "\\shell\\play\\command");

                retval = RegCreateKeyEx(HKEY_CLASSES_ROOT,
                                        filetypenameshellcommand,
                                        0,
                                        NULL,
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_READ | KEY_WRITE,
                                        NULL,
                                        &hkeyFileType,
                                        &dwResult);

                if (retval != ERROR_SUCCESS)
                {
                    gui_criticalerror("RegCreateKeyEx (2) for '%s' failed: %d\n", filetypenameshellcommand, retval);
                }
                else
                {
                    unsigned char playername[512];
                    unsigned char playernameuppercase[512];
                    DWORD dwType = REG_NONE;
                    DWORD dwSize;
                    
                    dwSize = sizeof(playername);
                    retval = RegQueryValueEx( hkeyFileType,
                                              "",
                                              0,
                                              &dwType,
                                              playername,
                                              &dwSize );

                    if (retval != ERROR_SUCCESS)
                    {
                        if (retval != ERROR_FILE_NOT_FOUND)
                            gui_criticalerror("RegQueryValueEx (2) for '%s' failed: %d\n", "(Default)", retval);
                        else
                            strcpy(playername, "");
                        dwType = REG_SZ;
                    }
                        
                    if (dwType == REG_SZ)
                    {
                        unsigned char myplayername[512];
                        unsigned char myplayernameuppercase[512];
                        sprintf(myplayername, "\42%s\42 \42%%L\42", appVars.szProgramExecutable);
                        
                        /* make uppercase versions of playername strings */
                        strcpy(playernameuppercase, playername);
                        _strupr(playernameuppercase);
                        
                        strcpy(myplayernameuppercase, myplayername);
                        _strupr(myplayernameuppercase);

                        switch (mode)
                        {
                        case Query:
                            
                            /* try to match player name with asfrecorder */
                            if ( (strstr(playernameuppercase, myplayernameuppercase ) == NULL) &&
                                 (strstr(playernameuppercase, "ASFRECORDER"         ) == NULL) &&
                                 (strstr(playernameuppercase, "ASFREC~"             ) == NULL)    )
                            {
                                result = FALSE;
                                break;
                            }
                            break;
                            
                        case Register:
                            /* Create backup of old player only if its name */
                            /* does not contain the string "ASFRecorder" and*/
                            /* if it is not empty */
                            if ((strcmp(playernameuppercase, ""           )        ) &&
                                (strstr(playernameuppercase, "ASFRECORDER") == NULL) &&
                                (strstr(playernameuppercase, "ASFREC~1"   ) == NULL)    )
                            {
                                retval = RegSetValueEx( hkeyFileType,
                                                        "ASFRecorder_backup",
                                                        0,
                                                        REG_SZ,
                                                        playername,
                                                        strlen(playername)+1 );
                                if (retval != ERROR_SUCCESS)
                                {
                                    gui_criticalerror("RegSetValueEx (3) for '%s' failed: %d\n", "ASFRecorder_backup", retval);
                                }
                            }
                            
                            retval = RegSetValueEx( hkeyFileType,
                                                    "",
                                                    0,
                                                    REG_SZ,
                                                    myplayername,
                                                    strlen(myplayername)+1 );
                            if (retval != ERROR_SUCCESS)
                            {
                                gui_criticalerror("RegSetValueEx (4) for '%s' failed: %d\n", "(Default)", retval);
                            }
                            break;
                            
                        case Unregister:
                            dwSize = sizeof(playername);
                            retval = RegQueryValueEx( hkeyFileType,
                                                      "ASFRecorder_backup",
                                                      0,
                                                      &dwType,
                                                      playername,
                                                      &dwSize );
                            if ((retval != ERROR_SUCCESS) && (retval != ERROR_FILE_NOT_FOUND))
                            {
                                gui_criticalerror("RegQueryValueEx (3) for '%s' failed: %d\n", "ASFRecorder_backup", retval);
                            }
                            else
                            {
                                if (retval == ERROR_FILE_NOT_FOUND)
                                {
                                    dwType = REG_SZ;
                                    strcpy(playername, "");
                                }
                                
                                if (dwType == REG_SZ)
                                {
                                    retval = RegSetValueEx( hkeyFileType,
                                                            "",
                                                            0,
                                                            REG_SZ,
                                                            playername,
                                                            strlen(playername)+1 );
                                    if (retval != ERROR_SUCCESS)
                                    {
                                        gui_criticalerror("RegSetValueEx (5) for '%s' failed: %d\n", "(Default)", retval);
                                    }
                                    else
                                    {
                                        retval = RegDeleteValue( hkeyFileType,
                                            "ASFRecorder_backup" );
                                        if ((retval != ERROR_SUCCESS) && (retval != ERROR_FILE_NOT_FOUND))
                                        {
                                            gui_criticalerror("RegDeleteValue (1) for '%s' failed: %d\n", "ASFRecorder_backup", retval);
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                    RegCloseKey(hkeyFileType);
                }
            }
        }
        RegCloseKey(hkeyFileExtension);
    }
    return result;

} // FileTypeRegistration


//
// OnRegisterFileTypes
//
// Register redirection file types.
//

void OnRegisterFileTypes()
{
    if ( (!FileTypeRegistration("ASX", Query)) ||
         (!FileTypeRegistration("WAX", Query)) ||
         (!FileTypeRegistration("WVX", Query)) ||
         (!FileTypeRegistration("WMX", Query))   )
    {
        FileTypeRegistration("ASX", Register);
        FileTypeRegistration("WAX", Register);
        FileTypeRegistration("WVX", Register);
        FileTypeRegistration("WMX", Register);
        PlayerMessageBox( IDS_REGISTERED );
    }
    else
    {
        PlayerMessageBox( IDS_ALREADYREGISTERED );
    }

} // OnRegisterFileTypes


//
// OnRegisterFileTypes
//
// Unregister redirection file types.
//

void OnUnregisterFileTypes()
{
    if ( FileTypeRegistration("ASX", Query) ||
         FileTypeRegistration("WAX", Query) ||
         FileTypeRegistration("WVX", Query) ||
         FileTypeRegistration("WMX", Query)   )
    {
        FileTypeRegistration("ASX", Unregister);
        FileTypeRegistration("WAX", Unregister);
        FileTypeRegistration("WVX", Unregister);
        FileTypeRegistration("WMX", Unregister);
        PlayerMessageBox( IDS_UNREGISTERED );
    }
    else
    {
        PlayerMessageBox( IDS_NOTREGISTERED );
    }

} // OnUnregisterFileTypes
