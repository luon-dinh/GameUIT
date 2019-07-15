#include"SpriteManager.h"

SpriteManager* SpriteManager::instance = NULL;

void SpriteManager::addSprite(Sprite *sprite)
{
	sprites[sprite->tag].push_back(sprite);
}

SpriteManager *SpriteManager::getInstance()
{
	if (!instance)
		instance = new SpriteManager();
	return instance;
}

void SpriteManager::LoadResources()
{
	auto spriteManager = SpriteManager::getInstance();
	//load resources
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 0, 0, 56, 60));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 0, 60, 56, 120));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 0, 120, 56, 180));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 0, 180, 56, 240));
}

Sprite* SpriteManager::getSprite(Tag tag, int index)
{
	return sprites[tag][index];
}

std::vector<Sprite*> SpriteManager::getSprites(Tag tag, int first, int last)
{
	std::vector<Sprite*> sprites;
	for (int i = first; i < last+1 ; i++)
	{
		sprites.push_back(this->sprites[tag][i]);
	}
	return sprites;
}