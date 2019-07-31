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
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 4, 19, 49, 41));//stand 0
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 18, 105, 42));//run 1
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 78, 105, 102)); //2
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 138, 105, 162)); //3
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 62, 198, 105, 222)); //4
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 118, 18, 161, 42)); //shield up 5
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 189, 18, 217, 42));// duck //6
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 235, 19, 273, 41));//jump 7
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 305, 19, 324, 39));//roll 8
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 305, 81, 324, 100)); //9
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 305, 141, 324, 161));//10
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 305, 200, 324, 220));//11
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 353, 0, 378, 40));//kick 12
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 402, 18, 441, 52));// shield attack 13
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 402, 62, 441, 101));//14
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 456, 3, 497, 41));//stand punch //15
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 456, 72, 497, 101));//16
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 526, 3, 553, 42));// duck punch 17
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 526, 74, 553, 102));//18
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 581, 18, 609, 42));//dash //19
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 581, 61, 609, 92));//20
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 581, 110, 609, 149));//21
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 638, 20, 665, 41));//shield down 22
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 671, 21, 724, 40));//hang on 23
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 671, 80, 724, 100));//24
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 671, 144, 724, 160));//25
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 861, 12, 889, 41));//die stand/26
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 861, 76, 889, 101));//27
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 12, 992, 44));//float 28
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 72, 992, 104));//29
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 132, 992, 164));//30
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 199, 992, 219));//31
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 262, 992, 278));//32
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 326, 992, 334));//33
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 385, 992, 394));//34
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 441, 992, 459));//35
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 965, 502, 992, 518));//36
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 1040, 262, 1048, 278));//diving //37
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 1040, 322, 1048, 338));//38
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 905, 12,943, 41));//die on air!=none 39
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 917, 72, 945, 102));//40
	spriteManager->addSprite(new Sprite(Tag::PLAYER, 922, 136, 945, 162));//41

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
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 164, 15, 203, 39));//shoot 10
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 164, 53, 203, 91));//11
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 164, 111, 203, 143));//12
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 209, 12, 260, 41));//fly 13
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 209, 64, 260, 93));//14
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 209, 119, 260, 145));//15
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 268, 10, 312, 38));//stand punch 16
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARD, 268, 54, 312, 90));//17
	//cắt sprite cho wizard bullet
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARDBULLET, 4, 0, 12, 16));//0
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARDBULLET, 0, 16, 16, 32));//1
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARDBULLET, 0, 36, 16, 43));//2
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARDBULLET, 20, 4, 28, 11));//3
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARDBULLET, 21, 20, 27, 28));//4
	spriteManager->addSprite(new Sprite(Tag::BOSSWIZARDBULLET, 21, 36, 26, 44));//5

	// cắt sprite cho HP
	spriteManager->addSprite(new Sprite(Tag::HP_RENDER, 0, 0, 8, 8));
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