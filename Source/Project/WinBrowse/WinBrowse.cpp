// WinBrowse.cpp : Defines the entry point for the DLL application.
//
#include <windows.h>
#include <io.h>
#include <TCHAR.h>
#define F_OK	0		// exist	
#define R_OK	2		// read
#define W_OK	4		// write
#define X_OK	6		// excute

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) 
// -----------------------------------------------------------//
// Function :   browse
// Param    :   pszFilePath
// Return   :   bool
// Comment  :   Open File Function
// -----------------------------------------------------------//
bool browse(const char* pszFilePath)
{
	if(pszFilePath == NULL)
	{
		return false;
	}
	// Check File IsExist
	if(access(pszFilePath, F_OK) == -1)
	{
		return false;
	}
	
	// Open File/Dir
	SHELLEXECUTEINFO info;
	memset(&info, 0x00, sizeof(info));
	info.cbSize = sizeof(info);
	info.hwnd = NULL;
	info.lpVerb = _T("open");
	info.lpFile = pszFilePath;
	info.lpParameters = NULL;
	info.nShow = SW_SHOWNORMAL;
	info.fMask = SEE_MASK_NOCLOSEPROCESS;
	
	if(::ShellExecuteEx(&info) == false)
	{
		return false;
	}
	
	return true;
}