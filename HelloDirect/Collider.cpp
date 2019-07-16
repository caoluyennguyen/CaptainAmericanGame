#include "Collider.h"
#include "Game.h"

Collider::Collider(float Width, float Height)
{
	width = Width;
	height = Height;
}

void Collider::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}

