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
	textures->addTexture(Tag::ITEM, (char*)".\\..\\Resources\\Images\\Item\\EvenPixelWidthItem.png");
	//textures->addTexture(Tag::MAP1, ".\\..\\Resources\\Images\\map1.png");
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
