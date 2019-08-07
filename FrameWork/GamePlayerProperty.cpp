#include "GamePlayerProperty.h"


GamePlayerProperty::GamePlayerProperty() {
	this->nonAttackableFrameCount = -1;
	this->SetHealth(2 * HEALTH_PER_HEART);
	this->maxNonAttackableFrames = MAX_NON_ATTACKABLE_FRAME;
}

GamePlayerProperty::~GamePlayerProperty() {

}

void GamePlayerProperty::UpdateGameProperty() {
	if (this->IsNonAttackable() && this->maxNonAttackableFrames != -1) {
		this->UpdateNonAttackableState();
	}

	
}

void GamePlayerProperty::BeingAttacked(int objectDamage) {
	// nếu đang bất tử thì không xử lý
	if (this->IsImmortal() || this->IsNonAttackable()) {
		return;
	}
	// giảm máu con của player
	this->LoseHealth(objectDamage);
	// chuyển sang trạng thái vô địch
	this->SetToNonAttackableState();
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
	if (this->nonAttackableFrameCount > this->maxNonAttackableFrames) {
		if (this->IsDead()) {
			this->SetToImmortalState();
			return;
		}
		SetToNormalState();
	}
}

void GamePlayerProperty::SetHealth(int health) {
	GameObjectProperty::SetHealth(health);

	if (this->GetHealth() == HEALTH_PER_HEART) {
		this->isNearlyDead = true;
	}
}

void GamePlayerProperty::ResetTransScene() {
	this->canGoToNextScene = false;
	ExitSignal::getInstance()->SetActive(false);
}

bool GamePlayerProperty::IsNearlyDead() {
	return this->isNearlyDead;
}

bool GamePlayerProperty::CanGoNextScene() {
	return this->canGoToNextScene;
}

void GamePlayerProperty::IncreaseHealth(int value) {
	int newValue = this->health + value;
	if (newValue > HEALTH_PER_HEART * MAX_HEART) {
		this->SetHealth(HEALTH_PER_HEART * MAX_HEART);
		return;
	}
	this->SetHealth(newValue);
}

void GamePlayerProperty::LoseHealth(int value) {
	this->SetHealth(this->health - value);
}

void GamePlayerProperty::SetToImmortalState() {
	this->isNonAttackable = true;
	this->nonAttackableFrameCount = -1;
}

void GamePlayerProperty::SetToNonAttackableState(int frames) {
	this->maxNonAttackableFrames = frames;
	this->isNonAttackable = true;
	this->nonAttackableFrameCount = 0;
}

void GamePlayerProperty::SetToNormalState() {
	this->isNonAttackable = false;
	this->nonAttackableFrameCount = -1;
}

void GamePlayerProperty::LootItem(Item* item) {
	switch (item->itemtype) {
		case ItemType::EXIT:{
			this->canGoToNextScene = true;
			ExitSignal::getInstance()->SetActive(true);
			break;
		}
		case ItemType::HALFHEART: {
			this->IncreaseHealth(HEALTH_PER_HEART / 2);
			break;
		}
		case ItemType::HEART: {
			this->IncreaseHealth(HEALTH_PER_HEART);
			break;
		}
		case ItemType::HP: {
			this->IncreaseHealth(1);
			break;
		}				   
	}
}

void GamePlayerProperty::ResetGameProperty() {
	ExitSignal::getInstance()->SetActive(false);
	this->canGoToNextScene = false;
}

int GamePlayerProperty::GetHeart() {
	if (this->GetHealth() == 0)
		return 0;

	return this->GetHealth() / HEALTH_PER_HEART + (this->GetHealth() % HEALTH_PER_HEART > 0);
}

void GamePlayerProperty::SetHeart(int heart) {
	if (heart >= MAX_HEART) {
		this->SetHealth(MAX_HEART * HEALTH_PER_HEART);
		return;
	}
	this->SetHealth(heart * HEALTH_PER_HEART);
}