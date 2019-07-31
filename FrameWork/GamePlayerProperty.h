﻿#pragma once
#include "GameObjectProperty.h"
#include "Item.h"

class GamePlayerProperty : public GameObjectProperty {
protected:
	int nonAttackableFrameCount;
	bool isNonAttackable;
	bool isNearlyDead;
	bool isDead;

	void IncreaseHealth(int value);
	void LoseHealth(int value);
	void UpdateNonAttackableState();

	void SetHealth(int health) override;


	const int MAX_NON_ATTACKABLE_FRAME = 105;
	const int HEALTH_PER_HEART = 4;
public:
	GamePlayerProperty();
	~GamePlayerProperty();

	virtual bool IsNonAttackable();
	virtual bool IsImmortal();
	virtual void SetToImmortalState();				// Chuyển sang trạng thái bất tử
	virtual void SetToNormalState();				// Chuyển sang trạng thái bình thường
	bool IsNearlyDead();
	int GetHeart();									// Lấy trái tim để render

	void LootItem(Item* item);						//	 khi va chạm với item thì loot item đó
	void UpdateGameProperty()				 override;
	void ResetGameProperty()				 override;
	void BeingAttacked(int objectDamage)	 override;
	virtual int GetDamage() 				 override { return GameObjectProperty::GetDamage(); };
};