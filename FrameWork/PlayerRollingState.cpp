#include "PlayerRollingState.h"



PlayerRollingState::PlayerRollingState()
{
	state = State::ROLLING;
	this->curRollTime = 0;
}


PlayerRollingState::~PlayerRollingState()
{
}

void PlayerRollingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	
	// chuyển sang trạng thái nhảy
	if (this->curRollTime >= this->MAX_ROLLING_TIME) {
		player->ChangeState(State::JUMPING);
	}

	// chuyển sang trạng thái đá
	if (keyboard->isKeyDown(PLAYER_ATTACK)) {
		
	}

	this->curRollTime += 10;
}

void PlayerRollingState::OnCollision(Object* object, collisionOut* collision) {
	//auto side = collision->side;

	//// collide with ground
	//if (object->type == Type::GROUND) {
	//	if (side == CollisionSide::top || side == CollisionSide::bottom) {
	//		Player::getInstance()->SetVy(0);
	//	}
	//}
}

void PlayerRollingState::Update(float dt)
{
	this->InputHandler();
}