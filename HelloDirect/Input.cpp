#include "Input.h"



Input::Input(Game* game, SceneManager* scene)
{
	this->game = game;
	this->scene = scene;
}

Input::~Input()
{
}

void Input::KeyState(BYTE* state)
{
	Captain* captain = scene->GetCaptain();
	if (captain->GetState() == JUMP && captain->IsTouchGround() == false)
		return;

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
		scene->GetCaptain()->SetState(JUMP);
		break;
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

//
//void Input::Captain_Walk_Left()
//{
//	scene->GetCaptain()->SetOrientation(-1);
//	scene->GetCaptain()->SetState(WALK);
//}
//
//void Input::Captain_Walk_Right()
//{
//	scene->GetCaptain()->SetOrientation(1);
//	scene->GetCaptain()->SetState(WALK);
//}
//
//void Input::Captain_Jump()
//{
//	if (scene->GetCaptain()->GetState() == JUMP ||
//		scene->GetCaptain()->GetState() == HIT_STAND ||
//		scene->GetCaptain()->GetState() == HIT_SIT)
//		return;
//
//	scene->GetCaptain()->SetState(JUMP);
//}
//
//void Input::Captain_Hit()
//{
//	if ((scene->GetCaptain()->GetState() == HIT_STAND || scene->GetCaptain()->GetState() == HIT_SIT))
//		return;
//
//	if (scene->GetCaptain()->GetState() == STAND || scene->GetCaptain()->GetState() == JUMP)
//	{
//		scene->GetCaptain()->SetState(HIT_STAND);
//	}
//	else if (scene->GetCaptain()->GetState() == SIT)
//	{
//		scene->GetCaptain()->SetState(HIT_SIT);
//	}
//}