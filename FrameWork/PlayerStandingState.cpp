#include"PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	//Player::getInstance()->state = standing;
	state = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
}

void PlayerStandingState::InputHandler()
{
	Player* player = Player::getInstance();
	if (KeyboardManager::getInstance()->isKeyDown(DIK_UP))
	{
		player->pos.y += player->vy;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		player->pos.y += player->vy;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_LEFT))
	{
		player->vx = 10;
		player->ChangeState(State::RUNNING);
		player->pos.x += player->vx;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_RIGHT))
	{
		player->vx = -10;
		player->ChangeState(State::RUNNING);
		player->pos.x += player->vx;
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