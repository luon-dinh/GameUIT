#include "PlayerKickingState.h"



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

	// chuyển sang trạng thái nhảy
	if (this->curKickTime >= this->MAX_KICKING_TIME) {
		player->ChangeState(State::JUMPING);
	}

	// chuyển sang trạng thái đá
	if (keyboard->isKeyDown(PLAYER_ATTACK)) {

	}

	this->curKickTime += 10;
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