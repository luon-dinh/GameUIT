#include "TileSet.h"

TileSet::TileSet(const char *tileSetFile, int _numOfTileType)
{
	TextureManager::getInstance()->addTexture(Tag::MAP1, tileSetFile);
	numOfTileType = _numOfTileType;

	tileSet = new Sprite[numOfTileType];

	for (int i = 0; i < numOfTileType; ++i)
	{
		tileSet = new Sprite(Tag::MAP1, 0, i*tileSize, tileSize, (i + 1)*tileSize);
	}
		
	tileSize = 
}

TileSet::~TileSet()
{
	delete tileSet;
}

void TileSet::DrawTile(int tileNum, D3DXVECTOR3 position)
{
	RECT cutRECT;
	cutRECT.top = 0;
	cutRECT.left = tileNum * tileSize;
	cutRECT.bottom = tileSize;
	cutRECT.right = cutRECT.left + tileSize;

	D3DXVECTOR3 center(tileSize / 2, tileSize / 2, 0);

	tileSet->Draw(cutRECT, center, position);
}

int TileSet::getTileSize()
{
	return tileSize;
}