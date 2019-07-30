#include "GameObjectProperty.h"


GameObjectProperty::GameObjectProperty() {

}

GameObjectProperty::~GameObjectProperty() {

}

int GameObjectProperty::GetHealth() {
	return this->health;
}

void GameObjectProperty::SetHealth(int health) {
	this->health = health;
}


int GameObjectProperty::GetDamage() {
	return this->damage;
}

void GameObjectProperty::SetDamage(int damage) {
	this->damage = damage;
}

void GameObjectProperty::BeingAttacked(int objectDamage) {
	this->health -= objectDamage;
}

bool GameObjectProperty::IsDead() {
	if (this->health > 0)
		return false;

	return this->health == 0;
}