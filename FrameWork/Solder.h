#pragma once
#include "Enemy.h""
#include"Shield.h"
#include"BulletManager.h"

class Solder : public Enemy {
private:
public:
	Solder(RunType runType, float x, float y);
	~Solder();
	Solder() {};
	bool canJump;
	State stateName;
	RunType runType;
	float duckingTime = 2000;
	float standingTime = 500;
	float runningTime = 1500;
	float timeCurrentState;
	float deltaY = 0;
	float bulletSpeedy = 0.5;
	virtual float PosToBottom();
	float delayBeaten;
	float delayToDead;
	const float maxDelayBeaten=2000;
	const int score = 200;
	std::unordered_map<State, Animation*> animations;
	virtual void LoadAllAnimation();
	virtual void ChangeState(State state)override; 
	virtual void OnCollision(Object* object, collisionOut* colOut) override;
	virtual bool OnRectCollided(Object* object, CollisionSide side)override;
	virtual void OnNotCollision(Object* oject)override;
	virtual void Update(float dt) override;
	virtual void Render();
	virtual float getHeight()override;
	virtual float getWidth()override;
	virtual BoundingBox getBoundingBox()override;
};