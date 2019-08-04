#define _CRT_SECURE_NO_WARNINGS
#include "TileMap.h"
#include "Debug.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

TileMap::~TileMap()
{
	delete tileSet;
	for (int i = 0; i < maxRow; ++i)
	{
		delete tileMap[i];
	}
	delete tileMap;
}

TileMap::TileMap(const char * tileSetFile,const char * tileMapFile, Tag tag)
{
	//Đọc tileMapFile từ file txt và lưu vào ma trận map.
	std::ifstream inFile;
	inFile.open(tileMapFile);
	if (!inFile)
		PrintDebug("TileMap not exist ! \n");

	char* cInputString = nullptr;
	std::string sInputString;

	//Dòng đầu tiên sẽ chứa 3 thông số : Số loại tile, số tile theo hàng ngang, số tile theo hàng dọc.
	std::getline(inFile, sInputString);
	
	std::istringstream iss(sInputString);
	iss >> numOfTileType >> maxCol >> maxRow;

	/*
	//Đọc các thông số của dòng đầu tiên.
	char *p = strtok(cInputString, " "); //strtok dùng để cắt string.

	//Duyệt qua từng thông số.
	//Thông số đầu tiên : Số loại Tile.
	sscanf(p, "%d", &numOfTileType);
	p = strtok(NULL, " ");

	//Thông số thứ hai : Số tile theo hàng ngang (maxCol).
	sscanf(p, "%d", &maxCol);
	p = strtok(NULL, " ");

	//Thông số thứ ba : Số tile theo hàng dọc (maxRow).
	sscanf(p, "%d", &maxRow);
	*/
	//Khởi tạo tileMap.
	//Duyệt theo hàng ngang trước.
	tileMap = new int *[maxRow];

	for (int i = 0; i < maxRow; ++i)
	{
		//Một hàng sẽ có maxCol cột.
		tileMap[i] = new int[maxCol];
	}

	//Bắt đầu đọc thông tin map từ file.
	for (int i = maxRow - 1; i >= 0; --i)
	{
		std::getline(inFile, sInputString); //Đọc tiếp dòng kế hoy.
		std::istringstream iss(sInputString);
		for (int j = 0; j < maxCol; ++j)
		{
			iss >> tileMap[i][j];
		}
	}

	//Ta tạo TileSet chỉ khi map có tile.
	tileSet = new TileSet(tileSetFile, numOfTileType, tag);

	//Sau khi xong thì thông tin map đã được load đầy đủ.
	//Tiếp theo ta cần lấy thông tin kích cỡ tile.
	tileSize = tileSet->getTileSize();
}

void TileMap::Update(double dt)
{

}

void TileMap::Draw(Camera* camera)
{
	//StartRow, EndRow, StartCol, EndCol lúc nào cũng phải bao srcRECT 1 tile.
	//Quét theo chiều từ dưới lên, từ trái qua phải.

	RECT srcRECT = camera->getCameraRECT();

	int startCol = srcRECT.left / (tileSize) - 1;
	int endCol = srcRECT.right / (tileSize) + 1;
	int startRow = srcRECT.bottom / (tileSize) - 1;
	int endRow = srcRECT.top / (tileSize) + 1;

	int curRow = 0;
	int curCol = 0;
	for (int i = startRow; i <= endRow; ++i)
	{
		//Vẽ từng hàng ngang.
		//Xét điều kiện : Nếu hàng đang tính vẽ mà nằm ngoài map thì phải chỉnh lại.
		if (i < 0 || i >= maxRow)
			continue;
		curRow = i;
		for (int j = startCol; j <= endCol; ++j)
		{
			if (j < 0 || j >= maxCol)
				continue;

			curCol = j;

			int tileID = tileMap[curRow][curCol]; //Lấy tileID từ file text.

			//Tính toạ độ thực tế, xem ở WorldPort thì tile này sẽ vẽ ở đâu.
			D3DXVECTOR3 worldPos( curCol * tileSize + tileSize/2, curRow * (tileSize) + tileSize/2, 0);
			D3DXVECTOR3 viewPortPos = camera->convertWorldToViewPort(worldPos);
			tileSet->DrawTile(tileID, viewPortPos);
		}
	}
}