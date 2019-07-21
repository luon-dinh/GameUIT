#pragma once

#include "EnemyState.h"
#include "Solder.h"


class SolderDuckState : public EnemyState {
private:

public:
	SolderDuckState();
	~SolderDuckState();

	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;

};