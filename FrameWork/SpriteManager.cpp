﻿#include"SpriteManager.h"

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

	//Cắt sprite cho bảng exit.
	//Cắt sprite là cắt theo trục y hướng xuống.
	spriteManager->addSprite(new Sprite(Tag::EXITSIGN, 0, 0, 16, 32));
	spriteManager->addSprite(new Sprite(Tag::EXITSIGN, 0, 32, 16, 64));
	//Cắt sprite cho từng trạng thái của player
	spriteManager->addSprite(Tag::PLAYER, 0, 1);//stad
	spriteManager->addSprite(Tag::PLAYER, 1, 4);//run
	spriteManager->addSprite(Tag::PLAYER, 2, 1);//shieldup
	spriteManager->addSprite(Tag::PLAYER, 3, 1);//sit
	spriteManager->addSprite(Tag::PLAYER, 4, 1);//jump
	spriteManager->addSprite(Tag::PLAYER, 5, 2);//roll
	spriteManager->addSprite(Tag::PLAYER, 6, 1);//kick
	spriteManager->addSprite(Tag::PLAYER, 7, 2);//attack/throwshield
	spriteManager->addSprite(Tag::PLAYER, 8, 2);//punch_stand
	spriteManager->addSprite(Tag::PLAYER, 9, 2);//punching_sit
	spriteManager->addSprite(Tag::PLAYER, 10, 2);//dash
	spriteManager->addSprite(Tag::PLAYER, 11, 1);//shielddown
	spriteManager->addSprite(Tag::PLAYER, 12, 3);//hangon
	spriteManager->addSprite(Tag::PLAYER, 13, 1);//jumpdown
	spriteManager->addSprite(Tag::PLAYER, 14, 2);//jump form rotate
	spriteManager->addSprite(Tag::PLAYER, 15, 2);//die /onground 
	spriteManager->addSprite(Tag::PLAYER, 16, 3);//die onair
	spriteManager->addSprite(Tag::PLAYER, 17, 9); //flow
	spriteManager->addSprite(Tag::PLAYER, 18, 6); // dive
	//Cắt sprite cho từng trạng thái của shield
	spriteManager->addSprite(new Sprite(Tag::SHIELD, 0, 8, 16, 15));
	spriteManager->addSprite(new Sprite(Tag::SHIELD, 0, 27, 16, 42));
	spriteManager->addSprite(new Sprite(Tag::SHIELD, 3, 49, 12, 65));
	spriteManager->addSprite(new Sprite(Tag::SHIELD, 5, 69, 11, 92));
	//cắt sprite cho Item
	spriteManager->addSprite(new Sprite(Tag::ITEM, 0, 0, 14, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 14, 0, 28, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 28, 0, 42, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 42, 0, 56, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 56, 0, 70, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 70, 0, 84, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 70, 12, 84, 24));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 84, 0, 98, 12));
	// cắt sprite cho container
	spriteManager->addSprite(new Sprite(Tag::ITEMCONTAINER, 0, 0, 16, 16));
	spriteManager->addSprite(new Sprite(Tag::ITEMCONTAINER, 0, 16, 16, 32));
	//cắt sprite cho blue soldier
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDIER, 0, 0, 43, 24));
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDIER, 0, 24, 43, 48));
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDIER, 0, 48, 43, 72));
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDIER, 43, 0, 86, 24));
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDIER, 86, 0, 129, 24));
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDIER, 129, 0, 172, 24));
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