#include "BulletRedRocketNonLinear.h"

BulletRedRocketNonLinear::BulletRedRocketNonLinear(MoveDirection rocketDirection, int posX, int posY, int Speed) : BulletRedRocket(rocketDirection, posX, posY, Speed)
{
	rocketAnim = new Animation(Tag::REDROCKERTERBULLET, 0, 2, rocketFlashingRate);
	rocketNonLinearAnim = new Animation(Tag::REDROCKERTERBULLET, 2, 4, rocketFlashingRate);
}

BulletRedRocketNonLinear::~BulletRedRocketNonLinear()
{
	if (rocketAnim != nullptr)
		delete rocketAnim;
}

void BulletRedRocketNonLinear::Update(float dt)
{
	BulletRedRocket::Update(dt);
	//Xét nếu quãng đường đi đủ lâu rồi thì đổi hướng.
	if (isLinear)
	{
		if (linearGone > linearLength)
		{
			this->animation = rocketNonLinearAnim;
			isLinear = false;
			this->vx = sin(rocketAngle * PI / 180) * rocketSpeed;
			this->vy = cos(rocketAngle * PI / 180) * abs(rocketSpeed);
		}
		else
		{
			linearGone += this->vx;
		}
		this->pos.x += this->vx;
	}
	else
	{
		this->pos.x += this->vx;
		this->pos.y += this->vy;
	}

}