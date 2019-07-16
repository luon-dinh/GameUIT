#include "Collision.h"
#include<iostream>
using namespace std;

Collision* Collision::instance = NULL;


Collision* Collision::getInstance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

collisionOut Collision::SweptAABB(BoundingBox recta, BoundingBox rectb)
{
	collisionOut out;
	out.collisionTime = 1;
	out.side = CollisionSide::none;
	if (recta.vx > 0.0f)
	{
		dxEntry = rectb.left - recta.right;
		dxExit = rectb.right - recta.left;
	}
	else
	{
		dxEntry = rectb.right - recta.left;
		dxExit = rectb.left - recta.right;
	}
	if (recta.vy > 0.0f)
	{
		dyEntry = rectb.top - recta.bottom;
		dyExit = rectb.bottom - recta.top;
	}
	else
	{
		dyEntry = rectb.bottom - recta.top;
		dyExit = rectb.top - recta.bottom;
	}

	if (recta.vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / recta.vx;
		txExit = dxExit / recta.vx;
	}
	if (recta.vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / recta.vy;
		tyExit = dyExit / recta.vy;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(tyExit, txExit);

	if ((entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f))
	{
		out.collisionTime = 1;
		return out;
	}

	out.collisionTime = entryTime;

	if (txEntry > tyEntry)
	{
		if (dxEntry > 0.0f)
		{
			out.side = CollisionSide::right;
		}
		else
		{
			out.side = CollisionSide::left;
		}

	}
	else
	{
		if (dyEntry > 0.0f)
		{
		}
		else
		{
			out.side = CollisionSide::bottom;
		}
	}
	return out;
}


bool Collision::IsCollide(BoundingBox box1, BoundingBox box2)
{
	return !(box1.left > box2.right || box1.right < box2.left || box1.top > box2.bottom || box1.bottom < box2.top);
}