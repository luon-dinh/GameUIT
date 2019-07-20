#pragma once
#include<Windows.h>

enum CollisionSide {
	none,
	top,
	left,
	right,
	bottom
};
struct collisionOut {
	float collisionTime;
	CollisionSide side;
};

struct BoundingBox {
	float top, left, right, bottom;
	int vx, vy;
	BoundingBox(float top_, float left_, float bottom_, float right_, int vx_, int vy_)
	{
		top = top_;
		left = left_;
		bottom=bottom_;
		right = right_;
		vx = vx_;
		vy = vy_;
	}
	BoundingBox() {};
	~BoundingBox() {};
};

struct Rect
{
	float x, y;
	float width, height;

	Rect() {}
	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	bool IsContain(Rect r)
	{
		return !((x + width < r.x) || (x > r.x + r.width) || (y < r.y - r.height) || (y - height > r.y));
	}
};

class Collision
{
private:
	float dxEntry, dyEntry, dxExit, dyExit;
	float txEntry, tyEntry, txExit, tyExit;
	float entryTime, exitTime;

	static Collision *instance;
public:
	static Collision * getInstance();
	collisionOut SweptAABB(BoundingBox recta, BoundingBox rectb);
	collisionOut SweptAABB(BoundingBox recta, BoundingBox rectb, float acceleratorA);
	bool IsCollide(BoundingBox box1, BoundingBox box2);
};

