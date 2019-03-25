#include "stdafx.h"

//static SDL_Point points[] = { 
//	{ 50, 150 }, { 150, 100 },
//	{ 300, 200 }, { 300, 100 },
//	{ 150, 200 }, { 50, 150 },
//};
//static SDL_Rect rects[] = { 
//	{ 50, 150, 10, 10 }, { 150, 100, 10, 10 },
//	{ 300, 200, 10, 10 }, { 300, 100, 10, 10 },
//	{ 150, 200, 10, 10 }, { 50, 150, 10, 10 },
//};

CSystem::CSystem(void)
{

}

CSystem::~CSystem(void)
{

}

bool CSystem::Initialize()
{
	CBaseWindow::Initialize();
	CTimeManager::Initialize();

	m_pGameFrame = new CFrameSkip;
	m_pGameFrame->SetFramePerSec(60);

	m_pInputManager = new CInputManager;
	m_pInputManager->SetInputHandler(this);


	startScreen = new STARTSCREEN;
	startScreen->Init(m_pRender);


	//여기에 오브젝트 초기화 코드를 넣으세요
	//btnUp = InitButton(CBaseWindow::m_pRender, 
	
	return true;
}

void CSystem::Pulse()
{
	CTimeManager::Pulse();
	m_pInputManager->Pulse();

	if (state == 2) mainGame->Update(m_fAcculTime);

	float fTimeStep = CTimeManager::GetTimeStep();

	if (m_pGameFrame->Update(fTimeStep))
	{
		SDL_SetRenderDrawColor(m_pRender, MIN8, MIN8, MAX8, MAX8);
		//SDL_RenderClear(m_pRender);
		//====================================
		//여기에 오브젝트 프로세스 코드를 넣으세요. 
		if (state == 1) startScreen->Render(m_pRender);
		if (state == 2) mainGame->Render(m_pRender);
		//====================================
		SDL_RenderPresent(m_pRender);
	}
}

void CSystem::Terminate()
{
	//여기에 오브젝트 종료/해제 코드를 넣으세요.
	startScreen->Release();
	if (mainGame != NULL) mainGame->Release();

	m_pInputManager->Terminate();
	
	CBaseWindow::Terminate();
	CTimeManager::Terminate();

	delete this;

	exit(0);
}

void CSystem::Run()
{	
	while (m_bIsGameRun)
	{
		Pulse(); //Update()
	}
}

#define g_pKeyCodeScan(vk) (m_pInputManager->GetOldKeyState(vk)&&m_pInputManager->GetCurKeyState(vk))

void CSystem::KeyboardHandler()
{
	if (g_pKeyCodeScan(SDLK_ESCAPE)) Terminate();
	if (state == 2)
	{
		bool mainGameKeyboardInputs[5]; // Input variable for each musician's play

		for (int i = 0; i < 5; i++)
			mainGameKeyboardInputs[i] = false;

		if (g_pKeyCodeScan(SDL_SCANCODE_Q)) mainGameKeyboardInputs[0] = true;
		if (g_pKeyCodeScan(SDL_SCANCODE_W)) mainGameKeyboardInputs[1] = true;
		if (g_pKeyCodeScan(SDL_SCANCODE_E)) mainGameKeyboardInputs[2] = true;
		if (g_pKeyCodeScan(SDL_SCANCODE_R)) mainGameKeyboardInputs[3] = true;
		if (g_pKeyCodeScan(SDL_SCANCODE_T)) mainGameKeyboardInputs[4] = true;

		mainGame->KeyboardUpdate(this, mainGameKeyboardInputs);
	}
}

void CSystem::MouseHandler(MOUSESTATE mouseState)
{
	if (state == 1) startScreen->Update(this, m_pRender, mouseState);
	if (state == 2) mainGame->MouseUpdate(this, m_pRender, mouseState);
}

void CSystem::GoToStartScreen()
{
	startScreen->Init(m_pRender);
}


