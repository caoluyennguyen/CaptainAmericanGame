#include "Rocket.h"

Rocket::Rocket()
{
	AddAnimation(ROCKET_ANI);
	SetState(BULLET);
}


Rocket::~Rocket()
{
}

void Rocket::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_ROCKET, FILEPATH_TEX_SMALL_ENEMY, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texFireball = textures->Get(ID_TEX_ROCKET);

	sprites->Add(90001, 232, 73, 247, 80, texFireball);
	sprites->Add(90002, 256, 73, 271, 80, texFireball);


	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(90001);
	ani->Add(90002);
	animations->Add(ROCKET_ANI, ani);
}

void Rocket::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (stopMovement == true)
		return;

	GameObject::Update(dt);
	x += dx;
}

void Rocket::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Rocket::SetState(int state)
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

void Rocket::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 6;
	bottom = top + 6;
}

void Rocket::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}

