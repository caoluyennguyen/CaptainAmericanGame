#include "Captain.h"

Captain::Captain() : GameObject()
{
	SetState(STAND);

	AddAnimation(STAND_ANI);
	AddAnimation(WALK_ANI);
	AddAnimation(UP_ANI);
	AddAnimation(JUMP_ANI);
	AddAnimation(HIT_SIT_ANI);
	AddAnimation(HIT_STAND_ANI);
	AddAnimation(SIT_ANI);
	AddAnimation(HIT_JUMP_ANI);
	AddAnimation(SWIFT_ANI);
	AddAnimation(DEFLECT_ANI);

	AddAnimation(STAND_SHIELD_ANI);
	AddAnimation(WALK_SHIELD_ANI);
	AddAnimation(UP_SHIELD_ANI);
	AddAnimation(JUMP_SHIELD_ANI);
	AddAnimation(HIT_SIT_SHIELD_ANI);
	AddAnimation(HIT_STAND_SHIELD_ANI);
	AddAnimation(SIT_SHIELD_ANI);
	AddAnimation(HIT_JUMP_SHIELD_ANI);
	AddAnimation(SWIFT_SHIELD_ANI);

	item = -1;
	life = 4;
}

void Captain::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	//Textures* texture = Textures::GetInstance();

	textures->Add(ID_TEX_CAPTAIN, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texCap = textures->Get(ID_TEX_CAPTAIN);

	textures->Add(ID_TEX_CAPTAIN_SHIELD, FILEPATH_TEX_CAP_SHIELD, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texCapShield = textures->Get(ID_TEX_CAPTAIN_SHIELD);

#pragma region idle
	sprites->Add(10001, 21, 11, 43, 56, texCap);
	//sprites->Add(10001, 116, 272, 131, 288, texCap);
#pragma endregion

#pragma region move
	sprites->Add(10002, 52, 11, 76, 56, texCap);
	sprites->Add(10003, 84, 11, 108, 56, texCap);
	sprites->Add(10004, 116, 11, 140, 56, texCap);
	sprites->Add(10005, 148, 11, 172, 56, texCap);
#pragma endregion

#pragma region jump
	sprites->Add(10006, 244, 15, 266, 53, texCap);
	sprites->Add(10007, 276, 28, 294, 48, texCap);
	sprites->Add(10008, 312, 30, 332, 48, texCap);
	sprites->Add(10009, 244, 15, 266, 53, texCap);

#pragma endregion

#pragma region shield up
	sprites->Add(10010, 180, 13, 204, 56, texCap);
#pragma endregion

#pragma region hit sit
	sprites->Add(10011, 195, 67, 232, 112, texCap);
	sprites->Add(10012, 244, 67, 272, 112, texCap);
#pragma endregion

#pragma region hit stand
	sprites->Add(10013, 105, 71, 143, 112, texCap);
	sprites->Add(10014, 154, 71, 183, 112, texCap);
#pragma endregion

#pragma region sit
	sprites->Add(10015, 212, 11, 236, 56, texCap);
#pragma endregion

#pragma region deflect
	sprites->Add(10016, 202, 192, 231, 230, texCap);
#pragma endregion

#pragma region hit jump
	sprites->Add(10017, 340, 23, 380, 48, texCap);
#pragma endregion

#pragma region swift
	sprites->Add(10032, 281, 67, 312, 112, texCap);
	sprites->Add(10033, 321, 67, 360, 108, texCap);
#pragma endregion


#pragma region idle shield
	sprites->Add(10018, 203, 3, 228, 48, texCapShield);
#pragma endregion

#pragma region move shield
	sprites->Add(10019, 203, 49, 228, 94, texCapShield);
	sprites->Add(10020, 175, 49, 200, 94, texCapShield);
#pragma endregion

#pragma region jump shield
	//sprites->Add(10021, 61, 90, 87, 135, texCapShield);
	sprites->Add(10021, 206, 97, 228, 135, texCapShield);
	sprites->Add(10022, 276, 28, 294, 48, texCap);
	sprites->Add(10023, 312, 30, 332, 48, texCap);
	//sprites->Add(10024, 61, 90, 87, 135, texCapShield);
	sprites->Add(10024, 206, 97, 228, 135, texCapShield);

#pragma endregion

#pragma region shield up
	sprites->Add(10025, 204, 223, 228, 268, texCapShield);
#pragma endregion

#pragma region hit sit shield
	sprites->Add(10026, 73, 286, 101, 331, texCapShield);
	sprites->Add(10027, 104, 286, 141, 331, texCapShield);
#pragma endregion

#pragma region hit stand shield
	sprites->Add(10028, 147, 132, 186, 177, texCapShield);
	sprites->Add(10029, 189, 132, 228, 177, texCapShield);
#pragma endregion

#pragma region sit shield
	//sprites->Add(10030, 206, 97, 228, 135, texCapShield);
	sprites->Add(10030, 61, 90, 87, 135, texCapShield);
#pragma endregion
/*
#pragma region deflect
	sprites->Add(10031, 202, 192, 231, 230, texCap);
#pragma endregion
*/
#pragma region hit jump
	sprites->Add(10031, 186, 273, 228, 298, texCapShield);
#pragma endregion

#pragma region swift_shield
	sprites->Add(10034, 281, 67, 312, 112, texCap);
	sprites->Add(10035, 321, 67, 360, 108, texCap);
#pragma endregion


#pragma region CREATING ANIMATION
	LPANIMATION ani;

	ani = new Animation();
	ani->Add(10001);
	animations->Add(STAND_ANI, ani);

	ani = new Animation();
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	animations->Add(WALK_ANI, ani);

	ani = new Animation();
	ani->Add(10010);
	animations->Add(UP_ANI, ani);

	ani = new Animation();
	ani->Add(10006);
	ani->Add(10007);
	ani->Add(10008);
	ani->Add(10009);
	animations->Add(JUMP_ANI, ani);

	ani = new Animation();
	ani->Add(10011);
	ani->Add(10012);
	animations->Add(HIT_SIT_ANI, ani);

	ani = new Animation();
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(HIT_STAND_ANI, ani);

	ani = new Animation();
	ani->Add(10015);
	animations->Add(SIT_ANI, ani);

	ani = new Animation();
	ani->Add(10017);
	animations->Add(HIT_JUMP_ANI, ani);

	ani = new Animation();
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(SWIFT_ANI, ani);

	ani = new Animation();
	ani->Add(10016, 400);
	animations->Add(DEFLECT_ANI, ani);


	ani = new Animation();
	ani->Add(10018);
	animations->Add(STAND_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10019);
	ani->Add(10020);
	animations->Add(WALK_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10025);
	animations->Add(UP_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	ani->Add(10024);
	animations->Add(JUMP_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10026);
	ani->Add(10027);
	animations->Add(HIT_SIT_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10028);
	ani->Add(10029);
	animations->Add(HIT_STAND_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10030);
	animations->Add(SIT_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10031);
	animations->Add(HIT_JUMP_SHIELD_ANI, ani);

	ani = new Animation();
	ani->Add(10034);
	ani->Add(10035);
	animations->Add(SWIFT_SHIELD_ANI, ani);
#pragma endregion

}

void Captain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	vy += CAPTAIN_GRAVITY * dt;

	// Reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > CAPTAIN_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		isUntouchable = false;
	}
	
	if (x < 0) x = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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
		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj))
			{
				if (ny != 0)
				{
					if (ny == -1)
					{
						vy = 0;
						isTouchGround = true;
					}
					else
					{
						y += dy;
						isTouchGround = false;
					}
				}
			}
			else if (dynamic_cast<Items*>(e->obj))
			{
				if (e->obj->GetState() == HEART)
				{
					life += 1;
					e->obj->isEnable = false;
				}
				else if (e->obj->GetState() == STAR)
				{
					e->obj->isEnable = false;
				}
			}
			else if (dynamic_cast<Shield*>(e->obj))
			{
				hasShield = true;
				DebugOut(L"%d %d\n", e->nx, e->ny);

				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Shooter*>(e->obj) || dynamic_cast<Rocketer*>(e->obj) || dynamic_cast<Skyper*>(e->obj) ||
				dynamic_cast<Bullet*>(e->obj) || dynamic_cast<Laser*>(e->obj) || dynamic_cast<Barrel*>(e->obj) ||
				dynamic_cast<Wizard*>(e->obj) || dynamic_cast<MiniBoss*>(e->obj))
			{
				if (dynamic_cast<Bullet*>(e->obj) || dynamic_cast<Barrel*>(e->obj))
				{
					if (this->hasShield == true && e->nx != this->nx)
					{
						e->obj->SetEnable(false);
						return;
					}
					else e->obj->SetEnable(false);
				}
				else if (dynamic_cast<Laser*>(e->obj))
				{
					if (e->ny != 0 && e->obj->state == LASER_DOWN &&
						this->GetState() == UP && this->hasShield == true)
					{
						e->obj->SetEnable(false);
						return;
					}
					else if (e->nx != this->nx && e->obj->state == LASER_ASIDE &&
						this->hasShield == true)
					{
						e->obj->SetEnable(false);
						return;
					}
					else
					{
						e->obj->SetEnable(false);
					}
				}
				else if (dynamic_cast<Shooter*>(e->obj) || dynamic_cast<Rocketer*>(e->obj))
				{
					if ((this->state == HIT_JUMP || this->state == HIT_SIT || this->state == HIT_STAND ) &&
						e->nx != this->nx)
					{
						e->obj->SetEnable(false);
						return;
					}
				}

				if (isUntouchable == false)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1.0f && this->nx == 1) this->nx = -1;
						else if (e->nx == -1.0f && this->nx == -1) this->nx = 1;
					}

					LoseHP(1);
					SetState(INJURED);
					StartUntouchable();
				}
				else
				{
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}
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

void Captain::Render()
{
	if (isUntouchable) 
	{
		int r = rand() % 2;

		if (r == 0) animations[state]->Render(1, nx, x, y);
		else animations[state]->Render(1, nx, x, y, 100);
	}
	else
	{
		if (hasShield && this->GetState() != INJURED)
		{
			animations[state + 10]->Render(1, nx, x, y);
		}
		else animations[state]->Render(1, nx, x, y);
	}
}

void Captain::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case STAND:
		vx = 0;
		break;
	case WALK:
		if (nx > 0) vx = CAPTAIN_WALKING_SPEED;
		else vx = -CAPTAIN_WALKING_SPEED;
		break;
	case UP:
		vx = 0;
		vy = 0;
		break;
	case JUMP:
		isTouchGround = false;
		vy = -CAPTAIN_JUMP_SPEED_Y;
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_SIT:
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case HIT_STAND:
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case SIT:
		vx = 0;
		vy = 0;
		break;
	case HIT_JUMP:
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case SWIFT:
		vx = 0.2f * nx;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case INJURED:
		vy = -0.3f;
		if (nx > 0) vx = -0.13f;
		else vx = 0.13f;
		animations[state]->Reset();
		animations[state]->SetAniStartTime(GetTickCount());
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


void Captain::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

void Captain::LoseHP(int x)
{
	life -= x;
}

void Captain::CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listEnemy)
{
	float captain_l, captain_t, captain_r, captain_b;

	GetBoundingBox(captain_l, captain_t, captain_r, captain_b);

	for (UINT i = 0; i < listEnemy->size(); i++)
	{
		LPGAMEOBJECT enemy = listEnemy->at(i);

		// Khi đang chạy hoặc chết thì hủy
		if (enemy->GetState() == ENEMY_RUN || enemy->GetState() == ENEMY_DESTROYED)
			continue;

		float enemy_l, enemy_t, enemy_r, enemy_b;
		enemy->GetActiveBoundingBox(enemy_l, enemy_t, enemy_r, enemy_b);

		if (GameObject::AABB(captain_l, captain_t, captain_r, captain_b, enemy_l, enemy_t, enemy_r, enemy_b) == true)
		{
			D3DXVECTOR2 enemyEntryPostion = enemy->GetEntryPosition();

			if (dynamic_cast<Shooter*>(enemy))
			{
				Shooter * shooter = dynamic_cast<Shooter*>(enemy);
				if (shooter->GetState() == ENEMY_STOP && shooter->IsAbleToActivate() == true)
				{
					shooter->SetState(ENEMY_RUN);
				}
			}
			else if (dynamic_cast<Rocketer*>(enemy))
			{
				Rocketer * rocketer = dynamic_cast<Rocketer*>(enemy);
				if (rocketer->GetState() == ENEMY_STOP && rocketer->IsAbleToActivate() == true)
				{
					rocketer->SetState(ENEMY_RUN);
				}
			}
		}
	}
}



