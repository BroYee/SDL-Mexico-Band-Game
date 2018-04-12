#include "stdafx.h"

class CSystem : public CBaseWindow,
			   public CTimeManager,
			   public IInputHandler
{	
//private:
//	enum DrawingState{ POINTS = 0, LINES, BOXES, END };
//	int m_nIsDrawingState = POINTS;
//
private:
	CFrameSkip*		m_pGameFrame;
	CInputManager*	m_pInputManager;

	STARTSCREEN* startScreen;
	MAINGAME* mainGame = NULL;

	int state = 1;


public:
	CSystem(void);
	~CSystem(void);

private:
	void Pulse();

public:
	bool Initialize();
	void Terminate();
	void Run();

public:
	void KeyboardHandler();
	void MouseHandler(MOUSESTATE mouseState);

private:
	void GoToStartScreen();

public:
	friend void BUTTON::ClickUp(CSystem* system);

};
