﻿#pragma once

#include "Game.h"
#include "Grid.h"
#include "TileMap.h"
#include "GameObject.h"
#include "Captain.h"
#include "Box.h"
#include "Bullet.h"
//#include "Input.h"


class SceneManager
{
	int IDScene;

	Game * game;
	Grid * grid;
	Unit * unit;

	Captain * captain =  new Captain();
	Enemy * enemy = new Enemy();
	Ground * ground = new Ground();

	TileMaps * tilemaps = TileMaps::GetInstance();
	Textures * textures = Textures::GetInstance();
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();

	vector<Unit*> listUnits;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPGAMEOBJECT> listStaticObjectsToRender;
	vector<LPGAMEOBJECT> listMovingObjectsToRender;
	bool isSetSimonAutoWalk = false;
	bool isMovingCamera = false;
	int countDxCamera = 0;

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
	void SetInactivationByPosition();

	void ChangeScene(int scene);
	int GetIDScene() { return this->IDScene; }

	Captain* GetCaptain() { return this->captain; }
	Enemy* GetBoss() { return this->enemy; }


	bool IsUsingStopWatch() { return isUsingStopWatch; }
	void StartStopWatch() { isUsingStopWatch = true; stopWatchCounter = GetTickCount(); }

	void Captain_Update(DWORD dt);
	void Enemy_Update(DWORD dt);
};

