#include "stdafx.h"

void MUSICIAN::Init(SDL_Renderer* screen, const char* imgName, int nX, int nY, int _playAnimSpriteNum, float _playAnimSpriteDelay[])
{
	playAnimSpriteNum = _playAnimSpriteNum;
	playAnimSpriteIndex = 0;
	isPlaying = false;
	if (playAnimSpriteNum != 0)
	{
		playAnimSpriteDelay = new float[playAnimSpriteNum];
	}
	for (int i = 0; i < playAnimSpriteNum; i++)
	{
		playAnimSpriteDelay[i] = _playAnimSpriteDelay[i];
	}

	

	char tempPath[128] = "./Images/Musicians/";
	strcat(tempPath, imgName);
	strcat(tempPath, "/idleSprite");
	strcat(tempPath, imgName);
	strcat(tempPath, ".bmp");
	SDL_Surface* tempSurface = SDL_LoadBMP(tempPath);
	Uint32 colorkey = SDL_MapRGB(tempSurface->format, 255, 0, 255); //»ö±ò Å° °ª
	SDL_SetColorKey(tempSurface, SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤
	idleSprite = SDL_CreateTextureFromSurface(screen, tempSurface);
	currentSprite = idleSprite;

	memset(tempPath, '\0', 128);
	strcat(tempPath, "./Images/Musicians/");
	strcat(tempPath, imgName);
	strcat(tempPath, "/restingSprite");
	strcat(tempPath, imgName);
	strcat(tempPath, ".bmp");
	tempSurface = SDL_LoadBMP(tempPath);
	colorkey = SDL_MapRGB(tempSurface->format, 255, 0, 255);
	SDL_SetColorKey(tempSurface, SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤
	restingSprite = SDL_CreateTextureFromSurface(screen, tempSurface);

	rtClip = new SDL_Rect;
	rtClip->x = nX;
	rtClip->y = nY;
	rtClip->w = tempSurface->w;
	rtClip->h = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	
	
	SDL_Surface** tempSurfaces;
	tempSurfaces = new SDL_Surface*[playAnimSpriteNum];
	playAnimSprites = new SDL_Texture*[playAnimSpriteNum];
	
	for (int i = 0; i < playAnimSpriteNum; i++)
	{
		char longTempPath[128] = "./Images/Musicians/";
		strcat(longTempPath, imgName);
		strcat(longTempPath, "/playAnimSprites");
		strcat(longTempPath, imgName);

		char _tempPath[100];
		sprintf(_tempPath, "%d.bmp", i);
		strcat(longTempPath, _tempPath);

		tempSurfaces[i] = SDL_LoadBMP(longTempPath); if (tempSurfaces[i] == NULL) printf("tempSurfaces[%d] is NULL\n", i);
		Uint32 colorkey = SDL_MapRGB(tempSurfaces[i]->format, 255, 0, 255); //»ö±ò Å° °ª
		SDL_SetColorKey(tempSurfaces[i], SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤

		playAnimSprites[i] = SDL_CreateTextureFromSurface(screen, tempSurfaces[i]);
	}
	for (int i = 0; i < playAnimSpriteNum; i++)
	{
		SDL_FreeSurface(tempSurfaces[i]);
	}

	isReleased = false;

}

void MUSICIAN::Update(SDL_Renderer* screen, float fAcculTime)
{
	if (isResting) currentSprite = restingSprite;
	else if (!isPlaying) currentSprite = idleSprite;
	else Play(fAcculTime);
}

void MUSICIAN::Render(SDL_Renderer* screen)
{
	if (isReleased == true || currentSprite == NULL) return;
	SDL_RenderCopy(screen, currentSprite, NULL, rtClip);
}

void MUSICIAN::Release()
{
	if (isReleased) return;
	if (rtClip != NULL) delete rtClip;

	if (currentSprite != NULL) SDL_DestroyTexture(currentSprite);

	if (playAnimSpriteNum < 10 && playAnimSpriteNum >= 0)
	{
		for (int i = 0; i < playAnimSpriteNum; i++)
		{
			if (playAnimSprites[i] != NULL) SDL_DestroyTexture(playAnimSprites[i]);
		}
	}

	SDL_DestroyTexture(idleSprite);

	isReleased = true;

	//delete this;
}

void MUSICIAN::Play(float fAcculTime)
{
	LoadNextSpriteWithDelay(fAcculTime);
}

void MUSICIAN::LoadNextSpriteWithDelay(float fAcculTime)
{
	if (isReleased == true) return;

	if (playAnimSpriteIndex > playAnimSpriteNum)
	// if last animation sprite was end of the animation
	{
		playAnimSpriteIndex = 0;
		// set first animation sprite for current animation sprite
	}

	if (m_startTime == 0) m_startTime = fAcculTime;
	// if it is start of animation save current time to use it for animation

	if (fAcculTime >= m_startTime + (playAnimSpriteDelay[playAnimSpriteIndex - 1] / animSpeed))
	// if it's time to load next animation sprite
	{
		if (playAnimSpriteIndex >= 0 && playAnimSpriteIndex <= (playAnimSpriteNum - 1))		
			currentSprite = playAnimSprites[playAnimSpriteIndex];

		playAnimSpriteIndex++;
		m_startTime = fAcculTime;
	}
}


void MUSICIAN::StartPlay()
{
	isPlaying = true;
}

void MUSICIAN::StopPlay()
{
	isPlaying = false;
	playAnimSpriteIndex = 0;
}

void MUSICIAN::ChangeDelayPerAnimation(float delay)
{
	
	//cout << endl << playAnimSpriteDelay[playAnimSpriteNum - 1] << endl;
	playAnimSpriteDelay[playAnimSpriteNum - 1] = delay;
	//cout << playAnimSpriteDelay[playAnimSpriteNum - 1] << endl;
}

void MUSICIAN::Rest()
{
	isResting = true;
}

void MUSICIAN::StopRest()
{
	isResting = false;
}

void MUSICIAN::SetAnimationSpeed(float speed)
{
	animSpeed = speed;
}

//void MUSICIAN::ResetAnimationSpeed()
//{
//	animSpeedDoubled = 0;
//}
//
//void MUSICIAN::DoubleAnimationSpeed()
//{
//	animSpeedDoubled = 1;
//}
//
//void MUSICIAN::HalfAnimationSpeed()
//{
//	animSpeedDoubled = - 1;
//}