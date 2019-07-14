#include"Animation.h"
#include"Camera.h"
void Animation::Render(float x, float y)
{
	if (sprites.size()==0)
		return;
	if (sprites[curframeindex] != NULL)
	{
		sprites[curframeindex]->Render(x, y);	
	}
}

void Animation::Render(float x, float y, int first, int last)
{
	//for(int i=0;)

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
	sprites.push_back(SpriteManager::getInstance()->getSprite(tag, index));
	toframe = 1;
	curframeindex = 0;
	tiperframe = TIME_PER_FRAME;
}

Animation::Animation(Tag tag, int first, int last, int timeperframe)
{
	sprites = SpriteManager::getInstance()->getSprites(tag, first, last);
	toframe = sprites.size();
	curframeindex = 0;
	tiperframe = timeperframe;
}