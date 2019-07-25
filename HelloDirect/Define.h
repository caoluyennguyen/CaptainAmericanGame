#pragma once

// main
#define WINDOW_CLASS_NAME		L"CaptainAmerican"
#define MAIN_WINDOW_TITLE		L"CaptainAmerican"

#define BACKGROUND_COLOR		D3DCOLOR_XRGB(255,255,255)
#define SCREEN_WIDTH			1000
#define SCREEN_HEIGHT			350

#define DEFAULT_CELL_WIDTH		256
#define DEFAULT_CELL_HEIGHT		240

#define MAX_FRAME_RATE			90

// Input
#define DIRECTINPUT_VERSION		0x0800
#define KEYBOARD_BUFFER_SIZE	1024


#pragma region Texture ID

#define ID_TEX_BBOX					-1
#define ID_TEX_STAGE_1				0
#define ID_TEX_CAPTAIN				1
#define ID_TEX_ENEMY				2
#define ID_TEX_GROUND				3

#pragma endregion


#pragma region PathFile

#define FILEPATH_TEX_GROUND			L"Textures\\ground.png"
#define FILEPATH_TEX_STAGE_1		L"Textures\\stage1.png"
#define FILEPATH_DATA_STAGE_1		L"Textures\\stage1_data.txt"
#define FILEPATH_TEX_CAP			L"Textures\\Cap.png"
#define FILEPATH_TEX_ENEMY			L"Textures\\Enemy.png"

#pragma endregion


#pragma region State

// Simon
#define STAND		0
#define WALK		1
#define SIT			2
#define JUMP		3
#define HIT_SIT		4
#define HIT_STAND	5
#define UP			6


#pragma endregion



#pragma region BBox Size


// Ground
#define GROUND_BBOX_WIDTH			16
#define GROUND_BBOX_HEIGHT			16

// Enemy
#define ENEMY_BBOX_WIDTH			30
#define ENEMY_BBOX_HEIGHT			38

//====================================
#define CAPTAIN_BBOX_WIDTH			22
#define CAPTAIN_BBOX_HEIGHT			45

#define CAPTAIN_WALKING_SPEED		0.1f
#define CAPTAIN_JUMP_SPEED_Y		0.5f
#define CAPTAIN_GRAVITY				0.03f

#pragma endregion




