#pragma once
#include "Sprite.h"
#include <d3dx9.h>
#include <d3d9.h>

class TileSet
{
	Sprite** tileSet;
	int tileSize;
	int numOfTileType;
public:
	TileSet(const char * tileSetFile, int _numOfTileType);
	~TileSet();
	void DrawTile(int tileNum, D3DXVECTOR3 position); //Vẽ một tile với tileNum tương ứng lên vị trí position.
	int getTileSize();
};