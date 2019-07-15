#include"Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER,0);
	animations[RUNNING] = new Animation(PLAYER, 1);
	this->state = STANDING;
	this->pos.x = NORMALPLAYER_WIDTH/2;
	this->pos.y = NORMALPALYER_HEIGHT/2;
	this->tag = Tag::PLAYER;
	this->health = 100;
	this->energy = 0;
	curanimation = animations[this->state];

	LoadAllStates();
	this->playerstate = standingState;
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
	this->playerstate->Update(dt);
}

void Player::Render()
{
	curanimation->Render(this->pos.x,this->pos.y);
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
	case State::RUNNING: InnerChangeState(runningState);break;
	}
}

void Player::InnerChangeState(PlayerState* state) {
	this->state = playerstate->state;
	playerstate = state;
	curanimation = animations[playerstate->state];
}

int Player::getWidth()
{
	return this->curanimation->getWidth();
}

int Player::getHeight()
{
	return this->curanimation->getHeight();
}