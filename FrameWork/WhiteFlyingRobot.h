#pragma once
#include "BulletWhiteFlyingRocketer.h"
#include "Enemy.h"
#include "Delay.h"

class WhiteFlyingRobot : public Enemy
{
private:
	//Tốc độ góc.
	const double angularVelocity = 2;
	
	//Delay giữa 2 lần thay đổi tốc độ góc.
	const int delayFlyingTime = 20;

	//Delay phóng lửa để bay.
	const int delayFlyingSprite = 120;
	//Delay xoay vòng vòng khi rớt xuống đất.
	const int delayFallingAnim = 60;
	//Delay cho sprite khi bắn.
	const int delayAttackingAnim = 200;

	//Tốc độ tối đa theo 2 trục X,Y.
	//Dựa vào tốc độ tối đa mà ta cũng có thể xác định quỹ đạo bay.
	const double VXMax = 3;
	const double VYMax = 1;

	//Thời gian beaten.
	const int beatenTime = 1000;

	//Do quỹ đạo bay là 1 ellipse, vì vậy ta sẽ quét góc theo tâm.
	//Góc hiện tại.
	double currentDegree = 0;

	//Delay time dùng để xét khoảng thời gian đã qua.
	int delayTime = 0;

	//Thời gian đã qua của state hiện tại.
	int currentStateTime = 0;

	//Thời gian đã qua của việc chớp chớp.
	int currentBeatenTick = 0;

	//Thời gian delay.
	Delay* attackDelay;

	//Một map để lưu trữ từng animation tương ứng với state.
	std::unordered_map<State, Animation*> stateAnim;

	//Trạng thái của Robot.
	State robotState;

	const int score = 300;
	Player* player;
public:
	WhiteFlyingRobot(int posX, int posY);
	~WhiteFlyingRobot();
	void ChangeState(State) override;
	void Update(float dt) override;
	void Render() override;

	void EnemyAliveUpdate(double dt) override;
	void EnemyAttackingUpdate(double dt);
	void EnemyBeatenUpdate(double dt) override;
	void EnemyDeadUpdate(double dt) override;

	void LoadAllAnimation();
	void OnCollision(Object* object, collisionOut* colout) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	void OnNotCollision(Object* object) override;
	BoundingBox getBoundingBox() override;
};