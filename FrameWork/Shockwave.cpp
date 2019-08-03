#include "Shockwave.h"
#include "Camera.h"
#include "Debug.h"


Shockwave::Shockwave(int posX, int posY)
{
	this->pos.x = posX;
	this->pos.y = posY;
	this->vx = this->vy = 0;
	this->tag = Tag::ELECTRIC_SHOCKWAVE;
	this->type = Type::SHOCKWAVE;
	waveAnim = new Animation(Tag::ELECTRIC_SHOCKWAVE, 0, 6, shockWaveFlashingDelayTime);
	enableDelay = new Delay(timeEnabled);
	disableDelay = new Delay(timeDisabled);
}

Shockwave::~Shockwave()
{
	if (waveAnim != nullptr)
		delete waveAnim;
	if (enableDelay != nullptr)
		delete enableDelay;
	if (disableDelay != nullptr)
		delete disableDelay;
}

void Shockwave::Update(float dt)
{
	if (isShockwaveActivated)
	{
		waveAnim->Update(dt);
		//Nếu đã đủ thời gian bật thì ta tắt.
		if (enableDelay->GetDelayStatus(dt))
		{
			isShockwaveActivated = false;
		}
	}
	else
	{
		//Nếu đã đủ thời gian tắt thì ta bật.
		if (disableDelay->GetDelayStatus(dt))
		{
			isShockwaveActivated = true;
		}
	}
}

void Shockwave::Render()
{
	if (isShockwaveActivated)
	{
		D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
		waveAnim->Render(viewPort);
	}
}

BoundingBox Shockwave::getBoundingBox()
{
	BoundingBox box;
	box.vx = box.vy = 0;
	return box;
}