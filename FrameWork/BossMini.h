#pragma once
#include"Enemy.h"
#include"BulletMiniSpecial.h"

class BossMini :public Enemy {
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua boss
	static BossMini* instance;
	void LoadAllAnimations();
public:
	const float maxTimeNotRender=1000;
	const float maxHelth = 20;
	const int maxTimeStateDelay = 1000;
	const float maxDelatXRun = 150;
	const float minMap = 20;
	const float maxMap = 235;
	const float mapWidth=256;
	const int maxBullet=3;
	const float speed = 2;
	const float bulletSpeed = 3;
	const float deltaToThrow = 80;
	const float defaultDT = 30;
	float delayAttack;
	int countTimeBeaten;
	int countBullet;
	float timeNotRender;
	float timeCurrentState;
	float deltaX;
	bool canNewBullet;//
	bool hasBullet;
	BulletMiniSpecial* defaultBullet;

	float getWidth()override;
	float getHeight()override;
	void Update(float dt);
	void Render();
	void ChangeState(State stateName);
	void OnCollision(Object* object, collisionOut* colOut)override;
	bool OnRectCollided(Object* object, CollisionSide side)override;
	BoundingBox getBoundingBox()override;
	Animation* currentAnimation;
	static BossMini* getInStance();
	State state;
	BossMini();
	~BossMini();
};

