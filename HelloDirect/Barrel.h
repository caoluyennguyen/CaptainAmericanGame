#pragma once
#include "GameObject.h"
#include "Box.h"
#include "Captain.h"
class Barrel :
	public GameObject
{
public:
	Barrel();
	~Barrel() {};

	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);
};

