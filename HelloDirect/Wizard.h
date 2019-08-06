#pragma once
#include "GameObject.h"

class Wizard :
	public GameObject
{
	int HP = 3;//BOSS_HP; 

	bool isFlyToTarget = false;
	bool isFlyToCap = false;

	D3DXVECTOR2 capPostion;
	D3DXVECTOR2 target;

	int idTarget = 0;

	int startTimeWaiting = 0;
	bool isStopWaiting = false;

	bool dropItem = false;
public:
	Wizard();
	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);

	D3DXVECTOR2 GetRandomSpot();
	void FlyToTarget(DWORD dt);
	void GetVelocity();

	void StartStopTimeCounter() { isStopWaiting = true; startTimeWaiting = GetTickCount(); }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetSimonPosition(float sx, float sy) { capPostion.x = sx; capPostion.y = sy; }

	int GetIdTarget() { return idTarget; }

	bool DropItem() { return dropItem; }

	void LoseHP(int x);
	int GetHP() { return HP; }
};

