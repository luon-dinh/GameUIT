#pragma once
#include "GameObjectProperty.h"
#include "Item.h"

class GamePlayerProperty : public GameObjectProperty {
protected:
	int nonAttackableFrameCount;
	bool isNonAttackable;
	bool isNearlyDead;

	int childHealth;

	const int MAX_NON_ATTACKABLE_FRAME = 35;
	const int MAX_CHILD_HEALTH = 4;

	void IncreaseChildHealth();
	void LoseChildHealth();

	void SetHealth(int health) override;

public:
	GamePlayerProperty();
	~GamePlayerProperty();

	void Update() override;
	void BeingAttacked(int objectDamage) override;

	bool IsNonAttackable();
	void UpdateNonAttackableState();

	bool IsNearlyDead();

	void LootItem(Item* item);			//	 khi va chạm với item thì loot item đó
};