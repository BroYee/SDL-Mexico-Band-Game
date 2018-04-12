#include "stdafx.h"

#define PlayButtonImgUpPath "./Images/inStartPlayButtonUp.bmp"
#define PlayButtonImgDownPath "./Images/inStartPlayButtonDown.bmp"

#define HowToButtonImgUpPath "./Images/inStartHowToButtonUp.bmp"
#define HowToButtonImgDownPath "./Images/inStartHowToButtonDown.bmp"

#define ExitButtonImgUpPath "./Images/inStartExitButtonUp.bmp"
#define ExitButtonImgDownPath "./Images/inStartExitButtonDown.bmp"

#define CreditButtonImgUpPath "./Images/inStartCreditButtonUp.bmp"
#define CreditButtonImgDownPath "./Images/inStartCreditButtonDown.bmp"


int InStartPressPlayButton()
{
	printf("InStartPressStartButton\n");
	return 1;
}

int InStartPressHowToButton()
{
	printf("InStartPressHowToButton\n");
	return 2;
}

int InStartPressExitButton()
{
	printf("InStartPressExitButton\n");
	return 0;
	
}

int InStartPressCreditButton()
{
	printf("InStartPressCreditButton\n");
	return 3;
}


void STARTSCREEN::Init(SDL_Renderer* screen)
{

	SDL_Surface* tempSurface = SDL_LoadBMP("./Images/startScreenBg.bmp");
	startScreenBg = SDL_CreateTextureFromSurface(screen, tempSurface);
	SDL_FreeSurface(tempSurface);

	playButton = new BUTTON;
	playButton->InitButton(screen, PlayButtonImgUpPath, PlayButtonImgDownPath, 560, 340, InStartPressPlayButton);
	
	howToButton = new BUTTON;
	howToButton->InitButton(screen, HowToButtonImgUpPath, HowToButtonImgDownPath, 300, 530, InStartPressHowToButton);

	exitButton = new BUTTON;
	exitButton->InitButton(screen, ExitButtonImgUpPath, ExitButtonImgDownPath, 630, 540, InStartPressExitButton);

	creditButton = new BUTTON;
	creditButton->InitButton(screen, CreditButtonImgUpPath, CreditButtonImgDownPath, 880, 530, InStartPressCreditButton);
	
}

void STARTSCREEN::Update(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState)
{
	if (mouseState.btn[MouseButton::LEFT] == true)
	{
		playButton->MouseDown(mouseState.x, mouseState.y);
		howToButton->MouseDown(mouseState.x, mouseState.y);
		exitButton->MouseDown(mouseState.x, mouseState.y);
		creditButton->MouseDown(mouseState.x, mouseState.y);
	}
	else if (mouseState.btn[MouseButton::LEFT] != true)
	{
		playButton->MouseUp(system, mouseState.x, mouseState.y);
		howToButton->MouseUp(system, mouseState.x, mouseState.y);
		exitButton->MouseUp(system, mouseState.x, mouseState.y);
		creditButton->MouseUp(system, mouseState.x, mouseState.y);
	}


}

void STARTSCREEN::Render(SDL_Renderer* screen)
{
	SDL_Rect* rtStartScreenBg = new SDL_Rect;
	rtStartScreenBg->x = 0;
	rtStartScreenBg->y = 0;
	rtStartScreenBg->w = 1280;
	rtStartScreenBg->h = 720;
	SDL_RenderCopy(screen, startScreenBg, NULL, rtStartScreenBg);
	delete rtStartScreenBg;

	playButton->Draw(screen);
	howToButton->Draw(screen);
	exitButton->Draw(screen);
	creditButton->Draw(screen);
}

void STARTSCREEN::Release()
{
	if (this == NULL) return;

	SDL_DestroyTexture(startScreenBg);

	playButton->Release();
	howToButton->Release();
	exitButton->Release();
	creditButton->Release();

}


