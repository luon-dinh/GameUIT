#include"GreenSolder.h"

GreenSolder::GreenSolder(RunType runType, float x, float y)
{
	this->tag = Tag::GREENSOLDIER;
	LoadAllAnimation();
	this->vy = 0;
	this->vx = 0;
	this->pos.x = x;
	this->pos.y = y;
	this->runType = runType;
	this->canJump = true;
	this->health = 2;
	this->duckingTime = 1500;
	this->runningTime = 1000;
	this->onAirState = OnAir::None;
	this->delayBeaten = 0;
	this->delayToDead = 0;
	this->currentAnimation = animations[State::STANDING];
	auto player = Player::getInstance();
	float deltax = this->pos.x - player->pos.x;
	if (deltax > 0)
		this->direction = Player::MoveDirection::RightToLeft;
	else
	{
		this->direction = Player::MoveDirection::LeftToRight;
	}
	if (runType == RunType::SPECIAL || runType == RunType::CANRUN)
		//this->stateName = State::RUNNING;
		ChangeState(State::RUNNING);
	else
	{
		ChangeState(State::STANDING);
		//this->stateName = State::STANDING;
	}
}

GreenSolder::~GreenSolder()
{

}

void GreenSolder::LoadAllAnimation()
{
	animations[State::RUNNING] = new Animation(Tag::GREENSOLDIER, 0, 3);// run
	animations[State::STANDING] = new Animation(Tag::GREENSOLDIER, 3, 4);//stand
	animations[State::DUCKING] = new Animation(Tag::GREENSOLDIER, 4, 5);//duck
	animations[State::DEAD] = new Animation(Tag::GREENSOLDIER, 5, 6);//dead
}
