#pragma once

MUSICIAN;

class MAINGAME
{
private:
	BUTTON* playButton;
	BUTTON* pauseButton;
	BUTTON* goBackButton;

	// Variables for Music list
	BUTTON* musicUpButton;
	BUTTON* musicDownButton;

	SDL_Texture* currentMusicImg;

	SDL_Texture** musicImgs;

	int musicIndex;

	bool nowPlaying;
	bool musicPaused;

	// Only one gameScreenBg
	SDL_Texture* gameScreenBg;

	MUSICIAN* guitar;
	MUSICIAN* cactus;
	MUSICIAN* singer;
	MUSICIAN* barTender;
	MUSICIAN* dog;

	float currentMusicTime;
	float musicStartTime;
	float musicPauseTime;
	float musicPauseStartTime;

	bool musicianAnimationPlaying[5];
	float*** musicianAnimationDelay;

	ofstream outFile[5][5];
	ifstream inFile[5][5];

	int musicianAnimationIndex[5];

	float m_acculTime;


public:
	void Init(SDL_Renderer* screen);
	void Update(float acculTime);
	void MouseUpdate(CSystem* system, SDL_Renderer* screen, MOUSESTATE mouseState);
	void KeyboardUpdate(CSystem* system, bool input[]);
	void Render(SDL_Renderer* screen);
	void Release();

	void PlayMusic(float acculTime);
	void PauseMusic();
	void StopMusic();

	void MusicStopCheck();

	void MusicIndexUp();
	void MusicIndexDown();

	void PlayButtonSetVisible(bool b);
	void PauseButtonSetVisible(bool b);

	void MusicianAnimationManager();

	void InitMusicianAnimationDelay();

	size_t Count_Line(istream& is);
};



