#pragma once

class MUSICIAN
{
private:
	SDL_Texture* idleSprite;
	SDL_Texture** playAnimSprites;
	int playAnimSpriteNum;
	bool isPlaying = false;
	SDL_Rect* rtClip;
	int playAnimSpriteIndex;
	SDL_Texture* currentSprite;
	float* playAnimSpriteDelay;
	bool isReleased = false;

public:

	void Init(SDL_Renderer* screen, const char* imgName, int nX, int nY, int _playAnimSpriteNum, float _playAnimSpriteDelay[]);

	void Update(SDL_Renderer* screen, float fAcculTime);
	void Render(SDL_Renderer* screen);
	void Release();

	void Play(float fAcculTime);
	void LoadNextSpriteWithDelay(float fAcculTime);

	void StartPlay();
	void StopPlay();
};

