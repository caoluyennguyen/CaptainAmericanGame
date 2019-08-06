#include "Rocketer.h"

Rocketer::Rocketer()
{
	AddAnimation(ROCKETER_RUN_ANI);
	AddAnimation(ROCKETER_DEAD_ANI);
	AddAnimation(ROCKETER_SHOOT_ANI);
	AddAnimation(ROCKETER_SIT_ANI);
	AddAnimation(ROCKETER_STOP_ANI);
}

void Rocketer::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_SHOOTER, FILEPATH_TEX_SMALL_ENEMY, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texShooter = textures->Get(ID_TEX_SHOOTER);

	sprites->Add(60001, 72, 66, 95, 112, texShooter);
	sprites->Add(60002, 105, 66, 127, 112, texShooter);
	sprites->Add(60003, 136, 66, 159, 112, texShooter);
	sprites->Add(60004, 136, 66, 159, 112, texShooter);
	sprites->Add(60005, 168, 66, 192, 112, texShooter);
	sprites->Add(60006, 200, 75, 224, 112, texShooter);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(60001);
	ani->Add(60002);
	ani->Add(60003);
	animations->Add(ROCKETER_RUN_ANI, ani);

	ani = new Animation(200);
	ani->Add(60004);
	animations->Add(ROCKETER_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(60006);
	animations->Add(ROCKETER_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(60004);
	animations->Add(ROCKETER_SIT_ANI, ani);
}

void Rocketer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
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
		SetState(ENEMY_SIT);
		return;
	}

	else if (state == ENEMY_STOP)
	{
		vx = 0;
		return;
	}

	GameObject::Update(dt);

	vy += 0.002f * dt;

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

		/*x += dx;
		y += min_ty * dy + ny * 0.1f;*/

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (ny != 0)
			{
				if (ny == -1.0f)
				{
					vx = 0;
					vy = 0;
				}
				else
				{
					y += dy;
				}
			}
			else
			{
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
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

void Rocketer::Render()
{
	if (state != ENEMY_STOP)
		animations[state]->Render(1, nx, x, y);
}

void Rocketer::SetState(int state)
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
		vx = 0.1 * nx;
		vy = -0.4;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_STOP:
		x = entryPosition.x;
		y = entryPosition.y;
		vx = vy = 0;
		StartRespawnTimeCounter();
		break;
	case ENEMY_SIT:
		vy = 0;
		lastTimeShoot = GetTickCount();
		deltaTimeToShoot = 500 + rand() % 2000;
	default:
		break;
	}
}

void Rocketer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y; 
	right = left + 24;
	bottom = top + 40;
}

void Rocketer::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - 100;
	right = entryPosition.x + 100;
	top = entryPosition.y - 200;
	bottom = entryPosition.y + 200;
}

bool Rocketer::IsAbleToActivate()
{
	DWORD now = GetTickCount();

	if (isRespawnWaiting == true && now - respawnTime_Start >= 3000)
		return true;

	return false;
}