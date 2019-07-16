#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"

class PlayerSittingState : public PlayerState {
public:
	PlayerSittingState();
	~PlayerSittingState();

	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};