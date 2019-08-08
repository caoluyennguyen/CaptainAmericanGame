#include "Wizard.h"

Wizard::Wizard()
{
	AddAnimation(WIZARD_FLY_UP_ANI);	
	AddAnimation(WIZARD_SHOOT_ANI);
	AddAnimation(WIZARD_DEAD_ANI);
	AddAnimation(WIZARD_IDLE_ANI);
	AddAnimation(WIZARD_STOP_ANI);
	AddAnimation(WIZARD_FLY_UP_ANI);
	AddAnimation(WIZARD_FLY_UP_ANI);
	AddAnimation(WIZARD_FLY_SHOOT_ANI);
}

void Wizard::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_WIZARD, FILEPATH_TEX_WIZARD, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texWizard = textures->Get(ID_TEX_WIZARD);

	// fly
	sprites->Add(120001, 48, 130, 77, 181, texWizard);
	// fly shoot
	sprites->Add(120002, 131, 134, 157, 181, texWizard);
	sprites->Add(120003, 168, 134, 197, 181, texWizard);
	// die
	sprites->Add(120004, 220, 37, 253, 64, texWizard);
	sprites->Add(120005, 268, 44, 304, 64, texWizard);
	// idle
	sprites->Add(120006, 9, 16, 32, 64, texWizard);
	// shoot
	sprites->Add(120007, 32, 76, 56, 120, texWizard);
	sprites->Add(120008, 66, 76, 104, 120, texWizard);
	sprites->Add(120009, 112, 76, 152, 120, texWizard);

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add(120001);
	animations->Add(WIZARD_FLY_UP_ANI, ani);

	ani = new Animation(200);
	//ani->Add(120002);
	ani->Add(120003);
	animations->Add(WIZARD_FLY_SHOOT_ANI, ani);

	ani = new Animation(200);
	ani->Add(120004);
	ani->Add(120005);
	animations->Add(WIZARD_DEAD_ANI, ani);

	ani = new Animation(200);
	ani->Add(120006);
	animations->Add(WIZARD_IDLE_ANI, ani);

	ani = new Animation(200);
	ani->Add(120007);
	ani->Add(120008);
	ani->Add(120009);
	animations->Add(WIZARD_SHOOT_ANI, ani);
}

void Wizard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == WIZARD_DESTROYED && animations[state]->IsOver(150) == true)
	{
		//SetState(WIZARD_STOP);
		//this->isEnable = false;
		return;
	}
	if (state == WIZARD_FLY_SHOOT && animations[state]->IsOver(200) == false)
	{
		return;
	}

	/*if (isStopWaiting == true)
	{
		if (GetTickCount() - startTimeWaiting > 2000)
		{
			isStopWaiting = false;
			startTimeWaiting = 0;
			isFlying = true;
			isShooting = true;
		}
		else
		{
			isFlying = false;
			isShooting = false;
			return;
		}
	}*/

	FlyAroundScreen(dt);

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

	//if (isFlyToTarget == false)
	//{
	//	isFlyToTarget = true;
	//	// deternmind target
	//	if (idTarget == 1)
	//	{
	//		isFlyToCap = true;
	//		target = capPostion;
	//	}
	//	else
	//	{
	//		target = GetRandomSpot();
	//	}
	//	// get velocity
	//	GetVelocity();
	//}
	//else
	//{
	//	FlyToTarget(dt);
	//}

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
					SetState(WIZARD_IDLE);
					rollBack = -rollBack;
				}
				else
					y += dy;
			}
			else
			{
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
	/*case WIZARD_FLY_UP:
		lastTimeShoot = GetTickCount();
		deltaTime = 500 + rand() % 2000;
		vx = 0;
		vy = -0.1f;
		break;
	case WIZARD_FLY_DOWN:
		vx = 0;
		vy = 0.1f;
		break;
	case WIZARD_FLY_ASIDE:
		vx = -0.1f * rollBack;
		vy = 0;
		break;*/
	case WIZARD_FLY_UP:
		lastTimeShoot = GetTickCount();
		deltaTime = 5000;
		
		break;
	case WIZARD_DESTROYED:
		vx = vy = 0;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case WIZARD_SHOOT:
		vx = vy = 0;
		lastTimeFly = GetTickCount();
		deltaTime = 500 + rand() % 2000;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case WIZARD_STOP:
		x = entryPosition.x;
		y = entryPosition.y;
		vx = vy = 0;
		//StartRespawnTimeCounter();
		break;
	case WIZARD_IDLE:
		StartStopTimeCounter();
		animations[state]->SetAniStartTime(GetTickCount());
		//deltaTimeToShoot = 500 + rand() % 2000;
	case WIZARD_FLY_SHOOT:
		vx = -0.1f * rollBack;
		vy = 0;
		break;
		animations[state]->SetAniStartTime(GetTickCount());
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

//void Wizard::IsFlying(DWORD dt)
//{
//	if (isFlying == true)
//	{
//		if (rollBack == 1)
//		{
//			if (x > 207.0 && y > 50.0f)
//			{
//				SetState(WIZARD_FLY_UP);
//			}
//			else if (y < 50.0f && x > 65)
//			{
//				if (x < capPostion.x + 10 && x > capPostion.x - 10)
//				{
//					SetState(WIZARD_FLY_SHOOT);
//				}
//				else SetState(WIZARD_FLY_ASIDE);
//			}
//			else if (x < (65.0f - rand() % 65))
//			{
//				SetState(WIZARD_FLY_DOWN);
//			}
//		}
//		else
//		{
//			if (x < 65.0f && y > 50.0f)
//			{
//				SetState(WIZARD_FLY_UP);
//			}
//			else if (y < 50.0f && x < 207.0f)
//			{
//				if (x < capPostion.x + 10 && x > capPostion.x - 10)
//				{
//					SetState(WIZARD_FLY_SHOOT);
//				}
//				else SetState(WIZARD_FLY_ASIDE);
//			}
//			if (x > 207.0)
//			{
//				SetState(WIZARD_FLY_DOWN);
//			}
//		}
//	}
//}

void Wizard::FlyAroundScreen(DWORD dt)
{
	if (rollBack == 1)
	{
		if (x > 207.0 && y > 50.0f)
		{
			vx = 0;
			vy = -0.1f;
		}
		else if (y < 50.0f && x > 65)
		{
			if (x < capPostion.x + 10 && x > capPostion.x - 10)
			{
				SetState(WIZARD_FLY_SHOOT);
			}
			else
			{
				SetState(WIZARD_FLY_UP);
				vx = -0.1f * rollBack;
				vy = 0;
			}
		}
		else if (x < (65.0f - rand() % 65))
		{
			vx = 0;
			vy = 0.1f;
		}
	}
	else
	{
		if (x < 65.0f && y > 50.0f)
		{
			vx = 0;
			vy = -0.1f;
		}
		else if (y < 50.0f && x < 207.0f)
		{
			if (x < capPostion.x + 10 && x > capPostion.x - 10)
			{
				SetState(WIZARD_FLY_SHOOT);
			}
			else
			{
				SetState(WIZARD_FLY_UP);
				vx = -0.1f * rollBack;
				vy = 0;
			}
		}
		if (x > 207.0)
		{
			vx = 0;
			vy = 0.1f;
		}
	}
}

void Wizard::IsShooting()
{
}