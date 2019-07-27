#pragma once
#include "BulletWhiteFlyingRocketer.h"
#include "Enemy.h"

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

	//Tốc độ tối đa theo 2 trục X,Y.
	//Dựa vào tốc độ tối đa mà ta cũng có thể xác định quỹ đạo bay.
	double VXMax = 3;
	double VYMax = 1;

	//Do quỹ đạo bay là 1 ellipse, vì vậy ta sẽ quét góc theo tâm.
	//Góc hiện tại.
	double currentDegree = 0;

	//Delay time dùng để xét khoảng thời gian đã qua.
	int delayTime = 0;

	//Một map để lưu trữ từng animation tương ứng với state.
	std::unordered_map<State, Animation*> stateAnim;

	//Trạng thái của Robot.
	State robotState;

	Player* player;
public:
	WhiteFlyingRobot(int posX, int posY);
	~WhiteFlyingRobot();
	void Update(float dt) override;
	void Render() override;
	void LoadAllAnimation();
	void OnCollision(Object* object, collisionOut* colout) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	void OnNotCollision(Object* object) override;
};