#pragma once
#include "Object.h"


class Enemy : public Object {
protected:
	enum EnemyType {
		BlueSolder,	
		RobotRocketer,
		WhiteRobotRocketer
	};

	enum Direction {
		LeftToRight,
		RightToLeft
	};

	EnemyType type;
	Direction direction;
public:

	Enemy(EnemyType type);
	~Enemy();


	virtual EnemyType GetType();
	virtual void SetType(EnemyType type);
	virtual Direction GetDirection();
	virtual void SetDirection(Direction direction);

	virtual void Move() = 0;
	virtual void Shoot() = 0;
	virtual void OnCollision(Object* object, collisionOut* colOut) override = 0;

};