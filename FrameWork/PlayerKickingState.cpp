#include "PlayerKickingState.h"
#include"Debug.h"


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

	int timePressedJump = 0;
	// xét thời gian đã press phím jump
	if (player->GetOnAirState() == Player::OnAir::Jumping) {
		//phím Jump đã được nhấn từ trước
		if (!keyboard->getKeyPressedOnce(PLAYER_JUMP, timePressedJump) && timePressedJump > 0) {
			//chuyển sang trạng thái roll
			if (timePressedJump / 10 > MAX_KICKING_TIME) {
				player->ChangeState(State::ROLLING);
				return;
			}
			player->SetVy(player->vy + 0.15);
		}
	}

	//  Đổi hướng qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
	}

	// Đổi hướng qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
	}

	this->curKickTime++;

	/*if (player->IsReachMaxJump()) {
		player->SetVy(0);
	}*/
}



void PlayerKickingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) {
		// chạm vào ground trên đầu
		if (side == CollisionSide::top) {
			//player->SetVy(0);
		}
		else {
			// chạm nền dưới
			if (side == CollisionSide::bottom ) {
				player->OnStandingOnGround(object);
				DebugOut(L"\nState Now:\n");
				PrintDebugNumber(player->state);
			}
		}
	}
	if (object->type == Type::WATERRL) {
		player->OnCollisionWithWater(object, collision);
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
	if (player->direction == Player::MoveDirection::RightToLeft)
	{
		box.left = player->pos.x - 30;
		box.right = player->pos.x;
	}
	else if (player->direction == Player::MoveDirection::LeftToRight)
	{
		box.left = player->pos.x;
		box.right = player->pos.x + 30;
	}
	/*box.left = player->pos.x - 11;
	box.right = player->pos.x + 11;*/
	return box;
}
