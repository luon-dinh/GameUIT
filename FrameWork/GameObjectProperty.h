#pragma once


class GameObjectProperty {
protected:
	int health;
	int damage;

	virtual int GetHealth();
	virtual void SetHealth(int health);
	int GetDamage();
	void SetDamage(int damage);
	bool IsDead();

public:
	GameObjectProperty();
	~GameObjectProperty();

	virtual void BeingAttacked(int objectDamage);
	virtual void Update() = 0;
};