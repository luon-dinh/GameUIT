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
	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		player->ChangeState(State::KICKING);
		return;
	}
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetVx(-PLAYER_NORMAL_SPEED);
	}
	else
		if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
			player->SetVx(PLAYER_NORMAL_SPEED);
		}
	
	PlayerRollingState::curRollTime += 15;
	if (player->IsReachMaxJump()) {
		player->SetVy(0);
	}
}

BOOL PlayerRollingState::HasRollFullTime() {
	return curRollTime >= MAX_ROLLING_TIME;
}

void PlayerRollingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;
	auto player = Player::getInstance();
	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom) {
 			player->pos.y += collision->collisionTime * player->vy;
			player->ChangeState(State::STANDING);
		}
	}
}

void PlayerRollingState::Update(float dt)
{
	this->InputHandler();
}

BoundingBox PlayerRollingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 7;
	box.bottom = player->pos.y - 10;
	box.left = player->pos.x - 10;
	box.right = player->pos.x + 10;
	return box;
}
