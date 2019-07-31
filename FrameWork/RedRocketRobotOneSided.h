#pragma once
#include "RedRocketRobot.h"
#include "BulletRedRocketLinear.h"

class RedRocketRobotOneSided : public RedRocketRobot
{
protected:
	//Đây là khoảng mà robot sẽ đi qua đi lại.
	const int walkRange = 80;

	//Thời gian delay đến khi được đi tiếp khi đứng lên.
	const int standingToWalkingDelay = 200;

	//Thời gian delay cho sprite nhảy.
	const int jumpingDelay = 100;

	//Chiều dài đoạn mà nó nhảy.
	const int jumpLength = 50;

	//Độ cao mà nó nhảy.
	const int jumpHeight = 50;

	//Toạ độ mà nó hạ cánh.
	int destJumpX;

	//Toạ độ trước khi nhảy.
	int prevJumpY;

	//Khoảng cách tối đa mà nó đi được.
	int minX;
	int maxX;
	//Cờ để xét xem robot đang đi từ trái qua phải hay phải qua trái.
	bool isMovingLeftToRight;

	//Lưu lại trạng thái trước khi chuyển qua beaten state.
	State previousState;

	//Biến đánh dấu trạng thái nhảy.
	bool isJumping = false;

	int currentStateTime = 0;
public:
	RedRocketRobotOneSided(int posX, int posY);
	~RedRocketRobotOneSided();
	void Update(float dt) override;
	void Render() override;
	void EnemyAliveUpdate(double dt) override;
	void EnemyJumpingUpdate(double dt);
	void EnemyAttackingUpdate(double dt);
	void EnemyBeatenUpdate(double dt) override;
	void EnemyDeadUpdate(double dt) override;
	//Hàm dùng để thay đổi hướng đi của robot.
	void ChangeMoveDirection();
	void ChangeState(State);
	void OnCollision(Object* object, collisionOut* colout) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	void OnNotCollision(Object* object) override;
};