#pragma once

#include "GameObject.h"

class Shooter : public GameObject
{
	DWORD respawnTime_Start = 0;
	bool isRespawnWaiting = false;

	DWORD lastTimeShoot = 0; // thời gian kể từ lúc vừa bắn xong đến lần bắn tiếp theo
	DWORD deltaTimeToShoot = 0; // khoảng thời gian kể từ lúc fishman xuất hiện đến lúc bắn 

	int nxShoot = 0; // Hướng quay mặt sau khi bắn (để luôn quay mặt về phía Simon)

public:
	Shooter();
	~Shooter() {};

	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool stopMovement = false);
	void Render();
	void SetState(int state);
	void SetNxShoot(int x) { nxShoot = x; }
	void StartRespawnTimeCounter() { isRespawnWaiting = true; respawnTime_Start = GetTickCount(); }
	void SetIsRespawnWaiting(bool x) { isRespawnWaiting = x; }
	bool IsRespawnWaiting() { return isRespawnWaiting; }
	bool IsAbleToActivate();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetLastTimeShoot() { return lastTimeShoot; }
	int GetDeltaTimeToShoot() { return deltaTimeToShoot; }
};

