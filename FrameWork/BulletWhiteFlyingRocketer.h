#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Player.h"

class BulletWhiteFlyingRocketer : public Bullet
{
private:
	const int bulletFlashingRate = 120;
	//Thời gian tối thiểu trước khi viên đạn có thể đổi hướng.
	const int minTimeRedirect = 300;
	//Số lần đổi hướng tối đa của viên đạn.
	const int maxRedirect = 8;
	//Tốc độ đạn lúc nào cũng nhanh hơn player một chút.
	const double BulletSpeed = 2;
	//Để đạn bay mượt hơn, khi tính ra được VX hoặc VY quá nhỏ, ta cho = 0.
	//Góc quay tối đa trong 1 frame.
	const double maxRotateDegree = 990;
	Animation * animBullet0;
	Animation * animBullet45;
	Animation * animBullet90;
	Animation * animBullet135;
	Animation * animBullet180;
	Animation * animBullet225;
	Animation * animBullet270;
	Animation * animBullet315;
	Player * player;

	float curDelayTime = 0;
	int redirectTime = 0;

	//Mọi góc chúng ta xét đều bắt đầu từ trục y hướng lên.
	double currentDegree = -1;

	bool RedirectTowardPlayer();

	Animation* getAnimOnDeg();
public:
	BulletWhiteFlyingRocketer(MoveDirection robotDirection, int posX, int posY);
	~BulletWhiteFlyingRocketer();
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	BoundingBox getBoundingBox() override;
};