#pragma once
#include"Enemy.h"

class BossMini :public Enemy {
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua boss
	static BossMini* instance;
	void LoadAllAnimations();
public:
	const float maxTimeNotRender=1000;
	const float maxHelth = 20;
	const int maxTimeBeaten = 3;
	int countTimeBeaten;
	float timeNotRender;

	void Update(float dt);
	void Render();
	void ChangeState(State stateName);
	void OnCollision(Object* object, collisionOut* colOut)override;
	bool OnRectCollided(Object* object, CollisionSide side)override;
	BoundingBox getBoundingBox()override;
	Animation* currentAnimation;
	State state;
	BossMini();
	~BossMini();
};

