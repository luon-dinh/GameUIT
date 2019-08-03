#include "DisappearingPlatform.h"
#include "Camera.h"

DisappearingPlatform::DisappearingPlatform(int _posX, int _posY)
{
	firstSplitDelay = new Delay(firstTimeSplitDelayTime);
	normalSplitDelay = new Delay(normalSplitDelayTime);
	joiningTimeDelayPhase1 = new Delay(joiningTimeDelayPhase1Time);
	joiningTimeDelayPhase2 = new Delay(joiningTimeDelayPhase2Time);
	renderDelay = new Delay(flashingDelayTime);
	brickSprite = new Sprite(Tag::SPLIT_BRICK, 0, 0, 16, 16);
	this->pos.x = _posX;
	this->pos.y = _posY;
	this->vx = this->vy = 0;
	isCollidable = true;
	this->type = Type::PLATFORM;
	this->tag = Tag::DISAPPEARING_PLATFORM;
}

DisappearingPlatform::~DisappearingPlatform()
{
	if (firstSplitDelay != nullptr)
		delete firstSplitDelay;
	if (normalSplitDelay != nullptr)
		delete normalSplitDelay;
	if (joiningTimeDelayPhase1 != nullptr)
		delete joiningTimeDelayPhase1;
	if (joiningTimeDelayPhase2 != nullptr)
		delete joiningTimeDelayPhase2;
	if (renderDelay != nullptr)
		delete renderDelay;
}

void DisappearingPlatform::Update(float dt)
{
	//Nếu platform chưa được activate.
	if (!isPlatformActivated && isCollidable && !isSplitting)
	{
		//Chờ đến khi split lần đầu.
		if (firstSplitDelay->GetDelayStatus(dt))
		{
			isPlatformActivated = true;
			isSplitting = true;
			isCollidable = false;
		}
	}
	else if (isPlatformActivated && isCollidable && !isSplitting)
	{
		isRenderable = true;
		if (normalSplitDelay->GetDelayStatus(dt))
		{
			isSplitting = true;
			isCollidable = false;
		}
	}
	//Nếu đang split thì ta đợi đến đủ thời gian unsplit.
	else if (isPlatformActivated && !isCollidable && isSplitting)
	{
		if (joiningTimeDelayPhase1->GetDelayStatus(dt))
		//Hết thời gian split thì nó bắt đầu ghép lại.
			isSplitting = false;
	}
	//Nếu vẫn chưa join vào với nhau.
	else if (isPlatformActivated && !isCollidable && !isSplitting)
	{
		if (joiningTimeDelayPhase2->GetDelayStatus(dt))
			isCollidable = true;
	}

	//Xét việc render chớp chớp.
	if (!isCollidable)
	{
		if (isRenderable && renderDelay->GetDelayStatus(dt))
			isRenderable = false;
		else if (!isRenderable && renderDelay->GetDelayStatus(dt))
			isRenderable = true;
	}
}

void DisappearingPlatform::Render()
{
	if (!isRenderable)
		return;

	D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
	
	//Kiểm tra xem platform đang ở trạng thái nào để render cho phù hợp.
	if (isCollidable)
	{
		brickSprite->Render(viewPort.x - 8, viewPort.y);
		brickSprite->Render(viewPort.x + 8, viewPort.y);
	}
	else if (isSplitting)
	{
		brickSprite->Render(viewPort.x - 16 - 8, viewPort.y);
		brickSprite->Render(viewPort.x + 16 + 8, viewPort.y);
	}
	else if (!isSplitting)
	{
		brickSprite->Render(viewPort.x - 16, viewPort.y);
		brickSprite->Render(viewPort.x + 16, viewPort.y);
	}
}

BoundingBox DisappearingPlatform::getBoundingBox()
{
	BoundingBox box;
	box.vx = box.vy = 0;
	box.top = this->pos.y + platformHeight;
	box.bottom = this->pos.y - platformHeight;
	box.left = this->pos.y - platformWidth;
	box.right = this->pos.y + platformWidth;
	return box;
}