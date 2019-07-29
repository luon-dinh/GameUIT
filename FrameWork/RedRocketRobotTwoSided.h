#pragma once
#include "RedRocketRobot.h"

class RedRocketRobotTwoSided : public RedRocketRobot
{
	//Khoảng cách đi đến khi chuyển state.
	const int walkingDistant = 50;

	//Khoảng thời gian cho từng state đứng & ngồi.
	const int attackingStateTime = attackingDelay + 1000;
	
	//Quãng đường đã đi.
	int gone = 0;

	//State trước đó.
	State previousState;
public:
	RedRocketRobotTwoSided(int posX, int posY);
	~RedRocketRobotTwoSided();
protected:
	void Update(float dt);
	void Render();
	void EnemyWalkingUpdate(double dt);
	void EnemyAttackingUpdate(double dt);
	void EnemyBeatenUpdate(double dt) override;
	void EnemyDeadUpdate(double dt) override;

	virtual void Fire();

	void ChangeState(State);
	void OnCollision(Object* object, collisionOut* colout) override;
	bool OnRectCollided(Object* object, CollisionSide side) override { return true; };
	void OnNotCollision(Object* object) override {};
};