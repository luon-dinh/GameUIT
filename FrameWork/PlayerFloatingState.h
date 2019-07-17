#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerFloatingState : public PlayerState {
public:
	BoundingBox getBoundingBox();
	PlayerFloatingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};