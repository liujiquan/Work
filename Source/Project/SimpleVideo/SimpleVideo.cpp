// SimpleVideo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MediaUtil.h"
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	
//	PlayVedio("C:\\Work\\Source\\Project\\bin\\amano.asf");
	PlayVedio("http://10.10.1.67/CyberX/amano.asf");
//	PlayVedio2("http://10.10.1.67/CyberX/amano.asf");
	return 0;
}



