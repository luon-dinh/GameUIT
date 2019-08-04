#pragma once
#include "Object.h"
#include "Player.h"

class PlayerHandPunch : public Object{
private:
	bool existInOneFrame;
	

	const int HAND_PUNCH_DAMAGE = 2;
public:
	PlayerHandPunch();
	~PlayerHandPunch();
	void SetPositionToPlayer();

	BoundingBox getBoundingBox() override;
	
	void Render() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	int GetCollisionDamage() override;
};