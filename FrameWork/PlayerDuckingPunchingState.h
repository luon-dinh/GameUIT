#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDuckingPunchingState : public PlayerState {
public:
	BoundingBox getBoundingBox();
	PlayerDuckingPunchingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};