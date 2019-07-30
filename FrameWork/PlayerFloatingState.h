#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Global.h"


class PlayerFloatingState : public PlayerState {
private:
	bool isDropToWater;
	int curTimeDrop;
	const int MAX_TIME_DROP = 300;			//	 miliseconds
	int countAnimationFrame;
public:
	BoundingBox getBoundingBox();
	PlayerFloatingState();
	~PlayerFloatingState();
	void InputHandler() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* collision) override;
};