#pragma once

#include <vector>

#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Box.h"
#include "Bullet.h"
#include "Shield.h"
#include "Shooter.h"
#include "Rocketer.h"

using namespace std;

class Captain : public GameObject
{
	int score;
	int item;
	int energy;
	int life;
	int HP;

	bool isUntouchable = false;
	DWORD untouchable_start = 0;

public:
	bool isStand = false;
	bool hasShield = true; 
	bool isTouchGround = false;
	int changeScene = -1;

	Captain();
	int GetEnergy() { return this->energy; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetItem() { return this->item; }
	int GetHP() { return this->HP; }

	void Render();
	virtual void LoadResources(Textures*& textures, Sprites*& sprites, Animations*& animations);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void GetActiveBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetChangeScene() { return this->changeScene; }
	void SetChangeScene(int x) { this->changeScene = x; }
	void SetState(int state);
	void StartUntouchable() { isUntouchable = true; untouchable_start = GetTickCount(); }
	void AddScore(int x) { score += x; }
	void LoseEnergy(int x) { energy -= x; }
	void LoseHP(int x);
	void CheckCollisionWithEnemyActiveArea(vector<LPGAMEOBJECT>* listEnemy);

	bool IsTouchGround() { return isTouchGround; }
	bool IsStand() { return this->isStand; }
};


