#include "Map.h"


const auto ADD_COL = (SCREEN_WIDTH >> 4) + 1;
//const auto MOVE_TILE = TILE_SIZE>>1;

Map::Map(int level)
{
	
	std::ifstream ifile;
	char fileName[30];
	int numSetTiles;
	sprintf_s(fileName, ".\\..\\Resources\\Texts\\map%d.txt", level+1);


	ifile.open(fileName);
	ifile >> numSetTiles;
	ifile >> columns;
	ifile >> rows;

	
	width = columns << 4;
	height = rows << 4;

	rect.width = width;
	rect.height = height;
	rect.x = 0;
	rect.y = rect.height;

	switch (level+1)
	{
	case 1:
		mapLevel = MAP1;
		break;

	case 2:
		mapLevel = MAP2;
		break;

	case 3:
		mapLevel = MAP3;
		break;
	case 4:
		mapLevel = MAP4;
	}

	auto sprites = SpriteManager::getInstance();
	for (int i = 0; i < numSetTiles; ++i)
	{
		sprites->addSprite(new Sprite(mapLevel, 0, i << 4, 16, i + 1 << 4));
	}

	mapTiles = new int* [rows];
	for (int r =0; r <rows; ++r)
	{
		mapTiles[r] = new int[columns];
		for (int c = 0; c < columns; ++c)
		{
			ifile >> mapTiles[r][c];
		}
	}
	ifile.close();
	
}

void Map::Update()
{
	Camera::GetInstance()->Update(this->rect);
	colBegin = max(0, Camera::GetInstance()->x / 16);
	colEnd = min(colBegin + ADD_COL, columns);
}

void Map::Render()
{
	auto sprites = SpriteManager::getInstance();

	for (auto r = 0; r != rows; ++r)
	{
		for (auto c = colBegin; c != colEnd; ++c)
		{
			auto sprite = sprites->getSprite(mapLevel, mapTiles[r][c]);
			sprite->Render(((c << 4)  - (int)Camera::GetInstance()->x), ((r << 4) ));
		}
	}
}