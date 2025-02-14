﻿#pragma once

#include "Game.h"
#include "Grid.h"
#include "TileMap.h"
#include "GameObject.h"
#include "Captain.h"
#include "Box.h"
#include "Bullet.h"
#include "Shield.h"
#include "Shooter.h"
#include "Rocketer.h"
#include "Rocket.h"
#include "Items.h"
#include "GiftedPoint.h"
#include "Skyper.h"
#include "Wizard.h"
#include "MiniBoss.h"
#include "Laser.h"
#include "Barrel.h"
#include "Sound.h"

class SceneManager
{
	int IDScene;

	Game* game;
	Grid* grid;
	Unit* unit;

	Captain* captain = new Captain();
	//Enemy* enemy = new Enemy();
	Shield* shield = new Shield();
	Ground* ground = new Ground();
	Shooter* shooter = new Shooter();
	Rocketer* rocketer = new Rocketer();
	Bullet* bullet = new Bullet();
	Rocket* rocket = new Rocket();
	Items* items = new Items();
	GiftedPoint* point = new GiftedPoint();
	Skyper* skyper = new Skyper();
	Wizard* wizard = new Wizard();
	MiniBoss* miniboss = new MiniBoss();
	Laser* laser = new Laser();
	Barrel* barrel = new Barrel();

	TileMaps* tilemaps = TileMaps::GetInstance();
	Textures* textures = Textures::GetInstance();
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	vector<Unit*> listUnits;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPGAMEOBJECT> listItems;
	vector<LPGAMEOBJECT> listStaticObjectsToRender;
	vector<LPGAMEOBJECT> listMovingObjectsToRender;
	bool isSetSimonAutoWalk = false;
	bool isMovingCamera = false;
	int countDxCamera = 0;
	int countLaser = 1;

	bool isUsingStopWatch = false;
	int stopWatchCounter = 0;

public:
	SceneManager(Game* game, int idScene);
	~SceneManager();

	void LoadResources();		// load all sprites and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);		// load all objects (position, state, isenable) from file and save to vector Objects
	void CreateListChangeSceneObjects();

	void GetObjectFromGrid();

	void Update(DWORD dt);
	void Render();
	void UpdateCameraPosition();
	void UpdateGrid();

	void SetDropItems(LPGAMEOBJECT object);
	void StopedByPosition();

	void ChangeScene(int scene);
	int GetIDScene() { return this->IDScene; }

	Captain* GetCaptain() { return this->captain; }
	//Enemy* GetBoss() { return this->enemy; }
	Shield* GetShield() { return this->shield; }


	bool IsUsingStopWatch() { return isUsingStopWatch; }
	void StartStopWatch() { isUsingStopWatch = true; stopWatchCounter = GetTickCount(); }

	void Captain_Update(DWORD dt);
	//void Enemy_Update(DWORD dt);
	void Shield_Update(DWORD dt);
	void Shooter_Update(DWORD dt, LPGAMEOBJECT& object);
	void Rocketer_Update(DWORD dt, LPGAMEOBJECT& object);
	void Skyper_Update(DWORD dt, LPGAMEOBJECT& object);
	void Wizard_Update(DWORD dt, LPGAMEOBJECT& object);
	void MiniBoss_Update(DWORD dt, LPGAMEOBJECT& object);
};

