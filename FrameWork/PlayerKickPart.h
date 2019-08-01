#pragma once
#include "Object.h"
#include "Player.h"

class PlayerKickPart : Object, public GameObjectProperty {
private:
	PlayerKickPart();
	~PlayerKickPart();

	static PlayerKickPart* instance;
public:

	static PlayerKickPart* getInstance();
	static void releaseInstance();
	void SetPositionToPlayer();

	BOOL GetActive() override;
	BoundingBox getBoundingBox() override;

	void Render() override;
	void Update(float dt) override;
	void UpdateGameProperty() override {};
	void ResetGameProperty() override {};
	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	int GetCollisionDamage() override;
};