#include "Shield.h"
#include "Captain.h"
#include "Bullet.h"
#include "Box.h"
#include "Shooter.h"
#include "Rocketer.h"
#include "GiftedPoint.h"

Shield::Shield()
{
	AddAnimation(SHIELD_ANI);
}

void Shield::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{

	textures->Add(ID_TEX_SHIELD, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 tex = textures->Get(ID_TEX_SHIELD);

	sprites->Add(20001, 116, 272, 131, 288, tex);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(20001);
	animations->Add(SHIELD_ANI, ani);
}

void Shield::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	GameObject::Update(dt);

	vx -= 0.01f * nx;

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
		// kiểm tra va chạm với object
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Shooter*>(e->obj)
				|| dynamic_cast<Rocketer*>(e->obj))
			{
				e->obj->SetState(ENEMY_DESTROYED);
			}
			else if (dynamic_cast<Ground*>(e->obj)) // || dynamic_cast<Enemy*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<Captain*>(e->obj))
			{
				this->isEnable = false;
			}
			else if (dynamic_cast<GiftedPoint*>(e->obj))
			{
				e->obj->SetState(1);
			}
		}
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Shield::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void Shield::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 15;
	bottom = top + 16;
}

void Shield::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
