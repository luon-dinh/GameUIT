#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerShieldAttackState : public PlayerState {
private:
	int countFrame;
public:
	Animation* animation1 = new Animation(Tag::PLAYER, 13, 14);
	Animation* animation2 = new Animation(Tag::PLAYER, 14, 15);
	PlayerShieldAttackState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;


	const int MAX_FRAME_PREPARE_ATTACK = 10;
};