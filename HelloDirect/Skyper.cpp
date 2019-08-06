#include "Skyper.h"

Skyper::Skyper()
{
	AddAnimation(SKYPER_FLY_ANI);
	AddAnimation(SKYPER_DEAD_ANI);
	AddAnimation(SKYPER_SHOOT_ANI);
	AddAnimation(SKYPER_SIT_ANI);
	AddAnimation(SKYPER_STOP_ANI);
}

void Skyper::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	LPDIRECT3DTEXTURE9 texShooter = textures->Get(ID_TEX_SHOOTER);

	sprites->Add(110001, 36, 131, 60, 168, texShooter);
	sprites->Add(110002, 68, 131, 92, 168, texShooter);
	sprites->Add(110003, 100, 131, 124, 168, texShooter);
	sprites->Add(110004, 132, 131, 156, 168, texShooter);
	sprites->Add(110005, 228, 124, 252, 168, texShooter);
	sprites->Add(110006, 260, 124, 284, 168, texShooter);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(110001);
	ani->Add(110002);
	ani->Add(110003);
	animations->Add(SKYPER_FLY_ANI, ani);

	ani = new Animation(200);
	ani->Add(110001);
	animations->Add(SKYPER_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(110006);
	animations->Add(SKYPER_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(110001);
	animations->Add(SKYPER_SIT_ANI, ani);
}

void Skyper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == ENEMY_DESTROYED && animations[state]->IsOver(150) == true)
	{
		SetState(ENEMY_STOP);
		//this->isEnable = false;
		return;
	}

	if (stopMovement == true)
		return;

	if (state == ENEMY_SHOOT && animations[state]->IsOver(1000) == true)
	{
		nx = nxShoot;
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

		/*if (ny != 0)
		{
			if (ny == -1.0f)
			{
				vy = 0;
			}
			else
			{
				y += dy;
			}
		}*/
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Skyper::Render()
{
	if (state != ENEMY_STOP)
		animations[state]->Render(1, nx, x, y);
}

void Skyper::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_RUN:
		//vx = 0.1f * nx;
		lastTimeShoot = GetTickCount();
		deltaTimeToShoot = 500 + rand() % 2000;
		respawnTime_Start = 0;
		isRespawnWaiting = false;
		break;
	case ENEMY_DESTROYED:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_SHOOT:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_STOP:
		x = entryPosition.x;
		y = entryPosition.y;
		vx = vy = 0;
		StartRespawnTimeCounter();
		break;
	case ENEMY_SIT:
		lastTimeShoot = GetTickCount();
		deltaTimeToShoot = 500 + rand() % 2000;
	default:
		break;
	}
}

void Skyper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 24;
	bottom = top + 40;
}

void Skyper::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - 100;
	right = entryPosition.x + 100;
	top = entryPosition.y - 200;
	bottom = entryPosition.y + 200;
}

bool Skyper::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= 3000)
		return true;

	return false;
}
