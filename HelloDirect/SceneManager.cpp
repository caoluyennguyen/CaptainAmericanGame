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
	items->LoadResources(textures, sprites, animations);
	ground->LoadResources(textures, sprites, animations);
	shield->LoadResources(textures, sprites, animations);
	shooter->LoadResources(textures, sprites, animations);
	rocketer->LoadResources(textures, sprites, animations);
	bullet->LoadResources(textures, sprites, animations);
	point->LoadResources(textures, sprites, animations);
	rocket->LoadResources(textures, sprites, animations);
	skyper->LoadResources(textures, sprites, animations);
	wizard->LoadResources(textures, sprites, animations);
	miniboss->LoadResources(textures, sprites, animations);

	tilemaps->Add(STAGE_1, FILEPATH_TEX_STAGE_1, FILEPATH_DATA_STAGE_1, 2048, 288, 16, 16);
	tilemaps->Add(STAGE_1_BOSS, FILEPATH_TEX_STAGE_1_BOSS, FILEPATH_DATA_STAGE_1_BOSS, 256, 256, 16, 16);
	tilemaps->Add(STAGE_2, FILEPATH_TEX_STAGE_2, FILEPATH_DATA_STAGE_2, 1024, 244, 16, 16);
	tilemaps->Add(STAGE_2_BOSS, FILEPATH_TEX_STAGE_2_BOSS, FILEPATH_DATA_STAGE_2_BOSS, 512, 480, 16, 16);
	
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
		case GROUND:
			ground = new Ground();
			ground->SetPosition(pos_x, pos_y);
			ground->SetState(state);
			ground->SetEnable(isEnable);
			ground->SetIDItem(idItem);
			unit = new Unit(grid, ground, pos_x, pos_y);
			break;
		case GIFTEDPOINT:
			point = new GiftedPoint();
			point->SetPosition(pos_x, pos_y);
			point->SetState(state);
			point->SetEnable(isEnable);
			point->SetIDItem(idItem);
			unit = new Unit(grid, point, pos_x, pos_y);
			break;
		case SHOOTER:
			shooter = new Shooter();
			shooter->SetPosition(pos_x, pos_y);
			shooter->SetEntryPosition(pos_x, pos_y);
			shooter->SetState(state);
			shooter->SetEnable(isEnable);
			shooter->SetIDItem(idItem);
			unit = new Unit(grid, shooter, pos_x, pos_y);
			break;
		case ROCKETER:
			rocketer = new Rocketer();
			rocketer->SetPosition(pos_x, pos_y);
			rocketer->SetEntryPosition(pos_x, pos_y);
			rocketer->SetState(state);
			rocketer->SetEnable(isEnable);
			rocketer->SetIDItem(idItem);
			unit = new Unit(grid, rocketer, pos_x, pos_y);
			break;
		case SKYPER:
			skyper = new Skyper();
			skyper->SetPosition(pos_x, pos_y);
			skyper->SetEntryPosition(pos_x, pos_y);
			skyper->SetState(state);
			skyper->SetEnable(isEnable);
			skyper->SetIDItem(idItem);
			unit = new Unit(grid, skyper, pos_x, pos_y);
			break;
		case WIZARD:
			wizard = new Wizard();
			wizard->SetPosition(pos_x, pos_y);
			wizard->SetEntryPosition(pos_x, pos_y);
			wizard->SetState(state);
			wizard->SetEnable(isEnable);
			wizard->SetIDItem(idItem);
			unit = new Unit(grid, wizard, pos_x, pos_y);
			break;
		case MINIBOSS:
			miniboss = new MiniBoss();
			miniboss->SetPosition(pos_x, pos_y);
			miniboss->SetEntryPosition(pos_x, pos_y);
			miniboss->SetState(state);
			miniboss->SetEnable(isEnable);
			miniboss->SetIDItem(idItem);
			unit = new Unit(grid, miniboss, pos_x, pos_y);
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

		if (dynamic_cast<Items*>(obj) || dynamic_cast<GiftedPoint*>(obj))
			listStaticObjectsToRender.push_back(obj);
		else if (dynamic_cast<Shooter*>(obj) || dynamic_cast<Rocketer*>(obj) ||
			dynamic_cast<Bullet*>(obj) || dynamic_cast<Rocket*>(obj) || 
			dynamic_cast<Wizard*>(obj) || dynamic_cast<Skyper*>(obj) ||
			dynamic_cast<MiniBoss*>(obj))
		{
			listMovingObjectsToRender.push_back(obj);
		}

		listObjects.push_back(obj);
	}
}

void SceneManager::UpdateCameraPosition()
{
	if (captain->x > SCREEN_WIDTH / 2
		&& captain->x + SCREEN_WIDTH / 2 < tilemaps->Get(IDScene)->GetMapWidth())
	{
		//game->SetCameraPosition(captain->x - SCREEN_WIDTH / 2, 0);
		TileMap * map = tilemaps->Get(IDScene);
		int min_col = map->min_max_col_to_draw[map->index][0];
		int max_col = map->min_max_col_to_draw[map->index][1];

		if (captain->x >= min_col * 16 + (SCREEN_WIDTH / 2 - 8) &&
			captain->x <= max_col * 16 - (SCREEN_WIDTH / 2 - 8))
		{
			game->SetCameraPositionX(captain->x - SCREEN_WIDTH / 2);
		}
	}
	if (captain->y > 300 || captain->y <= 50)
	{
		game->SetCameraPositionY(captain->y - 208);
	}
}

void SceneManager::UpdateGrid()
{
	for (int i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i]->GetObj();

		if (obj->IsEnable() == false)
			continue;
		float newPos_x, newPos_y;
		listUnits[i]->GetObj()->GetPosition(newPos_x, newPos_y);
		listUnits[i]->Move(newPos_x, newPos_y);
	}
}

void SceneManager::SetDropItems(LPGAMEOBJECT object)
{
	if (dynamic_cast<GiftedPoint*>(object) && object->GetState() == 1)
	{
		if (object->idItem != -1 && object->IsDroppedItem() == false)
		{
			object->SetIsDroppedItem(true);

			items = new Items();
			items->SetEnable(true);
			items->SetPosition(object->x, object->y);
			items->SetItem(object->idItem);

			listItems.push_back(items);
			unit = new Unit(grid, items, object->x, object->y);
		}
	}
}

void SceneManager::Update(DWORD dt)
{
	float pos_x, pos_y;
	captain->GetPosition(pos_x, pos_y);

	if (IDScene == STAGE_1 && pos_x >= 1955.0f)
	{
		ChangeScene(STAGE_1_BOSS);
		game->SetCameraPosition(0.0f, 0.0f);
		return;
	}
	else if (IDScene == STAGE_1_BOSS && pos_x >= 400.0f)
	{
		ChangeScene(STAGE_2);
		game->SetCameraPosition(0.0f, 0.0f);
		return;
	}
	else if (IDScene == STAGE_2 && pos_x >= 900.0f)
	{
		ChangeScene(STAGE_2_BOSS);
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

		SetDropItems(object);
		
		if (dynamic_cast<Shooter*>(object))
		{
			Shooter_Update(dt, object);
		}
		else if (dynamic_cast<Rocketer*>(object))
		{
			Rocketer_Update(dt, object);
		}
		else if (dynamic_cast<Skyper*>(object))
		{
			//Skyper_Update(dt, object);
		}
		else if (dynamic_cast<Wizard*>(object))
		{
			Wizard_Update(dt, object);
		}
		else if (dynamic_cast<MiniBoss*>(object))
		{
			//MiniBoss_Update(dt, object);
		}
		else
		{
			object->Update(dt, &listObjects);
		}
	}
	// ra khỏi màn hình là bị xóa
	StopedByPosition();
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
		//obj->RenderBoundingBox();
	}

	for (auto obj : listMovingObjectsToRender)
	{
		obj->Render();
		obj->RenderBoundingBox();
		//obj->RenderActiveBoundingBox();
	}

	captain->Render();
	//captain->RenderBoundingBox();

	if (shield->IsEnable() == true)
	{
		shield->Render();
		//shield->RenderBoundingBox();
	}
}

void SceneManager::ChangeScene(int scene)
{
	IDScene = scene;

	switch (IDScene)
	{
	case STAGE_1:
		grid = new Grid(2048, 606, DEFAULT_CELL_WIDTH, DEFAULT_CELL_HEIGHT);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case STAGE_1_BOSS:
		grid = new Grid(526, 600, 128, 120);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_1_BOSS);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case STAGE_2:
		grid = new Grid(1024, 970, 128, 120);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	case STAGE_2_BOSS:
		grid = new Grid(512, 500, 128, 120);
		LoadObjectsFromFile(FILEPATH_OBJECTS_SCENE_2_BOSS);
		captain->SetPosition(0.0f, 100.0f);
		game->SetCameraPosition(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void SceneManager::StopedByPosition()
{
	D3DXVECTOR2 entryViewPort = game->GetCameraPositon();

	for (auto object : listObjects)
	{
		float x, y;
		object->GetPosition(x, y);

		//if (x < entryViewPort.x ||  x > entryViewPort.x + SCREEN_WIDTH - 1)
		if (x < entryViewPort.x ||  x > entryViewPort.x + SCREEN_WIDTH - 1)
		{
			if ((dynamic_cast<Shooter*>(object) || dynamic_cast<Rocketer*>(object)) 
				&& object->GetState() == ENEMY_RUN)
			{
				object->SetState(ENEMY_STOP);
			}
			else if (dynamic_cast<Bullet*>(object) || dynamic_cast<Rocket*>(object))
			{
				object->SetEnable(false);
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
			dynamic_cast<Bullet*>(obj) || dynamic_cast<Rocketer*>(obj) ||
			dynamic_cast<Skyper*>(obj) || dynamic_cast<Items*>(obj) ||
			dynamic_cast<Wizard*>(obj) || dynamic_cast<MiniBoss*>(obj)) &&
			obj->GetState() != ENEMY_STOP && obj->IsEnable() == true)
		{
			coObjects.push_back(obj);
		}
	}

	captain->Update(dt, &coObjects);
	captain->CheckCollisionWithEnemyActiveArea(&listMovingObjectsToRender);
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
		if ((dynamic_cast<Shooter*>(obj) || dynamic_cast<Rocketer*>(obj) ||
			dynamic_cast<GiftedPoint*>(obj)) && obj->IsEnable() == true)
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
	vector<LPGAMEOBJECT> coObjects;

	// Quay hướng captain
	float cx, cy;
	captain->GetPosition(cx, cy);
	float sx, sy;
	shooter->GetPosition(sx, sy);

	if (sx < cx) shooter->SetNx(1);
	else shooter->SetNx(-1);

	if ((shooter->GetState() == ENEMY_RUN || shooter->GetState() == ENEMY_SIT) &&
		GetTickCount() - shooter->GetLastTimeShoot() >= shooter->GetDeltaTimeToShoot())
	{
		shooter->SetState(ENEMY_SHOOT);

		// Bắn đạn
		bullet = new Bullet();
		bullet->SetPosition(sx + 5.0f, sy + 10.0f);
		bullet->SetOrientation(shooter->nx);
		bullet->SetState(BULLET);
		bullet->SetEnable(true);

		unit = new Unit(grid, bullet, sx + 5.0f, sy + 10.0f);
	}
	else
	{
		coObjects.clear();
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
	vector<LPGAMEOBJECT> coObjects;

	// Quay hướng captain
	float cx, cy;
	captain->GetPosition(cx, cy);
	float rx, ry;
	rocketer->GetPosition(rx, ry);

	if (rx < cx) rocketer->SetNx(1);
	else rocketer->SetNx(-1);

	if ((rocketer->GetState() == ENEMY_RUN || rocketer->GetState() == ENEMY_SIT) &&
		GetTickCount() - rocketer->GetLastTimeShoot() >= rocketer->GetDeltaTimeToShoot())
	{
		rocketer->SetState(ENEMY_SHOOT);
		
		/*
		// Bắn đạn
		rocket = new Rocket();
		rocket->SetPosition(rx + 5.0f, ry + 10.0f);
		rocket->SetOrientation(nx);
		rocket->SetState(BULLET);
		rocket->SetEnable(true);

		unit = new Unit(grid, rocket, rx + 5.0f, ry + 10.0f);*/
	}
	else
	{
		coObjects.clear();
		for (auto obj : listObjects)
		{
			if (dynamic_cast<Ground*>(obj))
			{
				coObjects.push_back(obj);
			}
		}

	}
	rocketer->Update(dt, &coObjects);
}

void SceneManager::Wizard_Update(DWORD dt, LPGAMEOBJECT& object)
{
	if (object->GetState() == ENEMY_STOP)
		return;

	wizard = dynamic_cast<Wizard*>(object);

	float sx, sy;
	captain->GetPosition(sx, sy);
	wizard->SetSimonPosition(sx, sy);
	wizard->SetOrientation(-captain->nx);
	wizard->Update(dt);
}

void SceneManager::MiniBoss_Update(DWORD dt, LPGAMEOBJECT& object)
{
	if (object->GetState() == ENEMY_STOP)
		return;

	miniboss = dynamic_cast<MiniBoss*>(object);

	float sx, sy;
	captain->GetPosition(sx, sy);
	miniboss->SetSimonPosition(sx, sy);
	miniboss->SetOrientation(-captain->nx);
	miniboss->Update(dt);
}