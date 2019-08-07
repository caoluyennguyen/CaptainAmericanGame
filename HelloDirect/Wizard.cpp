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

	// fly
	sprites->Add(120001, 48, 130, 77, 181, texWizard);
	// shoot
	sprites->Add(120002, 131, 134, 157, 181, texWizard);
	sprites->Add(120003, 168, 134, 197, 181, texWizard);
	// die
	sprites->Add(120004, 220, 37, 253, 64, texWizard);
	sprites->Add(120005, 268, 44, 304, 64, texWizard);
	// fly
	sprites->Add(120006, 9, 16, 32, 64, texWizard);
	//sprites->Add(120006, 260, 124, 284, 168, texWizard);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(120001);
	animations->Add(WIZARD_FLY_ANI, ani);

	ani = new Animation(200);
	ani->Add(120002);
	ani->Add(120003);
	animations->Add(WIZARD_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(120004);
	ani->Add(120005);
	animations->Add(WIZARD_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(120006);
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

	if (isStopWaiting == true)
	{
		if (GetTickCount() - startTimeWaiting > 2000)
		{
			isStopWaiting = false;
			startTimeWaiting = 0;
		}
		else
		{
			return;
		}
	}

	//if (state == ENEMY_SHOOT && animations[state]->IsOver(200) == true)
	//{
	//	//nx = nxShoot;
	//	SetState(ENEMY_SIT);
	//	return;
	//}
	//else if (state == ENEMY_STOP)
	//{
	//	vx = 0;
	//	return;
	//}

	if (isFlyToTarget == false)
	{
		isFlyToTarget = true;

		// deternmind target
		if (idTarget == 1)
		{
			isFlyToCap = true;
			target = capPostion;
		}
		else
		{
			target = GetRandomSpot();
		}

		// get velocity
		GetVelocity();
	}
	else
	{
		FlyToTarget(dt);
	}
}

void Wizard::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Wizard::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_RUN:
		idTarget = 0;
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

D3DXVECTOR2 Wizard::GetRandomSpot()
{
	D3DXVECTOR2 randomSpot;

	float left = entryPosition.x - 200;
	float top = entryPosition.y;

	float distance = 0;

	do // chọn điểm random sao cho quãng đường bay dài dài một tí
	{
		randomSpot.x = left + rand() % (2 * 200);
		randomSpot.y = top + rand() % (200);

		float dx = abs(x - randomSpot.x);
		float dy = abs(y - randomSpot.y);

		if (max(dx, dy) / min(dx, dy) > 1.5)
			continue;

		distance = sqrt(pow(x - randomSpot.x, 2) + pow(y - randomSpot.y, 2));
	} while (distance < 100.0f);

	if (randomSpot.x < 0 || randomSpot.x > 256 ||
		randomSpot.y < 0 || randomSpot.y > 400)
	{
		randomSpot.x = 200;
		randomSpot.y = 200;
	}

	return randomSpot;
}


void Wizard::FlyToTarget(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (abs(x - target.x) <= 2.0f)
	{
		isFlyToTarget = false;
		this->SetPosition(target.x, target.y);

		idTarget = (idTarget + 1) % 3;

		if (isFlyToCap == true)
		{
			isFlyToCap = false;
		}
		else
		{
			StartStopTimeCounter();
		}
	}
}

void Wizard::GetVelocity()
{
	float dx = abs(x - target.x);
	float dy = abs(y - target.y);

	// lấy phương hướng
	int nx, ny;

	if (x < target.x) nx = 1;
	else nx = -1;

	if (y < target.y) ny = 1;
	else ny = -1;

	// tính vận tốc
	vx = 0.1f;
	vy = 0.1f * (dy / dx);

	vx *= nx;
	vy *= ny;
}