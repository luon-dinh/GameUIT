#include"Animation.h"
void Animation::Render(float x, float y)
{
	if (sprites.size()==0)
		return;
	if (sprites[curframeindex] != NULL)
	{
		sprites[curframeindex]->Render(x, y);	
	}
}

void Animation::Render(D3DXVECTOR2 pos)
{
	Render(pos.x, pos.y);
}

void Animation::Render(D3DXVECTOR3 pos)
{
	Render(D3DXVECTOR2(pos.x,pos.y));
}

void Animation::Render(float x, float y, int first, int last)
{
	//for(int i=0;)

}

void Animation::Render(D3DXVECTOR2 pos, TransformationMode transMode, float scaleRatio) {
	if (sprites.size() == 0)
		return;
	if (sprites[curframeindex] != NULL)
	{
		sprites[curframeindex]->Render(transMode, scaleRatio, pos);
	}
}

Animation::~Animation()
{
	for (auto s : sprites)
	{
		s = nullptr;
	}
	sprites.clear();
}

void Animation::Update(float dt)
{
	if (this == NULL)
		return;
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

Animation::Animation(Tag tag, int first, int last, int timeperframe)
{
	this->tag = tag;
	sprites = SpriteManager::getInstance()->getSprites(tag, first, last);
	toframe = sprites.size();
	curframeindex = 0;
	tiperframe = timeperframe;
}

Animation::Animation(Tag tag, int rowindex, int numofsprites)
{
	this->tag = tag;
	for (int i = 0; i < numofsprites; i++)
	{
		sprites.push_back(new Sprite(this->tag, rowindex * 56, i * 60, (rowindex + 1) * 56, (i + 1) * 60));
	}
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