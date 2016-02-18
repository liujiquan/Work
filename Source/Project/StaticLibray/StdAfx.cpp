// stdafx.cpp : source file that includes just the standard includes
//	StaticLibray.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "StaticLibrary.h"
// -----------------------------------------------------------//
// Function :   __declspec
// Param    :   dllimport
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
char* fnSharedDll(void)
{
	return ("This a Static Library.");
}
