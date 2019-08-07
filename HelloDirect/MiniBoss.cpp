#include "MiniBoss.h"

MiniBoss::MiniBoss()
{
	AddAnimation(MINIBOSS_RUN_ANI);
	AddAnimation(MINIBOSS_DEAD_ANI);
	AddAnimation(MINIBOSS_SHOOT_ANI);
	AddAnimation(MINIBOSS_SIT_ANI);
	AddAnimation(MINIBOSS_STOP_ANI);
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
	ani->Add(130007);
	ani->Add(130008);
	animations->Add(MINIBOSS_SIT_ANI, ani);
}

void MiniBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == ENEMY_DESTROYED && animations[state]->IsOver(150) == true)
	{
		SetState(ENEMY_STOP);
		//this->isEnable = false;
		return;
	}

	if (stopMovement == true)
		return;

	if (state == ENEMY_SHOOT && animations[state]->IsOver(200) == true)
	{
		//nx = nxShoot;
		SetState(ENEMY_SIT);
		return;
	}

	else if (state == ENEMY_STOP)
	{
		vx = 0;
		return;
	}

	GameObject::Update(dt);

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

		x += dx;
		y += min_ty * dy + ny * 0.1f;

		if (ny != 0)
		{
			if (ny == -1.0f)
			{
				vy = 0;
			}
			else
			{
				y += dy;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void MiniBoss::Render()
{
	if (state != ENEMY_STOP)
		animations[state]->Render(1, nx, x, y);
}

void MiniBoss::SetState(int state)
{
	//GameObject::SetState(state);
	//switch (state)
	//{
	//case ENEMY_RUN:
	//	//vx = 0.1f * nx;
	//	lastTimeShoot = GetTickCount();
	//	deltaTimeToShoot = 500 + rand() % 2000;
	//	respawnTime_Start = 0;
	//	isRespawnWaiting = false;
	//	break;
	//case ENEMY_DESTROYED:
	//	vx = vy = 0;
	//	animations[state]->SetAniStartTime(GetTickCount());
	//	break;
	//case ENEMY_SHOOT:
	//	vx = 0.1 * nx;
	//	vy = -0.2;
	//	animations[state]->SetAniStartTime(GetTickCount());
	//	break;
	//case ENEMY_STOP:
	//	x = entryPosition.x;
	//	y = entryPosition.y;
	//	vx = vy = 0;
	//	StartRespawnTimeCounter();
	//	break;
	//case ENEMY_SIT:
	//	lastTimeShoot = GetTickCount();
	//	deltaTimeToShoot = 500 + rand() % 2000;
	//default:
	//	break;
	//}
}

void MiniBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 24;
	bottom = top + 40;
}

void MiniBoss::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - 100;
	right = entryPosition.x + 100;
	top = entryPosition.y - 200;
	bottom = entryPosition.y + 200;
}