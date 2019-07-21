#include "PlayerShieldDownState.h"
#include"Shield.h"

PlayerShieldDownState::PlayerShieldDownState() {
	this->state = State::SHIELD_DOWN;
}

PlayerShieldDownState::~PlayerShieldDownState() {

}

void PlayerShieldDownState::InputHandler() {
	auto keyboard = KeyboardManager::getInstance();
	auto player = Player::getInstance();

	if (!keyboard->isKeyDown(PLAYER_SIT)) {
		if(player->onAirState==Player::OnAir::None)
			player->ChangeState(State::STANDING);
		else 
		{
			player->ChangeState(State::JUMPING);
		}
		return;
	}
	/*if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		return;
	}*/
}

void PlayerShieldDownState::Update(float dt) {
	InputHandler();

}

void PlayerShieldDownState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND && side == CollisionSide::bottom) {
   		player->SetAirState(Player::OnAir::None);
		player->SetVx(0);
		player->SetGroundCollision(new GroundCollision(object, side));
		player->pos.y = object->pos.y + player->getHeight() / 2 + Shield::getInstance()->getHeight() / 2;
	}
}

BoundingBox PlayerShieldDownState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 8;
	box.bottom = player->pos.y - 19;
	box.left = player->pos.x - 10;
	box.right = player->pos.x + 11;
	return box;
}