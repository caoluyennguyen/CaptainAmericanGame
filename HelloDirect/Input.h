#pragma once

#include "Game.h"
#include "SceneManager.h"

class Input : public KeyEventHandler
{
	Game* game;
	SceneManager* scene;
public:
	Input(Game* game, SceneManager* scene);
	~Input();

	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	/*void Captain_Walk_Left();
	void Captain_Walk_Right();
	void Captain_Jump();
	void Captain_Hit();*/
};

