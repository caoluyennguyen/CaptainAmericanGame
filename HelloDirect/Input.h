#pragma once

#include "Game.h"
#include "Captain.h"

class Input : public KeyEventHandler
{
	Game* game;
	Captain* captain;
public:
	Input(Game* game, Captain* captain);
	~Input();

	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

