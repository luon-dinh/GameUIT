#include"PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	//Player::getInstance()->state = standing;
	state = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
	Player* player = Player::getInstance();
	player->vy = player->vy - 0.035 ;
	player->pos.y = player->pos.y + player->vy;
	Player::getInstance()->curanimation->Update(dt);
}

void PlayerStandingState::InputHandler()
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

void PlayerStandingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;

	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::top || side == CollisionSide::bottom) {
			Player::getInstance()->vy = 0;
		}
	}
}