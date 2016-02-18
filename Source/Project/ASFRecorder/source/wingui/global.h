
// Allows Visual C++ to precompile the standard header files

#include <stdio.h>
#include <string.h>

/* networking headers */
#include <winsock2.h>

#ifdef  __MINGW32__
#define WIN32
#endif /* __MINGW32__ */


#ifdef NDEBUG
  #define ASSERT( exp ) ((void)0)
#else
  void DbgAssert(const char *pCondition, const char *pFileName, int iLine);
  #define ASSERT(exp) if(!(exp)) DbgAssert( TEXT(#exp), TEXT(__FILE__), TEXT(__LINE__) );
#endif

#include <windows.h>
#include <commdlg.h>
#include <wingdi.h>


#include <shlwapi.h>
#include <commctrl.h>

#include <objbase.h>
#include <strmif.h>
#include <control.h>
#include <evcode.h>
#include <uuids.h>

#ifdef  __MINGW32__
#include "msimg32.h"
#endif /* __MINGW32__ */

#include "resource.h"


#define OATRUE (-1)
#define OAFALSE (0)

#define APP_NAME "ASFRecorder"

#define APPREGKEY_ROOT    HKEY_CURRENT_USER
#define APPREGKEY_BASE    "Software\\" APP_NAME
#define APPREGKEY_URLLIST APPREGKEY_BASE "\\RecentURLList"

#define URLS_TO_REMEMBER 25

typedef struct
{
    char szAppName[ 32 ];
    HANDLE hInstance;
    HWND hwndMainFrame;
    BOOL bFatalError;
    char *szProgramExecutable;
} AppVars;


/* Prototype for GUI code in external module */

int  gui_initialize(void);
void gui_uninitialize(void);
void gui_setbatchmode(int flag);
int  gui_startedfromdesktop(void);

int  gui_start_transmission(char *url, char *filename, int filenamesize, unsigned int totaltime, unsigned int maxtime);
void gui_finished_transmission();
void gui_progressinfo(int bytes, char *timecode, int progress, int seqno, int currenttime);
void gui_modify_duration(unsigned int totaltime);

void gui_prepareasyncsocket(SOCKET s);
void gui_restoresyncsocket(SOCKET s);
void gui_return_on_network_activity();
void gui_return_on_network_connect(int *retval);
int  gui_nonblocking_socket_check(int num);
void gui_waitforuseraction(void);

void gui_showtext(char *text, ...);
void gui_setstatus(char *statustext, ...);
void gui_seterror(char *errortext, ...);
void gui_criticalerror(char *errortext, ...);
void gui_logtext(char *text, ...);
char *gui_translate_errorcode(int error);


int PASCAL PseudoWinMain( HINSTANCE hInstance,
                          HINSTANCE hPrevInstance,
                          LPSTR lpszCmdParam,
                          int nCmdShow );

int DoMainLoop(int network_mask);

void EndOfWinMain(void);


HRESULT GetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor);

void PlayerMessageBox( UINT nResource );

BOOL FAR PASCAL AboutDlgProc( HWND hwnd, UINT message, UINT wParam, LONG lParam );
void DoAboutDialog( HINSTANCE hInstance, HANDLE hwnd );

BOOL FAR PASCAL OpenURLDlgProc( HWND hwnd, UINT message, UINT wParam, LONG lParam );
void DoOpenURLDialog( HINSTANCE hInstance, HANDLE hwnd );

BOOL InitFileOpenDialog( HWND hwnd );
BOOL DoFileOpenDialog( HWND hwnd, LPSTR lpstrFileName, LPSTR lpstrTitleName );

BOOL InitFileSaveDialog( HWND hwnd );
BOOL DoFileSaveDialog( HWND hwnd, LPSTR lpstrFileName, LPSTR lpstrTitleName );

typedef enum tagState {Uninitialized, Stopped, Paused, Playing } State;

typedef struct tagMedia
{
    State state;
    IGraphBuilder *pGraph;
    HANDLE hGraphNotifyEvent;
} Media;

BOOL InitMedia(void);
void SetTitle( HWND hwnd, char *szFile );
BOOL OpenMediaFile( HWND hwnd, LPSTR szFile );
HANDLE GetGraphEventHandle( void );

BOOL CanPreview(void);
BOOL CanPlay(void);
BOOL CanStop(void);
BOOL CanPause(void);
BOOL IsInitialized(void);
void DeleteContents(void);

// Event handlers

BOOL GetStopPosition(REFTIME *rtstop, LONGLONG *llstop);
BOOL SetStopPosition(int milliseconds);
BOOL SetCurrentPosition(REFTIME position);
BOOL OnMediaSeeking(BOOL Enable);
BOOL OnMediaPlay(void);
BOOL OnMediaPause(void);
BOOL OnMediaStop(BOOL reallystop, BOOL rewind);
BOOL OnMediaAbortStop(void);
void OnGraphNotify(void);


void UpdateToolbar(void);
void DrawButton( HINSTANCE hInstance, DRAWITEMSTRUCT FAR * lpDrawItem );
void CalcToolbarSize( SIZE *pSize );
BOOL InitToolbar( HINSTANCE hInstance, HWND hwnd );

BOOL InitStatusbar( HINSTANCE hInstance, HWND hwndMainFrame );
void SetStatusText(int partno, int drawmode, COLORREF cref, LPSTR text,...);
void SetStatusTextArgs(int partno, int drawmode, COLORREF cref, LPSTR text, void *args);
void CalcStatusSize ( SIZE *pSize, int *array );
void AdjustStatusbar(HWND hwndStatus, HWND hwndParent, int *array);
HWND DoCreateStatusbar(HWND hwndParent, int nStatusID, 
                       HINSTANCE hinst, int *array);
void CALLBACK StatusbarTimerFunc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);


void CalcTrackbarSize ( SIZE *pSize );
void AdjustTrackbar ( HWND hwndTrack, HWND hwndParent );
BOOL InitTrackbar( HINSTANCE hInstance, HWND hwnd );
void CALLBACK TrackbarTimerFunc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

BOOL FileTypeRegistration(LPTSTR filetype, int mode);
void OnRegisterFileTypes(void);
void OnUnregisterFileTypes(void);
