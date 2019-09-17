#include "Bullet.h"

Bullet::Bullet()
{
	AddAnimation(BULLET_ANI);
	AddAnimation(BULLET_ANI);
	SetState(BULLET);
}


Bullet::~Bullet()
{
}

void Bullet::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_BULLET, FILEPATH_TEX_SMALL_ENEMY, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texFireball = textures->Get(ID_TEX_BULLET);

	sprites->Add(70001, 265, 33, 271, 39, texFireball);


	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(70001);
	animations->Add(BULLET_ANI, ani);
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (stopMovement == true)
		return;

	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void Bullet::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Bullet::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case BULLET:
		vx = 0.15f * nx;
		vy = 0;
		break;
	default:
		break;
	}
}

void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 6;
	bottom = top + 6;
}

void Bullet::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

