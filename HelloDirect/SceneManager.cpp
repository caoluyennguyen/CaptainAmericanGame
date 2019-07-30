#include "SceneManager.h"


SceneManager::SceneManager(Game * game, int idScene)
{
	this->game = game;
	IDScene = idScene;
}


SceneManager::~SceneManager()
{
}

void SceneManager::LoadResources()
{
	captain->LoadResources(textures, sprites, animations);

	enemy->LoadResources(textures, sprites, animations);

	ground->LoadResources(textures, sprites, animations);

	tilemaps->Add(STAGE_1, FILEPATH_TEX_STAGE_1, FILEPATH_DATA_STAGE_1, 2048, 288, 16, 16);
	tilemaps->Add(STAGE_2, FILEPATH_TEX_STAGE_2, FILEPATH_DATA_STAGE_2, 2048, 288, 16, 16);
	
	captain = new Captain();
}

void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
{
	fstream fs;
	fs.open(FilePath, ios::in);
	if (fs.fail())
	{
		DebugOut(L"[INFO] Scene %d load data failed: file path = %s\n", IDScene, FilePath);
		fs.close();
		return;
	}

	int ID_Obj;
	float pos_x, pos_y;
	int state;
	bool isEnable;
	int idItem;

	while (!fs.eof())
	{
		fs >> ID_Obj >> pos_x >> pos_y >> state >> isEnable >> idItem;

		switch (ID_Obj)
		{
		case ENEMY:
			enemy = new Enemy();
			enemy->SetPosition(pos_x, pos_y);
			enemy->SetState(state);
			enemy->SetEnable(isEnable);
			enemy->SetIDItem(idItem);
			unit = new Unit(grid, enemy, pos_x, pos_y);
			break;
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			unit = new Unit(grid, ground, pos_x, pos_y);
			break;
		default:
			break;
		}
	}

	fs.close();
 }

void SceneManager::GetObjectFromGrid()
{
	listUnits.clear();
	listObjects.clear();
	listStaticObjectsToRender.clear();
	listMovingObjectsToRender.clear();

	grid->Get(game->GetCameraPositon(), listUnits);

	DebugOut(L"%d \n", listUnits.size());

	for (int i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i]->GetObj();

		if (dynamic_cast<Enemy*>(obj))
			listStaticObjectsToRender.push_back(obj);

		listObjects.push_back(obj);
	}
}

void SceneManager::UpdateCameraPosition()
{
	if (captain->x > SCREEN_WIDTH / 2 &&
		captain->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		TileMap* map = tilemaps->Get(IDScene);
		int min_col = map->min_max_col_to_draw[map->index][0];
		int max_col = map->min_max_col_to_draw[map->index][1];

		if (captain->x >= min_col * 16 + (SCREEN_WIDTH / 2 - 8) &&
			captain->x <= max_col * 16 - (SCREEN_WIDTH / 2 - 8))
		{
			game->SetCameraPosition(captain->x - SCREEN_WIDTH / 2, 0);
		}
	}
}

void SceneManager::UpdateGrid()
{
	for (int i = 0; i < listUnits.size(); i++)
	{
		float newPos_x, newPos_y;
		listUnits[i]->GetObj()->GetPosition(newPos_x, newPos_y);
		listUnits[i]->Move(newPos_x, newPos_y);
	}
}

void SceneManager::Update(DWORD dt)
{
	float pos_x, pos_y;
	captain->GetPosition(pos_x, pos_y);

	if (IDScene == STAGE_1 && pos_x >= 1450.0f)
	{
		ChangeScene(STAGE_2);
		game->SetCameraPosition(0.0f, 0.0f);
		return;
	}
	
	// get object from grid by camera position
	GetObjectFromGrid();

	//Update
	Captain_Update(dt);

	for (int i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];

		object->Update(dt, &listObjects);
	}

	// render camera
	UpdateCameraPosition();
	// update grid
	UpdateGrid();
}

void SceneManager::Render()
{
	tilemaps->Get(IDScene)->Draw(game->GetCameraPositon());

	for (auto obj : listStaticObjectsToRender)
	{
		obj->Render();
		obj->RenderBoundingBox();
	}

	for (auto obj : listMovingObjectsToRender)
	{
		obj->Render();
		obj->RenderBoundingBox();
		obj->RenderActiveBoundingBox();
	}

	captain->Render();
	captain->RenderBoundingBox();

}

void SceneManager::ChangeScene(int scene)
{
	IDScene = scene;

	switch (IDScene)
	{
	case STAGE_1:
		grid = new Grid(2048, 480, DEFAULT_CELL_WIDTH, DEFAULT_CELL_HEIGHT);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case STAGE_2:
		grid = new Grid(2048, 480, DEFAULT_CELL_WIDTH, DEFAULT_CELL_HEIGHT);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void SceneManager::Captain_Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	for (auto obj : listObjects)
	{
		if ((dynamic_cast<Ground*>(obj) || dynamic_cast<Enemy*>(obj)
			&& obj->IsEnable() == true))
		{
			coObjects.push_back(obj);
		}
	}

	captain->Update(dt, &coObjects);
	//captain->CheckCollisionWithEnemyActiveArea(&listObjects);
}
