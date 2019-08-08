#include "Barrel.h"

Barrel::Barrel()
{
	AddAnimation(BARREL_ANI);
}

void Barrel::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_BARREL, FILEPATH_TEX_MINIBOSS, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texFireball = textures->Get(ID_TEX_BARREL);

	sprites->Add(150001, 402, 42, 424, 56, texFireball);

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(150001);
	animations->Add(BARREL_ANI, ani);
}

void Barrel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (stopMovement == true)
		return;

	GameObject::Update(dt);
	x += dx;

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
				}
				else
					y += dy;
			}
			else if (dynamic_cast<Captain*>(e->obj))
			{
				this->isEnable = false;
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

void Barrel::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Barrel::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case BULLET:
		vx = 0.1f * nx;
		break;
	default:
		break;
	}
}

void Barrel::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 10;
	bottom = top + 10;
}

void Barrel::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
