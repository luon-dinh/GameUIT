#include"TextureManager.h"

TextureManager* TextureManager::instance = NULL;

void TextureManager::loadResources()
{
	auto textures = TextureManager::getInstance();
	textures->addTexture(Tag::PLAYER,".\\..\\Resources\\Images\\Captain_State\\SpriteSheetCaptain.png");
	//textures->addTexture(Tag::ITEM, ".\\..\\Resources\\Images\\captainstand.png");
	textures->addTexture(Tag::WATERTOP, AnimFilePath::WATER_TOP_ANIM);
	textures->addTexture(Tag::WATERBOTTOM, AnimFilePath::WATER_BOTTOM_ANIM);
	textures->addTexture(Tag::SEWER, AnimFilePath::SEWER_ANIM);
	textures->addTexture(Tag::EXITSIGN, AnimFilePath::EXIT_SIGN);
	//Thêm textures này vào để debug.
	textures->addTexture(Tag::TESTMAPOBJECTRED, (char*)".\\..\\Resources\\Images\\red_8_8.png");
	textures->addTexture(Tag::TESTMAPOBJECTBLUE, (char*)".\\..\\Resources\\Images\\blue_8_8.png");
	textures->addTexture(Tag::SHIELD, (char*)".\\..\\Resources\\Images\\SpriteSheetCaptainShield.png");
	//texture dung cho ITEM
	textures->addTexture(Tag::ITEM, (char*)".\\..\\Resources\\Images\\Item\\Items.png");
	//texture dung cho CONTAINER
	textures->addTexture(Tag::ITEMCONTAINER, (char*)".\\..\\Resources\\Images\\Item\\Container.png");
	//texture dùng cho blue soldier
	textures->addTexture(Tag::BLUESOLDIER, (char*)".\\..\\Resources\\Images\\Enermy\\BlueSoldier.png");
	textures->addTexture(Tag::BLUESOLDERBULLET, (char*)".\\..\\Resources\\Images\\Enermy\\SoldierBullet.png");
	//textures->addTexture(Tag::MAP1, ".\\..\\Resources\\Images\\map1.png");
	//add texture dùng cho bullet explode
	textures->addTexture(Tag::BULLETEXPLODE, (char*)".\\..\\Resources\\Images\\Enermy\\BulletExplode.png");
	//texture dùng cho redrockerter
	textures->addTexture(Tag::REDROCKERTERBULLET, (char*)".\\..\\Resources\\Images\\Enermy\\RedRockerterBullet.png");
	textures->addTexture(Tag::REDROCKERTER, (char*)".\\..\\Resources\\Images\\Enermy\\RedRockerter.png");
	//texture dùng cho white rockerter
	textures->addTexture(Tag::WHITEROCKERTER, (char*)".\\..\\Resources\\Images\\Enermy\\WhiteRockerter.png");
	textures->addTexture(Tag::WHITEROCKERTERBULLET, (char*)".\\..\\Resources\\Images\\Enermy\\BulletWhiteRockerter.png");
};
void TextureManager::addTexture(Tag tag, const char* path)
{
	textures[tag] = (new Texture(path))->getTexture();
	
}

LPDIRECT3DTEXTURE9 TextureManager::getTexture(Tag tag)
{
	return textures[tag];
}

TextureManager* TextureManager::getInstance()
{
	if (!instance)
		instance = new TextureManager();
	return instance;
}
