#include "stdafx.h"


void MUSICIAN::Init(SDL_Renderer* screen, const char* imgName, int nX, int nY, int _playAnimSpriteNum, float _playAnimSpriteDelay[])
{
	playAnimSpriteNum = _playAnimSpriteNum;
	printf("startNum : %d\n", playAnimSpriteNum);
	playAnimSpriteIndex = 0;
	isPlaying = false;
	if (playAnimSpriteNum != 0) playAnimSpriteDelay = new float[playAnimSpriteNum];
	for (int i = 0; i < playAnimSpriteNum; i++)
		playAnimSpriteDelay[i] = _playAnimSpriteDelay[i];

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

}

void MUSICIAN::Update(SDL_Renderer* screen, float fAcculTime)
{
	if (!isPlaying) currentSprite = idleSprite;
	else Play(fAcculTime);
		
}

void MUSICIAN::Render(SDL_Renderer* screen)
{
	if (isReleased == true || currentSprite == NULL) return;
	SDL_RenderCopy(screen, currentSprite, NULL, rtClip);

}

void MUSICIAN::Release()
{
	if (rtClip != NULL) delete rtClip;

	//delete playAnimSpriteDelay;

	if (currentSprite != NULL) SDL_DestroyTexture(currentSprite);

	if (playAnimSpriteNum < 10 && playAnimSpriteNum >= 0)
	{
		for (int i = 0; i < playAnimSpriteNum; i++)
		{
			printf("endNum : %d\n", playAnimSpriteNum);
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
	{
		playAnimSpriteIndex = 0;
	}
	
	static float startTime = fAcculTime;

	if (fAcculTime >= startTime + playAnimSpriteDelay[playAnimSpriteIndex - 1])
	{
		printf("fAcculTime : %f // playAnimSpriteIndex : %d\n", fAcculTime, playAnimSpriteIndex);

		currentSprite = playAnimSprites[playAnimSpriteIndex];
		playAnimSpriteIndex++;
		startTime = fAcculTime;
	}

}

void MUSICIAN::StartPlay()
{
	printf("StartPlay\n");
	isPlaying = true;
}

void MUSICIAN::StopPlay()
{
	printf("StopPlay\n");
	isPlaying = false;
}
