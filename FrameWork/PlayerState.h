#pragma once
#include"Collision.h"
#include"Object.h"
#include "Global.h"

class PlayerState {
protected:
public:
	State state;
	PlayerState() {};
	virtual void InputHandler() {};
	virtual void Update(float dt) {};
	virtual void OnCollision(Object* object, collisionOut* collision) {};

};
