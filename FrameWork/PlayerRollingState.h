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
	
	BOOL HasRollFullTime();
	const int MAX_ROLLING_TIME = 25; // thời gian rolling time tối đa
	const int ADDED_SPEED = 0.2;

};