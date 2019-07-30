#include "Bullet.h"

Enemy::Enemy() : GameObject()
{
	AddAnimation(ENEMY_ANI);

	SetState(ENEMY_ACTIVE);
}

void Enemy::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_ENEMY, FILEPATH_TEX_ENEMY, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_ENEMY);

	sprites->Add(30001, 268, 85, 298, 128, texCandle);
	sprites->Add(30002, 308, 85, 338, 128, texCandle);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(30001, 150);
	ani->Add(30002, 150);
	animations->Add(ENEMY_ANI, ani);
}

void Enemy::Render()
{
	if (state != ENEMY_INACTIVE)
	animations[state]->Render(1, nx, x, y);
}

void Enemy::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case ENEMY_ACTIVE:
		break;
	case ENEMY_DESTROYED:
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	case ENEMY_INACTIVE:
		break;
	default:
		break;
	}
}

void Enemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY_BBOX_WIDTH;
	bottom = y + ENEMY_BBOX_HEIGHT;
}

void Enemy::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = entryPosition.x - ENEMY_ACTIVE_BBOX_WIDTH;
	right = entryPosition.x + ENEMY_ACTIVE_BBOX_WIDTH;
	top = entryPosition.y - ENEMY_ACTIVE_BBOX_HEIGHT;
	bottom = entryPosition.y + ENEMY_ACTIVE_BBOX_HEIGHT;
}

//bool Zombie::IsAbleToActivate()
//{
//	DWORD now = GetTickCount();
//
//	if (isRespawnWaiting == true && now - respawnTime_Start >= ZOMBIE_RESPAWN_TIME)
//		return true;
//
//	return false;
//}