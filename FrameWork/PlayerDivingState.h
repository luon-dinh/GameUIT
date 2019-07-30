#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDivingState : public PlayerState {
private:
	int countAnimationFrame;
public:
	BoundingBox getBoundingBox();
	PlayerDivingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;


	const int MAX_DASHING_TIME = 400;
};