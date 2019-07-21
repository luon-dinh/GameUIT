#include "EnemyState.h"


EnemyState::EnemyState(EnemyState::StateName stateName) {
	this->SetState(stateName);
}

EnemyState::~EnemyState() {

}

EnemyState::StateName EnemyState::GetState() {
	return this->state;
}

void EnemyState::SetState(EnemyState::StateName stateName) {
	this->state = stateName;
}

