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
	//PLAYER STANDING 0
	spriteManager->addSprite(Tag::PLAYER,0,1);
	//PLAYER RUNNING 1-4
	spriteManager->addSprite(Tag::PLAYER, 1, 4);
	//PLAYER SHIELDUP 5
	spriteManager->addSprite(Tag::PLAYER, 2, 1);
	//PLAYER SITTING 6
	spriteManager->addSprite(Tag::PLAYER, 3, 1);
	//PLAYER JUMPING 7
	spriteManager->addSprite(Tag::PLAYER, 4, 1);
	//PLAYER ROLLING 8-9
	spriteManager->addSprite(Tag::PLAYER, 5, 2);
	//PLAYER KICKING 10
	spriteManager->addSprite(Tag::PLAYER, 6, 1);
	// PLAYER ATTACKING
	spriteManager->addSprite(Tag::PLAYER, 7, 2);
	//PLAYER PUNCHING
	spriteManager->addSprite(Tag::PLAYER, 8, 2);
	//PLAYER ATTACKING_SIT
	spriteManager->addSprite(Tag::PLAYER, 9, 2);
	//PLAYER DASHING
	spriteManager->addSprite(Tag::PLAYER, 10, 2);
	// PLAYER SHIELDOWN
	spriteManager->addSprite(Tag::PLAYER,11, 1);
	//PLAYER HANGON
	spriteManager->addSprite(Tag::PLAYER, 12, 2);
	//PLAYER JUMP DOWN
	spriteManager->addSprite(Tag::PLAYER, 13, 1);
	//PLAYER JUMP FROM ROTATE
	spriteManager->addSprite(Tag::PLAYER, 14, 1);
	//PLAYER DIE
	spriteManager->addSprite(Tag::PLAYER, 15, 2);
	//PLAYER DIE ON AIR
	spriteManager->addSprite(Tag::PLAYER, 16, 3);
	//PLAYER FLOWING
	spriteManager->addSprite(Tag::PLAYER, 17, 9);
}

void SpriteManager::addSprite(Tag tag, int rowindex, int numberofsprites)
{
	SpriteManager *spriteManager = SpriteManager::getInstance();
	for (int i = 0; i < numberofsprites; i++)
	{
		spriteManager->addSprite(new Sprite(tag, rowindex * 56, i * 60, (rowindex + 1) * 56, (i + 1) * 60));
	}
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