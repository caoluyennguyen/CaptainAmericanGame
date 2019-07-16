#pragma once
#include "GameObject.h"

class Collider : public CGameObject
{
private:
	float width;
	float height;
public:
	Collider(float Width, float Height);
	void Render() {};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};