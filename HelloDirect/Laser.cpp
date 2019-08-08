#include "Laser.h"

Laser::Laser()
{
	AddAnimation(LASER_DOWN_ANI);
	AddAnimation(LASER_ASIDE_ANI);
	AddAnimation(BIG_LASER_ANI);
}

void Laser::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_LASER, FILEPATH_TEX_WIZARD, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texLaser = textures->Get(ID_TEX_LASER);
	LPDIRECT3DTEXTURE9 texBigLaser = textures->Get(ID_TEX_MINIBOSS);

	sprites->Add(140001, 256, 136, 263, 152, texLaser);
	sprites->Add(140002, 248, 162, 256, 167, texLaser);
	sprites->Add(140003, 216, 41, 232, 52, texBigLaser);

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(140001);
	animations->Add(LASER_DOWN_ANI, ani);
	ani = new Animation(100);
	ani->Add(140002);
	animations->Add(LASER_ASIDE_ANI, ani);
	ani = new Animation(100);
	ani->Add(140003);
	animations->Add(BIG_LASER_ANI, ani);
}

void Laser::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (stopMovement == true)
		return;

	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void Laser::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Laser::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case LASER_ASIDE:
		vx = 0.15f * nx;
		vy = 0;
		break;
	case LASER_DOWN:
		vx = 0;
		vy = 0.15f;
		break;
	case BIG_LASER:
		vx = 0.15f * nx;
		vy = 0;
		break;
	default:
		break;
	}
}

void Laser::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 6;
	bottom = top + 6;
}

void Laser::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

