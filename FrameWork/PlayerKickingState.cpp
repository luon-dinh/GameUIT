#include "PlayerKickingState.h"



PlayerKickingState::PlayerKickingState()
{
	state = State::KICKING;
	this->curKickTime = 0;
}


PlayerKickingState::~PlayerKickingState()
{
}

void PlayerKickingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	
	if (this->curKickTime > MAX_KICKING_TIME) {
		// trạng thái trước đó là ROLLING thì chuyển về lại ROLLING
		if (player->GetPreviousState()->state == State::ROLLING)
			player->ChangeState(State::ROLLING);
		else
			player->ChangeState(State::JUMPING);
		this->curKickTime = 0;
		return;
	}
	this->curKickTime += 30;

	if (player->IsReachMaxJump()) {
		player->SetVy(0);
	}
}



void PlayerKickingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;
	auto player = Player::getInstance();

	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom) {
			player->ChangeState(State::STANDING);
		}
	}
}

void PlayerKickingState::Update(float dt)
{
	this->InputHandler();
}

BoundingBox PlayerKickingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 12;
	box.bottom = player->pos.y - 13;
	box.left = player->pos.x - 30;
	box.right = player->pos.x + 10;
	return box;
}
