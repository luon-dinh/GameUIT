#pragma once
#include "Enemy.h""
#include"Shield.h"
#include"BulletManager.h"

class Solder : public Enemy {
private:
public:
	Solder(RunType runType);
	~Solder();
	bool canJump;
	State stateName;
	RunType runType;
	float timeCurrentState;
	std::unordered_map<State, Animation*> animations;
	std::list<Object*> additionalObjects;
	std::list<Object*>* getAdditionalObjects()override
	{
		return &additionalObjects;
	}
	void LoadAllAnimation();
	void ChangeState(State state)override; 
	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side)override;
	void OnNotCollision(Object* oject)override;
	void Update(float dt) override;
	void Render();
	BoundingBox getBoundingBox()override;
};