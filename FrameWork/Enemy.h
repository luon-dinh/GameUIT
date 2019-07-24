#pragma once
#include "Object.h"
#include"Player.h"


class Enemy : public Object {
protected:
	
public:
	Enemy();
	~Enemy();
	float speed;
	bool isDead;
	Player::MoveDirection direction;
	Animation* curentAnimation;
	virtual void Shoot() {};
	virtual void OnCollision(Object* object, collisionOut* colOut) {};
	virtual void Update(float dt);
	virtual void ChangeState(State stateName) {};
	virtual void Render();
	virtual void Respawn();
};