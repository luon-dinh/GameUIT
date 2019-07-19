#pragma once
#include "PlayerState.h"
#include"Player.h"
class PlayerRunningState :
	public PlayerState
{
private:
	enum BeforeDash {
		DashLeft,
		DashRight,
		None
	};

	BeforeDash befDash;
	int timeFlip = 0;			// miliseconds

	int MAX_FLIP_TIME = 200;
public:
	BoundingBox getBoundingBox();
	void InputHandler();
	void Update(float dt);
	void OnCollision(Object* object, collisionOut* collision);
	BOOL ChangeToDash(BeforeDash currentDash);
	PlayerRunningState();
	~PlayerRunningState();
};

