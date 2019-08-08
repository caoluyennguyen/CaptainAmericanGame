#pragma once
#include "GameObject.h"
#include "Box.h"
#include "Shield.h"

class MiniBoss : 
	public GameObject
{
	int HP = 3;

	DWORD lastTimeShoot = 0; 
	DWORD lastTimeRun = 0;
	DWORD lastTimeThrow = 0;
	DWORD deltaTime = 0;

	D3DXVECTOR2 capPostion;
	D3DXVECTOR2 target;

	int idTarget = 0;

	int startTimeWaiting = 0;
	bool isStopWaiting = false;

	bool dropItem = false;
public:
	MiniBoss();
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

	void SetCapPosition(float sx, float sy) { capPostion.x = sx; capPostion.y = sy; }

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetLastTimeRun() { return lastTimeRun; }
	int GetLastTimeThrow() { return lastTimeThrow; }
	int GetDeltaTime() { return deltaTime; }

	void LoseHP(int x);
	int GetHP() { return HP; }
};

