#include "BulletWhiteFlyingRocketer.h"
#include "Debug.h"

BulletWhiteFlyingRocketer::BulletWhiteFlyingRocketer(MoveDirection robotDirection, int posX, int posY)
{
	player = Player::getInstance();
	animBullet90 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 0, 2, bulletFlashingRate);
	animBullet135 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 2, 4, bulletFlashingRate);
	animBullet180 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 4, 6, bulletFlashingRate);
	animBullet225 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 6, 8, bulletFlashingRate);
	animBullet270 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 8, 10, bulletFlashingRate);
	animBullet315 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 10, 12, bulletFlashingRate);
	animBullet0 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 12, 14, bulletFlashingRate);
	animBullet45 = new Animation(Tag::WHITEFLYINGROBOTBULLET, 14, 16, bulletFlashingRate);

	//Khởi tạo hướng đi cho viên đạn.
	if (robotDirection == MoveDirection::LeftToRight)
	{
		this->animation = animBullet90;
		currentDegree = 90;
	}
	else
	{
		this->animation = animBullet270;
		currentDegree = 270;
	}
	//Khởi tạo vị trí ban đầu của viên đạn.
	this->pos.x = posX;
	this->pos.y = posY;
}

BulletWhiteFlyingRocketer::~BulletWhiteFlyingRocketer()
{
	delete animBullet270;
	delete animBullet225;
	delete animBullet180;
	delete animBullet135;
	delete animBullet90 ;
	delete animBullet45 ;
	delete animBullet0	;
	delete animBullet315;
}

void BulletWhiteFlyingRocketer::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->tag)
	{
	case Tag::PLAYER:
	case Tag::STATICOBJECT:
		this->animation = animationExplode;
		this->vx = this->vy = 0;
		isExploded = true;
		curDelayTime = 0;
		break;
	case Tag::SHIELD:
		break;
	default:
		break;
	}
}

bool BulletWhiteFlyingRocketer::RedirectTowardPlayer()
{
	//Lấy radian của góc hiện tại của camera.
	double curRadian = currentDegree * PI / 180;
	//Tính góc cần xoay.
	double alphaBullet = currentDegree;
	double deltaX = player->pos.x - this->pos.x;
	double deltaY = player->pos.y - this->pos.y;
	double alphaPlayer = atan2(deltaX, deltaY) * 180 / PI;
	if (alphaPlayer < 0)
		alphaPlayer += 360;
	if (alphaPlayer < 0.0001)
		alphaPlayer = 0;
	//Đây là góc mà viên đạn cần xoay.
	double degreeNeedToSpin = alphaPlayer - alphaBullet;
	currentDegree += (abs(degreeNeedToSpin)> maxRotateDegree) ? ((degreeNeedToSpin > 0) ? (maxRotateDegree) : (-maxRotateDegree)) : (degreeNeedToSpin);
	//Cập nhập lại vận tốc theo 2 phương x,y.
	auto convertToRadian = [](double degree) {return degree * PI / 180; };
	this->vx = sin(convertToRadian(currentDegree)) * BulletSpeed;
	this->vy = cos(convertToRadian(currentDegree)) * BulletSpeed;
	if (degreeNeedToSpin > 0)
		return true;
	return false;
}

void BulletWhiteFlyingRocketer::Update(float dt)
{
	curDelayTime += dt;
	this->animation->Update(dt);

	//Nếu đã nổ tung rồi và đã hết thời gian chờ thì ta deactivate nó luôn.
	if (isExploded)
	{
		if (curDelayTime > delayDisappear)
			DeactivateObjectInGrid();
		return;
	}

	//Nếu vẫn còn số lần chuyển hướng và đã delay đủ thì mới chuyển hướng.
	if (redirectTime < maxRedirect && curDelayTime >= minTimeRedirect)
	{
		curDelayTime = 0;
		RedirectTowardPlayer();
			/*++redirectTime;*/
	}
	//Chuyển animation.
	this->animation = getAnimOnDeg();
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	PrintDebug("\nCurrent Degree : ");
	PrintDebugNumber(currentDegree);
}

BoundingBox BulletWhiteFlyingRocketer::getBoundingBox()
{
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.left = this->pos.x - 8;
	box.right = this->pos.x;
	if (this->direction == MoveDirection::LeftToRight)
	{
		box.right = this->pos.x + 8;
	}
		
	else if (this->direction == MoveDirection::RightToLeft)
	{
		box.left = this->pos.x;
	}
	
	box.top = this->pos.y + 8;
	box.bottom = this->pos.y;
	return box;
}

Animation* BulletWhiteFlyingRocketer::getAnimOnDeg()
{
	double currentDegree = this->currentDegree;
	while (currentDegree > 360)
		currentDegree -= 360;
	//Để hiển thị thêm đẹp, ta cho một function định nghĩa nằm trong khoảng delta.
	auto DegreeInRange = [currentDegree](double num) {return (num - 20 <= currentDegree) && (currentDegree <= num + 20); };
	if (DegreeInRange(0))
		return animBullet0;
	if (currentDegree < 90)
		return animBullet45;
	if (DegreeInRange(90))
		return animBullet90;
	if (currentDegree < 180)
		return animBullet135;
	if (DegreeInRange(180))
		return animBullet180;
	if (currentDegree < 270)
		return animBullet225;
	if (DegreeInRange(270))
		return animBullet270;
	return animBullet315;
}