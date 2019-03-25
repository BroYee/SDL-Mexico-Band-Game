#include "stdafx.h"

void BUTTON::InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, const char* szOver, int x, int y, int(*f)(void))
{
	SDL_Surface* imgTemp;

	imgTemp = SDL_LoadBMP(szUp);
	Uint32 colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //색깔 키 값 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //색깔 키 값 설정
	imgUp = SDL_CreateTextureFromSurface(screen, imgTemp);
	SDL_FreeSurface(imgTemp);

	imgTemp = SDL_LoadBMP(szDown);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //색깔 키 값 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //색깔 키 값 설정
	imgDown = SDL_CreateTextureFromSurface(screen, imgTemp);

	imgTemp = SDL_LoadBMP(szOver);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //색깔 키 값 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //색깔 키 값 설정
	imgOver = SDL_CreateTextureFromSurface(screen, imgTemp);

	imgCurrent = imgUp;

	rtClip = new SDL_Rect;
	rtClip->x = x;
	rtClip->y = y;
	rtClip->w = imgTemp->w;
	rtClip->h = imgTemp->h;

	SetCoord(x, y);
	SetVisible(true);

	func = f;

	SDL_FreeSurface(imgTemp);

}

void BUTTON::Release()
{
	if (isDeleted) return;
	if (imgUp != NULL)	SDL_DestroyTexture(imgUp);
	if (imgDown != NULL)	SDL_DestroyTexture(imgDown);

	isDeleted = true;

	delete(this);
}

void BUTTON::Draw(SDL_Renderer* screen)
{
	if (!bIsVisible) return;
	if ((int)isDeleted == 221) printf("\nthis has been deleted\n\n");
	else SDL_RenderCopy(screen, imgCurrent, NULL, rtClip);
}

BUTTON::eButtonState BUTTON::GetState()
{
	if (imgCurrent == imgDown)
		return BUTTON::eButtonState::BUTTONDOWN;
	else
		return BUTTON::eButtonState::BUTTONUP;
}

void BUTTON::ClickDown()
{
	sndPlaySound(L"Musics/DownButtonSound.wav", SND_ASYNC);
	imgCurrent = imgDown;
}

void BUTTON::ClickUp(CSystem* system)
{
	imgCurrent = imgUp; //클릭업상태로 변경
	static float startTime = 0;
	static bool playButtonClicked = false;
	static bool pauseButtonClicked = false;

	if (func != 0)
	{
 		switch (func())
		{
		case 0:  // Exit Button
			isDeleted = true;
			ExitGame(system);
			break;
		case 1:  // Start Button
			system->startScreen->Release();
			StartGame(system->mainGame, system->m_pRender);
			system->state = 2;
			break;
		case 2:  // How To Button
			system->startScreen->ShowHowToScreen();
			break;
		case 3:  // Credit Button
			system->startScreen->ShowCreditScreen();
			break;
		case 4:  // Go Back Button from howto,credit
			system->startScreen->GoBack();
			break;
		case 5:  // Go Back Button from MainGame
			system->mainGame->Release();
			GoToStart(system->startScreen, system->m_pRender);
			system->state = 1;
			break;
		case 6:  // Music Up Button
			system->mainGame->MusicIndexUp();
			break;
		case 7:  // Music Down Button
			system->mainGame->MusicIndexDown();
			break;
		case 8: // PlayButton
		{
			system->mainGame->PlayButtonSetVisible(false);
			system->mainGame->PauseButtonSetVisible(true);
			system->mainGame->PlayMusic(system->m_fAcculTime);

			playButtonClicked = true;
		}
		case 9: // PauseButton
		{
			if (playButtonClicked)
			{
				startTime = system->CTimeManager::m_fAcculTime;
				playButtonClicked = false;
			}

			if (system->CTimeManager::m_fAcculTime >= startTime + 0.3f)
			{
				system->mainGame->PauseButtonSetVisible(false);
				system->mainGame->PlayButtonSetVisible(true);
				system->mainGame->PauseMusic();

				pauseButtonClicked = true;
			}
			break;
		}

		}
	}
}

bool BUTTON::IsOver(int px, int py)
{
	if (isDeleted || rtClip == nullptr) printf("\nthis has been deleted\n\n");
	else
	{
		if ((px >= nX) && (px < (nX + rtClip->w)))
		{
			if ((py >= nY) && (py < (nY + rtClip->h)))
			{
				imgCurrent = imgOver;
				return true;
			}
		}
	}
	return false;
}

void BUTTON::Toggle()
{
	if (imgCurrent == imgUp)
		imgCurrent = imgDown;
	else
		imgCurrent = imgUp;
}

void BUTTON::ResetOnDown()
{
	imgCurrent = imgDown;
}

void BUTTON::ResetOnUp()
{
	imgCurrent = imgUp;
}

void BUTTON::ResetOnOver()
{
	imgCurrent = imgOver;
}

void BUTTON::SetCoord(int x, int y)
{
	nX = x;
	nY = y;
}

void BUTTON::SetRect(int x, int y, int w, int h)
{
	rtClip->x = x;
	rtClip->y = y;
	rtClip->w = w;
	rtClip->h = h;
}

void BUTTON::SetVisible(bool visible)
{
	bIsVisible = visible;
}

bool BUTTON::IsVisible()
{
	return bIsVisible;
}

void BUTTON::MouseDown(int px, int py)
{
	if (IsOver(px, py) && IsVisible())
	{
		ClickDown();
	}
}

void BUTTON::MouseUp(CSystem* system, int px, int py)
{
	if (IsOver(px, py) && IsVisible()) //마우스가 버튼 위에 있고 보이는 상태면
	{
		ClickUp(system); //클릭 업 상태로 변경
		ResetOnUp(); //이미지 리셋
	}
}

SDL_Texture* BUTTON::GetCurrentImg()
{
	return imgCurrent;
}

SDL_Rect* BUTTON::GetRtClip()
{
	return rtClip;
}

void BUTTON::ExitGame(CSystem* system)
{
	system->Terminate();
}

void BUTTON::StartGame(MAINGAME*& mainGame, SDL_Renderer* screen)
{
	mainGame = new MAINGAME;
	mainGame->Init(screen);
}

void BUTTON::GoToStart(STARTSCREEN*& startScreen, SDL_Renderer* screen)
{
	startScreen = new STARTSCREEN;
	startScreen->Init(screen);

}
