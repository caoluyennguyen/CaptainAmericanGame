#include "MiniBoss.h"

MiniBoss::MiniBoss()
{
	AddAnimation(MINIBOSS_RUN_ANI);
	AddAnimation(MINIBOSS_DEAD_ANI);
	AddAnimation(MINIBOSS_SHOOT_ANI);
	AddAnimation(MINIBOSS_SIT_ANI);
	AddAnimation(MINIBOSS_SIT_ANI);
	AddAnimation(MINIBOSS_THROW_ANI);
}

void MiniBoss::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_MINIBOSS, FILEPATH_TEX_MINIBOSS, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texMiniboss = textures->Get(ID_TEX_MINIBOSS);

	// run
	sprites->Add(130001, 8, 33, 38, 72, texMiniboss);
	sprites->Add(130002, 51, 33, 75, 72, texMiniboss);
	sprites->Add(130003, 89, 33, 117, 72, texMiniboss);
	// shoot
	sprites->Add(130004, 168, 29, 206, 72, texMiniboss);
	// injured
	sprites->Add(130005, 360, 24, 390, 72, texMiniboss);
	sprites->Add(130006, 240, 29, 270, 72, texMiniboss);
	// carry and throw
	sprites->Add(130007, 280, 24, 306, 72, texMiniboss);
	sprites->Add(130008, 320, 29, 352, 72, texMiniboss);
	// idle
	sprites->Add(130009, 240, 29, 270, 72, texMiniboss);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(130001);
	ani->Add(130002);
	ani->Add(130003);
	animations->Add(MINIBOSS_RUN_ANI, ani);

	ani = new Animation(200);
	ani->Add(130004);
	animations->Add(MINIBOSS_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(130005);
	ani->Add(130006);
	animations->Add(MINIBOSS_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(130009);
	animations->Add(MINIBOSS_SIT_ANI, ani);

	ani = new Animation(400);
	ani->Add(130007);
	ani->Add(130008);
	animations->Add(MINIBOSS_THROW_ANI, ani);
}

void MiniBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == ENEMY_DESTROYED && animations[state]->IsOver(150) == true)
	{
		SetState(ENEMY_THROW);
		HP--;
	}

	if (stopMovement == true)
		return;

	if (HP < 0)
	{
		state = ENEMY_STOP;
	}
	else if (state == ENEMY_THROW && this->animations[state]->IsOver(1000) == false)
	{
		return;
	}

	GameObject::Update(dt);

	vy += 0.001f * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj))
			{
				if (ny != 0)
				{
					vy = 0;
				}
				else
					y += dy;
			}
			else if (dynamic_cast<Shield*>(e->obj))
			{
				HP--;
			}
			else
			{
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}

	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void MiniBoss::Render()
{
	if (state != ENEMY_STOP)
	{
		animations[state]->Render(1, nx, x, y);
	}
}

void MiniBoss::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_RUN:
		vx = 0.05f * nx;
		vy = 0;
		lastTimeThrow = GetTickCount();
		deltaTime = 500 + rand() % 2000; // Random trong khoảng thời gian là 0.5 - 2s
		break;
	case ENEMY_DESTROYED:
		vx = vy = 0;
		lastTimeThrow = GetTickCount();
		deltaTime = 10000;
		animations[state]->SetAniStartTime(GetTickCount());
		HP--;
		break;
	case ENEMY_SHOOT:
		vx = vy = 0;
		lastTimeRun = GetTickCount();
		deltaTime = 500 + rand() % 2000;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_STOP:
		vx = vy = 0;
		break;
	case ENEMY_SIT:
		vx = vy = 0;
		lastTimeThrow = GetTickCount();
		deltaTime = 500 + rand() % 2000;
		animations[state]->SetAniStartTime(GetTickCount());

	case ENEMY_THROW:
		vx = vy = 0;
		lastTimeShoot = GetTickCount();
		deltaTime = 500 + rand() % 2000;
	default:
		break;
	}
}

void MiniBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 30;
	bottom = top + 40;
}

void MiniBoss::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - 100;
	right = entryPosition.x + 100;
	top = entryPosition.y - 200;
	bottom = entryPosition.y + 200;
}