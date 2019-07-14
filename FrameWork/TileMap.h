#pragma once
#include "Sprite.h"
#include "TileSet.h"
#include "Camera.h"

class TileMap
{
	TileSet* tileSet; //Sprite của các loại tile.
	int maxCol;
	int maxRow;
	int tileSize;
	int numOfTileType;
	int ** tileMap; //File txt chứa Map.
public:
	//TileMap load theo hàng trước xong mới đến cột.
	TileMap(const char * tileSetFile, const char * tileMapFile);
	~TileMap();
	void Update();
	void Draw(Camera* camera);
};