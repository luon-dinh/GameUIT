#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerFloatingState : public PlayerState {
public:
	PlayerFloatingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};