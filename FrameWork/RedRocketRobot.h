#pragma once
#include "BulletRedRocket.h"
#include "Enemy.h"

class RedRocketRobot : public Enemy
{
public:
	enum RedRocketRobotType
	{
		ONESIDED,
		TWOSIDED,
		NONSHOOTING
	};
protected:
	//Delay cho animation đi bộ.
	const int walkingSpriteDelay = 200;
	//Thời gian dừng lại từ lúc chuyển trạng thái đến trước khi bắn.
	const int attackingDelay = 300;
	//Tốc độ đi.
	const double walkingSpeed = 1;
	//Máu.
	const int RedRocketRobotHealth = 5;

	//Đây là delay giữa những lần đi của robot.
	const int walkingDelay = 0;

	//Đây là tốc độ đạn mà quái bắn ra.
	int rocketSpeed = 6;

	//Thời gian delay đến khi ngồi xuống.
	const int standingDelay = 500;

	//Thời gian cho state ngồi.
	const int crouchingState = attackingDelay + 200;

	//Thời gian beaten.
	const int beatenTime = 700;

	//Thời gian shocking.
	const int shockingTime = 200;

	//Thời gian shocking khi chết.
	const int deadShockingTime = 300;

	//Thời gian của trạng thái hiện tại.
	int currentStateTime = 0;

	//Thời gian đã qua của việc chớp chớp.
	int currentBeatenTick = 0;

	//Thời gian dùng để điều khiển việc chớp chớp.
	int flashingTick = 0;

	//Thời gian đã qua của việc đi.
	int currentWalkingTick = 0;

	//Thời gian dùng để điều khiển thời gian chờ khi bắn.
	int currentFiringTick = 0;

	//Cờ đánh dấu là đang bị beaten (chớp chớp).
	bool isBeingBeaten = false;

	//Cờ đánh dấu xem đây có phải là lần đầu tiên nhảy hay không.
	bool isFirstTimeFalling = true;

	//Animation.
	Animation* walking;
	Animation* standing;
	Animation* crouching;
	Animation* shocking;

	RedRocketRobotType robotType;
	Player * player;

	//Biến quy định xét xem liệu quái đã bắn chưa.

	//State.
	State robotState;

	//Biến cho biết trong trạng thái hiện tại robot đã tấn công hay chưa.
	bool isAttacked = false;

	void LoadAllAnimation();
public:
	RedRocketRobot(int posX, int posY);
	~RedRocketRobot();
	virtual void Update(float dt) override {};
	virtual void Render() override {};
	virtual void EnemyAliveUpdate(double dt) override {};
	virtual void EnemyAttackingUpdate(double dt) {};
	virtual void EnemyBeatenUpdate(double dt) override {};
	virtual void EnemyDeadUpdate(double dt) override {};
	//Hàm dùng để thay đổi hướng đi của robot.
	virtual void ChangeMoveDirection() {};
	virtual void ChangeState(State) {};
	virtual void OnCollision(Object* object, collisionOut* colout) override {};
	virtual bool OnRectCollided(Object* object, CollisionSide side) override { return true; };
	virtual void OnNotCollision(Object* object) override {};
	int GetCollisionDamage() override { return 1; }
	void KillObject() override;
};