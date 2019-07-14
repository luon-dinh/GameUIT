#include"TextureManager.h"

TextureManager* TextureManager::instance = NULL;

void TextureManager::loadResources()
{
	auto textures = TextureManager::getInstance();
	//textures->addTexture(Tag::PLAYER,".\\..\\Resources\\Images\\charleston_boss_map.png");
	textures->addTexture(Tag::MAP1, ".\\..\\Resources\\Images\\map1.png");
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
