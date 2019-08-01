#pragma once
#include "RedRocketRobot.h"

class RedRocketRobotTwoSided : public RedRocketRobot
{
protected:
	//Khoảng cách đi đến khi chuyển state.
	const int walkingDistant = 100;

	//Khoảng thời gian cho từng state đứng & ngồi.
	const int attackingStateTime = attackingDelay + 1000;
	//Chiều dài đoạn mà nó nhảy.
	const int jumpLength = 50;

	//Độ cao mà nó nhảy.
	const int jumpHeight = 50;
	
	//Quãng đường đã đi.
	int gone = 0;

	//Đích đến khi nhảy.
	int destJumpX;

	//State trước đó.
	State previousState;

	//Ground trước đó mà nó đụng (dùng để xét rơi khỏi ground).
	Object* previousGround;
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

	void EnemyJumpingUpdate(double dt);

	void ChangeState(State);
	void OnCollision(Object* object, collisionOut* colout) override;
	bool OnRectCollided(Object* object, CollisionSide side) override { return true; };
	void OnNotCollision(Object* object) override;
};