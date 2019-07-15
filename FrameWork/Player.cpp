#include"Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	animations[STANDING] = new Animation(PLAYER,0);
	animations[RUNNING] = new Animation(PLAYER, 1);
	this->state = STANDING;
	this->pos.x = 0;
	this->pos.y = SCREEN_HEIGHT / 2;
	this->tag = Tag::PLAYER;
	this->width = NORMALPLAYER_WIDTH;
	this->height = NORMALPALYER_HEIGHT;
	this->health = 100;
	this->energy = 0;
	curanimation = animations[this->state];
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
//
void Player::ChangeState(PlayerState* newplayerstate)
{
	delete playerstate;
	playerstate = newplayerstate;
	playerstate->state = newplayerstate->state;
	curanimation = animations[playerstate->state];
	this->state = playerstate->state;
}
int Player::getWidth()
{
	return this->curanimation->getWidth();
}

int Player::getHeight()
{
	return this->curanimation->getHeight();
}