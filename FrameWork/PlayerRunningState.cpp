#include "PlayerRunningState.h"



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

	// Không phím nào được nhấn thì chuyển sang trạng thái đứng yên
	player->ChangeState(State::STANDING);
}

void PlayerRunningState::OnCollision(Object* object, collisionOut* collision) {
	//auto side = collision->side;

	//// collide with ground
	//if (object->type == Type::GROUND) {
	//	if (side == CollisionSide::top || side == CollisionSide::bottom) {
	//		Player::getInstance()->SetVy(0);
	//	}
	//}
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
	box.right = player->pos.y + 12;
	return box;
}