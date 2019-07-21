#pragma once
#include "Enemy.h"


class Solder : public Enemy {
private:
public:
	Solder(EnemyType type);
	~Solder();


	void Move() override;
	void Shoot() override;
	void OnCollision(Object* object, collisionOut* colOut) override;

};