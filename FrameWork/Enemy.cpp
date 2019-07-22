#include "Enemy.h"


Enemy::Enemy(Enemy::EnemyType type) {
	this->type = type;
}

Enemy::~Enemy() {

}

Enemy::EnemyType Enemy::GetType() {
	return this->type;
}

void Enemy::SetType(EnemyType type) {
	this->type = type;
}

Enemy::Direction Enemy::GetDirection() {
	return this->direction;
}

void Enemy::SetDirection(Enemy::Direction direction) {
	this->direction = direction;
}

