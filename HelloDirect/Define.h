#pragma once

// main
#define WINDOW_CLASS_NAME		L"CaptainAmerican"
#define MAIN_WINDOW_TITLE		L"CaptainAmerican"

#define BACKGROUND_COLOR		D3DCOLOR_XRGB(255,255,255)
#define SCREEN_WIDTH			512
#define SCREEN_HEIGHT			320

#define DEFAULT_CELL_WIDTH		256
#define DEFAULT_CELL_HEIGHT		160

#define MAX_FRAME_RATE			90

// Input
#define DIRECTINPUT_VERSION		0x0800
#define KEYBOARD_BUFFER_SIZE	1024

#pragma region Properties

// Simon
#define CAPTAIN_UNTOUCHABLE_TIME		2000
#define CAPTAIN_WALKING_SPEED			0.13f
#define CAPTAIN_WALKING_SPEED_LOWER		0.05f
#define CAPTAIN_JUMP_SPEED_Y			0.5f
#define CAPTAIN_GRAVITY					0.002f
#define CAPTAIN_GRAVITY_LOWER			0.001f
#define CAPTAIN_DEFLECT_SPEED_X			0.13f
#define CAPTAIN_DEFLECT_SPEED_Y			0.3f
#pragma endregion


#pragma region Texture ID

#define ID_TEX_BBOX					-1
#define ID_TEX_BBOX_2				-2
#define ID_TEX_STAGE_1				0
#define ID_TEX_CAPTAIN				1
#define ID_TEX_CAPTAIN_SHIELD		2
#define ID_TEX_ENEMY				3
#define ID_TEX_GROUND				4
#define ID_TEX_SHIELD				5
#define ID_TEX_SHOOTER				6
#define ID_TEX_BULLET				7
#define ID_TEX_ROCKETER				8
#define ID_TEX_ROCKET				9

#pragma endregion


#pragma region PathFile

#define FILEPATH_TEX_STAGE_1		L"Textures\\stage1.png"
#define FILEPATH_DATA_STAGE_1		L"Textures\\stage1_data.txt"
#define FILEPATH_OBJECTS_SCENE_1	L"Textures\\stage1_objects.txt"

#define FILEPATH_TEX_STAGE_1_BOSS		L"Textures\\stage1-boss.png"
#define FILEPATH_DATA_STAGE_1_BOSS		L"Textures\\stage1-boss_data.txt"
#define FILEPATH_OBJECTS_SCENE_1_BOSS	L"Textures\\stage1-boss_objects.txt"

#define FILEPATH_TEX_GROUND			L"Textures\\ground.png"
#define FILEPATH_TEX_CAP			L"Textures\\Cap.png"
#define FILEPATH_TEX_CAP_SHIELD		L"Textures\\capnamerica.png"
#define FILEPATH_TEX_ENEMY			L"Textures\\Mini-Bosser.png"
#define FILEPATH_TEX_SMALL_ENEMY	L"Textures\\Enemies.png"

#pragma endregion


#pragma region State

// Scene
#define STAGE_1			0
#define STAGE_1_BOSS			1

// Simon
#define STAND			0
#define WALK			1
#define UP				2
#define JUMP			3
#define HIT_SIT			4
#define HIT_STAND		5
#define SIT				6
#define HIT_JUMP		7
#define SWIFT			8
#define	DEFLECT			9

// Enemy
#define ENEMY_ACTIVE	0
#define ENEMY_DESTROYED 1
#define ENEMY_SHOOT		2
#define ENEMY_INACTIVE	3

// Bullet
#define BULLET			0

#pragma endregion

#pragma region Animation ID

// Captain
#define STAND_ANI				101
#define WALK_ANI				102
#define UP_ANI					103
#define JUMP_ANI				104
#define HIT_SIT_ANI				105
#define HIT_STAND_ANI			106
#define SIT_ANI					107
#define HIT_JUMP_ANI			108
#define SWIFT_ANI				109
#define DEFLECT_ANI				110

#define STAND_SHIELD_ANI		111
#define WALK_SHIELD_ANI			112
#define UP_SHIELD_ANI			113
#define JUMP_SHIELD_ANI			114
#define HIT_SIT_SHIELD_ANI		115
#define HIT_STAND_SHIELD_ANI	116
#define SIT_SHIELD_ANI			117
#define HIT_JUMP_SHIELD_ANI		118
#define SWIFT_SHIELD_ANI		119

// Shield
#define SHIELD_ANI			201

// Enemy
#define ENEMY_ANI			301

// Ground
#define GROUND_ANI_1		401

// Shooter
#define SHOOTER_RUN_ANI			501
#define SHOOTER_SHOOT_ANI		502
#define SHOOTER_DEAD_ANI		503
#define SHOOTER_INACTIVE_ANI	504

// Rocketer
#define ROCKETER_RUN_ANI		601
#define ROCKETER_SHOOT_ANI		602
#define ROCKETER_DEAD_ANI		603
#define ROCKETER_INACTIVE_ANI	604

// Bullet
#define BULLET_ANI			701

// Rocket
#define ROCKET_ANI			801

#pragma endregion

#pragma region BBox Size


// Ground
#define GROUND_BBOX_WIDTH			16
#define GROUND_BBOX_HEIGHT			16

// Enemy
#define ENEMY_BBOX_WIDTH			30
#define ENEMY_BBOX_HEIGHT			38
#define ENEMY_ACTIVE_BBOX_WIDTH		200
#define ENEMY_ACTIVE_BBOX_HEIGHT	200

//====================================
#define CAPTAIN_BBOX_WIDTH			22
#define CAPTAIN_BBOX_HEIGHT			45

#define CAPTAIN_WALKING_SPEED		0.1f
#define CAPTAIN_JUMP_SPEED_Y		0.7f
#define CAPTAIN_GRAVITY				0.002f

#pragma endregion

#pragma region ID objects to load from file

#define	ENEMY		0
#define	GROUND		1
#define SHOOTER		2
#define ROCKETER	3

#pragma endregion



