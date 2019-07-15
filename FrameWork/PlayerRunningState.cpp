#include "PlayerRunningState.h"



PlayerRunningState::PlayerRunningState()
{

}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::InputHandler()
{
	if (KeyboardManager::getInstance()->isKeyDown(DIK_UP))
	{
		Player::getInstance()->pos.y++;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		Player::getInstance()->pos.y--;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_LEFT))
	{
		Player::getInstance()->pos.x--;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_RIGHT))
	{
		Player::getInstance()->pos.x++;
	}
}

void PlayerRunningState::OnCollision(Object* object, collisionOut* collision) {
	BoundingBox bounding = object->getBoundingBox();
}

void PlayerRunningState::Update(float dt)
{
	this->InputHandler();
}