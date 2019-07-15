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
	//Cắt sprite cho water top.
	//Lấy ra chiều cao để biết load như thế nào.
	LPDIRECT3DTEXTURE9 waterTopTexture = TextureManager::getInstance()->getTexture(Tag::WATERTOP);
	D3DSURFACE_DESC desc;
	waterTopTexture->GetLevelDesc(0, &desc);
	int waterTopTextureSize = desc.Height;
	int numOfFrames = desc.Width / desc.Height;
	for (int i = 0; i < numOfFrames; ++i)
		spriteManager->addSprite(new Sprite(Tag::WATERTOP, 0, i*waterTopTextureSize, waterTopTextureSize, (i + 1)*waterTopTextureSize));

	//Cắt sprite cho water bottom.
	//Lấy ra chiều cao để biết load như thế nào.
	LPDIRECT3DTEXTURE9 waterBottomTexture = TextureManager::getInstance()->getTexture(Tag::WATERBOTTOM);
	waterBottomTexture->GetLevelDesc(0, &desc);
	int waterBottomTextureSize = desc.Height;
	numOfFrames = desc.Width / desc.Height;
	for (int i = 0; i < numOfFrames; ++i)
		spriteManager->addSprite(new Sprite(Tag::WATERBOTTOM, 0, i*waterBottomTextureSize, waterBottomTextureSize, (i + 1)*waterBottomTextureSize));

	//Cắt sprite cho sewer.
	//Lấy ra chiều cao để biết load như thế nào.
	LPDIRECT3DTEXTURE9 sewerTexture = TextureManager::getInstance()->getTexture(Tag::SEWER);
	sewerTexture->GetLevelDesc(0, &desc);
	int sewerTextureSize = desc.Height;
	numOfFrames = desc.Width / desc.Height;
	for (int i = 0; i < numOfFrames; ++i)
		spriteManager->addSprite(new Sprite(Tag::SEWER, 0, i*sewerTextureSize, sewerTextureSize, (i + 1)*sewerTextureSize));
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