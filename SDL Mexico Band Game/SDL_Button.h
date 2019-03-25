#pragma once

#include "C:\\SDL2-2.0.8\\include\\sdl.h"
#include "C:\\SDL2-2.0.8\\include\\sdl_main.h"

#pragma comment(lib, "C:\\SDL2-2.0.8\\lib\\x86\\SDL2.lib")
#pragma comment(lib, "C:\\SDL2-2.0.8\\lib\\x86\\SDL2main.lib")

class MAINGAME;
class CSystem;
class STARTSCREEN;

class BUTTON
{
private:
	enum eButtonState { BUTTONDOWN, BUTTONUP };

	SDL_Texture* imgUp;
	SDL_Texture* imgDown;
	SDL_Texture* imgOver;
	SDL_Texture* imgCurrent;
	
	SDL_Rect* rtClip;

	int nX, nY;
	bool bIsVisible = true;

	bool isDeleted = false;

	int(*func)(void);

public:

	void InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, const char* szOver, int x, int y, int(*f)(void));
	void Release(); // 메모리 해제
	void Draw(SDL_Renderer* screen); // 버튼 그리기

	eButtonState GetState();
	void ClickDown();
	void ClickUp(CSystem* system);

	bool IsOver(int px, int py); // 마우스가 버튼 위
	void Toggle(); // 반전
	void ResetOnDown();
	void ResetOnUp(); // 무조곤 Up 상태로
	void ResetOnOver();
	void SetCoord(int x, int y); // 좌표 수정
	void SetRect(int x, int y, int w, int h);
	void SetVisible(bool visible);
	bool IsVisible();

	void MouseDown(int px, int py);
	void MouseUp(CSystem* system, int px, int py);

	bool IsDeleted() { return isDeleted; }

	// StartScreen
	void StartGame(MAINGAME*& mainGame, SDL_Renderer* screen);
	void ExitGame(CSystem* system);

	//InGame
	void GoToStart(STARTSCREEN*& startScreen, SDL_Renderer* screen);

	SDL_Texture* GetCurrentImg();
	SDL_Rect* GetRtClip();
};

