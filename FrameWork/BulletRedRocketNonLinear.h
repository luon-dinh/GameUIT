#pragma once
#include "BulletRedRocket.h"

class BulletRedRocketNonLinear : public BulletRedRocket
{
	//Quãng đường đi tối đa trước khi đổi hướng.
	const int linearLength = 25;

	//Góc xoay của viên đạn (mặc định trong game là 40 độ).
	const double rocketAngle = 40;

	//Quãng đường đã đi được.
	int linearGone = 0;

	//Biến cờ đánh dấu xem hiện tại đi như thế nào (thẳng, chéo,...).
	bool isLinear = false;

	Animation * rocketNonLinearAnim;
public:
	BulletRedRocketNonLinear(MoveDirection rocketDirection, int posX, int posY, int Speed);
	~BulletRedRocketNonLinear();
	void Update(float dt) override;
};