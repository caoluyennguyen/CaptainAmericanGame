#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"

class Enemy : public GameObject
{
public:
	Enemy();

	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* Objects = NULL, vector<LPGAMEOBJECT*>* coObject = NULL);
	void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);
	//bool IsAbleToActivate();
};

