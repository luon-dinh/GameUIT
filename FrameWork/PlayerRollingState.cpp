#include "PlayerRollingState.h"


int PlayerRollingState::curRollTime = 0;

PlayerRollingState::PlayerRollingState()
{
	state = State::ROLLING;
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
		PlayerRollingState::curRollTime = 0;
	}

	// chuyển sang trạng thái đá
	if (keyboard->isKeyDown(PLAYER_ATTACK)) {
		player->ChangeState(State::KICKING);
		return;
	}
	
	PlayerRollingState::curRollTime += 40;
}

BOOL PlayerRollingState::HasRollFullTime() {
	return curRollTime >= MAX_ROLLING_TIME;
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