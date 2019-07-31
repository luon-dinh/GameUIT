#pragma once

class GameObjectProperty {
protected:
	int health;
	int damage;

	virtual int GetHealth();
	virtual void SetHealth(int health);
	

public:
	GameObjectProperty();
	~GameObjectProperty();

	virtual int GetDamage();
	virtual void SetDamage(int damage);
	virtual void BeingAttacked(int objectDamage);
	virtual bool IsDead();
	virtual void Update() = 0;
	virtual void ResetProperty() = 0;
};