#pragma once
#include "Object.h"

class SolidBoxCollision {
private:
	Object* solidBox;
	CollisionSide side;

public:
	SolidBoxCollision();
	SolidBoxCollision(Object* solidBox, CollisionSide side);
	~SolidBoxCollision();

	Object* GetSolidBox();
	CollisionSide GetCollisionSide();
	void SetSolidBox(Object* solidBox);
	void SetCollisionSide(CollisionSide side);
};