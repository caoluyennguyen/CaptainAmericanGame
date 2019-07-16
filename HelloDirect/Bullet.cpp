//#include "Bullet.h"
//#include "Game.h"
//
//Bullet::Bullet(int Left, int Top, int Right, int Bottom)
//{
//	left = Left;
//	top = Top;
//	right = Right;
//	bottom = Bottom;
//	vx = 3.0f;
//}
//
//void Bullet::Add(LPCWSTR filePath, D3DCOLOR transparentColor)
//{
//	D3DXIMAGE_INFO info;
//	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
//	if (result != D3D_OK)
//	{
//		return;
//	}
//
//	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
//	LPDIRECT3DTEXTURE9 texture;
//
//	result = D3DXCreateTextureFromFileEx(
//		d3ddv,								// Pointer to Direct3D device object
//		filePath,							// Path to the image to load
//		info.Width * 2,							// Texture width
//		info.Height * 2,						// Texture height
//		1,
//		D3DUSAGE_DYNAMIC,
//		D3DFMT_UNKNOWN,
//		D3DPOOL_DEFAULT,
//		D3DX_DEFAULT,
//		D3DX_DEFAULT,
//		transparentColor,
//		&info,
//		NULL,
//		&texture);								// Created texture pointer
//
//	if (result != D3D_OK)
//	{
//		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
//		return;
//	}
//
//	tex = texture;
//
//}
//
//void Bullet::Render()
//{
//	CGame * game = CGame::GetInstance();
//	game->Draw(x, y, tex, left, top, right, bottom);
//}