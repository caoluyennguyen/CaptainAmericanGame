#include "Input.h"



Input::Input(Game* game, Captain* captain)
{
	this->game = game;
	this->captain = captain;
}

Input::~Input()
{
}

void Input::KeyState(BYTE* state)
{
	/*if (captain->GetState() == JUMP && captain->IsTouchGround() == false)
			return;*/

	if (game->IsKeyDown(DIK_RIGHT))
	{
		captain->nx = 1;
		captain->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		captain->nx = -1;
		captain->SetState(WALK);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		captain->SetState(SIT);
	}
	else
	{
		captain->SetState(STAND);
	}
}

void Input::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_Z:
		captain->SetState(JUMP);
		break;
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
