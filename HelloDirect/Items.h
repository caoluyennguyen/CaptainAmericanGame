﻿#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "Box.h"
#include "Captain.h"

class Items : public GameObject
{

	DWORD timeAppear;   // thời gian bắt đầu xuất hiện của item, dùng để xét cho item tự huỷ
public:
	Items();

	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);

	void SetItem(int idItem);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

};

