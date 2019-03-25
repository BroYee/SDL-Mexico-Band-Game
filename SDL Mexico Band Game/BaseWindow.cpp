#include "stdafx.h"
#include "BaseWindow.h"

CBaseWindow::CBaseWindow(void) : m_bIsGameRun(SDL_TRUE)
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

CBaseWindow::~CBaseWindow(void)
{
	SDL_Quit();
}

bool CBaseWindow::Initialize()
{
	w = (int)GetSystemMetrics(SM_CXSCREEN);
	h = (int)GetSystemMetrics(SM_CYSCREEN);

	ZeroMemory(&devmode, sizeof(DEVMODE));
	devmode.dmSize = sizeof(DEVMODE);
	devmode.dmBitsPerPel = 32;
	devmode.dmPelsWidth = 1280;
	devmode.dmPelsHeight = 720;
	devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&devmode, CDS_FULLSCREEN);

	m_pWnd = SDL_CreateWindow("The Little Music Lovers", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
	m_pRender = SDL_CreateRenderer(m_pWnd, -1, 0);

	return true;
}

void CBaseWindow::Terminate()
{
	static bool isTerminated = false;
	if (isTerminated) return; 
	SDL_DestroyRenderer(m_pRender);
	SDL_DestroyWindow(m_pWnd);
	isTerminated = true;

	ZeroMemory(&devmode, sizeof(DEVMODE));
	devmode.dmSize = sizeof(DEVMODE);
	devmode.dmBitsPerPel = 32;
	devmode.dmPelsWidth = w;
	devmode.dmPelsHeight = h;
	devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&devmode, CDS_FULLSCREEN);
}