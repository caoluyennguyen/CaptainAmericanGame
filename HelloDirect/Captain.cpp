#include "Captain.h"

void Captain::LoadResources()
{
	Textures* texture = Textures::GetInstance();

	texture->Add(ID_TEX_CAPTAIN, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texCap = texture->Get(ID_TEX_CAPTAIN);

#pragma region idle left
	sprites->Add(10001, 21, 11, 43, 56, texCap);
#pragma endregion

#pragma region move left
	sprites->Add(10002, 52, 11, 76, 56, texCap);
	sprites->Add(10003, 84, 11, 108, 56, texCap);
	sprites->Add(10004, 116, 11, 140, 56, texCap);
	sprites->Add(10005, 148, 11, 172, 56, texCap);
#pragma endregion

#pragma region jump left
	sprites->Add(10027, 244, 15, 266, 53, texCap);
	sprites->Add(10028, 276, 28, 294, 48, texCap);
	sprites->Add(10029, 312, 30, 332, 48, texCap);
	sprites->Add(10030, 244, 15, 266, 53, texCap);

#pragma endregion

#pragma region shield up left
	sprites->Add(10058, 180, 13, 204, 56, texCap);
#pragma endregion

#pragma region CREATING ANIMATION

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(10001);
	animations->Add(STAND, ani);

	ani = new Animation();
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	animations->Add(WALK, ani);

	ani = new Animation();
	ani->Add(10058);
	animations->Add(SIT, ani);

	ani = new Animation();
	ani->Add(10027);
	ani->Add(10028);
	ani->Add(10029);
	ani->Add(10030);
	animations->Add(JUMP, ani);

	AddAnimation(STAND);
	AddAnimation(WALK);
	AddAnimation(SIT);
	AddAnimation(JUMP);
#pragma endregion


	SetPosition(0.0f, 150.0f);
}

void Captain::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	GameObject::Update(dt);

	vy += CAPTAIN_GRAVITY;

	/*if (y > 224)
	{
		vy = 0;
		y = 224.0f;
	}*/

	if (state == HIT_SIT || state == HIT_STAND)
	{
		D3DXVECTOR3 simonPositon;
		GetPosition(simonPositon.x, simonPositon.y);

	}

	// Check collision between Simon and other objects
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// ground
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// collision of Simon and Candle -> do nothing -> update x;
			if (dynamic_cast<Enemy*>(e->obj))
			{
				x -= nx * 0.4f;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//for (int i = 0; i < coEventsResult.size(); i++) delete coEventsResult[i];
}

void Captain::Render()
{

	animations[state]->Render(nx, x, y);
}

void Captain::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case STAND:
		isStand = true;
		vx = 0;
		break;
	case WALK:
		if (nx > 0) vx = CAPTAIN_WALKING_SPEED;
		else vx = -CAPTAIN_WALKING_SPEED;
		break;
	case JUMP:
		isStand = true;
		if (y == 224)
			vy = -CAPTAIN_JUMP_SPEED_Y;
		break;
	case UP:
		isStand = true;
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}
}

void Captain::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CAPTAIN_BBOX_WIDTH;
	bottom = y + CAPTAIN_BBOX_HEIGHT;
}





