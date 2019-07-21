#pragma once

#include "EnemyState.h"
#include "Solder.h"


class SolderBeatenState : public EnemyState {
private:

public:
	SolderBeatenState();
	~SolderBeatenState();

	void Update(float dt) override;
	void OnCollision(Object* object, collisionOut* colOut) override;

};