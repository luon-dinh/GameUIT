#include "GamePlayerProperty.h"


GamePlayerProperty::GamePlayerProperty() {
	this->nonAttackableFrameCount = -1;
	this->SetHealth(2 * HEALTH_PER_HEART);
}

GamePlayerProperty::~GamePlayerProperty() {

}

void GamePlayerProperty::UpdateGameProperty() {
	if (this->IsNonAttackable() && this->nonAttackableFrameCount != -1) {
		this->UpdateNonAttackableState();
	}
}

void GamePlayerProperty::BeingAttacked(int objectDamage) {
	// giảm máu con của player
	this->LoseHealth(objectDamage);

	// nếu đang bất tử thì không xử lý
	if (this->IsImmortal()) {
		return;
	}
	this->isNonAttackable = true;
	this->nonAttackableFrameCount = 0;
}

bool GamePlayerProperty::IsNonAttackable() {
	return this->isNonAttackable && this->nonAttackableFrameCount != -1;
}

bool GamePlayerProperty::IsImmortal() {
	return this->isNonAttackable && this->nonAttackableFrameCount == -1;
}


void GamePlayerProperty::UpdateNonAttackableState() {
	this->nonAttackableFrameCount++;
	
	// rời khỏi trạng thái không thể tấn công
	if (this->nonAttackableFrameCount > MAX_NON_ATTACKABLE_FRAME) {
		this->isNonAttackable = false;
		this->nonAttackableFrameCount = -1;
	}
}

void GamePlayerProperty::SetHealth(int health) {
	GameObjectProperty::SetHealth(health);

	if (this->GetHealth() == 1) {
		this->isNearlyDead = true;
	}
}

bool GamePlayerProperty::IsNearlyDead() {
	return this->isNearlyDead;
}

void GamePlayerProperty::IncreaseHealth(int value) {
	this->SetHealth(this->health + value);
}

void GamePlayerProperty::LoseHealth(int value) {
	this->SetHealth(this->health - value);
}

void GamePlayerProperty::SetToImmortalState() {
	this->isNonAttackable = true;
	this->nonAttackableFrameCount = -1;
}

void GamePlayerProperty::SetToNormalState() {
	this->isNonAttackable = false;
	this->nonAttackableFrameCount = -1;
}

void GamePlayerProperty::LootItem(Item* item) {

}

void GamePlayerProperty::ResetGameProperty() {

}

int GamePlayerProperty::GetHeart() {
	if (this->GetHealth() == 0)
		return 0;

	return this->GetHealth() / HEALTH_PER_HEART + (this->GetHealth() % HEALTH_PER_HEART > 0);
}