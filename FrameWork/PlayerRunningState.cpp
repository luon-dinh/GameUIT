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
	if (KeyboardManager::getInstance()->isKeyDown(DIK_UP))
	{
		player->pos.y += player->vy;
		//player->ChangeState(State::JUMPING);
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		player->pos.y += player->vy;
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_LEFT))
	{
		if (player->direction == Player::MoveDirection::LeftToRight) {
			player->direction = Player::MoveDirection::RightToLeft;
			player->vx *= -1;
			return;
		}
		player->pos.x += player->vx;
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_RIGHT))
	{
		if (player->direction == Player::MoveDirection::RightToLeft) {
			player->direction = Player::MoveDirection::LeftToRight;
			player->vx *= -1;
			return;
		}
		player->pos.x += player->vx;
		return;
	}
	player->vx = 0;
	player->ChangeState(State::STANDING);
}

void PlayerRunningState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;

	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::top || side == CollisionSide::bottom) {
			Player::getInstance()->vy = 0;
		}
	}
}

void PlayerRunningState::Update(float dt)
{
	this->InputHandler();
	Player::getInstance()->curanimation->Update(dt);
}