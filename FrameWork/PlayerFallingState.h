#pragma once
#include "PlayerState.h"
#include"Player.h"
class PlayerFallingState :
	public PlayerState
{
public:
	void InputHandler();
	void Update(float dt);
	void OnCollision(Object* object, collisionOut* collision);
	PlayerFallingState();
	~PlayerFallingState();
};

