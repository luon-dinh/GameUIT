#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerFlyingBeatenState : public PlayerState {
private:
	const int ANIMATION_FRAME = 8;
	int currentFrame;
public:
	PlayerFlyingBeatenState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};