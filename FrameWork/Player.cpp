#include"Player.h"
#include"Camera.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER, 0);
	animations[RUNNING] = new Animation(PLAYER, 1, 4, TIME_PER_FRAME / 4);
	this->state = STANDING;
	this->pos.x = 0;
	this->pos.y = 50;
	this->tag = Tag::PLAYER;
	this->health = 100;
	this->energy = 0;
	this->vx = 0;
	this->vy = 0;
	this->onAirState = OnAir::None;
	this->direction = MoveDirection::LeftToRight;
	curanimation = animations[this->state];

	LoadAllStates();
}

void Player::LoadAllStates() {
	this->runningState = new PlayerRunningState();
	this->standingState = new PlayerStandingState();
}


Player::~Player()
{

}


void Player::Update(float dt)
{
	this->AddPos();
	// Update state
	this->playerstate->Update(dt);
}

void Player::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x,pos.y,0));
	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from right to left
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
	}
	else {
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal);
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




void Player::KeyDown()
{


	if (KeyboardManager::getInstance()->isKeyDown(DIK_UP))
	{
		
	}

	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		
	}

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
			this->accelerate.x = -PLAYER_ACCELERATE;
		}
	}
	else {
		if (vx > 0) {
			this->direction = MoveDirection::LeftToRight;
			this->accelerate.x = PLAYER_ACCELERATE;
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

void Player::AddPos() {
	this->accelerate.x = 0;
	AddPosX();
	AddPosY();
}

void Player::SetMoveDirection(MoveDirection moveDir) {
	auto curMoveDir = this->direction;
	this->direction = moveDir;
	if (this->direction != curMoveDir) {
		if (this->direction == MoveDirection::LeftToRight)
			SetAccelerate(D3DXVECTOR2(PLAYER_ACCELERATE, this->accelerate.y));
		else {
			SetAccelerate(D3DXVECTOR2(-PLAYER_ACCELERATE, this->accelerate.y));
		}
	}
}

void Player::SetAccelerate(D3DXVECTOR2 accelerate) {
	this->accelerate.x = accelerate.x;
	this->accelerate.y = accelerate.y;
}

void Player::SetAirState(OnAir onAirState) {
	auto oldState = this->onAirState;
	this->onAirState = onAirState;

	if (this->onAirState == OnAir::None) {
		this->accelerate.y = 0;
		this->vy = 0;
		return;
	}
	if (this->onAirState == OnAir::Jumping) {
		this->accelerate.y = -PLAYER_ACCELERATE;
		this->vy = PLAYER_NORMAL_SPEED;
		return;
	}
	if (this->onAirState == OnAir::Falling) {
		this->vy = 0;
		this->accelerate.y = PLAYER_ACCELERATE;
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