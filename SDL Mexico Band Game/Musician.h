#pragma once

class MUSICIAN_INFO
{
private: 
	float m_delayPerAnimation;
	bool m_nowPlaying;
	int m_animationSpeed;

public:
	MUSICIAN_INFO(float delay, bool nowPlaying, int animationSpeed) :m_delayPerAnimation(delay), m_nowPlaying(nowPlaying), m_animationSpeed(animationSpeed) {}

};

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
	SDL_Texture* restingSprite;
	float* playAnimSpriteDelay;
	bool isReleased;
	float m_startTime = 0;
	bool isResting = false;
	float animSpeed = 1.0f;

public:

	void Init(SDL_Renderer* screen, const char* imgName, int nX, int nY, int _playAnimSpriteNum, float _playAnimSpriteDelay[]);

	void Update(SDL_Renderer* screen, float fAcculTime);
	void Render(SDL_Renderer* screen);
	void Release();

	void Play(float fAcculTime);
	void LoadNextSpriteWithDelay(float fAcculTime);

	void StartPlay();
	void StopPlay();

	void ChangeDelayPerAnimation(float delay);

	bool IsReleased() {	return isReleased; }
	void Rest();
	void StopRest();

	void SetAnimationSpeed(float speed);

	/*void ResetAnimationSpeed();
	void DoubleAnimationSpeed();
	void HalfAnimationSpeed();*/

	bool IsPlaying() { return isPlaying; }
	bool IsResting() { return isResting; }

	

};

