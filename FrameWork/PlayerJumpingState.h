#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerJumpingState : public PlayerState{
private:
	const int MIN_TIME_JUMP_1 = 10;
	const int MIN_TIME_JUMP_2 = 28;
	const int MIN_TIME_ROLL = 35;
	const float ADDED_SPEED_1 = 0.1;
	const float ADDED_SPEED_2 = 0.13;
public:
	BoundingBox getBoundingBox();
	PlayerJumpingState() { state = State::JUMPING; }
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};