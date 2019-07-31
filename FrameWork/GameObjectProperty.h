#pragma once

class GameObjectProperty {
protected:
	int health;
	int damage;


	virtual void SetHealth(int health);
	

public:
	GameObjectProperty();
	~GameObjectProperty();

	virtual int GetHealth();
	virtual int GetDamage();
	virtual void SetDamage(int damage);
	virtual void BeingAttacked(int objectDamage);
	virtual bool IsDead();
	virtual void UpdateGameProperty() = 0;
	virtual void ResetGameProperty() = 0;
};