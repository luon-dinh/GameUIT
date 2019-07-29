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
	const int RedRocketRobotHealth = 3;

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
	virtual void Update(float dt) override;
	virtual void ChangeState() {};
};