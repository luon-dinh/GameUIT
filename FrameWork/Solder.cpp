#include "Solder.h"
#include"Camera.h"

Solder::Solder(bool movable)
{
	this->movable = movable;
	this->tag = Tag::BLUESOLDIER;
	LoadAllAnimation();
	timeCurrentState = 0;
	this->vy = 0;
	this->vx = ENEMY_SPEED;
	bullet = BulletManager::getInstance()->CreateBullet(Tag::BLUESOLDERBULLET);
	if(!movable)
		ChangeState(State::STANDING);
	else
	{
		ChangeState(State::RUNNING);
	}
}

Solder::~Solder() {
	if (bullet)
		delete bullet;
}


void Solder::Shoot() {
	bullet->existTime = 0;
	bullet->SetActive(true);
	bullet->direction = this->direction;
	bullet->pos.y = this->getBoundingBox().top - 4;
	bullet->pos.x = this->pos.x;
}

void Solder::OnCollision(Object* object, collisionOut* colOut) {
	
}

void Solder::Update(float dt)
{
	

	if (bullet->GetActive()==true)
	{
		bullet->Update(dt);
	}

	if (!isDead)
	{
		if (stateName != State::RUNNING)
		{
			auto player = Player::getInstance();
			float deltax = this->pos.x - player->pos.x;
			if (deltax > 0)
				this->direction = Player::MoveDirection::RightToLeft;
			else
			{
				this->direction = Player::MoveDirection::LeftToRight;
			}
		}
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		// nếu đang ở trạng thái beaten và hết thời gian của trạng thái beaten thì blue solder bị chết
		if (stateName == State::BEATEN&&timeCurrentState>=ENEMY_BEATEN_TIME)
			isDead = true;
		auto shield = Shield::getInstance();
		//nếu bị shield đánh chuyển sang beaten---> test 
		if (Collision::getInstance()->IsCollide(shield->getBoundingBox(), this->getBoundingBox()) && shield->state == Shield::ShieldState::Attack)
			ChangeState(State::BEATEN);
		this->curentAnimation->Update(dt);
		//tùy theo trạng thái hiện tại mà thay đổi trạng thái
		switch (this->stateName)
		{
		case State::DUCKING:
			if (timeCurrentState >= BLUE_SOLDER_DUCKING_TIME)
			{
				ChangeState(State::STANDING);
			}
			else
			{
				timeCurrentState += dt;
			}
			break;
		case State::STANDING:
			if (timeCurrentState < BLUE_SOLDER_STANDING_TIME)
			{
				if(timeCurrentState+dt>=BLUE_SOLDER_STANDING_TIME/2&&timeCurrentState<BLUE_SOLDER_STANDING_TIME/2)
					Shoot();
				timeCurrentState += dt;
			}
			else
			{
				ChangeState(State::DUCKING);
			}
			break;
		case State::RUNNING:
			break;
		default:
			timeCurrentState += dt;
			break;
		}
	}

}

void Solder::Render()
{
	if (bullet->GetActive())
		bullet->Render();
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (this->direction)
		{
		case Player::MoveDirection::LeftToRight:
			this->curentAnimation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->curentAnimation->Render(pos);
			break;
		default:
			break;
		}
	}
}


void Solder::LoadAllAnimation()
{
	animations[State::RUNNING] = new Animation(Tag::BLUESOLDIER, 0, 3);// run
	animations[State::STANDING] = new Animation(Tag::BLUESOLDIER, 3);//stand
	animations[State::DUCKING] = new Animation(Tag::BLUESOLDIER, 4);//duck
	animations[State::BEATEN] = new Animation(Tag::BLUESOLDIER, 5);//beaten
}

void Solder::ChangeState(State stateName)
{
	
	switch (stateName)
	{
	case State::STANDING:
		this->curentAnimation = animations[State::STANDING];
		this->vx = this->vy = 0;
		isDead = false;
		break;
	case State::RUNNING:
		this->curentAnimation = animations[State::RUNNING];
		if (this->direction == Player::MoveDirection::LeftToRight)
			this->vx = ENEMY_SPEED* PLAYER_NORMAL_SPEED;
		else
			this->vx = -ENEMY_SPEED*PLAYER_NORMAL_SPEED;
		isDead = false;
		break;
	case State::DUCKING:
		this->curentAnimation = animations[State::DUCKING];
		this->vx = this->vy = 0;
		isDead = false;
		break;
	case State::BEATEN:
		this->curentAnimation = animations[State::BEATEN];
		this->vx = this->vy = 0;
		if (this->direction == Player::MoveDirection::LeftToRight)
			this->pos.x -= 3;
		else
		{
			this->pos.x += 3;
		}
		break;
	default:
		break;
	}
	this->stateName = stateName;
	timeCurrentState = 0;
}
