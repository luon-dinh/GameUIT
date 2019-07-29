#pragma once
#include "RedRocketRobot.h"
#include "BulletRedRocketLinear.h"

class RedRocketRobotOneSided : public RedRocketRobot
{
	//Đây là khoảng mà robot sẽ đi qua đi lại.
	const int walkRange = 100;

	//Đây là delay giữa những lần đi của robot.
	const int walkingDelay = 0;

	//Đây là tốc độ đạn mà quái bắn ra.
	const int rocketSpeed = 5;
	//Thời gian delay đến khi ngồi xuống.
	const int standingDelay = 500;
	//Thời gian delay đến khi được đi tiếp khi đứng lên.
	const int standingToWalkingDelay = 200;
	//Thời gian cho state ngồi.
	const int crouchingState = attackingDelay + 200;

	//Thời gian beaten.
	const int beatenTime = 1000;

	//Thời gian shocking.
	const int shockingTime = 200;

	//Thời gian shocking khi chết.
	const int deadShockingTime = 800;

	//Thời gian đã qua của việc chớp chớp.
	int currentBeatenTick = 0;

	//Thời gian dùng để điều khiển việc chớp chớp.
	int flashingTick = 0;

	//Thời gian đã qua của việc đi.
	int currentWalkingTick = 0;

	//Cờ đánh dấu là đang bị beaten (chớp chớp).
	bool isBeingBeaten = false;

	//Khoảng cách tối đa mà nó đi được.
	int minX;
	int maxX;
	//Cờ để xét xem robot đang đi từ trái qua phải hay phải qua trái.
	bool isMovingLeftToRight;

	//Lưu lại trạng thái trước khi chuyển qua beaten state.
	State previousState;

	int currentStateTime = 0;
public:
	RedRocketRobotOneSided(int posX, int posY);
	~RedRocketRobotOneSided();
	void Update(float dt) override;
	void Render() override;
	void EnemyAliveUpdate(double dt) override;
	void EnemyAttackingUpdate(double dt);
	void EnemyBeatenUpdate(double dt) override;
	void EnemyDeadUpdate(double dt) override;
	//Hàm dùng để thay đổi hướng đi của robot.
	void ChangeMoveDirection();
	void ChangeState(State);
	void OnCollision(Object* object, collisionOut* colout) override;
	bool OnRectCollided(Object* object, CollisionSide side) override { return true; };
	void OnNotCollision(Object* object) override {};
};