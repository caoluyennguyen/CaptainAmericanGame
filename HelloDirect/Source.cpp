#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Define.h"

#include "Debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Captain.h"
#include "Bullet.h"
#include "TileMap.h"
#include "Box.h"
#include "Grid.h"


Game* game;
Captain* captain;
Enemy* enemy;
TileMap* tilemap;
Ground* ground;
Unit* unit;
Grid* grid;
vector<Ground*> grounds;
//vector<LPGAMEOBJECT> coObjects;

vector<Unit*> listUnits;
vector<LPGAMEOBJECT> listObjects;

vector<LPGAMEOBJECT> listStaticObjectsToRender;
vector<LPGAMEOBJECT> listMovingObjectsToRender;

class KeyHandler : public KeyEventHandler
{
	virtual void KeyState(BYTE* state)
	{
		/*if (captain->GetState() == JUMP && captain->IsTouchGround() == false)
			return;*/

		if (game->IsKeyDown(DIK_RIGHT))
		{
			captain->nx = 1;
			captain->SetState(WALK);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			captain->nx = -1;
			captain->SetState(WALK);
		}
		else if (game->IsKeyDown(DIK_UP))
		{
			captain->SetState(SIT);
		}
		else
		{
			captain->SetState(STAND);
		}
	}

	virtual void OnKeyDown(int KeyCode)
	{
		DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

		switch (KeyCode)
		{
		case DIK_Z:
			captain->SetState(JUMP);
			break;
		default:
			break;
		}
	}

	virtual void OnKeyUp(int KeyCode)
	{
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	}
};

KeyHandler* keyHandler;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// clear back buffer with background color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		tilemap->Draw(game->GetCameraPositon());


		captain->Render();
		captain->RenderBoundingBox();

		/*for (int i = 0; i < coObjects.size(); i++)
			coObjects[i]->Render();*/
		for (auto obj : listStaticObjectsToRender)
		{
			obj->Render();
			obj->RenderBoundingBox();
		}

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

void GetObjectFromGrid()
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

void UpdateGrid()
{
	for (int i = 0; i < listUnits.size(); i++)
	{
		float newPos_x, newPos_y;
		listUnits[i]->GetObj()->GetPosition(newPos_x, newPos_y);
		listUnits[i]->Move(newPos_x, newPos_y);
	}
}

void Update(DWORD dt)
{
	GetObjectFromGrid();
	vector<LPGAMEOBJECT> coObjects;

	for (auto obj : listObjects)
	{
		if (dynamic_cast<Ground*>(obj))
		{
			coObjects.push_back(obj);
		}
	}

	captain->Update(dt, &coObjects);

	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEOBJECT object = listObjects[i];
		object->Update(dt, &listObjects);
	}

	// render camera
	float cx, cy;
	captain->GetPosition(cx, cy);

	if (cx > SCREEN_WIDTH / 2 && cx + SCREEN_WIDTH / 2 < tilemap->GetMapWidth())
		game->SetCameraPosition(cx - SCREEN_WIDTH / 2, 0);

	UpdateGrid();

}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	grid = new Grid(1536, 480, DEFAULT_CELL_WIDTH, DEFAULT_CELL_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);

	captain = new Captain();

	keyHandler = new KeyHandler();
	game->InitKeyboard(keyHandler);
	captain->LoadResources();

	enemy = new Enemy();
	enemy->LoadResources();
	enemy->SetPosition(160.0f, 200.0f);
	//coObjects.push_back(candle);
	unit = new Unit(grid, enemy, 160.0f, 200.0f);

	enemy = new Enemy();
	enemy->LoadResources();
	enemy->SetPosition(900.0f, 200.0f);
	//coObjects.push_back(candle);
	unit = new Unit(grid, enemy, 900.0f, 200.0f);

	tilemap = new TileMap(0, FILEPATH_TEX_STAGE_1, FILEPATH_DATA_STAGE_1, 2048, 288, 16, 16);
	tilemap->LoadResources();
	tilemap->Load_MapData();

	for (int i = 0; i < 48; i++)
	{
		ground = new Ground();
		ground->SetPosition(17 * i, 240.0f);
		grounds.push_back(ground);
		unit = new Unit(grid, ground, 17 * i, 240.0f);
	}

	/*for (int i = 0; i < grounds.size(); i++)
		coObjects.push_back(grounds[i]);*/

	Run();

	return 0;
}