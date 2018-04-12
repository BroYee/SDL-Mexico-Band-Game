#pragma once

MUSICIAN;

class MAINGAME
{
private:
	BUTTON* pauseButton;
	BUTTON* mainButton;

	SDL_Texture* gameScreenBg;

	MUSICIAN* guitar;
	MUSICIAN* cactus;
	MUSICIAN* singer;
	MUSICIAN* barTender;
	MUSICIAN* dog;

public:
	void Init(SDL_Renderer* screen);
	void Update(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState);
	void Render(SDL_Renderer* screen);
	void Release();

};



