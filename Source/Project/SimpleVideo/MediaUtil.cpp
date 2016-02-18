#include "stdafx.h"
#include "MediaUtil.h"
#include <vector>
using namespace std;
/************************************************************************/
/* Member                                                                     */
/************************************************************************/
vector<int64_t>	g_TimestampList;		// 
int g_VideoFrameCount = 0;				//
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

bool PlayVedio(char* szFilePath)
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
	// Excute Stream Info
	if(av_find_stream_info(pFormatContext) < 0)		goto END;
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
	
	SDL_Window* sdlWindow_ = SDL_CreateWindow("BaseWindow",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		dwWidth,
		dwHeight,
		SDL_WINDOW_OPENGL);
	
	SDL_Window* sdlWindow = SDL_CreateWindow("QuanMedia",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		dwWidth,
		dwHeight,
		SDL_WINDOW_SHOWN);
	if(sdlWindow == NULL)	goto END;

	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(
		sdlWindow, 
		-1, //2D
		0);
	if(sdlRenderer == NULL)	goto END;
	SDL_DestroyWindow(sdlWindow_);		// Question
	
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

bool PlayVedio2(char* szFilePath)
{
	if(szFilePath == NULL)				return false;
	if(strlen(szFilePath) == 0)			return false;
	AVFormatContext *pFormatContext = NULL;		// Format Context
	AVCodecContext  *pVedioCodecContext = NULL;	// Codec Context	ÊÓÆµ½âÂëÆ÷ÈÝÆ÷
	AVCodecContext  *pAudioCodecContext = NULL;	// Codec Context	ÒôÆµ½âÂëÆ÷ÈÝÆ÷
	AVCodec			*pVedioCodec = NULL;		// Codec			ÊÓÆµ½âÂëÆ÷
	AVCodec			*pAudioCodec = NULL;		// Codec			ÒôÆµ½âÂëÆ÷
	AVFrame* pMainFrame = NULL;					// pMainFrame
	AVFrame* pMemFrame = NULL;					// pMemFrame
	AVPacket* packet = NULL;					// packet
	uint8_t* pszShowBuffer = NULL;				// pszShowBuffer
	DWORD dwRet;
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
	// Excute Stream Info
	if(av_find_stream_info(pFormatContext) != 0)		goto END;
	int nVedioIndex = -1;
	int nAudioIndex = -1;
	for(int i = 0; i < pFormatContext->nb_streams; i++)
	{
		// Vedio
		if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			nVedioIndex =  i;
		}
		else if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			nAudioIndex = i;
		}
	}
	if(nVedioIndex == -1)	goto END;
	pVedioCodecContext = pFormatContext->streams[nVedioIndex]->codec;	// ÊÓÆµ½âÂëÆ÷ÈÝÆ÷
	pAudioCodecContext = pFormatContext->streams[nAudioIndex]->codec;	// ÒôÆµ½âÂëÆ÷ÈÝÆ÷
	pVedioCodec = avcodec_find_decoder(pVedioCodecContext->codec_id);	// ÊÓÆµ½âÂëÆ÷
	pAudioCodec = avcodec_find_decoder(pAudioCodecContext->codec_id);	// ÒôÆµ½âÂëÆ÷
	if(pVedioCodec == NULL)		goto END;
	if(pAudioCodec == NULL)		goto END;
	if(avcodec_open2(pVedioCodecContext, pVedioCodec, NULL) != 0)	goto END;
	if(avcodec_open2(pVedioCodecContext, pAudioCodec, NULL) != 0)	goto END;
	{
		AVPacket* packet = (AVPacket*)av_malloc(sizeof(AVPacket));
		AVFrame* pFrame = avcodec_alloc_frame();	// MemFrame
		int nStreamsCount = pFormatContext->nb_streams;
		for(int i = 0 ; i < nStreamsCount; i++)
		{
			AVStream*  pStream = pFormatContext->streams[i];
			
		}
		int nRet = 0;

//		g_TimestampList.clear();
		while(nRet == 0)
		{
			nRet = av_read_frame(pFormatContext, packet);
			if(nRet != 0)	continue;
			void* PacketData = packet->data;
			int PacketSize = packet->size;
			int packetPos = packet->pos;
			int packetDuration = packet->duration;
			int packetPresentTimeStamp = packet->pts;
			int packetDecodeTimeStamp = packet->dts;
//			printf("*****************Packet**%d*****************\n", packet->stream_index);
//			//printf("======================>PacketData\n");
//			//				printf("%s\n", PacketData);
//			printf("pos[%d]	size[%d]	pos+size[%d] packetDuration[%d]\n", 
//				packetPos, PacketSize, packetPos+PacketSize, packetDuration);
//			printf("dpts[%d]	dts[%d]\n\n\n", packetPresentTimeStamp, packetDecodeTimeStamp);
			
			// Vedio
			int got_frame = -1;
			int nDecodeRet = -1;
			if(packet->stream_index == nVedioIndex)
			{
				nDecodeRet = avcodec_decode_video2(pVedioCodecContext,
					pFrame, 
					&got_frame, 
					packet);
			}
			else if(packet->stream_index == nAudioIndex)
			{
				int16_t nSample;
			//	nDecodeRet = avcodec_decode_audio3(pAudioCodecContext, &nSample, &got_frame, 
			//		packet ); 
				nDecodeRet = avcodec_decode_audio4(pAudioCodecContext, 
					pFrame,
                    &got_frame, 
					packet);
			}
			else
			{
				continue;
			}
			if(nDecodeRet >= 0)
			{
				if(packet->stream_index == nVedioIndex)
				{
					void* FrameData = pFrame->data[0];
					int FrameLineSize = pFrame->linesize[0];
					int FrameWid = pFrame->width;
					int FrameHei = pFrame->height;
					int Frame_PacketPos = pFrame->pkt_pos;
					int Frame_PacketDuration = pFrame->pkt_duration;
					int Frame_PacketSize = pFrame->pkt_size;
					int Frame_pkt_presentTimestamp = pFrame->pkt_pts;
					int Frame_pkt_decodeTimeStamp = pFrame->pkt_dts;

					printf("*****************Frame**%d*****************\n", pFrame->type);
	//				printf("LineSize[%d],wid[%d]hei[%d]	pktpos[%d]	pktDura[%d]	pktsize[%d]pts[%d]dts[%d]\n\n\n"
	//					,FrameLineSize, FrameWid, FrameHei, Frame_PacketPos,
	//					Frame_PacketDuration, Frame_PacketSize,
	//					Frame_pkt_presentTimestamp,Frame_pkt_decodeTimeStamp );
					int nSecond = Frame_pkt_presentTimestamp % 1000;
					int nMin = Frame_pkt_presentTimestamp / 1000 % 60;
					int nHour = Frame_pkt_presentTimestamp / 1000 / 60 % 24; 
					int nSecond2 = Frame_pkt_decodeTimeStamp % 1000;
					int nMin2 = Frame_pkt_decodeTimeStamp / 1000 % 60;
					int nHour2 = Frame_pkt_decodeTimeStamp / 1000 / 60 % 24; 
					printf("presentTime:%02d:%02d:%04d	DecodeTime:%02d:%02d:%04d\n", 
						nHour, nMin, nSecond, nHour2, nMin2, nSecond2);
					
					g_VideoFrameCount++;
					g_TimestampList.push_back(pFrame->pkt_pts);
				}
				else if(packet->stream_index == nAudioIndex)
				{

				}
			}
			else
			{
				char szBuffer[260] = {0};
				av_strerror(nDecodeRet, szBuffer, 260);
				int i = 0;
			}
			
		}	
		av_free(packet);
		avcodec_free_frame(&pFrame);
	}
	// Show
	DWORD dwWidth = pVedioCodecContext->width;			// ÊÓÆµwitdh
	DWORD dwHeight = pVedioCodecContext->height;		// ÊÓÆµheight
	pMainFrame = avcodec_alloc_frame();// MainFrame
	pMemFrame = avcodec_alloc_frame();// MemFrame
	
	DWORD dwSize = avpicture_get_size(PIX_FMT_YUV420P, dwWidth, dwHeight);
	pszShowBuffer = (uint8_t*)av_malloc(dwSize);
	avpicture_fill((AVPicture*)pMainFrame, pszShowBuffer, PIX_FMT_YUV420P, dwWidth, dwHeight);
	// SDL
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_WINDOW_BORDERLESS))	goto END;
	
	SDL_Window* sdlWindow_ = SDL_CreateWindow("BaseWindow",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		dwWidth,
		dwHeight,
		SDL_WINDOW_OPENGL);
	SDL_Window* sdlWindow = SDL_CreateWindow("QuanMedia",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		dwWidth,
		dwHeight,
		SDL_WINDOW_SHOWN);
	if(sdlWindow == NULL)	goto END;

	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(
		sdlWindow, 
		-1, //2D
		0);
	if(sdlRenderer == NULL)	goto END;
	SDL_DestroyWindow(sdlWindow_);
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
	av_dump_format(pFormatContext, 0, szFilePath, 0);		// ¼ì²éÊÇ·ñ·ûºÏ¹æ·¶
	struct SwsContext* img_convert_ctx;

	img_convert_ctx = sws_getContext(
		dwWidth,
		dwHeight,
		pVedioCodecContext->pix_fmt,
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
	
//	int64_t timestamp = g_TimestampList.at(g_VideoFrameCount/2);
//	int nRet = av_seek_frame(pFormatContext, nVedioIndex, timestamp, AVSEEK_FLAG_FRAME);
	while(true)
	{
		SDL_WaitEvent(&event);
		if(event.type != THREADID)	continue;
		DWORD intRet = av_read_frame(pFormatContext, packet);
		if(intRet >= 0)
		{
			if(packet->stream_index == nVedioIndex)
			{
				intRet = avcodec_decode_video2(pVedioCodecContext,
						pMemFrame, 
						&got_picture, 
						packet);
				if(intRet < 0)	goto END;

				if(got_picture)
				{
					sws_scale(img_convert_ctx,
						(const uint8_t* const*)pMemFrame->data,
						pMemFrame->linesize,
						0,
						dwHeight,
						pMainFrame->data,
						pMainFrame->linesize);
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
	if(pVedioCodecContext)
		avcodec_close(pVedioCodecContext);
	if(pAudioCodecContext)
		avcodec_close(pAudioCodecContext);
	if(pFormatContext)
	{
		avformat_close_input(&pFormatContext);
		avformat_free_context(pFormatContext);		// free
	}
	
	return true;
}
