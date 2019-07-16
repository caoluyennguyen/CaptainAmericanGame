#include "Megaman.h"

void CMegaman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	// simple fall down

	vy += MEGAMAN_GRAVITY_Y * dt;

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

void CMegaman::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = MEGAMAN_ANI_IDLE_RIGHT;
		else ani = MEGAMAN_ANI_IDLE_LEFT;
	}
	else if (vx == MEGAMAN_WALKING_SPEED)
		ani = MEGAMAN_ANI_WALKING_RIGHT;
	else if (vx == 0.1f) ani = MEGAMAN_ANI_FIGHT;
	else if (vx == MEGAMAN_SWIFT_SPEED) ani = MEGAMAN_ANI_SWIFT;
	else ani = MEGAMAN_ANI_WALKING_LEFT;

	if (dy != 0)
	{
		if (nx > 0)
		{
			ani = MEGAMAN_ANI_JUMP_RIGHT;
		}
		else
		{
			ani = MEGAMAN_ANI_JUMP_LEFT;
		}
	}

	animations[ani]->Render(x, y);
}

void CMegaman::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MEGAMAN_STATE_WALKING_RIGHT:
		vx = MEGAMAN_WALKING_SPEED;
		nx = 1;
		break;
	case MEGAMAN_STATE_WALKING_LEFT:
		vx = -MEGAMAN_WALKING_SPEED;
		nx = -1;
		break;
	case MEGAMAN_STATE_JUMP:
		vy = -MEGAMAN_JUMP_SPEED_Y;

	case MEGAMAN_STATE_IDLE:
		vx = 0.0f;
		break;

	case MEGAMAN_STATE_FIGHT:
		vx = 0.1f;
		break;

	case MEGAMAN_STATE_SWIFT:
		vx = MEGAMAN_SWIFT_SPEED;
		break;
	}
}

void CMegaman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + MEGAMAN_BBOX_WIDTH;
	bottom = y + MEGAMAN_BBOX_HEIGHT;
}


