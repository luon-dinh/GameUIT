#pragma once
#include "Object.h"
#include "Player.h"

class PlayerHandPunch : Object, public GameObjectProperty {
private:
	PlayerHandPunch();
	~PlayerHandPunch();

	static PlayerHandPunch* instance;
public:
	
	static PlayerHandPunch* getInstance();
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
};