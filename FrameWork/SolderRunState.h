#pragma once

#include "EnemyState.h"
#include "Solder.h"


class SolderRunState : public EnemyState {
private:

public:
	SolderRunState();
	~SolderRunState();

	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;

};