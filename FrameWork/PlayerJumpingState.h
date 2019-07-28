#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerJumpingState : public PlayerState{
private:
	const int MIN_TIME_JUMP_1 = 20;
	const int MIN_TIME_JUMP_2 = 30;
	const int MIN_TIME_ROLL = 40;
	const float ADDED_SPEED_1 = 0.09;
	const float ADDED_SPEED_2 = 0.14;

	const int DELAY_CHANGE_DIRECTION_TIME = 8;
	int curDelayTime;
	
public:
	PlayerJumpingState() { state = State::JUMPING; this->curDelayTime = 0; }
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};