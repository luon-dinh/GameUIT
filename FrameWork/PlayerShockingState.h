#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"

class PlayerShockingState : public PlayerState {
private:
	const int SHOCKING_FRAME = 30;
	int curShockFrame;
public:
	PlayerShockingState();
	~PlayerShockingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};