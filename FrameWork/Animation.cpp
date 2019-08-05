#include"Animation.h"
void Animation::Render(float x, float y, D3DCOLOR color)
{
	if (sprites.size()==0)
		return;
	if (sprites[curframeindex] != NULL)
	{
		sprites[curframeindex]->Render(x, y, color);
	}
}

void Animation::Render(D3DXVECTOR2 pos, D3DCOLOR color)
{
	Render(pos.x, pos.y, color);
}

void Animation::Render(D3DXVECTOR3 pos, D3DCOLOR color)
{
	Render(D3DXVECTOR2(pos.x,pos.y), color);
}

void Animation::Render(float x, float y, int first, int last, D3DCOLOR color)
{
	//for(int i=0;)

}

void Animation::Render(D3DXVECTOR2 pos, TransformationMode transMode, D3DCOLOR color, float scaleRatio) {
	if (sprites.size() == 0)
		return;
	if (sprites[curframeindex] != NULL)
	{
		sprites[curframeindex]->Render(transMode, scaleRatio, pos, color);
	}
}

void Animation::Render(D3DXVECTOR2 pos, float scaleRatioX, float scaleRatioY, D3DCOLOR color) {
	if (sprites.size() == 0)
		return;
	if (sprites[curframeindex] != NULL)
	{
		sprites[curframeindex]->Render(scaleRatioX, scaleRatioY, pos, color);
	}
}

void Animation::Render(D3DXVECTOR2 pos, float rotateRadian) {
	if (sprites.size() == 0) {
		return;
	}
	if (sprites[curframeindex] != NULL) {
		sprites[curframeindex]->SetCustomRotateRadian(rotateRadian);
		sprites[curframeindex]->Render(pos, TransformationMode::CustomRotate);
	}
}

Animation::~Animation()
{
	/*for (auto s : sprites) 
	{
		s = nullptr;
	}*/
	sprites.clear();
}

void Animation::Update(float dt)
{
	if (this == NULL)
		return;
	if (!loop && (curframeindex == toframe))
	{
		return;
	}
	if (ticurframe > tiperframe)
	{
		ticurframe = 0;
		if (++curframeindex == toframe)
		{
			curframeindex = 0;
		}
	}
	else
	{
		ticurframe += dt;
	}
}

Sprite* Animation::getSprite(int index)
{
	return sprites[index];
}

Animation::Animation(Tag tag, int index)
{
	this->tag = tag;
	sprites.push_back(SpriteManager::getInstance()->getSprite(tag, index));
	toframe = 1;
	curframeindex = 0;
	tiperframe = TIME_PER_FRAME;
}

Animation::Animation(Tag tag, int first, int last, int timeperframe, bool _loop)
{
	this->tag = tag;
	loop = _loop;
	sprites = SpriteManager::getInstance()->getSprites(tag, first, last);
	toframe = sprites.size();
	curframeindex = 0;
	tiperframe = timeperframe;
}

int Animation::getWidth()
{
	auto spriteManager = SpriteManager::getInstance();
	return spriteManager->getSprite(this->tag, curframeindex)->getRECT().right - spriteManager->getSprite(this->tag, curframeindex)->getRECT().left;
}

int Animation::getHeight()
{
	auto spriteManager = SpriteManager::getInstance();
	return spriteManager->getSprite(this->tag, curframeindex)->getRECT().top - spriteManager->getSprite(this->tag, curframeindex)->getRECT().bottom;
}

void Animation::ReplaceSprite(int index, Sprite* sprite)
{
	if (index > sprites.size())//index truyền vào lớn hơn số sprite hiện có
		return;
	sprites[index] = sprite;
}

void Animation::DelayCurrentFrame(float delta)
{
	ticurframe -= delta;
}