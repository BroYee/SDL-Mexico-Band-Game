#include "stdafx.h"


#define InGamePauseButtonImgUpPath "./Images/pauseButtonUp.bmp"
#define InGamePauseButtonImgDownPath "./Images/pauseButtonDown.bmp"

#define InGameMainButtonImgUpPath "./Images/mainButtonUp.bmp"
#define InGameMainButtonImgDownPath "./Images/mainButtonDown.bmp"


int InGamePressPauseButton()
{
	printf("InGamePressPauseButton\n");
	return 4;
}

int InGamePressMainButton()
{
	printf("InGamePressMainButton\n");
	return 5;
}


void MAINGAME::Init(SDL_Renderer* screen)
{
	// Background
	SDL_Surface* tempSurface = SDL_LoadBMP("./Images/gameScreenBg.bmp");
	gameScreenBg = SDL_CreateTextureFromSurface(screen, tempSurface);
	SDL_FreeSurface(tempSurface);

	pauseButton = new BUTTON;
	pauseButton->InitButton(screen, InGamePauseButtonImgUpPath, InGamePauseButtonImgDownPath, 300, 400, InGamePressPauseButton);

	mainButton = new BUTTON;
	mainButton->InitButton(screen, InGameMainButtonImgUpPath, InGameMainButtonImgDownPath, 300, 600, InGamePressMainButton);
	
	// Musicians

	float* tempDelay = new float[0];
	tempDelay[0] = 1.0f;

	float* barTenderDelay = new float[4];
	barTenderDelay[0] = 1.5f;
	barTenderDelay[1] = 2.0f;
	barTenderDelay[2] = 3.0f;
	barTenderDelay[3] = 2.5f;

	guitar = new MUSICIAN;
	guitar->Init(screen, "Guitar", 80, 120, 0, tempDelay);
	
	cactus = new MUSICIAN;
	cactus->Init(screen, "Cactus", 255, 120, 0, tempDelay);

	singer = new MUSICIAN;
	singer->Init(screen, "Singer", 380, 120, 0, tempDelay);
	
	barTender = new MUSICIAN;
	barTender->Init(screen, "BarTender", 525, 120, 3, barTenderDelay);
	
	dog = new MUSICIAN;
	dog->Init(screen, "Dog", 680, 120, 0, tempDelay);

	
	barTender->StartPlay();
}

void MAINGAME::Update(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState)
{
	if (mouseState.btn[MouseButton::LEFT] == true)
	{
		pauseButton->MouseDown(mouseState.x, mouseState.y);
		mainButton->MouseDown(mouseState.x, mouseState.y);
	}
	if (mouseState.btn[MouseButton::LEFT] != true)
	{
		pauseButton->MouseUp(system, mouseState.x, mouseState.y);
		mainButton->MouseUp(system, mouseState.x, mouseState.y);
	}

	guitar->Update(screen, system->m_fAcculTime);
	cactus->Update(screen, system->m_fAcculTime);
	singer->Update(screen, system->m_fAcculTime);
	barTender->Update(screen, system->m_fAcculTime);
	dog->Update(screen, system->m_fAcculTime);

}

void MAINGAME::Render(SDL_Renderer* screen)
{
	SDL_Rect* rtGameScreenBg = new SDL_Rect;
	rtGameScreenBg->x = 0;
	rtGameScreenBg->y = 0;
	rtGameScreenBg->w = 1280;
	rtGameScreenBg->h = 720;
	SDL_RenderCopy(screen, gameScreenBg, NULL, rtGameScreenBg);
	delete rtGameScreenBg;

	pauseButton->Draw(screen);
	mainButton->Draw(screen);

	// Musicians
	guitar->Render(screen);
	cactus->Render(screen);
	singer->Render(screen);
	barTender->Render(screen);
	dog->Render(screen);

}

void MAINGAME::Release()
{
	dog->Release();
	barTender->Release();
	singer->Release();
	cactus->Release();
	guitar->Release();

	SDL_DestroyTexture(gameScreenBg);

	pauseButton->Release();
	mainButton->Release();

}




