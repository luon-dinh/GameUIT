#include "GamePlayerProperty.h"


GamePlayerProperty::GamePlayerProperty() {
	this->nonAttackableFrameCount = 0;
}

GamePlayerProperty::~GamePlayerProperty() {

}

void GamePlayerProperty::Update() {
	if (this->IsNonAttackable()) {
		this->UpdateNonAttackableState();
	}

}

void GamePlayerProperty::BeingAttacked(int objectDamage) {
	// giảm máu con của player
	this->LoseChildHealth();

	// chuyển về trạng thái không thể tấn công
	this->isNonAttackable = true;
}

bool GamePlayerProperty::IsNonAttackable() {
	return this->isNonAttackable;
}

void GamePlayerProperty::UpdateNonAttackableState() {
	this->nonAttackableFrameCount++;
	
	// rời khỏi trạng thái không thể tấn công
	if (this->nonAttackableFrameCount > MAX_NON_ATTACKABLE_FRAME) {
		this->isNonAttackable = false;
		this->nonAttackableFrameCount = 0;
	}
}

void GamePlayerProperty::SetHealth(int health) {
	this->SetHealth(health);

	if (this->GetHealth() == 1) {
		this->isNearlyDead = true;
	}
}

bool GamePlayerProperty::IsNearlyDead() {
	return this->isNearlyDead;
}

void GamePlayerProperty::IncreaseChildHealth() {
	this->childHealth++;
	if (this->childHealth == MAX_CHILD_HEALTH) {
		this->SetHealth(++this->health);
	}
}

void GamePlayerProperty::LoseChildHealth() {
	this->childHealth--;
	if (this->childHealth == 0) {
		this->SetHealth(--this->health);
	}
}

void GamePlayerProperty::LootItem(Item* item) {

}

void GamePlayerProperty::ResetProperty() {

}