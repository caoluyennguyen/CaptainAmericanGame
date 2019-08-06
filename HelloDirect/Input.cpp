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
	if (captain->GetState() == HIT_SIT && captain->animations[HIT_SIT]->IsOver(200) == false) 
		return;
	if (captain->GetState() == HIT_STAND && captain->animations[HIT_STAND]->IsOver(200) == false) 
		return;
	if (captain->GetState() == HIT_JUMP && captain->animations[HIT_JUMP]->IsOver(200) == false)
		return;
	if (captain->GetState() == SWIFT && captain->animations[SWIFT]->IsOver(200) == false)
		return;
	if (captain->GetState() == INJURED && captain->animations[INJURED]->IsOver(600) == false)
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
		if (captain->GetState() == HIT_STAND
			|| captain->GetState() == HIT_SIT
			|| captain->GetState() == HIT_JUMP)
			return;
		else if (captain->GetState() == STAND) {
			captain->SetState(HIT_STAND);
			if (captain->hasShield == true)
			{
				Captain_Throw_Shield();
				captain->hasShield = false;
			}
		}
		else if (captain->GetState() == SIT) captain->SetState(HIT_SIT);
		else if (captain->GetState() == JUMP) captain->SetState(HIT_JUMP);
		break;
	case DIK_X:
		if (captain->GetState() == JUMP
			|| captain->GetState() == HIT_STAND
			|| captain->GetState() == HIT_SIT
			|| captain->GetState() == HIT_JUMP)
			return;
		captain->SetState(JUMP);
		break;
	case DIK_C:
		if (captain->GetState() == SWIFT)
			return;
		captain->SetState(SWIFT);
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
