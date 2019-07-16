
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Megaman.h"
#include "Camera.h"
#include "Background.h"
#include "Box.h"
#include "Collider.h"

#define WINDOW_CLASS_NAME L"HelloDirect"
#define MAIN_WINDOW_TITLE L"CaptainAmerican"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define MAX_FRAME_RATE 120

#define ID_TEX_MEGAMAN 0
#define ID_TEX_MEGAMAN2 1
#define ID_TEX_BACKGROUND 100
//#define ID_TEX_MISC 20


CGame *game;
CMegaman *megaman;
Camera *camera;
Background *background;

vector<LPGAMEOBJECT> objects;
void Game_End(HWND);

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_X:     
		megaman->SetState(MEGAMAN_STATE_JUMP);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_RIGHT))
		megaman->SetState(MEGAMAN_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		megaman->SetState(MEGAMAN_STATE_WALKING_LEFT);
	else megaman->SetState(MEGAMAN_STATE_IDLE);
	if (game->IsKeyDown(DIK_UP)) megaman->SetState(MEGAMAN_STATE_FIGHT);

	else if (game->IsKeyDown(DIK_Z)) megaman->SetState(MEGAMAN_STATE_SWIFT);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		Game_End(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	camera = new Camera(1080, 720, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MEGAMAN, L"megaman.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_MEGAMAN2, L"Cap.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_MISC, L"misc.png", D3DCOLOR_XRGB(176, 224, 248));
	//textures->Add(ID_TEX_BACKGROUND, L"background.png", D3DCOLOR_XRGB(255, 255, 255));

	CSprites * sprites = CSprites::GetInstance();

	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMega = textures->Get(ID_TEX_MEGAMAN);
	LPDIRECT3DTEXTURE9 texMega2 = textures->Get(ID_TEX_MEGAMAN2);

	//LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	//LPDIRECT3DTEXTURE9 texBack = textures->Get(ID_TEX_BACKGROUND);

#pragma region idle left
	/*sprites->Add(10001, 185*3, 16*3, 215*3, 51*3, texMega2);
	sprites->Add(10002, 151*3, 16*3, 181*3, 51*3, texMega2);
	sprites->Add(10003, 117*3, 16*3, 147*3, 51*3, texMega2);*/
	sprites->Add(10001, 20*3, 14*3, 42*3, 59*3, texMega2);
#pragma endregion

#pragma region move left
	/*sprites->Add(10004, 381 * 3, 106 * 3, 401 * 3, 141 * 3, texMega2);
	sprites->Add(10005, 357 * 3, 106 * 3, 379 * 3, 141 * 3, texMega2);
	sprites->Add(10006, 325 * 3, 106 * 3, 356 * 3, 141 * 3, texMega2);
	sprites->Add(10007, 292 * 3, 106 * 3, 325 * 3, 141 * 3, texMega2);
	sprites->Add(10008, 264 * 3, 106 * 3, 290 * 3, 141 * 3, texMega2);
	sprites->Add(10009, 240 * 3, 106 * 3, 263 * 3, 141 * 3, texMega2);
	sprites->Add(10010, 215 * 3, 107 * 3, 239 * 3, 141 * 3, texMega2);
	sprites->Add(10011, 183 * 3, 106 * 3, 213 * 3, 141 * 3, texMega2);
	sprites->Add(10012, 147 * 3, 106 * 3, 181 * 3, 141 * 3, texMega2);
	sprites->Add(10013, 118 * 3, 106 * 3, 146 * 3, 141 * 3, texMega2);*/
	sprites->Add(10002, 51*3, 17*3, 75*3, 59*3, texMega2);
	sprites->Add(10003, 83*3, 16*3, 107*3, 59*3, texMega2);
	sprites->Add(10004, 115*3, 17*3, 139*3, 59*3, texMega2);
	sprites->Add(10005, 147*3, 16*3, 171*3, 59*3, texMega2);
#pragma endregion

#pragma region idle right
	sprites->Add(10014, 324*3, 16*3, 353*3, 51*3, texMega);
	sprites->Add(10015, 358*3, 16*3, 387*3, 51*3, texMega);
	sprites->Add(10016, 392*3, 16*3, 421*3, 51*3, texMega);
#pragma endregion

#pragma region move right
	sprites->Add(10017, 106 * 3, 106 * 3, 136 * 3, 141 * 3, texMega);
	sprites->Add(10018, 136 * 3, 106 * 3, 157 * 3, 141 * 3, texMega);
	sprites->Add(10019, 158 * 3, 106 * 3, 180 * 3, 141 * 3, texMega);
	sprites->Add(10020, 182 * 3, 106 * 3, 213 * 3, 141 * 3, texMega);
	sprites->Add(10021, 214 * 3, 108 * 3, 247 * 3, 141 * 3, texMega);
	sprites->Add(10022, 247 * 3, 108 * 3, 275 * 3, 141 * 3, texMega);
	sprites->Add(10023, 276 * 3, 107 * 3, 298 * 3, 141 * 3, texMega);
	sprites->Add(10024, 299 * 3, 106 * 3, 324 * 3, 141 * 3, texMega);
	sprites->Add(10025, 326 * 3, 106 * 3, 355 * 3, 141 * 3, texMega);
	sprites->Add(10026, 358 * 3, 106 * 3, 390 * 3, 141 * 3, texMega);
	sprites->Add(10027, 391 * 3, 106 * 3, 421 * 3, 141 * 3, texMega);
#pragma endregion

#pragma region jump left
	/*sprites->Add(10028, 311 * 3, 53 * 3, 335 * 3, 100 * 3, texMega2);
	sprites->Add(10029, 290 * 3, 53 * 3, 307 * 3, 100 * 3, texMega2);
	sprites->Add(10030, 265 * 3, 53 * 3, 285 * 3, 100 * 3, texMega2);
	sprites->Add(10031, 240 * 3, 53 * 3, 263 * 3, 100 * 3, texMega2);
	sprites->Add(10032, 211 * 3, 53 * 3, 238 * 3, 100 * 3, texMega2);
	sprites->Add(10033, 182 * 3, 53 * 3, 207 * 3, 100 * 3, texMega2);
	sprites->Add(10034, 151 * 3, 53 * 3, 181 * 3, 100 * 3, texMega2);*/
	sprites->Add(10028, 275*3, 31*3, 293*3, 51*3, texMega2);
	sprites->Add(10029, 311*3, 33*3, 331*3, 51*3, texMega2);
#pragma endregion

#pragma region jump right
	sprites->Add(10035, 202 * 3, 53 * 3, 226 * 3, 100 * 3, texMega);
	sprites->Add(10036, 229 * 3, 53 * 3, 246 * 3, 100 * 3, texMega);
	sprites->Add(10037, 250 * 3, 53 * 3, 271 * 3, 100 * 3, texMega);
	sprites->Add(10038, 273 * 3, 53 * 3, 296 * 3, 100 * 3, texMega);
	sprites->Add(10039, 297 * 3, 53 * 3, 325 * 3, 100 * 3, texMega);
	sprites->Add(10040, 330 * 3, 53 * 3, 354 * 3, 100 * 3, texMega);
	sprites->Add(10041, 356 * 3, 53 * 3, 385 * 3, 100 * 3, texMega);
#pragma endregion

#pragma region fight
	sprites->Add(10042, 86 * 3, 233 * 3, 119 * 3, 268 * 3, texMega);
	sprites->Add(10043, 127 * 3, 233 * 3, 160 * 3, 268 * 3, texMega);
	sprites->Add(10044, 164 * 3, 233 * 3, 200 * 3, 268 * 3, texMega);
	sprites->Add(10045, 203 * 3, 233 * 3, 240 * 3, 268 * 3, texMega);
	sprites->Add(10046, 244 * 3, 233 * 3, 275 * 3, 268 * 3, texMega);
	sprites->Add(10047, 282 * 3, 233 * 3, 313 * 3, 268 * 3, texMega);
	sprites->Add(10048, 317 * 3, 233 * 3, 347 * 3, 268 * 3, texMega);
	sprites->Add(10049, 355 * 3, 233 * 3, 391 * 3, 268 * 3, texMega);
	sprites->Add(10050, 395 * 3, 233 * 3, 434 * 3, 268 * 3, texMega);
#pragma endregion

#pragma region swift
	//sprites->Add(10051, 284 * 3, 157 * 3, 312 * 3, 190 * 3, texMega);
	sprites->Add(10052, 316 * 3, 157 * 3, 355 * 3, 190 * 3, texMega);
#pragma endregion

	//box
	//sprites->Add(20001, 408*3, 225*3, 424*3, 241*3, texMisc);
	//background
	//sprites->Add(20002, 0*3, 0*3, 1000*3, 1000*3, texBack);

#pragma region CREATING ANIMATION
	LPANIMATION ani;

	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(901, ani);

	ani = new CAnimation(100); //idle right
	ani->Add(10014);
	ani->Add(10015);
	ani->Add(10016);
	animations->Add(400, ani);

	ani = new CAnimation(100); //idle left
	ani->Add(10001);
	//ani->Add(10002);
	//ani->Add(10003);
	animations->Add(401, ani);

	ani = new CAnimation(100); //move right
	ani->Add(10017);
	ani->Add(10018);
	ani->Add(10019);
	ani->Add(10020);
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	ani->Add(10024);
	ani->Add(10025);
	ani->Add(10026);
	ani->Add(10027);
	animations->Add(500, ani);

	ani = new CAnimation(100); //move left
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	/*ani->Add(10006);
	ani->Add(10007);
	ani->Add(10008);
	ani->Add(10009);
	ani->Add(10010);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);*/
	animations->Add(501, ani);

	ani = new CAnimation(100); //jump left
	ani->Add(10028);
	ani->Add(10029);
	/*ani->Add(10030);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	ani->Add(10034);*/
	animations->Add(601, ani);

	ani = new CAnimation(100); //jump right
	ani->Add(10035);
	ani->Add(10036);
	ani->Add(10037);
	ani->Add(10038);
	ani->Add(10039);
	ani->Add(10040);
	ani->Add(10041);
	animations->Add(600, ani);

	ani = new CAnimation(30); //fight 
	ani->Add(10042);
	ani->Add(10043);
	ani->Add(10044);
	ani->Add(10045);
	ani->Add(10046);
	ani->Add(10047);
	ani->Add(10048);
	ani->Add(10049);
	ani->Add(10050);
	animations->Add(700, ani);

	ani = new CAnimation(100); //swift
	//ani->Add(10051);
	ani->Add(10052);
	animations->Add(800, ani);
#pragma endregion

	megaman = new CMegaman();
	megaman->AddAnimation(400);		// idle right
	megaman->AddAnimation(401);		// idle left
	megaman->AddAnimation(500);		// move right
	megaman->AddAnimation(501);		// move left
	megaman->AddAnimation(600);		// jump right
	megaman->AddAnimation(601);		// jump left
	megaman->AddAnimation(700);		// fight
	megaman->AddAnimation(800);		// swift

	megaman->SetPosition(90.0f, 0.0f);

	////ani = new CAnimation(0); //background
	////ani->Add(20002);
	////animations->Add(902, ani);

	background = new Background(0, 0, 1024*2, 875*2);
	background->Add(L"CaptainAmericaAndTheAvengers-Stage1.png", D3DCOLOR_XRGB(255, 255, 255));

	//background = new Background();
	//background->AddAnimation(902);

	background->SetPosition(0.0f, 0.0f);

#pragma region CREATING COLLIDER
	Collider *collider = new Collider(48, 48);
	collider->SetPosition(400.0f + 48.0f, 900.0f);
	objects.push_back(collider);

	Collider *collider1 = new Collider(134, 120);
	collider1->SetPosition(0, 866);
	objects.push_back(collider1);

	Collider *collider2 = new Collider(190, 90);
	collider2->SetPosition(135, 772);
	objects.push_back(collider2);

	Collider *collider3 = new Collider(130, 90);
	collider3->SetPosition(320, 828);
	objects.push_back(collider3);

	Collider *collider4 = new Collider(900, 70);
	collider4->SetPosition(450, 896);
	objects.push_back(collider4);

	Collider *collider5 = new Collider(446, 320);
	collider5->SetPosition(744, 390);
	objects.push_back(collider5);

	Collider *collider6 = new Collider(574, 510);
	collider6->SetPosition(0, 66);
	objects.push_back(collider6);

	Collider *collider7 = new Collider(94, 66);
	collider7->SetPosition(490, 576);
	objects.push_back(collider7);

	Collider *collider8 = new Collider(40, 340);
	collider8->SetPosition(966, 60);
	objects.push_back(collider8);
#pragma endregion
	
	objects.push_back(background);
	objects.push_back(megaman);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	if (camera)
	{
		if (!camera->IsFollowing())
		{
			camera->Follow(megaman);
		}

		camera->Update();
	}
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
}

/*
	Render a frame
*/

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (camera)
		{
			camera->SetTransform(d3ddv);
		}

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
	

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
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

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);  

	LoadResources();
	Run();

	return 0;
}

void Game_End(HWND hWnd)
{
	delete background;
	delete megaman; 
	delete camera;
	delete game;
}