﻿#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Textures.h"
#include "Sprites.h"
#include "Debug.h"

using namespace std;

class TileMap
{
	
	int map_Width;			// chiều rộng của map
	int map_Height;			// chiều cao của map

	int nums_row = 0;			// số hàng của map
	int nums_col = 0;			// số cột của map

	int tile_Width;			// chiều rộng một tile
	int tile_Height;		// chiều cao một tile

	LPCWSTR filePath_tex;
	LPCWSTR filePath_data;
	int ID;					// ID của tile map, dùng để tạo class quản lí TileMaps sau này ...

public:
	vector<vector<int>> map_Data;	// ma trận lưu dữ liệu map

	vector<vector<int>> min_max_col_to_draw;
	int index = 0; // index hiện tại của min_max_col_to_draw

	int start_col_to_draw;
	int end_col_to_draw;

	Sprites * sprites;	// lưu các tile

	TileMap() {}
	TileMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height);

	void LoadResources();	// load tất cả các block tile lưu vào sprites
	void Load_MapData();	// load ma trận dữ liệu map 
	void CreateZoneToDraw(); // khởi tạo vector 2 chiều min_max_col_to_draw
	void Draw(D3DXVECTOR3 camPosition);	// vẽ tất cả các tile nằm trong camera
	void Draw(int start_col, int end_col);

	int GetMapWidth() { return map_Width; }
};

typedef TileMap * LPTILEMAP;

class TileMaps
{
	static TileMaps * _instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int map_width, int map_height, int tile_width, int tile_height);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }

	static TileMaps * GetInstance();
};
