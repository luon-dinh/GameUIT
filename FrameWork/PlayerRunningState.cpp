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

	if (keyboard->isKeyDown(DIK_DOWN))
	{
		player->pos.y += player->vy;
		return;
	}
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		return;
	}
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		return;
	}
	player->SetVx(0);
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
	Player::getInstance()->AddPos();
	Player::getInstance()->curanimation->Update(dt);
}