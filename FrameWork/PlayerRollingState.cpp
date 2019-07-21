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
		player->SetVx(-PLAYER_NORMAL_SPEED);
		player->SetVx(0);
	}
	else {
		if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
			player->SetVx(-PLAYER_NORMAL_SPEED);
		else {
			player->SetVx(PLAYER_NORMAL_SPEED);
		}
	}
	
	PlayerRollingState::curRollTime += 15;
	player->vy += 0.1;
}

BOOL PlayerRollingState::HasRollFullTime() {
	return curRollTime >= MAX_ROLLING_TIME;
}

void PlayerRollingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) {

		// chạm vào ground trên đầu
		if (side == CollisionSide::top) {
			//player->SetVy(0);
		}
		else {
			// chạm nền dưới
			if (side == CollisionSide::bottom) {
				player->SetGroundCollision(new GroundCollision(object, side));
 				player->ChangeState(State::STANDING);
				player->pos.y = object->pos.y + player->getHeight() / 2;
			}
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
