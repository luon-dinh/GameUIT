#include "PlayerRollingState.h"
#include"Debug.h"

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
		// Phím ngồi đang được nhấn thì chuyển sang shield down
		if (keyboard->isKeyDown(PLAYER_SIT)) {
			if (player->hasShield)
				player->ChangeState(State::SHIELD_DOWN);
		}
		else {
 			player->ChangeState(State::JUMPING);
		}
		PlayerRollingState::curRollTime = 0;
	}

	// chuyển sang trạng thái đá
	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		player->ChangeState(State::KICKING);
		return;
	}

	if (!keyboard->isKeyDown(PLAYER_MOVE_LEFT) && !keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetVx(0);
	}
	else {
		if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
			player->SetVx(-PLAYER_NORMAL_SPEED);
		else {
			player->SetVx(PLAYER_NORMAL_SPEED);
		}
	}
	
	PlayerRollingState::curRollTime++;
	player->SetVy(player->vy + ADDED_SPEED);
}

BOOL PlayerRollingState::HasRollFullTime() {
	return curRollTime >= MAX_ROLLING_TIME;
}

void PlayerRollingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) {
		// chạm nền dưới
		if (side == CollisionSide::bottom) {
			player->OnStandingOnGround(object);
			PlayerRollingState::curRollTime = 0;
			return;
		}
	}

	if (object->type == Type::SOLIDBOX) {
       	player->OnCollisionWithSolidBox(object, collision);
		PlayerRollingState::curRollTime = 0;
		return;
	}
}

void PlayerRollingState::Update(float dt)
{
	this->InputHandler();
}

