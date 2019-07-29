#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Captain.h"
#include "Box.h"
#include "Bullet.h"
#include "Grid.h"
#include "TileMap.h"
#include "Input.h"


class SceneManager
{
	int IDScene;

	Game* game;
	Captain* captain;
	Enemy* enemy;
	Ground* ground;

	TileMaps* tilemaps = TileMaps::GetInstance();
	Textures* textures = Textures::GetInstance();
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	vector<LPGAMEOBJECT> Objects;

public:
	SceneManager(Game* game, int idScene);
	~SceneManager();

	void LoadResources();		// load all sprites and tilemaps
	void LoadObjectsFromFile(LPCWSTR FilePath);		// load all objects (position, state, isenable) from file and save to vector Objects

	virtual void Update(DWORD dt);
	virtual void Render();

	void ChangeScene(int scene);
	Captain* GetSimon() { return this->captain; }
};

