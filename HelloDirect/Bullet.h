#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"

class Enemy : public GameObject
{
public:
	Enemy() : GameObject() {}

	void LoadResources();
	void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

