#pragma once

#include "d3dx9.h"
#include "Define.h"
#include "Textures.h"
#include "Sprites.h"
#include "Captain.h"
#include "SceneManager.h"

#include <vector>
#include <string>

using namespace std;
class GameInfo
{
private:
	SceneManager* scenes;
	Game* game;
	Captain* captain;

	vector<LPSPRITE> playerLife;

	int scene;
	int captainLife;
	int bossHP;

public:
	GameInfo(SceneManager* scenes, Game* game);
	~GameInfo() {};

	void Init();
	void Update(DWORD dt, bool stopwatch);
	void Render();
};

