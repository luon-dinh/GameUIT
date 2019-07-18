#pragma once
#include"PlayerState.h"
#include"Player.h"

class PlayerStandingState: public PlayerState {
public:
	PlayerStandingState();
	~PlayerStandingState() {};
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
	void InputHandler() override;
	BoundingBox getBoundingBox();
};
