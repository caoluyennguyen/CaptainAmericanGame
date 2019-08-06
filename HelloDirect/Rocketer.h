#pragma once

#include "GameObject.h"

class Rocketer : public GameObject
{
	DWORD respawnTime_Start = 0;
	bool isRespawnWaiting = false;

	DWORD lastTimeShoot = 0; 
	DWORD deltaTimeToShoot = 0;  

public:
	Rocketer();
	~Rocketer() {};

	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);
	void SetNx(int x) { this->nx = x; }
	void StartRespawnTimeCounter() { isRespawnWaiting = true; respawnTime_Start = GetTickCount(); }
	void SetIsRespawnWaiting(bool x) { isRespawnWaiting = x; }
	bool IsRespawnWaiting() { return isRespawnWaiting; }
	bool IsAbleToActivate();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetDeltaTimeToShoot() { return deltaTimeToShoot; }
};

