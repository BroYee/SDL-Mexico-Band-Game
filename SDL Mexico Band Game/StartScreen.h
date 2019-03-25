#pragma once

class STARTSCREEN
{
private:
	BUTTON* playButton;
	BUTTON* howToButton;
	BUTTON* exitButton;
	BUTTON* creditButton;
	BUTTON* inHowToGoBackButton;
	BUTTON* inCreditGoBackButton;

	SDL_Texture* startScreenBg;
	SDL_Texture* howToScreenBg;
	SDL_Texture* creditScreenBg;

	int state; // show whether it's creditScreen or start-- or howTo--



public:
	void Init(SDL_Renderer* screen);
	void Update(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState);
	void Render(SDL_Renderer* screen);
	void Release();

	void ShowHowToScreen();
	void ShowCreditScreen();
	void GoBack();



};