#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerRollingState : public PlayerState {
private:

public:
	PlayerRollingState();
	~PlayerRollingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
	BoundingBox getBoundingBox() { return BoundingBox(); };
	
	BOOL HasRollFullTime();
	const int MAX_ROLLING_TIME = 400; // thời gian rolling time tối đa
	static int curRollTime;
};