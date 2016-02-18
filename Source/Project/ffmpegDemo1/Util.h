//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Util.h
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __UTIL_H_2459134951B94A1895E650CFD52F4215__
#define __UTIL_H_2459134951B94A1895E650CFD52F4215__
#pragma once

extern "C"
{
//#include "../include/ffmpeg/include/inttypes.h"
//#include "../include/ffmpeg/include/libavformat/avformat.h"
//#include "../include/ffmpeg/include/libavcodec//avcodec.h"
//#include "../include/ffmpeg/include/libswscale/swscale.h"
//#include "../include/ffmpeg/include/libavutil/avutil.h"
//#include "../include/ffmpeg/include/libavutil/mathematics.h"
//#include "../include/sdl/include/SDL.h"
//#include "../include/sdl/include/SDL_thread.h"

#include "include/inttypes.h"
//#include "include/libavformat/avformat.h"
//#include "include/libavcodec//avcodec.h"
//#include "include/libswscale/swscale.h"
//#include "include/libavutil/avutil.h"
//#include "include/libavutil/mathematics.h"
#include "../include/sdl/include/SDL.h"
#include "../include/sdl/include/SDL_thread.h"
};
#undef main
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "postproc.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "SDL.lib")

#include <vector>
using namespace std;
#define THREADID	(SDL_USEREVENT + 1)
int ThreadFunc(void* param);
bool PlayVedio(char* szFilePath);
bool PlayVedio2(char* szFilePath, HWND hwnd);

#endif//__UTIL_H_2459134951B94A1895E650CFD52F4215__