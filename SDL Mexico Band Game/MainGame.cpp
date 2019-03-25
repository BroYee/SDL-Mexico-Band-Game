#include "stdafx.h"

#define InGamePlayButtonImgUpPath "./Images/playButtonUp.bmp"
#define InGamePlayButtonImgDownPath "./Images/playButtonDown.bmp"
#define InGamePlayButtonImgOverPath "./Images/playButtonOver.bmp"

#define InGamePauseButtonImgUpPath "./Images/pauseButtonUp.bmp"
#define InGamePauseButtonImgDownPath "./Images/pauseButtonDown.bmp"
#define InGamePauseButtonImgOverPath "./Images/pauseButtonOver.bmp"

#define InGameGoBackButtonImgUpPath "./Images/inGameGoBackButtonUp.bmp"
#define InGameGoBackButtonImgDownPath "./Images/inGameGoBackButtonDown.bmp"
#define InGameGoBackButtonImgOverPath "./Images/inGameGoBackButtonOver.bmp"

#define InGameMusicUpButtonImgUpPath "./Images/musicUpButtonUp.bmp"
#define InGameMusicUpButtonImgDownPath "./Images/musicUpButtonDown.bmp"
#define InGameMusicUpButtonImgOverPath "./Images/musicUpButtonOver.bmp"

#define InGameMusicDownButtonImgUpPath "./Images/musicDownButtonUp.bmp"
#define InGameMusicDownButtonImgDownPath "./Images/musicDownButtonDown.bmp"
#define InGameMusicDownButtonImgOverPath "./Images/musicDownButtonOver.bmp"

bool forInput = false;


int InGamePressPlayButton()
{
	return 8;
}

int InGamePressPauseButton()
{
	return 9;
}

int InGamePressMainButton()
{
	return 5;
}

int InGamePressMusicUpButton()
{
	return 6;
}

int InGamePressMusicDownButton()
{
	return 7;
}

void MAINGAME::Init(SDL_Renderer* screen)
{
	// Background
	SDL_Surface* tempSurface = SDL_LoadBMP("./Images/gameScreenBg.bmp");
	gameScreenBg = SDL_CreateTextureFromSurface(screen, tempSurface);
	SDL_FreeSurface(tempSurface);

	playButton = new BUTTON;
	playButton->InitButton(screen, InGamePlayButtonImgUpPath, InGamePlayButtonImgDownPath, InGamePlayButtonImgOverPath, 65, 594, InGamePressPlayButton);
	playButton->SetVisible(true);

	pauseButton = new BUTTON;
	pauseButton->InitButton(screen, InGamePauseButtonImgUpPath, InGamePauseButtonImgDownPath, InGamePauseButtonImgOverPath, 65, 594, InGamePressPauseButton);
	pauseButton->SetVisible(false);

	goBackButton = new BUTTON;
	goBackButton->InitButton(screen, InGameGoBackButtonImgUpPath, InGameGoBackButtonImgDownPath, InGameGoBackButtonImgOverPath, 1246, 3, InGamePressMainButton);
	
	// Music list
	musicUpButton = new BUTTON;
	musicUpButton->InitButton(screen, InGameMusicUpButtonImgUpPath, InGameMusicUpButtonImgDownPath, InGameMusicUpButtonImgOverPath, 203, 42, InGamePressMusicUpButton);

	musicDownButton = new BUTTON;
	musicDownButton->InitButton(screen, InGameMusicDownButtonImgUpPath, InGameMusicDownButtonImgDownPath, InGameMusicDownButtonImgOverPath, 203, 164, InGamePressMusicDownButton);

	musicImgs = new SDL_Texture*[4];
	for (int i = 0; i < 5; i++)
	{
		char tempPath[128] = "./Images/musicImgs";
		char _tempPath[100];
		sprintf(_tempPath, "%d.bmp", i);
		strcat(tempPath, _tempPath);

		SDL_Surface* tempSurface = SDL_LoadBMP(tempPath);
		Uint32 colorkey = SDL_MapRGB(tempSurface->format, 255, 0, 255); //»ö±ò Å° °ª
		SDL_SetColorKey(tempSurface, SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤

		musicImgs[i] = SDL_CreateTextureFromSurface(screen, tempSurface);

		SDL_FreeSurface(tempSurface);
	}

	musicIndex = 0;

	// Musicians

	float* guitarDelay = new float[8];
	guitarDelay[0] = 0.1f;
	guitarDelay[1] = 0.1f;
	guitarDelay[2] = 0.1f;
	guitarDelay[3] = 0.1f;
	guitarDelay[4] = 0.1f;
	guitarDelay[5] = 0.1f;
	guitarDelay[6] = 0.1f;
	guitarDelay[7] = 0.2f;

	float* cactusDelay = new float[8];
	cactusDelay[0] = 0.2f;
	cactusDelay[1] = 0.2f;
	cactusDelay[2] = 0.2f;
	cactusDelay[3] = 0.2f;
	cactusDelay[4] = 0.2f;
	cactusDelay[5] = 0.2f;
	cactusDelay[6] = 0.2f;
	cactusDelay[7] = 0.2f;

	float* singerDelay = new float[7];
	singerDelay[0] = 0.2f;
	singerDelay[1] = 0.2f;
	singerDelay[2] = 0.2f;
	singerDelay[3] = 0.2f;
	singerDelay[4] = 0.2f;
	singerDelay[5] = 0.2f;
	singerDelay[6] = 0.3f;

	float* barTenderDelay = new float[8];
	barTenderDelay[0] = 0.15f;
	barTenderDelay[1] = 0.15f;
	barTenderDelay[2] = 0.15f;
	barTenderDelay[3] = 0.15f;
	barTenderDelay[4] = 0.15f;
	barTenderDelay[5] = 0.15f;
	barTenderDelay[6] = 0.15f;
	barTenderDelay[7] = 0.4f;

	float* dogDelay = new float[8];
	dogDelay[0] = 0.2f;
	dogDelay[1] = 0.2f;
	dogDelay[2] = 0.2f;
	dogDelay[3] = 0.2f;
	dogDelay[4] = 0.2f;
	dogDelay[5] = 0.2f;
	dogDelay[6] = 0.2f;
	dogDelay[7] = 0.4f;


	guitar = new MUSICIAN;
	guitar->Init(screen, "Guitar", 80, 120, 8, guitarDelay);
	
	cactus = new MUSICIAN;
	cactus->Init(screen, "Cactus", 255, 120, 8, cactusDelay);

	singer = new MUSICIAN;
	singer->Init(screen, "Singer", 380, 120, 7, singerDelay);
	
	barTender = new MUSICIAN;
	barTender->Init(screen, "BarTender", 525, 120, 8, barTenderDelay);
	
	dog = new MUSICIAN;
	dog->Init(screen, "Dog", 680, 120, 8, dogDelay);

	nowPlaying = false;
	musicPaused = false;

	srand((unsigned)time(NULL));

	musicStartTime = 0.0f;
	currentMusicTime = 0.0f;
	musicPauseTime = 0.0f;
	// MusicianAnimationData
	for (int i = 0; i < 5; i++)
	{
		musicianAnimationPlaying[i] = false;
	}

	if (forInput)
	{
		// OutFiles
		outFile[0][0].open("Data/guitarAngelusAnimationData.txt");
		outFile[0][1].open("Data/guitarMNAAnimationData.txt");
		outFile[0][2].open("Data/guitarPLAnimationData.txt");
		outFile[0][3].open("Data/guitarPCAnimationData.txt");
		outFile[0][4].open("Data/guitarRMAnimationData.txt");

		outFile[1][0].open("Data/cactusAngelusAnimationData.txt");
		outFile[1][1].open("Data/cactusMNAAnimationData.txt");
		outFile[1][2].open("Data/cactusPLAnimationData.txt");
		outFile[1][3].open("Data/cactusPCAnimationData.txt");
		outFile[1][4].open("Data/cactusRMAnimationData.txt");

		outFile[2][0].open("Data/singerAngelusAnimationData.txt");
		outFile[2][1].open("Data/singerMNAAnimationData.txt");
		outFile[2][2].open("Data/singerPLAnimationData.txt");
		outFile[2][3].open("Data/singerPCAnimationData.txt");
		outFile[2][4].open("Data/singerRMAnimationData.txt");

		outFile[3][0].open("Data/barTenderAngelusAnimationData.txt");
		outFile[3][1].open("Data/barTenderMNAAnimationData.txt");
		outFile[3][2].open("Data/barTenderPLAnimationData.txt");
		outFile[3][3].open("Data/barTenderPCAnimationData.txt");
		outFile[3][4].open("Data/barTenderRMAnimationData.txt");

		outFile[4][0].open("Data/dogAngelusAnimationData.txt");
		outFile[4][1].open("Data/dogMNAAnimationData.txt");
		outFile[4][2].open("Data/dogPLAnimationData.txt");
		outFile[4][3].open("Data/dogPCAnimationData.txt");
		outFile[4][4].open("Data/dogRMAnimationData.txt");
	}

	// InFiles
	inFile[0][0].open("Data/CompletedData/C_guitarAngelusAnimationData.txt");
	inFile[0][1].open("Data/CompletedData/C_guitarMNAAnimationData.txt");
	inFile[0][2].open("Data/CompletedData/C_guitarPLAnimationData.txt");
	inFile[0][3].open("Data/CompletedData/C_guitarPCAnimationData.txt");
	inFile[0][4].open("Data/CompletedData/C_guitarRMAnimationData.txt");

	inFile[1][0].open("Data/CompletedData/C_cactusAngelusAnimationData.txt");
	inFile[1][1].open("Data/CompletedData/C_cactusMNAAnimationData.txt");
	inFile[1][2].open("Data/CompletedData/C_cactusPLAnimationData.txt");
	inFile[1][3].open("Data/CompletedData/C_cactusPCAnimationData.txt");
	inFile[1][4].open("Data/CompletedData/C_cactusRMAnimationData.txt");

	inFile[2][0].open("Data/CompletedData/C_singerAngelusAnimationData.txt");
	inFile[2][1].open("Data/CompletedData/C_singerMNAAnimationData.txt");
	inFile[2][2].open("Data/CompletedData/C_singerPLAnimationData.txt");
	inFile[2][3].open("Data/CompletedData/C_singerPCAnimationData.txt");
	inFile[2][4].open("Data/CompletedData/C_singerRMAnimationData.txt");

	inFile[3][0].open("Data/CompletedData/C_barTenderAngelusAnimationData.txt");
	inFile[3][1].open("Data/CompletedData/C_barTenderMNAAnimationData.txt");
	inFile[3][2].open("Data/CompletedData/C_barTenderPLAnimationData.txt");
	inFile[3][3].open("Data/CompletedData/C_barTenderPCAnimationData.txt");
	inFile[3][4].open("Data/CompletedData/C_barTenderRMAnimationData.txt");

	inFile[4][0].open("Data/CompletedData/C_dogAngelusAnimationData.txt");
	inFile[4][1].open("Data/CompletedData/C_dogMNAAnimationData.txt");
	inFile[4][2].open("Data/CompletedData/C_dogPLAnimationData.txt");
	inFile[4][3].open("Data/CompletedData/C_dogPCAnimationData.txt");
	inFile[4][4].open("Data/CompletedData/C_dogRMAnimationData.txt");

	InitMusicianAnimationDelay();

	for (int i = 0; i < 5; i++)
		musicianAnimationIndex[i] = 0;

}

void MAINGAME::Update(float acculTime)
{
	static int index = 0;
	static bool wasPaused = true;

	m_acculTime = acculTime;

	if (index == 0) musicPauseStartTime = acculTime;
	
	if (musicPaused)
	{
		if (!wasPaused)
		{
			musicPauseStartTime = acculTime;
			wasPaused = true;
		}
	}
	else
	{
		if (wasPaused)
		{
			float tempMusicPauseTime = (acculTime - musicPauseStartTime);
			musicPauseTime += tempMusicPauseTime;
			wasPaused = false;
		}
	}

	if (nowPlaying && !musicPaused)
	{
		//if ((acculTime - musicStartTime - musicPauseTime) >= 0)
		currentMusicTime = (acculTime - musicStartTime - musicPauseTime);
	}

	cout << "CurrentMusicTime : " << currentMusicTime << endl;

	currentMusicImg = musicImgs[musicIndex];

	MusicStopCheck();

	guitar->SetAnimationSpeed(1);
	cactus->SetAnimationSpeed(1);
	singer->SetAnimationSpeed(1);
	barTender->SetAnimationSpeed(1);
	dog->SetAnimationSpeed(1);

	if (!nowPlaying)
	{
		guitar->ChangeDelayPerAnimation(drand(0.2f, 1.0f));
		cactus->ChangeDelayPerAnimation(drand(0.4f, 1.0f));
		singer->ChangeDelayPerAnimation(drand(0.2f, 3.0f));
		barTender->ChangeDelayPerAnimation(drand(0.2f, 4.0f));
		dog->ChangeDelayPerAnimation(drand(0.2f, 2.0f));

		barTender->StopRest();
		guitar->StopRest();
		cactus->StopRest();
		singer->StopRest();
		dog->StopRest();
	}
	else if (nowPlaying)
	{
		switch (musicIndex)
		{
		case 0:
			/*guitar->ChangeDelayPerAnimation(drand(0.2f, 0.4f));
			cactus->ChangeDelayPerAnimation(drand(0.4f, 0.5f));
			singer->ChangeDelayPerAnimation(drand(2.0f, 4.0f));
			dog->ChangeDelayPerAnimation(drand(0.2f, 0.4f));*/

			singer->SetAnimationSpeed(1.5f);
			cactus->SetAnimationSpeed(2.5f);
			dog->SetAnimationSpeed(2);
			barTender->SetAnimationSpeed(1.75f);

			guitar->Rest();

			barTender->StopRest();			
			cactus->StopRest();
			singer->StopRest();
			dog->StopRest();

			break;
		case 1:
			/*guitar->ChangeDelayPerAnimation(drand(3.0f, 5.0f));
			cactus->ChangeDelayPerAnimation(drand(3.0f, 5.0f));
			singer->ChangeDelayPerAnimation(drand(3.0f, 5.0f));
			barTender->ChangeDelayPerAnimation(drand(3.0f, 5.0f));
			dog->ChangeDelayPerAnimation(drand(3.0f, 5.0f));*/

			cactus->SetAnimationSpeed(1.0f);
			singer->SetAnimationSpeed(1.0f);
			dog->SetAnimationSpeed(0.5f);

			barTender->Rest();
			dog->Rest();

			singer->StopRest();
			guitar->StopRest();
			cactus->StopRest();

			break;
		case 2:
			/*guitar->ChangeDelayPerAnimation(drand(1.0f, 2.0f));
			cactus->ChangeDelayPerAnimation(drand(1.0f, 2.0f));
			singer->ChangeDelayPerAnimation(drand(1.0f, 3.0f));
			barTender->ChangeDelayPerAnimation(drand(1.0f, 4.0f));
			dog->ChangeDelayPerAnimation(drand(1.0f, 2.0f));*/

			guitar->SetAnimationSpeed(1.5f);
			dog->SetAnimationSpeed(2);

			barTender->Rest();

			guitar->StopRest();
			singer->StopRest();
			cactus->StopRest();			
			dog->StopRest();

			break;
		case 3:
			/*guitar->ChangeDelayPerAnimation(drand(0.2f, 0.8f));
			cactus->ChangeDelayPerAnimation(drand(0.4f, 2.0f));
			singer->ChangeDelayPerAnimation(drand(0.2f, 3.0f));
			barTender->ChangeDelayPerAnimation(drand(0.2f, 4.0f));
			dog->ChangeDelayPerAnimation(drand(0.2f, 2.0f));*/

			singer->SetAnimationSpeed(0.75f);

			cactus->Rest();
			dog->Rest();

			singer->StopRest();
			guitar->StopRest();
			barTender->StopRest();

			break;
		case 4:
			/*guitar->ChangeDelayPerAnimation(drand(0.2f, 5.0f));
			cactus->ChangeDelayPerAnimation(drand(0.4f, 5.0f));
			singer->ChangeDelayPerAnimation(drand(0.2f, 6.0f));
			barTender->ChangeDelayPerAnimation(drand(0.2f, 6.0f));
			dog->ChangeDelayPerAnimation(drand(0.2f, 5.0f));*/

			if (index % 3 == 0)
			{
				guitar->SetAnimationSpeed(2);
				cactus->SetAnimationSpeed(2);
				singer->SetAnimationSpeed(2);
				barTender->SetAnimationSpeed(1.5);
			}

			dog->Rest();

			cactus->StopRest();
			singer->StopRest();
			guitar->StopRest();
			barTender->StopRest();

			break;
		default:
			break;
		}
		if (!forInput)
		{
			MusicianAnimationManager();

			if (musicianAnimationPlaying[0]) guitar->StartPlay();
			else guitar->StopPlay();
			if (musicianAnimationPlaying[1]) cactus->StartPlay();
			else cactus->StopPlay();
			if (musicianAnimationPlaying[2]) singer->StartPlay();
			else singer->StopPlay();
			if (musicianAnimationPlaying[3]) barTender->StartPlay();
			else barTender->StopPlay();
			if (musicianAnimationPlaying[4]) dog->StartPlay();
			else dog->StopPlay();
		}
	}
	if (forInput)
	{
		if (musicPaused)
		{
			guitar->StopPlay();
			cactus->StopPlay();
			singer->StopPlay();
			barTender->StopPlay();
			dog->StopPlay();
		}
	}
	else if (musicPaused || !nowPlaying)
	{
		guitar->StopPlay();
		cactus->StopPlay();
		singer->StopPlay();
		barTender->StopPlay();
		dog->StopPlay();
	}

	index++;
}

void MAINGAME::MouseUpdate(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState)
{
	if (mouseState.type == SDL_MOUSEMOTION)
	{
		if (playButton->IsVisible()) if (!(playButton->IsOver(mouseState.x, mouseState.y))) playButton->ResetOnUp();
		if (pauseButton->IsVisible()) if (!(pauseButton->IsOver(mouseState.x, mouseState.y))) pauseButton->ResetOnUp();
		if (!(goBackButton->IsOver(mouseState.x, mouseState.y))) goBackButton->ResetOnUp();
		if (!(musicUpButton->IsOver(mouseState.x, mouseState.y))) musicUpButton->ResetOnUp();
		if (!(musicDownButton->IsOver(mouseState.x, mouseState.y))) musicDownButton->ResetOnUp();
	}
	if (mouseState.btn[MouseButton::LEFT] == true)
	{
		if (mouseState.type == SDL_MOUSEBUTTONDOWN)
		{
			if (playButton->IsVisible()) playButton->MouseDown(mouseState.x, mouseState.y);
			if (pauseButton->IsVisible()) pauseButton->MouseDown(mouseState.x, mouseState.y);
			goBackButton->MouseDown(mouseState.x, mouseState.y);
			musicUpButton->MouseDown(mouseState.x, mouseState.y);
			musicDownButton->MouseDown(mouseState.x, mouseState.y);
		}
		else if (mouseState.type == SDL_MOUSEBUTTONUP)
		{
			if (playButton->IsVisible()) playButton->MouseUp(system, mouseState.x, mouseState.y);
			if (pauseButton->IsVisible()) pauseButton->MouseUp(system, mouseState.x, mouseState.y);
			goBackButton->MouseUp(system, mouseState.x, mouseState.y);
			musicUpButton->MouseUp(system, mouseState.x, mouseState.y);
			musicDownButton->MouseUp(system, mouseState.x, mouseState.y);
		}
		else
		{
			if (playButton->IsVisible()) if ((playButton->IsOver(mouseState.x, mouseState.y))) playButton->ResetOnDown();
			if (pauseButton->IsVisible()) if ((pauseButton->IsOver(mouseState.x, mouseState.y))) pauseButton->ResetOnDown();
			if ((goBackButton->IsOver(mouseState.x, mouseState.y))) goBackButton->ResetOnDown();
			if ((musicUpButton->IsOver(mouseState.x, mouseState.y))) musicUpButton->ResetOnDown();
			if ((musicDownButton->IsOver(mouseState.x, mouseState.y))) musicDownButton->ResetOnDown();
		}
	}

	guitar->Update(screen, system->m_fAcculTime);
	cactus->Update(screen, system->m_fAcculTime);
	singer->Update(screen, system->m_fAcculTime);
	barTender->Update(screen, system->m_fAcculTime);
	dog->Update(screen, system->m_fAcculTime);
}

void MAINGAME::KeyboardUpdate(CSystem* system, bool input[])
{
	if (forInput)
	{
		// Guitar
		if (input[0] == true)
		{
			if (nowPlaying && !guitar->IsPlaying())
			{
				outFile[0][musicIndex] << currentMusicTime << endl;
			}
			guitar->StartPlay();
		}
		else if (input[0] == false)
		{
			if (nowPlaying && guitar->IsPlaying())
			{
				outFile[0][musicIndex] << currentMusicTime << endl;
			}
			guitar->StopPlay();
		}
		// Cactus
		if (input[1] == true)
		{
			if (nowPlaying && !cactus->IsPlaying())
			{
				outFile[1][musicIndex] << currentMusicTime << endl;
			}
			cactus->StartPlay();
		}
		else if (input[1] == false)
		{
			if (nowPlaying && cactus->IsPlaying())
			{
				outFile[1][musicIndex] << currentMusicTime << endl;
			}
			cactus->StopPlay();
		}
		// Singer
		if (input[2] == true)
		{
			if (nowPlaying && !singer->IsPlaying())
			{
				outFile[2][musicIndex] << currentMusicTime << endl;
			}
			singer->StartPlay();
		}
		else if (input[2] == false)
		{
			if (nowPlaying && singer->IsPlaying())
			{
				outFile[2][musicIndex] << currentMusicTime << endl;
			}
			singer->StopPlay();
		}
		// BarTender
		if (input[3] == true)
		{
			if (nowPlaying && !barTender->IsPlaying())
			{
				outFile[3][musicIndex] << currentMusicTime << endl;
			}
			barTender->StartPlay();
		}
		else if (input[3] == false)
		{
			barTender->StopPlay();
			if (nowPlaying && barTender->IsPlaying())
			{
				outFile[3][musicIndex] << currentMusicTime << endl;
			}
		}
		// Dog
		if (input[4] == true)
		{
			if (nowPlaying && !dog->IsPlaying())
			{
				outFile[4][musicIndex] << currentMusicTime << endl;
			}
			dog->StartPlay();
		}
		else if (input[4] == false)
		{
			if (nowPlaying && dog->IsPlaying())
			{
				outFile[4][musicIndex] << currentMusicTime << endl;
			}
			dog->StopPlay();
		}
	}
}


void MAINGAME::Render(SDL_Renderer* screen)
{
	SDL_Rect rtGameScreenBg;
	rtGameScreenBg.x = 0;
	rtGameScreenBg.y = 0;
	rtGameScreenBg.w = 1280;
	rtGameScreenBg.h = 720;
	SDL_RenderCopy(screen, gameScreenBg, NULL, &rtGameScreenBg);

	SDL_Rect rtMusic;
	rtMusic.x = 160;
	rtMusic.y = 76;
	rtMusic.w = 131;
	rtMusic.h = 84;
	SDL_RenderCopy(screen, currentMusicImg, NULL, &rtMusic);

	if (playButton->IsVisible()) playButton->Draw(screen);
	if (pauseButton->IsVisible()) pauseButton->Draw(screen);
	goBackButton->Draw(screen);
	musicUpButton->Draw(screen);
	musicDownButton->Draw(screen);

	// Musicians
	guitar->Render(screen);
	cactus->Render(screen);
	singer->Render(screen);
	barTender->Render(screen);
	dog->Render(screen);

}

void MAINGAME::Release()
{
	wchar_t strTemp[128];
	wsprintf(strTemp, L"stop Musics/music%d.mp3", musicIndex);
	mciSendString(strTemp, NULL, 0, NULL);

	mciSendString(L"play Musics/music1.mp3", NULL, 0, NULL);

	if (!dog->IsReleased()) dog->Release();
	if (!barTender->IsReleased()) barTender->Release();
	if (!singer->IsReleased()) singer->Release();
	if (!cactus->IsReleased()) cactus->Release();
	if (!guitar->IsReleased()) guitar->Release();

	SDL_DestroyTexture(gameScreenBg);

	if (!pauseButton->IsDeleted()) pauseButton->Release();
	if (!goBackButton->IsDeleted()) goBackButton->Release();
	if (!musicUpButton->IsDeleted()) musicUpButton->Release();
	if (!musicDownButton->IsDeleted()) musicDownButton->Release();

	if (forInput)
	{
		// OutFiles
		outFile[0][0].close();
		outFile[0][1].close();
		outFile[0][2].close();
		outFile[0][3].close();
		outFile[0][4].close();

		outFile[1][0].close();
		outFile[1][1].close();
		outFile[1][2].close();
		outFile[1][3].close();
		outFile[1][4].close();

		outFile[2][0].close();
		outFile[2][1].close();
		outFile[2][2].close();
		outFile[2][3].close();
		outFile[2][4].close();

		outFile[3][0].close();
		outFile[3][1].close();
		outFile[3][2].close();
		outFile[3][3].close();
		outFile[3][4].close();

		outFile[4][0].close();
		outFile[4][1].close();
		outFile[4][2].close();
		outFile[4][3].close();
		outFile[4][4].close();
	}

	// InFiles
	inFile[0][0].close();
	inFile[0][1].close();
	inFile[0][2].close();
	inFile[0][3].close();
	inFile[0][4].close();

	inFile[1][0].close();
	inFile[1][1].close();
	inFile[1][2].close();
	inFile[1][3].close();
	inFile[1][4].close();

	inFile[2][0].close();
	inFile[2][1].close();
	inFile[2][2].close();
	inFile[2][3].close();
	inFile[2][4].close();

	inFile[3][0].close();
	inFile[3][1].close();
	inFile[3][2].close();
	inFile[3][3].close();
	inFile[3][4].close();
	
	inFile[4][0].close();
	inFile[4][1].close();
	inFile[4][2].close();
	inFile[4][3].close();
	inFile[4][4].close();
}

void MAINGAME::PlayMusic(float acculTime)
{
	wchar_t strTemp[128];
	wsprintf(strTemp, L"play Musics/music%d.mp3", musicIndex);
	mciSendString(strTemp, NULL, 0, NULL);
	nowPlaying = true;
	if (!musicPaused) musicStartTime = acculTime;
	musicPaused = false;
}

void MAINGAME::PauseMusic()
{
	wchar_t strTemp[128];
	wsprintf(strTemp, L"pause Musics/music%d.mp3", musicIndex);
	mciSendString(strTemp, NULL, 0, NULL);
	nowPlaying = false;
	musicPaused = true;
}

void MAINGAME::StopMusic()
{
	wchar_t strTemp[128];
	wsprintf(strTemp, L"stop Musics/music%d.mp3", musicIndex);
	mciSendString(strTemp, NULL, 0, NULL);
	nowPlaying = false;
	musicPaused = false;
	musicStartTime = 0.0f;
	currentMusicTime = 0.0f;

	musicPauseTime = 0.0f;
	musicPauseStartTime = m_acculTime;

	for (int i = 0; i < 5; i++)
	{
		musicianAnimationPlaying[i] = false;
		musicianAnimationIndex[i] = 0;
	}


}

void MAINGAME::MusicStopCheck()
{
	//cout << "currentMusicTime : " << currentMusicTime << endl;

	switch (musicIndex)
	{
	case 0:
		if (currentMusicTime >= 254)
		{
			StopMusic();
			PlayButtonSetVisible(true);
			PauseButtonSetVisible(false);
		}
		break;
	case 1:
		if (currentMusicTime >= 96)
		{
			StopMusic();
			PlayButtonSetVisible(true);
			PauseButtonSetVisible(false);
		}
		break;
	case 2:
		if (currentMusicTime >= 106)
		{
			StopMusic();
			PlayButtonSetVisible(true);
			PauseButtonSetVisible(false);
		}
		break;
	case 3:
		if (currentMusicTime >= 120)
		{
			StopMusic();
			PlayButtonSetVisible(true);
			PauseButtonSetVisible(false);
		}
		break;
	case 4:
		if (currentMusicTime >= 104)
		{
			StopMusic();
			PlayButtonSetVisible(true);
			PauseButtonSetVisible(false);
		}
	}

}

void MAINGAME::MusicIndexUp()
{
	StopMusic();
	if (musicIndex <= 0) musicIndex = 5;
	musicIndex--;
	//PlayMusic();
	PlayButtonSetVisible(true);
	PauseButtonSetVisible(false);
	//cout << "musicIndex : " << musicIndex << endl;
}

void MAINGAME::MusicIndexDown()
{	
	StopMusic();
	if (musicIndex >= 4) musicIndex = -1;
	musicIndex++;
	//PlayMusic();
	PlayButtonSetVisible(true);
	PauseButtonSetVisible(false);

}

void MAINGAME::PlayButtonSetVisible(bool b)
{
	playButton->SetVisible(b);
}

void MAINGAME::PauseButtonSetVisible(bool b)
{
	pauseButton->SetVisible(b);
}

void MAINGAME::MusicianAnimationManager()
{
	if (nowPlaying)
	{
		if (!guitar->IsResting())
		{
			if (currentMusicTime > musicianAnimationDelay[0][musicIndex][musicianAnimationIndex[0]])
			{
				musicianAnimationPlaying[0] = !musicianAnimationPlaying[0];
				if (musicianAnimationIndex[0] == 0) musicianAnimationPlaying[0] = true;
				musicianAnimationIndex[0]++;
			}
		}
		if (!cactus->IsResting())
		{
			if (currentMusicTime >= musicianAnimationDelay[1][musicIndex][musicianAnimationIndex[1]])
			{
				musicianAnimationPlaying[1] = !musicianAnimationPlaying[1];
				if (musicianAnimationIndex[1] == 0) musicianAnimationPlaying[1] = true;
				musicianAnimationIndex[1]++;
			}
		}
		if (!singer->IsResting())
		{
			if (currentMusicTime >= musicianAnimationDelay[2][musicIndex][musicianAnimationIndex[2]])
			{
				musicianAnimationPlaying[2] = !musicianAnimationPlaying[2];
				if (musicianAnimationIndex[2] == 0) musicianAnimationPlaying[2] = true;
				musicianAnimationIndex[2]++;
			}
		}
		if (!barTender->IsResting())
		{
			if (currentMusicTime >= musicianAnimationDelay[3][musicIndex][musicianAnimationIndex[3]])
			{
				musicianAnimationPlaying[3] = !musicianAnimationPlaying[3];
				if (musicianAnimationIndex[3] == 0) musicianAnimationPlaying[3] = true;
				musicianAnimationIndex[3]++;
			}
		}
		if (!dog->IsResting())
		{
			if (currentMusicTime >= musicianAnimationDelay[4][musicIndex][musicianAnimationIndex[4]])
			{
				musicianAnimationPlaying[4] = !musicianAnimationPlaying[4];
				if (musicianAnimationIndex[4] == 0) musicianAnimationPlaying[4] = true;
				musicianAnimationIndex[4]++;
			}
		}
	}
}

void MAINGAME::InitMusicianAnimationDelay()
{
	musicianAnimationDelay = new float**[5];

	for (int i = 0; i < 5; i++)
	{
		musicianAnimationDelay[i] = new float*[5];
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int size = Count_Line(inFile[i][j]);
			if (size >= 0)
			{
				musicianAnimationDelay[i][j] = new float[size];
				for (int k = 0; k < size; k++)
				{
					string line;
					getline(inFile[i][j], line);
					const char * c = line.c_str();
					musicianAnimationDelay[i][j][k] = atof(c);
				}
			}
		}
	}

}

size_t MAINGAME::Count_Line(istream& is)
{
	// skip when bad
	if (is.bad()) return 0;
	// save state
	std::istream::iostate state_backup = is.rdstate();
	// clear state
	is.clear();
	std::istream::streampos pos_backup = is.tellg();

	is.seekg(0);
	size_t line_cnt;
	size_t lf_cnt = std::count(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>(), '\n');
	line_cnt = lf_cnt;
	// if the file is not end with '\n' , then line_cnt should plus 1  
	is.unget();
	if (is.get() != '\n') { ++line_cnt; }

	// recover state
	is.clear(); // previous reading may set eofbit
	is.seekg(pos_backup);
	is.setstate(state_backup);

	return line_cnt;
}