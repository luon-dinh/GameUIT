#pragma once
#include "Object.h"
#include "Player.h"

class PlayerKickPart : public Object {
private:
	bool existInOneFrame;

	const int KICK_DAMAGE = 2;
public:

	PlayerKickPart();
	~PlayerKickPart();

	void SetPositionToPlayer();

	BoundingBox getBoundingBox() override;

	void Render() override;
	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	int GetCollisionDamage() override;
};