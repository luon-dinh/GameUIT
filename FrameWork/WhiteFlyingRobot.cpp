#include "WhiteFlyingRobot.h"
#include "SceneManager.h"

WhiteFlyingRobot::WhiteFlyingRobot(int posX, int posY)
{
	this->tag = Tag::WHITEFLYINGROBOT;
	this->direction = MoveDirection::LeftToRight;
	LoadAllAnimation();
	player = Player::getInstance();
	LoadAllAnimation();
	robotState = State::FLYING;
	currentAnimation = stateAnim[robotState];
	this->pos.x = posX;
	this->pos.y = posY;
	isDead = false;
}

WhiteFlyingRobot::~WhiteFlyingRobot()
{
	//Xoá sạch map.
	for (auto anim : stateAnim)
		delete anim.second;
}

void WhiteFlyingRobot::Update(float dt)
{
	delayTime += dt;
	if (delayTime < delayFlyingTime)
		return;
	delayTime = 0;
	//Mỗi lần xoay 1 góc 1 độ.
	currentDegree = fmod(currentDegree + angularVelocity, 360);

	auto inRange = [](double value, double realValue) {return (value - 1 <= realValue) && (realValue <= value + 1); };

	//Quái chỉ bắn khi ở góc 0 độ và góc 90 độ.
	if (inRange(0,currentDegree) || inRange(90,currentDegree))
	{
		SceneManager::getInstance()->AddObjectToCurrentScene(new BulletWhiteFlyingRocketer(this->direction, this->pos.x, this->pos.y));
	}

	//Cập nhật lại tốc độ bay hiện tại dựa vào góc.
	auto convertToRad = [](double degree) {return degree * PI / 180; };
	this->vx = cos(convertToRad(currentDegree)) * VXMax;
	this->vy = -sin(convertToRad(currentDegree)) * VYMax;
	//Cập nhật lại phương hướng (hướng trái hay phải) của enemy.
	if (player->pos.x > this->pos.x)
		this->direction = MoveDirection::LeftToRight;
	else
		this->direction = MoveDirection::RightToLeft;
	//Cập nhật lại vị trí theo tốc độ.
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	//Cập nhật animation.
	this->currentAnimation->Update(dt);
}

void WhiteFlyingRobot::Render()
{
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (this->direction)
		{
		case Player::MoveDirection::LeftToRight:
			this->currentAnimation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->currentAnimation->Render(pos);
			break;
		default:
			break;
		}
	}
}

void WhiteFlyingRobot::LoadAllAnimation()
{
	//Load animation tương ứng với trạng thái.
	Animation* flyingAnim = new Animation(Tag::WHITEFLYINGROBOT, 0, 2, delayFlyingSprite);
	Animation* fallingAnim = new Animation(Tag::WHITEFLYINGROBOT, 2, 4, delayFallingAnim);
	std::pair<State, Animation*> flyingPair(State::FLYING, flyingAnim);
	std::pair<State, Animation*> spinningPair(State::FALLING, fallingAnim);
	stateAnim.insert(flyingPair);
	stateAnim.insert(spinningPair);
}

void WhiteFlyingRobot::OnCollision(Object* object, collisionOut* colout)
{

}

bool WhiteFlyingRobot::OnRectCollided(Object* object, CollisionSide side)
{
	return true;
}

void WhiteFlyingRobot::OnNotCollision(Object* object)
{

}