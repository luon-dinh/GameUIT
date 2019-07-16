#include"Player.h"
#include"Camera.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER, 0,1);
	animations[RUNNING] = new Animation(PLAYER, 1, 4);
	animations[JUMPING] = new Animation(PLAYER, 2, 1);

	this->pos.x = 30;
	this->pos.y = 200;
	this->tag = Tag::PLAYER;
	this->health = 100;
	this->energy = 0;
	this->vx = 0;
	this->vy = 0;
	this->direction = MoveDirection::LeftToRight;

	LoadAllStates();

	ChangeState(State::JUMPING);
	SetAirState(OnAir::Falling);
}

void Player::LoadAllStates() {
	this->runningState = new PlayerRunningState();
	this->standingState = new PlayerStandingState();
	this->jumpingState = new PlayerJumpingState();
}


Player::~Player()
{

}


void Player::Update(float dt)
{
	// Update lại vị trí của position sau mỗi frame
	this->UpdatePosition();
	// Update state
	this->playerstate->Update(dt);
	// Update animation
	this->curanimation->Update(dt);
}

void Player::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x,pos.y,0));
	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from right to left
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
	switch (stateName) {
	case State::STANDING: InnerChangeState(standingState);break;
	case State::RUNNING:  InnerChangeState(runningState);break;
	case State::JUMPING: 
	{
		InnerChangeState(jumpingState);
		this->SetAirState(OnAir::Jumping);
		break;
	}
	}
}

void Player::InnerChangeState(PlayerState* state) {
	this->state = state->state;
	playerstate = state;
	curanimation = animations[playerstate->state];
}

void Player::SetVx(float vx) {
	this->vx = vx;
	if (vx == 0)
		return;
	if (this->direction == MoveDirection::LeftToRight) {
		if (vx < 0) {
			this->direction = MoveDirection::RightToLeft;
			this->accelerate.x = -GROUND_GRAVITY;
		}
	}
	else {
		if (vx > 0) {
			this->direction = MoveDirection::LeftToRight;
			this->accelerate.x = GROUND_GRAVITY;
		}
	}
}

void Player::SetVy(float vy) {
	this->vy = vy;
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
	this->vy += this->accelerate.y;
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
		//if (this->direction == MoveDirection::LeftToRight) {
		//	this->vx = PLAYER_NORMAL_SPEED;
		//}
		//else {
		//	this->vx = -PLAYER_NORMAL_SPEED;
		//}
		//this->vx *= -1;
	}
}

void Player::SetAccelerate(D3DXVECTOR2 accelerate) {
	this->accelerate.x = accelerate.x;
	this->accelerate.y = accelerate.y;
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