#pragma once
#include"PlayerState.h"
#include"Player.h"

class PlayerStandingState: public PlayerState {
public:
	PlayerStandingState();
	~PlayerStandingState() {};
	void Update(float dt) ;
	void OnCollision(Object* object, collisionOut* collision);
	void InputHandler();
	BoundingBox getBoundingBox();
};
