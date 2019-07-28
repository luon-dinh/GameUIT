#pragma once
#include "BulletRedRocket.h"

class BulletRedRocketLinear : public BulletRedRocket
{
public:
	BulletRedRocketLinear(MoveDirection rocketDirection, int posX, int posY, int Speed);
	~BulletRedRocketLinear();
	void Update(float dt) override;
};