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

	const int DELAY_CHANGE_DIRECTION_TIME = 8;
	int curDelayTime;
	
public:
	PlayerJumpingState() { state = State::JUMPING; this->curDelayTime = 0; }
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};