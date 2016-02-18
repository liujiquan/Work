#include <sdl.h>
#include <windows.h>
#undef main
int SDLFunction1();
int SDLFunction2();
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
//	SDLFunction1();
	SDLFunction2();
	return 0;
}

int SDLFunction3()
{
	int nRet = -1;
	SDL_Rect rect;
	bool bRunning = true;
	int  i = 0;
	int width = 600;
	int height = 400;
	
	nRet = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
	if(nRet != 0)	return	0;
	SDL_Surface* screen = SDL_SetVideoMode(width, height, 0, 0);
	if(screen == NULL)			goto END;

	// ´´½¨¸²¸Ç
	SDL_Overlay* overLay = SDL_CreateYUVOverlay(width, height, SDL_YV12_OVERLAY, screen);
	if(overLay == NULL)			goto END;



	SDL_FreeYUVOverlay(overLay);
	SDL_FreeSurface(screen);
END:
	SDL_Quit();
	return 0;
}

void sdl_diplay(AVPicture* pFrame, SDL_Overlay* bmp, PixelFormat pixFormat, int width, int height)
{
	SDL_Rect rect;
	AVPicture frame;

	SDL_LockYUVOverlay(bmp);
	frame.data[0] = bmp->pixels[0];
	frame.data[1] = bmp->pixels[2];
	frame.data[2] = bmp->pixels[1];
	SDL_UnlockYUVOverlay(bmp);

}

int SDLFunction2()
{
	int nRet = -1;
	SDL_Rect rect;
	bool bRunning = true;
	int  i = 0;

	nRet = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
	if(nRet != 0)	return	0;
	
	SDL_Surface* memDCArr[3];
	memDCArr[0] = SDL_LoadBMP("C:\\Work\\Source\\Project\\SDLDemo1\\Win32_SDLDemo1\\bitmap1.bmp");
	memDCArr[1] = SDL_LoadBMP("C:\\Work\\Source\\Project\\SDLDemo1\\Win32_SDLDemo1\\bitmap2.bmp");
	memDCArr[2] = SDL_LoadBMP("C:\\Work\\Source\\Project\\SDLDemo1\\Win32_SDLDemo1\\bitmap3.bmp");

	SDL_Surface* pDestDC = SDL_SetVideoMode(600,400, 0, SDL_DOUBLEBUF|SDL_RESIZABLE);
	if(memDCArr[0] == NULL || memDCArr[1] == NULL || memDCArr[2] == NULL || pDestDC == NULL)	goto END;
	
	rect.x = 100;
	rect.y = 0;
	rect.w = memDCArr[0]->w * 2;
	rect.h = memDCArr[0]->h * 2;
	
	
	while(bRunning)
	{	
		SDL_BlitSurface(memDCArr[i], NULL, pDestDC, &rect);
		SDL_Flip(pDestDC);	// Update screen
		SDL_Delay(1000);		// delay
		i++;
		if(i == 3)	i = 0;
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				bRunning = FALSE;
			}
		}
	}

	SDL_FreeSurface(memDCArr[0]);
	SDL_FreeSurface(memDCArr[1]);
	SDL_FreeSurface(memDCArr[2]);
	SDL_FreeSurface(pDestDC);
END:
	SDL_Quit();

	return 0;
}

int SDLFunction1()
{
	int nRet = -1;
	
	nRet = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
	if(nRet != 0)	return	0;
	
	SDL_Surface* pWnd = SDL_LoadBMP("C:\\Work\\Source\\Project\\SDLDemo1\\Win32_SDLDemo1\\bitmap1.bmp");
	SDL_Surface* pWnd2 = SDL_SetVideoMode(600,400, 0, SDL_DOUBLEBUF|SDL_RESIZABLE);
	if(pWnd2 == NULL || pWnd == NULL)	goto END;
	
	SDL_BlitSurface(pWnd, NULL, pWnd2, NULL);
	SDL_Flip(pWnd2);	// µ¹×°
	SDL_Delay(2000);
	SDL_FreeSurface(pWnd);
	SDL_FreeSurface(pWnd2);
END:
	SDL_Quit();

	return 0;
}