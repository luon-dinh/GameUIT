#include "PlayerRunningState.h"



PlayerRunningState::PlayerRunningState()
{

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
		player->ChangeState(State::JUMPING);
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		player->pos.y += player->vy;
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_LEFT))
	{
		player->pos.x += player->vx;
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_RIGHT))
	{
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
}