#undef  __cplusplus
extern "C" {
	//FFMPEG
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	//SDL	
	#include <sdl/SDL.h>
	#include <sdl/SDL_thread.h>	
}
#define __cplusplus

#define THREADID	(SDL_USEREVENT + 1)
int ThreadFunc(void* param);
bool PlayVedio(char* szFilePath, HWND hwnd);
typedef unsigned long DWORD;

