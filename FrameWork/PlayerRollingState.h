#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerRollingState : public PlayerState {
private:

	int curRollTime;
public:
	PlayerRollingState();
	~PlayerRollingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
	
	
	const int MAX_ROLLING_TIME = 400; // thời gian rolling time tối đa
};