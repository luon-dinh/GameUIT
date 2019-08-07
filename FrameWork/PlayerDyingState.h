#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDyingState : public PlayerState {
private:
	const int ANIMATION_FRAME = 60;
	int currentFrame;
public:
	PlayerDyingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};