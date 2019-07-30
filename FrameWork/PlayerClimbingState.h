#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerClimbingState : public PlayerState {
private:
	const int FRAME_PER_ANIMATION = 35;
	const int NUMBER_OF_ANIMATION = 3;
	int currentFrame;
public:
	PlayerClimbingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};