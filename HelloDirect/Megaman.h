#pragma once
#include "GameObject.h"

#define MEGAMAN_WALKING_SPEED		0.3f
#define MEGAMAN_JUMP_SPEED_Y		1.0f
#define MEGAMAN_GRAVITY_X			-0.1f
#define MEGAMAN_GRAVITY_Y			0.005f
#define MEGAMAN_SWIFT_SPEED			0.4f

#define MEGAMAN_STATE_IDLE			0
#define MEGAMAN_STATE_WALKING_RIGHT	100
#define MEGAMAN_STATE_WALKING_LEFT	200
#define MEGAMAN_STATE_JUMP			300
#define MEGAMAN_STATE_FIGHT_LEFT	400
#define MEGAMAN_STATE_FIGHT_RIGHT	500
#define MEGAMAN_STATE_SWIFT_LEFT	600
#define MEGAMAN_STATE_SWIFT_RIGHT	700

#define MEGAMAN_ANI_IDLE_RIGHT			0
#define MEGAMAN_ANI_IDLE_LEFT			1
#define MEGAMAN_ANI_WALKING_RIGHT		2
#define MEGAMAN_ANI_WALKING_LEFT		3
#define MEGAMAN_ANI_JUMP_RIGHT			4
#define MEGAMAN_ANI_JUMP_LEFT			5
#define MEGAMAN_ANI_FIGHT				6
#define MEGAMAN_ANI_SWIFT				7

#define MEGAMAN_BBOX_WIDTH			90
#define MEGAMAN_BBOX_HEIGHT			105

class CMegaman : public CGameObject
{
private:
public:
	CMegaman() : CGameObject() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};