#include "PlayerRunningState.h"
#include"Debug.h"


PlayerRunningState::PlayerRunningState()
{
	state = RUNNING;

}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	if (player == NULL || keyboard == NULL)
		return;
	int timePressedMove = 0;
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{

		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
		}
		return;
	}

	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{

		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
		}
		return;
	}

	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		if (player->hasShield) {
			player->ChangeState(State::SHIELD_ATTACK);
		}
	}

	// Không phím nào được nhấn thì chuyển sang trạng thái đứng yên
	player->ChangeState(State::STANDING);
}

void PlayerRunningState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;
	auto player = Player::getInstance();

	// collide with ground
	if (object->type == Type::GROUND) { 
		player->SetGroundCollision(new GroundCollision(object, side));
		if (side == CollisionSide::bottom)
		{
			DebugOut(L"\nRunning Bottom");
			player->ChangeState(State::STANDING);
			player->pos.y = object->pos.y + player->getHeight() / 2;
		}
		return;
	}

	// va chạm với solid box
	if (object->type == Type::SOLIDBOX) {
		player->SetVx(0);
		return;
	}
}




void PlayerRunningState::Update(float dt)
{
	this->InputHandler();
}


BoundingBox PlayerRunningState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 21;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 13;
	box.right = player->pos.x + 12;
	return box;
}