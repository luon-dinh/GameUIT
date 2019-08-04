#pragma once
#include "PlayerState.h"
#include"Player.h"

class PlayerShieldDownState : public PlayerState
{
private:
	bool isPushDown;

	int curPushFrameCount;
	const int PUSH_FRAME = 10;
public:
	void InputHandler();
	void Update(float dt);
	void OnCollision(Object* object, collisionOut* collision);
	PlayerShieldDownState();
	~PlayerShieldDownState();
};

