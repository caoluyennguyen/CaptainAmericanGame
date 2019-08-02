#include "GameInfo.h"

GameInfo::GameInfo(SceneManager* scenes, Game* game)
{
	this->game = game;
	this->scenes = scenes;
	this->captain = scenes->GetCaptain();
}

void GameInfo::Init()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(ID_TEX_HP, FILEPATH_TEX_CAP, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texHP = textures->Get(ID_TEX_HP);

	for (int i = 0; i < 5; i++)
	{
		Sprite* player = new Sprite(100, 234, 306, 246, 318, texHP);
		playerLife.push_back(player);
	}
}

void GameInfo::Update(DWORD dt, bool stopwatch)
{
	captainLife = captain->GetLife();
}

void GameInfo::Render()
{
	for (int i = 0; i < captainLife; i++)
	{
		playerLife[i]->Draw(0, -1, 10, 20 + i * 20);
	}
}