#include "Box.h"

Ground::Ground() : GameObject()
{
	AddAnimation(GROUND_ANI_1);

}

void Ground::LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations)
{
	textures->Add(ID_TEX_GROUND, FILEPATH_TEX_GROUND, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND);

	sprites->Add(40001, 0, 0, 17, 17, texGround);

	LPANIMATION ani;

	ani = new Animation();
	ani->Add(40001);
	animations->Add(GROUND_ANI_1, ani);
}

void Ground::Render()
{
	animations[0]->Render(1, -1, x, y);
}

void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GROUND_BBOX_WIDTH;
	b = y + GROUND_BBOX_HEIGHT;
}

void Ground::GetActiveBoundingBox(float& left, float& top, float& right, float& bottom)
{
	GetBoundingBox(left, top, right, bottom);
}
