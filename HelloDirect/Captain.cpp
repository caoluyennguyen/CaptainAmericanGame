#include "Captain.h"

Captain::Captain() : GameObject()
{
	SetState(STAND);

	AddAnimation(STAND_ANI);
	AddAnimation(WALK_ANI);
	AddAnimation(SIT_ANI);
	AddAnimation(JUMP_ANI);
	AddAnimation(HIT_SIT_ANI);
	AddAnimation(HIT_STAND_ANI);
	AddAnimation(UP_ANI);

	score = 0;
	item = -1;
	energy = 99;
	life = 3;
	HP = 10;
}

void Captain::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	//Textures* texture = Textures::GetInstance();

	textures->Add(ID_TEX_CAPTAIN, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texCap = textures->Get(ID_TEX_CAPTAIN);

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
	animations->Add(STAND_ANI, ani);

	ani = new Animation();
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	animations->Add(WALK_ANI, ani);

	ani = new Animation();
	ani->Add(10058);
	animations->Add(SIT_ANI, ani);

	ani = new Animation();
	ani->Add(10027);
	ani->Add(10028);
	ani->Add(10029);
	ani->Add(10030);
	animations->Add(JUMP_ANI, ani);

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
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			/*if (dynamic_cast<Enemy*>(e->obj))
			{
				DebugOut(L"%d %d\n", e->nx, e->ny);

				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				x += dx;
				y += min_ty * dy + ny * 0.1f;

				if (ny != 0) vy = 0;
			}
			else
			{
				x += min_tx * dx + nx * 0.1f;
				y += min_ty * dy + ny * 0.1f;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}*/
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
			//else if (dynamic_cast<Enemy*>(e->obj))
			//{
			//	if (isUntouchable == false)
			//	{
			//		// nếu dơi tông trúng simon thì cho huỷ
			//		if (dynamic_cast<Enemy*>(e->obj))
			//		{
			//			Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
			//			enemy->SetState(ENEMY_DESTROYED);
			//		}

			//		if (e->nx != 0)
			//		{
			//			if (e->nx == 1.0f && this->nx == 1) this->nx = -1;
			//			else if (e->nx == -1.0f && this->nx == -1) this->nx = 1;
			//		}

			//		SetState(DEFLECT);
			//		StartUntouchable();

			//		LoseHP(2);
			//	}
			//	else
			//	{
			//		if (e->nx != 0) x += dx;
			//		if (e->ny != 0) y += dy;
			//	}
			//}
			else
			{
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}


	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//for (int i = 0; i < coEventsResult.size(); i++) delete coEventsResult[i];
}

void Captain::Render()
{
	//animations[state]->Render(nx, x, y);
	/*if (isUntouchable) 
	{
		int r = rand() % 2;

		if (r == 0) animations[state]->Render(1, nx, x, y);
		else animations[state]->Render(1, nx, x, y, 100);
	}
	else
	{
		animations[state]->Render(1, nx, x, y);
	}*/
	animations[state]->Render(1, nx, x, y);
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
		isTouchGround = false;
		isStand = true;
		vy = -CAPTAIN_JUMP_SPEED_Y;
		animations[state]->SetAniStartTime(GetTickCount());
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


void Captain::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

void Captain::LoseHP(int x)
{
	HP -= x;

	if (HP < 0)
	{
		HP = 0;
		life -= 1;
	}
}

void Captain::CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listEnemy)
{
	float captain_l, captain_t, captain_r, captain_b;

	GetBoundingBox(captain_l, captain_t, captain_r, captain_b);

	for (UINT i = 0; i < listEnemy->size(); i++)
	{
		LPGAMEOBJECT enemy = listEnemy->at(i);

		// Không cần xét vùng active nữa khi nó đang active / destroyed
		if (enemy->GetState() == ENEMY_ACTIVE || enemy->GetState() == ENEMY_DESTROYED)
			continue;

		float enemy_l, enemy_t, enemy_r, enemy_b;
		enemy->GetActiveBoundingBox(enemy_l, enemy_t, enemy_r, enemy_b);

		/*if (GameObject::AABB(captain_l, captain_t, captain_r, captain_b, enemy_l, enemy_t, enemy_r, enemy_b) == true)
		{
			D3DXVECTOR2 enemyEntryPostion = enemy->GetEntryPosition();

			if (dynamic_cast<Enemy*>(enemy))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(enemy);
				enemy->SetState(ENEMY_ACTIVE);
				if (enemy->IsAbleToActivate() == true)
				{
					if (enemyEntryPostion.x < x) enemy->SetOrientation(1);
					else enemy->SetOrientation(-1);

					enemy->SetState(ZOMBIE_ACTIVE);
				}
			}
		}*/
	}
}



