#include "PlayerFallingState.h"



PlayerFallingState::PlayerFallingState()
{
	state = State::FALLING;
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->InputHandler();
	Player* player = Player::getInstance();
	player->pos.y = player->pos.y + player->vy;
	player->vy -= 0.035;
	Player::getInstance()->curanimation->Update(dt);
}

void PlayerFallingState::InputHandler()
{
	Player* player = Player::getInstance();
	if (KeyboardManager::getInstance()->isKeyDown(DIK_UP))
	{
		player->vy = 10;
		player->pos.y += player->vy;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		player->vy = -10;
		player->pos.y += player->vy;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_LEFT))
	{
		player->vx = -10;
		player->ChangeState(State::RUNNING);
		player->direction = Player::MoveDirection::RightToLeft;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_RIGHT))
	{
		player->vx = 10;
		player->ChangeState(State::RUNNING);
		player->direction = Player::MoveDirection::LeftToRight;
	}
}

void PlayerFallingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;

	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom) {
			Player *player = Player::getInstance();
			player->pos.y = player->pos.y + collision->collisionTime*player->vy;
			player->vy = 0;
			player->ChangeState(State::STANDING);
		}
	}
}