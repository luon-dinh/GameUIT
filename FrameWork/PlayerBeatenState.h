#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerBeatenState : public PlayerState {
private:
	const int ANIMATION_FRAME = 10;
	int currentFrame;
public:
	PlayerBeatenState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};