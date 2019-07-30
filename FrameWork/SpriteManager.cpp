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
	spriteManager->addSprite(new Sprite(Tag::ITEM, 0, 0, 16, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 16, 0, 32, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 32, 0, 48, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 32, 12, 48, 24));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 48, 0, 64, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 64, 0, 80, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 80, 0, 96, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 96, 0, 112, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 96, 12, 112, 24));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 112, 0, 128, 12));
	spriteManager->addSprite(new Sprite(Tag::ITEM, 112, 12, 128, 24));
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
	//cắt sprite cho bullet explode
	spriteManager->addSprite(new Sprite(Tag::BULLETEXPLODE, 0, 0, 28, 30));
	spriteManager->addSprite(new Sprite(Tag::BULLETEXPLODE, 0, 30, 28, 60));
	spriteManager->addSprite(new Sprite(Tag::BULLETEXPLODE, 0, 60, 28, 90));

	//Cắt sprite cho hiệu ứng nổ của enemy.
	spriteManager->addSprite(new Sprite(Tag::ENEMYEXPLODE, 0, 0, 28, 30));
	spriteManager->addSprite(new Sprite(Tag::ENEMYEXPLODE, 0, 30, 28, 60));
	spriteManager->addSprite(new Sprite(Tag::ENEMYEXPLODE, 0, 60, 28, 90));
	//cắt sprite cho blue solder bullet
	spriteManager->addSprite(new Sprite(Tag::BLUESOLDERBULLET, 0, 0, 6, 6));
	//cắt sprite cho redrockerter bullet
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTERBULLET, 0, 0, 15, 15));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTERBULLET, 0, 15, 15, 30));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTERBULLET, 15, 0, 30, 15));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTERBULLET, 15, 15, 30, 30));
	//cắt sprite cho red rockerter
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTER, 0, 0, 46, 24));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTER, 0, 24, 46, 48));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTER, 0, 48, 46, 72));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTER, 46, 0, 92, 24));
	spriteManager->addSprite(new Sprite(Tag::REDROCKERTER, 92, 0, 138, 24));
	//cắt sprite cho white rockerter bullet
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTERBULLET, 0, 0, 15, 15));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTERBULLET, 0, 15, 15, 30));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTERBULLET, 15, 0, 30, 15));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTERBULLET, 15, 15, 30, 30));
	//cắt sprite cho white rockerter
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTER, 0, 0, 46, 24));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTER, 0, 24, 46, 48));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTER, 0, 48, 46, 72));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTER, 46, 0, 92, 24));
	spriteManager->addSprite(new Sprite(Tag::WHITEROCKERTER, 92, 0, 138, 24));
	//Cắt sprite cho white flying robot bullet.
	const int whiteFlyingRobotBulletSize = 17;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			spriteManager->addSprite(new Sprite(Tag::WHITEFLYINGROBOTBULLET, i*whiteFlyingRobotBulletSize, j*whiteFlyingRobotBulletSize, (i + 1)*whiteFlyingRobotBulletSize, (j + 1)*whiteFlyingRobotBulletSize));
		}
	}

	//Cắt sprite cho white flying robot.
	spriteManager->addSprite(new Sprite(Tag::WHITEFLYINGROBOT, 0, 0, 36, 27));
	spriteManager->addSprite(new Sprite(Tag::WHITEFLYINGROBOT, 0, 28, 36, 55));
	spriteManager->addSprite(new Sprite(Tag::WHITEFLYINGROBOT, 37, 0, 73, 27));
	spriteManager->addSprite(new Sprite(Tag::WHITEFLYINGROBOT, 37, 28, 73, 55));


	////Cắt sprite cho boss wizard.
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 3, 14, 52, 37));//stand 0
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 3, 66, 52, 89));//1 stand smile
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 3, 118, 52, 141));//2 stand smile
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 59, 10, 104, 41));//run 3
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 59, 70, 104, 86));//4
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 59, 115, 104, 144));//5
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 59, 174, 104, 190));//6
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 110, 12, 151, 41));//fall shooted 7
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 129, 60, 156, 93)); //die 8
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 136, 112, 156, 148)); //9
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 164, 15, 253, 39));//shoot 10
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 164, 53, 253, 91));//11
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 164, 111, 253, 143));//12
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 209, 12, 260, 41));//fly 13
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 209, 64, 260, 93));//14
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 209, 119, 260, 145));//15
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 268, 10, 312, 38));//stand punch 16
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 268, 54, 312, 90));//17
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