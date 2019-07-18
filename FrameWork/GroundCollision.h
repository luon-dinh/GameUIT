#pragma once
#include "Object.h"

class GroundCollision {
private:
	Object* ground;
	CollisionSide side;

public:
	GroundCollision();
	GroundCollision(Object* ground, CollisionSide side);
	~GroundCollision();
	
	Object* GetGround();
	CollisionSide GetCollisionSide();
	void SetGround(Object* ground);
	void SetCollisionSide(CollisionSide side);
};