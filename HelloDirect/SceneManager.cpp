#include "SceneManager.h"


SceneManager::SceneManager(Game* game, int idScene)
{
	this->game = game;
	IDScene = idScene;
}


SceneManager::~SceneManager()
{
}

void SceneManager::LoadResources()
{
	captain = new Captain();
	captain->LoadResources(textures, sprites, animations);

	enemy = new Enemy();
	enemy->LoadResources(textures, sprites, animations);

	ground = new Ground();
	ground->LoadResources(textures, sprites, animations);

	tilemaps->Add(STAGE_1, FILEPATH_TEX_STAGE_1, FILEPATH_DATA_STAGE_1, 2048, 288, 16, 16);
	tilemaps->Add(STAGE_2, FILEPATH_TEX_STAGE_2, FILEPATH_DATA_STAGE_2, 2048, 288, 16, 16);
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	Objects.clear();

	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
		DebugOut(L"[INFO] Scene %d load data failed: file path = %s\n", IDScene, FilePath);
		fs.close();
		return;
	}

	captain = new Captain();
	captain->SetPosition(20.0f, 50.0f);
	Objects.push_back(captain);

	int ID_Obj;
	float pos_x, pos_y;
	int state;
	bool isEnable;

	while (!fs.eof())
	{
		fs >> ID_Obj >> pos_x >> pos_y >> state >> isEnable;

		switch (ID_Obj)
		{
		case ENEMY:
			enemy = new Enemy();
			enemy->SetPosition(pos_x, pos_y);
			enemy->SetState(state);
			enemy->isEnable = isEnable;
			Objects.push_back(enemy);
			break;
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->isEnable = isEnable;
			Objects.push_back(ground);
			break;
		default:
			break;
		}
	}

	fs.close();
	DebugOut(L"Objects size: %d \n", Objects.size());
 }

void SceneManager::Update(DWORD dt)
{
	float pos_x, pos_y;
	captain->GetPosition(pos_x, pos_y);

	DebugOut(L"%f %f\n", pos_x, pos_y);

	if (IDScene == STAGE_1 && pos_x >= 1450.0f)
	{
		ChangeScene(STAGE_2);
		game->SetCameraPosition(0.0f, 0.0f);
		return;
	}

	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->isEnable == false)
			continue;


		vector<LPGAMEOBJECT*> coObjects; // truyền con trỏ cấp 2, để trong hàm update có thể thay đổi trực tiếp đến phần tử của Objects

		if (dynamic_cast<Captain*>(Objects[i]))
		{
			for (int j = 0; j < Objects.size(); j++)
			{
				if (Objects[j]->isEnable == false)
					continue;

				if (i != j) // thêm tất cả objects "ko phải là simon", dùng trong hàm update của simon 
					coObjects.push_back(&(Objects[j]));
			}
		}
		else
		{
			coObjects.push_back(&(Objects[i]));
		}

		Objects[i]->Update(dt, &Objects, &coObjects);
	}

	// render camera
	float cx, cy;
	captain->GetPosition(cx, cy);

	if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
		game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCameraPositon());

	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->isEnable == false)
			continue;

		Objects[i]->Render();
	}
}

void SceneManager::ChangeScene(int scene)
{
	IDScene = scene;

	switch (IDScene)
	{
	case STAGE_1:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		break;
	case STAGE_2:
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		break;
	default:
		break;
	}
}
