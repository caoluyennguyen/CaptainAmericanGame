#include "Shooter.h"

Shooter::Shooter()
{
	AddAnimation(SHOOTER_RUN_ANI);
	AddAnimation(SHOOTER_DEAD_ANI);
	AddAnimation(SHOOTER_SHOOT_ANI);
	AddAnimation(SHOOTER_SIT_ANI);
	AddAnimation(SHOOTER_DEAD_ANI);
}

void Shooter::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_SHOOTER, FILEPATH_TEX_SMALL_ENEMY, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texShooter = textures->Get(ID_TEX_SHOOTER);

	sprites->Add(50001, 72, 16, 96, 56, texShooter);
	sprites->Add(50002, 104, 16, 126, 56, texShooter);
	sprites->Add(50003, 136, 16, 160, 56, texShooter);
	sprites->Add(50004, 168, 13, 192, 56, texShooter);
	sprites->Add(50005, 200, 13, 224, 56, texShooter);
	sprites->Add(50006, 232, 24, 256, 56, texShooter);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(50001);
	ani->Add(50002);
	ani->Add(50003);
	animations->Add(SHOOTER_RUN_ANI, ani);

	ani = new Animation(200);
	ani->Add(50004);
	//ani->Add(50005);
	animations->Add(SHOOTER_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(50006);
	animations->Add(SHOOTER_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(50005);
	animations->Add(SHOOTER_SIT_ANI, ani);
}

void Shooter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == ENEMY_DESTROYED)
	{
		if (animations[state]->IsOver(200) == true)
		{

			SetState(ENEMY_STOP);
			this->isEnable = false;
			return;
		}
	}

	if (stopMovement == true)
		return;

	if (state == ENEMY_SHOOT && animations[state]->IsOver(1000) == true)
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
	//vx += 0.1f * dt;

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

void Shooter::Render()
{
	if (state != ENEMY_STOP)
		animations[state]->Render(1, nx, x, y);
}

void Shooter::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_RUN:
		//vx = 0.1f * nx;
		lastTimeShoot = GetTickCount();
		deltaTimeToShoot = 500 + rand() % 2000; // Random trong khoảng thời gian là 0.5 - 2s
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

void Shooter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y; 
	right = left + 24;
	bottom = top + 40;
}

void Shooter::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - 100;
	right = entryPosition.x + 100;
	top = entryPosition.y - 200;
	bottom = entryPosition.y + 200;
}

bool Shooter::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= 3000)
		return true;

	return false;
}