#include "Items.h"


Items::Items() : GameObject()
{
	vy = 0.2f;

	AddAnimation(HEART_ANI);
	AddAnimation(STAR_ANI);

	timeAppear = -1;
}

void Items::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_ITEM_HEART, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM_STAR, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));
	
	LPDIRECT3DTEXTURE9 tex;

	tex = textures->Get(ID_TEX_ITEM_HEART);
	sprites->Add(80001, 200, 311, 208, 320, tex);

	tex = textures->Get(ID_TEX_ITEM_STAR);
	sprites->Add(80002, 168, 306, 176, 320, tex);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(80001);
	animations->Add(HEART_ANI, ani);

	ani = new Animation();
	ani->Add(80002);
	animations->Add(STAR_ANI, ani);

}

void Items::Render()
{
	animations[state]->Render(1, -1, x, y);
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (timeAppear == -1)
	{
		timeAppear = GetTickCount();
	}
	else
	{
		DWORD now = GetTickCount();

		if (now - timeAppear > 3000)
		{
			isEnable = false;
			return;
		}
	}


	GameObject::Update(dt);

	// Check collision between item and ground (falling on ground)
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

		y += min_ty * dy + ny * 0.1f;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Items::SetItem(int idItem)
{
	state = idItem;
}

void Items::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	switch (state)
	{
	case HEART:
		right = left + 8;
		bottom = top + 14;
		break;
	case STAR:
		right = left + 8;
		bottom = top + 9;
		break;
	default:
		right = left;
		bottom = top;
		break;
	}
}

void Items::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
