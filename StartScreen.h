#pragma once

class STARTSCREEN
{
private:
	BUTTON* playButton;
	BUTTON* howToButton;
	BUTTON* exitButton;
	BUTTON* creditButton;

	SDL_Texture* startScreenBg;



public:
	void Init(SDL_Renderer* screen);
	void Update(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState);
	void Render(SDL_Renderer* screen);
	void Release();


};