#pragma once
#include "GameObject.h"
#include "Box.h"

class Wizard :
	public GameObject
{
	int HP = 3;//BOSS_HP; 

	D3DXVECTOR2 capPostion;
	DWORD lastTimeShoot = 0; // thời gian kể từ lúc vừa bắn xong đến lần bắn tiếp theo
	DWORD lastTimeFly = 0; // thời gian kể từ lúc vừa bắn xong đến lần bắn tiếp theo
	DWORD deltaTime = 0;

	int rollBack = 1;

	int startTimeWaiting = 0;
	bool isStopWaiting = false;
	bool isFlying = true;
	bool isShooting = true;

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

	void FlyAroundScreen(DWORD dt);
	void IsShooting();

	void StartStopTimeCounter() { isStopWaiting = true; startTimeWaiting = GetTickCount(); }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetCapPosition(float sx, float sy) { capPostion.x = sx; capPostion.y = sy; }

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetLastTimeFly() { return lastTimeFly; }
	int GetDeltaTime() { return deltaTime; }

	void LoseHP(int x);
	int GetHP() { return HP; }
};

