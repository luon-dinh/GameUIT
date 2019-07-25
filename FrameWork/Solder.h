#pragma once
#include "Enemy.h""
#include"Shield.h"
#include"BulletManager.h"

class Solder : public Enemy {
private:
public:
	Solder(bool movable);
	~Solder();
	State stateName;
	bool movable;
	float timeCurrentState;
	std::unordered_map<State, Animation*> animations;
	std::list<Object*>* additionalObjects;
	std::list<Object*>* getAdditionalObjects()override
	{
		return additionalObjects;
	}
	void LoadAllAnimation();
	void ChangeState(State state)override; 
	void Shoot() override;
	void OnCollision(Object* object, collisionOut* colOut) override;
  void Update(float dt) override;
	void Respawn()override {};
	void Render();
};