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
	virtual void OnCollision(Object* object, collisionOut* colOut) override{};
	bool OnRectCollided(Object* object, CollisionSide side)override { return false; };
	void OnNotCollision(Object* object)override {};
	virtual void Update(float dt);
	virtual void ChangeState(State stateName) {};
	virtual void Render();
	virtual void Respawn();
};