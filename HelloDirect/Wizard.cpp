#include "Wizard.h"

Wizard::Wizard()
{
	AddAnimation(WIZARD_FLY_ANI);
	AddAnimation(WIZARD_DEAD_ANI);
	AddAnimation(WIZARD_SHOOT_ANI);
	AddAnimation(WIZARD_SIT_ANI);
	AddAnimation(WIZARD_STOP_ANI);
}

void Wizard::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_WIZARD, FILEPATH_TEX_WIZARD, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texWizard = textures->Get(ID_TEX_WIZARD);

	// idle
	sprites->Add(120001, 48, 130, 77, 181, texWizard);
	// shoot
	sprites->Add(120002, 66, 76, 104, 120, texWizard);
	// die
	sprites->Add(120003, 220, 37, 253, 64, texWizard);
	sprites->Add(120004, 268, 44, 304, 64, texWizard);
	//sprites->Add(120005, 228, 124, 252, 168, texWizard);
	//sprites->Add(120006, 260, 124, 284, 168, texWizard);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(120001);
	ani->Add(120002);
	ani->Add(120003);
	animations->Add(WIZARD_FLY_ANI, ani);

	ani = new Animation(200);
	ani->Add(120001);
	animations->Add(WIZARD_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(120006);
	animations->Add(WIZARD_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(120001);
	animations->Add(WIZARD_SIT_ANI, ani);
}

void Wizard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
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

void Wizard::Render()
{
	if (state != ENEMY_STOP)
		animations[state]->Render(1, nx, x, y);
}

void Wizard::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_RUN:
		//vx = 0.1f * nx;
		//lastTimeShoot = GetTickCount();
		//deltaTimeToShoot = 500 + rand() % 2000;
		//respawnTime_Start = 0;
		//isRespawnWaiting = false;
		break;
	case ENEMY_DESTROYED:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_SHOOT:
		vx = 0.1 * nx;
		vy = -0.2;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_STOP:
		x = entryPosition.x;
		y = entryPosition.y;
		vx = vy = 0;
		//StartRespawnTimeCounter();
		break;
	case ENEMY_SIT:
		//lastTimeShoot = GetTickCount();
		//deltaTimeToShoot = 500 + rand() % 2000;
	default:
		break;
	}
}

void Wizard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 24;
	bottom = top + 40;
}

void Wizard::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - 100;
	right = entryPosition.x + 100;
	top = entryPosition.y - 200;
	bottom = entryPosition.y + 200;
}