#include "stdafx.h"

void BUTTON::InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, int x, int y, int(*f)(void))
{
	SDL_Surface* imgTemp;

	imgTemp = SDL_LoadBMP(szUp);
	Uint32 colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //���� Ű �� 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //���� Ű �� ����
	imgUp = SDL_CreateTextureFromSurface(screen, imgTemp);
	SDL_FreeSurface(imgTemp);

	imgTemp = SDL_LoadBMP(szDown);
	colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //���� Ű �� 
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //���� Ű �� ����
	imgDown = SDL_CreateTextureFromSurface(screen, imgTemp);

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
	if ((int)isDeleted == 221) return;
	if (imgUp != 0)	SDL_DestroyTexture(imgUp);
	if (imgDown != 0)	SDL_DestroyTexture(imgDown);

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
	imgCurrent = imgDown;
}

void BUTTON::ClickUp(CSystem* system)
{
	imgCurrent = imgUp; //Ŭ�������·� ����
	if (func != 0)
	{
 		switch (func())
		{
		case 0:
			isDeleted = true;
			ExitGame(system);
			break;
		case 1:
			system->startScreen->Release();
			StartGame(system->mainGame, system->m_pRender);
			system->state = 2;
			break;
		case 2:
			StartHowTo();
			break;
		case 3:
			StartCredit();
			break;
		case 4:

			break;
		case 5:
			system->mainGame->Release();
			GoToStart(system->startScreen, system->m_pRender);
			system->state = 1;
			break;
		}
	}
}

bool BUTTON::IsOver(int px, int py) //��ġ ���ϴ� �Լ�
{
	if ((int)isDeleted == 221) printf("\nthis has been deleted\n\n");
	else
	{
		printf("IsOver %d\n", isDeleted);
		if ((px >= nX) && (px < (nX + rtClip->w)))
		{
			if ((py >= nY) && (py < (nY + rtClip->h)))
			{
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

void BUTTON::ResetOnUp()
{
	imgCurrent = imgUp;
}

void BUTTON::SetCoord(int x, int y)
{
	nX = x;
	nY = y;
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
	if (IsOver(px, py) && IsVisible()) //���콺�� ��ư ���� �ְ� ���̴� ���¸�
	{
		ClickUp(system); //Ŭ�� �� ���·� ����
		ResetOnUp(); //�̹��� ����
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

void BUTTON::StartHowTo()
{


}

void BUTTON::StartCredit()
{


}

void BUTTON::GoToStart(STARTSCREEN*& startScreen, SDL_Renderer* screen)
{
	startScreen = new STARTSCREEN;
	startScreen->Init(screen);

}

