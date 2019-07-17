#pragma once
#include "PlayerState.h"
#include"Player.h"
class PlayerRunningState :
	public PlayerState
{
public:
	BoundingBox getBoundingBox();
	void InputHandler();
	void Update(float dt);
	void OnCollision(Object* object, collisionOut* collision);
	PlayerRunningState();
	~PlayerRunningState();
};

