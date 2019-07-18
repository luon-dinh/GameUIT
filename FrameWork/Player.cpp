#include"Player.h"
#include"Camera.h"

Player* Player::instance = NULL;

Player::Player()
{
	LoadAllAnimations();
	LoadAllStates();

	this->pos.x = 30;
	this->pos.y = 80;
	this->tag = Tag::PLAYER;
	this->health = 100;
	this->energy = 0;
	this->vx = 0;
	this->vy = 0;
	this->direction = MoveDirection::LeftToRight;

	this->state = State::JUMPING;
	this->playerstate = playerStates[State::JUMPING];
	this->curanimation = animations[this->state];
	this->prevState = NULL;
}

PlayerState* Player::GetPreviousState() {
	return this->prevState;
}

void Player::SetPreviousState(State stateName) {
	this->prevState = playerStates[stateName];
}

void Player::LoadAllAnimations() {
	animations[STANDING] = new Animation(PLAYER, 0, 1);
	animations[RUNNING] = new Animation(PLAYER, 1, 5);
	animations[JUMPING] = new Animation(PLAYER, 7, 8);
	animations[DUCKING]	= new Animation(PLAYER, 6, 7);
	animations[DUCKING_PUNCHING] = new Animation(PLAYER, 15, 17);
	animations[SHIELD_UP] = new Animation(PLAYER, 2, 1);
	animations[ROLLING] = new Animation(PLAYER, 8, 10);
	animations[KICKING] = new Animation(PLAYER, 10, 11);
}

void Player::LoadAllStates() {
	this->playerStates[State::STANDING] = new PlayerStandingState();
	this->playerStates[State::RUNNING]  = new PlayerRunningState();
	this->playerStates[State::JUMPING]  = new PlayerJumpingState();
	this->playerStates[State::DUCKING]  = new PlayerSittingState();
	this->playerStates[State::DUCKING_PUNCHING] = new PlayerDuckingPunchingState();
	this->playerStates[State::SHIELD_UP] = new PlayerShieldUpState();
	this->playerStates[State::KICKING] = new PlayerKickingState();
	this->playerStates[State::ROLLING] = new PlayerRollingState();
}



Player::~Player()
{

}


BoundingBox Player::getBoundingBox()
{
	return this->playerstate->getBoundingBox();
}

void Player::Update(float dt)
{
	if (this->pos.y <= 30) {
		this->pos.y = 30;
	}
	// Update state
	this->playerstate->Update(dt);
	// Update lại vị trí của position sau mỗi frame
	this->UpdatePosition();

	// Update animation
	this->curanimation->Update(dt);
}

void Player::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x,pos.y,0));
	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from left to right
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y),TransformationMode::FlipHorizontal);
	}
	else {
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
	}
}

void Player::OnCollision(Object* object, collisionOut* collisionOut) {
	this->playerstate->OnCollision(object, collisionOut);
}

Player* Player::getInstance()
{
	if (!instance)
		instance = new Player();
	return instance;
}


void Player::ChangeState(PlayerState* newplayerstate)
{
	delete playerstate;
	playerstate = newplayerstate;
	playerstate->state = newplayerstate->state;
	curanimation = animations[playerstate->state];
	this->state = playerstate->state;
}

void Player::ChangeState(State stateName) {
	if (this->state == stateName)
		return;

	InnerChangeState(stateName);

	// thay đổi riêng biệt cho từng loại state
	switch (stateName) {
		case State::STANDING: {
			this->SetAirState(Player::OnAir::None);
			this->SetVx(0);
			this->SetVy(0);
			break;
		}
		case State::RUNNING:
		{
			this->SetAirState(Player::OnAir::None);
			if (this->direction == MoveDirection::LeftToRight)
				SetVx(PLAYER_NORMAL_SPEED);
			else {
				SetVx(-PLAYER_NORMAL_SPEED);
			}
			break;
		}
		case State::JUMPING: 
		{
			// nếu trước đó đang falling tiếp tục là falling
			if (this->onAirState == OnAir::Falling) {
				this->vy += 2;
				return;
			}
			this->SetAirState(OnAir::Jumping);
			break;
		}
	}
}

void Player::InnerChangeState(State stateName) {
	SetPreviousState(this->state);
	this->state = stateName;
	this->playerstate = playerStates[stateName];
	curanimation = animations[stateName];
}

void Player::SetVx(float vx) {
	this->vx = vx;
	if (vx == 0)
		return;
	if (this->direction == MoveDirection::LeftToRight) {
		if (vx < 0) {
			this->direction = MoveDirection::RightToLeft;
		}
	}
	else {
		if (vx > 0) {
			this->direction = MoveDirection::LeftToRight;
		}
	}
}

void Player::SetVy(float vy) {
	this->vy = vy;
	if (this->vy == 0) {
		// Nếu vận tốc bằng 0 khi đang nhảy thì rơi xuống lại
		if (this->onAirState == OnAir::Jumping)
			SetAirState(OnAir::Falling);
	}
}


void Player::SetVelocity(D3DXVECTOR2 veloc) {
	this->vx = veloc.x;
	this->vy = veloc.y;
}

void Player::AddPosX() {
	this->vx += this->accelerate.x;
	this->pos.x += this->vx;
}

void Player::AddPosY() {
	this->SetVy(this->vy + this->accelerate.y);
	this->pos.y += this->vy;
}

void Player::UpdatePosition() {
	this->accelerate.x = 0;
	AddPosX();
	AddPosY();
}

void Player::SetMoveDirection(MoveDirection moveDir) {
	auto curMoveDir = this->direction;
	this->direction = moveDir;
	if (this->direction != curMoveDir) {
		this->vx *= -1;
	}
}

void Player::SetAccelerate(D3DXVECTOR2 accelerate) {
	this->accelerate.x = accelerate.x;
	this->accelerate.y = accelerate.y;
}

Player::OnAir Player::GetOnAirState() {
	return this->onAirState;
}

void Player::SetAirState(OnAir onAirState) {
	if (this->onAirState == onAirState)
		return;
	auto oldState = this->onAirState;
	this->onAirState = onAirState;

	if (this->onAirState == OnAir::None) {
		this->accelerate.y = 0;
		this->vy = 0;
		return;
	}
	if (this->onAirState == OnAir::Jumping) {
		this->accelerate.y = -GROUND_GRAVITY;
		this->vy = PLAYER_JUMP_SPEED;
		return;
	}
	if (this->onAirState == OnAir::Falling) {
		this->vy = 0;
		this->accelerate.y = -GROUND_GRAVITY;
	}
}


int Player::getWidth()
{
	return this->curanimation->getWidth();
}

int Player::getHeight()
{
	return this->curanimation->getHeight();
}