#pragma once
#include "Object.h"
#include "Player.h"

class PlayerHandOnRope : public Object {
public:

	PlayerHandOnRope();
	~PlayerHandOnRope();
	void SetPositionToPlayer();

	BoundingBox getBoundingBox() override;

	void Render() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	void OnNotCollision(Object* object) override;
};