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
	Captain * captain = scene->GetCaptain();

	if ((captain->GetState() == JUMP || captain->GetState() == STAND )
		&& captain->IsTouchGround() == false)
		return;
	if (captain->GetState() == HIT_STAND && captain->animations[HIT_STAND]->IsOver(200) == false) 
		return;
	if (captain->GetState() == HIT_SIT && captain->animations[HIT_SIT]->IsOver(200) == false) 
		return;
	if (captain->GetState() == HIT_JUMP && captain->animations[HIT_JUMP]->IsOver(200) == false) 
		return;
	if (captain->GetState() == DEFLECT && captain->animations[DEFLECT]->IsOver(600) == false)
		return;
	if (captain->GetState() == SWIFT && captain->animations[SWIFT]->IsOver(200) == false)
		return;
	else captain->animations[captain->GetState()]->SetAniStartTime(0);

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
	else if (game->IsKeyDown(DIK_DOWN))
	{
		captain->SetState(SIT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		captain->SetState(UP);
	}
	/*else if (game->IsKeyDown(DIK_X))
	{
		captain->SetState(JUMP);
	}*/
	else
	{
		captain->SetState(STAND);
	}
}

void Input::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	Captain* captain = scene->GetCaptain();

	switch (KeyCode)
	{
	case DIK_Z:
		if (scene->GetCaptain()->GetState() == HIT_STAND
			|| scene->GetCaptain()->GetState() == HIT_SIT
			|| scene->GetCaptain()->GetState() == HIT_JUMP)
			return;
		else if (scene->GetCaptain()->GetState() == STAND) {
			scene->GetCaptain()->SetState(HIT_STAND);
			Captain_Throw_Shield();
			if (captain->hasShield = true)
			{
				captain->hasShield = false;
			}
		}
		else if (scene->GetCaptain()->GetState() == SIT) scene->GetCaptain()->SetState(HIT_SIT);
		else if (scene->GetCaptain()->GetState() == JUMP) scene->GetCaptain()->SetState(HIT_JUMP);
		break;
	case DIK_X:
		if (scene->GetCaptain()->GetState() == JUMP
			|| scene->GetCaptain()->GetState() == HIT_STAND
			|| scene->GetCaptain()->GetState() == HIT_SIT
			|| scene->GetCaptain()->GetState() == HIT_JUMP)
			return;
		scene->GetCaptain()->SetState(JUMP);
		break;
	case DIK_C:
		if (scene->GetCaptain()->GetState() == SWIFT)
			return;
		scene->GetCaptain()->SetState(SWIFT);
		break;
	default:
		break;
	}
}

void Input::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}


void Input::Captain_Throw_Shield()
{
	Captain* captain = scene->GetCaptain();
	Shield* shield = scene->GetShield();

	float cx, cy;

	// position
	captain->GetPosition(cx, cy);
	shield->SetPosition(cx, cy);
	shield->SetOrientation(captain->GetOrientation());
	shield->SetEnable(true);
	shield->SetSpeed(shield->GetOrientation() * 0.4f, 0);
}
