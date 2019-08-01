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
	//enemy->LoadResources(textures, sprites, animations);
	ground->LoadResources(textures, sprites, animations);
	shield->LoadResources(textures, sprites, animations);
	shooter->LoadResources(textures, sprites, animations);
	rocketer->LoadResources(textures, sprites, animations);
	bullet->LoadResources(textures, sprites, animations);

	tilemaps->Add(STAGE_1, FILEPATH_TEX_STAGE_1, FILEPATH_DATA_STAGE_1, 2048, 288, 16, 16);
	tilemaps->Add(STAGE_1_BOSS, FILEPATH_TEX_STAGE_1_BOSS, FILEPATH_DATA_STAGE_1_BOSS, 255, 255, 16, 16);
	
	captain = new Captain();
	shield = new Shield();
	shield->SetEnable(false);
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
		/*case ENEMY:
			enemy = new Enemy();
			enemy->SetPosition(pos_x, pos_y);
			enemy->SetState(state);
			enemy->SetEnable(isEnable);
			enemy->SetIDItem(idItem);
			unit = new Unit(grid, enemy, pos_x, pos_y);
			break;*/
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			unit = new Unit(grid, ground, pos_x, pos_y);
			break;
		case SHOOTER:
			shooter = new Shooter();
			shooter->SetPosition(pos_x, pos_y);
			shooter->SetState(state);
			shooter->SetEnable(isEnable);
			shooter->SetIDItem(idItem);
			unit = new Unit(grid, shooter, pos_x, pos_y);
			break;
		case ROCKETER:
			rocketer = new Rocketer();
			rocketer->SetPosition(pos_x, pos_y);
			rocketer->SetState(state);
			rocketer->SetEnable(isEnable);
			rocketer->SetIDItem(idItem);
			unit = new Unit(grid, rocketer, pos_x, pos_y);
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

		/*if (dynamic_cast<Enemy*>(obj))
			listStaticObjectsToRender.push_back(obj);*/
		if (dynamic_cast<Shooter*>(obj) || dynamic_cast<Rocketer*>(obj) ||
			dynamic_cast<Bullet*>(obj))
		{
			listMovingObjectsToRender.push_back(obj);
		}
		listObjects.push_back(obj);
	}
}

void SceneManager::UpdateCameraPosition()
{
	if (captain->x > SCREEN_WIDTH / 2)
		//&& captain->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		game->SetCameraPosition(captain->x - SCREEN_WIDTH / 2, 0);
		/*TileMap * map = tilemaps->Get(IDScene);
		int min_col = map->min_max_col_to_draw[map->index][0];
		int max_col = map->min_max_col_to_draw[map->index][1];

		if (captain->x >= min_col * 32 + (SCREEN_WIDTH / 2 - 16) &&
			captain->x <= max_col * 32 - (SCREEN_WIDTH / 2 - 16))
		{
			game->SetCameraPosition(captain->x - SCREEN_WIDTH / 2, 0);
		}*/
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

	if (IDScene == STAGE_1 && pos_x >= 1950.0f)
	{
		ChangeScene(STAGE_1_BOSS);
		game->SetCameraPosition(0.0f, 0.0f);
		return;
	}
	
	// get object from grid by camera position
	GetObjectFromGrid();

	//Update
	Captain_Update(dt);
	Shield_Update(dt);

	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];

		if (dynamic_cast<Shooter*>(object))
		{
			Shooter_Update(dt, object);
		}
		else if (dynamic_cast<Rocketer*>(object))
		{
			Rocketer_Update(dt, object);
		}
		else
		{
			object->Update(dt, &listObjects);
		}
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

	if (shield->IsEnable() == true)
	{
		shield->Render();
		shield->RenderBoundingBox();
	}
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
	case STAGE_1_BOSS:
		grid = new Grid(2000, 286, 128, 128);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1_BOSS);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	default:
		break;
	}
}


void SceneManager::SetInactivationByPosition()
{
	D3DXVECTOR2 entryViewPort = game->GetCameraPositon();

	for (auto object : listObjects)
	{
		float x, y;
		object->GetPosition(x, y);

		if (x < entryViewPort.x || x > entryViewPort.x + SCREEN_WIDTH - 1)
		{
			if (dynamic_cast<Shooter*>(object) || 
				dynamic_cast<Rocketer*>(object))
			{
				object->SetState(ENEMY_INACTIVE);
			}
			else if (dynamic_cast<Bullet*>(object))
			{
				object->SetEnable(false);
			}
		}
		else if (dynamic_cast<Shooter*>(object) && object->GetState() != ENEMY_INACTIVE)
		{
			shooter = dynamic_cast<Shooter*>(object);

			if (x < entryViewPort.x || x > entryViewPort.x + SCREEN_WIDTH - 1 ||
				y < entryViewPort.y || y > shooter->GetEntryPosition().y)
			{
				shooter->SetState(ENEMY_INACTIVE);
			}
		}
		else if (dynamic_cast<Rocketer*>(object) && object->GetState() != ENEMY_INACTIVE)
		{
			rocketer = dynamic_cast<Rocketer*>(object);

			if (x < entryViewPort.x || x > entryViewPort.x + SCREEN_WIDTH - 1 ||
				y < entryViewPort.y || y > rocketer->GetEntryPosition().y)
			{
				rocketer->SetState(ENEMY_INACTIVE);
			}
		}
	}

}

void SceneManager::Captain_Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(shield);
	for (auto obj : listObjects)
	{
		if ((dynamic_cast<Ground*>(obj) || dynamic_cast<Shooter*>(obj) ||
			dynamic_cast<Bullet*>(obj) || dynamic_cast<Rocketer*>(obj) &&
			obj->GetState() != ENEMY_INACTIVE && obj->IsEnable() == true))
		{
			coObjects.push_back(obj);
		}
	}

	captain->Update(dt, &coObjects);
	captain->CheckCollisionWithEnemyActiveArea(&listObjects);
}

void SceneManager::Shield_Update(DWORD dt)
{
	if (shield->IsEnable() == false)
		return;

	//shield->SetSpeed(0.01f * shield->nx, 0.01f * (captain->y - shield->y));

	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(captain);
	for (auto obj : listObjects)
	{
		if ((dynamic_cast<Shooter*>(obj) &&
			obj->IsEnable() == true))
		{
			coObjects.push_back(obj);
		}
	}

	shield->Update(dt, &coObjects);
	shield->vy = 0.02f * (captain->y - shield->y);
}

void SceneManager::Shooter_Update(DWORD dt, LPGAMEOBJECT& object)
{
	shooter = dynamic_cast<Shooter*>(object);

	if (shooter->GetState() == ENEMY_ACTIVE &&
		GetTickCount() - shooter->GetLastTimeShoot() >= shooter->GetDeltaTimeToShoot())
	{
		shooter->SetState(ENEMY_SHOOT);

		// Bắn đạn
		float sx, sy, nx;
		shooter->GetPosition(sx, sy);
		nx = shooter->GetOrientation();

		bullet = new Bullet();
		bullet->SetPosition(sx + 5.0f, sy + 10.0f);
		bullet->SetOrientation(nx);
		bullet->SetState(BULLET);
		bullet->SetEnable(true);

		unit = new Unit(grid, bullet, sx + 5.0f, sy + 10.0f);

		// Quay hướng về phía captain
		float cx, cy;
		captain->GetPosition(cx, cy);

		if (sx < cx) shooter->SetNxShoot(1);
		else shooter->SetNxShoot(-1);
	}
	else
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj))
			{
				coObjects.push_back(obj);
			}
		}

		shooter->Update(dt, &coObjects);
	}
}

void SceneManager::Rocketer_Update(DWORD dt, LPGAMEOBJECT& object)
{
	rocketer = dynamic_cast<Rocketer*>(object);

	if (rocketer->GetState() == ENEMY_ACTIVE &&
		GetTickCount() - rocketer->GetLastTimeShoot() >= rocketer->GetDeltaTimeToShoot())
	{
		rocketer->SetState(ENEMY_SHOOT);

		float sx, sy, nx;
		rocketer->GetPosition(sx, sy);
		nx = rocketer->GetOrientation();
		float cx, cy;
		captain->GetPosition(cx, cy);

		if (sx < cx) rocketer->SetNxShoot(1);
		else rocketer->SetNxShoot(-1);
	}
	else
	{
		vector<LPGAMEOBJECT> coObjects;

		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj))
			{
				coObjects.push_back(obj);
			}
		}

		rocketer->Update(dt, &coObjects);
	}
}