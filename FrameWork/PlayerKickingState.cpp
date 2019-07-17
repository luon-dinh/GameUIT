﻿#include "PlayerKickingState.h"



PlayerKickingState::PlayerKickingState()
{
	state = State::KICKING;
	this->curKickTime = 0;
}


PlayerKickingState::~PlayerKickingState()
{
}

void PlayerKickingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	
	if (this->curKickTime > MAX_KICKING_TIME) {
		// trạng thái trước đó là ROLLING thì chuyển về lại ROLLING
		if (player->GetPreviousState()->state == State::ROLLING)
			player->ChangeState(State::ROLLING);
		else
			player->ChangeState(State::JUMPING);
		this->curKickTime = 0;
		return;
	}
	this->curKickTime += 30;
}



void PlayerKickingState::OnCollision(Object* object, collisionOut* collision) {
	//auto side = collision->side;

	//// collide with ground
	//if (object->type == Type::GROUND) {
	//	if (side == CollisionSide::top || side == CollisionSide::bottom) {
	//		Player::getInstance()->SetVy(0);
	//	}
	//}
}

void PlayerKickingState::Update(float dt)
{
	this->InputHandler();
}