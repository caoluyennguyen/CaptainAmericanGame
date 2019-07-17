#pragma once
#include "GameObject.h"

#define CAPTAIN_WALKING_SPEED		0.3f
#define CAPTAIN_JUMP_SPEED_Y		1.0f
#define CAPTAIN_GRAVITY_X			-0.1f
#define CAPTAIN_GRAVITY_Y			0.005f
#define CAPTAIN_SWIFT_SPEED			0.4f

#define CAPTAIN_STATE_IDLE			0
#define CAPTAIN_STATE_WALKING_RIGHT	100
#define CAPTAIN_STATE_WALKING_LEFT	200
#define CAPTAIN_STATE_JUMP			300
#define CAPTAIN_STATE_FIGHT			400
#define CAPTAIN_STATE_SWIFT_LEFT	500
#define CAPTAIN_STATE_SWIFT_RIGHT	600
#define CAPTAIN_STATE_SHIELD_RIGHT	700
#define CAPTAIN_STATE_SHIELD_LEFT	800

#define CAPTAIN_ANI_IDLE_RIGHT			0
#define CAPTAIN_ANI_IDLE_LEFT			1
#define CAPTAIN_ANI_WALKING_RIGHT		2
#define CAPTAIN_ANI_WALKING_LEFT		3
#define CAPTAIN_ANI_JUMP_RIGHT			4
#define CAPTAIN_ANI_JUMP_LEFT			5
#define CAPTAIN_ANI_FIGHT_RIGHT			6
#define CAPTAIN_ANI_SWIFT_RIGHT			7
#define CAPTAIN_ANI_FIGHT_LEFT			8
#define CAPTAIN_ANI_SWIFT_LEFT			9
#define CAPTAIN_ANI_SHIELD_UP_RIGHT		10
#define CAPTAIN_ANI_SHIELD_UP_LEFT		11


#define CAPTAIN_BBOX_WIDTH			90
#define CAPTAIN_BBOX_HEIGHT			105

class CCaptain : public CGameObject
{
private:
public:
	CCaptain() : CGameObject() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};