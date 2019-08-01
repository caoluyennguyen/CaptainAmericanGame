#pragma once

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
class Shield : public GameObject
{
public:
	Shield();
	~Shield() {};

	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	bool CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom);

};

