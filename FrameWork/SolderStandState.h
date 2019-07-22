#pragma once

#include "EnemyState.h"
#include "Solder.h"


class SolderStandState : public EnemyState {
private:

public:
	SolderStandState();
	~SolderStandState();

	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;

};