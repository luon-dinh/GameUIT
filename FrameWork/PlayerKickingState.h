#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerKickingState : public PlayerState {
private:

	int curKickTime;
public:
	PlayerKickingState();
	~PlayerKickingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;

	const int MAX_KICKING_TIME = 15;
};