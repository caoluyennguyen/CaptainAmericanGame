#include "Bullet.h"



void Enemy::LoadResources()
{
	Textures* texture = Textures::GetInstance();

	texture->Add(ID_TEX_ENEMY, FILEPATH_TEX_ENEMY, D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texCandle = texture->Get(ID_TEX_ENEMY);

	sprites->Add(30001, 268, 85, 298, 128, texCandle); // normal candle
	sprites->Add(30002, 308, 85, 338, 128, texCandle);


	LPANIMATION ani;

	ani = new Animation();
	ani->Add(30001, 150);
	ani->Add(30002, 150);
	animations->Add(0, ani);

	AddAnimation(0);

	//SetPosition(160.0f, 224.0f);
}

void Enemy::Render()
{
	animations[state]->Render(nx, x, y);
}

void Enemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY_BBOX_WIDTH;
	bottom = y + ENEMY_BBOX_HEIGHT;
}
