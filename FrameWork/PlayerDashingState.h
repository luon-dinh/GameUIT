#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDashingState : public PlayerState {
private:
	int curDashTime;
public:
	BoundingBox getBoundingBox();
	PlayerDashingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;

	
	const int MAX_DASHING_TIME = 400;
};