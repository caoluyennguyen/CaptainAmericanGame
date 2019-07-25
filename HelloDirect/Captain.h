#pragma once

#include <vector>

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Bullet.h"

using namespace std;

class Captain : public GameObject
{

public:
	bool isStand = true; 

	Captain() : GameObject() {}

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetState(int state);

	bool IsTouchGround() { return vy == 0; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


