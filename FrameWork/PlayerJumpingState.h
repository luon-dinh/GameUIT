#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerJumpingState : public PlayerState{
private:
	const int MIN_TIME_JUMP_1 = 150;
	const int MIN_TIME_JUMP_2 = 400;
	const int MIN_TIME_DASH = 1000;
	const float ADDED_SPEED = 0.2;
public:
	BoundingBox getBoundingBox();
	PlayerJumpingState() { state = State::JUMPING; }
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};