#include "PlayerFloatingState.h"

PlayerFloatingState::PlayerFloatingState() {
	this->state = State::FLOATING;
	this->countAnimationFrame = 9;
}

void PlayerFloatingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	// bơi qua trái (cùng chiều dòng nước)
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->Float(Player::MoveDirection::RightToLeft);
		// nhấn phím nhảy thì nhảy lên bờ
		if (keyboard->isKeyDown(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
			this->countAnimationFrame = 9;
		}
		return;
	}
	else {
		// bơi qua phải
		if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
			player->Float(Player::MoveDirection::LeftToRight);
			if (keyboard->isKeyDown(PLAYER_JUMP)) {
				player->ChangeState(State::JUMPING);
				this->countAnimationFrame = 9;
			}
			return;
		}
	}
	// nhấn phím nhảy thì chuyển sang trạng thái nhảy
	if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		this->countAnimationFrame = 9;
		return;
	}
	// nhấn phím ngồi thì chuyển sang trạng thái lặn
	if (keyboard->getKeyPressedOnce(PLAYER_SIT)) {
		player->ChangeState(State::DIVING);
		this->countAnimationFrame = 9;
		return;
	}

	// trong trường hợp không có phím nào được nhấn thì vận tốc của player bằng vận tốc dòng nước
	player->SetVx(-WATER_SPEED, FALSE);
}

PlayerFloatingState::~PlayerFloatingState() {

}

void PlayerFloatingState::Update(float dt) {
	auto player = Player::getInstance();
	auto shield = Shield::getInstance();
	if (this->countAnimationFrame == 0 || player->GetPreviousState()->state == State::DIVING) {
		player->curanimation = new Animation(Tag::PLAYER, 38, 40);
	}
	else {
		this->countAnimationFrame--;
	}
	if (player->hasShield) {
		shield->SetShieldState(Shield::ShieldState::NotRender);
	}
	
	InputHandler();
}

void PlayerFloatingState::OnCollision(Object* object, collisionOut* collision) {
}

BoundingBox PlayerFloatingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 13;
	box.bottom = player->pos.y - 12;
	box.left = player->pos.x - 18;
	box.right = player->pos.x + 14;
	return box;
}