#include "GiftedPoint.h"

GiftedPoint::GiftedPoint()
{
	AddAnimation(CLOSE_POINT_ANI);
	AddAnimation(OPEN_POINT_ANI);

}

void GiftedPoint::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_GIFTED_POINT, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texGiftedPoint = textures->Get(ID_TEX_GIFTED_POINT);

	sprites->Add(30001, 216, 308, 224, 316, texGiftedPoint); 

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(30001, 150);
	animations->Add(CLOSE_POINT_ANI, ani);

	ani = new Animation();
	ani->Add(30001, 150);
	animations->Add(OPEN_POINT_ANI, ani);

}

void GiftedPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool stopMovement)
{
	if (state == 1 && animations[state]->IsOver(200) == true) 	//nếu render xong hết đốm lửa rồi thì set enable = false -> biến mất
	{
		this->isEnable = false;
	}
}

void GiftedPoint::Render()
{
	animations[state]->Render(1, nx, x, y);
}

void GiftedPoint::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case 0: // close
		break;
	case 1: // open
		animations[state]->SetAniStartTime(GetTickCount());
		break;
	default:
		break;
	}
}

void GiftedPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	switch (state)
	{
	case 0:
		right = left + 8;
		bottom = top + 8;
		break;
	case 1:
		right = left + 8;
		bottom = top + 8;
		break;
	default:
		right = left;
		bottom = top;
		break;
	}
}

void GiftedPoint::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}