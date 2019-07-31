#pragma once
#include "Bullet.h"

class BulletRedRocket : public Bullet
{
public:
	enum RedRocketType
	{
		Linear,
		NonLinear
	};
protected:
	const int rocketFlashingRate = 120;
	//Thời gian để sau khi nổ thì đạn biến mất.
	const int delayDisappear = 300;
	//Tốc độ của viên đạn.
	int rocketSpeed = 0;
	
	bool isExploded;

	//Animation của viên đạn bay thẳng.
	Animation* rocketAnim;

public:
	BulletRedRocket(MoveDirection rocketDirection,int posX, int posY, int Speed);
	~BulletRedRocket();
	virtual void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	BoundingBox getBoundingBox() override;
	int GetBulletDamage() override {
		return 1;
	};
	bool CanGetThroughShield() override { return true; }
};