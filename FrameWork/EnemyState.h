#pragma once
#include "Enemy.h"


class EnemyState {
protected:
	enum StateName {
		Duck,
		Stand,
		Attack,
		Beaten,
		Run
	};

	StateName state;
public:
	EnemyState(StateName state);
	~EnemyState();


	virtual StateName GetState();
	virtual void SetState(StateName state);

	virtual void Update(float dt)								   = 0;
	virtual void OnCollision(Object* object, collisionOut* colOut) = 0;
	virtual void AutoProcess()									   = 0;
};