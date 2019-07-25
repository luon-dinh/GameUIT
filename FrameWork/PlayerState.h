#pragma once
#include"Collision.h"
#include"Object.h"
#include "Global.h"

class PlayerState {
protected:

	static bool detectCollision;
	
	static Object* object;
	static CollisionSide side;

public:
	State state;
	PlayerState() { this->detectCollision = false; };
	virtual void InputHandler() {};
	virtual void Update(float dt) {};
	virtual void OnCollision(Object* object, collisionOut* collision) {};
	virtual BoundingBox getBoundingBox() = 0;

	static bool GetCollisionResult();
	static void SetCollisionInfo(Object* object, CollisionSide side);
};
