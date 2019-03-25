#include "stdafx.h"

#define PlayButtonImgUpPath "./Images/inStartPlayButtonUp.bmp"
#define PlayButtonImgDownPath "./Images/inStartPlayButtonDown.bmp"
#define PlayButtonImgOverPath "./Images/inStartPlayButtonOver.bmp"

#define HowToButtonImgUpPath "./Images/inStartHowToButtonUp.bmp"
#define HowToButtonImgDownPath "./Images/inStartHowToButtonDown.bmp"
#define HowToButtonImgOverPath "./Images/inStartHowToButtonOver.bmp"

#define ExitButtonImgUpPath "./Images/inStartExitButtonUp.bmp"
#define ExitButtonImgDownPath "./Images/inStartExitButtonDown.bmp"
#define ExitButtonImgOverPath "./Images/inStartExitButtonOver.bmp"

#define CreditButtonImgUpPath "./Images/inStartCreditButtonUp.bmp"
#define CreditButtonImgDownPath "./Images/inStartCreditButtonDown.bmp"
#define CreditButtonImgOverPath "./Images/inStartCreditButtonOver.bmp"

#define InHowToGoBackButtonImgUpPath "./Images/inHowToGoBackButtonUp.bmp"
#define InHowToGoBackButtonImgDownPath "./Images/inHowToGoBackButtonDown.bmp"
#define InHowToGoBackButtonImgOverPath "./Images/inHowToGoBackButtonOver.bmp"

#define InCreditGoBackButtonImgUpPath "./Images/inCreditGoBackButtonUp.bmp"
#define InCreditGoBackButtonImgDownPath "./Images/inCreditGoBackButtonDown.bmp"
#define InCreditGoBackButtonImgOverPath "./Images/inCreditGoBackButtonOver.bmp"


int InStartPressPlayButton()
{
	return 1;
}

int InStartPressHowToButton()
{
	return 2;
}

int InStartPressExitButton()
{
	return 0;
}

int InStartPressCreditButton()
{
	return 3;
}

int InHowToPressGoBackButton()
{
	return 4;
}

int InCreditPressGoBackButton()
{
	return 4;
}

void STARTSCREEN::Init(SDL_Renderer* screen)
{
	// Put image to each BgTexture
	SDL_Surface* tempSurface = SDL_LoadBMP("./Images/startScreenBg.bmp");
	startScreenBg = SDL_CreateTextureFromSurface(screen, tempSurface);

	tempSurface = SDL_LoadBMP("./Images/howToScreenBg.bmp");
	howToScreenBg = SDL_CreateTextureFromSurface(screen, tempSurface);

	tempSurface = SDL_LoadBMP("./Images/creditScreenBg.bmp");
	creditScreenBg = SDL_CreateTextureFromSurface(screen, tempSurface);

	SDL_FreeSurface(tempSurface);

	// Button Init
	playButton = new BUTTON;
	playButton->InitButton(screen, PlayButtonImgUpPath, PlayButtonImgDownPath, PlayButtonImgOverPath, 560, 340, InStartPressPlayButton);
	
	howToButton = new BUTTON;
	howToButton->InitButton(screen, HowToButtonImgUpPath, HowToButtonImgDownPath, HowToButtonImgOverPath, 300, 530, InStartPressHowToButton);

	exitButton = new BUTTON;
	exitButton->InitButton(screen, ExitButtonImgUpPath, ExitButtonImgDownPath, ExitButtonImgOverPath, 630, 540, InStartPressExitButton);

	creditButton = new BUTTON;
	creditButton->InitButton(screen, CreditButtonImgUpPath, CreditButtonImgDownPath, CreditButtonImgOverPath, 880, 530, InStartPressCreditButton);
	
	inHowToGoBackButton = new BUTTON;
	inHowToGoBackButton->InitButton(screen, InHowToGoBackButtonImgUpPath, InHowToGoBackButtonImgDownPath, InHowToGoBackButtonImgOverPath, 1246, 3, InHowToPressGoBackButton);

	inCreditGoBackButton = new BUTTON;
	inCreditGoBackButton->InitButton(screen, InCreditGoBackButtonImgUpPath, InCreditGoBackButtonImgDownPath, InCreditGoBackButtonImgOverPath, 1246, 3, InCreditPressGoBackButton);

	state = 0;

	// Start startScreen's background music
	mciSendString(L"play Musics/startMusic.mp3", NULL, 0, NULL);
}

void STARTSCREEN::Update(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState)
{
	if (mouseState.type == SDL_MOUSEMOTION)
	{
		if (state == 0)
		{
			if (!(playButton->IsOver(mouseState.x, mouseState.y))) playButton->ResetOnUp();
			if (!(howToButton->IsOver(mouseState.x, mouseState.y))) howToButton->ResetOnUp();
			if (!(exitButton->IsOver(mouseState.x, mouseState.y))) exitButton->ResetOnUp();
			if (!(creditButton->IsOver(mouseState.x, mouseState.y))) creditButton->ResetOnUp();
		}
		else if (state == 1)
		{
			if (!(inHowToGoBackButton->IsOver(mouseState.x, mouseState.y))) inHowToGoBackButton->ResetOnUp();
		}
		else if (state == 2)
		{
			if (!(inCreditGoBackButton->IsOver(mouseState.x, mouseState.y))) inCreditGoBackButton->ResetOnUp();
		}
	}
	if (mouseState.btn[MouseButton::LEFT] == true)
	{
		if (mouseState.type == SDL_MOUSEBUTTONDOWN)
		{
			if (state == 0)
			{
				playButton->MouseDown(mouseState.x, mouseState.y);
				howToButton->MouseDown(mouseState.x, mouseState.y);
				exitButton->MouseDown(mouseState.x, mouseState.y);
				creditButton->MouseDown(mouseState.x, mouseState.y);
			}
			else if (state == 1)
			{
				inHowToGoBackButton->MouseDown(mouseState.x, mouseState.y);
			}
			else if (state == 2)
			{
				inCreditGoBackButton->MouseDown(mouseState.x, mouseState.y);
			}
		}
		else if (mouseState.type == SDL_MOUSEBUTTONUP)
		{
			if (state == 0)
			{
				playButton->MouseUp(system, mouseState.x, mouseState.y);
				howToButton->MouseUp(system, mouseState.x, mouseState.y);
				exitButton->MouseUp(system, mouseState.x, mouseState.y);
				creditButton->MouseUp(system, mouseState.x, mouseState.y);
			}
			else if (state == 1)
			{
				inHowToGoBackButton->MouseUp(system, mouseState.x, mouseState.y);
			}
			else if (state == 2)
			{
				inCreditGoBackButton->MouseUp(system, mouseState.x, mouseState.y);
			}
		}
		else
		{
			if (state == 0)
			{
				if ((playButton->IsOver(mouseState.x, mouseState.y))) playButton->ResetOnDown();
				if ((howToButton->IsOver(mouseState.x, mouseState.y))) howToButton->ResetOnDown();
				if ((exitButton->IsOver(mouseState.x, mouseState.y))) exitButton->ResetOnDown();
				if ((creditButton->IsOver(mouseState.x, mouseState.y))) creditButton->ResetOnDown();
			}
			else if (state == 1)
			{
				if ((inHowToGoBackButton->IsOver(mouseState.x, mouseState.y))) inHowToGoBackButton->ResetOnDown();
			}
			else if (state == 2)
			{
				if ((inCreditGoBackButton->IsOver(mouseState.x, mouseState.y))) inCreditGoBackButton->ResetOnDown();
			}
		}
	}
	


}

void STARTSCREEN::Render(SDL_Renderer* screen)
{
	SDL_Rect tempRt; // Temp rect for StartScreenBg
	tempRt.x = 0;
	tempRt.y = 0;
	tempRt.w = 1280;
	tempRt.h = 720;

	SDL_RenderCopy(screen, startScreenBg, NULL, &tempRt);

	// Buttons of StartScreen
	playButton->Draw(screen);
	howToButton->Draw(screen);
	exitButton->Draw(screen);
	creditButton->Draw(screen);

	if (state == 1) // If state is howTo
	{		
		SDL_RenderCopy(screen, howToScreenBg, NULL, &tempRt);
	}
	else if (state == 2) // If state is credit
	{
		SDL_RenderCopy(screen, creditScreenBg, NULL, &tempRt);
	}

	// Button of howToScreen and creditScreen
	if (state == 1)
	{
		inHowToGoBackButton->Draw(screen);
	}
	else if (state == 2)
	{
		inCreditGoBackButton->Draw(screen);
	}

}

void STARTSCREEN::Release()
{
	if (this == NULL) return;

	mciSendString(L"stop Musics/startMusic.mp3", NULL, 0, NULL);

	SDL_DestroyTexture(startScreenBg);
	SDL_DestroyTexture(howToScreenBg);
	SDL_DestroyTexture(creditScreenBg);

	playButton->Release();
	howToButton->Release();
	exitButton->Release();
	creditButton->Release();
	inHowToGoBackButton->Release();
	inCreditGoBackButton->Release();
}

void STARTSCREEN::ShowHowToScreen()
{
	state = 1;
}

void STARTSCREEN::ShowCreditScreen()
{
	state = 2;
}

void STARTSCREEN::GoBack()
{
	state = 0; cout << "GoBack" << endl;
}
