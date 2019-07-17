#include "Captain.h"

void CCaptain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// simple fall down

	vy += CAPTAIN_GRAVITY_Y * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CCaptain::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = CAPTAIN_ANI_IDLE_RIGHT;
		else ani = CAPTAIN_ANI_IDLE_LEFT;
	}

	//else if (vx == 0.1f) ani = MEGAMAN_ANI_FIGHT;
	if (vx == CAPTAIN_SWIFT_SPEED) ani = CAPTAIN_ANI_SWIFT_RIGHT;
	else if (vx == -CAPTAIN_SWIFT_SPEED) ani = CAPTAIN_ANI_SWIFT_LEFT;
	else if (vx == CAPTAIN_WALKING_SPEED) ani = CAPTAIN_ANI_WALKING_RIGHT;
	else if (vx == -CAPTAIN_WALKING_SPEED) ani = CAPTAIN_ANI_WALKING_LEFT;
	else if (vx == 0.1f) ani = CAPTAIN_ANI_FIGHT_RIGHT;
	else if (vx == -0.1f) ani = CAPTAIN_ANI_FIGHT_LEFT;
	else if (vx == 0.01f) ani = CAPTAIN_ANI_SHIELD_UP_RIGHT;
	else if (vx == -0.01f) ani = CAPTAIN_ANI_SHIELD_UP_LEFT;

	else if (dy != 0)
	{
		if (nx > 0)
		{
			ani = CAPTAIN_ANI_JUMP_RIGHT;
		}
		else
		{
			ani = CAPTAIN_ANI_JUMP_LEFT;
		}
	}

	animations[ani]->Render(x, y);
}

void CCaptain::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CAPTAIN_STATE_WALKING_RIGHT:
		vx = CAPTAIN_WALKING_SPEED;
		nx = 1;
		break;
	case CAPTAIN_STATE_WALKING_LEFT:
		vx = -CAPTAIN_WALKING_SPEED;
		nx = -1;
		break;
	case CAPTAIN_STATE_JUMP:
		vy = -CAPTAIN_JUMP_SPEED_Y;

	case CAPTAIN_STATE_IDLE:
		vx = 0.0f;
		break;

	case CAPTAIN_STATE_FIGHT:
		vx = 0.1f * nx;
		break;

	case CAPTAIN_STATE_SWIFT_RIGHT:
		vx = CAPTAIN_SWIFT_SPEED;
		nx = 1;
		break;

	case CAPTAIN_STATE_SWIFT_LEFT:
		vx = -CAPTAIN_SWIFT_SPEED;
		nx = -1;
		break;

	case CAPTAIN_STATE_SHIELD_RIGHT:
		vx = 0.01f;
		nx = 1;
		break;

	case CAPTAIN_STATE_SHIELD_LEFT:
		vx = -0.01f;
		nx = -1;
		break;
	}
}

void CCaptain::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CAPTAIN_BBOX_WIDTH;
	bottom = y + CAPTAIN_BBOX_HEIGHT;
}