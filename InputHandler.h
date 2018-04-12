#pragma once

enum MouseButton { LEFT, RIGHT, MIDDLE };
typedef struct _MOUSESTATE
{
	int x;
	int y;
	BYTE btn[4];
	
}MOUSESTATE;

class IInputHandler
{
public:
	IInputHandler()
	{
	}

	virtual ~IInputHandler()
	{
	}

public:
	virtual void KeyboardHandler(void) = 0;
	virtual void MouseHandler(MOUSESTATE mouseState) = 0;
};


