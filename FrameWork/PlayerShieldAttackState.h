#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerShieldAttackState : public PlayerState {
private:
	int countFrame;
public:
	PlayerShieldAttackState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;


	const int MAX_FRAME_PREPARE_ATTACK = 15;
};