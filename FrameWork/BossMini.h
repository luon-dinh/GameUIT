#pragma once
#include"Enemy.h"
#include"BulletMiniSpecial.h"

class BossMini :public Enemy {
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua boss
	static BossMini* instance;
	void LoadAllAnimations();
public:
	const float maxHelth = 16;
	const float maxDelatXRun = 150;
	const float minMap = 0;
	const float maxMap = 256;
	const float mapWidth=256;
	const int maxBullet=3;
	const float speed = 2;
	const float bulletSpeed = 3;
	const float deltaToThrow = 60;
	const float defaultDT = 35;
	const float maxTimeNotCollidable = 1500;
	const float maxTimeStateDelay = 1000;
	const float maxtimeDashStateDelay = 1500;
	const float maxTimeAttack = 2000;
	float timeNotCollideable;
	int countTimesBeaten;
	const int maxTimesBeaten=3;
	const int maxTimesBeaten2=10;
	int countBullet;
	float timeCurrentState;
	float deltaX;
	bool canNewBullet;//
	BulletMiniSpecial* defaultBullet;
	bool canDash;

	int GetCollisionDamage()override;
	float getPosToBottom();
	float getWidth();
	float getHeight();
	void Update(float dt);
	void Render();
	void ChangeState(State stateName);
	void OnCollision(Object* object, collisionOut* colOut);
	bool OnRectCollided(Object* object, CollisionSide side);
	BoundingBox getBoundingBox();
	Animation* currentAnimation;
	static BossMini* getInstance();
	State state;
	BossMini();
	~BossMini();
};

