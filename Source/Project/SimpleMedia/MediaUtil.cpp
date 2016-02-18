#include "stdafx.h"
#include "MediaUtil.h"

static bool g_ThreadRunning = false;
int ThreadFunc(void* param)
{
	while(g_ThreadRunning)
	{
		SDL_Event event;
		event.type = THREADID;
		SDL_PushEvent(&event);
		SDL_Delay(40);
	}

	return 0;
}

bool PlayVedio(char* szFilePath, HWND hwnd/* = NULL*/)
{
	if(szFilePath == NULL)				return false;
	if(strlen(szFilePath) == 0)			return false;
	AVFormatContext *pFormatContext = NULL;	// Format Context
	AVCodecContext  *pCodecContext = NULL;	// Codec Context
	AVCodec			*pCodec = NULL;			// Codec
	AVFrame* pMainFrame = NULL;				// pMainFrame
	AVFrame* pMemFrame = NULL;				// pMemFrame
	AVPacket* packet = NULL;				// packet
	uint8_t* pszShowBuffer = NULL;			// pszShowBuffer
	DWORD dwRet = 0;
	
	{
	// Init
	av_register_all();
	if(avformat_network_init() != 0)	return false;
	pFormatContext = avformat_alloc_context();	// malloc
	if(pFormatContext == NULL)			return false;
	// Open File
	if(avformat_open_input(&pFormatContext, szFilePath, NULL, NULL) != 0)
	{
		goto END;
	}
	int nVedioIndex = -1;
	for(BYTE i = 0; i < pFormatContext->nb_streams; i++)
	{
		// Vedio
		if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			nVedioIndex =  i;
			break;
		}
	}
	if(nVedioIndex == -1)	goto END;
	pCodecContext = pFormatContext->streams[nVedioIndex]->codec;
	pCodec = avcodec_find_decoder(pCodecContext->codec_id);
	if(pCodec == NULL)		goto END;
	if(avcodec_open2(pCodecContext, pCodec, NULL) != 0)	goto END;
	// Show
	DWORD dwWidth = pCodecContext->width;		// witdh
	DWORD dwHeight = pCodecContext->height;		// height
	pMainFrame = avcodec_alloc_frame();// MainFrame
	pMemFrame = avcodec_alloc_frame();	// MemFrame
	
	DWORD dwSize = avpicture_get_size(PIX_FMT_YUV420P, dwWidth, dwHeight);
	pszShowBuffer = (uint8_t*)av_malloc(dwSize);
	avpicture_fill((AVPicture*)pMainFrame, pszShowBuffer, PIX_FMT_YUV420P, dwWidth, dwHeight);
	// SDL
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_WINDOW_BORDERLESS))	goto END;
	SDL_Window* sdlWindow_ = NULL;	

	sdlWindow_ = SDL_CreateWindow("BaseWindow",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		dwWidth,
		dwHeight,
		SDL_WINDOW_OPENGL);
	
	SDL_Window* sdlWindow  = NULL;
	if(hwnd)
	{
		sdlWindow = SDL_CreateWindowFrom((void*)hwnd);
	}
	else
	{
		sdlWindow = SDL_CreateWindow("QuanMedia",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			dwWidth,
			dwHeight,
		SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	}
	if(sdlWindow == NULL)	goto END;
	

	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(
		sdlWindow, 
		-1, //2D
		0);
	if(sdlRenderer == NULL)	goto END;
	SDL_DestroyWindow(sdlWindow_);		// Question
	SDL_EnableScreenSaver();
	SDL_Texture* sdlTexture = SDL_CreateTexture(
		sdlRenderer, 
		SDL_PIXELFORMAT_IYUV, 
		SDL_TEXTUREACCESS_STREAMING, 
		dwWidth,
		dwHeight);
	SDL_Rect sdlRect;
	sdlRect.x = 0;
	sdlRect.y = 0;
	sdlRect.w = dwWidth;
	sdlRect.h = dwHeight;
	// Recieve packet
	packet = (AVPacket*)av_malloc(sizeof(AVPacket));
	av_dump_format(pFormatContext, 0, szFilePath, 0);		
	struct SwsContext* img_convert_ctx;

	img_convert_ctx = sws_getContext(
		dwWidth,
		dwHeight,
		pCodecContext->pix_fmt,
		dwWidth,
		dwHeight,
		PIX_FMT_YUV420P,
		SWS_BICUBIC,
		NULL, NULL, NULL);
	// SDL Thread
	g_ThreadRunning = true;
	SDL_Thread* sdlThread = SDL_CreateThread(ThreadFunc, NULL, NULL);
	SDL_Event event;
	int got_picture = NULL;
	while(true)
	{
		SDL_WaitEvent(&event);
		if(event.type != THREADID)	continue;
		DWORD intRet = av_read_frame(pFormatContext, packet);	// Return the next frame of a stream
		if(intRet == 0)
		{
//			if(packet->stream_index == nVedioIndex)
			{
				intRet = avcodec_decode_video2(pCodecContext,
						pMemFrame, 
						&got_picture, 
						packet);				// Decode the video frame
				if(intRet < 0)	goto END;

				if(got_picture)
				{
					sws_scale(img_convert_ctx,
						(const uint8_t* const*)pMemFrame->data,
						pMemFrame->linesize,
						0,
						dwHeight,
						pMainFrame->data,
						pMainFrame->linesize);	// Scale the image slice in srcSlice and put the resulting scaled
					SDL_UpdateTexture(sdlTexture, &sdlRect, pMainFrame->data[0], pMainFrame->linesize[0]);
					SDL_RenderClear(sdlRenderer);							// clear
					SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);	// CopyData
					SDL_RenderPresent(sdlRenderer);
				}
			}	
		}
		else
		{
			break;
		}
	}
	g_ThreadRunning = false;
	SDL_Quit();
	}
END:
	if(packet)
		av_free_packet(packet);	
	if(pMemFrame)
		avcodec_free_frame(&pMemFrame);
	if(pMainFrame)
		avcodec_free_frame(&pMainFrame);
	if(pszShowBuffer)
		av_free(pszShowBuffer);						// free
	if(pCodecContext)
		avcodec_close(pCodecContext);
	if(pFormatContext)
	{
		avformat_close_input(&pFormatContext);
		avformat_free_context(pFormatContext);		// free
	}

	return true;
}

//extern C_LINKAGE int SDL_main(int argc, char *argv[])	{	return 0;	}
//_CRTIMP FILE * __cdecl ___iob_func()
//{
//	return NULL;
//}

