#pragma once
#include "PlayerState.h"
#include"Player.h"

class PlayerShieldDownState : public PlayerState
{
public:
	BoundingBox getBoundingBox();
	void InputHandler();
	void Downdate(float dt);
	void OnCollision(Object* object, collisionOut* collision);
	PlayerShieldDownState();
	~PlayerShieldDownState();
};

