#pragma once
#include "RedRocketRobot.h"

class RedRocketRobotOneSided : public RedRocketRobot
{
	//Đây là khoảng mà robot sẽ đi qua đi lại.
	const int walkRange = 10;
	//Đây là tốc độ đạn mà quái bắn ra.
	const int rocketSpeed = 5;
	//Thời gian delay đến khi ngồi xuống.
	const int standingDelay = 500;
	//Thời gian delay đến khi được đi tiếp khi đứng lên.
	const int standingToWalkingDelay = 200;
	//Thời gian cho state ngồi.
	const int crouchingState = attackingDelay + 200;

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
	void EnemyAliveUpdate(double dt) override;
	void EnemyAttackingUpdate(double dt);
	void EnemyBeatenUpdate(double dt) override;
	void EnemyDeadUpdate(double dt) override;
	//Hàm dùng để thay đổi hướng đi của robot.
	void ChangeMoveDirection();
	void ChangeState(State);
};