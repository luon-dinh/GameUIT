#include "BulletRedRocketLinear.h"

BulletRedRocketLinear::BulletRedRocketLinear(MoveDirection rocketDirection, int posX, int posY, int Speed) : BulletRedRocket(rocketDirection, posX, posY, Speed)
{
	rocketAnim = new Animation(Tag::REDROCKERTERBULLET, 0, 2, rocketFlashingRate);
	animation = rocketAnim;
}

BulletRedRocketLinear::~BulletRedRocketLinear()
{
	if (rocketAnim != nullptr)
		delete rocketAnim;
}

void BulletRedRocketLinear::Update(float dt)
{
	BulletRedRocket::Update(dt);
	//Cập nhật lại vị trí của viên đạn theo tốc độ đạn.
	this->pos.x += this->vx;
}