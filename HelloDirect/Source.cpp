﻿#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Define.h"
 
#include "Debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Input.h"
#include "SceneManager.h"
#include "TileMap.h"
#include "Grid.h"
#include "GameInfo.h"

Game* game;
Input* input;
SceneManager* scenes;
GameInfo* gameInfo;

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

		scenes->Render();
		gameInfo->Render();

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

//void GetObjectFromGrid()
//{
//	listUnits.clear();
//	listObjects.clear();
//	listStaticObjectsToRender.clear();
//	listMovingObjectsToRender.clear();
//
//	grid->Get(game->GetCameraPositon(), listUnits);
//
//	DebugOut(L"%d \n", listUnits.size());
//
//	for (int i = 0; i < listUnits.size(); i++)
//	{
//		LPGAMEOBJECT obj = listUnits[i]->GetObj();
//
//		if (dynamic_cast<Enemy*>(obj))
//			listStaticObjectsToRender.push_back(obj);
//
//		listObjects.push_back(obj);
//	}
//}
//
//void UpdateGrid()
//{
//	for (int i = 0; i < listUnits.size(); i++)
//	{
//		float newPos_x, newPos_y;
//		listUnits[i]->GetObj()->GetPosition(newPos_x, newPos_y);
//		listUnits[i]->Move(newPos_x, newPos_y);
//	}
//}

void Update(DWORD dt)
{
	scenes->Update(dt);
	gameInfo->Update(dt, false);
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

	game = Game::GetInstance();
	game->Init(hWnd);

	scenes = new SceneManager(game, STAGE_1);
	scenes->LoadResources();
	scenes->ChangeScene(STAGE_1);

	input = new Input(game, scenes);
	game->InitKeyboard(input);

	gameInfo = new GameInfo(scenes, game);
	gameInfo->Init();

	Run();

	return 0;
}