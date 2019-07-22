#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerStandPunchState : public PlayerState {
private:
public:
	BoundingBox getBoundingBox();
	PlayerStandPunchState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;

	const int MAX_PUNCH_TIME = 300;
};