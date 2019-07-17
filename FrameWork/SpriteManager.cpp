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
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 4, 19, 49, 41));
	//PLAYER RUNNING 1-4
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 18, 105, 42));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 78, 105, 102));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 138, 105, 162));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 198, 105, 222));

	//PLAYER SHIELDUP 5
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 118, 18, 161, 42));
	//PLAYER SITTING 6
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 189, 18, 217, 42));
	//PLAYER JUMPING 7
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 232, 19, 270, 41));
	//PLAYER ROLLING 8-9
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 296, 20, 321, 40));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 296, 80, 321, 100));
	//PLAYER KICKING 10
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 352, 0, 377, 40));
	// PLAYER ATTACKING
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 402, 19, 441, 52));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 402, 62, 441, 101));
	//PLAYER PUNCHING
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 456, 3, 497, 41));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 456, 72, 497, 101));
	//PLAYER ATTACKING_SIT
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 526, 5, 553, 42));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 526, 74, 553, 102));
	//PLAYER DASHING
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 580, 9, 609, 42));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 580, 60, 609, 99));
	// PLAYER SHIELDOWN
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 636, 20, 662, 42));
	//PLAYER HANGON
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 672, 20, 728, 40));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 672, 80, 728, 100));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 672, 140, 728, 160));
	//PLAYER JUMP DOWN
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 751, 19, 778, 41));
	//PLAYER JUMP FROM ROTATE
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 795, 20, 833, 40));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 795, 80, 833, 100));
	//PLAYER DIE
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 861, 12, 889, 42));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 861, 76, 889, 102));
	//PLAYER DIE ON AIR
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 905, 8, 945, 41));
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 905, 72, 945, 102));
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
	for (int i = first; i < last ; i++)
	{
		sprites.push_back(this->sprites[tag][i]);
	}
	return sprites;
}